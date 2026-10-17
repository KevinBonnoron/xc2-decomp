#pragma once
#include <stddef.h>

#include "ml/critical_section.h"
#include "mm_mtl/fixstr.h"

namespace ml {

class BaseObjectM {
public:
  virtual ~BaseObjectM();
  virtual int AddRef();
  virtual int Release();
  virtual void SetName(const char *name);

  int refCount;
  mm::mtl::FixStr<128> name;
  CriticalSection criticalSection;
};

static_assert(offsetof(BaseObjectM, name) == 0x0c, "");
static_assert(offsetof(BaseObjectM, criticalSection) == 0x90, "");
static_assert(sizeof(BaseObjectM) == 0xb8, "");

} // namespace ml
