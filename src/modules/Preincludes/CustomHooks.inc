// Server
forward LoadServerData();
public LoadServerData() {
	return 1;
}

// Account and Character
forward ResetAccountVariables(playerid);
public ResetAccountVariables(playerid) {
  return 1;
}
forward ResetCharacterVariables(playerid);
public ResetCharacterVariables(playerid) {
  return 1;
}
forward SaveCharacterState(playerid);
public SaveCharacterState(playerid) {
  return 1;
}

// Enters
forward OnEnterStart(playerid, enteridx); // Calls when player send /enter command
public OnEnterStart(playerid, enteridx) { 
  return 1; 
}
forward OnExitStart(playerid, enteridx); // Calls when player send /exit command
public OnExitStart(playerid, enteridx) { 
  return 1; 
}
forward OnEnterDone(playerid, enteridx); // Calls if player entered sucessfully
public OnEnterDone(playerid, enteridx) { 
  return 1; 
}
forward OnExitDone(playerid, enteridx); // Calls if player exited sucessfully
public OnExitDone(playerid, enteridx) { 
  return 1; 
}
forward OnEnterPickupPickUp(playerid, STREAMER_TAG_PICKUP:pickupid, enteridx, propidx); // Called when the player picks up any enter pickup, if it exists
public OnEnterPickupPickUp(playerid, STREAMER_TAG_PICKUP:pickupid, enteridx, propidx) { // Meaning pickup created FOR "ENTER", not any pickup
  return 1;
}
