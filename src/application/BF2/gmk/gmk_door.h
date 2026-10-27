#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_camera.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
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
class GmkDoorPhantomTargetInfo;

class GmkDoor : public AGmkBase {
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

  static const GmkType GMK_TYPE = GMK_TYPE_DOOR;
  static mm::mtl::RTTI m_rtti;

  GmkDoor() : unknown60(nullptr) {}
  ~GmkDoor() override;
  GmkType getGmkType() const override;
  int getGameFlagId() const;
  const mm::mtl::RTTI *getRTTI() const;
  u32 getProgress() const;
  bool isDoorOpened() const;
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
  void disposeGfObjHandle();
  bool isGmkFinished() const;

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  u8 _48[0x60 - 0x48];
  GmkCamera unknown60; // Inferred role: gimmick camera; original member name unknown.
  u8 _1c0[0x2b8 - 0x1c0];
  gf::GF_OBJ_HANDLE *unknown2b8; // Inferred role: door game object handle; original member name unknown.
  f32 unknown2C0;                // Role and original member name unknown.
  u8 _2c4[0x360 - 0x2c4];
};

static_assert(sizeof(GmkDoor::BdatInfo) == 0x48, "");
static_assert(offsetof(GmkDoor, unknown60) == 0x60, "");
static_assert(offsetof(GmkDoor, unknown2b8) == 0x2b8, "");
static_assert(offsetof(GmkDoor, unknown2C0) == 0x2c0, "");
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
