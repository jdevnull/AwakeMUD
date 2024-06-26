/* ************************************************************************
*   File: weather.c                                     Part of CircleMUD *
*  Usage: functions handling time and the weather                         *
*                                                                         *
*  All rights reserved.  See license.doc for complete information.        *
*                                                                         *
*  Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University *
*  CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.               *
************************************************************************ */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "structs.hpp"
#include "awake.hpp"
#include "utils.hpp"
#include "comm.hpp"
#include "handler.hpp"
#include "interpreter.hpp"
#include "db.hpp"
#include "newmagic.hpp"
extern struct time_info_data time_info;
extern struct char_data *character_list;
extern struct index_data *mob_index;

void weaken_or_terminate_spirits(bool sunrise);

const char *moon[] =
  {
    "new",
    "waxing",
    "full",
    "waning",
    "\n"
  };

bool precipitation_is_snow(int jurisdiction) {
  time_t s = time(NULL);
  struct tm* current_time = localtime(&s);

  // It only snows in Seattle. Portland can go fuck itself.
  if (jurisdiction != JURISDICTION_SEATTLE)
    return FALSE;

  // Our version of Seattle snows in December and January.
  return (current_time->tm_mon + 1) == 12 || (current_time->tm_mon + 1) == 1;
}

void another_hour(void)
{
  bool new_month = FALSE;
  const char *temp;

  time_info.hours++;

  switch (time_info.hours) {
  case 7:
    weather_info.sunlight = SUN_RISE;
    if (weather_info.sky == SKY_CLOUDLESS)
      temp = "^y";
    else
      temp = "^L";
    snprintf(buf, sizeof(buf), "%sThe sun rises in the east.^n\r\n", temp);
    send_to_outdoor(buf, TRUE, FALSE);
    snprintf(buf, sizeof(buf), "%sThe murky light of the sun dawns behind the clouds.^n\r\n", temp);
    send_to_outdoor(buf, TRUE, TRUE);

    weaken_or_terminate_spirits(TRUE);
    
    break;
  case 9:
    weather_info.sunlight = SUN_LIGHT;
    switch (weather_info.sky) {
    case SKY_CLOUDLESS:
      temp = "^Y";
      break;
    case SKY_CLOUDY:
    case SKY_RAINING:
      temp = "^n";
      break;
    case SKY_LIGHTNING:
      temp = "^L";
      break;
    default:
      temp = "^Y";
      break;
    }
    snprintf(buf, sizeof(buf), "%sThe day has begun.^n\r\n", temp);
    send_to_outdoor(buf, TRUE, FALSE);
    if (weather_info.sky < SKY_CLOUDY || weather_info.sky > SKY_LIGHTNING)
      temp = "^o";
    snprintf(buf, sizeof(buf), "%sThe day has begun.^n\r\n", temp);
    send_to_outdoor(buf, TRUE, TRUE);
    break;
  case 18:
    weather_info.sunlight = SUN_SET;
    switch (weather_info.sky) {
    case SKY_CLOUDLESS:
      temp = "^r";
      break;
    case SKY_CLOUDY:
      temp = "^B";
      break;
    case SKY_RAINING:
      temp = "^b";
      break;
    case SKY_LIGHTNING:
      temp = "^L";
      break;
    default:
      temp = "^r";
      break;
    }
    snprintf(buf, sizeof(buf), "%sThe sun slowly disappears in the west.^n\r\n", temp);
    send_to_outdoor(buf, TRUE, FALSE);
    snprintf(buf, sizeof(buf), "%sThe sun sullenly sinks into the west.^n\r\n", temp);
    send_to_outdoor(buf, TRUE, TRUE);

    weaken_or_terminate_spirits(FALSE);
    
    break;
  case 21:
    weather_info.sunlight = SUN_DARK;
    if (weather_info.sky == SKY_CLOUDLESS)
      snprintf(buf, sizeof(buf), "^bThe night has begun. The moon is %s.^n\r\n",moon[weather_info.moonphase]);
    else
      snprintf(buf, sizeof(buf), "^LThe night has begun.^n\r\n");

    send_to_outdoor(buf, TRUE, FALSE);
    send_to_outdoor(buf, TRUE, TRUE);
    break;
  }

  if (time_info.hours > 23) {
    time_info.hours -= 24;
    time_info.day++;
    time_info.weekday++;
    if (time_info.weekday > 6)
      time_info.weekday = 0;

    if (((time_info.month == 3) || (time_info.month == 5) ||
         (time_info.month == 8) || (time_info.month == 10)) &&
        (time_info.day > 29))
      new_month = TRUE;
    else if ((time_info.month == 1) && (time_info.day > 27))
      new_month = TRUE;
    else if (time_info.day > 30)
      new_month = TRUE;
    if (new_month) {
      time_info.day = 0;
      time_info.month++;

      if (time_info.month > 11) {
        time_info.month = 0;
        time_info.year++;
      }
    }
  }
  if(time_info.day < 7)
    weather_info.moonphase = MOON_NEW;
  else if(time_info.day > 7 && time_info.day < 14)
    weather_info.moonphase = MOON_WAX;
  else if(time_info.day > 14 && time_info.day < 21)
    weather_info.moonphase = MOON_FULL;
  else
    weather_info.moonphase = MOON_WANE;

}

void another_minute(void)
{
  time_info.minute++;

  if (time_info.minute >= 60) {
    time_info.minute = 0;
    another_hour();
  }
}

void weather_change(void)
{
  PERF_PROF_SCOPE(pr_, __func__);
  int diff, change;

  if ((time_info.month >= 8) && (time_info.month <= 12))
    diff = (weather_info.pressure > 985 ? -2 : 2);
  else
    diff = (weather_info.pressure > 1015 ? -2 : 2);

  weather_info.change += (dice(1, 4) * diff + dice(2, 6) - dice(2, 6));

  weather_info.change = MIN(weather_info.change, 12);
  weather_info.change = MAX(weather_info.change, -12);

  weather_info.pressure += weather_info.change;

  weather_info.pressure = MIN(weather_info.pressure, 1040);
  weather_info.pressure = MAX(weather_info.pressure, 960);

  change = 0;
  switch (weather_info.sky) {
  case SKY_CLOUDLESS:
    if (weather_info.pressure < 990)
      change = 1;
    else if (weather_info.pressure < 1010)
      if (dice(1, 4) == 1)
        change = 1;
    break;
  case SKY_CLOUDY:
    if (weather_info.pressure < 970)
      change = 2;
    else if (weather_info.pressure < 990)
      if (dice(1, 4) == 1)
        change = 2;
      else
        change = 0;
    else if (weather_info.pressure > 1030)
      if (dice(1, 4) == 1)
        change = 3;
    break;
  case SKY_RAINING:
    if (weather_info.pressure < 970)
      if (dice(1, 4) == 1)
        change = 4;
      else
        change = 0;
    else if (weather_info.pressure > 1030)
      change = 5;
    else if (weather_info.pressure > 1010)
      if (dice(1, 4) == 1)
        change = 5;
    break;
  case SKY_LIGHTNING:
    if (weather_info.pressure > 1010)
      change = 6;
    else if (weather_info.pressure > 990)
      if (dice(1, 4) == 1)
        change = 6;
    break;
  default:
    change = 0;
    weather_info.sky = SKY_CLOUDLESS;
    break;
  }

  if (change == 1) {
    send_to_outdoor("^LThe sky starts to get cloudy.^n\r\n", TRUE, FALSE);
    send_to_outdoor("^LThe clouds start to thicken.^n\r\n", TRUE, TRUE);
    weather_info.sky = SKY_CLOUDY;
  }

  if (change == 3) {
    send_to_outdoor("^CThe clouds disappear.^n\r\n", TRUE, FALSE);
    send_to_outdoor("^CThe clouds start to thin.^n\r\n", TRUE, TRUE);
    weather_info.sky = SKY_CLOUDLESS;
  }

  if (change == 2 || (change >= 4 && change <= 6)) {
    for (struct descriptor_data *i = descriptor_list; i; i = i->next) {
      if (!i->connected && i->character && AWAKE(i->character) &&
          !(PLR_FLAGGED(i->character, PLR_WRITING) ||
            PLR_FLAGGED(i->character, PLR_EDITING) ||
            PLR_FLAGGED(i->character, PLR_MAILING) ||
            PLR_FLAGGED(i->character, PLR_MATRIX) ||
            PLR_FLAGGED(i->character, PLR_REMOTE)) &&
          OUTSIDE(i->character)) 
      {

        if (PRF_FLAGGED(i->character, PRF_NO_WEATHER) ||
            (i->original && PRF_FLAGGED(i->original, PRF_NO_WEATHER)))
        {
          continue;
        }

        int jurisdiction = GET_JURISDICTION(get_ch_in_room(i->character));
        switch (change) {
          case 2:
            if (precipitation_is_snow(jurisdiction)) {
              SEND_TO_Q("^WIt starts to snow.^n\r\n", i);
            } else {
              if (jurisdiction == JURISDICTION_SECRET) {
                SEND_TO_Q("^BDrops of bitter rain start to fall around you.^n\r\n", i);
              } else {
                SEND_TO_Q("^BIt starts to rain.^n\r\n", i);
              }
            }
            weather_info.sky = SKY_RAINING;
            break;
          case 4:
            if (precipitation_is_snow(jurisdiction)) {
              SEND_TO_Q("^WThe snow intensifies.^n\r\n", i);
            } else {
              SEND_TO_Q("^WLightning^L starts to show in the sky.^n\r\n", i);
            }
            weather_info.sky = SKY_LIGHTNING;
            break;
          case 5:
            if (precipitation_is_snow(jurisdiction)) {
              SEND_TO_Q("^cThe snow stops.^n\r\n", i);
            } else {
              if (jurisdiction == JURISDICTION_SECRET) {
                SEND_TO_Q("^cThe acrid rain peters out.^n\r\n", i);
              } else {
                SEND_TO_Q("^cThe rain stops.^n\r\n", i);
              }
            }
            weather_info.sky = SKY_CLOUDY;
            weather_info.lastrain = 0;
            break;
          case 6:
            if (precipitation_is_snow(jurisdiction)) {
              SEND_TO_Q("^WThe heavy snow slackens to light flurries now and then.^n\r\n", i);
            } else {
              SEND_TO_Q("^cThe ^Wlightning^c stops.^n\r\n", i);
            }
            weather_info.sky = SKY_RAINING;
            break;
        }
      }
    }
  }

  if (weather_info.sky < SKY_RAINING)
    weather_info.lastrain++;
}

void weaken_or_terminate_spirits(bool sunrise) {
      bool should_loop = TRUE;
      int loop_rand = rand();
      int loop_counter = 0;

      while (should_loop) {
        should_loop = FALSE;
        loop_counter++;

        for (struct char_data *ch = character_list; ch; ch = ch->next_in_character_list) {
          if (ch->last_loop_rand == loop_rand) {
            continue;
          } else {
            ch->last_loop_rand = loop_rand;
          }
          
          if (IS_PC_CONJURED_SPIRIT(ch)) {
            if (--GET_SPARE2(ch) <= 0) {
              act("$n abruptly fades from existance.", TRUE, ch, 0, 0, TO_ROOM);
              end_spirit_existance(ch, FALSE);
              should_loop = TRUE;
              break;
            } else {
              if (sunrise) {
                act("$n weakens as the metaphysical power of sunrise ripples through it.\r\n", TRUE, ch, 0, 0, TO_ROOM);
              } else {
                act("$n weakens as the metaphysical power of sunset ripples through it.\r\n", TRUE, ch, 0, 0, TO_ROOM);
              }
            }
          }
        }

        if (loop_counter > 1) {
          // mudlog_vfprintf(NULL, LOG_SYSLOG, "Looped %d times over weaken_or_terminate_spirits().", loop_counter);
        }
      }
    }