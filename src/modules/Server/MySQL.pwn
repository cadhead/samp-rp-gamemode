#include <YSI_Coding\y_hooks>
static 
  MySQL:gSQL,        // Main Database Connection Handler
  va_query[2048];     // Main MySQL query string

MySQL:SQL_GetHandle() {
  return gSQL;
}

// Formated mysql_tquery - DML SQL(UPDATE, DELETE, INSERT)
mysql_fquery(MySQL:connection_handle, const fquery[], va_args<>) {
  mysql_format(connectionHandle, va_query, sizeof(va_query), fquery, va_start<2>);

  mysql_tquery(SQL_Handle(), "START TRANSACTION");
  mysql_tquery(connection_handle, va_query);
  mysql_tquery(SQL_Handle(), "COMMIT");

  return 1;
}

// Formated mysql_format with direct string returning
va_fquery(MySQL:connection_handle, const fquery[], va_args<>) {
	mysql_format(connection_handle, va_query, sizeof(va_query), fquery, va_start<2>);
	return va_query;
}

public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle) {
  Log_Write("logfiles/AMX_Query_Log.txt", 
    "[%s] - MySQL Error ID: %d\nError %s: Callback %s\nQuery: %s", 
    ReturnDate(), 
    errorid, 
    error, 
    callback, 
    query
  );

  printf("[%s] - MySQL Error ID: %d\nError %s: Callback %s\nQuery: %s", 
    ReturnDate(), 
    errorid, 
    error, 
    callback, 
    query    
  );

  return 1;
}

hook OnGameModeInit() {
  gSQL = mysql_connect_file();
  if(gSQL == MYSQL_INVALID_HANDLE) {
    print("[SERVER ERROR]: Failed to connect MySQL Database!");

  	return 1;
  }

  mysql_log(ERROR | WARNING);
  print("> MySQL Connection & Log Mode Established.");

  // LoadServerData();

  return 1;
}

hook OnGameModeExit() {
  mysql_close();
  return 1;
}
