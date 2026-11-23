#include "gf/object/component/pc/gf_pc_pad_agent.h"

#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_callback.h"
#include "mm_mtl/bitflag.h"

namespace anm {
class ResASM;
} // namespace anm

namespace fw {
struct EffectResData;
} // namespace fw

namespace gf {
struct GF_OBJ_HANDLE;

namespace pc {

void registerAsmCallback(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm, fw::EffectResData *effectData) {
  if (resAsm != nullptr) {
    registerAsmCallbackField(handle, resAsm);
    registerAsmCallbackBattle(handle, resAsm);
  }
}

PadAgent::PadAgent(u32 padNo) : unknown08(padNo) {}

void PadAgent::setup(GfComPropertyPc &property) {
  m_padBattle.setup(unknown08, property);
  m_padField.setup(unknown08, property);
}

void PadAgent::cleanup(GfComPropertyPc &property) {
  m_padBattle.cleanup(property);
  m_padField.cleanup(property);
}

void PadAgent::update(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  property.unknown6c = property.unknown60;
  property.unknown60.unknown08.clear();
  m_padBattle.update(info, property);
  m_padField.update(info, property);
}

const mm::mtl::RTTI *PadAgent::getRTTI() const { return &m_rtti; }

} // namespace pc
} // namespace gf
