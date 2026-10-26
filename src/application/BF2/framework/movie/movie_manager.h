#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "ml/work_background.h"
#include "mm_mtl/singleton.h"
#include "types.h"

class ICMovie;

namespace layer {
class LayerBase;
} // namespace layer

namespace mm {
namespace mtl {
class IAllocator;
}
} // namespace mm

namespace fw {

class MovieManager : public ManagerObject, public mm::mtl::PtrSingleton<MovieManager>, public ml::IWorkBackground {
public:
  ~MovieManager();
  const char *getName() const override;
  void open(mm::mtl::IAllocator *allocator, u32 layer);
  void open(mm::mtl::IAllocator *allocator, int width, int height, u32 layer);
  void close();
  void update();
  void stop();
  bool set_file(const char *path);
  f32 get_length();
  f32 pos();
  void play();
  void pause();
  bool isstandby();
  bool ispause();
  bool isplaying();
  void bkgHomeMenu(bool isEnter) override;

  u32 unknown20;               // Inferred role: ui object handle; original member name unknown.
  layer::LayerBase *unknown28; // Inferred role: layer; original member name unknown.
  ICMovie *unknown30;          // Inferred role: movie; original member name unknown.
  bool unknown38;              // Inferred role: playing; original member name unknown.
  u32 unknown3c;               // Inferred role: pitch; original member name unknown.
  u32 unknown40;               // Inferred role: update count; original member name unknown.
};

static_assert(offsetof(MovieManager, unknown20) == 0x20, "");
static_assert(offsetof(MovieManager, unknown28) == 0x28, "");
static_assert(offsetof(MovieManager, unknown3c) == 0x3c, "");
static_assert(offsetof(MovieManager, unknown40) == 0x40, "");

static_assert(offsetof(MovieManager, unknown30) == 0x30, "");
static_assert(offsetof(MovieManager, unknown38) == 0x38, "");

} // namespace fw
