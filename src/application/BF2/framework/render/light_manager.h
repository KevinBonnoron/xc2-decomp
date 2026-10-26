#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {

struct UpdateInfo;
class LightObject;

class LightManager : public ManagerObject, public mm::mtl::PtrSingleton<LightManager> {
public:
  static const u32 LAYER_MAX = 32;

  struct Group {
    mm::mtl::IntrusiveList<LightObject> unknown00; // Inferred role: lights; original member name unknown.
  };

  virtual void update(const UpdateInfo &info, u32 layer);

  mm::mtl::FixedArray<Group, LAYER_MAX> unknown18; // Inferred role: groups; original member name unknown.
};

static_assert(sizeof(LightManager::Group) == 0x18, "");
static_assert(offsetof(LightManager, unknown18) == 0x18, "");

} // namespace fw
