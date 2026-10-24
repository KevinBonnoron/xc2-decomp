#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkDoorGob;

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

  ~GmkDoor() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x360 - 0x48];
};

static_assert(sizeof(GmkDoor::BdatInfo) == 0x48, "");
static_assert(sizeof(GmkDoor) == 0x360, "");

typedef TGmkList<GmkDoor, GmkDoor::BdatInfo, 0x524f4f44, 2, GmkDoorGob> GmkDoorList;

} // namespace gmk
