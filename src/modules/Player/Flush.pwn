#include <YSI_Coding\y_hooks>

static NULL_Account[e_Account];
static NULL_Character[e_Character];

hook OnPlayerDisconnect(playerid, reason) {
  FlushAccountState(playerid);
  FlushCharacterState(playerid);
}

static FlushAccountState(playerid) {
  gAccount[playerid] = NULL_Account;
}

static FlushCharacterState(playerid) {
  gCharacter[playerid] = NULL_Character;
}
