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

  u32 unknown08;         // Inferred role: pad no; original member name unknown.
  PadBattle m_padBattle; // Inferred role: battle; original member name unknown.
  PadField m_padField;   // Inferred role: field; original member name unknown.
};

static_assert(offsetof(PadAgent, unknown08) == 0x08, "");
static_assert(offsetof(PadAgent, m_padBattle) == 0x10, "");
static_assert(offsetof(PadAgent, m_padField) == 0x90, "");
static_assert(sizeof(PadAgent) == 0xd8, "");

} // namespace pc
} // namespace gf
