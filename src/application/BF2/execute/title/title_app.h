#pragma once
#include <stddef.h>

#include "apps/launcher_app.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace layer {
class LayerBase;
} // namespace layer

namespace ml {
class WorkObj;
} // namespace ml

namespace tl {

// Layout from the constructor inlined in ml::WorkUtil::createWork<tl::TitleApp> (1.0.0: 0x7100142828): the object is 0x780 bytes, apps::LauncherApp
// (0x760) comes first and PtrSingleton<TitleApp> follows at 0x760. The vtable is _ZTVN2tl8TitleAppE (0x7101176d28); wkStandbyLogin is its key function.
class TitleApp : public apps::LauncherApp, public mm::mtl::PtrSingleton<TitleApp> {
public:
  TitleApp(const char *name, ml::WorkObj *parent) : LauncherApp(name, parent, 10), unknown768(0), unknown770(nullptr), unknown778(nullptr) {}

  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  void now_loading(bool isEnd);
  static void execute();

  static const char *m_szTitle;

  u32 unknown768;               // Inferred role: language type, stored by the language specific execute and passed to FrameworkConfig by wkStandbyLogin; original member name unknown.
  layer::LayerBase *unknown770; // Inferred role: memory layer shown while loading; original member name unknown.
  u8 *unknown778;               // Inferred role: 4 KB buffer of the loading animation; original member name unknown.
};

static_assert(offsetof(TitleApp, unknown768) == 0x768, "");
static_assert(offsetof(TitleApp, unknown770) == 0x770, "");
static_assert(offsetof(TitleApp, unknown778) == 0x778, "");
static_assert(sizeof(TitleApp) == 0x780, "");

class TitleAppEN {
public:
  static void execute();

  static const char *m_szTitle;
};

class TitleAppCN {
public:
  static void execute();

  static const char *m_szTitle;
};

class TitleAppTW {
public:
  static void execute();

  static const char *m_szTitle;
};

} // namespace tl
