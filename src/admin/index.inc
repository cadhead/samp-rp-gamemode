#if defined _admin_included
  #endinput
#endif

#define _admin_included

#include "./admin/vehicle.inc"
#include "./admin/weapon.inc"
#include "./admin/enters.inc"

CMD:askin(playerid, params[]) {
  new skinid, target;

  sscanf(params, "dd", skinid, target);

  if (!target) target = playerid;

  if (skinid > 311 || skinid < 1 || skinid == 74) {
    SendClientMessage(playerid, COLOR_ERROR, "> Неверный ID скина!");

    return 1;
  }

  SetPlayerSkin(playerid, skinid);

  return 1;
}

CMD:setpos(playerid, params[]) {
  static Float:x, Float:y, Float:z, i, w;

  if (sscanf(params, "fffD(-1)D(-1)", x, y, z, i, w)) {
    return SendClientMessage(playerid, -1, "> Использование: /setpos [x] [y] [z] <интерьер> <вирт. мир>");
  }

  new veh = GetPlayerVehicleID(playerid);

  if (i == -1) {
    i = GetPlayerInterior(playerid);
  } else {
    SetPlayerInterior(playerid, i);
  }

  if (w == -1) {
    w = GetPlayerVirtualWorld(playerid);
  } else {
    if (veh != 0) SetVehicleVirtualWorld(veh, w);
    SetPlayerVirtualWorld(playerid, w);
  }

  if (veh != 0) SetVehiclePos(veh, x, y, z);
  else SetPlayerPos(playerid, x, y, z);

  SendClientMessage(playerid, -1, "> Вы перемещены на координаты X: %.3f, Y: %.3f, Z: %.3f", false, x, y, z);
  if (i >= 0 || w >= 0) SendClientMessage(playerid, -1, "> В интерьер: %d, вирт. мир: %d", false, i, w);

  return 1;
}
