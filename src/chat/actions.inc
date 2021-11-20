#if defined _chat_actions_included
	#endinput
#endif

#define _chat_actions_included

CMD:me(playerid, params[]) {
  if (isnull(params)) return SendCommandUsageMessage(playerid, "me");

  new
    chat_message[MAX_PLAYER_NAME + MAX_CHAT_INPUT + 1]
  ;

  format(chat_message, sizeof chat_message, "* %s %s", gCharacterFormatedName[playerid], params);

  ProxDetector(playerid, CHAT_ACTION_MAX_RANGE, COLOR_ACTIONS, chat_message, 0);

  return 1;
}

CMD:do(playerid, params[]) {
  if (isnull(params)) return SendCommandUsageMessage(playerid, "do");

  new
    chat_message[MAX_PLAYER_NAME + MAX_CHAT_INPUT + 1]
  ;

  format(chat_message, sizeof chat_message, "* %s ((%s))", params, gCharacterFormatedName[playerid]);

  ProxDetector(playerid, CHAT_ACTION_MAX_RANGE, COLOR_ACTIONS, chat_message, 0);

  return 1;
}

CMD:todo(playerid, params[]) {
  new
    chat_message[MAX_PLAYER_NAME + MAX_CHAT_INPUT + 1],
    text[MAX_CHAT_INPUT],
    action[MAX_CHAT_INPUT]
  ;

  if (sscanf(params, "p<*>s["#MAX_CHAT_INPUT"]s["#MAX_CHAT_INPUT"]", text, action)) return SendCommandUsageMessage(playerid, "todo");

  format(chat_message, sizeof chat_message, "{EAEAEA}\"%s\", - {C2A2DA}сказал %s, %s", text, gCharacterFormatedName[playerid], action);

  ProxDetector(playerid, CHAT_ACTION_MAX_RANGE, COLOR_WHITE, chat_message, 0);

  return 1;
}
