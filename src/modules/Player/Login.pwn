#include <YSI_Coding\y_hooks>

static const LOGIN_TIME           = DURATION_MS(5 minutes);
static const LOGIN_MAX_TRIES      = (3);

static
  IsLogged[MAX_PLAYERS],
  Timer:LoginCheckTimer[MAX_PLAYERS],
  LoginInputs[MAX_PLAYERS];

// API
IsPlayerLoggedIn(playerid) {
  return IsLogged[playerid];
}
// -

timer LoginCheck[LOGIN_TIME](playerid) {
  if (!IsPlayerLoggedIn(playerid) && IsPlayerConnected(playerid)) {
    SendClientMessage(playerid, COLOR_ADMIN_ACTION, "> Время на авторизацию вышло.");
    KickPlayer(playerid);
  }

  return 1;
}

hook OnPlayerConnect(playerid) {
  new
    tmpname[MAX_PLAYER_NAME],
    user_id;

  TogglePlayerSpectating(playerid, true);

  LoginCheckTimer[playerid] = defer LoginCheck(playerid);

  GetPlayerName(playerid, tmpname);

  inline Login() {
    SetUserState(playerid);

    Dialog_Show(playerid, Dialog:dLogin_main);
  }

  inline CheckIsCharacterExists() {
    if (!cache_num_rows()) {
      SendRegistrationMessage(playerid);

      return KickPlayer(playerid);
    }

    cache_get_value_int(0, "UserID", user_id);

    MySQL_TQueryInline(SQL_GetHandle(),  
      using inline Login,
      va_fquery(SQL_GetHandle(), "SELECT * FROM accounts WHERE ID = '%d'", user_id)
    );
  }

  MySQL_TQueryInline(SQL_GetHandle(),  
    using inline CheckIsCharacterExists,
    va_fquery(SQL_GetHandle(), "SELECT UserID FROM characters WHERE Name = '%e'", tmpname)
  );

  return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
  stop LoginCheckTimer[playerid];

  IsLogged[playerid] = false;
  LoginCheckTimer[playerid] = Timer:0;
  LoginInputs[playerid] = 0;
}

hook OnPlayerSpawn(playerid) {
  TogglePlayerSpectating(playerid, false);
}

DialogCreate:dLogin_main(playerid) {
  static const info[] = "\\c_______________________________________\n\n\
    \\c "cGREY"Добро пожаловать на "cYELLOW""SERVER_NAME".\n\
    \\c "cGREY"Используйте данные UCP-аккаунта для входа.\n\
    \\c_______________________________________\n\n\
    "cWHITE"Username: "cGREY"%s\n\
    "cWHITE"Password:";

  new
    tmp_str[sizeof(info) + MAX_PLAYER_NAME + 10];

  format(tmp_str, sizeof tmp_str, info, gAccount[playerid][e_acName]);

  return Dialog_Open(playerid, Dialog:dLogin_main, DIALOG_STYLE_PASSWORD, "Авторизация", tmp_str, "Вход", "Помощь");
}

DialogResponse:dLogin_main(playerid, response, listitem, inputtext[]) {
  if (!response) return Dialog_Show(playerid, Dialog:dLogin_main);
  if (IsValidPassword(playerid, inputtext)) {
    new
      tmpname[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, tmpname);

    inline LoadCharacter() {
      SetCharacterState(playerid);
      IsLogged[playerid] = true;
    }

    MySQL_TQueryInline(SQL_GetHandle(),  
      using inline LoadCharacter,
      va_fquery(SQL_GetHandle(), "SELECT * FROM characters WHERE Name = '%e'", tmpname)
    );
    return va_SendClientMessage(playerid, COLOR_YELLOW, "> Привет, %s! Приятной игры.", gAccount[playerid][e_acName]);
  }
  if (strlen(inputtext) < 6) return Dialog_Show(playerid, Dialog:dLogin_main);

  ++LoginInputs[playerid];

  return SendPlayerBadLogin(playerid);
}

static SendPlayerBadLogin(playerid) {
  if (LoginInputs[playerid] >= 3) {
    va_SendClientMessage(playerid, COLOR_ERROR, "> Неверный пароль. Попытка входа неудачна.");

    return KickPlayer(playerid);
  }

  va_SendClientMessage(playerid, COLOR_ERROR,
    "> Неверный пароль. У вас осталось %d попыток пройти авторизацию.",
    LOGIN_MAX_TRIES - LoginInputs[playerid]);
  return Dialog_Show(playerid, Dialog:dLogin_main);
}

static SendRegistrationMessage(playerid) {
  SendClientMessage(playerid, COLOR_YELLOW, "Персонажа с таким именем не существует.");
  SendClientMessage(playerid, COLOR_YELLOW, "Пройти регистрацию можно на сайте "WEB_URL".");
}

static IsValidPassword(playerid, const passwd[]) {
  new
    tmp[65];

  SHA256_PassHash(passwd, gAccount[playerid][e_acPasswdSalt], tmp, 64);
  return !strcmp(tmp, gAccount[playerid][e_acPasswdHash]);
}

static SetUserState(playerid) {
  cache_get_value_int(0, "ID", gAccount[playerid][e_acID]);
  cache_get_value(0, "Username", gAccount[playerid][e_acName]);
  cache_get_value(0, "PassHash", gAccount[playerid][e_acPasswdHash]);
  cache_get_value(0, "PassSalt", gAccount[playerid][e_acPasswdSalt]);
  cache_get_value(0, "Email", gAccount[playerid][e_acEmail]);
  cache_get_value_int(0, "ALevel", gAccount[playerid][e_acAdmin]);
  cache_get_value_int(0, "PLevel", gAccount[playerid][e_acPremium]);
}

static SetCharacterState(playerid) {
  new tmp_str[128];

  cache_get_value_int(0, "Cash", gCharacter[playerid][e_cCash]);
  cache_get_value_int(0, "Skin", gCharacter[playerid][e_cSkin]);
  cache_get_value(0, "SpawnPos", tmp_str);
  sscanf(tmp_str, "p<|>ffffii", 
    gCharacter[playerid][e_cSpawn][POS_X],
    gCharacter[playerid][e_cSpawn][POS_Y],
    gCharacter[playerid][e_cSpawn][POS_Z],
    gCharacter[playerid][e_cSpawn][POS_ANGLE],
    gCharacter[playerid][e_cSpawnWorld],
    gCharacter[playerid][e_cSpawnInt]
  );

  SetSpawnPointDefault(playerid);
  FormatCharacterName(playerid);
  SetSpawnInfo(playerid, 0, gCharacter[playerid][e_cSkin],
    XYZ0(gCharacter[playerid][e_cSpawn]),
    gCharacter[playerid][e_cSpawn][POS_ANGLE],
    0, 0, 0, 0, 0, 0);
  SpawnPlayer(playerid);
}

static SetSpawnPointDefault(playerid) {
  for (new i; i < 3; i++) { // Check is character has no spawn point
    if (gCharacter[playerid][e_cSpawn][i] == 0) break;
    else return;
  }

  gCharacter[playerid][e_cSpawn][POS_X] 	  = CHARACTER_DEFAULT_POS_X;
  gCharacter[playerid][e_cSpawn][POS_Y]     = CHARACTER_DEFAULT_POS_Y;
  gCharacter[playerid][e_cSpawn][POS_Z]     = CHARACTER_DEFAULT_POS_Z;
  gCharacter[playerid][e_cSpawn][POS_ANGLE] = CHARACTER_DEFAULT_POS_A;
}

static FormatCharacterName(playerid) {
  new name[MAX_PLAYER_NAME + 1];

  GetPlayerName(playerid, name);

  for (new i = 0; i < MAX_PLAYER_NAME; i++) {
    if (name[i] == '_') name[i] = ' ';
  }

  strcopy(gCharacterFormatedName[playerid], name);
}

public OnPlayerRequestClass(playerid, classid) {
  return 0;
}

public OnPlayerRequestSpawn(playerid) {
	return 0;
}