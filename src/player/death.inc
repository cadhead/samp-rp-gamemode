#if defined _pl_death_included
	#endinput
#endif

#define _pl_death_included

#include <YSI_Coding\y_hooks>

enum {
  CHARACTER_HEALTHY = 0,
  CHARACTER_INJURED,
  CHARACTER_DIED
}

new static
  Text3D:death_text[MAX_PLAYERS],
  respawn_time[MAX_PLAYERS],
  Float:death_pos[MAX_PLAYERS][3],
  damage_taken_times[MAX_PLAYERS],
  damage_taken_total[MAX_PLAYERS][100]
;

new static
  Float:spawn_hospital[][] = {
    { 2028.9686, -1420.2394, 16.9922, 139.7419 },
    { 1178.9486, -1322.5089, 14.1453, 273.7729 }
  };

static const max_respawn_time = 10;

#define GetCharacterDeathStage(%0) gCharacter[%0][e_cDeathStage]
#define STAGE_HEALTH_AMOUNT 10.0

CMD:test(playerid, params[]) {
  sscanf(params, "f", gHealth);
  SetPlayerHealth(playerid, gHealth);

  return 1;
}

hook OnPlayerDeath(playerid, bool:cancelable) {
  GetPlayerPos(playerid, XYZ0(gCharacter[playerid][e_cSpawnPos]));
  SetSpawnInfo( 
    playerid, 
    0,
    gCharacter[playerid][e_cSkin], 
    XYZ0(gCharacter[playerid][e_cSpawnPos]),
    90.0, 
    0, 0, 0, 0, 0, 0 
  );

  SetPlayerVirtualWorld(playerid, gCharacter[playerid][e_cSpawnWorld]);
  SetPlayerInterior(playerid, gCharacter[playerid][e_cSpawnInt]);

  SetCharacterDeathStage(playerid, GetCharacterDeathStage(playerid));

  return 1;
}

hook OnPlayerDamageDone(playerid, Float:amount, issuerid, weapon, bodypart) {
  if (playerid == INVALID_PLAYER_ID) return 1;

  new character_death_state = GetCharacterDeathStage(playerid);
  new character_state_dead = character_death_state == CHARACTER_DIED;

  if (character_death_state == CHARACTER_INJURED) {
    character_death_state = CHARACTER_DIED;
  }

  GetPlayerHealth(playerid, gHealth);
  if (gHealth <= STAGE_HEALTH_AMOUNT) {
    SetPlayerHealth(playerid, STAGE_HEALTH_AMOUNT);
    GetPlayerPos(playerid, XYZ0(death_pos[playerid]));

    if (!character_death_state) {
      character_death_state = CHARACTER_INJURED;
    }
  }

  if (!character_state_dead) {
    SetCharacterDeathStage(playerid, character_death_state);
    SetCharacterDamageTaken(playerid, issuerid, bodypart, weapon, amount);
  }

  return 1;
}

hook OnPlayerUpdate(playerid) {
  if (GetCharacterDeathStage(playerid)) {
    if (GetPlayerAnimationIndex(playerid) == 1151) return 1;
    if (GetPlayerAnimationIndex(playerid) == 1701) return 1;
    ApplyDeathAnimation(playerid, GetCharacterDeathStage(playerid));
  }

  return 1;
}

CMD:acceptdeath(playerid) {
  if (GetCharacterDeathStage(playerid) != CHARACTER_INJURED) return 1;

  SetCharacterDeathStage(playerid, CHARACTER_DIED);

  return 1;
}

CMD:respawnme(playerid) {
  if (GetCharacterDeathStage(playerid) != CHARACTER_DIED) return 1;
  if (respawn_time[playerid] && gettime() < respawn_time[playerid]) {
    SendClientMessage(playerid, COLOR_ERROR, 
      "> Перед респавном должно пройти %d секунд. Осталось: %d.",
      true, max_respawn_time, respawn_time[playerid] - gettime()
    );

    return 1;
  }

  respawn_time[playerid] = 0;
  gRandomValue = random(2);

  SetCharacterDeathStage(playerid, CHARACTER_HEALTHY);
  SendClientMessage(playerid, COLOR_ERROR, "> Вы приняли PK. Связанные с ним события больше не часть истории вашего персонажа.", false);
  SetPlayerPos(playerid, spawn_hospital[gRandomValue][X], spawn_hospital[gRandomValue][Y], spawn_hospital[gRandomValue][Z]);
  SetPlayerFacingAngle(playerid, spawn_hospital[gRandomValue][ANGLE]);
  SetPlayerInterior(playerid, 0);
  SetPlayerVirtualWorld(playerid, 0);
  SetPlayerHealth(playerid, 100.0);

  return 1;
}

stock SetCharacterDeathStage(playerid, stage) {
  switch(stage) {
    case CHARACTER_INJURED: {
      gCharacter[playerid][e_cDeathStage] = CHARACTER_INJURED;
      TogglePlayerControllable(playerid, false);
    }
    case CHARACTER_DIED: {
      gCharacter[playerid][e_cDeathStage] = CHARACTER_DIED;
      respawn_time[playerid] = gettime() + max_respawn_time;
    }
    case CHARACTER_HEALTHY: {
      gCharacter[playerid][e_cDeathStage] = CHARACTER_HEALTHY;
      TogglePlayerControllable(playerid, true);
    }
  }

  ApplyDeathAnimation(playerid, stage);
  SendDeathStageMessage(playerid, stage);
}

static stock ApplyDeathAnimation(playerid, stage) {
  switch(stage) {
    case CHARACTER_INJURED: {
      ApplyAnimation(playerid, "WUZI", "CS_Dead_Guy", 4.1, 0, 1, 1, 1, 1);
    }
    case CHARACTER_DIED: {
      ApplyAnimation(playerid, "PED", "FLOOR_hit_f", 4.1, 0, 1, 1, 1, 1);
    }
  }
}

static stock SendDeathStageMessage(playerid, stage) {
  switch(stage) {
    case CHARACTER_INJURED: {
      SendClientMessage(playerid, COLOR_ERROR, "> Ваш персонаж сильно ранен! Если его не спасут — он умрёт.", false);
      SendClientMessage(playerid, COLOR_ERROR, "> Чтобы принять смерть введите /acceptdeath.");
    }
    case CHARACTER_DIED: {
      SendClientMessage(playerid, COLOR_ERROR, "> Ваш персонаж мёртв! Вы сможете принять PK через %d секунд.", true, max_respawn_time);
      SendClientMessage(playerid, COLOR_ERROR, "> Чтобы зареспавниться, введите /respawnme.", false);
    }
  }

  CreateDeathMessage3dText(playerid, stage);
}

static stock CreateDeathMessage3dText(playerid, stage) {
  new message[144];

  switch(stage) {
    case CHARACTER_INJURED: {
      format(message, sizeof message,
        "(( Ранен %i раз, /damages %i для более детальной информации. ))",
        10, playerid
      );
    }
    case CHARACTER_DIED: {
      strcat(message, "(( ПЕРСОНАЖ МЁРТВ ))");
    }
    default: {
      DestroyDynamic3DTextLabel(death_text[playerid]);
      death_text[playerid] = Text3D:INVALID_3DTEXT_ID;
    }
  }

  if (!strlen(message)) return 0;

  if (IsValidDynamic3DTextLabel(death_text[playerid])) {
    UpdateDynamic3DTextLabelText(death_text[playerid], COLOR_RED, message);
  } else {
    death_text[playerid] = CreateDynamic3DTextLabel(
      message, COLOR_RED, XYZ0(death_pos[playerid]), 15.0, playerid
    );
  }

  return 1;
}

static stock SetCharacterDamageTaken(playerid, issuerid, bodypart, weaponid, Float:amount) {
  new
    id,
    Float:armour
  ;

  damage_taken_times[playerid]++;
  for(new i = 0; i < 100; i++) {
    if (damage_taken_total[playerid][i])  {
      id = i;
      break;
    }
  }

  damage_taken_total[playerid][id] = floatround(amount, floatround_round);

  return 1;
}
