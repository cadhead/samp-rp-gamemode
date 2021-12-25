#if defined _adm_enters_included
	#endinput
#endif

#define _adm_enters_included

new static enter_name[MAX_PLAYERS][64];
new static enter_pos[MAX_PLAYERS][64];

#include <YSI_Coding\y_hooks>

CMD:addenter(playerid, params[]) {
  if (sscanf(params, "s[32]", params)) {
    if (!GetPVarInt(playerid, "cmd_addenter_stage")) {
      SendClientMessage(playerid, COLOR_WHITE, "> Использование: /addenter [название]");

      return 0;
    }

    SetPVarInt(playerid, "cmd_addenter_stage", 0);
    SerializeCharacterPosition(playerid, gStringSmall);

    new enterid = EntersAddOne(enter_name[playerid], enter_pos[playerid], gStringSmall);
    SendClientMessage(playerid, COLOR_SUCCESS, "> Вход/выход в %s успешно создан.", false, enter_name[playerid]);

    return enterid;
  }

  SetPVarInt(playerid, "cmd_addenter_stage", 1);
  SerializeCharacterPosition(playerid, enter_pos[playerid]);
  strcopy(enter_name[playerid], params);

  SendClientMessage(playerid, COLOR_SUCCESS, "> Вход в %s установлен, но не будет сохранён без выхода.", false,  enter_name[playerid]);
  SendClientMessage(playerid, COLOR_SUCCESS, "> Чтобы добавить выход встаньте на желаемую точку и введите команду повторно.", false);
  SendClientMessage(playerid, COLOR_SUCCESS, "> Указывать название больше не требуется - это запустит процесс заново.", false);

  return 0;
}

CMD:delenter(playerid, params[]) {
  extract params -> new idx; else return 1;
  if (idx >= GetEntersCount()) return 1;

  EntersDeleteOne(idx);

  return 1;
}
