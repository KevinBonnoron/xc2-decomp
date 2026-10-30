#pragma once
#include <stddef.h>

#include "framework/sound/sound_ssd_drv.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
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

// Inferred role: sound source id; original type name unknown.
struct unknown128 {
  u32 unknown00; // Inferred role: id; original member name unknown.
  u32 unknown04; // Inferred role: name hash; original member name unknown.
};

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
  void stopAll();
  bool canRelease() const;
  mm::mtl::IntrusivePtr<SoundSsdSource> getSource(u32 index) const;
  mm::mtl::IntrusivePtr<SoundSsdSource> findSourceFromID(u32 id) const;
  mm::mtl::IntrusivePtr<SoundSsdSource> findSource(const char *name) const;
  bool isLoopSource(u32 id) const;
  bool isLoopSource(const char *name) const;

  u8 _10[0x178 - 0x10];
  SoundSsdBank *unknown178;                                                    // Inferred role: bank; original member name unknown.
  mm::mtl::FixedVector<mm::mtl::IntrusivePtr<SoundSsdSource>, 256> unknown180; // Inferred role: sources; original member name unknown.
  mm::mtl::FixedVector<unknown128, 256> unknown988;                            // Inferred role: source ids; original member name unknown.
};

static_assert(offsetof(SoundPack, unknown178) == 0x178, "");
static_assert(offsetof(SoundPack, unknown180) == 0x180, "");
static_assert(offsetof(SoundPack, unknown988) == 0x988, "");

static_assert(offsetof(SoundPack::SetupInfo, unknown84) == 0x84, "");
static_assert(offsetof(SoundPack::SetupInfo, unknown90) == 0x90, "");
static_assert(offsetof(SoundPack::SetupInfo, unknowna4) == 0xa4, "");

} // namespace fw
