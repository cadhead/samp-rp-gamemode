#if defined _hlp_popup_included
	#endinput
#endif

#define _hlp_popup_included

const MAX_LINE_MESSAGE_LENGTH =  90;

static
  Text:box,
  PlayerText:messageTD[MAX_PLAYERS][4],
  bool:_PopUpActivated[MAX_PLAYERS] = { false, ... },
  timer[MAX_PLAYERS]
;

static CreateBox() {
  box = TextDrawCreate(600.000000, 300.540008, "box");
  TextDrawLetterSize(box, 0.000000, 6.705555);
  TextDrawTextSize(box, 430.799987, 0.000000);
  TextDrawAlignment(box, 1);
  TextDrawColor(box, 0);
  TextDrawUseBox(box, true);
  TextDrawBoxColor(box, 102);
  TextDrawSetShadow(box, 0);
  TextDrawSetOutline(box, 0);
  TextDrawFont(box, 0);
}

static CreateMessage(playerid) {
  static const Float:posY[] = {
    300.026580, 315.026580, 330.026580, 345.026580
  };

  for (new i; i < 4; i++) {
    messageTD[playerid][i] = CreatePlayerTextDraw(playerid, 442.399963, posY[i], "");
    PlayerTextDrawLetterSize(playerid, messageTD[playerid][i], 0.301249, 1.330832);
    PlayerTextDrawAlignment(playerid, messageTD[playerid][i], 1);
    PlayerTextDrawColor(playerid, messageTD[playerid][i], -1);
    PlayerTextDrawSetShadow(playerid, messageTD[playerid][i], 0);
    PlayerTextDrawSetOutline(playerid, messageTD[playerid][i], 1);
    PlayerTextDrawBackgroundColor(playerid, messageTD[playerid][i], 51);
    PlayerTextDrawFont(playerid, messageTD[playerid][i], 1);
    PlayerTextDrawSetProportional(playerid, messageTD[playerid][i], 1);
  }
}

static ShowPopupTextDraw(playerid, message[][]) {
  TextDrawShowForPlayer(playerid, box);

  for (new i; i < 4; i++) {
    PlayerTextDrawSetString(playerid, messageTD[playerid][i], message[i]);
    PlayerTextDrawShow(playerid, messageTD[playerid][i]);
  }
}

@__hlp_popup_HidePopup(playerid);
@__hlp_popup_HidePopup(playerid) {
  TextDrawHideForPlayer(playerid, box);
  for (new i; i < 4; i++) {
    PlayerTextDrawSetString(playerid, messageTD[playerid][i], "");
    PlayerTextDrawHide(playerid, messageTD[playerid][i]);
  }

  _PopUpActivated[playerid] = false;
}

ShowPopupMessage(playerid, message[][], interval = 5000) {
  if (_PopUpActivated[playerid]) @__hlp_popup_HidePopup(playerid);

  ShowPopupTextDraw(playerid, message);

  timer[playerid] = SetTimer("@__hlp_popup_HidePopup", interval, false);

  _PopUpActivated[playerid] = true;
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit() { CreateBox(); }
hook OnPlayerConnect(playerid) {
  CreateMessage(playerid);  
}
