#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class ModelObj;

class ModelManager : public IManager, public mm::mtl::Singleton<ModelManager> {
public:
  static constexpr u32 MODEL_COUNT = 1024;

  ModelManager();
  virtual ~ModelManager() {}
  void update();
  void render();
  virtual void OnEventProc(MSG_TYPE type);

private:
  mm::mtl::FixedVector<ModelObj *, MODEL_COUNT> unknown10; // Inferred role: models; original member name unknown.
};

static_assert(sizeof(ModelManager) == 0x2018, "");

} // namespace event
