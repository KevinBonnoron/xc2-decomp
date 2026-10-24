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

  fw::PadRelay unknown08;     // Inferred role: relay; original member name unknown.
  fw::PadRelay unknown40;     // Inferred role: target relay; original member name unknown.
  GfComPropertyPc *unknown78; // Inferred role: property; original member name unknown.
};

static_assert(offsetof(PadBattle, unknown08) == 0x08, "");
static_assert(offsetof(PadBattle, unknown40) == 0x40, "");
static_assert(offsetof(PadBattle, unknown78) == 0x78, "");
static_assert(sizeof(PadBattle) == 0x80, "");

} // namespace pc
} // namespace gf
