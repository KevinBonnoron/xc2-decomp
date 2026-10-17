#include "gf/object/component/pc/gf_pc_agent.h"

namespace gf {

namespace pc {

Agent::~Agent() {}

const mm::mtl::RTTI *Agent::getRTTI() const { return &m_rtti; }

void Agent::setup(GfComPropertyPc &property) {}

void Agent::cleanup(GfComPropertyPc &property) {}

bool Agent::testFiledAI() const { return false; }

void Agent::setFieldAI(GfComPropertyPc &property, bool isEnable) {}

bool Agent::testBattleAI() const { return false; }

void Agent::setBattleAI(GfComPropertyPc &property, bool isEnable) {}

bool Agent::recieveMessage(GfComPropertyPc &property, fw::MessageObject *sender, fw::Message &message) { return false; }

} // namespace pc
} // namespace gf
