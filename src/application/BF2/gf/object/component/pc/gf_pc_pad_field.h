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

class PadField {
public:
  PadField();
  void setup(int padNo, GfComPropertyPc &property);
  void decideAction() const;
  void jumpAction() const;
  void lockAction() const;
  void wallReleaseAction() const;
  void lureAction() const;
  void moveFront(f32 value);
  void moveSide(f32 value);
  void cleanup(GfComPropertyPc &property);
  virtual void update(const fw::UpdateInfo &info, GfComPropertyPc &property);
  void setInput(InputID id) const;

  fw::PadRelay unknown08;     // Inferred role: relay; original member name unknown.
  GfComPropertyPc *unknown40; // Inferred role: property; original member name unknown.
};

static_assert(offsetof(PadField, unknown08) == 0x08, "");
static_assert(offsetof(PadField, unknown40) == 0x40, "");
static_assert(sizeof(PadField) == 0x48, "");

} // namespace pc
} // namespace gf
