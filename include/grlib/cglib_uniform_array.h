#pragma once
#include <new>
#include <stddef.h>

#include "grlib/cglib_mem_handle.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace grlib {

class CGLibOneUniformBlock;

template <typename T> class CGLibUniformArray {
public:
  void setupArray(u32 count);
  T &operator[](u32 index) { return m_items[index]; }

  T *m_items;
  u32 unknown08; // Inferred role: item count; original member name unknown.
  u8 _0c[0x18 - 0x0c];
  CGLibMemType unknown18; // Inferred role: mem type; original member name unknown.
};

template <typename T> void CGLibUniformArray<T>::setupArray(u32 count) {
  for (u32 i = 0; i < unknown08; i++) {
    m_items[i].release();
  }
  unknown08 = 0;
  if (m_items != nullptr) {
    mtl::MemManager::deallocate(m_items, 0, false);
    m_items = nullptr;
  }
  CGLibMemHandle::free(unknown18);
  unknown08 = count;
  m_items = static_cast<T *>(mtl::MemManager::allocate(CGLibMemHandle::s_hMemHandle, count * sizeof(T), 8, false, "no name", 0));
  for (u32 i = 0; i < unknown08; i++) {
    new (&m_items[i]) T();
  }
}

class CGLibOneUniformArray : public CGLibUniformArray<CGLibOneUniformBlock> {};

static_assert(offsetof(CGLibUniformArray<CGLibOneUniformBlock>, unknown08) == 0x08, "");
static_assert(offsetof(CGLibUniformArray<CGLibOneUniformBlock>, unknown18) == 0x18, "");
static_assert(sizeof(CGLibUniformArray<CGLibOneUniformBlock>) == 0x28, "");

} // namespace grlib
