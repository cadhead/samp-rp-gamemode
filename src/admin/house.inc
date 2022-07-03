#if defined _adm_house_included
	#endinput
#endif

#define _adm_house_included

CMD:houseadd(playerid, params[]) {
  return Dialog_Show(playerid, Dialog:houseadd);
}
alias:houseadd("hadd")

CMD:houseedit(playerid) {
  return Dialog_Show(playerid, Dialog:houseedit_main);
}
alias:houseedit("hedit")

DialogCreate:houseadd(playerid) {
  return Dialog_Open(playerid, Dialog:houseadd, DIALOG_STYLE_LIST,
    "¬ыберите интерьер дома",
    gHousesInteriorsNames,
    DIALOG_ACCEPT, DIALOG_CANCEL
  );
}

DialogResponse:houseadd(playerid, response, listitem, inputtext[]) {
  if (!response || gHousesInteriors[listitem][0][0] == -1) return 0;

  new
    enterid,
    propid,
    virtworld = CheckEntersEnterExist(gHousesInteriors[listitem][0][0], ENTER_TYPE_HOUSE),
    property_name[32]
  ;

  format(property_name, sizeof property_name, "House #%d", GetEntersCount() + 1);

  format(gString, sizeof gString, "%s|%d", gHousesInteriors[listitem][2], virtworld);
  SerializeCharacterPosition(playerid, gStringSmall);
  enterid = EntersAddOne(property_name, gStringSmall, gString, ENTER_TYPE_HOUSE);
  propid = PropertiesAddOne(enterid);

  SendClientMessage(playerid, COLOR_SUCCESS, "> %s был успешно создан.", false, property_name);
  SetPVarInt(playerid, "EditedProp", propid);

  return Dialog_Show(playerid, Dialog:houseedit_main);
}
