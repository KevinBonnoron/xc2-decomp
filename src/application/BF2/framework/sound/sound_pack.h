#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

enum SoundCategory : int;
enum SoundPriority : int;

class SoundPack : public mm::mtl::ReferenceObject {
public:
  struct SetupInfo {
    SetupInfo() : category(static_cast<SoundCategory>(3)), priority(static_cast<SoundPriority>(0)), assetName(nullptr), data(nullptr), size(0), maxSound(128) {}

    mm::mtl::FixStr<128> name;
    SoundCategory category;
    SoundPriority priority;
    const char *assetName;
    void *data;
    u32 size;
    u32 maxSound;
  };

  static SoundPack *createFromStream(mm::mtl::IAllocator *allocator, const SetupInfo &info);
  ~SoundPack() override;
};

static_assert(offsetof(SoundPack::SetupInfo, category) == 0x84, "");
static_assert(offsetof(SoundPack::SetupInfo, assetName) == 0x90, "");
static_assert(offsetof(SoundPack::SetupInfo, maxSound) == 0xa4, "");

} // namespace fw
