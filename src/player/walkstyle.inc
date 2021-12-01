#if defined _pl_walkstyle_included
	#endinput
#endif

#define _pl_walkstyle_included

#include <YSI_Coding\y_hooks>

new character_walk_style[MAX_PLAYERS];
new static walk_timer[MAX_PLAYERS];

#define GetCharacterWalkStyle(%0) character_walk_style[playerid]
#define SetCharacterWalkStyle(%0,%1) character_walk_style[playerid] = %1

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if (
    (
      (newkeys & KEY_WALK && newkeys & KEY_UP)
      || (newkeys & KEY_WALK && newkeys & KEY_DOWN)
      || (newkeys & KEY_WALK && newkeys & KEY_LEFT) 
      || (newkeys & KEY_WALK && newkeys & KEY_RIGHT)
    )
    || (
      (oldkeys & KEY_WALK && newkeys & KEY_UP)
      || (oldkeys & KEY_WALK && newkeys & KEY_DOWN)
      || (oldkeys & KEY_WALK && newkeys & KEY_LEFT)
      || (oldkeys & KEY_WALK && newkeys & KEY_RIGHT)
    )
    || (
      (newkeys & KEY_WALK && oldkeys & KEY_UP)
      || (newkeys & KEY_WALK && oldkeys & KEY_DOWN)
      || (newkeys & KEY_WALK && oldkeys & KEY_LEFT)
      || (newkeys & KEY_WALK && oldkeys & KEY_RIGHT)
    )
    && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT
  ) {
    walk_timer[playerid] = SetTimerEx("PlayWalkAnimation", 200, 0, "d", playerid);
  }

	return 1;
}

forward PlayWalkAnimation(playerid);
public PlayWalkAnimation(playerid) {
  new 
    keys,
    updown,
    leftright
  ;

  GetPlayerKeys(playerid, keys, updown, leftright);
  KillTimer(walk_timer[playerid]);
  if (!GetCharacterWalkStyle(playerid)) return 1;
  if (
    (keys & KEY_WALK && updown & KEY_UP)
    || (keys & KEY_WALK && updown & KEY_DOWN)
    || (keys & KEY_WALK && leftright & KEY_LEFT)
    || (keys & KEY_WALK && leftright & KEY_RIGHT)
  ) {
    ProcessWalkAnimation(playerid, GetCharacterWalkStyle(playerid));
    walk_timer[playerid] = SetTimerEx("PlayWalkAnimation", 200, 0, "d", playerid);
  } else {
    ProcessWalkAnimation(playerid, GetCharacterWalkStyle(playerid));
  }

  return 1;
}

static stock ProcessWalkAnimation(playerid, id) {
  switch (id) {
    case 1: PlayAnimation(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1);
    case 2: PlayAnimation(playerid, "PED", "WALK_armed", 4.1, 1, 1, 1, 1, 1);
    case 3: PlayAnimation(playerid, "PED", "WALK_fat", 4.1, 1, 1, 1, 1, 1);
    case 4: PlayAnimation(playerid, "PED", "WALK_fatold", 4.1, 1, 1, 1, 1, 1);
    case 5: PlayAnimation(playerid, "FAT", "FatWalk", 4.1, 1, 1, 1, 1, 1);
    case 6: PlayAnimation(playerid, "MUSCULAR", "MuscleWalk", 4.1, 1, 1, 1, 1, 1);
    case 7: PlayAnimation(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1);
    case 8: PlayAnimation(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1);
    case 9: PlayAnimation(playerid, "PED", "WALK_player", 4.1, 1, 1, 1, 1, 1);
    case 10: PlayAnimation(playerid, "PED", "WALK_old", 4.1, 1, 1, 1, 1, 1);
    case 11: PlayAnimation(playerid, "PED", "WALK_wuzi", 4.1, 1, 1, 1, 1, 1);
    case 12: PlayAnimation(playerid, "PED", "WOMAN_walkbusy", 4.1, 1, 1, 1, 1, 1);
    case 13: PlayAnimation(playerid, "PED", "WOMAN_walkfatold", 4.1, 1, 1, 1, 1, 1);
    case 14: PlayAnimation(playerid, "PED", "WOMAN_walknorm", 4.1, 1, 1, 1, 1, 1);
    case 15: PlayAnimation(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1);
    case 16: PlayAnimation(playerid, "PED", "WOMAN_walkshop", 4.1, 1, 1, 1, 1, 1);
  }

  return 1;
}

CMD:walkstyle(playerid, params[]) {
  if(sscanf(params, "d", params[0])) {
    SendClientMessage(playerid, COLOR_WHITE, "> Использование /walkstyle [1-16]");
    SendClientMessage(playerid, COLOR_WHITE, "Random: 7, 8.");
    SendClientMessage(playerid, COLOR_WHITE, "Normal: 1, 2, 6, 9, 11.");
    SendClientMessage(playerid, COLOR_WHITE, "Old/Fat: 3, 4, 5, 10.");
    SendClientMessage(playerid, COLOR_WHITE, "Woman: 12, 13, 14, 15, 16.");

    return 1;
  }

  if (params[0] == 0) {
    SetCharacterWalkStyle(playerid, params[0]);
    SendClientMessage(playerid, COLOR_SUCCESS, "> Установлен стандартный стиль походки.");

    return 1;
  }
  if(!(1 <= params[0] <= 16)) return 1;

  SetCharacterWalkStyle(playerid, params[0]);
  SendClientMessage(playerid, COLOR_SUCCESS, "> Вы сменили стиль походки.");

  return 1;
}
