#if defined _pl_kick_included
	#endinput
#endif

#define _pl_kick_included

stock KickPlayer(playerid, const reason[] = ""){
  if (!IsPlayerConnected(playerid)) {
		return 0;
	}

  static const fstr[] = "Вы были выкикнуты с сервера. Причина: %s";

  new
    is_with_reason,
    message[128]
  ;

  is_with_reason = strlen(reason) != 0;

  if (is_with_reason) {
    format(message, sizeof message, fstr, playerid, reason);
    SendClientMessage(playerid, COLOR_ERROR, message, false);
  }

  SetTimerEx("PlayerKickFix", 100, 0, "d", playerid);

  return 1;
}

forward PlayerKickFix(playerid);
public PlayerKickFix(playerid) {
	Kick(playerid);
}
