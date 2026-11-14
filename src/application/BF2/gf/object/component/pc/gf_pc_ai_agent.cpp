#include "gf/object/component/pc/gf_pc_ai_agent.h"

#include "gf/game/gf_game_player_formation.h"
#include "gf/object/component/pc/gf_com_property_pc.h"

namespace gf {
namespace pc {

AIAgent::AIAgent() : unknown08(0) {}

AIAgent::~AIAgent() {}

void AIAgent::setup(GfComPropertyPc &property) {
  if (property.unknown38 != PLAYER_ID_UNKNOWN_4294967295) {
    unknown10.setup(property);
  }
  unknowna0.setup(property);
}

void AIAgent::cleanup(GfComPropertyPc &property) {
  unknowna0.cleanup(property);
  if (property.unknown38 != PLAYER_ID_UNKNOWN_4294967295) {
    unknown10.cleanup(property);
  }
}

void AIAgent::update(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  if (property.unknown38 != PLAYER_ID_UNKNOWN_4294967295 && testFiledAI()) {
    unknown10.update(info, property);
  }
  if (testBattleAI()) {
    unknowna0.update(info, property);
  }
}

void AIAgent::setFieldAI(GfComPropertyPc &property, bool isEnable) {
  if (testFiledAI() == isEnable) {
    return;
  }
  if (isEnable) {
    unknown08 |= 1;
    unknown10.onActivate(property);
  } else {
    unknown08 &= ~1;
    unknown10.onDeactivate(property);
  }
}

void AIAgent::setBattleAI(GfComPropertyPc &property, bool isEnable) {
  if (testBattleAI() == isEnable) {
    return;
  }
  if (isEnable) {
    unknown08 |= 2;
    unknown10.onActivate(property);
  } else {
    unknown08 &= ~2;
    unknown10.onDeactivate(property);
  }
}

const mm::mtl::RTTI *AIAgent::getRTTI() const { return &m_rtti; }

bool AIAgent::testFiledAI() const { return (unknown08 & 1) != 0; }

bool AIAgent::testBattleAI() const { return (unknown08 & 2) != 0; }

bool AIAgent::recieveMessage(GfComPropertyPc &property, fw::MessageObject *sender, fw::Message &message) {
  if (testFiledAI()) {
    return unknown10.recieveMessage(property, sender, message);
  }
  return false;
}

} // namespace pc
} // namespace gf
