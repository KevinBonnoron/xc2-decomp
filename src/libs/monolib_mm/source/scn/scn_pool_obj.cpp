#include "ml/scn_pool_obj.h"

#include "ml/scn_obj.h"
#include "ml/scn_obj_light.h"

namespace ml {

ScnPoolObj::~ScnPoolObj() {
  {
    CS lock(unknown10);
  }
  release(1);
  release(2);
  release(3);
  release(4);
  release(5);
  release(6);
  for (reslist<ScnObj *>::Node *node = unknown1e8.begin(); node != unknown1e8.end(); node = node->getNext()) {
    if (node->value != nullptr) {
      delete node->value;
    }
  }
}

void ScnPoolObj::deleteObj() {
  for (u16 type = 0; type < 7; type++) {
    release(type);
  }
}

void ScnPoolObj::update() {
  CS lock(unknown10);
  for (reslist<ScnObj *>::Node *node = unknown68.begin(); node != unknown68.end(); node = node->getNext()) {
    if (!node->value->unknown12) {
      node->value->update();
    }
  }
  for (reslist<ScnObj *>::Node *node = unknowna8.begin(); node != unknowna8.end(); node = node->getNext()) {
    if (!node->value->unknown12) {
      node->value->update();
    }
  }
}

void ScnPoolObj::renderDebug(DebDraw *debDraw) {
  CS lock(unknown10);
  for (reslist<ScnObj *>::Node *node = unknown68.begin(); node != unknown68.end(); node = node->getNext()) {
    if (!node->value->unknown12) {
      node->value->renderDebug(debDraw);
    }
  }
  for (reslist<ScnObj *>::Node *node = unknowna8.begin(); node != unknowna8.end(); node = node->getNext()) {
    if (!node->value->unknown12) {
      node->value->renderDebug(debDraw);
    }
  }
}

bool ScnPoolObj::isValidInsert(u16 type) const {
  CS lock(unknown38);
  const reslist<ScnObj *> *list = getList(type);
  return list->m_capacity > list->m_size;
}

bool ScnPoolObj::isExistLgtEnv() const {
  CS lock(unknown38);
  bool isExist = false;
  for (reslist<ScnObj *>::Node *node = unknown128.begin(); node != unknown128.end(); node = node->getNext()) {
    isExist |= static_cast<ScnObjLight *>(node->value)->isEnv();
  }
  return isExist;
}

const reslist<ScnObj *> *ScnPoolObj::getList(u16 type) const {
  switch (type) {
  case ScnObj::TYPE_MODEL:
    return &unknowna8;
  case ScnObj::TYPE_CAM:
    return &unknown68;
  case 3:
    return &unknowne8;
  case ScnObj::TYPE_LIGHT:
    return &unknown128;
  case ScnObj::TYPE_IBL:
    return &unknown168;
  case ScnObj::TYPE_CLIP:
    return &unknown1a8;
  default:
    return nullptr;
  }
}

reslist<ScnObj *> *ScnPoolObj::getList(u16 type) {
  switch (type) {
  case ScnObj::TYPE_MODEL:
    return &unknowna8;
  case ScnObj::TYPE_CAM:
    return &unknown68;
  case 3:
    return &unknowne8;
  case ScnObj::TYPE_LIGHT:
    return &unknown128;
  case ScnObj::TYPE_IBL:
    return &unknown168;
  case ScnObj::TYPE_CLIP:
    return &unknown1a8;
  default:
    return nullptr;
  }
}

bool ScnPoolObj::insert(ScnObj *obj) {
  CS lock(unknown10);
  if (isValidInsert(obj->unknown10)) {
    CS listLock(unknown38);
    getList(obj->unknown10)->push_back(obj);
    return true;
  }
  return false;
}

} // namespace ml
