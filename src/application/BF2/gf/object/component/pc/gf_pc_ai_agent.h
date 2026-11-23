#pragma once
#include <stddef.h>

#include "gf/object/component/pc/gf_pc_agent.h"
#include "gf/object/component/pc/gf_pc_ai_agent_battle.h"
#include "gf/object/component/pc/gf_pc_ai_agent_field.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

namespace pc {

class AIAgent : public Agent {
public:
  static mm::mtl::RTTI m_rtti;

  AIAgent();
  ~AIAgent() override;
  void setup(GfComPropertyPc &property) override;
  void cleanup(GfComPropertyPc &property) override;
  void update(const fw::UpdateInfo &info, GfComPropertyPc &property) override;
  void setFieldAI(GfComPropertyPc &property, bool isEnable) override;
  void setBattleAI(GfComPropertyPc &property, bool isEnable) override;
  const mm::mtl::RTTI *getRTTI() const override;
  bool testFiledAI() const override;
  bool testBattleAI() const override;
  bool recieveMessage(GfComPropertyPc &property, fw::MessageObject *sender, fw::Message &message) override;

  u32 unknown08;                 // Inferred role: flags (bit 0 field AI, bit 1 battle AI); original member name unknown.
  AIAgentField m_aIAgentField;   // Inferred role: field AI; original member name unknown.
  AIAgentBattle m_aIAgentBattle; // Inferred role: battle AI; original member name unknown.
};

static_assert(offsetof(AIAgent, unknown08) == 0x08, "");
static_assert(offsetof(AIAgent, m_aIAgentField) == 0x10, "");
static_assert(offsetof(AIAgent, m_aIAgentBattle) == 0xa0, "");
static_assert(sizeof(AIAgent) == 0xa8, "");

} // namespace pc
} // namespace gf
