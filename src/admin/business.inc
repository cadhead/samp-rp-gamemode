#if defined _adm_business_included
	#endinput
#endif

#define _adm_business_included

static property_name[MAX_PLAYERS][32];

CMD:businessadd(playerid, params[]) {
  extract params -> new string:name[32]; else {
    SendClientMessage(playerid, COLOR_WHITE, "> Использование: /b(usiness)add [название] <цена>", false);
    return 0;
  }
  
  property_name[playerid] = name;

  return Dialog_Show(playerid, Dialog:businessadd);
}
alias:businessadd("badd")

CMD:businessedit(playerid) {
  return Dialog_Show(playerid, Dialog:businessedit_main);
}
alias:businessedit("bedit")

DialogCreate:businessadd(playerid) {
  return Dialog_Open(playerid, Dialog:businessadd, DIALOG_STYLE_LIST,
    "Выберите интерьер бизнеса",
    gBusinessInteriorsNames,
    DIALOG_ACCEPT, DIALOG_CANCEL
  );
}

DialogResponse:businessadd(playerid, response, listitem, inputtext[]) {
  if (!response || gBusinessInteriors[listitem][0][0] == -1) return 0;

  new 
    enterid,
    propid,
    virtworld = CheckEntersEnterExist(gBusinessInteriors[listitem][0][0])
  ;

  format(gString, sizeof gString, "%s|%d", gBusinessInteriors[listitem][2], virtworld);
  SerializeCharacterPosition(playerid, gStringSmall);
  enterid = EntersAddOne(property_name[playerid], gStringSmall, gString, ENTER_TYPE_BUSSINESS);
  propid = PropertiesAddOne(enterid);

  SendClientMessage(playerid, COLOR_SUCCESS, "> Бизнес %s был успешно создан.", false, property_name[playerid]);
  SetPVarInt(playerid, "EditedProp", propid);

  return Dialog_Show(playerid, Dialog:businessedit_main);
}
