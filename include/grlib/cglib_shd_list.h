#pragma once
#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace grlib {

// Layout evidence: CGLibShdListBase<CGLibDecShader>::createPacShader 0x71007c232c, ~CGLibShdListBase 0x71007c4808.
template <class T> class CGLibShdListBase {
public:
  CGLibShdListBase() : unknown40(nullptr), unknown48(nullptr), unknown50(0) {}
  virtual ~CGLibShdListBase() { release(); }
  bool createPacShader(const void *data, u32 value, bool isCopy);

  void release() {
    unknown10.release();
    if (unknown48 != nullptr) {
      for (s32 i = 0; i < unknown50; i++) {
        unknown40[i].~T();
      }
      unknown50 = 0;
      if (unknown48 != nullptr) {
        mtl::MemManager::deallocate(unknown48, 0, false);
        unknown48 = nullptr;
      }
    }
  }

  const void *unknown08;     // Inferred role: shader pack data; original member name unknown.
  CGLibVtlMemPool unknown10; // Inferred role: mem pool; original member name unknown.
  T *unknown40;              // Inferred role: shaders; original member name unknown.
  void *unknown48;           // Inferred role: allocated buffer; original member name unknown.
  s32 unknown50;             // Inferred role: shader num; original member name unknown.
  u32 unknown54;             // Inferred role: shader mode; original member name unknown.
};

class CGLibShdListData : public CGLibShdListBase<CGLibDecShader> {
public:
  ~CGLibShdListData() { release(); }
};

static_assert(sizeof(CGLibShdListData) == 0x58, "");

} // namespace grlib
