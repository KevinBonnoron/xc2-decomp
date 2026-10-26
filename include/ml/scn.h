#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_render_callback.h"
#include "types.h"

namespace ml {

class DebDraw;
class Scn;
class ScnDebug;
class ScnObj;
class ScnObjModel;
class ScnPoolObj;
class ScnRenderDrSys;
class WinView;

enum SCNCAM : int {};

class ScnObjCam {
public:
  struct RENDER_INFO {
    u8 _00[0x10];
    mm::Vec3 position;
  };

  static void renderDebug(DebDraw *debDraw);
  static void setCopydataCam(bool isCopydata);
  const char *getName() const;

  u8 _00[0x18];
  mm::mtl::FixStr<64> m_name;
  u8 _5c[0x78 - 0x5c];
  RENDER_INFO *renderInfo;
};

static_assert(offsetof(ScnObjCam, m_name) == 0x18, "");
static_assert(offsetof(ScnObjCam, renderInfo) == 0x78, "");

class ScnCamMan {
public:
  static void setCrossIdTarget(const WinView *view);
  void setView(WinView *view, int screen);
  void clrView(WinView *view, int screen);
  const ScnObjCam *getCam(const WinView *view) const;
  ScnObjCam *getCam(const WinView *view);

  u8 _00[0x08 - 0x00];
  Scn *unknown08; // Inferred role: scn; original member name unknown.
};

static_assert(offsetof(ScnCamMan, unknown08) == 0x08, "");

class Scn : public mm::mtl::PtrSingleton<Scn> {
public:
  struct DebDrawInfo {
    SCNPRIO_CB unknown00; // Inferred role: priority; original member name unknown.
    s32 unknown04;        // Inferred role: screen; original member name unknown.
  };

  void setPause(bool isPause);
  void setDebDraw(SCNCAM cam, SCNPRIO_CB priority);
  ScnObjModel *createMdl(const void *data, const char *name, int screenID);
  ScnObj *createLgt(const void *data, int screenID);
  ScnObj *createClip(const void *data, int screenID);
  ScnObj *createIBL(const void *data, int screenID);
  ScnObj *createEnvColi(const void *data, int screenID);
  void releaseItem(ScnObj *obj);
  void setDeleteRender();
  static u32 thRenderKillTerminate(void *argument, void *userData);
  void renderStop();
  void setFrameSpd(f32 speed);
  f32 getFrameSpd() const;
  void enableScnDebug(bool isEnable);
  void setView(WinView *view, int screen);
  void clrView(WinView *view, int screen);
  ScnObjCam *getCam(int index);
  ScnObjCam *getCam(const WinView *view);
  const ScnObjCam *getCam(const WinView *view) const;

  u8 _08[0x20 - 0x08];
  ScnPoolObj *unknown20;     // Inferred role: pool object; original member name unknown.
  ScnCamMan *unknown28;      // Inferred role: cam man; original member name unknown.
  ScnDebug *unknown30;       // Inferred role: scn debug; original member name unknown.
  ScnRenderDrSys *unknown38; // Inferred role: render dr sys; original member name unknown.
  u8 _40[0x64 - 0x40];
  mtl::ALLOC_HANDLE unknown64; // Inferred role: alloc handle; original member name unknown.
  u8 _68[0xac - 0x68];
  bool unknownac; // Inferred role: tex stm; original member name unknown.
  u8 _ad[0xdf8 - 0xad];
  bool unknowndf8; // Inferred role: pause; original member name unknown.
  bool unknowndf9; // Inferred role: render stop; original member name unknown.
  u8 _dfa[0xe00 - 0xdfa];
  DebDrawInfo unknowne00[2]; // Inferred role: deb draw infos; original member name unknown.
};

static_assert(offsetof(Scn, unknown20) == 0x20, "");
static_assert(offsetof(Scn, unknown38) == 0x38, "");
static_assert(offsetof(Scn, unknown64) == 0x64, "");
static_assert(offsetof(Scn, unknownac) == 0xac, "");
static_assert(offsetof(Scn, unknowndf8) == 0xdf8, "");
static_assert(offsetof(Scn, unknowne00) == 0xe00, "");

} // namespace ml
