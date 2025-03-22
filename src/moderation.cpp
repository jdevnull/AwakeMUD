// Moderation systems.

#include <vector>
#include <regex.h>

#include "awake.hpp"
#include "structs.hpp"
#include "db.hpp"
#include "handler.hpp"
#include "comm.hpp"
#include "moderation.hpp"

extern int add_or_rewrite_ban_entry(const char *site, int ban_type, const char *banned_by);
extern int isbanned(char *hostname);

// TODO: Read this from a file on disk. Check in an empty copy of that file so people can't see your filters.
// Note that all regexes will automatically be surrounded by .*\b\b.* when compiled.
std::vector<class automod_entry> automod_entries = {
  {"say_this_if_you_want_to_get_banned", "This is a test phrase to ensure automod is working, but it'll ban you all the same.", NULL}
};

std::vector<class automod_entry> additional_restring_entries = {
  {"rising\\ssun", "The Rising Sun is the imperialist Japanese flag, which in Shadowrun is associated with high degrees of racism. Playing characters with Imperialist Japanese allegiances often leads to reactive roleplay of counter-Japanese sentiment, which runs afoul of our policy against portraying IRL racisms. As such, we don't allow the use of the Rising Sun symbol in restrings. If you meant to discuss the actual sun as it rose, we apologize for this and recommend you use 'sunrise' etc instead.", NULL}
};

void automod_entry::compile() {
  int compilation_code;
  char pattern[1000];
  compiled_regex = new regex_t;

  snprintf(pattern, sizeof(pattern), "%s%s%s", REGEX_SEP_START, stringified_regex, REGEX_SEP_END);

  // log_vfprintf("Compiling regex pattern '%s' (base pattern '%s')...", pattern, base_pattern);

  if ((compilation_code = regcomp(compiled_regex, pattern, REG_ICASE | REG_EXTENDED))) {
    char errbuf[2048] = { '\0' };
    regerror(compilation_code, compiled_regex, errbuf, sizeof(errbuf));
    mudlog_vfprintf(NULL, LOG_SYSLOG, "SYSERR: Failed to compile regex '%s': %s.", pattern, errbuf);
    delete compiled_regex;
    compiled_regex = NULL;
  }
}

void prepare_compiled_regexes() {
  log("Compiling regexes for automod...");
  for (auto &entry : automod_entries) {
    entry.compile();
  }
  for (auto &entry : additional_restring_entries) {
    entry.compile();
  }
}

bool _compare_string_to_regex_vector(const char *msg, struct char_data *speaker, std::vector<class automod_entry> *entries) {
  rnum_t frozen_rnum = real_room(10044);
  regmatch_t match_array[1];
  int match_code;

  for (auto &entry : *entries) {
    if (!entry.compiled_regex)
      continue;

    // No match, no problem.
    if ((match_code = regexec(entry.compiled_regex, msg, 1, match_array, 0)) == REG_NOMATCH)
      continue;

    // Match? Problem.
    else if (match_code == 0) {
      // Extract the offending phrase.
      char matched_string[MAX_INPUT_LENGTH + 2];
      memset(matched_string, 0, sizeof(matched_string));
      memcpy(matched_string, msg + match_array[0].rm_so, match_array[0].rm_eo - match_array[0].rm_so);

      // I don't want to get frozen while testing this, so high-level staff are immune.
      if (GET_LEVEL(speaker) >= LVL_CONSPIRATOR) {
        send_to_char(speaker, "WARNING: You would have been dinged by automod for that command (tripped: %s). It has been blocked from execution.\r\n", matched_string);
        mudlog_vfprintf(speaker, LOG_WIZLOG, "Automoderator staff warning: Staff member %s wrote banned content '''%s''' (tripped: %s).", GET_CHAR_NAME(speaker), msg, matched_string);
        return TRUE;
      }

      int strikes = (speaker->player_specials ? ++speaker->player_specials->saved.automod_counter : AUTOMOD_FREEZE_THRESHOLD + 1);

      // Not enough strikes to be frozen? Just warn.
      if (strikes < AUTOMOD_FREEZE_THRESHOLD) {
        // Notify player.
        mudlog_vfprintf(speaker, LOG_WIZLOG, "AUTOMODERATOR WARNED: %s attempted to write '''%s''' (tripped: %s). Issued warning, strike %d/%d.", GET_CHAR_NAME(speaker), msg, matched_string, strikes, AUTOMOD_FREEZE_THRESHOLD);
        send_to_char(speaker, "^RYou're not allowed to write '%s'.^n Your command has been aborted."
                              " Please be cautious: continued triggerings of the automated moderator system"
                              " will result in your play session being halted for staff review.\r\n", matched_string);
        send_to_char(speaker, "\r\nContext: %s\r\n", entry.explanation);
        return TRUE;
      } else {
        // Knock the threshold back down to 0 (they're already frozen, and this cleans up paperwork for if they're unfrozen):
        if (speaker->player_specials) {
          speaker->player_specials->saved.automod_counter = 0;
        }

        // Log it.
        mudlog_vfprintf(speaker, LOG_WIZLOG, "AUTOMODERATOR FROZE AN OFFENDER: %s attempted to write '''%s''' (tripped: '%s'). Freezing and transporting away for staff review.", GET_CHAR_NAME(speaker), msg, matched_string);

        // Ban new character registrations from their IP, provided they weren't already banned.
        if (speaker->desc && isbanned(speaker->desc->host) < BAN_NEW) {
          add_or_rewrite_ban_entry(speaker->desc->host, BAN_NEW, "automod system");
          mudlog_vfprintf(speaker, LOG_WIZLOG, "AUTOMODERATOR HAS BANNED NEW CHARACTERS FROM %s.", speaker->desc->host);
        }

        // Notify player.
        send_to_char(speaker, "^RYou're not allowed to write '%s'.^n Your character has been frozen pending staff review. Reach out on Discord if you need this expedited (link is on our website, file a ticket in #support-main).\r\n", matched_string);
        send_to_char(speaker, "\r\nFor further info on why that word is disallowed, check out %s.\r\n", entry.explanation);

        // Freeze the character.
        PLR_FLAGS(speaker).SetBit(PLR_FROZEN);
        GET_FREEZE_LEV(speaker) = MAX(2, GET_FREEZE_LEV(speaker));

        // Transport away.
        if (frozen_rnum >= 0) {
          act("$n is whisked away by the game administration.", TRUE, speaker, 0, 0, TO_ROOM);
          char_from_room(speaker);
          char_to_room(speaker, &world[frozen_rnum]);
          act("$n is unceremoniously deposited at the conference table.", TRUE, speaker, 0, 0, TO_ROOM);
        }
      }

      return TRUE;
    }

    // If you've gotten here, you encountered an error while processing the regex.
    char errbuf[2048] = { '\0' };
    regerror(match_code, entry.compiled_regex, errbuf, sizeof(errbuf));
    mudlog_vfprintf(speaker, LOG_SYSLOG, "SYSERR: Failed to run regex against '%s': %s.", msg, errbuf);
  }

  return FALSE;
}

// Given a string, search it for offensive terms. If found, log for staff and freeze/remove the character.
bool check_for_banned_content(const char *raw_msg, struct char_data *speaker, int moderation_mode) {
  if (!raw_msg || !speaker) {
    mudlog_vfprintf(speaker, LOG_SYSLOG, "SYSERR: Received invalid arguments to check_for_banned_content('''%s''', %s).", raw_msg ? raw_msg : "NULL", speaker ? GET_CHAR_NAME(speaker) : "NULL");
    return FALSE;
  }

  // We don't care about messages from non-puppeted NPCs. Presumably, they've been vetted.
  if (!speaker->desc)
    return FALSE;

  // Strip color codes from content.
  const char *msg = get_string_after_color_code_removal(raw_msg, NULL);

  // Iterate through all regexes, applying them to the message.
  if (_compare_string_to_regex_vector(msg, speaker, &automod_entries))
    return TRUE;

  if (moderation_mode == MODERATION_MODE_DESCRIPTIONS && _compare_string_to_regex_vector(msg, speaker, &additional_restring_entries))
    return TRUE;

  // No banned content detected.
  return FALSE;
}