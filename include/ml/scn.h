#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_render_callback.h"
#include "types.h"

namespace ml {

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

  u8 _00[0x78];
  RENDER_INFO *renderInfo;
};

class ScnCamMan {
public:
  void setView(WinView *view, int screen);
  void clrView(WinView *view, int screen);
  const ScnObjCam *getCam(const WinView *view) const;
  ScnObjCam *getCam(const WinView *view);

  u8 _00[0x08 - 0x00];
  Scn *m_scn;
};

static_assert(offsetof(ScnCamMan, m_scn) == 0x08, "");

class Scn : public mm::mtl::PtrSingleton<Scn> {
public:
  struct DebDrawInfo {
    SCNPRIO_CB priority;
    s32 screen;
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
  ScnPoolObj *poolObj;
  ScnCamMan *m_camMan;
  ScnDebug *m_scnDebug;
  ScnRenderDrSys *renderDrSys;
  u8 _40[0x64 - 0x40];
  mtl::ALLOC_HANDLE allocHandle;
  u8 _68[0xac - 0x68];
  bool m_isTexStm;
  u8 _ad[0xdf8 - 0xad];
  bool m_isPause;
  bool m_isRenderStop;
  u8 _dfa[0xe00 - 0xdfa];
  DebDrawInfo m_debDrawInfos[2];
};

static_assert(offsetof(Scn, poolObj) == 0x20, "");
static_assert(offsetof(Scn, renderDrSys) == 0x38, "");
static_assert(offsetof(Scn, allocHandle) == 0x64, "");
static_assert(offsetof(Scn, m_isTexStm) == 0xac, "");
static_assert(offsetof(Scn, m_isPause) == 0xdf8, "");
static_assert(offsetof(Scn, m_debDrawInfos) == 0xe00, "");

} // namespace ml
