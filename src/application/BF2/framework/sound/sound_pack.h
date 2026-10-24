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
    SetupInfo() : unknown84(static_cast<SoundCategory>(3)), unknown88(static_cast<SoundPriority>(0)), unknown90(nullptr), unknown98(nullptr), unknowna0(0), unknowna4(128) {}

    mm::mtl::FixStr<128> unknown00; // Inferred role: name; original member name unknown.
    SoundCategory unknown84;        // Inferred role: category; original member name unknown.
    SoundPriority unknown88;        // Inferred role: priority; original member name unknown.
    const char *unknown90;          // Inferred role: asset name; original member name unknown.
    void *unknown98;                // Inferred role: data; original member name unknown.
    u32 unknowna0;                  // Inferred role: size; original member name unknown.
    u32 unknowna4;                  // Inferred role: max sound; original member name unknown.
  };

  static SoundPack *createFromStream(mm::mtl::IAllocator *allocator, const SetupInfo &info);
  ~SoundPack() override;
};

static_assert(offsetof(SoundPack::SetupInfo, unknown84) == 0x84, "");
static_assert(offsetof(SoundPack::SetupInfo, unknown90) == 0x90, "");
static_assert(offsetof(SoundPack::SetupInfo, unknowna4) == 0xa4, "");

} // namespace fw
