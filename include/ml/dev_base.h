#pragma once
#include "ml/work_obj.h"

namespace ml {

class DevBase : public WorkObj {
public:
  DevBase(const char *name, WorkObj *parent, int childNum) : WorkObj(name, parent, childNum), _1a8(0) {}
  ~DevBase() override {}

  int _1a8;
};

} // namespace ml
