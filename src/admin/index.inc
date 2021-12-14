#if defined _admin_included
	#endinput
#endif

#define _admin_included

#include "./admin/vehicle.inc"
#include "./admin/weapon.inc"

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
