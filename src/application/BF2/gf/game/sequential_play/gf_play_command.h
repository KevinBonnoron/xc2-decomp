#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfPlayComPlayerDead {
public:
  static bool isDead();
};

class GfPlayComResetBlade {
public:
  static bool isPlaying(u32 partyId);
};

class GfPlayComQuestCompleteUI {
public:
  static int s_active;
};

class GfPlayComOpenMenu {
public:
  static int s_active;
};

class GfPlayComMenuChapter {
public:
  static int s_activate;
};

class GfPlayComMenuZone {
public:
  static int s_activate;
};

class GfPlayComMenuPrecious {
public:
  static int s_activate;
};

class GfPlayComHoodHomuraBattou : public mm::mtl::PtrSingleton<GfPlayComHoodHomuraBattou> {};

} // namespace gf
