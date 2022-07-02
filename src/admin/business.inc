#if defined _adm_business_included
	#endinput
#endif

#define _adm_business_included

static property_name[MAX_PLAYERS][32];

CMD:businessadd(playerid, params[]) {
  extract params -> new string:name[32]; else {
    SendClientMessage(playerid, COLOR_WHITE, "> �������������: /b(usiness)add [��������] <����>", false);
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
    "�������� �������� �������",
    gBusinessInteriorsNames,
    DIALOG_ACCEPT, DIALOG_CANCEL
  );
}

DialogResponse:businessadd(playerid, response, listitem, inputtext[]) {
  if (!response) return 0;

  new 
    enterid,
    propid
  ;

  SerializeCharacterPosition(playerid, gStringSmall);
  enterid = EntersAddOne(property_name[playerid], gStringSmall, gBusinessInteriors[listitem][2], ENTER_TYPE_PROPERTY);
  propid = PropertiesAddOne(enterid);

  SendClientMessage(playerid, COLOR_SUCCESS, "> ������ %s ��� ������� ������.", false, property_name[playerid]);
  SetPVarInt(playerid, "EditedProp", propid);

  return Dialog_Show(playerid, Dialog:businessedit_main);
}