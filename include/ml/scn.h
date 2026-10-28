#pragma once
#include <stddef.h>

#include "ml/work_event.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_render_callback.h"
#include "types.h"

namespace ml {

class CriticalSection;
class DebDraw;
class FileResTh;
class Scn;
class ScnDebug;
class ScnObj;
class ScnObjModel;
class ScnPoolObj;
class ScnRenderDrSys;
class WinView;

enum SCNCAM : int {};

enum SCNCB {
  SCNCB_UNKNOWN_0, // Inferred role: calls cbPreUpdate; original name unknown.
  SCNCB_UNKNOWN_1, // Inferred role: calls cbRenderAfter; original name unknown.
  SCNCB_UNKNOWN_2, // Inferred role: calls cbManipuPickOn; original name unknown.
  SCNCB_UNKNOWN_3, // Inferred role: calls cbManipuPickOff; original name unknown.
  SCNCB_UNKNOWN_4, // Inferred role: calls cbManipuPickMove; original name unknown.
};

class ScnObjCam {
public:
  struct RENDER_INFO {
    mm::Vec3 m_pos;
    mm::Vec3 position;
    u8 _20[0x70 - 0x20];
    mm::Mat44 unknown70; // Inferred role: world matrix; original member name unknown.
    u8 _b0[0xf0 - 0xb0];
    mm::Vec3 unknownf0; // Inferred role: rotation; original member name unknown.
    u8 _100[0x140 - 0x100];
    mm::Vec3 m_targetPos;
    f32 unknown150[4]; // Inferred role: frustum edges; original member name unknown.
    u8 _160[0x1a0 - 0x160];
    mm::Mat44 unknown1a0; // Inferred role: projection matrix; original member name unknown.
    u8 _1e0[0x1e8 - 0x1e0];
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
  static ScnObjCam *create(Scn *scn, int screen);
  void updateViewMatrix(bool isUpdate);
  void setRot(const mm::Vec3 &rot);
  void updateFovNearFar();
  void setFovDefault();
  void setPos(const mm::Vec3 &pos);
  void setTargetPos(const mm::Vec3 &pos);
  void addPosTarget(const mm::Vec3 &pos);
  void addTrack(const mm::Vec3 &pos);
  void addRotAtCam(const mm::Vec3 &rot);
  void setDist(const f32 &dist);
  void apply();

  u8 _00[0x08];
  Scn *unknown08; // Inferred role: scn; original member name unknown.
  u8 _10[0x18 - 0x10];
  mm::mtl::FixStr<64> m_name;
  u8 _5c[0x78 - 0x5c];
  RENDER_INFO *renderInfo;
  RENDER_INFO *unknown80; // Inferred role: back render info; original member name unknown.
};

static_assert(sizeof(ScnObjCam::RENDER_INFO) == 0x380, "");
static_assert(offsetof(ScnObjCam, unknown08) == 0x08, "");
static_assert(offsetof(ScnObjCam, m_name) == 0x18, "");
static_assert(offsetof(ScnObjCam, renderInfo) == 0x78, "");
static_assert(offsetof(ScnObjCam, unknown80) == 0x80, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown70) == 0x70, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknownf0) == 0xf0, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown1a0) == 0x1a0, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, m_targetPos) == 0x140, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown150) == 0x150, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown1e8) == 0x1e8, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown1f4) == 0x1f4, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, m_targetDist) == 0x1fc, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown200) == 0x200, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown2c0) == 0x2c0, "");

class ScnCamMan {
public:
  ScnCamMan(Scn *scn);
  virtual ~ScnCamMan();
  static void setCrossIdTarget(const WinView *view);
  void setView(WinView *view, int screen);
  void clrView(WinView *view, int screen);
  const ScnObjCam *getCam(const WinView *view) const;
  ScnObjCam *getCam(const WinView *view);
  WinView *getView(s16 screen);
  const WinView *getView(s16 screen) const;

  Scn *unknown08;                          // Inferred role: scn; original member name unknown.
  mm::mtl::FixedVector<u32, 10> unknown10; // Inferred role: view work ids per screen; original member name unknown.
  s32 unknown40;                           // Inferred role: current screen; original member name unknown.
};

static_assert(offsetof(ScnCamMan, unknown08) == 0x08, "");
static_assert(offsetof(ScnCamMan, unknown10) == 0x10, "");
static_assert(offsetof(ScnCamMan, unknown40) == 0x40, "");

class Scn : public IWorkEvent, public mm::mtl::PtrSingleton<Scn> {
public:
  struct DebDrawInfo {
    SCNPRIO_CB unknown00; // Inferred role: priority; original member name unknown.
    s32 unknown04;        // Inferred role: screen; original member name unknown.
  };

  // Inferred type: render callback entry; the original type name is unknown.
  struct unknown001 {
    unknown001(IScnRender *render, SCNPRIO_CB priority, bool flag1, bool flag2) : unknown00(render), unknown08(priority), unknown0c(flag2), unknown0d(flag1), unknown0e(false) {}

    IScnRender *unknown00; // Inferred role: callback; original member name unknown.
    SCNPRIO_CB unknown08;  // Inferred role: priority; original member name unknown.
    bool unknown0c;        // Inferred role: flag; original member name unknown.
    bool unknown0d;        // Inferred role: flag; original member name unknown.
    bool unknown0e;        // Inferred role: removed; original member name unknown.
  };

  void setPause(bool isPause);
  void term();
  void callbackToListener(SCNCB type);
  static u32 thUpAfter(void *argument, void *userData);
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
  void addRenderCB(IScnRender *render, SCNPRIO_CB priority, bool flag1, bool flag2);
  void addEntryRes(FileResTh *res);
  FileResTh *allocEntryRes(const char *path);
  void removeEntryRes(FileResTh *res);
  const WinView *getView(int index) const;
  ScnObjCam *getCam(const WinView *view);
  const ScnObjCam *getCam(const WinView *view) const;

  u8 _10[0x20 - 0x10];
  ScnPoolObj *unknown20;     // Inferred role: pool object; original member name unknown.
  ScnCamMan *unknown28;      // Inferred role: cam man; original member name unknown.
  ScnDebug *unknown30;       // Inferred role: scn debug; original member name unknown.
  ScnRenderDrSys *unknown38; // Inferred role: render dr sys; original member name unknown.
  u8 _40[0x64 - 0x40];
  mtl::ALLOC_HANDLE unknown64; // Inferred role: alloc handle; original member name unknown.
  u8 _68[0xac - 0x68];
  bool unknownac; // Inferred role: tex stm; original member name unknown.
  u8 _ad[0xb4 - 0xad];
  s32 unknownb4;            // Inferred role: cpu group handle; original member name unknown.
  unknown001 unknownb8[64]; // Inferred role: render callbacks; original member name unknown.
  s32 unknown4b8;           // Inferred role: render callback count; original member name unknown.
  u8 _4bc[0x4c0 - 0x4bc];
  mm::mtl::FixedQueue<unknown001, 64> unknown4c0; // Inferred role: render callbacks to add; original member name unknown.
  u8 _8d0[0xce0 - 0x8d0];
  CriticalSection *unknownce0;                      // Inferred role: scn lock; original member name unknown.
  CriticalSection *unknownce8;                      // Inferred role: entry res critical section; original member name unknown.
  mm::mtl::FixedVector<FileResTh *, 32> unknowncf0; // Inferred role: entry res; original member name unknown.
  bool unknowndf8;                                  // Inferred role: pause; original member name unknown.
  bool unknowndf9;                                  // Inferred role: render stop; original member name unknown.
  u8 _dfa[0xe00 - 0xdfa];
  DebDrawInfo unknowne00[2]; // Inferred role: deb draw infos; original member name unknown.
};

static_assert(offsetof(Scn, unknown20) == 0x20, "");
static_assert(offsetof(Scn, unknown38) == 0x38, "");
static_assert(offsetof(Scn, unknown64) == 0x64, "");
static_assert(offsetof(Scn, unknownac) == 0xac, "");
static_assert(offsetof(Scn, unknownb4) == 0xb4, "");
static_assert(offsetof(Scn, unknownb8) == 0xb8, "");
static_assert(offsetof(Scn, unknown4b8) == 0x4b8, "");
static_assert(offsetof(Scn, unknown4c0) == 0x4c0, "");
static_assert(offsetof(Scn, unknownce0) == 0xce0, "");
static_assert(offsetof(Scn, unknownce8) == 0xce8, "");
static_assert(offsetof(Scn, unknowncf0) == 0xcf0, "");
static_assert(offsetof(Scn, unknowndf8) == 0xdf8, "");
static_assert(offsetof(Scn, unknowne00) == 0xe00, "");

} // namespace ml
