#if defined _constants_included
	#endinput
#endif

#define _constants_included

enum (<<= 1)
{
  CMD_ADMIN = 1,
  CMD_MODER
};

new Float:gPosition[3];
new Float:gHealth;
new gRandomValue;

#define X     0
#define Y     1
#define Z     2
#define ANGLE 3
