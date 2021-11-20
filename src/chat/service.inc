#if defined _chat_service_included
	#endinput
#endif

#define _chat_service_included

enum e_UsageMessage {
  e_umCmd[MAX_COMMAND_NAME],
  e_umMessage[MAX_CHAT_INPUT]
}

new gUsageMessage[][e_UsageMessage] = {
  { "me", "/me [действие]" },
  { "low", "/l(ow) [текст]" },
  { "local", "/local [текст]" },
  { "shout", "/s(hout) [текст]" },
  { "b", "/b [текст]" },
  { "ooc", "/o(oc) [текст]" },
  { "pm", "/pm [id] [текст]" },
  { "sms", "/sms [номер] [текст]" },
  { "do", "/do [действие]" },
  { "todo", "/todo [текст*действие]" }
};

stock SendCommandUsageMessage(playerid, const cmd[]) {
  for(new i = 0; i < sizeof gUsageMessage; i++) {
    if (!strcmp(gUsageMessage[i][e_umCmd], cmd)) {
      SendClientMessage(playerid, COLOR_WHITE, "> Использование: %s", false, gUsageMessage[i][e_umMessage]);

      return 1;
    }
  }

  return 0;
}
