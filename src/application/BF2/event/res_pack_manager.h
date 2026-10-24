#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace event {

class IResPackEvent;
class ResPack;

class ResPackManager {
public:
  static constexpr u32 PACK_COUNT = 16;

  ResPackManager();
  virtual ~ResPackManager() {}
  void clear();
  void update();
  void draw();
  void load(mtl::ALLOC_HANDLE handle, const char *path, IResPackEvent *event);
  bool isLoading() const;

private:
  mm::mtl::FixedVector<ResPack *, PACK_COUNT> unknown08; // Inferred role: packs; original member name unknown.
};

static_assert(sizeof(ResPackManager) == 0x90, "");

} // namespace event
