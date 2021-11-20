#if defined _adm_vehicle_included
	#endinput
#endif

#define _adm_vehicle_included

CMD:aveh(playerid, params[]) {
  new 
    action[14],
    args[MAX_CHAT_INPUT]
  ;

  if (sscanf(params, "s[13]S()["#MAX_CHAT_INPUT"]", action, args)) {
    SendClientMessage(playerid, COLOR_WHITE, "> Использование: /aveh [действие] <параметры>");

    return 1;
  }

  if (GetCommandAction("create")) {
    new
      vehicletype = 522,
      color1 = 0,
      color2 = 0,
      Float:pos[3]
    ;
    
    GetPlayerPos(playerid, XYZ0(pos));
    sscanf(args, "ddd", vehicletype, color1, color2);
    CreateVehicle(vehicletype, XYZ0(pos), 0, color1, color2, -1);
    PutPlayerInVehicle(playerid, gLastCreatedVehicle, 0);
  }

  if (GetCommandAction("remove")) {
    new vehicleid = GetPlayerVehicleID(playerid);

    if (IsPlayerVehicleDriver(playerid, vehicleid)) {
      DestroyVehicle(vehicleid);
      SendClientMessage(playerid, COLOR_SUCCESS, "> Транспорт успешно удалён.");
    } else {
      SendClientMessage(playerid, COLOR_ERROR, "> Чтобы удалить транспорт, нужно сначала сесть в него.");
    }
  }

  return 1;
}
