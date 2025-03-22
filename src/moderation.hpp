#ifndef __moderation_h__
#define __moderation_h__

#include <regex.h>

#define AUTOMOD_FREEZE_THRESHOLD  2

#define MODERATION_MODE_NORMAL       0
#define MODERATION_MODE_DESCRIPTIONS 1

#define GET_AUTOMOD_COUNTER(ch)  (((ch) && (ch)->player_specials) ? (ch)->player_specials->saved.automod_counter : 0)
#define GET_SETTABLE_AUTOMOD_COUNTER(ch) ((ch)->player_specials->saved.automod_counter)

class automod_entry {
public:
    const char *stringified_regex;
    const char *explanation;
    regex_t *compiled_regex;

    void compile();

    ~automod_entry() {
        if (compiled_regex) {
            regfree(compiled_regex);
        }
    }
};

// This is only run once in comm.cpp at boot.
void prepare_compiled_regexes();

bool check_for_banned_content(const char *msg, struct char_data *speaker, int moderation_mode=MODERATION_MODE_NORMAL);

#ifdef osx
#define REGEX_SEP_START "[[:<:]]"
#define REGEX_SEP_END   "[[:>:]]"
#else
#define REGEX_SEP_START "\\b"
#define REGEX_SEP_END   "\\b"
#endif

#endif