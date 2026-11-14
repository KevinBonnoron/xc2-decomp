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
    OBJ_TYPE_UNKNOWN_0 = 0,        // Inferred role: none; original name unknown.
    OBJ_TYPE_UNKNOWN_0_2 = 1 << 0, // Inferred role: npc; original name unknown.
    OBJ_TYPE_UNKNOWN_1 = 1 << 1,   // Inferred role: routed npc; original name unknown.
    OBJ_TYPE_UNKNOWN_2 = 1 << 2,   // Inferred role: enemy; original name unknown.
    OBJ_TYPE_UNKNOWN_3 = 1 << 3,   // Inferred role: routed enemy; original name unknown.
    OBJ_TYPE_UNKNOWN_4 = 1 << 4,   // Inferred role: routed map obj; original name unknown.
    OBJ_TYPE_UNKNOWN_5 = 1 << 5,   // Inferred role: mob; original name unknown.
    OBJ_TYPE_UNKNOWN_6 = 1 << 6,   // Inferred role: routed mob; original name unknown.
  };

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: active flag; original name unknown.
  };

  enum {
    DISP_FLAG_UNKNOWN_0 = 0, // Inferred role: disp flag; original name unknown.
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
