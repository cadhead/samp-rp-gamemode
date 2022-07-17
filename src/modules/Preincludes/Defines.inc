// Accounts
#define MAX_ACCOUNTS                                    MAX_PLAYERS
#define MAX_PASSWDHASH                                  (64)
#define MAX_PASSWDSALT                                  (32)

#define MAX_WARNS                                       (3)

// Characters
#define CHARACTER_DEFAULT_POS_X                         (1715.7280)
#define CHARACTER_DEFAULT_POS_Y                         (-1936.9874)
#define CHARACTER_DEFAULT_POS_Z                         (13.5833)
#define CHARACTER_DEFAULT_POS_A                         (180.0000)
#define CHARACTER_DEFAULT_POS_WORLD                     (0)
#define CHARACTER_DEFAULT_POS_INT                       (0)
#define CHARACTER_DEFAULT_SKIN                          (2)

// Factions
#define MAX_FACTIONS                                    (32)
#define MAX_FACTION_NAME                                (32)
#define MAX_FACTION_RANKS                               (12)

// Enters, Props
#define MAX_ENTERS                                      (512)
#define MAX_PROPERTIES                                  MAX_ENTERS

#define PROPERTY_TYPE_HOUSE                             (0)
#define PROPERTY_TYPE_APTROOM                           (1)
#define PROPERTY_TYPE_BUSINESS                          (2)
#define PROPERTY_TYPE_24SHOP                            (3)
#define PROPERTY_TYPE_GAS                               (4)
#define PROPERTY_TYPE_AMMUNATION                        (5)
#define PROPERTY_TYPE_BAR                               (6)

// Death / Damage system
#define STAGE_HEALTH_AMOUNT                             (10.0)

#define BODY_PART_CHEST	                                (3)
#define BODY_PART_GROIN                                 (4)
#define BODY_PART_LEFT_ARM                              (5)
#define BODY_PART_RIGHT_ARM                             (6)
#define BODY_PART_LEFT_LEG                              (7)
#define BODY_PART_RIGHT_LEG                             (8)
#define BODY_PART_HEAD                                  (9)

// Chat
#define MAX_CHAT_INPUT                                  (128)
#define MAX_CHAT_LENGTH                                 (144)
#define MAX_COMMAND_NAME                                (15)
#define MAX_CHAT_IC_TALK_ACTION                         (15)
#define MAX_CHAT_PM_INPUT                               (60)
#define MAX_CHAT_SMS_INPUT                              (60)

#define CHAT_LOCAL_MAX_RANGE                            (20.0)
#define CHAT_LOW_MAX_RANGE                              (4.0)
#define CHAT_SHOUT_MAX_RANGE                            (30.0)
#define CHAT_ACTION_MAX_RANGE                           (30.0)
#define CHAT_OOC_MAX_RANGE                              (30.0)
#define CHAT_MEGAPHONE_MAX_RANGE                        (30.0)

#define CHATBUBBLE_EXPIRED_TIME                         (5000)
#define CHATBUBBLE_DRAW_DISTANCE                        CHAT_ACTION_MAX_RANGE

// Helpers
/**
 * XYZ0(ar) -> ar[0], ar[1], ar[2]
 *
 * Example:
 *   new Float:pos[3];
 *   GetPlayerPos(playerid, XYZ0(pos));
**/
#define XYZ0(%1)  %1[0],%1[1],%1[2]

#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define HOLDING(%0) \
	((newkeys & (%0)) == (%0))
#define RELEASED(%0) \
	(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

#define POS_X									(0)
#define POS_Y									(1)
#define POS_Z 								(2)
#define POS_ANGLE 						(3)

/*
 * Compile-time duration.
 *
 * Example:
 *   DURATION(1 hour, 20 minutes) -> 4800
 */
#define DURATION_MS(%1)     (DURATION(%1) * 1000)
#define DURATION(%1)        (DURATION_PT:%1,0)
#define DURATION_PT:%1,     (%1:DURATION)+_:DURATION_PT:
#define second%1:DURATION
#define seconds%1:DURATION
#define minute%1:DURATION   * DURATION_MINUTE
#define minutes%1:DURATION  * DURATION_MINUTE
#define hour%1:DURATION     * DURATION_HOUR
#define hours%1:DURATION    * DURATION_HOUR
#define day%1:DURATION      * DURATION_DAY
#define days%1:DURATION     * DURATION_DAY
#define week%1:DURATION     * DURATION_WEEK
#define weeks%1:DURATION    * DURATION_WEEK
#define month%1:DURATION    * DURATION_MONTH
#define months%1:DURATION   * DURATION_MONTH
#define year%1:DURATION     * DURATION_YEAR

