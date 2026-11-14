#include "event/model_manager.h"

#include <stddef.h>

#include "event/mdlstm_manager.h"
#include "event/memory_manager.h"
#include "event/model_obj.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

ModelManager::ModelManager() {}

void ModelManager::update() {
  for (u32 i = 0; i < unknown10.size(); i++) {
    unknown10[i]->update();
  }
}

void ModelManager::OnEventProc(MSG_TYPE type) {
  if (type == MSG_TYPE_UNKNOWN_14 && !unknown10.empty()) {
    for (u32 i = 0; i < unknown10.size(); i++) {
      unknown10[i]->update();
    }
  }
}

void ModelManager::render() {}

ModelObj *ModelManager::searchModel(u32 index) {
  for (size_t i = 0; i < unknown10.size(); i++) {
    if (!unknown10[i]->isReserve(static_cast<int>(index)) && unknown10[i]->isSame()) {
      return unknown10[i];
    }
  }
  return nullptr;
}

ModelObj *ModelManager::searchModel(u32 index, const char *path, bool isPriority, u32 id) {
  for (size_t i = 0; i < unknown10.size(); i++) {
    if (!unknown10[i]->isReserve(static_cast<int>(index)) && unknown10[i]->isSame(path, isPriority, id)) {
      return unknown10[i];
    }
  }
  return nullptr;
}

ModelObj *ModelManager::searchModel(u32 index, const char *path, const ModelObj::DESC &desc, bool isPriority, u32 id) {
  for (size_t i = 0; i < unknown10.size(); i++) {
    if (!unknown10[i]->isReserve(index) && unknown10[i]->isSame(path, desc, isPriority, id)) {
      return unknown10[i];
    }
  }
  return nullptr;
}

ModelObj *ModelManager::searchModel(u32 index, MODEL_TYPE type, u32 modelId, const ModelObj::OPTION &option, bool isPriority, u32 id) {
  for (size_t i = 0; i < unknown10.size(); i++) {
    if (!unknown10[i]->isReserve(index) && unknown10[i]->isSame(type, modelId, option, isPriority, id)) {
      return unknown10[i];
    }
  }
  return nullptr;
}

ModelObj *ModelManager::createModel(const char *path, bool isPriority, u32 id, int index) {
  if (mm::mtl::Singleton<MdlstmManager>::getPtr()->isReuseEnable()) {
    ModelObj *found = searchModel(index, path, isPriority, id);
    if (found != nullptr) {
      found->setReserve(index, true);
      return found;
    }
  }
  ModelObj *model = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ModelObj(path, isPriority, id);
  model->setReserve(index, true);
  unknown10.push_back(model);
  return model;
}

ModelObj *ModelManager::createModel(const char *path, const ModelObj::DESC &desc, bool isPriority, u32 id, int index) {
  if (mm::mtl::Singleton<MdlstmManager>::getPtr()->isReuseEnable()) {
    ModelObj *found = searchModel(index, path, desc, isPriority, id);
    if (found != nullptr) {
      found->setReserve(index, true);
      return found;
    }
  }
  ModelObj *model = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ModelObj(path, desc, isPriority, id);
  model->setReserve(index, true);
  unknown10.push_back(model);
  return model;
}

ModelObj *ModelManager::createModel(MODEL_TYPE type, u32 modelId, const ModelObj::OPTION &option, bool isPriority, u32 id, int index) {
  if (mm::mtl::Singleton<MdlstmManager>::getPtr()->isReuseEnable()) {
    ModelObj *found = searchModel(index, type, modelId, option, isPriority, id);
    if (found != nullptr) {
      found->setReserve(index, true);
      return found;
    }
  }
  ModelObj *model = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ModelObj(type, modelId, option, isPriority, id);
  model->setReserve(index, true);
  unknown10.push_back(model);
  return model;
}

ModelObj *ModelManager::createModel(int index) {
  if (mm::mtl::Singleton<MdlstmManager>::getPtr()->isReuseEnable()) {
    ModelObj *found = searchModel(index);
    if (found != nullptr) {
      found->setReserve(index, true);
      return found;
    }
  }
  ModelObj *model = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) ModelObj();
  model->setReserve(index, true);
  unknown10.push_back(model);
  return model;
}

} // namespace event
