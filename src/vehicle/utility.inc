new
  gLastCreatedVehicle
;

stock Vehicle_CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren=0) {
  gLastCreatedVehicle = CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren=0);
  
  return gLastCreatedVehicle;
}

#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif

#define CreateVehicle Vehicle_CreateVehicle