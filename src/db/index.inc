#if defined _db_included
	#endinput
#endif

#define _db_included

#include <YSI_Coding\y_hooks>

#define DATABASE_HOST     "remotemysql.com"
#define DATABASE_USER     "N2D6jM6jIm"
#define DATABASE_NAME     "N2D6jM6jIm"
#define DATABASE_PASSWD   "qrc7cyARhE"

static MySQL:gConnectionHandle;

hook OnGameModeInit() {
  DB_Connect(DATABASE_HOST, DATABASE_USER, DATABASE_PASSWD, DATABASE_NAME);
}

hook OnGameModeExit() {
  DB_ConnectionClose();
}

public DB_Connect(const host[], const user[], const pass[], const db[]) {
  new MySQLOpt:option_id = mysql_init_options();
  mysql_set_option(option_id, AUTO_RECONNECT, true);

  gConnectionHandle = mysql_connect(host, user, pass, db);
  mysql_tquery(gConnectionHandle, !"SET CHARACTER SET 'utf8'", "", "");
  mysql_tquery(gConnectionHandle, !"SET NAMES 'utf8'", "", "");
  mysql_tquery(gConnectionHandle, !"SET character_set_client = 'cp1251'", "", "");
  mysql_tquery(gConnectionHandle, !"SET character_set_connection = 'cp1251'", "", "");
  mysql_tquery(gConnectionHandle, !"SET character_set_results = 'cp1251'", "", "");
  mysql_tquery(gConnectionHandle, !"SET SESSION collation_connection = 'utf8_general_ci'", "", "");

  switch(mysql_errno()) {
    case 0: print("successfully connected to database.");
    case 1044: print("Can't connect to database. [Wrong username]");
    case 1045: print("Can't connect to database. [Wrong password]");
    case 1049: print("Can't connect to database. [Not valid DB]");
    case 2003: print("Can't connect to database. [Can't connect to host]");
    case 2005: print("Can't connect to database. [Wrong host]");
    default: printf("Can't connect to database. [Unsigned error, code: %d]", mysql_errno());
  }
}

public DB_ConnectionClose() {
  return mysql_close(gConnectionHandle);
}

public MySQL:DB_GetConnectionHandle() {
  return gConnectionHandle;
}
