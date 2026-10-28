#pragma once
#include <stddef.h>

#include "framework/coli/coli_object.h"
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_camera.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_ctrl_vol_se.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_phantom.h"
#include "mm_mtl/vector.h"
#include "types.h"

struct CBdatWrapper;

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gmk {

class GmkDoorGob;

class GmkDoor : public AGmkBase, public IGmkPhantomEventListener, public fw::ColiUserData {
public:
  struct BdatInfo {
    bool isGfObjMustExist() const;
    bool isPhantomMustExist() const;
    bool isLoadSaveData() const;
    bool isPopCondMatched() const;
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);

    u16 unknown00;           // Inferred role: condition; original member name unknown.
    u8 unknown02;            // Inferred role: response type; original member name unknown.
    u8 unknown03;            // Inferred role: response character; original member name unknown.
    u16 unknown04;           // Inferred role: name radius; original member name unknown.
    u16 unknown06;           // Inferred role: lod model; original member name unknown.
    u16 unknown08;           // Inferred role: miss msg id; original member name unknown.
    bool unknown0a;          // Inferred role: open lod anime; original member name unknown.
    bool unknown0b;          // Inferred role: open se map pack; original member name unknown.
    u16 unknown0c;           // Inferred role: open se; original member name unknown.
    u8 unknown0e;            // Inferred role: open se size; original member name unknown.
    const char *unknown10;   // Inferred role: open camera gimmick id; original member name unknown.
    u8 unknown18;            // Inferred role: open camera gimmick attribute; original member name unknown.
    bool unknown19;          // Inferred role: close lod anime; original member name unknown.
    bool unknown1a;          // Inferred role: close se map pack; original member name unknown.
    u16 unknown1c;           // Inferred role: close se; original member name unknown.
    u8 unknown1e;            // Inferred role: close se size; original member name unknown.
    const char *unknown20;   // Inferred role: close camera gimmick id; original member name unknown.
    u8 unknown28;            // Inferred role: close camera gimmick attribute; original member name unknown.
    f32 unknown2c;           // Inferred role: door next wait; original member name unknown.
    const char *unknown30;   // Inferred role: special close camera gimmick id; original member name unknown.
    u8 unknown38;            // Inferred role: special close camera gimmick attribute; original member name unknown.
    bool unknown39;          // Inferred role: gmk camera pos; original member name unknown.
    BootedGmkCond unknown3a; // Inferred role: booted gmk; original member name unknown.
    BootedGmkCond unknown3e; // Inferred role: op booted gmk; original member name unknown.
    BootedGmkCond unknown42; // Inferred role: special pop booted gmk; original member name unknown.
  };

  enum Progress {
    PROGRESS_UNKNOWN_0 = 0, // Inferred role: before boot (seqDoor_BeforeBoot); original name unknown.
    PROGRESS_UNKNOWN_1 = 1, // Inferred role: booted (seqDoor_Booted); original name unknown.
    PROGRESS_UNKNOWN_2 = 2, // Inferred role: shutdowned (seqDoor_Shutdowned); original name unknown.
    PROGRESS_UNKNOWN_3 = 3, // Inferred role: special booted (seqDoor_SpBooted); original name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_DOOR;
  static mm::mtl::RTTI m_rtti;

  GmkDoor() : unknown60(nullptr) {}
  ~GmkDoor() override;
  GmkType getGmkType() const override;
  int getGameFlagId() const;
  const mm::mtl::RTTI *getRTTI() const override;
  void onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo &info) override;
  void onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo &info) override;
  u32 getProgress() const;
  void setProgress(Progress progress);
  void pollBootGmk();
  void bootGmk(bool isImmediate, bool isCamera);
  void spBootGmk(bool isImmediate, bool isCamera);
  void shutdownGmk(bool isImmediate, bool isCamera);
  void openDoor(bool isImmediate);
  void closeDoor(bool isImmediate);
  void seqDoor_BeforeBoot(f32 deltaTime);
  void createGfObjHandle();
  void createGmkPhantom();
  bool isDoorOpened() const;
  bool isLocked() const;
  bool isSpLocked() const;
  void isSeLoop(bool isMapPack, u16 seId) const;
  void seqDoor_Shutdowned(f32 deltaTime);
  void seqDoor_Booted(f32 deltaTime);
  void seqDoor_SpBooted(f32 deltaTime);
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;
  bool createGmkCamera(const char *name, u8 attribute, bool param3);
  void disposeGmkCamera();
  void disposeGmkPhantom();
  void disposeGfObjHandle();
  bool isGmkFinished() const;

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  GmkCamera unknown60; // Inferred role: gimmick camera; original member name unknown.
  u8 _1c0[0x238 - 0x1c0];
  GmkPhantom *unknown238; // Inferred role: phantom; original member name unknown.
  u8 _240[0x243 - 0x240];
  bool unknown243; // Inferred role: player is inside the phantom; original member name unknown.
  u8 _244[0x2a0 - 0x244];
  GmkPhantom *unknown2a0; // Inferred role: phantom; original member name unknown.
  u8 _2a8[0x2b0 - 0x2a8];
  bool unknown2b0; // Inferred role: player entered the phantom this frame; original member name unknown.
  bool unknown2b1; // Inferred role: unknown2b0 of the previous frame; original member name unknown.
  u8 _2b2[0x2b8 - 0x2b2];
  gf::GF_OBJ_HANDLE *unknown2b8; // Inferred role: door game object handle; original member name unknown.
  f32 unknown2C0;                // Role and original member name unknown.
  u8 _2c4[0x2c8 - 0x2c4];
  void (GmkDoor::*unknown2c8)(f32); // Inferred role: seq; original member name unknown.
  u8 _2d8[0x2e0 - 0x2d8];
  GmkCtrlVolSe unknown2e0; // Inferred role: se; original member name unknown.
};

static_assert(sizeof(GmkDoor::BdatInfo) == 0x48, "");
static_assert(offsetof(GmkDoor, unknown60) == 0x60, "");
static_assert(offsetof(GmkDoor, unknown238) == 0x238, "");
static_assert(offsetof(GmkDoor, unknown243) == 0x243, "");
static_assert(offsetof(GmkDoor, unknown2a0) == 0x2a0, "");
static_assert(offsetof(GmkDoor, unknown2b0) == 0x2b0, "");
static_assert(offsetof(GmkDoor, unknown2b8) == 0x2b8, "");
static_assert(offsetof(GmkDoor, unknown2C0) == 0x2c0, "");
static_assert(offsetof(GmkDoor, unknown2c8) == 0x2c8, "");
static_assert(offsetof(GmkDoor, unknown2e0) == 0x2e0, "");
static_assert(sizeof(GmkDoor) == 0x360, "");

typedef TGmkList<GmkDoor, GmkDoor::BdatInfo, 0x524f4f44, 2, GmkDoorGob> GmkDoorList;

class GmkDoorPhantomManager : public gf::IGfObjListener {
public:
  GmkDoorPhantomManager();
  virtual ~GmkDoorPhantomManager();
  void create();
  void dispose();
  void addTargetInfo(gf::GF_OBJ_HANDLE *handle);
  void removeTargetInfo(gf::GF_OBJ_HANDLE *handle);
  void listenerGfObj(OBJEVT event, gf::GF_OBJ_HANDLE *handle, u32 objectType) override;
  void update(f32 deltaTime);

  mm::mtl::Vector<GmkDoorPhantomTargetInfo> unknown08; // Inferred role: phantom targets; original member name unknown.
};

static_assert(offsetof(GmkDoorPhantomManager, unknown08) == 0x08, "");
static_assert(sizeof(GmkDoorPhantomManager) == 0x30, "");

} // namespace gmk
