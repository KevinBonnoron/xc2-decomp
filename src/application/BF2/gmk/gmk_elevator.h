#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkElevatorGobCustom;
class GmkElevatorLocatorGob;

class GmkElevator : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0x30];
  };

  static const GmkType GMK_TYPE = GMK_TYPE_ELEVATOR;

  ~GmkElevator() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x4d0 - 0x48];
};

static_assert(sizeof(GmkElevator::BdatInfo) == 0x30, "");
static_assert(sizeof(GmkElevator) == 0x4d0, "");

typedef TGmkList<GmkElevator, GmkElevator::BdatInfo, 0x54564c45, 2, GmkElevatorGobCustom> GmkElevatorList;

class GmkElevatorLocator : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_ELEVATOR_LOCATOR;

  ~GmkElevatorLocator() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
};

static_assert(sizeof(GmkElevatorLocator) == 0x48, "");

typedef TGmkList<GmkElevatorLocator, GmkElevatorLocator::BdatInfo, 0x434c4c45, 2, GmkElevatorLocatorGob> GmkElevatorLocatorList;

} // namespace gmk
