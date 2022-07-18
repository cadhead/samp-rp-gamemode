#define __PL_HELPER                     (1)
#define __PL_MODER                      (2)
#define __PL_ADMIN                      (3)
#define __PL_OWNER                      (256)

#define __PL_PREMIUM_BRONZE             (1)
#define __PL_PREMIUM_SILVER             (2)
#define __PL_PREMIUM_GOLD               (3)

static group_names[][] = {
  "Player", "Helper", "Game Admin", "Server Admin", "Management"
};

PlayerIsHelper(playerid) {
  return (gAccount[playerid][e_acAdmin] == __PL_HELPER);
}

PlayerIsModer(playerid) {
  return (gAccount[playerid][e_acAdmin] == __PL_MODER);
}

PlayerIsAdmin(playerid) {
  return (gAccount[playerid][e_acAdmin] == __PL_ADMIN);
}

PlayerIsOwner(playerid) {
  return (gAccount[playerid][e_acAdmin] == __PL_OWNER);
}

PlayerIsPremium(playerid) {
  return (gAccount[playerid][e_acPremium] >= __PL_PREMIUM_BRONZE);
}

PlayerGetPremiumLevel(playerid) {
  return gAccount[playerid][e_acPremium];
}

PlayerGetGroupName(playerid, dest[]) {
  strcat(dest, group_names[gAccount[playerid][e_acAdmin]]);
}
