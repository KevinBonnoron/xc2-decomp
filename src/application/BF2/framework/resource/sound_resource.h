#pragma once
#include <stddef.h>

#include "framework/resource/resource_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class AssetData;
class AssetLoader;
class SoundPack;
enum SoundCategory : int;
enum SoundPriority : int;

class SoundResource : public ResourceObject {
public:
  enum State {
    STATE_NONE = 0,
    STATE_LOADING = 1,
    STATE_LOADED = 2,
  };

  struct SetupInfo {
    SetupInfo() : category(static_cast<SoundCategory>(3)), priority(static_cast<SoundPriority>(0)), maxSound(128) {}

    SoundCategory category;
    SoundPriority priority;
    u32 maxSound;
  };

  static SoundResource *search(mm::mtl::IAllocator *allocator, const char *path);
  static SoundResource *request(mm::mtl::IAllocator *allocator, const char *path, const SetupInfo &info, LOAD_PRIO priority);
  SoundResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority);
  ~SoundResource() override;
  void update() override;
  const char *getMemName();
  bool valid() const override;
  void *getAssetData();
  int getAssetSize() const;
  const char *getAssetName() const;
  SoundPack *getSoundPack();

  State state;
  AssetLoader *loader;
  AssetData *asset;
  SoundPack *soundPack;
  SetupInfo setupInfo;
};

static_assert(offsetof(SoundResource, state) == 0xb0, "");
static_assert(offsetof(SoundResource, soundPack) == 0xc8, "");
static_assert(offsetof(SoundResource, setupInfo) == 0xd0, "");
static_assert(sizeof(SoundResource) == 0xe0, "");

} // namespace fw
