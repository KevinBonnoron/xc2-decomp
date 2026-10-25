#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_phantom.h"
#include "types.h"

struct CBdatWrapper;
namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class GmkElevatorGobCustom;
class GmkElevatorLocatorGob;

class GmkElevator : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);

    u16 unknown00;  // Inferred role: condition; original member name unknown.
    u16 unknown02;  // Inferred role: call name radius; original member name unknown.
    u16 unknown04;  // Inferred role: lift name radius; original member name unknown.
    u16 unknown06;  // Inferred role: lift lod; original member name unknown.
    u16 unknown08;  // Inferred role: shutter a lod; original member name unknown.
    u16 unknown0a;  // Inferred role: shutter b lod; original member name unknown.
    u16 unknown0c;  // Inferred role: switch a lod; original member name unknown.
    u16 unknown0e;  // Inferred role: switch b lod; original member name unknown.
    u16 unknown10;  // Inferred role: switch se; original member name unknown.
    u16 unknown12;  // Inferred role: shutter se; original member name unknown.
    u16 unknown14;  // Inferred role: lift start se; original member name unknown.
    u16 unknown16;  // Inferred role: lift loop se; original member name unknown.
    u16 unknown18;  // Inferred role: lift stop se; original member name unknown.
    u8 unknown1a;   // Inferred role: lift min volume dist; original member name unknown.
    u8 unknown1b;   // Inferred role: lift max volume dist; original member name unknown.
    bool unknown1c; // Inferred role: lift reverse; original member name unknown.
    f32 unknown20;  // Inferred role: call lift speed; original member name unknown.
    u16 unknown24;  // Inferred role: miss msg id; original member name unknown.
    f32 unknown28;  // Inferred role: next wait; original member name unknown.
    u16 unknown2c;  // Inferred role: lift a map jump id; original member name unknown.
    u16 unknown2e;  // Inferred role: lift b map jump id; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_ELEVATOR;

  ~GmkElevator() override;
  GmkType getGmkType() const override;
  int getGameFlagId() const;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;
  void onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo &info);
  void clearRequests();
  bool isCallSwitch(gf::GF_OBJ_HANDLE *handle) const;
  bool isLiftSwitch(gf::GF_OBJ_HANDLE *handle) const;
  bool isElevatorMoveOK() const;
  bool isGmkFinished() const;

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  u8 _48[0x290 - 0x48];
  gf::GF_OBJ_HANDLE *unknown290[4]; // Inferred role: switches, call switches at even indices and lift switches at odd ones; original member name unknown.
  u8 _2b0[0x4c8 - 0x2b0];
  u32 unknown4C8; // Role and original member name unknown.
  f32 unknown4CC; // Role and original member name unknown.
};

static_assert(sizeof(GmkElevator::BdatInfo) == 0x30, "");
static_assert(offsetof(GmkElevator, unknown290) == 0x290, "");
static_assert(offsetof(GmkElevator, unknown4C8) == 0x4c8, "");
static_assert(offsetof(GmkElevator, unknown4CC) == 0x4cc, "");
static_assert(sizeof(GmkElevator) == 0x4d0, "");

typedef TGmkList<GmkElevator, GmkElevator::BdatInfo, 0x54564c45, 2, GmkElevatorGobCustom> GmkElevatorList;

class GmkElevatorLocator : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_ELEVATOR_LOCATOR;

  ~GmkElevatorLocator() override { dispose(); }
  GmkType getGmkType() const override;
  bool isValid() const override;
};

static_assert(sizeof(GmkElevatorLocator) == 0x48, "");

typedef TGmkList<GmkElevatorLocator, GmkElevatorLocator::BdatInfo, 0x434c4c45, 2, GmkElevatorLocatorGob> GmkElevatorLocatorList;

} // namespace gmk
