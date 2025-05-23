
#ifndef _olc_h_
#define _olc_h_

#define NUM_BARRIERS            9
#define NUM_AFF_FLAGS           22

#define WEAPON_MAXIMUM_STRENGTH_BONUS 4

// extern functions
extern void write_index_file(const char *suffix);
extern bool can_edit_zone(struct char_data *ch, struct zone_data *zone);

// Message sent in function.
extern bool is_olc_available(struct char_data *ch);

#define CH              d->character
#ifdef NO_CLS
#define CLS(ch)         ;
#else
#define CLS(ch)         send_to_char("\033[H\033[J", ch)
#endif
#define ZCMD            zone_table[zone].cmd[cmd_no]

#define VEDIT_CONFIRM_EDIT           0
#define VEDIT_MAIN_MENU              1
#define VEDIT_EDIT_NAMELIST          2
#define VEDIT_SHORTDESC              3
#define VEDIT_DESC                   4
#define VEDIT_LONGDESC               5
#define VEDIT_INSDESC       6
#define VEDIT_CONFIRM_SAVEDB         7
#define VEDIT_CONFIRM_SAVESTRING     8
#define VEDIT_PROMPT_APPLY           9
#define VEDIT_LEAVE	10
#define VEDIT_ARRIVE	11
#define VEDIT_ATT	12
#define VEDIT_HAND	13
#define VEDIT_SP	14
#define VEDIT_ACC	15
#define VEDIT_BOD	16
#define VEDIT_ARMOR	17
#define VEDIT_SIG	18
#define VEDIT_AUTO      19
#define VEDIT_LOAD      20
#define VEDIT_SEAT      21
#define VEDIT_SEAT2     22
#define VEDIT_COST      23
#define VEDIT_TYPE      24
#define VEDIT_PILOT	25
#define VEDIT_FLAGS	26
#define VEDIT_REARDESC	27
#define VEDIT_ENGINE		28

#define HEDIT_CONFIRM_EDIT	0
#define HEDIT_MAIN_MENU		1
#define HEDIT_TRIGGER		2
#define HEDIT_NAME		3
#define HEDIT_PARENT		4
#define HEDIT_KEYWORDS		5
#define HEDIT_DESC		6
#define HEDIT_SECURITY_COLOR	7
#define HEDIT_SECURITY_RATING	8
#define HEDIT_SECURITY_DIFF	9
#define HEDIT_TYPE		10
#define HEDIT_CONFIRM_SAVESTRING 11
#define HEDIT_EXIT		12
#define HEDIT_RATINGS		13
#define HEDIT_RATINGS_ACCESS	14
#define HEDIT_RATINGS_CONTROL	15
#define HEDIT_RATINGS_INDEX	16
#define HEDIT_RATINGS_FILES	17
#define HEDIT_RATINGS_SLAVE	18
#define HEDIT_EXIT_ADD		19
#define HEDIT_EXIT_ADD2		20
#define HEDIT_EXIT_DEL		21
#define HEDIT_TRIGGER_DEL	22
#define HEDIT_TRIGGER_ADD	23
#define HEDIT_TRIGGER_ADD2	24
#define HEDIT_TRIGGER_ADD3	25
#define HEDIT_SSTOP		26
#define HEDIT_SSTART		27
#define HEDIT_EXTRA_MENU	28
#define HEDIT_EXTRA_ACCESS	29
#define HEDIT_EXTRA_CONTROL	30
#define HEDIT_EXTRA_INDEX	31
#define HEDIT_EXTRA_FILES	32
#define HEDIT_EXTRA_SLAVE	33
#define HEDIT_EXTRA_ACCESS2	34
#define HEDIT_EXTRA_FILES2	35
#define HEDIT_EXTRA_SLAVE2	36
#define HEDIT_EXIT_ADD3     37
#define HEDIT_EXIT_ADD4     38


#define ICEDIT_MAIN_MENU		0
#define ICEDIT_CONFIRM_EDIT		1
#define ICEDIT_CONFIRM_SAVESTRING 	2
#define ICEDIT_NAME			3
#define ICEDIT_ROOM			4
#define ICEDIT_DESC			5
#define ICEDIT_TYPE			6
#define ICEDIT_RATING			7
#define ICEDIT_SUBTYPE			8
#define ICEDIT_TRAP			9
#define ICEDIT_OPTION_MENU		10
#define ICEDIT_EXPERT			11

#define IEDIT_CONFIRM_EDIT           0
#define IEDIT_MAIN_MENU              1
#define IEDIT_EDIT_NAMELIST          2
#define IEDIT_SHORTDESC              3
#define IEDIT_DESC                   4
#define IEDIT_LONGDESC               5
#define IEDIT_TYPE                   6
#define IEDIT_EXTRAS                 7
#define IEDIT_WEAR                   8
#define IEDIT_WEIGHT                 9
#define IEDIT_COST                  10
#define IEDIT_TIMER                 12
#define IEDIT_VALUE_1               13
#define IEDIT_VALUE_2               14
#define IEDIT_VALUE_3               15
#define IEDIT_VALUE_4               16
#define IEDIT_VALUE_5               17
#define IEDIT_VALUE_6               18
#define IEDIT_VALUE_7               19
#define IEDIT_APPLY                 20
#define IEDIT_APPLYMOD              21
#define IEDIT_EXTRADESC_KEY         22
#define IEDIT_CONFIRM_SAVEDB        23
#define IEDIT_CONFIRM_SAVESTRING    24
#define IEDIT_PROMPT_APPLY          25
#define IEDIT_EXTRADESC_DESCRIPTION 26
#define IEDIT_EXTRADESC_MENU        27
#define IEDIT_MATERIAL                  28
#define IEDIT_RATING                    29
#define IEDIT_AFF_BITS                  30
#define IEDIT_VALUE_8                   31
#define IEDIT_VALUE_9                   32
#define IEDIT_VALUE_10                  33
#define IEDIT_AVAILTN			34
#define IEDIT_AVAILDAY			35
#define IEDIT_LEGAL1			36
#define IEDIT_LEGAL2                    37
#define IEDIT_LEGAL3                    38
#define IEDIT_VALUE_11                  39
#define IEDIT_VALUE_12                  40
#define IEDIT_SOURCEINFO                41
#define IEDIT_STREETINDEX               42

/* Submodes of REDIT connectedness */
#define REDIT_CONFIRM_EDIT              0
#define REDIT_MAIN_MENU                 1
#define REDIT_NAME                      2
#define REDIT_DESC                      3
#define REDIT_FLAGS                     4
#define REDIT_SECTOR                    5
#define REDIT_EXIT_MENU                 6
#define REDIT_CONFIRM_SAVEDB            7
#define REDIT_CONFIRM_SAVESTRING        8
#define REDIT_EXIT_NUMBER               9
#define REDIT_EXIT_DESCRIPTION          10
#define REDIT_EXIT_KEYWORD              11
#define REDIT_EXIT_KEY                  12
#define REDIT_EXIT_KEY_LEV              13
#define REDIT_EXIT_DOORFLAGS            14
#define REDIT_EXTRADESC_MENU            15
#define REDIT_EXTRADESC_KEY             16
#define REDIT_EXTRADESC_DESCRIPTION     17
#define REDIT_EXIT_HIDDEN               19
#define REDIT_EXIT_BARRIER              20
#define REDIT_EXIT_MATERIAL             21
#define REDIT_MATRIX	                22
#define REDIT_LIBRARY_RATING		23
#define REDIT_HOST			29
#define REDIT_IO			30
#define REDIT_BASE			31
#define REDIT_TRACE			32
#define REDIT_ACCESS			33
#define REDIT_PARENT			34
#define REDIT_COMMLINK			35
#define REDIT_ADDRESS			36
#define REDIT_NDESC			37
#define REDIT_LIGHT			38
#define REDIT_SMOKE			39
#define REDIT_COMBAT			40
#define REDIT_COVER			41
#define REDIT_CROWD			42
#define REDIT_TYPE			43
#define REDIT_X				44
#define REDIT_Y				45
#define REDIT_Z				46
#define REDIT_BACKGROUND		47
#define REDIT_BACKGROUND2		48
#define REDIT_EXIT_ENTRY_STRING_SECONDPERSON 49
#define REDIT_EXIT_ENTRY_STRING_THIRDPERSON 50
#define REDIT_EXIT_EXIT_STRING_THIRDPERSON  51
#define REDIT_STAFF_LOCK_LEVEL 52
#define REDIT_FLIGHT_CODE      53
#define REDIT_LATITUDE         54
#define REDIT_LONGITUDE        55

#define MEDIT_CONFIRM_EDIT                    0
#define MEDIT_CONFIRM_SAVESTRING              1
#define MEDIT_MAIN_MENU                       2
#define MEDIT_EDIT_NAMELIST                   3
#define MEDIT_SHORT_DESCR                     4
#define MEDIT_REG_DESCR                       5
#define MEDIT_LONG_DESCR                      6
#define MEDIT_MOB_FLAGS                       7
#define MEDIT_AFF_FLAGS                       8
#define MEDIT_NUYEN                           10
#define MEDIT_EXPERIENCE                      11
#define MEDIT_ATTRIBUTES                      12
#define MEDIT_BOD                             13
#define MEDIT_QUI                             14
#define MEDIT_STR                             15
#define MEDIT_CHA                             16
#define MEDIT_INT                             17
#define MEDIT_WIL                             18
#define MEDIT_MAG                             19
#define MEDIT_BALLISTIC                       20
#define MEDIT_IMPACT                          21
#define MEDIT_PHYSICAL                        22
#define MEDIT_MENTAL                          23
#define MEDIT_POSITION                        24
#define MEDIT_DEFAULT_POSITION                25
#define MEDIT_GENDER                          26
#define MEDIT_WEIGHT                          27
#define MEDIT_HEIGHT                          28
#define MEDIT_LEVEL                           29
#define MEDIT_SKILLS                          30
#define MEDIT_SKILL1                          31
#define MEDIT_SKILL2                          32
#define MEDIT_SKILL3                          33
#define MEDIT_SKILL4                          34
#define MEDIT_SKILL5                          35
#define MEDIT_ATTACK_TYPE                     36
#define MEDIT_SKILL1_VAL                      37
#define MEDIT_SKILL2_VAL                      38
#define MEDIT_SKILL3_VAL                      39
#define MEDIT_SKILL4_VAL                      40
#define MEDIT_SKILL5_VAL                      41
#define MEDIT_ARRIVE_MSG                      42
#define MEDIT_LEAVE_MSG                       43
#define MEDIT_CLASS                           44
#define MEDIT_CREDSTICK                       45
#define MEDIT_AMMO                            46
#define MEDIT_AMMO_SELECT_WEAPON              47
#define MEDIT_AMMO_SELECT_AMMO                48
#define MEDIT_AMMO_SELECT_QUANTITY            49
#define MEDIT_CYBERWARE                       50
#define MEDIT_ADD_CYBERWARE                   51
#define MEDIT_DEL_CYBERWARE                   52
#define MEDIT_BIOWARE                         53
#define MEDIT_ADD_BIOWARE                     54
#define MEDIT_DEL_BIOWARE                     55
#define MEDIT_EQUIPMENT                       56
#define MEDIT_SELECT_EQUIPMENT_VNUM           57
#define MEDIT_SELECT_EQUIPMENT_WEARLOC        58
#define MEDIT_DEL_EQUIPMENT                   59
#define MEDIT_HIGHLIGHT                       60
#define MEDIT_PRECAST_SPELLS                  61
#define MEDIT_ADD_PRECAST_SPELL               62
#define MEDIT_DELETE_PRECAST_SPELL            63
#define MEDIT_ADD_PRECAST_SPELL_WITH_SUBTYPE  64
#define MEDIT_EDIT_EXISTING_SPELL             65
#define MEDIT_FACTION_AFFILIATION             66

// quest defines
#define QEDIT_CONFIRM_EDIT                            0
#define QEDIT_CONFIRM_SAVESTRING                      1
#define QEDIT_MAIN_MENU                               2
#define QEDIT_JOHNSON                                 3
#define QEDIT_TIME                                    4
#define QEDIT_MIN_REP                                 5
#define QEDIT_MAX_REP                                 6
#define QEDIT_NUYEN                                   7
#define QEDIT_KARMA                                   8
#define QEDIT_M_MENU                                  9
#define QEDIT_M_AWAIT_NUMBER                         10
#define QEDIT_M_VNUM                                 11
#define QEDIT_M_NUYEN                                12
#define QEDIT_M_KARMA                                13
#define QEDIT_M_LOAD                                 14
#define QEDIT_M_OBJECTIVE                            15
#define QEDIT_M_LDATA                                16
#define QEDIT_M_LDATA2                               17
#define QEDIT_M_ODATA                                18
#define QEDIT_O_MENU                                 19
#define QEDIT_O_AWAIT_NUMBER                         20
#define QEDIT_O_VNUM                                 21
#define QEDIT_O_NUYEN                                22
#define QEDIT_O_KARMA                                23
#define QEDIT_O_LOAD                                 24
#define QEDIT_O_OBJECTIVE                            25
#define QEDIT_O_LDATA                                26
#define QEDIT_O_LDATA2                               27
#define QEDIT_O_ODATA                                28
#define QEDIT_INTRO                                  29
#define QEDIT_DECLINE                                30
#define QEDIT_QUIT                                   31
#define QEDIT_FINISH                                 32
#define QEDIT_INFO                                   33
#define QEDIT_REWARD                                 34
#define QEDIT_SHOUR                                  35
#define QEDIT_EHOUR                                  36
#define QEDIT_SSTRING                                37
#define QEDIT_ESTRING                                38
#define QEDIT_DONE                                   39
#define QEDIT_LOCATION                               40
#define QEDIT_EMOTE_MENU                             41
#define QEDIT_EMOTE__INSERT_EMOTE_BEFORE             42
#define QEDIT_EMOTE__AWAIT_NUMBER_FOR_DELETION       43
#define QEDIT_EMOTE__AWAIT_NUMBER_FOR_EDIT           44
#define QEDIT_EMOTE__AWAIT_NUMBER_FOR_INSERT_BEFORE  45
#define QEDIT_INTRO_EMOTE                            46
#define QEDIT_QUIT_EMOTE                             47
#define QEDIT_DECLINE_EMOTE                          48
#define QEDIT_FINISH_EMOTE                           49
#define QEDIT_EMOTE_MENU__INFO_EMOTES                50
#define QEDIT_PREREQUISITE                           51
#define QEDIT_DISQUALIFYING                          52

// zone defines
#define ZEDIT_CONFIRM_EDIT_DATA         0
#define ZEDIT_CONFIRM_CREATE_DATA       1
#define ZEDIT_CONFIRM_ADD_CMD           2
#define ZEDIT_CONFIRM_EDIT_CMD          3
#define ZEDIT_DATA_MENU                 4
#define ZEDIT_ZONE_NAME                 5
#define ZEDIT_TOP_OF_ZONE               6
#define ZEDIT_LIFESPAN                  7
#define ZEDIT_RESET_MODE                8
#define ZEDIT_CONFIRM_SAVEDATA          9
#define ZEDIT_COMMAND_MENU              10
#define ZEDIT_CONFIRM_SAVECMDS          11
#define ZEDIT_IF_FLAG_CMD               12
#define ZEDIT_CMD_TYPE                  13
#define ZEDIT_ARG1                      14
#define ZEDIT_ARG2                      15
#define ZEDIT_ARG3                      16
#define ZEDIT_DIRECTION_OF_DOOR         17
#define ZEDIT_REMOVE_ROOM               18
#define ZEDIT_LOAD_ROOM                 19
#define ZEDIT_WEAR                      20
#define ZEDIT_DOOR_STATE                21
#define ZEDIT_CONFIRM_INSERT_CMD        22
#define ZEDIT_SECURITY                  23
#define ZEDIT_ID_LIST                   24
#define ZEDIT_JURISDICTIONS             26
#define ZEDIT_PGHQ                      27
#define ZEDIT_ARG4                      28
#define ZEDIT_AURA_TYPE                 29
#define ZEDIT_AURA_FORCE                30
#define ZEDIT_RESTRICTED_EDIT           31
#define ZEDIT_APPROVED                  32

#define CEDIT_CONFIRM_EDIT        0
#define CEDIT_MAIN_MENU           1
#define CEDIT_CONFIRM_SAVESTRING  2
#define CEDIT_ALIAS               3
#define CEDIT_SHORT_DESC          4
#define CEDIT_DESC                5
#define CEDIT_LONG_DESC           6
#define CEDIT_VOICE               7
#define CEDIT_HEIGHT              8
#define CEDIT_WEIGHT              9
#define CEDIT_ARRIVE              10
#define CEDIT_LEAVE               11
#define CEDIT_LIFESTYLE           12

#define SHEDIT_CONFIRM_EDIT	0
#define SHEDIT_MAIN_MENU	1
#define SHEDIT_BUYTYPES_MENU	2
#define SHEDIT_TEXT_MENU	3
#define SHEDIT_SELLING_MENU	4
#define SHEDIT_CONFIRM_SAVESTRING	5
#define SHEDIT_RACE_MENU	6
#define SHEDIT_FLAG_MENU	7
#define SHEDIT_KEEPER		8
#define SHEDIT_TYPE		9
#define SHEDIT_PROFIT_BUY	10
#define SHEDIT_PROFIT_SELL	11
#define SHEDIT_RANDOM		12
#define SHEDIT_OPEN		13
#define SHEDIT_OPEN2		14
#define SHEDIT_NSIK		15
#define SHEDIT_NSIP		16
#define SHEDIT_NEN		17
#define SHEDIT_NOBUY		18
#define SHEDIT_BUYMSG		19
#define SHEDIT_SELLMSG		20
#define SHEDIT_SELL_ADD		21
#define SHEDIT_SELL_ADD1	22
#define SHEDIT_SELL_ADD2	23
#define SHEDIT_SELL_DELETE	24
#define SHEDIT_ETTI		25
#define SHEDIT_SHOPNAME		26

#define HOUSEEDIT_COMPLEX_MAIN_MENU         0
#define HOUSEEDIT_COMPLEX_NAME              1
#define HOUSEEDIT_COMPLEX_LANDLORD          2
#define HOUSEEDIT_COMPLEX_EDITORS           3

#define HOUSEEDIT_APARTMENT_MAIN_MENU       0
#define HOUSEEDIT_APARTMENT_SHORTNAME       1
#define HOUSEEDIT_APARTMENT_NAME            2
#define HOUSEEDIT_APARTMENT_ATRIUM          3
#define HOUSEEDIT_APARTMENT_LIFESTYLE       4
#define HOUSEEDIT_APARTMENT_RENT            5
#define HOUSEEDIT_APARTMENT_KEY             6
#define HOUSEEDIT_APARTMENT_COMPLEX         7
#define HOUSEEDIT_APARTMENT_ROOMS           8
#define HOUSEEDIT_APARTMENT_GARAGE_OVERRIDE 9

#define FACTION_EDIT_MAIN_MENU              0
#define FACTION_EDIT_NAME                   1
#define FACTION_EDIT_DESC                   2
#define FACTION_EDIT_DEFAULT_STATUS         3
#define FACTION_EDIT_EDITORS                4

#define CLONE_EMOTE_VECTOR(from, into) {         \
  if ((from) && !((from)->empty())) {            \
    (into) = new emote_vector_t;                 \
    for (size_t i = 0; i < (from)->size(); i++)  \
      (into)->push_back(str_dup((from)->at(i))); \
  } else {                                       \
    (into) = NULL;                               \
  }                                              \
}

#endif
