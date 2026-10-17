#include "anm/anm_asm_control.h"

#include "anm/anm_asm_variable.h"

namespace anm {
class AsmListener;

ASMControl::~ASMControl() {
  for (u32 i = 0; i < 7; i++) {
    m_stateMachines[i].cleanup();
  }
  m_blender.cleanup();
}

void ASMControl::setListener(AsmListener *listener) {
  for (u32 i = 0; i < 7; i++) {
    m_stateMachines[i].m_listener = listener;
  }
}

void ASMControl::setVariable(const char *name, int value) {
  Variable *variable = findVariable(m_variables, name);
  if (variable != nullptr) {
    variable->setValue(value);
  }
}

bool ASMControl::getVariable(const char *name, int *value) const {
  const Variable *variable = findVariable(m_variables, name);
  if (variable == nullptr) {
    return false;
  }
  return variable->getValue(value);
}

void ASMControl::setVariable(const char *name, f32 value) {
  Variable *variable = findVariable(m_variables, name);
  if (variable != nullptr) {
    variable->setValue(value);
  }
}

bool ASMControl::getVariable(const char *name, f32 *value) const {
  const Variable *variable = findVariable(m_variables, name);
  if (variable == nullptr) {
    return false;
  }
  return variable->getValue(value);
}

} // namespace anm
