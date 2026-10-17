#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {

class UIObjFactory : public mm::mtl::PtrSingleton<UIObjFactory> {
public:
  void registPreloadResource(u32 type, const char *name);
  bool isLoading() const;
};

} // namespace ui
