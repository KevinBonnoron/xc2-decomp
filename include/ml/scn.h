#pragma once
#include <stddef.h>

#include "mm_math/mm_plane.h"
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
    mm::Vec3 m_pos;
    mm::Vec3 position;
    u8 _20[0xf0 - 0x20];
    mm::Vec3 unknownf0; // Inferred role: rotation; original member name unknown.
    u8 _100[0x140 - 0x100];
    mm::Vec3 m_targetPos;
    f32 unknown150[4]; // Inferred role: frustum edges; original member name unknown.
    u8 _160[0x1e8 - 0x160];
    f32 unknown1e8; // Inferred role: fov in degrees; original member name unknown.
    f32 unknown1ec; // Inferred role: inverse tangent of half fov; original member name unknown.
    f32 unknown1f0; // Inferred role: aspect ratio; original member name unknown.
    f32 unknown1f4; // Inferred role: near clip; original member name unknown.
    u8 _1f8[0x1fc - 0x1f8];
    f32 m_targetDist;
    mm::Plane unknown200[6]; // Inferred role: local planes; original member name unknown.
    mm::Plane unknown2c0[6]; // Inferred role: global planes; original member name unknown.
  };

  static void renderDebug(DebDraw *debDraw);
  static void setCopydataCam(bool isCopydata);
  const char *getName() const;
  const mm::Plane *getPlaneLcl(u32 index, bool isBack) const;
  const mm::Plane *getPlaneGbl(u32 index, bool isBack) const;
  void updateViewMatrix(bool isUpdate);
  void setRot(const mm::Vec3 &rot);
  void updateFovNearFar();
  void setFovDefault();
  void setPos(const mm::Vec3 &pos);
  void setTargetPos(const mm::Vec3 &pos);
  void addPosTarget(const mm::Vec3 &pos);
  void addTrack(const mm::Vec3 &pos);
  void addRotAtCam(const mm::Vec3 &rot);

  u8 _00[0x18];
  mm::mtl::FixStr<64> m_name;
  u8 _5c[0x78 - 0x5c];
  RENDER_INFO *renderInfo;
  RENDER_INFO *unknown80; // Inferred role: back render info; original member name unknown.
};

static_assert(sizeof(ScnObjCam::RENDER_INFO) == 0x380, "");
static_assert(offsetof(ScnObjCam, m_name) == 0x18, "");
static_assert(offsetof(ScnObjCam, renderInfo) == 0x78, "");
static_assert(offsetof(ScnObjCam, unknown80) == 0x80, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknownf0) == 0xf0, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, m_targetPos) == 0x140, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown150) == 0x150, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown1e8) == 0x1e8, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown1f4) == 0x1f4, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, m_targetDist) == 0x1fc, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown200) == 0x200, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown2c0) == 0x2c0, "");

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
  WinView *getView(int index);
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
