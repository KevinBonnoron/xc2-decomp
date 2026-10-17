#include "gf/object/component/pc/gf_pc_pad_agent.h"

#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_mtl/bitflag.h"

namespace gf {

namespace pc {

PadAgent::PadAgent(u32 padNo) : padNo(padNo) {}

void PadAgent::setup(GfComPropertyPc &property) {
  battle.setup(padNo, property);
  field.setup(padNo, property);
}

void PadAgent::cleanup(GfComPropertyPc &property) {
  battle.cleanup(property);
  field.cleanup(property);
}

void PadAgent::update(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  property.previousInput = property.input;
  property.input.flags.clear();
  battle.update(info, property);
  field.update(info, property);
}

const mm::mtl::RTTI *PadAgent::getRTTI() const { return &m_rtti; }

} // namespace pc
} // namespace gf
