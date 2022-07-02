#if defined _pr_ints_b_included
	#endinput
#endif

#define _pr_ints_b_included

new gBusinessInteriors[][][] = {
  { -1, "Custom", "" },
  { 6, "24/7", "-27.41|-56.66|1003.54|6"}
};

new gBusinessInteriorsNames[64];

#include <YSI_Coding\y_hooks>
hook OnGameModeInit() {
  new count = sizeof gBusinessInteriors;

  for (new idx; idx < count; idx++) {
    strcat(gBusinessInteriorsNames, gBusinessInteriors[idx][1]);
    if (idx != count - 1) strcat(gBusinessInteriorsNames, "\n");
  }
}
