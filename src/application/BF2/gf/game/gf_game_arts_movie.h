#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace mm {
namespace mtl {
class IAllocator;
}
} // namespace mm

namespace gf {

struct GF_SLOT_HANDLE;

class GfArtsMovie : public mm::mtl::PtrSingleton<GfArtsMovie>, public IGfEvent {
public:
  GfArtsMovie();
  ~GfArtsMovie();
  void update(const fw::UpdateInfo &info);
  void startSetup(const char *name);
  void updateForSetup(const fw::UpdateInfo &info);
  void updateForPlay(const fw::UpdateInfo &info);
  void updateForMemorySafe(const fw::UpdateInfo &info);
  static GfArtsMovie *createSiren();
  static void destroy();
  s32 getState() const;
  void gevPause(u32 resumeBits, u32 pauseBits) override;

  GF_SLOT_HANDLE *unknown10;                                 // Inferred role: movie buffer slot; original member name unknown.
  mm::mtl::IAllocator *unknown18;                            // Inferred role: movie buffer allocator; original member name unknown.
  u32 unknown20;                                             // Inferred role: cleared by constructor; original member name unknown.
  s32 m_state;                                               // Name from getState().
  mm::mtl::Delegate<void(const fw::UpdateInfo &)> unknown28; // Inferred role: update callback; original member name unknown.
};

static_assert(offsetof(GfArtsMovie, unknown10) == 0x10, "");
static_assert(offsetof(GfArtsMovie, unknown18) == 0x18, "");
static_assert(offsetof(GfArtsMovie, m_state) == 0x24, "");
static_assert(offsetof(GfArtsMovie, unknown28) == 0x28, "");
static_assert(sizeof(GfArtsMovie) == 0x48, "");

} // namespace gf
