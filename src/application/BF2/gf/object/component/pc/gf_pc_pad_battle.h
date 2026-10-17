#pragma once
#include <stddef.h>

#include "fw/fw_pad.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

namespace pc {

class PadBattle {
public:
  PadBattle();
  void setup(int padNo, GfComPropertyPc &property);
  void battleStart() const;
  void battleEnd() const;
  void art01() const;
  void art02() const;
  void art03() const;
  void bladeChange00() const;
  void bladeChange01() const;
  void bladeChange02() const;
  void kakusei() const;
  void requestPermit01() const;
  void requestPermit02() const;
  void spAttack() const;
  void chainAttack() const;
  void battlRescue() const;
  void changeCameraMode() const;
  void orderRally() const;
  void moveFront(f32 value);
  void moveSide(f32 value);
  void changeTargetR() const;
  void changeTargetL() const;
  void cleanup(GfComPropertyPc &property);
  virtual void update(const fw::UpdateInfo &info, GfComPropertyPc &property);
  void setInput(InputID id) const;

  fw::PadRelay relay;
  fw::PadRelay targetRelay;
  GfComPropertyPc *property;
};

static_assert(offsetof(PadBattle, relay) == 0x08, "");
static_assert(offsetof(PadBattle, targetRelay) == 0x40, "");
static_assert(offsetof(PadBattle, property) == 0x78, "");
static_assert(sizeof(PadBattle) == 0x80, "");

} // namespace pc
} // namespace gf
