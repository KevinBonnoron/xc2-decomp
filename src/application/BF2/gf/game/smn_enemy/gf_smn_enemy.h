#pragma once
#include <stddef.h>

#include <utility>

#include "gf/object/gf_obj_manager.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfRelSmnEnemy : public IGfObjListener {
public:
  struct PopInfo;

  virtual ~GfRelSmnEnemy();
  void removeEnemy(GF_OBJ_HANDLE *handle);
  void listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) override;

  u8 _08[0x78 - 0x08];
  mm::mtl::Vector<std::pair<PopInfo *, GF_OBJ_HANDLE *>> unknown78; // Inferred role: pop enemies; original member name unknown.
  mm::mtl::Vector<GF_OBJ_HANDLE *> unknowna0;                       // Inferred role: wait enemies; original member name unknown.
};

static_assert(offsetof(GfRelSmnEnemy, unknown78) == 0x78, "");
static_assert(offsetof(GfRelSmnEnemy, unknowna0) == 0xa0, "");

class GfSmnEnemyManager : public mm::mtl::PtrSingleton<GfSmnEnemyManager> {
public:
  static void create();
  static void dispose();
  static void update(f32 deltaTime);
};

} // namespace gf
