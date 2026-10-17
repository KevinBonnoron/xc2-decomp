#pragma once
#include <stddef.h>

#include "gf/object/component/pc/gf_pc_agent.h"
#include "gf/object/component/pc/gf_pc_pad_battle.h"
#include "gf/object/component/pc/gf_pc_pad_field.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

namespace pc {

class PadAgent : public Agent {
public:
  static mm::mtl::RTTI m_rtti;

  PadAgent(u32 padNo);
  void setup(GfComPropertyPc &property) override;
  void cleanup(GfComPropertyPc &property) override;
  void update(const fw::UpdateInfo &info, GfComPropertyPc &property) override;
  const mm::mtl::RTTI *getRTTI() const override;

  u32 padNo;
  PadBattle battle;
  PadField field;
};

static_assert(offsetof(PadAgent, padNo) == 0x08, "");
static_assert(offsetof(PadAgent, battle) == 0x10, "");
static_assert(offsetof(PadAgent, field) == 0x90, "");
static_assert(sizeof(PadAgent) == 0xd8, "");

} // namespace pc
} // namespace gf
