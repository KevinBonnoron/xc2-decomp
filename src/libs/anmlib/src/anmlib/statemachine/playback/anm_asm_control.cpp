#include "anm/anm_asm_control.h"

#include "anm/anm_asm_variable.h"

namespace anm {
class AsmListener;

ASMControl::~ASMControl() {
  for (u32 i = 0; i < 7; i++) {
    unknown70[i].cleanup();
  }
  unknown20.cleanup();
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
