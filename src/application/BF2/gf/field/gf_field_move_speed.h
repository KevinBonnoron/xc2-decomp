#pragma once
#include <stddef.h>

#include "gf/gf_tween.h"
#include "gf/object/gf_obj_handle.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
class GfComAsm;

class GfFieldMoveSpeed {
public:
  void dispose();
  GfComAsm *getComAsm() const;
  void setSpeedKmph(f32 speed, f32 time);

  GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
  f32 unknown08;            // Role and original member name unknown.
  f32 unknown0c;            // Role and original member name unknown.
  f32 unknown10;            // Role and original member name unknown.
  u8 _14[0x20 - 0x14];
  f32 unknown20; // Role and original member name unknown.
  f32 unknown24; // Role and original member name unknown.
  f32 unknown28; // Role and original member name unknown.
  f32 unknown2c; // Role and original member name unknown.
};

static_assert(offsetof(GfFieldMoveSpeed, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldMoveSpeed, unknown10) == 0x10, "");
static_assert(offsetof(GfFieldMoveSpeed, unknown20) == 0x20, "");
static_assert(offsetof(GfFieldMoveSpeed, unknown2c) == 0x2c, "");

class GfEnemyFieldMoveSpeed {
public:
  struct CreateInfo {
    GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
  };

  GfEnemyFieldMoveSpeed(const CreateInfo *info = nullptr);
  ~GfEnemyFieldMoveSpeed() { dispose(); }
  void create(const CreateInfo &info);
  void dispose() { unknown00 = INVALID_HANDLE; }
  GfComAsm *getComAsm() const;
  void setSpeedKmph(f32 speed, f32 time);
  void update(f32 deltaTime);

  static const char *s_V_speed;

  GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
  f32 unknown08;            // Role and original member name unknown.
  f32 unknown0c;            // Role and original member name unknown.
  f32 unknown10;            // Role and original member name unknown.
  u8 _14[0x18 - 0x14];
  GfSpeedTween unknown18; // Inferred role: speed tween; original member name unknown.
};

static_assert(offsetof(GfEnemyFieldMoveSpeed, unknown08) == 0x08, "");
static_assert(offsetof(GfEnemyFieldMoveSpeed, unknown10) == 0x10, "");
static_assert(offsetof(GfEnemyFieldMoveSpeed, unknown18) == 0x18, "");
static_assert(sizeof(GfEnemyFieldMoveSpeed) == 0x30, "");

} // namespace gf
