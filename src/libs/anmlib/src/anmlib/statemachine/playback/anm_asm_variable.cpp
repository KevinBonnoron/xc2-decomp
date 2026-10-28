#include "anm/anm_asm_variable.h"

#include <algorithm>
#include <string.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/vector.h"

namespace anm {

Variable::Variable() : m_pResVariable(nullptr) {}

void Variable::setup(const ResVariable &resVariable) {
  m_pResVariable = &resVariable;
  if (resVariable.type == VAR_INT) {
    m_intValue = 1;
  } else {
    m_floatValue = 0.0f;
  }
}

bool Variable::setValue(s32 value) {
  MM_ASSERT(m_pResVariable);
  if (m_pResVariable->type != VAR_INT) {
    return false;
  }
  m_intValue = value;
  return true;
}

bool Variable::setValue(f32 value) {
  MM_ASSERT(m_pResVariable);
  if (m_pResVariable->type != VAR_FLOAT) {
    return false;
  }
  m_floatValue = value;
  return true;
}

bool Variable::getValue(s32 *value) const {
  MM_ASSERT(m_pResVariable);
  if (m_pResVariable->type != VAR_INT) {
    return false;
  }
  *value = m_intValue;
  return true;
}

bool Variable::getValue(f32 *value) const {
  MM_ASSERT(m_pResVariable);
  if (m_pResVariable->type != VAR_FLOAT) {
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

// Inferred comparator: orders a variable against a name; original name unknown.
struct unknown001 {
  bool operator()(const Variable &variable, const char *name) const { return strcmp(variable.getName(), name) < 0; }
};

Variable *findVariable(mm::mtl::Vector<Variable> &variables, const char *name) {
  if (variables.size() != 0) {
    Variable *it = std::lower_bound(variables.begin(), variables.end(), name, unknown001());
    if (it != variables.end() && strcmp(it->getName(), name) == 0) {
      return it;
    }
  }
  return nullptr;
}

const Variable *findVariable(const mm::mtl::Vector<Variable> &variables, const char *name) {
  if (variables.size() != 0) {
    const Variable *it = std::lower_bound(variables.begin(), variables.end(), name, unknown001());
    if (it != variables.end() && strcmp(it->getName(), name) == 0) {
      return it;
    }
  }
  return nullptr;
}

} // namespace anm
