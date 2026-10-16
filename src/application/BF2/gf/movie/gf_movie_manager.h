#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
}
} // namespace mm

namespace gf {

struct GfSetupParam;

class GfMovieManager : public mm::mtl::PtrSingleton<GfMovieManager> {
public:
  GfMovieManager();
  static void build(const GfSetupParam &param);
  static void destroy();
  void close();
  void open(mm::mtl::IAllocator *allocator, u32 layer);
  bool set_file(const char *path);
  f32 get_length();
  f32 pos();
  void play();
  void pause();
  void stop();
  bool isstandby();
  bool ispause();
  bool isplaying();
};

static_assert(sizeof(GfMovieManager) == 0x8, "");

} // namespace gf
