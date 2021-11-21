#if defined _helpers_included
	#endinput
#endif

#define _helpers_included

#include "./helpers/fscm"
#include "./helpers/roleplay"
#include "./helpers/proxdetector"

enum {
	DURATION_SECOND = 1,
	DURATION_MINUTE = 60 * DURATION_SECOND,
	DURATION_HOUR   = 60 * DURATION_MINUTE,
	DURATION_DAY    = 24 * DURATION_HOUR,
	DURATION_WEEK   = 7 * DURATION_DAY,
	DURATION_MONTH  = 30 * DURATION_DAY,
	DURATION_YEAR   = 365 * DURATION_DAY,
	
	DURATION_PERMANENT = 0,
	DURATION_EXPIRED   = -1
};

#define GetCommandAction(%0) !strcmp(action, %0, true)

/*
 * XYZ0(ar) -> ar[0], ar[1], ar[2]
 *
 * Example:
 *   new Float:pos[3];
 *   GetPlayerPos(playerid, XYZ0(pos));
 */
#define XYZ0(%1)  %1[0],%1[1],%1[2]

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
#define years%1:DURATION    * DURATION_YEAR
