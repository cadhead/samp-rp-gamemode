#if defined _chat_included
	#endinput
#endif

#define _chat_included

#define MAX_CHAT_INPUT          128
#define MAX_CHAT_LENGTH         144
#define MAX_COMMAND_NAME        15
#define MAX_CHAT_IC_TALK_ACTION 15
#define MAX_CHAT_PM_INPUT       60
#define MAX_CHAT_SMS_INPUT      60

#define CHAT_LOCAL_MAX_RANGE     20.0
#define CHAT_LOW_MAX_RANGE       4.0
#define CHAT_SHOUT_MAX_RANGE     30.0
#define CHAT_ACTION_MAX_RANGE    30.0
#define CHAT_OOC_MAX_RANGE       30.0
#define CHAT_MEGAPHONE_MAX_RANGE 30.0

#define CHATBUBBLE_EXPIRED_TIME  5000
#define CHATBUBBLE_DRAW_DISTANCE CHAT_ACTION_MAX_RANGE

#include <YSI_Coding\y_hooks>

#include "./chat/service"
#include "./chat/actions"
#include "./chat/talk"

hook OnPlayerText(playerid, text[]) {
  callcmd::local(playerid, text);
}

stock ICChat(playerid, const text[], Float:range = CHAT_LOCAL_MAX_RANGE, const action[MAX_CHAT_IC_TALK_ACTION] = "произнес") {
  new
    chat_message[MAX_PLAYER_NAME + MAX_CHAT_INPUT + sizeof action]
  ;

  format(chat_message, sizeof chat_message, "%s %s: %s", gCharacterFormatedName[playerid], action, text);

  ProxDetector(playerid, range, COLOR_WHITE, chat_message);
}

stock OOCChat(playerid, const text[], bool:isGlobal = false) {
  new
    chat_message[MAX_PLAYER_NAME + MAX_CHAT_INPUT + 10]
  ;

  format(chat_message, sizeof chat_message, "(( %p[%d]: %s ))", playerid, playerid, text);

  if (isGlobal) {
    SendClientMessageToAll(COLOR_OOC_CHAT, chat_message);
  } else {  
    ProxDetector(playerid, CHAT_OOC_MAX_RANGE, COLOR_WHITE, chat_message);
  }
}

new Text:gBlackScreenTD[MAX_PLAYERS];
CMD:bscreen(playerid) {
  if (GetPVarInt(playerid, "IsBlackScreenEnabled") == 1) {
    SetPVarInt(playerid, "IsBlackScreenEnabled", 0);

    TextDrawHideForPlayer(playerid, gBlackScreenTD[playerid]);
  } else {
    SetPVarInt(playerid, "IsBlackScreenEnabled", 1);
    if (gBlackScreenTD[playerid]) {
      TextDrawShowForPlayer(playerid, gBlackScreenTD[playerid]);
    } else {
      gBlackScreenTD[playerid] = TextDrawCreate(1.0, 1.0, "_");
      TextDrawLetterSize(gBlackScreenTD[playerid], 1, 50);
      TextDrawUseBox(gBlackScreenTD[playerid], true);
      TextDrawBoxColor(gBlackScreenTD[playerid], COLOR_BLACK);
      TextDrawShowForPlayer(playerid, gBlackScreenTD[playerid]);
    }
  }
}
alias:bscreen("bl", "bs")
