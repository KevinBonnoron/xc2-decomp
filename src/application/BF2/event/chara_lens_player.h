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
    FLAG_UNKNOWN_0 = 0,   // Inferred role: direct flag; original name unknown.
    FLAG_UNKNOWN_1 = 1,   // Inferred role: manual flag; original name unknown.
    FLAG_UNKNOWN_32 = 32, // Inferred role: max flag; original name unknown.
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
  mm::mtl::unknown027<FLAG_UNKNOWN_32> unknown08; // Inferred role: flags; original member name unknown.
  mm::Vec2 m_target;
  mm::Vec2 unknown20;        // Inferred role: manual target; original member name unknown.
  mm::Vec2 unknown30;        // Inferred role: auto target; original member name unknown.
  CharaIKUpdater *unknown40; // Inferred role: ik; original member name unknown.
};

static_assert(sizeof(CharaLensPlayer) == 0x50, "");

} // namespace event
