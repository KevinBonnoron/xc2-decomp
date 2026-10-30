#pragma once
#include "event/i_manager.h"
#include "event/outsider_field.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class OutsiderManager : public IManager, public mm::mtl::Singleton<OutsiderManager> {
public:
  enum OBJ_TYPE {
    OBJ_TYPE_NONE = 0,
    OBJ_TYPE_NPC = 1 << 0,
    OBJ_TYPE_ROUTED_NPC = 1 << 1,
    OBJ_TYPE_ENEMY = 1 << 2,
    OBJ_TYPE_ROUTED_ENEMY = 1 << 3,
    OBJ_TYPE_ROUTED_MAP_OBJ = 1 << 4,
    OBJ_TYPE_MOB = 1 << 5,
    OBJ_TYPE_ROUTED_MOB = 1 << 6,
  };

  enum {
    FLAG_ACTIVE = 1 << 0,
  };

  enum {
    DISP_FLAG_DISP = 0,
  };

  OutsiderManager();
  virtual ~OutsiderManager() {}
  void clear();
  void update(bool isHide);
  void update();
  void updateSub(bool isHide, gmk::GmkType type);
  void updateSub(bool isHide, gf::GF_OBJ_HANDLE *handle);
  void render();
  void defineTgt(OBJ_TYPE targets);
  void defineFld(OutsiderField::TYPE type, const mm::Vec3 &pos, f32 radius);
  void setActive(bool isActive);
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  mm::mtl::unknown027<32> unknown10; // Inferred role: disp flags; original member name unknown.
  u32 unknown14;                     // Inferred role: flags; original member name unknown.
  OBJ_TYPE unknown18;                // Inferred role: targets; original member name unknown.
  OutsiderField unknown20;           // Inferred role: field; original member name unknown.
};

static_assert(sizeof(OutsiderManager) == 0x70, "");

} // namespace event
