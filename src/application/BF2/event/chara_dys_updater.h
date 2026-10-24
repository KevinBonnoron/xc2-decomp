#pragma once
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaDysUpdater {
public:
  enum {
    FLAG_RESET_DYNAMICS = 0,
    FLAG_RESET_MOVEMENT = 1,
    FLAG_MAX = 32,
  };

  CharaDysUpdater();
  virtual ~CharaDysUpdater() {}
  void create(gf::GF_OBJ_HANDLE *handle);
  void destroy();
  void update(f32 delta);
  static void resetDynamics(gf::GF_OBJ_HANDLE *handle);
  static void resetMovement(gf::GF_OBJ_HANDLE *handle);
  static void setDynamicsBlendWeight(gf::GF_OBJ_HANDLE *handle, f32 weight);
  void resetDynamics(int frame);
  void resetMovement(int frame);
  void setDynamicsBlendWeight(f32 weight);

private:
  mm::mtl::BitFlag<FLAG_MAX> unknown08; // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10;         // Inferred role: handle; original member name unknown.
  int unknown18;                        // Inferred role: reset dynamics frame; original member name unknown.
  int unknown1c;                        // Inferred role: reset movement frame; original member name unknown.
  f32 unknown20;                        // Inferred role: blend weight; original member name unknown.
};

static_assert(sizeof(CharaDysUpdater) == 0x28, "");

} // namespace event
