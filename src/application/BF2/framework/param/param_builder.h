#pragma once

#include "fw/fw_param_manager.h"
#include "mm_mtl/intrusive_ptr.h"

namespace fw {

class Reflection;

class ParamBuilder {
public:
  static mm::mtl::IntrusivePtr<ParamList> importBinary(void *data, Reflection *reflection);
};

} // namespace fw
