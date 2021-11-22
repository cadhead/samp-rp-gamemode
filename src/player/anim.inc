#if defined _pl_anim_included
  #endinput
#endif

#define _pl_anim_included

#include <YSI_Coding\y_hooks>

new static player_animation[MAX_PLAYERS];
#define IsPlayedPlayerAnimation(%0) player_animation[%0]
#define SetPlayerAnimationPlayed(%0,%1) player_animation[%0] = %1

hook OnPlayerSpawn(playerid) {
  PreloadAnimations(playerid);

  return 1;
}

stock PlayAnimation(playerid, const animlib[], const animname[], Float:fDelta, loop, lockx, locky, freeze, time) {
  if (GetCharacterDeathStage(playerid)) return 1;

  SetPlayerAnimationPlayed(playerid, 0);

  if (loop || freeze) {
    SetPlayerAnimationPlayed(playerid, 1);
  }

  ApplyAnimation(playerid, animlib, "null", 0.0,0,0,0,0,0, 1);
  ApplyAnimation(playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, 1);

  return 1;
}

stock StopAnimation(playerid) {
  if (GetCharacterDeathStage(playerid)) return 1;

  SetPlayerAnimationPlayed(playerid, 0);
  ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);

  return 1;
}

stock PreloadAnimations(playerid) {
  PreloadAnimLib(playerid, "BOMBER");
  PreloadAnimLib(playerid, "RAPPING");
  PreloadAnimLib(playerid, "SHOP");
  PreloadAnimLib(playerid, "BEACH");
  PreloadAnimLib(playerid, "SMOKING");
  PreloadAnimLib(playerid, "FOOD");
  PreloadAnimLib(playerid, "ON_LOOKERS");
  PreloadAnimLib(playerid, "DEALER");
  PreloadAnimLib(playerid, "CRACK");
  PreloadAnimLib(playerid, "CARRY");
  PreloadAnimLib(playerid, "COP_AMBIENT");
  PreloadAnimLib(playerid, "PARK");
  PreloadAnimLib(playerid, "INT_HOUSE");
  PreloadAnimLib(playerid, "FOOD");
  PreloadAnimLib(playerid, "GHANDS");
  PreloadAnimLib(playerid, "GANGS");
  PreloadAnimLib(playerid, "PED");
  PreloadAnimLib(playerid, "RIOT");
  PreloadAnimLib(playerid, "PAULNMAC");
  PreloadAnimLib(playerid, "FIGHT_B");
  PreloadAnimLib(playerid, "FIGHT_D");
  PreloadAnimLib(playerid, "SPRAYCAN");
  PreloadAnimLib(playerid, "MISC");
  PreloadAnimLib(playerid, "GRAVEYARD");
  PreloadAnimLib(playerid, "POLICE");
  PreloadAnimLib(playerid, "CAR_CHAT");
  PreloadAnimLib(playerid, "SWEET");
  PreloadAnimLib(playerid, "SUNBATHE");
  PreloadAnimLib(playerid, "CRIB");
  PreloadAnimLib(playerid, "BAR");
  PreloadAnimLib(playerid, "DANCING");
  PreloadAnimLib(playerid, "VENDING");
  PreloadAnimLib(playerid, "BSKTBALL");
  PreloadAnimLib(playerid, "BD_FIRE");
  PreloadAnimLib(playerid, "COLT45");
  PreloadAnimLib(playerid, "SILENCED");
  PreloadAnimLib(playerid, "TEC");
  PreloadAnimLib(playerid, "UZI");
  PreloadAnimLib(playerid, "OTB");
  PreloadAnimLib(playerid, "CAR");
  PreloadAnimLib(playerid, "MEDIC");
  PreloadAnimLib(playerid, "WUZI");
  PreloadAnimLib(playerid, "BLOWJOBZ");
  PreloadAnimLib(playerid, "LOWRIDER");
  PreloadAnimLib(playerid, "FINALE");
  PreloadAnimLib(playerid, "CLOTHES");
  PreloadAnimLib(playerid, "SNM");
}

stock PreloadAnimLib(playerid, const animlib[]) {
  ApplyAnimation(playerid, animlib, "null", 0.0,0,0,0,0,0);
}

CMD:stopanim(playerid) {
  return StopAnimation(playerid);
}
alias:stopanim("sa")

// === == === == === === == === == === === == === == === === == === == === === == === == ===

CMD:handsup(playerid, params[]) {
  
  PlayAnimation(playerid, "ROB_BANK","SHP_HandsUp_Scr", 4.0, 0, 1, 1, 1, 0);
  return true;
}

CMD:sit(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","SEAT_down",4.0,0,0,1,1,0);
  return true;
}

CMD:aim(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","gang_gunstand",3.0,0,1,1,1,0);
  return true;
}

CMD:cellin(playerid, params[]) {
  
  SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
  return true;
}

CMD:cellout(playerid, params[]) {
  
  SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
  return true;
}


CMD:drunk(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","WALK_DRUNK",4.1,1,1,1,1,1);
  return true;
}

CMD:bomb(playerid, params[]) {
  
  PlayAnimation(playerid, "BOMBER","BOM_Plant",4.0,0,0,0,0,0);
  return true;
}

CMD:bar(playerid, params[]) {
  
  PlayAnimation(playerid,"BAR","Barserve_bottle",4.0,0,0,0,0,0);
  return true;
}

CMD:stoptaxi(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","IDLE_taxi",4.0,0,0,0,0,0);
  return true;
}

CMD:getarrested(playerid, params[]) {
  
  PlayAnimation(playerid,"ped", "ARRESTgun", 4.0, 0, 1, 1, 1, -1);
  return true;
}

CMD:laugh(playerid, params[]) {
  
  PlayAnimation(playerid, "RAPPING", "Laugh_01", 4.0, 0, 0, 0, 0, 0);
  return true;
}

CMD:lookout(playerid, params[]) {
  
  PlayAnimation(playerid, "SHOP", "ROB_Shifty", 4.0, 0, 0, 0, 0, 0);
  return true;
}

CMD:crossarms(playerid, params[]) {
  
  PlayAnimation(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1);
  return true;
}

CMD:hide(playerid, params[]) {
  
  PlayAnimation(playerid, "ped", "cower", 3.0, 1, 0, 0, 0, 0);
  return true;
}

CMD:vomit(playerid, params[]) {
  
  PlayAnimation(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0);
  return true;
}

CMD:eat(playerid, params[]) {
  
  PlayAnimation(playerid, "FOOD", "EAT_Burger", 4.1,1,1,1,1,1);
  return true;
}

CMD:sipdrink(playerid, params[]) {
  
  PlayAnimation(playerid, "GANGS", "drnkbr_prtl", 4.1,1,1,1,1,1);
  return true;
}

CMD:slapass(playerid, params[]) {
  
  PlayAnimation(playerid, "SWEET", "sweet_ass_slap", 4.0, 0, 0, 0, 0, 0);
  return true;
}

CMD:chat(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","IDLE_CHAT",4.0,1,0,0,1,1);
  return true;
}

CMD:fucku(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","fucku",4.0,0,0,0,0,0);
  return true;
}

CMD:taichi(playerid, params[]) {
  
  PlayAnimation(playerid,"PARK","Tai_Chi_Loop",4.0,1,0,0,0,0);
  return true;
}

CMD:injured(playerid, params[]) {
  
  PlayAnimation(playerid, "SWEET", "Sweet_injuredloop", 4.0,0,0,1,1,0);
  return true;
}

CMD:no(playerid, params[]) {
  
  PlayAnimation(playerid,"GANGS","Invite_No",4.0,0,0,0,0,0);
  return true;
}

CMD:yes(playerid, params[]) {
  
  PlayAnimation(playerid,"GANGS","Invite_Yes",4.0,0,0,0,0,0);
  return true;
}

CMD:crawl(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","CAR_crawloutRHS",4.0,0,0,0,0,0);
  return true;
}

CMD:push(playerid, params[]) {
  
  PlayAnimation(playerid,"GANGS","shake_cara",4.0,0,0,0,0,0);
  return true;
}

CMD:akick(playerid, params[]) {
  
  PlayAnimation(playerid,"POLICE","Door_Kick",4.0,0,0,0,0,0);
  return true;
}

CMD:facepalm(playerid, params[]) {
  
  PlayAnimation(playerid,"MISC","plyr_shkhead",4.0,0,0,0,0,0);
  return true;
}

CMD:balls(playerid, params[]) {
  
  PlayAnimation(playerid,"MISC","scratchballs_01",4.0,0,0,0,0,0);
  return true;
}

CMD:lowbodypush(playerid, params[]) {
  PlayAnimation(playerid,"GANGS","shake_carSH",4.0,0,0,0,0,0);
  return true;
}

CMD:aspray(playerid, params[]) {
  
  PlayAnimation(playerid,"SPRAYCAN","spraycan_full",4.0,0,0,0,0,0);
  return true;
}

CMD:medic(playerid, params[]) {
  
  PlayAnimation(playerid,"MEDIC","CPR",4.0,0,0,0,0,0);
  return true;
}

CMD:koface(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","KO_shot_face",4.0,0,1,1,1,0);
  return true;
}

CMD:kostomach(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","KO_shot_stom",4.0,0,1,1,1,0);
  return true;
}

CMD:lifejump(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","EV_dive",4.0,0,1,1,1,0);
  return true;
}

CMD:rollfall(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","BIKE_fallR",4.0,0,1,1,1,0);
  return true;
}

CMD:hoodfrisked(playerid, params[]) {
  
  PlayAnimation(playerid,"POLICE","crm_drgbst_01",1.0,0,1,1,1,0);
  return true;
}

CMD:flip(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","KD_left",4.1,0,1,1,1,0);
  return true;
}

CMD:box(playerid, params[]) {
  
  PlayAnimation(playerid,"GYMNASIUM","GYMshadowbox",4.0,1,1,1,1,0);
  return true;
}

CMD:chant(playerid, params[]) {
  
  PlayAnimation(playerid,"RIOT","RIOT_CHANT",4.0,1,1,1,1,0);
  return true;
}

CMD:finger(playerid, params[]) {
  
  PlayAnimation(playerid,"RIOT","RIOT_FUKU",2.0,0,0,0,0,0);
  return true;
}

CMD:gpunch(playerid, params[]) {
  
  PlayAnimation(playerid,"FIGHT_B","FightB_G",4.0,0,0,0,0,0);
  return true;
}

CMD:gkick(playerid, params[]) {
  
  PlayAnimation(playerid,"FIGHT_D","FightD_G",4.0,0,0,0,0,0);
  return true;
}

CMD:lowthrow(playerid, params[]) {
  
  PlayAnimation(playerid,"GRENADE","WEAPON_throwu",3.0,0,0,0,0,0);
  return true;
}

CMD:riot(playerid, params[]) {
  
  PlayAnimation(playerid,"RIOT","RIOT_ANGRY",4.0,0,0,0,0,0);
  return true;
}

CMD:abp(playerid, params[]) {
  
  PlayAnimation(playerid,"benchpress","gym_bp_celebrate",4.0,0,0,0,0,0);
  return true;
}

CMD:cry(playerid, params[]) {
  
  PlayAnimation(playerid,"GRAVEYARD","mrnF_loop",4.0,1,0,0,0,0);
  return true;
}

CMD:taxir(playerid, params[]) {
  
  PlayAnimation(playerid, "MISC","hiker_pose", 3.0,0,1,1,1,0);
  return true;
}

CMD:taxil(playerid, params[]) {
  
  PlayAnimation(playerid, "MISC","hiker_pose_L", 3.0,0,1,1,1,0);
  return true;
}

CMD:gro(playerid, params[]) {
  
  PlayAnimation(playerid,"BEACH", "ParkSit_M_loop", 4.0, 1, 0, 0, 0, 0);
  return true;
}

CMD:seat(playerid, params[]) {
  
  PlayAnimation(playerid,"INT_HOUSE","LOU_In",4.0,0,0,1,1,0);
  return true;
}

CMD:tatto(playerid, params[]) {
  
  PlayAnimation(playerid,"TATTOOS", "TAT_ArmR_Pose_P", 4.1, 0, 1, 1, 1, 0);
  return true;
}

CMD:waiml(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","Driveby_L",4.1,0,1,1,1,1);
  return true;
}

CMD:waimr(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","Driveby_R",4.1,0,1,1,1,1);
  return true;
}

CMD:caim(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","IDLE_ROCKET",4.1,0,1,1,1,1);
  return true;
}

CMD:creep(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","Player_Sneak",4.1,1,1,1,1,1);
  return true;
}

CMD:sroll(playerid, params[]) {
  
  PlayAnimation(playerid,"SWAT","JMP_Wall1m_180",4.1,0,1,1,1,0);
  return true;
}

CMD:gesture(playerid, params[]) {
  
  PlayAnimation(playerid,"SWAT","swt_lkt",4.0,0,0,0,0,0);
  return true;
}

CMD:lookoutr(playerid, params[]) {
  
  PlayAnimation(playerid,"SWAT","swt_wllpk_L",4.0,0,0,1,1,0);
  return true;
}

CMD:lookoutl(playerid, params[]) {
  
  PlayAnimation(playerid,"SWAT","swt_wllpk_R",4.0,0,0,1,1,0);
  return true;
}

CMD:agreement(playerid, params[]) {
  
  PlayAnimation(playerid,"COP_AMBIENT","Coplook_think",4.0,1,0,0,0,0);
  return true;
}

CMD:bend(playerid, params[]) {
  
  PlayAnimation(playerid,"BAR","Barserve_order",4.0,0,0,0,0,0);
  return true;
}

CMD:rod(playerid, params[]) {
  
  PlayAnimation(playerid,"benchpress","gym_bp_up_A",4.0,0,0,1,1,0);
  return true;
}

CMD:tgro(playerid, params[]) {
  
  PlayAnimation(playerid,"CAMERA","camcrch_cmon",4.0,0,0,1,1,0);
  return true;
}

CMD:cmouth(playerid, params[]) {
  
  PlayAnimation(playerid,"ON_LOOKERS","panic_in",4.0,0,0,1,1,0);
  return true;
}

CMD:gog(playerid, params[]) {
  
  PlayAnimation(playerid,"goggles","goggles_put_on",4.1,0,1,1,1,1);
  return true;
}

CMD:nfall(playerid, params[]) {
  
  PlayAnimation(playerid,"HEIST9","CAS_G2_GasKO",4.1,0,1,1,1,0);
  return true;
}

CMD:hsit(playerid, params[]) {
  
  PlayAnimation(playerid,"INT_OFFICE","OFF_Sit_Bored_Loop",4.0,1,0,1,1,0);
  return true;
}

CMD:csit(playerid, params[]) {
  
  PlayAnimation(playerid,"INT_OFFICE","OFF_Sit_Type_Loop",4.0,1,0,1,1,0);
  return true;
}

CMD:bracing(playerid, params[]) {
  
  PlayAnimation(playerid,"PLAYIDLES","stretch",4.0,0,0,0,0,0);
  return true;
}

CMD:pool(playerid, params[]) {
  
  PlayAnimation(playerid,"POOL","POOL_Long_Start",4.1,0,1,1,1,0);
  return true;
}

CMD:ssearch(playerid, params[]) {
  
  PlayAnimation(playerid,"ROB_BANK","CAT_Safe_Rob",4.0,1,0,0,0,0);
  return true;
}

CMD:daim(playerid, params[]) {
  
  PlayAnimation(playerid,"RYDER","Van_Stand_Crate",3.0,0,1,1,1,0);
  return true;
}

CMD:rhandl(playerid, params[]) {
  
  PlayAnimation(playerid,"SCRATCHING","scdlulp",4.0,0,0,1,1,0);
  return true;
}

CMD:rhandr(playerid, params[]) {
  
  PlayAnimation(playerid,"SCRATCHING","scdrulp",4.0,0,0,1,1,0);
  return true;
}

CMD:hstand(playerid, params[]) {
  
  PlayAnimation(playerid,"SCRATCHING","scdrdlp",4.0,0,0,1,1,0);
  return true;
}

CMD:nlean(playerid, params[]) {
  
  PlayAnimation(playerid,"SHAMAL","SHAMAL_align",4.1,0,1,1,1,0);
  return true;
}

CMD:shelter(playerid, params[]) {
  
  PlayAnimation(playerid,"SHOP","SHP_Duck_Fire",4.0,0,0,1,1,0);
  return true;
}

CMD:lookback(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","flee_lkaround_01",4.0,0,0,0,0,0);
  return true;
}

CMD:wsit(playerid, params[]) {
  
  PlayAnimation(playerid,"SHOP","SHP_Gun_Duck",4.0,0,0,1,1,0);
  return true;
}

CMD:waim(playerid, params[]) {
  
  PlayAnimation(playerid,"TEC","TEC_reload",4.1,0,1,1,1,1);
  return true;
}

CMD:hangon(playerid, params[]) {
  
  PlayAnimation(playerid,"TRAIN","tran_ouch",4.0,0,0,1,1,0);
  return true;
}

CMD:sleepl(playerid, params[]) {
  
  PlayAnimation(playerid,"INT_HOUSE","BED_In_L",4.0,0,0,1,1,0);
  return true;
}

CMD:sleepr(playerid, params[]) {
  
  PlayAnimation(playerid,"INT_HOUSE","BED_In_R",4.0,0,0,1,1,0);
  return true;
}

CMD:blowj(playerid, params[]) {
  
  PlayAnimation(playerid,"BLOWJOBZ", "BJ_COUCH_START_W", 4.1, 0, 1, 1, 1, 0 );
  return true;
}

CMD:rseat(playerid, params[]) {
  
  PlayAnimation(playerid,"BLOWJOBZ", "BJ_COUCH_START_P", 4.1, 0, 1, 1, 1, 0 );
  return true;
}

CMD:polwalk(playerid, params[]) {
  
  PlayAnimation(playerid,"POLICE","Cop_move_FWD",3.0,1,1,1,1,1);
  return true;
}

CMD:nflip(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","BIKE_fall_off",4.1,0,1,1,1,0);
  return true;
}

CMD:csdead(playerid, params[]) {
  
  PlayAnimation(playerid,"WUZI","CS_Dead_Guy",4.1,0,1,1,1,0);
  return true;
}

CMD:follow(playerid, params[]) {
  
  PlayAnimation(playerid,"WUZI","Wuzi_follow",4.1,0,1,1,1,1);
  return true;
}

CMD:grnd(playerid, params[]) {
  
  PlayAnimation(playerid,"WUZI","Wuzi_grnd_chk",4.0,0,0,0,0,0);
  return true;
}

CMD:copa(playerid, params[]) {
  
  PlayAnimation(playerid,"COP_AMBIENT","Copbrowse_in",4.1,0,1,1,1,0);
  return true;
}

CMD:cmon(playerid, params[]) {
  
  PlayAnimation(playerid,"OTB","wtchrace_cmon",4.1,0,1,1,1,0);
  return true;
}

CMD:lose(playerid, params[]) {
  
  PlayAnimation(playerid,"OTB","wtchrace_lose",4.1,0,1,1,1,0);
  return true;
}

CMD:win(playerid, params[]) {
  
  PlayAnimation(playerid,"OTB","wtchrace_win",4.1,0,1,1,1,0);
  return true;
}

CMD:gunthreat(playerid, params[]) {
  
  PlayAnimation(playerid,"SHOP","SHP_Gun_Threat",4.1,0,1,1,1,0);
  return true;
}

CMD:givecash(playerid, params[]) {
  
  PlayAnimation(playerid,"SHOP","SHP_Rob_GiveCash",4.1,0,1,1,1,0);
  return true;
}

CMD:robr(playerid, params[]) {
  
  PlayAnimation(playerid,"SHOP","SHP_Rob_React",4.1,0,1,1,1,0);
  return true;
}

CMD:serend(playerid, params[]) {
  
  PlayAnimation(playerid,"SHOP","SHP_Serve_End",4.1,0,1,1,1,0);
  return true;
}

CMD:heist(playerid, params[]) {
  
  PlayAnimation(playerid,"HEIST9","Use_SwipeCard",4.0,0,0,0,0,0);
  return true;
}

CMD:frontfall(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","FLOOR_hit_f",4.1,0,1,1,1,0);
  return true;
}

CMD:pants(playerid, params[]) {
  
  PlayAnimation(playerid,"BLOWJOBZ","BJ_STAND_END_P",4.0,0,0,0,0,0);
  return true;
}
/////////////////////////////////////////////////////////////////////////
CMD:tired(playerid, params[]) {
  
  PlayAnimation(playerid,"FAT","IDLE_tired",4.0,0,0,1,1,0);
  return true;
}

CMD:climb(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","CLIMB_jump",4.0,0,0,1,1,0);
  return true;
}

CMD:tlean(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","DRIVE_BOAT",4.0,0,0,1,1,0);
  return true;
}

CMD:pushup(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","getup_front",4.0,1,0,1,1,0);
  return true;
}

CMD:protection(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","FightShB",4.0,0,1,1,1,1);
  return true;
}

CMD:swallow(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","gum_eat",4.0,0,0,0,0,0);
  return true;
}

CMD:stand(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","IDLE_HBHB",3.0,0,1,1,1,0);
  return true;
}

CMD:pullhand(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","Jetpack_Idle",3.0,0,1,1,1,0);
  return true;
}

CMD:nlook(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","roadcross_gang",4.0,0,0,0,0,0);
  return true;
}

CMD:extend(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","Shove_Partial",4.1,0,1,1,1,1);
  return true;
}

CMD:stopit(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","Walk_DoorPartial",4.0,0,0,0,0,0);
  return true;
}

CMD:ksit(playerid, params[]) {
  
  PlayAnimation(playerid,"INT_OFFICE","OFF_Sit_Crash",4.0,1,0,1,1,0);
  return true;
}

CMD:esit(playerid, params[]) {
  
  PlayAnimation(playerid,"INT_OFFICE","OFF_Sit_Drink",4.0,1,0,1,1,0);
  return true;
}

CMD:tsit(playerid, params[]) {
  
  PlayAnimation(playerid,"INT_OFFICE","OFF_Sit_Watch",4.0,0,0,1,1,0);
  return true;
}

CMD:rtake(playerid, params[]) {
  
  PlayAnimation(playerid,"BAR","Barserve_give",4.0,0,0,0,0,0);
  return true;
}

CMD:forwardlook(playerid, params[]) {
  
  PlayAnimation(playerid,"BD_FIRE","BD_Panic_02",4.1,0,1,1,1,0);
  return true;
}

CMD:wforwardlook(playerid, params[]) {
  
  PlayAnimation(playerid,"BD_FIRE","BD_Panic_03",4.1,0,1,1,1,0);
  return true;
}

CMD:taction(playerid, params[]) {
  
  PlayAnimation(playerid,"BD_FIRE","wash_up",4.0,0,0,0,0,0);
  return true;
}

CMD:catch(playerid, params[]) {
  
  PlayAnimation(playerid,"MD_CHASE","MD_HANG_Loop",4.1,0,1,1,1,0);
  return true;
}

CMD:despair(playerid, params[]) {
  
  PlayAnimation(playerid,"BSKTBALL","BBALL_react_miss",4.0,0,0,0,0,0);
  return true;
}

CMD:rooting(playerid, params[]) {
  
  PlayAnimation(playerid,"BSKTBALL","BBALL_react_score",4.1,1,1,1,1,0);
  return true;
}

CMD:spyglass(playerid, params[]) {
  
  PlayAnimation(playerid,"CAMERA","picstnd_take",4.1,0,1,1,1,0);
  return true;
}

CMD:looksky(playerid, params[]) {
  
  PlayAnimation(playerid,"ON_LOOKERS","lkup_loop",4.1,0,1,1,1,0);
  return true;
}

CMD:mshow(playerid, params[]) {
  
  PlayAnimation(playerid,"ON_LOOKERS","panic_point",4.1,0,1,1,1,0);
  return true;
}

CMD:wshow(playerid, params[]) {
  
  PlayAnimation(playerid,"ON_LOOKERS","panic_shout",4.1,0,1,1,1,0);
  return true;
}

CMD:hshow(playerid, params[]) {
  
  PlayAnimation(playerid,"ON_LOOKERS","point_loop",4.1,0,1,1,1,0);
  return true;
}

CMD:sh(playerid, params[]) {
  
  PlayAnimation(playerid,"ON_LOOKERS","shout_in",4.0,0,0,0,0,0);
  return true;
}

CMD:crossfingers(playerid, params[]) {
  
  PlayAnimation(playerid,"CASINO","cards_loop",4.1,0,1,1,1,0);
  return true;
}

CMD:delight(playerid, params[]) {
  
  PlayAnimation(playerid,"CASINO","manwinb",4.0,0,0,0,0,0);
  return true;
}

CMD:hdelight(playerid, params[]) {
  
  PlayAnimation(playerid,"CASINO","manwind",4.0,0,0,0,0,0);
  return true;
}

CMD:showtable(playerid, params[]) {
  
  PlayAnimation(playerid,"CASINO","Roulette_bet",4.1,0,1,1,1,0);
  return true;
}

CMD:tfacepalm(playerid, params[]) {
  
  PlayAnimation(playerid,"CASINO","Roulette_lose",4.1,0,1,1,1,0);
  return true;
}

CMD:tpull(playerid, params[]) {
  
  PlayAnimation(playerid,"CASINO","Slot_in",4.1,0,1,1,1,0);
  return true;
}

CMD:fail(playerid, params[]) {
  
  PlayAnimation(playerid,"CASINO","Slot_lose_out",4.0,0,0,0,0,0);
  return true;
}

CMD:joy(playerid, params[]) {
  
  PlayAnimation(playerid,"CASINO","Slot_win_out",4.0,0,0,0,0,0);
  return true;
}

CMD:wear(playerid, params[]) {
  
  PlayAnimation(playerid,"CARRY","crry_prtial",4.1,0,1,1,1,1);
  return true;
}

CMD:fsit(playerid, params[]) {
  
  PlayAnimation(playerid,"JST_BUISNESS","girl_02",4.1,0,1,1,1,0);
  return true;
}

CMD:crushjump(playerid, params[]) {
  
  PlayAnimation(playerid,"DODGE","Crush_Jump",4.1,0,1,1,1,0);
  return true;
}

CMD:scatch(playerid, params[]) {
  
  PlayAnimation(playerid,"FINALE","FIN_LegsUp_Loop",4.1,0,1,1,1,0);
  return true;
}

CMD:lookfloor(playerid, params[]) {
  
  PlayAnimation(playerid,"FINALE","FIN_Cop1_Loop",4.1,0,1,1,1,0);
  return true;
}

CMD:tramplefloor(playerid, params[]) {
  
  PlayAnimation(playerid,"FINALE","FIN_Cop1_Stomp",4.1,1,1,1,1,0);
  return true;
}

CMD:swing(playerid, params[]) {
  
  PlayAnimation(playerid,"Freeweights","gym_free_B",4.1,0,1,1,1,0);
  return true;
}

CMD:nbp(playerid, params[]) {
  
  PlayAnimation(playerid,"Freeweights","gym_free_celebrate",4.0,0,0,0,0,0);
  return true;
}

CMD:takehead(playerid, params[]) {
  
  PlayAnimation(playerid,"HAIRCUTS","BRB_Cut",4.1,0,1,1,1,0);
  return true;
}

CMD:readtable(playerid, params[]) {
  
  PlayAnimation(playerid,"SCRATCHING","sclng_r",4.1,0,1,1,1,0);
  return true;
}

CMD:squat(playerid, params[]) {
  
  PlayAnimation(playerid,"TEC","TEC_crouchfire",4.1,0,1,1,1,0);
  return true;
}

CMD:sprawl(playerid, params[]) {
  
  PlayAnimation(playerid,"TATTOOS","TAT_Idle_Loop_T",4.1,0,1,1,1,0);
  return true;
}

CMD:throwmoney(playerid, params[]) {
  
  PlayAnimation(playerid,"STRIP","PUN_CASH",4.0,0,0,0,0,0);
  return true;
}

CMD:sho(playerid, params[]) {
  
  PlayAnimation(playerid,"STRIP","PUN_HOLLER",4.0,0,0,0,0,0);
  return true;
}

CMD:faim(playerid, params[]) {
  
  PlayAnimation(playerid,"SWORD","sword_IDLE",4.1,0,1,1,1,0);
  return true;
}

CMD:piss(playerid, params[]) {
  
  PlayAnimation(playerid,"PAULNMAC","Piss_in",4.1,0,1,1,1,0);
  return true;
}

CMD:swingback(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","getup",4.1,1,1,1,1,0);
  return true;
}

CMD:onehand(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","CLIMB_jump2fall",4.1,0,1,1,1,0);
  return true;
}

CMD:backwalk(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","gas_cwr",4.1,1,1,1,1,1);
  return true;
}

CMD:feettog(playerid, params[]) {
  
  PlayAnimation(playerid,"PED","Idlestance_fat",4.1,0,1,1,1,0);
  return true;
}

CMD:mirro(playerid, params[]) {
  
  PlayAnimation(playerid,"CLOTHES","CLO_Pose_Hat",4.1,0,1,1,1,0);
  return true;
}

CMD:hips(playerid, params[]) {
  
  PlayAnimation(playerid,"COP_AMBIENT","Coplook_shake",4.1,0,1,1,1,0);
  return true;
}

CMD:pullo(playerid, params[]) {
  
  PlayAnimation(playerid,"AIRPORT","thrw_barl_thrw",4.1,0,1,1,1,0);
  return true;
}

CMD:obalance(playerid, params[]) {
  
  PlayAnimation(playerid,"BD_FIRE","BD_Panic_02",4.1,0,1,1,1,0);
  return true;
}

CMD:wobalance(playerid, params[]) {
  
  PlayAnimation(playerid,"BD_FIRE","BD_Panic_03",4.1,0,1,1,1,0);
  return true;
}

CMD:dance(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /dance [1-12]");
  switch(params[0]) {
    case 1 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE1);
    case 2 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE2);
    case 3 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE3);
    case 4 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE4);
    case 5 : PlayAnimation(playerid,"DANCING","bd_clap",4.1,1,1,1,1,1);
    case 6 : PlayAnimation(playerid,"DANCING","bd_clap1",4.1,1,1,1,1,1);
    case 7 : PlayAnimation(playerid,"DANCING","DAN_Down_A",4.1,1,1,1,1,1);
    case 8 : PlayAnimation(playerid,"DANCING","DAN_Left_A",4.1,1,1,1,1,1);
    case 9 : PlayAnimation(playerid,"DANCING","DAN_Loop_A",4.1,1,1,1,1,1);
    case 10 : PlayAnimation(playerid,"DANCING","DAN_Right_A",4.1,1,1,1,1,1);
    case 11 : PlayAnimation(playerid,"DANCING","DAN_Up_A",4.1,1,1,1,1,1);
    case 12 : PlayAnimation(playerid,"DANCING","dnce_M_a",4.1,1,1,1,1,1);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /dance [1-12]");
  }
  return true;
}

CMD:repcar(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /repcar [1-2]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"CAR","Fixn_Car_Loop",3.0,0,1,1,1,0);
    case 2 : PlayAnimation(playerid,"CAR","Fixn_Car_Out",3.0,0,1,1,1,0);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /repcar [1-2]");
  }
  return true;
}


CMD:hnds(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /hnds [1-7]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"LOWRIDER","prtial_gngtlkB",4.1,0,1,1,1,1);
    case 2 : PlayAnimation(playerid,"LOWRIDER","prtial_gngtlkC",4.1,0,1,1,1,1);
    case 3 : PlayAnimation(playerid,"LOWRIDER","prtial_gngtlkD",4.1,0,1,1,1,1);
    case 4 : PlayAnimation(playerid,"LOWRIDER","prtial_gngtlkE",4.1,0,1,1,1,1);
    case 5 : PlayAnimation(playerid,"LOWRIDER","prtial_gngtlkF",4.1,0,1,1,1,1);
    case 6 : PlayAnimation(playerid,"LOWRIDER","prtial_gngtlkG",4.1,0,1,1,1,1);
    case 7 : PlayAnimation(playerid,"LOWRIDER","prtial_gngtlkH",4.1,0,1,1,1,1);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /hnds [1-7]");
  }
  return true;
}

CMD:strip(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /strip [1-14]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"STRIP", "strip_A", 4.1, 1, 1, 1, 1, 1 );
    case 2 : PlayAnimation(playerid,"STRIP", "strip_B", 4.1, 1, 1, 1, 1, 1 );
    case 3 : PlayAnimation(playerid,"STRIP", "strip_C", 4.1, 1, 1, 1, 1, 1 );
    case 4 : PlayAnimation(playerid,"STRIP", "strip_D", 4.1, 1, 1, 1, 1, 1 );
    case 5 : PlayAnimation(playerid,"STRIP", "strip_E", 4.1, 1, 1, 1, 1, 1 );
    case 6 : PlayAnimation(playerid,"STRIP", "strip_F", 4.1, 1, 1, 1, 1, 1 );
    case 7 : PlayAnimation(playerid,"STRIP", "strip_G", 4.1, 1, 1, 1, 1, 1 );
       case 8: ApplyAnimation(playerid,"STRIP","STR_A2B",4.1,1,1,1,1,1);
        case 9: ApplyAnimation(playerid,"STRIP","STR_B2C",4.1,1,1,1,1,1);
        case 10: ApplyAnimation(playerid,"STRIP","STR_C1",4.1,1,1,1,1,1);
        case 11: ApplyAnimation(playerid,"STRIP","STR_C2",4.1,1,1,1,1,1);
        case 12: ApplyAnimation(playerid,"STRIP","STR_Loop_A",4.1,1,1,1,1,1);
        case 13: ApplyAnimation(playerid,"STRIP","STR_Loop_B",4.1,1,1,1,1,1);
        case 14: ApplyAnimation(playerid,"STRIP","STR_Loop_C",4.1,1,1,1,1,1);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /strip [1-14]");
  }
  return true;
}


CMD:deal(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /deal [1-3]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid, "DEALER", "DEALER_DEAL", 4.0, 0, 0, 0, 0, 0);
    case 2 : PlayAnimation(playerid, "DEALER","DEALER_IDLE", 3.0,0,1,1,1,0);
    case 3 : PlayAnimation(playerid,"GRAVEYARD","mrnM_loop",3.0,0,1,1,1,0);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /deal [1-3]");
  }
  return true;
}

CMD:asmoke(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /asmoke [1-6]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid, "SMOKING", "M_smklean_loop", 4.0, 1, 0, 0, 0, 0);
    case 2 : PlayAnimation(playerid, "SMOKING", "F_smklean_loop", 4.0, 1, 0, 0, 0, 0);
    case 3 : PlayAnimation(playerid, "SMOKING","M_smkstnd_loop", 4.0, 1, 0, 0, 0, 0);
    case 4 : PlayAnimation(playerid, "SMOKING","M_smk_out", 4.0, 0, 0, 0, 0, 0);
    case 5 : PlayAnimation(playerid, "SMOKING","M_smk_in",3.0,0,0,0,0,0);
    case 6 : PlayAnimation(playerid, "SMOKING","M_smk_tap",3.0,0,0,0,0,0);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /asmoke [1-6]");
  }
  return true;
}

CMD:rap(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /rap [1-9]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"RAPPING","RAP_A_Loop",4.0,1,0,0,0,0);
    case 2 : PlayAnimation(playerid,"RAPPING","RAP_C_Loop",4.0,1,0,0,0,0);
    case 3 : PlayAnimation(playerid,"GANGS","prtial_gngtlkD",4.0,1,0,0,1,1);
    case 4 : PlayAnimation(playerid,"GANGS","prtial_gngtlkH",4.0,1,0,0,1,1);
    case 5 : PlayAnimation(playerid,"GANGS","prtial_gngtlkF",4.0,1,0,0,1,1);
    case 6 : PlayAnimation(playerid,"GANGS","prtial_gngtlkG",4.0,1,0,0,1,1);
    case 7 : PlayAnimation(playerid,"PED","ATM",4.0,0,0,0,0,0);
    case 8 : PlayAnimation(playerid,"RAPPING","RAP_B_IN",3.0,0,1,1,1,0);
    case 9 : PlayAnimation(playerid,"GYMNASIUM","gym_tread_celebrate",4.1,0,1,1,1,0);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /rap [1-9]");
  }
  return true;
}

CMD:bat(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /bat [1-2]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"CRACK","Bbalbat_Idle_02",4.0, 1, 0, 0, 0, 0);
    case 2 : PlayAnimation(playerid,"CRACK","Bbalbat_Idle_01",4.0, 1, 0, 0, 0, 0);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /bat [1-2]");
  }
  return true;
}

CMD:basket(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /basket [1-6]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"BSKTBALL","BBALL_idleloop",4.0,1,0,0,0,0);
    case 2 : PlayAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
    case 3 : PlayAnimation(playerid,"BSKTBALL","BBALL_pickup",4.0,0,0,0,0,0);
    case 4 : PlayAnimation(playerid,"BSKTBALL","BBALL_run",4.1,1,1,1,1,1);
    case 5 : PlayAnimation(playerid,"BSKTBALL","BBALL_def_loop",4.0,1,0,0,0,0);
    case 6 : PlayAnimation(playerid,"BSKTBALL","BBALL_Dnk",4.0,0,0,0,0,0);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /basket [1-6]");
  }
  return true;
}

CMD:lean(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /lean [1-3]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"GANGS","leanIDLE",4.0,0,0,1,1,0);
    case 2 : PlayAnimation(playerid,"MISC","Plyrlean_loop",4.0,0,1,1,1,0);
    case 3 : PlayAnimation(playerid,"CAR_CHAT","car_talkm_loop",4.0,0,1,1,1,0);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /lean [1-3]");
  }
  return true;
}

CMD:lay(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /lay [1-5]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"BEACH", "bather", 4.0, 1, 0, 0, 0, 0);
    case 2 : PlayAnimation(playerid,"SUNBATHE","Lay_Bac_in",3.0,0,1,1,1,0);
    case 3 : PlayAnimation(playerid,"BEACH","ParkSit_W_loop",3.0,0,1,1,1,0);
    case 4 : PlayAnimation(playerid,"BEACH","SitnWait_loop_W",4.0, 1, 0, 0, 0, 0);
    case 5 : PlayAnimation(playerid,"SUNBATHE","SBATHE_F_LieB2Sit",3.0,0,1,1,1,0);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /lay [1-5]");
  }
  return true;
}

CMD:gsign(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /gsign [1-10]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"GHANDS","gsign1",4.1,0,1,1,1,1);
    case 2 : PlayAnimation(playerid,"GHANDS","gsign1LH",4.1,0,1,1,1,1);
    case 3 : PlayAnimation(playerid,"GHANDS","gsign2",4.1,0,1,1,1,1);
    case 4 : PlayAnimation(playerid,"GHANDS","gsign2LH",4.1,0,1,1,1,1);
    case 5 : PlayAnimation(playerid,"GHANDS","gsign3",4.1,0,1,1,1,1);
    case 6 : PlayAnimation(playerid,"GHANDS","gsign3LH",4.1,0,1,1,1,1);
    case 7 : PlayAnimation(playerid,"GHANDS","gsign4",4.1,0,1,1,1,1);
    case 8 : PlayAnimation(playerid,"GHANDS","gsign4LH",4.1,0,1,1,1,1);
    case 9 : PlayAnimation(playerid,"GHANDS","gsign5",4.1,0,1,1,1,1);
    case 10 : PlayAnimation(playerid,"GHANDS","gsign5LH",4.1,0,1,1,1,1);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /gsign [1-10]");
  }
  return true;
}

CMD:wave(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /wave [1-4]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid, "KISSING","gfwave2", 4.1,0,1,1,0,0);
    case 2 : PlayAnimation(playerid, "ON_LOOKERS","wave_loop", 4.1,1,1,1,0,0);
    case 3 : PlayAnimation(playerid,"CAMERA","camstnd_cmon",4.0,0,0,0,0,0);
    case 4 : PlayAnimation(playerid,"PED","endchat_01",4.1,0,1,1,0,0);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /wave [1-4]");
  }
  return true;
}

CMD:police(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /police [1-4]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"POLICE","CopTraf_Away",3.0,1,0,0,1,0);
    case 2 : PlayAnimation(playerid,"POLICE","CopTraf_Come",3.0,1,0,0,1,0);
    case 3 : PlayAnimation(playerid,"POLICE","CopTraf_Left",3.0,1,0,0,1,0);
    case 4 : PlayAnimation(playerid,"POLICE","CopTraf_Stop",3.0,1,0,0,1,0);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /police [1-4]");
  }
  return true;
}

CMD:crack(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /crack [1-7]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"CRACK","crckdeth2",3.0,1,1,1,1,0);
    case 2 : PlayAnimation(playerid,"CRACK","crckdeth4",3.0,0,1,1,1,0);
    case 3 : PlayAnimation(playerid,"CRACK","crckidle1",3.0,0,1,1,1,0);
    case 4 : PlayAnimation(playerid,"CRACK","crckidle2",3.0,0,1,1,1,0);
    case 5 : PlayAnimation(playerid,"CRACK","crckidle3",3.0,0,1,1,1,0);
    case 6 : PlayAnimation(playerid,"CRACK","crckdeth1",3.0,0,1,1,1,0);
    case 7 : PlayAnimation(playerid,"CRACK","crckdeth3",3.0,0,1,1,1,0);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /crack [1-7]");
  }
  return true;
}

CMD:car(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /car [1-11]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"LOWRIDER","lrgirl_bdbnce",4.1,0,1,1,1,0);
    case 2 : PlayAnimation(playerid,"LOWRIDER","lrgirl_hair",4.1,0,1,1,1,0);
    case 3 : PlayAnimation(playerid,"LOWRIDER","lrgirl_idle_to_l0",4.1,0,1,1,1,0);
    case 4 : PlayAnimation(playerid,"PED","Tap_hand",4.1,0,1,1,1,0);
    case 5 : PlayAnimation(playerid,"PED","Tap_handP",4.1,0,1,1,1,0);
    case 6 : PlayAnimation(playerid,"LOWRIDER","lrgirl_l12_to_l0",4.1,0,1,1,1,0);
    case 7 : PlayAnimation(playerid,"LOWRIDER","lrgirl_l2_to_l3",4.1,0,1,1,1,0);
    case 8 : PlayAnimation(playerid,"PED","CAR_LB",4.1,0,1,1,1,0);
    case 9 : PlayAnimation(playerid,"PED","CAR_sitp",4.1,0,1,1,1,0);
    case 10 : PlayAnimation(playerid,"PED","CAR_sitpLO",4.1,0,1,1,1,0);
    case 11 : PlayAnimation(playerid,"CAR_CHAT","carfone_loopA",4.1,1,1,1,1,0);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /car [1-11]");
  }
  return true;
}

CMD:wallow(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /wallow [1-2]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll",4.1,0,1,1,1,0);
    case 2 : PlayAnimation(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll_F",4.1,0,1,1,1,0);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /wallow [1-2]");
  }
  return true;
}

CMD:beckon(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /beckon [1-3]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"RYDER","RYD_Beckon_01",4.1,0,1,1,1,1);
    case 2 : PlayAnimation(playerid,"RYDER","RYD_Beckon_02",4.1,0,1,1,1,1);
    case 3 : PlayAnimation(playerid,"RYDER","RYD_Beckon_03",4.1,0,1,1,1,1);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /beckon [1-3]");
  }
  return true;
}

CMD:shotgun(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /shotgun [1-3]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"SHOTGUN","shotgun_crouchfire",4.1,0,1,1,1,1);
    case 2 : PlayAnimation(playerid,"SHOTGUN","shotgun_fire",4.1,0,1,1,1,1);
    case 3 : PlayAnimation(playerid,"SHOTGUN","shotgun_fire_poor",4.1,0,1,1,1,1);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /shotgun [1-3]");
  }
  return true;
}

CMD:colt(playerid, params[]) {
  
  if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_WHITE, "> Использование: /colt [1-3]");
  switch(params[0]) {
    case 1 : PlayAnimation(playerid,"COLT45","colt45_fire_2hands",4.1,0,1,1,1,1);
    case 2 : PlayAnimation(playerid,"COLT45","colt45_reload",4.1,0,1,1,1,1);
    case 3 : PlayAnimation(playerid,"COLT45","sawnoff_reload",4.1,0,1,1,1,1);
    default : SendClientMessage(playerid, COLOR_WHITE, "> Использование: /colt [1-3]");
  }
  return true;
}
