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
    TYPE type;
    f32 frame;
    bool isNoSpine;
    bool isFirst;
    f32 remainFrame;
  };

  CharaTarPlayer();
  virtual ~CharaTarPlayer() {}
  void create(gf::GF_OBJ_HANDLE *handle, CharaIKUpdater *ik);
  void destroy();
  void update(f32 delta);
  void setEnable(bool isEnable, f32 frame, bool isNoSpine);
  void setTargetPos(const mm::Vec3 &position);

private:
  gf::GF_OBJ_HANDLE *handle;
  CharaIKUpdater *ik;
  u32 flags;
  mm::mtl::FixedVector<Request, REQUEST_COUNT> requests;
  mm::Vec3 tar;
  mm::Vec3 startTar;
  mm::Vec3 targetPos;
  AnmF32 moveAnm;
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
      flags |= flag;
    } else {
      flags &= ~flag;
    }
  }

  gf::GF_OBJ_HANDLE *handle;
  CharaWeightPlayer *weight;
  u32 flags;
  REQUEST request;
  f32 requestFrame;
  bool isNoSpine;
  mm::Vec3 tar;
  mm::Vec3 startTar;
  mm::Vec3 targetPos;
  AnmF32 weightAnm;
  AnmF32 moveAnm;
  f32 aimmotWeights[AIMMOT_COUNT];
};

static_assert(sizeof(CharaTarPlayerMot) == 0x2a0, "");

} // namespace event
