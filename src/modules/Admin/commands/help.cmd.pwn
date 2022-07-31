#define CMD_AHELP_DIALOG_STR_LENGTH           (64 + 256 + 128 + 128)

static const
  dialog_str_helper[64] = cSKYBLUE"[helper]"cWHITE" /answer, /hduty.\n",
  dialog_str_moder[256] = cSKYBLUE"[moder]"cWHITE" /aduty, /lastdriver, /toga, /a, /hp, /arm, /health\n\
    /gotopos, /goto, /checklastlogin, /fly, /akill, /repair\n\
    /freeze, /unfreeze, /slap, /setviwo, /mute, /kick, /skin,\n\
    /jail, /unjail.\n",
  dialog_str_admin[128] = cSKYBLUE"[admin]"cWHITE" /ban, /banip, /edit, /aveh, /togooc, /give.\n",
  dialog_str_owner[128] = cSKYBLUE"[owner]"cWHITE" /make, /delete, /set, /restart.";

CMD:ahelp(playerid) {
  new
    dialog_str[CMD_AHELP_DIALOG_STR_LENGTH];

  if (PlayerIsHelper(playerid)) {
    strcat(dialog_str, dialog_str_helper);
  }

  if (PlayerIsModer(playerid)) {
    strcat(dialog_str, dialog_str_moder);
  }

  if (PlayerIsAdmin(playerid)) {
    strcat(dialog_str, dialog_str_admin);
  }

  if (PlayerIsOwner(playerid)) {
    strcat(dialog_str, dialog_str_owner);
  }

  ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Команды", dialog_str, "OK", "");
}
