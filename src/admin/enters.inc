#if defined _adm_enters_included
	#endinput
#endif

#define _adm_enters_included

new static enter_name[MAX_PLAYERS][64];
new static enter_pos[MAX_PLAYERS][64];

#include <YSI_Coding\y_hooks>

CMD:addenter(playerid, params[]) {
  new Float:pos[3];

  if (sscanf(params, "s[32]", params)) {
    if (!GetPVarInt(playerid, "cmd_addenter_stage")) {
      SendClientMessage(playerid, COLOR_WHITE, "> �������������: /addenter [��������]");

      return 1;
    }

    SetPVarInt(playerid, "cmd_addenter_stage", 0);
    GetPlayerPos(playerid, XYZ0(pos));
    format(gStringSmall, sizeof gStringSmall, "%.3f|%.3f|%.3f|%d|%d",
      XYZ0(pos), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid)
    );

    EntersAddOne(enter_pos[playerid], gStringSmall, enter_name[playerid]);
    SendClientMessage(playerid, COLOR_SUCCESS, "> ����/����� � %s ������� ������.", false, enter_name[playerid]);

    return 1;
  }

  SetPVarInt(playerid, "cmd_addenter_stage", 1);
  GetPlayerPos(playerid, XYZ0(pos));
  format(enter_pos[playerid], 64, "%.3f|%.3f|%.3f|%d|%d",
    XYZ0(pos), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid)
  );
  strcopy(enter_name[playerid], params);

  SendClientMessage(playerid, COLOR_SUCCESS, "> ���� � %s ����������, �� �� ����� �������� ��� ������.", false,  enter_name[playerid]);
  SendClientMessage(playerid, COLOR_SUCCESS, "> ����� �������� ����� �������� �� �������� ����� � ������� ������� ��������.", false);
  SendClientMessage(playerid, COLOR_SUCCESS, "> ��������� �������� ������ �� ��������� - ��� �������� ������� ������.", false);

  return 1;
}