StartGMX() {
  for (new a = 1; a <= 20; a++) {
    SendClientMessageToAll(-1, "\n");
    SendClientMessageToAll(-1, "\n");
    SendClientMessageToAll(-1, "\n");
    SendClientMessageToAll(-1, "\n");
    SendClientMessageToAll(-1, "\n");
  }

  CountSeconds_Set(30);

  foreach (new i : Player) {
    TogglePlayerControllable(i, false);
    SetPlayerPos(i, 1433.4633, -974.7463, 58.0000);
    InterpolateCameraPos(i, 1431.9108, -895.1843, 73.9480, 1431.9108, -895.1843, 73.9480, 100000, CAMERA_MOVE);
    InterpolateCameraLookAt(i, 1431.8031, -894.1859, 74.0085, 1431.8031, -894.1859, 74.0085, 100000, CAMERA_MOVE);
    CountSeconds_Set(CountSeconds_Get() + 3);
  }

  GMX_Set(1);

  new
    rconstring[100];
  format(rconstring, sizeof(rconstring), "hostname %s [Перезагрузка...]", SERVER_NAME);
  SendRconCommand(rconstring);
  SendRconCommand("password db2a5e36c68a0ed8d60065effed57d91c83e1b261333ff8f305");
  SendClientMessageToAll(COLOR_ADMIN_ACTION, "> Сервер скоро будет перезагружен.");
  SendClientMessageToAll(COLOR_ADMIN_ACTION, "> Пожалуйста, оставайтесь онлайн до автоматического отсоединения.");
}

task GMXTimer[1000]() {
  if (GMX_Get() == 1) {
    CountSeconds_Set(CountSeconds_Get() - 1);

    new
      string[10];

    format(string, sizeof(string), "%d", CountSeconds_Get());
    GameTextForAll(string, 1000, 4);

    if (CountSeconds_Get() < 1) {
      GMX_Set(0);
    }

    GameModeExit();

    return 1;
  }

  if (GMX_Get() == 2) {
    CountSeconds_Set(CountSeconds_Get() - 1);

    if (CountSeconds_Get() < 1) {
      GMX_Set(0);
      CountSeconds_Set(0);
      SendRconCommand("password 0");

      return 1;
    }
  }

  return 1;
}
