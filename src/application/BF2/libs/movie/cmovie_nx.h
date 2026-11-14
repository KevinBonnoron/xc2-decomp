#pragma once
#include <stddef.h>

#include "movie/cmovie.h"
#include "types.h"

class MovieDecoderPlayer;
namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace CMovieNX {

// Layout evidence: CMovie::initialize 0x710069b04c (members 0x08..0x20) and the vtable _ZTVN8CMovieNX6CMovieE.
class CMovie : public ICMovie {
public:
  u8 *randfill(u8 *buffer, size_t size);
  void initialize(mm::mtl::IAllocator *allocator) override;
  void finalize() override;
  void update(unsigned char *buffer, int width, int height, int pitch) override;
  int set_file(const char *path) override;
  float get_length() override;
  float pos() override;
  void play() override;
  void pause() override;
  void stop() override;
  bool isstandby() override;
  bool ispause() override;
  bool isplaying() override;
  void doHomeMenu(bool isEnter) override;

  MovieDecoderPlayer *unknown08;  // Inferred role: decoder player; original member name unknown.
  void *unknown10;                // Inferred role: frame buffer; original member name unknown.
  size_t unknown18;               // Inferred role: size of the frame buffer; original member name unknown.
  mm::mtl::IAllocator *unknown20; // Inferred role: allocator of the frame buffer; original member name unknown.
};

static_assert(offsetof(CMovie, unknown08) == 0x08, "");
static_assert(offsetof(CMovie, unknown10) == 0x10, "");
static_assert(offsetof(CMovie, unknown18) == 0x18, "");
static_assert(offsetof(CMovie, unknown20) == 0x20, "");
static_assert(sizeof(CMovie) == 0x28, "");

} // namespace CMovieNX
