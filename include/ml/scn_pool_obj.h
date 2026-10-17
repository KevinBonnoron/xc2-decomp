#pragma once
#include "types.h"

namespace ml {

class ScnObj;

class ScnPoolObj {
public:
  bool isValidInsert(u16 type) const;
  void insert(ScnObj *obj);
  bool isExistLgtEnv() const;
};

} // namespace ml
