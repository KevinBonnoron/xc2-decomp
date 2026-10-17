#pragma once
#include "types.h"

namespace anm {

enum VarType {
  VAR_INT,
  VAR_FLOAT,
};

struct ResVariable {
  VarType type;
  const char *name;
};

class Variable {
public:
  Variable();
  void setup(const ResVariable &resVariable);
  bool setValue(s32 value);
  bool setValue(f32 value);
  bool getValue(s32 *value) const;
  bool getValue(f32 *value) const;
  const char *getName() const;

  VarType getVarType() const { return m_pResVariable->type; }

  const ResVariable *m_pResVariable;
  union {
    s32 m_intValue;
    f32 m_floatValue;
  };
};

static_assert(sizeof(Variable) == 0x10, "");

} // namespace anm
