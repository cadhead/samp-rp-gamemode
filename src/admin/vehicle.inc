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
      vehicletype,
      color1,
      color2,
      Float:pos[3]
    ;
    
    GetPlayerPos(playerid, XYZ0(pos));
    if (sscanf(args, "ddd", vehicletype, color1, color2)) {
      CreateVehicle(400, XYZ0(pos), 0, 0, 0, 999999);

      return 1;
    }

    CreateVehicle(vehicletype, XYZ0(pos), 0, color1, color2, 999999);
  }

  return 1;
}
