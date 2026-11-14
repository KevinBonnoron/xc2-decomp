#pragma once
#include "event/i_manager.h"
#include "event/model_obj.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class ModelManager : public IManager, public mm::mtl::Singleton<ModelManager> {
public:
  static constexpr u32 MODEL_UNKNOWN_1024 = 1024; // Inferred role: model count; original name unknown.

  ModelManager();
  virtual ~ModelManager() {}
  void update();
  void render();
  ModelObj *createModel(int index);
  ModelObj *createModel(const char *path, bool isPriority, u32 id, int index);
  ModelObj *createModel(const char *path, const ModelObj::DESC &desc, bool isPriority, u32 id, int index);
  ModelObj *createModel(MODEL_TYPE type, u32 modelId, const ModelObj::OPTION &option, bool isPriority, u32 id, int index);
  ModelObj *searchModel(u32 index);
  ModelObj *searchModel(u32 index, const char *path, bool isPriority, u32 id);
  ModelObj *searchModel(u32 index, const char *path, const ModelObj::DESC &desc, bool isPriority, u32 id);
  ModelObj *searchModel(u32 index, MODEL_TYPE type, u32 modelId, const ModelObj::OPTION &option, bool isPriority, u32 id);
  void destroyModel(ModelObj *model, int index);
  virtual void OnEventProc(MSG_TYPE type);

private:
  mm::mtl::FixedVector<ModelObj *, MODEL_UNKNOWN_1024> unknown10; // Inferred role: models; original member name unknown.
};

static_assert(sizeof(ModelManager) == 0x2018, "");

} // namespace event
