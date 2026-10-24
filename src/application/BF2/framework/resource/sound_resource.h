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
    SetupInfo() : unknown00(static_cast<SoundCategory>(3)), unknown04(static_cast<SoundPriority>(0)), unknown08(128) {}

    SoundCategory unknown00; // Inferred role: category; original member name unknown.
    SoundPriority unknown04; // Inferred role: priority; original member name unknown.
    u32 unknown08;           // Inferred role: max sound; original member name unknown.
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

  State unknownb0;        // Inferred role: state; original member name unknown.
  AssetLoader *unknownb8; // Inferred role: loader; original member name unknown.
  AssetData *unknownc0;   // Inferred role: asset; original member name unknown.
  SoundPack *m_soundPack;
  SetupInfo unknownd0; // Inferred role: setup info; original member name unknown.
};

static_assert(offsetof(SoundResource, unknownb0) == 0xb0, "");
static_assert(offsetof(SoundResource, m_soundPack) == 0xc8, "");
static_assert(offsetof(SoundResource, unknownd0) == 0xd0, "");
static_assert(sizeof(SoundResource) == 0xe0, "");

} // namespace fw
