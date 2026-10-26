#include "event/model_manager.h"

#include <stddef.h>

#include "event/model_obj.h"

namespace event {

ModelManager::ModelManager() {}

void ModelManager::update() {
  for (u32 i = 0; i < unknown10.size(); i++) {
    unknown10[i]->update();
  }
}

void ModelManager::OnEventProc(MSG_TYPE type) {
  if (type == MSG_TYPE_UPDATE && !unknown10.empty()) {
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

} // namespace event
