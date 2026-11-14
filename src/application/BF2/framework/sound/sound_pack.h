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

  SoundPack(SoundCategory category, mm::mtl::IAllocator *allocator, const char *name, SoundPriority priority);
  static SoundPack *createFromStream(mm::mtl::IAllocator *allocator, const SetupInfo &info);
  void registSource(void *data, u32 size);
  static SoundPack *create(const SetupInfo &info);
  ~SoundPack() override;
  void stopAll();
  bool canRelease() const;
  mm::mtl::IntrusivePtr<SoundSsdSource> getSource(u32 index) const;
  mm::mtl::IntrusivePtr<SoundSsdSource> findSourceFromID(u32 id) const;
  mm::mtl::IntrusivePtr<SoundSsdSource> findSource(const char *name) const;
  bool isLoopSource(u32 id) const;
  bool isLoopSource(const char *name) const;

  SoundCategory unknown0c;        // Inferred role: category; original member name unknown.
  mm::mtl::IAllocator *unknown10; // Inferred role: allocator; original member name unknown.
  void *unknown18;                // Inferred role: data; original member name unknown.
  u32 unknown20;                  // Inferred role: data size; original member name unknown.
  mm::mtl::FixStr<256> unknown24; // Inferred role: name; original member name unknown.
  u32 unknown128;                 // Inferred role: name hash; original member name unknown.
  mm::mtl::FixStr<64> unknown12c; // Inferred role: name without path and extension; original member name unknown.
  SoundPriority unknown170;       // Inferred role: priority; original member name unknown.
  SoundSsdBank *unknown178;       // Inferred role: bank; original member name unknown.
  mm::mtl::FixedVector<mm::mtl::IntrusivePtr<SoundSsdSource>, 256> m_source;
  mm::mtl::FixedVector<fw::unknown128, 256> unknown988; // Inferred role: source ids; original member name unknown.
};

static_assert(offsetof(SoundPack, unknown0c) == 0x0c, "");
static_assert(offsetof(SoundPack, unknown10) == 0x10, "");
static_assert(offsetof(SoundPack, unknown18) == 0x18, "");
static_assert(offsetof(SoundPack, unknown20) == 0x20, "");
static_assert(offsetof(SoundPack, unknown24) == 0x24, "");
static_assert(offsetof(SoundPack, unknown128) == 0x128, "");
static_assert(offsetof(SoundPack, unknown12c) == 0x12c, "");
static_assert(offsetof(SoundPack, unknown170) == 0x170, "");
static_assert(offsetof(SoundPack, unknown178) == 0x178, "");
static_assert(offsetof(SoundPack, m_source) == 0x180, "");
static_assert(offsetof(SoundPack, unknown988) == 0x988, "");

static_assert(offsetof(SoundPack::SetupInfo, unknown84) == 0x84, "");
static_assert(offsetof(SoundPack::SetupInfo, unknown90) == 0x90, "");
static_assert(offsetof(SoundPack::SetupInfo, unknowna4) == 0xa4, "");

} // namespace fw
