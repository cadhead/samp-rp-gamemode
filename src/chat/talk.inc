#if defined _chat_talk_included
	#endinput
#endif

#define _chat_talk_included

// IC

CMD:local(playerid, params[]) {
  if (isnull(params)) return SendCommandUsageMessage(playerid, "local");
  ICChat(playerid, params);

  return 1;
}

CMD:low(playerid, params[]) {
  if (isnull(params)) return SendCommandUsageMessage(playerid, "low");
  ICChat(playerid, params, CHAT_LOW_MAX_RANGE, "тихо говорит");

  return 1;
}
alias:low("l")

CMD:shout(playerid, params[]) {
  if (isnull(params)) return SendCommandUsageMessage(playerid, "shout");
  ICChat(playerid, params, CHAT_SHOUT_MAX_RANGE, "кричит");

  return 1;
}
alias:shout("s")

// OOC

CMD:b(playerid, params[]) {
  if (isnull(params)) return SendCommandUsageMessage(playerid, "b");
  OOCChat(playerid, params);

  return 1;
}

CMD:ooc(playerid, params[]) {
  if (isnull(params)) return SendCommandUsageMessage(playerid, "ooc");
  OOCChat(playerid, params, true);

  return 1;
}
alias:ooc("o")

CMD:pm(playerid, params[]) {
  new
    targetid,
    message[MAX_CHAT_INPUT]
  ;

  if (sscanf(params, "ds["#MAX_CHAT_INPUT"]", targetid, message)) {
    SendCommandUsageMessage(playerid, "pm");

    return 0;
  }

  strdel(message, MAX_CHAT_PM_INPUT, sizeof message);

  SendClientMessage(
    playerid,
    COLOR_PM,
    "> [PM]: %s. ДЛЯ: %s[%d]",
    false,
    message, gCharacterFormatedName[targetid], targetid
  );

  SendClientMessage(
    targetid,
    COLOR_PM,
    "> [PM]: %s. ОТ: %s[%d]",
    false,
    message, gCharacterFormatedName[playerid], playerid
  );

  return 1;
}

CMD:sms(playerid, params[]) {
  new
    targetid,
    message[MAX_CHAT_INPUT]
  ;

  if (sscanf(params, "ds["#MAX_CHAT_INPUT"]", targetid, message)) {
    SendCommandUsageMessage(playerid, "sms");

    return 0;
  }

  strdel(message, MAX_CHAT_SMS_INPUT, sizeof message);

  SendClientMessage(
    playerid,
    COLOR_PM,
    "> [SMS]: %s. ДЛЯ: %d",
    false,
    message, targetid
  );

  SendClientMessage(
    targetid,
    COLOR_PM,
    "> [SMS]: %s. ОТ: %d",
    false,
    message, playerid
  );

  return 1;
}
