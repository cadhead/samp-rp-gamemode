#if defined _veh_cmd_included
	#endinput
#endif

#define _veh_cmd_included

CMD:veh(playerid, const params[]) {
  new 
    action[14],
    args[MAX_CHAT_INPUT],
    info[MAX_CHAT_LENGTH],
    vehicleid = GetPlayerVehicleID(playerid)
  ;

  if (sscanf(params, "s[13]S()["#MAX_CHAT_INPUT"]", action, args)) {
    SendClientMessage(playerid, COLOR_WHITE, "> »спользование: /veh [действие] <параметры>");

    return 1;
  }

  if (isnull(params)) return 0;

  if (GetCommandAction("engine")) {
    if (!IsPlayerVehicleDriver(playerid, vehicleid)) return 1;

    new chatbubble_message[MAX_PLAYER_NAME + 30];

    if (Vehicle_ToggleEngine(vehicleid)) {
      format(info, sizeof info, "* ¬ы завели двигатель %v.", GetVehicleModel(vehicleid));
      format(chatbubble_message, sizeof chatbubble_message, "* %s заводит двигатель.", gCharacterFormatedName[playerid]);
    } else {
      format(info, sizeof info, "* ¬ы заглушили двигатель %v.", GetVehicleModel(vehicleid));
      format(chatbubble_message, sizeof chatbubble_message, "* %s глушит двигатель.", gCharacterFormatedName[playerid]);
    }

    SendClientMessage(playerid, COLOR_ACTIONS, info, false);
    SetPlayerChatBubble(playerid, chatbubble_message, COLOR_ACTIONS, CHATBUBBLE_DRAW_DISTANCE, CHATBUBBLE_EXPIRED_TIME);
  }

  if (GetCommandAction("lights")) {
    if (!IsPlayerVehicleDriver(playerid, vehicleid)) return 1;

    Vehicle_ToggleLights(vehicleid);
  }

  return 1;
}
alias:veh("vehicle", "car")
