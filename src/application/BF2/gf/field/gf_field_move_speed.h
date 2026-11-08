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
  struct CreateInfo {
    GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
  };

  GfFieldMoveSpeed(const CreateInfo *info = nullptr);
  ~GfFieldMoveSpeed() { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  GfComAsm *getComAsm() const;
  void setSpeedKmph(f32 speed, f32 time);

  GF_OBJ_HANDLE *unknown00 = INVALID_HANDLE; // Inferred role: object; original member name unknown.
  f32 unknown08 = 12.0f;                     // Inferred role: minimum speed; original member name unknown.
  f32 unknown0c = 28.0f;                     // Inferred role: maximum speed; original member name unknown.
  f32 unknown10 = 0.0f;                      // Inferred role: current speed; original member name unknown.
  TGfTween<f32> unknown18;                   // Inferred role: speed tween; original member name unknown.
};

static_assert(offsetof(GfFieldMoveSpeed, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldMoveSpeed, unknown10) == 0x10, "");
static_assert(offsetof(GfFieldMoveSpeed, unknown18) == 0x18, "");
static_assert(sizeof(GfFieldMoveSpeed) == 0x30, "");

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

  GF_OBJ_HANDLE *unknown00 = INVALID_HANDLE; // Inferred role: object; original member name unknown.
  f32 unknown08 = 12.0f;                     // Inferred role: minimum speed; original member name unknown.
  f32 unknown0c = 28.0f;                     // Inferred role: maximum speed; original member name unknown.
  f32 unknown10 = 0.0f;                      // Inferred role: current speed; original member name unknown.
  GfSpeedTween unknown18;                    // Inferred role: speed tween; original member name unknown.
};

static_assert(offsetof(GfEnemyFieldMoveSpeed, unknown08) == 0x08, "");
static_assert(offsetof(GfEnemyFieldMoveSpeed, unknown10) == 0x10, "");
static_assert(offsetof(GfEnemyFieldMoveSpeed, unknown18) == 0x18, "");
static_assert(sizeof(GfEnemyFieldMoveSpeed) == 0x30, "");

} // namespace gf
