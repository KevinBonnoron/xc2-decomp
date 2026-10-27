#include "anm/anm_asm_control.h"

#include "anm/anm_array-inl.h"
#include "anm/anm_asm_variable.h"
#include "anm/anm_res_asm.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec4.h"

namespace anm {
class AsmListener;

ASMControl::ASMControl(const ResASM &resAsm, mm::mtl::IAllocator &allocator) : ReferenceObject(&allocator), unknown18(&resAsm), unknown48(&allocator) {
  unknown20.setup(resAsm, allocator);
  const ResStateArray *resStateArray = resAsm.unknown20;
  unknown48.resize(resStateArray->unknown28.size());
  for (u32 i = 0; i < resStateArray->unknown28.size(); i++) {
    unknown48[i].setup(resStateArray->unknown28[i]);
  }
  StateMachine *stateMachine = unknown70;
  for (u32 i = 0; i < LAYER_MAX; i++, stateMachine++) {
    stateMachine->unknown58 = &unknown20;
    stateMachine->unknown60 = &unknown48;
    stateMachine->setup(resAsm, i, allocator);
  }
  unknown380.unknown00 = mm::Vec4::zero;
  unknown380.unknown10 = mm::Quat::identity;
  unknown380.unknown20 = mm::Vec4::unit;
}

ASMControl::~ASMControl() {
  for (u32 i = 0; i < 7; i++) {
    unknown70[i].cleanup();
  }
  unknown20.cleanup();
}

void ASMControl::updateFrame(f32 deltaTime) {
  for (u32 i = 0; i < LAYER_MAX; i++) {
    unknown70[i].update(deltaTime);
  }
  unknown20.getDeltaExtractMotion(deltaTime, &unknown380);
  for (u32 i = 0; i < LAYER_MAX; i++) {
    unknown70[i].updateFrame(deltaTime);
  }
}

void ASMControl::setListener(AsmListener *listener) {
  for (u32 i = 0; i < 7; i++) {
    unknown70[i].unknown50 = listener;
  }
}

void ASMControl::setVariable(const char *name, int value) {
  Variable *variable = findVariable(unknown48, name);
  if (variable != nullptr) {
    variable->setValue(value);
  }
}

bool ASMControl::getVariable(const char *name, int *value) const {
  const Variable *variable = findVariable(unknown48, name);
  if (variable == nullptr) {
    return false;
  }
  return variable->getValue(value);
}

void ASMControl::setVariable(const char *name, f32 value) {
  Variable *variable = findVariable(unknown48, name);
  if (variable != nullptr) {
    variable->setValue(value);
  }
}

bool ASMControl::getVariable(const char *name, f32 *value) const {
  const Variable *variable = findVariable(unknown48, name);
  if (variable == nullptr) {
    return false;
  }
  return variable->getValue(value);
}

} // namespace anm

template anm::Control **mm::mtl::Vector<anm::Control *>::erase(anm::Control **);
template void mm::mtl::Vector<anm::Control *>::expand(size_t, size_t);
