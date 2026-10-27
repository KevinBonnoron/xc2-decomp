#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {

class EffectPack;
class ModelObject;
struct UpdateInfo;

class EffectLodManager : public mm::mtl::PtrSingleton<EffectLodManager> {
public:
  EffectLodManager();
  ~EffectLodManager() override;
  void init(ModelObject *modelObject, EffectPack *pack);
  void term();
  void update(const UpdateInfo &info);

  EffectPack *unknown08;                // Inferred role: effect pack; original member name unknown.
  ModelObject *unknown10;               // Inferred role: model; original member name unknown.
  mm::mtl::IntrusiveListBase unknown18; // Inferred role: lod nodes; original member name unknown.
  f32 unknown30;                        // Inferred role: lod scale; original member name unknown.
};

static_assert(offsetof(EffectLodManager, unknown08) == 0x08, "");
static_assert(offsetof(EffectLodManager, unknown10) == 0x10, "");
static_assert(offsetof(EffectLodManager, unknown18) == 0x18, "");
static_assert(offsetof(EffectLodManager, unknown30) == 0x30, "");
static_assert(sizeof(EffectLodManager) == 0x38, "");

} // namespace fw
