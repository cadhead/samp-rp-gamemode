#if defined _admin_included
	#endinput
#endif

#define _admin_included

#include "./admin/vehicle.inc"

CMD:askin(playerid, params[]) {
	new skinid, target;

	sscanf(params, "dd", skinid, target);

	if (target == INVALID_PLAYER_ID) {
		target = playerid;
	}

	if (skinid > 311 || skinid < 1) {
		SendClientMessage(playerid, COLOR_ERROR, "> Неверный id скина!");

		return 1;
	}

	if (target == INVALID_PLAYER_ID || !IsPlayerConnected(target)) {
		SendClientMessage(playerid, COLOR_ERROR, "> Игрок оффлайн!");

		return 1;
	}

	SetPlayerSkin(playerid, skinid);

	return 1;
}
