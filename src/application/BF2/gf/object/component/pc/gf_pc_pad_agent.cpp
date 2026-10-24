#include "gf/object/component/pc/gf_pc_pad_agent.h"

#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_mtl/bitflag.h"

namespace gf {

namespace pc {

PadAgent::PadAgent(u32 padNo) : unknown08(padNo) {}

void PadAgent::setup(GfComPropertyPc &property) {
  unknown10.setup(unknown08, property);
  unknown90.setup(unknown08, property);
}

void PadAgent::cleanup(GfComPropertyPc &property) {
  unknown10.cleanup(property);
  unknown90.cleanup(property);
}

void PadAgent::update(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  property.unknown6c = property.unknown60;
  property.unknown60.unknown08.clear();
  unknown10.update(info, property);
  unknown90.update(info, property);
}

const mm::mtl::RTTI *PadAgent::getRTTI() const { return &m_rtti; }

} // namespace pc
} // namespace gf
