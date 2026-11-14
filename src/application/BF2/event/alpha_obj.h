#pragma once
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

enum ALPHA_ATTR {
  ALPHA_ATTR_UNKNOWN_0 = 0, // Inferred role: attribute used by the outsider fade; original enumerator name unknown.
  ALPHA_ATTR_UNKNOWN_1 = 1, // Inferred role: chara; original name unknown.
  ALPHA_ATTR_UNKNOWN_2 = 2, // Inferred role: mdlstm; original name unknown.
  ALPHA_ATTR_UNKNOWN_4 = 4, // Inferred role: count; original name unknown.
};

class AlphaObj {
public:
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: active flag; original name unknown.
  };

  AlphaObj(gf::GF_OBJ_HANDLE *handle);
  virtual ~AlphaObj() {}
  void update();
  void draw(int x, int y);
  void setAlpha(ALPHA_ATTR attr, f32 alpha, f32 belongingAlpha);
  static void setEventAlpha(gf::GF_OBJ_HANDLE *handle, f32 alpha, f32 belongingAlpha);

  bool isActive() const { return (unknown08 & FLAG_UNKNOWN_0) != 0; }
  gf::GF_OBJ_HANDLE *getHandle() const { return unknown10; }

private:
  u32 unknown08;                       // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10;        // Inferred role: handle; original member name unknown.
  f32 unknown18[ALPHA_ATTR_UNKNOWN_4]; // Inferred role: alphas; original member name unknown.
  f32 unknown28[ALPHA_ATTR_UNKNOWN_4]; // Inferred role: belonging alphas; original member name unknown.
  f32 unknown38;                       // Inferred role: alpha; original member name unknown.
  f32 unknown3c;                       // Inferred role: belonging alpha; original member name unknown.
  s32 unknown40;                       // Inferred role: opaque frames; original member name unknown.
};

static_assert(sizeof(AlphaObj) == 0x48, "");

} // namespace event
