#if defined _hlp_memset_included
	#endinput
#endif

#define _hlp_memset_included

#pragma warning disable 203

memset(array[], value, size = sizeof(array)) {
  static
      fill_inst_offset;
  if (fill_inst_offset == 0) {
      #emit lctrl 6
      #emit move.alt                  // 4
      #emit lctrl 0                   // 8
      #emit add                       // 4
      #emit move.alt                  // 4
      #emit lctrl 1                   // 8
      #emit sub.alt                   // 4
      #emit add.c 92                  // 8
      #emit stor.pri fill_inst_offset // 8
  } {}                                // 
  #emit load.s.pri size               // 8
  #emit shl.c.pri 2                   // 8
  #emit sref.pri fill_inst_offset     // 8
  #emit load.s.alt 12                 // 8
  #emit load.s.pri 16                 // 8
  #emit fill 1                        // 4
  #emit zero.pri
  #emit retn
}
