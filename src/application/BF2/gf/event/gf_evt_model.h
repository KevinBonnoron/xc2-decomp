#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw
namespace mm {
struct Vec3;
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

enum GF_EVT_MODEL {
  GF_EVT_MODEL_DRIVER = 0,
  GF_EVT_MODEL_BLADE = 1,
  GF_EVT_MODEL_WEAPON = 2,
  GF_EVT_MODEL_EVENT = 3,
  GF_EVT_MODEL_NPC = 4,
  GF_EVT_MODEL_ENEMY = 5,
};

class GfEvtModel {
public:
  virtual ~GfEvtModel();
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual void update(const fw::UpdateInfo &info);
  virtual void setDispWeapon(bool isDisp);
  virtual void setDispWeapon(bool isDispRight, bool isDispLeft);
  virtual GF_OBJ_HANDLE *getWeaponHandleRight() const;
  virtual GF_OBJ_HANDLE *getWeaponHandleLeft() const;
  virtual void setWeaponBattleCommand();
  virtual void setWeaponFieldCommand();
  virtual void setWeaponBattleState();
  virtual void setWeaponFieldState();
  virtual void setWeaponBattleMount();
  virtual void setWeaponFieldMount();

  u8 _08[0x18 - 0x08];
  GF_EVT_MODEL type;
  GF_OBJ_HANDLE *handle;
};

static_assert(offsetof(GfEvtModel, type) == 0x18, "");
static_assert(offsetof(GfEvtModel, handle) == 0x20, "");

class GfEvtModelDriver : public GfEvtModel {
public:
  void playAnimWeaponRightCS(const char *name);
  bool isPlayEndAnimWeaponRightCS();
  void setAnimSpeedWeaponRightCS(f32 speed);
  void playAnimWeaponLeftCS(const char *name);
  bool isPlayEndAnimWeaponLeftCS();
  void setAnimSpeedWeaponLeftCS(f32 speed);
};

class GfEvtModelWeapon : public GfEvtModel {
public:
  static void playAnimCS(GF_OBJ_HANDLE *handle, const char *name);
  static bool isPlayEndAnimCS(GF_OBJ_HANDLE *handle);
  static void setAnimSpeedCS(GF_OBJ_HANDLE *handle, f32 speed);
  void playAnimCS(const char *name);
  bool isPlayEndAnimCS();
  void setAnimSpeedCS(f32 speed);
  void playAnimData(void *data);
};

class GfEvtModelSalvage : public GfEvtModel {
public:
  bool isValid() const;
  void setTransform(const mm::Vec3 &position, f32 rotation);
};

class GfEvtModelBlade : public GfEvtModel {
public:
  void playAnimWeaponRightCS(const char *name);
  bool isPlayEndAnimWeaponRightCS();
  void setAnimSpeedWeaponRightCS(f32 speed);
  void playAnimWeaponLeftCS(const char *name);
  bool isPlayEndAnimWeaponLeftCS();
  void setAnimSpeedWeaponLeftCS(f32 speed);
};

} // namespace gf
