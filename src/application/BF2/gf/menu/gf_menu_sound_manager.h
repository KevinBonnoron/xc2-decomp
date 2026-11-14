#pragma once
#include <stddef.h>

#include "gf/sound/gf_sound.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/type_traits.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_SE_CATEGORY_HANDLE;
struct GfSetupParam;

class GfMenuSoundManager : public mm::mtl::PtrSingleton<GfMenuSoundManager> {
public:
  // Inferred role: playing jingle; original type name unknown.
  struct unknown001 {
    unknown001() : unknown00(0) {}

    SoundHandle unknown00; // Inferred role: sound handle; original member name unknown.
    u32 unknown08;         // Inferred role: jingle id; original member name unknown.
  };

  GfMenuSoundManager(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfMenuSoundManager();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void postUpdate(const fw::UpdateInfo &info);
  bool isSpecInJingle(u32 id);
  static void fadeInFieldBgm(f32 time);
  static SoundHandle playJingle(u32 id);
  bool isSpecOutJingle(u32 id);
  static void fadeFieldBgm(f32 time, f32 volume);
  static void fadeOutFieldBgm(f32 time);

  bool unknown08;                                // Inferred role: initialized; original member name unknown.
  mm::mtl::FixedVector<unknown001, 8> unknown10; // Inferred role: playing jingles; original member name unknown.
  GF_SE_CATEGORY_HANDLE *unknown78;              // Inferred role: category handle; original member name unknown.
};

static_assert(sizeof(GfMenuSoundManager::unknown001) == 0xc, "");
static_assert(offsetof(GfMenuSoundManager, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuSoundManager, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuSoundManager, unknown78) == 0x78, "");
static_assert(sizeof(GfMenuSoundManager) == 0x80, "");

} // namespace gf

namespace mm {
namespace mtl {

template <> struct is_pod<gf::GfMenuSoundManager::unknown001> {
  static const bool unknown001 = true; // Inferred role: whether the type is plain old data, so it is copied with memcpy; original name unknown.
};

} // namespace mtl
} // namespace mm
