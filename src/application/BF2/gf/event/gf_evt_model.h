#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw
namespace mm {
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
};

static_assert(offsetof(GfEvtModel, type) == 0x18, "");

} // namespace gf
