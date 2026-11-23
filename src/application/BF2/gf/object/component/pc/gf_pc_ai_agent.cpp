#include "gf/object/component/pc/gf_pc_ai_agent.h"

#include "gf/game/gf_game_player_formation.h"
#include "gf/object/component/pc/gf_com_property_pc.h"

namespace gf {
namespace pc {

AIAgent::AIAgent() : unknown08(0) {}

AIAgent::~AIAgent() {}

void AIAgent::setup(GfComPropertyPc &property) {
  if (property.unknown38 != PLAYER_ID_UNKNOWN_4294967295) {
    m_aIAgentField.setup(property);
  }
  m_aIAgentBattle.setup(property);
}

void AIAgent::cleanup(GfComPropertyPc &property) {
  m_aIAgentBattle.cleanup(property);
  if (property.unknown38 != PLAYER_ID_UNKNOWN_4294967295) {
    m_aIAgentField.cleanup(property);
  }
}

void AIAgent::update(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  if (property.unknown38 != PLAYER_ID_UNKNOWN_4294967295 && testFiledAI()) {
    m_aIAgentField.update(info, property);
  }
  if (testBattleAI()) {
    m_aIAgentBattle.update(info, property);
  }
}

void AIAgent::setFieldAI(GfComPropertyPc &property, bool isEnable) {
  if (testFiledAI() == isEnable) {
    return;
  }
  if (isEnable) {
    unknown08 |= 1;
    m_aIAgentField.onActivate(property);
  } else {
    unknown08 &= ~1;
    m_aIAgentField.onDeactivate(property);
  }
}

void AIAgent::setBattleAI(GfComPropertyPc &property, bool isEnable) {
  if (testBattleAI() == isEnable) {
    return;
  }
  if (isEnable) {
    unknown08 |= 2;
    m_aIAgentField.onActivate(property);
  } else {
    unknown08 &= ~2;
    m_aIAgentField.onDeactivate(property);
  }
}

const mm::mtl::RTTI *AIAgent::getRTTI() const { return &m_rtti; }

bool AIAgent::testFiledAI() const { return (unknown08 & 1) != 0; }

bool AIAgent::testBattleAI() const { return (unknown08 & 2) != 0; }

bool AIAgent::recieveMessage(GfComPropertyPc &property, fw::MessageObject *sender, fw::Message &message) {
  if (testFiledAI()) {
    return m_aIAgentField.recieveMessage(property, sender, message);
  }
  return false;
}

} // namespace pc
} // namespace gf
