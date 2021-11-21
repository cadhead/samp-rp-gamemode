#if defined _veh_included
	#endinput
#endif

#define _veh_included

#include "./vehicle/utility"
#include "./vehicle/commands"

new static
  engine,
  lights,
  alarm,
  doors,
  bonnet,
  boot,
  objective
;

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
  switch (newkeys) {
    case KEY_ACTION: {
      callcmd::veh(playerid, "engine");
    }
    case KEY_SUBMISSION: {
      callcmd::veh(playerid, "lights");
    }
  }
}

stock Vehicle_ToggleEngine(vehicleid, newstate = VEHICLE_PARAMS_UNSET) {
  GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

  if (newstate == VEHICLE_PARAMS_UNSET) {
    if (engine == VEHICLE_PARAMS_OFF || engine == VEHICLE_PARAMS_UNSET) {
      newstate = VEHICLE_PARAMS_ON;
    } else {
      newstate = VEHICLE_PARAMS_OFF;
    }
  }

  SetVehicleParamsEx(vehicleid, newstate, lights, alarm, doors, bonnet, boot, objective);

  return newstate;
}

stock Vehicle_ToggleLights(vehicleid, newstate = VEHICLE_PARAMS_UNSET) {
  GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

  if (newstate == VEHICLE_PARAMS_UNSET) {
    if (lights == VEHICLE_PARAMS_OFF || lights == VEHICLE_PARAMS_UNSET) {
      newstate = VEHICLE_PARAMS_ON;
    } else {
      newstate = VEHICLE_PARAMS_OFF;
    }
  }

  SetVehicleParamsEx(vehicleid, engine, newstate, alarm, doors, bonnet, boot, objective);

  return newstate;
}

stock IsPlayerVehicleDriver(playerid, vehicleid) {
  if (vehicleid == INVALID_VEHICLE_ID) return 0;
  if (GetPlayerVehicleSeat(playerid) != 0) return 0;

  return 1;
}

