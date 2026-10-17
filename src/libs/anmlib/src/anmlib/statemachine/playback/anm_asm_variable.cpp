#include "anm/anm_asm_variable.h"

#include "mm/mm_std_base.h"

namespace anm {

Variable::Variable() : m_pResVariable(nullptr) {}

void Variable::setup(const ResVariable &resVariable) {
  m_pResVariable = &resVariable;
  if (resVariable.type == ResVariable::TYPE_INT) {
    m_intValue = 1;
  } else {
    m_floatValue = 0.0f;
  }
}

bool Variable::setValue(s32 value) {
  MM_ASSERT(m_pResVariable);
  if (m_pResVariable->type != ResVariable::TYPE_INT) {
    return false;
  }
  m_intValue = value;
  return true;
}

bool Variable::setValue(f32 value) {
  MM_ASSERT(m_pResVariable);
  if (m_pResVariable->type != ResVariable::TYPE_FLOAT) {
    return false;
  }
  m_floatValue = value;
  return true;
}

bool Variable::getValue(s32 *value) const {
  MM_ASSERT(m_pResVariable);
  if (m_pResVariable->type != ResVariable::TYPE_INT) {
    return false;
  }
  *value = m_intValue;
  return true;
}

bool Variable::getValue(f32 *value) const {
  MM_ASSERT(m_pResVariable);
  if (m_pResVariable->type != ResVariable::TYPE_FLOAT) {
    return false;
  }
  *value = m_floatValue;
  return true;
}

const char *Variable::getName() const {
  if (m_pResVariable == nullptr) {
    return "";
  }
  return m_pResVariable->name;
}

} // namespace anm
