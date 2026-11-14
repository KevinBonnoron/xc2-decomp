#pragma once
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
class GfObj;
} // namespace gf

namespace event {

class CharaIKUpdater {
public:
  enum FOOT_TYPE {
    FOOT_TYPE_UNKNOWN_0 = 0, // Inferred role: 0; original name unknown.
    FOOT_TYPE_UNKNOWN_1 = 1, // Inferred role: 1; original name unknown.
    FOOT_TYPE_UNKNOWN_2 = 2, // Inferred role: 2; original name unknown.
  };

  enum {
    FLAG_UNKNOWN_0 = 0,   // Inferred role: all ik flag; original name unknown.
    FLAG_UNKNOWN_1 = 1,   // Inferred role: foot ik 0 flag; original name unknown.
    FLAG_UNKNOWN_2 = 2,   // Inferred role: foot ik 1 flag; original name unknown.
    FLAG_UNKNOWN_3 = 3,   // Inferred role: foot ik 2 flag; original name unknown.
    FLAG_UNKNOWN_4 = 4,   // Inferred role: target ik flag; original name unknown.
    FLAG_UNKNOWN_5 = 5,   // Inferred role: target ik no spine flag; original name unknown.
    FLAG_UNKNOWN_6 = 6,   // Inferred role: lens ik flag; original name unknown.
    FLAG_UNKNOWN_32 = 32, // Inferred role: max flag; original name unknown.
  };

  enum {
    REQUEST_UNKNOWN_0 = 0,   // Inferred role: all ik; original name unknown.
    REQUEST_UNKNOWN_1 = 1,   // Inferred role: foot ik; original name unknown.
    REQUEST_UNKNOWN_2 = 2,   // Inferred role: target ik; original name unknown.
    REQUEST_UNKNOWN_3 = 3,   // Inferred role: target pos; original name unknown.
    REQUEST_UNKNOWN_4 = 4,   // Inferred role: lens ik; original name unknown.
    REQUEST_UNKNOWN_32 = 32, // Inferred role: max; original name unknown.
  };

  CharaIKUpdater();
  virtual ~CharaIKUpdater() {}
  void create(gf::GF_OBJ_HANDLE *handle);
  void destroy();
  void update(f32 delta);
  void render(const mm::Vec3 &position, f32 height);
  void setAllIK(bool isEnable);
  void setFootIK(bool isEnable, FOOT_TYPE type);
  void setTargetIK(bool isEnable, f32 frame, bool isNoSpine);
  void setTargetPos(const mm::Vec3 &position);
  void setLensIK(bool isEnable, f32 x, f32 y);
  static bool checkField(gf::GfObj *obj);

private:
  mm::mtl::unknown027<FLAG_UNKNOWN_32> unknown08;    // Inferred role: flags; original member name unknown.
  mm::mtl::unknown027<REQUEST_UNKNOWN_32> unknown0c; // Inferred role: requests; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10;                      // Inferred role: handle; original member name unknown.
  f32 unknown18;                                     // Inferred role: target frame; original member name unknown.
  mm::Vec3 unknown20;                                // Inferred role: target pos; original member name unknown.
  mm::Vec2 unknown30;                                // Inferred role: lens move; original member name unknown.
  mm::Vec2 unknown40;                                // Inferred role: lens translate min; original member name unknown.
  mm::Vec2 unknown50;                                // Inferred role: lens translate max; original member name unknown.
  mm::Vec2 unknown60;                                // Inferred role: lens rotate min; original member name unknown.
  mm::Vec2 unknown70;                                // Inferred role: lens rotate max; original member name unknown.
};

static_assert(sizeof(CharaIKUpdater) == 0x80, "");

} // namespace event
