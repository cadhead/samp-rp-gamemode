#if defined _hlp_fscm_included
	#endinput
#endif

#define _hlp_fscm_included

stock fSendClientMessage(playerid, color, const text[], NeedMultiLine = true, {Float, _}:...) {
  static
    args,
    str[144]
  ;

  if ((args = numargs()) == 4) {
    SendClientMessage(playerid, color, text, NeedMultiLine);
  } else {
    while (--args >= 4) {
      #emit LCTRL 5
      #emit LOAD.alt args
      #emit SHL.C.alt 2
      #emit ADD.C 12
      #emit ADD
      #emit LOAD.I
      #emit PUSH.pri
    }

    #emit PUSH.S text
    #emit PUSH.C 144
    #emit PUSH.C str
    #emit PUSH.S 8
    #emit SYSREQ.C format
    #emit LCTRL 5
    #emit SCTRL 4
    
    SendClientMessage(playerid, color, str, NeedMultiLine);

    #emit RETN
  }

  return 1;
}

#if defined _ALS_SendClientMessage
	#undef SendClientMessage
#else
	#define _ALS_SendClientMessage
#endif

#define SendClientMessage fSendClientMessage
