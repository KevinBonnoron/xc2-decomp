#pragma once
#include <stddef.h>

#include "mm_mtl/map.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {
class SoundPack;
} // namespace fw

namespace gf {

// Layout from its constructor, create, dispose, createSe and update; GfFobjManager embeds it at 0x90d0.
class GfFobjSeManager {
public:
  struct CreateInfo {
    CreateInfo() : unknown00(0.1f), unknown04(8) {}

    f32 unknown00; // Inferred role: minimum interval between two plays of one se; original member name unknown.
    u32 unknown04; // Inferred role: maximum number of playing se; original member name unknown.
  };

  // Layout evidence: createSe (0x71002f58f8) stores the se id and the sound handle as one 8-byte element of
  // Vector<SeInfo>, whose erase (0x71002f5ce4) and expand (0x71002fa274) move the elements with memmove/memcpy;
  // update (0x71002f5b30) tests the handle at 0x04 with fw::SoundManager::isPlaying.
  struct SeInfo {
    u16 unknown00; // Inferred role: se id; original member name unknown.
    u32 unknown04; // Inferred role: sound handle; original member name unknown.
  };

  GfFobjSeManager(const CreateInfo *info);
  ~GfFobjSeManager() { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  void update(f32 deltaTime);

  CreateInfo unknown00;              // Inferred role: create info; original member name unknown.
  fw::SoundPack *unknown08;          // Inferred role: se pack; original member name unknown.
  mm::mtl::Vector<SeInfo> unknown10; // Inferred role: playing se; original member name unknown.
  mm::mtl::Map<u16, f32> unknown38;  // Inferred role: elapsed time since the last play of each se; original member name unknown.
};

static_assert(offsetof(GfFobjSeManager::CreateInfo, unknown04) == 0x04, "");
static_assert(sizeof(GfFobjSeManager::CreateInfo) == 0x08, "");
static_assert(offsetof(GfFobjSeManager::SeInfo, unknown04) == 0x04, "");
static_assert(sizeof(GfFobjSeManager::SeInfo) == 0x08, "");
static_assert(offsetof(GfFobjSeManager, unknown08) == 0x08, "");
static_assert(offsetof(GfFobjSeManager, unknown10) == 0x10, "");
static_assert(offsetof(GfFobjSeManager, unknown38) == 0x38, "");
static_assert(sizeof(GfFobjSeManager) == 0x50, "");

} // namespace gf
