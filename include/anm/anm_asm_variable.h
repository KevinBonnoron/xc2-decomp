#pragma once
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {

// Inferred role: var type; original type name unknown.
enum unknown132 {
  unknown132_0, // Inferred role: int; original name unknown.
  VAR_FLOAT,
};

struct ResVariable {
  unknown132 type;
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

  unknown132 getVarType() const { return m_pResVariable->type; }

  const ResVariable *m_pResVariable;
  union {
    s32 m_intValue;
    f32 m_floatValue;
  };
};

static_assert(sizeof(Variable) == 0x10, "");

Variable *findVariable(mm::mtl::Vector<Variable> &variables, const char *name);
const Variable *findVariable(const mm::mtl::Vector<Variable> &variables, const char *name);

} // namespace anm
