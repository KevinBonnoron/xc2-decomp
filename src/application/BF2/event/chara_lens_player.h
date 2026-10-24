#pragma once
#include "mm_math/mm_vec2.h"
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace event {

class CharaIKUpdater;

class CharaLensPlayer {
public:
  static f32 MILD;

  enum {
    FLAG_DIRECT = 0,
    FLAG_MANUAL = 1,
    FLAG_MAX = 32,
  };

  CharaLensPlayer();
  virtual ~CharaLensPlayer() {}
  void create(CharaIKUpdater *ik);
  void destroy();
  void update(f32 delta);
  void render(const mm::Vec3 &position, f32 height);
  void setManualTarget(bool isManual, const mm::Vec2 &target, bool isDirect);
  void setAutoTarget(const mm::Vec2 &target, bool isDirect);
  const mm::Vec2 &getTarget() const;

private:
  mm::mtl::BitFlag<FLAG_MAX> unknown08; // Inferred role: flags; original member name unknown.
  alignas(16) mm::Vec2 m_target;
  u8 _18[0x20 - 0x18];
  mm::Vec2 unknown20; // Inferred role: manual target; original member name unknown.
  u8 _28[0x30 - 0x28];
  mm::Vec2 unknown30; // Inferred role: auto target; original member name unknown.
  u8 _38[0x40 - 0x38];
  CharaIKUpdater *unknown40; // Inferred role: ik; original member name unknown.
};

static_assert(sizeof(CharaLensPlayer) == 0x50, "");

} // namespace event
