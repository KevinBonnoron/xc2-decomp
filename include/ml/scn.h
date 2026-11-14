#pragma once
#include <stddef.h>

#include "ml/attr_transform.h"
#include "ml/scn_obj.h"
#include "ml/threadval.h"
#include "ml/work_event.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_render_callback.h"
#include "types.h"

namespace mm {
class Sphere;
} // namespace mm

namespace ml {

class CriticalSection;
class FileResTh;
class Scn;
class ScnDebug;
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

class ScnObjCam : public ScnObj {
public:
  struct RENDER_INFO {
    AttrTransform unknown00; // Inferred role: transform; original member name unknown.
    mm::Vec3 m_targetPos;
    f32 unknown150[4];    // Inferred role: frustum edges; original member name unknown.
    mm::Mat44 unknown160; // Inferred role: matrix converting view local to device coordinates; original member name unknown.
    mm::Mat44 unknown1a0; // Inferred role: projection matrix; original member name unknown.
    // Inferred role: viewport size; original member name unknown. A mm::Pnt<int>: ScnObjCam::setSize (0x7100742938) compares and copies it
    // through references to the two ints (two 32-bit loads; as two s32 members of this 16-aligned struct clang 3.9 merges them into one
    // 64-bit load).
    mm::Pnt<int> unknown1e0;
    f32 unknown1e8; // Inferred role: fov in degrees; original member name unknown.
    f32 unknown1ec; // Inferred role: inverse tangent of half fov; original member name unknown.
    f32 unknown1f0; // Inferred role: aspect ratio; original member name unknown.
    f32 unknown1f4; // Inferred role: near clip; original member name unknown.
    f32 unknown1f8; // Inferred role: far clip; original member name unknown.
    f32 m_targetDist;
    mm::Plane unknown200[6]; // Inferred role: local planes; original member name unknown.
    mm::Plane unknown2c0[6]; // Inferred role: global planes; original member name unknown.
  };

  // Inferred type: object owned by the camera; the original type name is unknown.
  class unknown001 {
  public:
    virtual ~unknown001() {}
    virtual void unknown10() = 0; // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
    virtual void unknown18() = 0; // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
    virtual void unknown20() = 0; // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
    virtual void unknown28() = 0; // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
    virtual void unknown30() = 0; // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
    virtual void unknown38() = 0; // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
    virtual void unknown40() = 0; // Inferred role: called by update; original name unknown.
  };

  ScnObjCam(Scn *scn, const char *name);
  ~ScnObjCam() override;
  void update() override;
  void renderDebug(DebDraw *debDraw) override;
  void apply() override;
  const char *getName() const override;
  static void setCopydataCam(bool isCopydata);
  const mm::Plane *getPlaneLcl(u32 index, bool isBack) const;
  const mm::Plane *getPlaneGbl(u32 index, bool isBack) const;
  static ScnObjCam *create(Scn *scn, int screen);
  static void infoInit(RENDER_INFO *info);
  void updateViewMatrix(bool isUpdate);
  void setDefault();
  void setInfo(int info);
  void setSize(const mm::Pnt<int> &size);
  void setLookAt(const mm::Vec3 &position, const mm::Vec3 &target, f32 roll);
  void setRot(const mm::Vec3 &rot);
  void updateFovNearFar();
  void setFovDefault();
  void setPos(const mm::Vec3 &pos);
  void setTargetPos(const mm::Vec3 &pos);
  void calcFrameFit(const mm::Sphere &sphere);
  void addPosTarget(const mm::Vec3 &pos);
  void addTrack(const mm::Vec3 &pos);
  void addRotAtCam(const mm::Vec3 &rot);
  void setDist(const f32 &dist);

  s32 m_info; // Inferred role: screen; original member name unknown.
  mm::mtl::FixStr<64> m_name;
  bool unknown5c;                   // Inferred role: view matrix updated; original member name unknown.
  unknown001 *unknown60;            // Inferred role: camera controller; original member name unknown.
  threadval<RENDER_INFO> unknown70; // Inferred role: render info; original member name unknown.
};

static_assert(offsetof(ScnObjCam, m_info) == 0x14, "");
static_assert(offsetof(ScnObjCam, m_name) == 0x18, "");
static_assert(offsetof(ScnObjCam, unknown5c) == 0x5c, "");
static_assert(offsetof(ScnObjCam, unknown60) == 0x60, "");
static_assert(offsetof(ScnObjCam, unknown70) == 0x70, "");
static_assert(sizeof(ScnObjCam::RENDER_INFO) == 0x380, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, m_targetPos) == 0x140, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown150) == 0x150, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown160) == 0x160, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown1a0) == 0x1a0, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown1e0) == 0x1e0, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown1e8) == 0x1e8, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown1f0) == 0x1f0, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown1f4) == 0x1f4, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown1f8) == 0x1f8, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, m_targetDist) == 0x1fc, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown200) == 0x200, "");
static_assert(offsetof(ScnObjCam::RENDER_INFO, unknown2c0) == 0x2c0, "");

// Layout from the ml::Scn::create defaults, which the Scn constructor copies; the members are unknown.
class ScnSetup {
public:
  ScnSetup() : unknown00(0), unknown08(0x300000), unknown0c(0), unknown34(0x14000000), unknown38(0x80), unknown3c(0x1000), unknown40(0), unknown44(true) {}

  u64 unknown00;                 // Inferred role: copied to the scn; original member name unknown.
  s32 unknown08;                 // Inferred role: size of the scn memory; original member name unknown.
  u32 unknown0c;                 // Inferred role: memory handle, 0 for the product memory; original member name unknown.
  mm::mtl::FixStr<32> unknown10; // Inferred role: scn name; original member name unknown.
  s32 unknown34;                 // Inferred role: copied to the scn; original member name unknown.
  s32 unknown38;                 // Inferred role: copied to the scn; original member name unknown.
  s32 unknown3c;                 // Inferred role: copied to the scn; original member name unknown.
  s32 unknown40;                 // Inferred role: copied to the scn; original member name unknown.
  bool unknown44;                // Inferred role: tex stm; original member name unknown.
};

static_assert(offsetof(ScnSetup, unknown10) == 0x10, "");
static_assert(offsetof(ScnSetup, unknown34) == 0x34, "");
static_assert(offsetof(ScnSetup, unknown44) == 0x44, "");
static_assert(sizeof(ScnSetup) == 0x48, "");

// The vtable of the game holds the IWorkEvent slots after the destructor (slots 0x20 to 0x48).
class ScnCamMan : public IWorkEvent {
public:
  ScnCamMan(Scn *scn);
  ~ScnCamMan() override;
  static void setCrossIdTarget(const WinView *view);
  void update();
  void apply();
  bool setCurrentCam();
  void setView(WinView *view, int screen);
  void clrView(WinView *view, int screen);
  const ScnObjCam *getCam(const WinView *view) const;
  ScnObjCam *getCam(const WinView *view);
  ScnObjCam *getCam(int screen);
  const ScnObjCam *getCam(int screen) const;
  WinView *getView(s16 screen);
  const WinView *getView(s16 screen) const;

  Scn *unknown08;                          // Inferred role: scn; original member name unknown.
  mm::mtl::FixedVector<u32, 10> unknown10; // Inferred role: view work ids per screen; original member name unknown.
  s32 unknown40;                           // Inferred role: current screen; original member name unknown.
};

static_assert(offsetof(ScnCamMan, unknown08) == 0x08, "");
static_assert(offsetof(ScnCamMan, unknown10) == 0x10, "");
static_assert(offsetof(ScnCamMan, unknown40) == 0x40, "");

class Scn : public IWorkEvent, public mm::mtl::ReferenceObject, public mm::mtl::PtrSingleton<Scn> {
public:
  // Inferred role: deb draw info; original type name unknown.
  struct unknown004 {
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

  Scn(const ScnSetup *setup);
  static Scn *create(const ScnSetup *setup);
  void init();
  void move();
  void draw();
  void tail();
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
  const ScnObjCam *getCam(int index) const;
  WinView *getView(int index);
  void addRenderCB(IScnRender *render, SCNPRIO_CB priority, bool flag1, bool flag2);
  void addEntryRes(FileResTh *res);
  FileResTh *allocEntryRes(const char *path);
  void removeEntryRes(FileResTh *res);
  const WinView *getView(int index) const;
  ScnObjCam *getCam(const WinView *view);
  const ScnObjCam *getCam(const WinView *view) const;

  ScnPoolObj *unknown20;     // Inferred role: pool object; original member name unknown.
  ScnCamMan *unknown28;      // Inferred role: cam man; original member name unknown.
  ScnDebug *unknown30;       // Inferred role: scn debug; original member name unknown.
  ScnRenderDrSys *unknown38; // Inferred role: render dr sys; original member name unknown.
  u8 _40[0x64 - 0x40];
  mtl::ALLOC_HANDLE unknown64; // Inferred role: alloc handle; original member name unknown.
  u8 _68[0xac - 0x68];
  bool unknownac; // Inferred role: tex stm; original member name unknown.
  u8 _ad[0xb0 - 0xad];
  bool unknownb0; // Inferred role: update done, reset by tail; original member name unknown.
  u8 _b1[0xb4 - 0xb1];
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
  unknown004 unknowne00[10]; // Inferred role: deb draw infos, one per camera; original member name unknown.
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
