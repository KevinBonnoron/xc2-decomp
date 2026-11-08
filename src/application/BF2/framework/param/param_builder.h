#pragma once

#include "fw/fw_param_manager.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace fw {

class Reflection;

class ParamBuilder {
public:
  static mm::mtl::IntrusivePtr<ParamList> create(void *data, u32 index, const char *name);
  static mm::mtl::IntrusivePtr<ParamList> importBinary(void *data, Reflection *reflection);
  static void destroy(u32 index);
  static bool restore(void *data);
};

} // namespace fw
