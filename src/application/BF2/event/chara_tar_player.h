#pragma once
#include <stddef.h>

#include "event/anm_f32.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaIKUpdater;
class CharaWeightPlayer;

class CharaTarPlayer {
public:
  static constexpr size_t REQUEST_COUNT = 6;

  enum {
    FLAG_ENABLE = 1 << 0,
  };

  enum TYPE {
    TYPE_ENABLE = 1,
    TYPE_DISABLE = 2,
    TYPE_MOVE = 3,
  };

  struct Request {
    TYPE unknown00; // Inferred role: type; original member name unknown.
    f32 unknown04;  // Inferred role: frame; original member name unknown.
    bool unknown08; // Inferred role: no spine; original member name unknown.
    bool unknown09; // Inferred role: first; original member name unknown.
    f32 unknown0c;  // Inferred role: remain frame; original member name unknown.
  };

  CharaTarPlayer();
  virtual ~CharaTarPlayer() {}
  void create(gf::GF_OBJ_HANDLE *handle, CharaIKUpdater *ik);
  void destroy();
  void update(f32 delta);
  void setEnable(bool isEnable, f32 frame, bool isNoSpine);
  void setTargetPos(const mm::Vec3 &position);

private:
  gf::GF_OBJ_HANDLE *unknown08;                           // Inferred role: handle; original member name unknown.
  CharaIKUpdater *unknown10;                              // Inferred role: ik; original member name unknown.
  u32 unknown18;                                          // Inferred role: flags; original member name unknown.
  mm::mtl::FixedVector<Request, REQUEST_COUNT> unknown20; // Inferred role: requests; original member name unknown.
  mm::Vec3 unknown90;                                     // Inferred role: tar; original member name unknown.
  mm::Vec3 unknowna0;                                     // Inferred role: start tar; original member name unknown.
  mm::Vec3 unknownb0;                                     // Inferred role: target pos; original member name unknown.
  AnmF32 unknownc0;                                       // Inferred role: move anm; original member name unknown.
};

static_assert(sizeof(CharaTarPlayer) == 0x1d0, "");

class CharaTarPlayerMot {
public:
  static constexpr u32 AIMMOT_COUNT = 6;

  enum {
    FLAG_ENABLE = 1 << 0,
    FLAG_NO_SPINE = 1 << 1,
  };

  enum REQUEST {
    REQUEST_NONE,
    REQUEST_ENABLE,
    REQUEST_MOVE,
    REQUEST_DISABLE,
  };

  CharaTarPlayerMot();
  virtual ~CharaTarPlayerMot() {}
  void create(gf::GF_OBJ_HANDLE *handle, CharaWeightPlayer *weight);
  void destroy();
  void update(f32 delta);
  void setEnable(bool isEnable, f32 frame, bool isNoSpine);
  void setTargetPos(const mm::Vec3 &position);

private:
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown18 |= flag;
    } else {
      unknown18 &= ~flag;
    }
  }

  gf::GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
  CharaWeightPlayer *unknown10; // Inferred role: weight; original member name unknown.
  u32 unknown18;                // Inferred role: flags; original member name unknown.
  REQUEST unknown1c;            // Inferred role: request; original member name unknown.
  f32 unknown20;                // Inferred role: request frame; original member name unknown.
  bool unknown24;               // Inferred role: no spine; original member name unknown.
  mm::Vec3 unknown30;           // Inferred role: tar; original member name unknown.
  mm::Vec3 unknown40;           // Inferred role: start tar; original member name unknown.
  mm::Vec3 unknown50;           // Inferred role: target pos; original member name unknown.
  AnmF32 unknown60;             // Inferred role: weight anm; original member name unknown.
  AnmF32 unknown170;            // Inferred role: move anm; original member name unknown.
  f32 unknown280[AIMMOT_COUNT]; // Inferred role: aimmot weights; original member name unknown.
};

static_assert(sizeof(CharaTarPlayerMot) == 0x2a0, "");

} // namespace event
