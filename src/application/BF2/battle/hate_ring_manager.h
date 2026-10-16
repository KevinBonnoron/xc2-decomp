#pragma once
#include "mm_mtl/singleton.h"

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

class HateRingManager : public mm::mtl::PtrSingleton<HateRingManager> {
public:
  void SetData(int id, gf::GF_OBJ_HANDLE *handle, int);
};

} // namespace btl
