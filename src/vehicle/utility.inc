new
  gLastCreatedVehicle
;

hook function CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren=0) {
  gLastCreatedVehicle = continue(vehicletype, x, y, z, rotation, color1, color2, respawn_delay, addsiren);
  
  return gLastCreatedVehicle;
}
