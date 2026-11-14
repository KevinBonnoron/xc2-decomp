#include "ml/scn_pool_obj.h"

#include "ml/scn.h"
#include "ml/scn_obj.h"
#include "ml/scn_obj_light.h"
#include "mtl/alloc_handle.h"

#include <algorithm>

namespace ml {

ScnPoolObj::ScnPoolObj(Scn *scn) : unknown60(scn), unknown228(0) {
  unknown68.create(10, scn->unknown64);
  unknowna8.create(0x200, scn->unknown64);
  unknowne8.create(0x200, scn->unknown64);
  unknown128.create(0x10, scn->unknown64);
  unknown168.create(0x40, scn->unknown64);
  unknown1a8.create(8, scn->unknown64);
  unknown1e8.create(0x200, scn->unknown64);
}

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
    if (!node->value->m_delete) {
      node->value->update();
    }
  }
  for (reslist<ScnObj *>::Node *node = unknowna8.begin(); node != unknowna8.end(); node = node->getNext()) {
    if (!node->value->m_delete) {
      node->value->update();
    }
  }
}

void ScnPoolObj::renderDebug(DebDraw *debDraw) {
  CS lock(unknown10);
  for (reslist<ScnObj *>::Node *node = unknown68.begin(); node != unknown68.end(); node = node->getNext()) {
    if (!node->value->m_delete) {
      node->value->renderDebug(debDraw);
    }
  }
  for (reslist<ScnObj *>::Node *node = unknowna8.begin(); node != unknowna8.end(); node = node->getNext()) {
    if (!node->value->m_delete) {
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
  case ScnObj::TYPE_UNKNOWN_1:
    return &unknowna8;
  case ScnObj::TYPE_UNKNOWN_2:
    return &unknown68;
  case 3:
    return &unknowne8;
  case ScnObj::TYPE_UNKNOWN_4:
    return &unknown128;
  case ScnObj::TYPE_UNKNOWN_5:
    return &unknown168;
  case ScnObj::TYPE_UNKNOWN_6:
    return &unknown1a8;
  default:
    return nullptr;
  }
}

reslist<ScnObj *> *ScnPoolObj::getList(u16 type) {
  switch (type) {
  case ScnObj::TYPE_UNKNOWN_1:
    return &unknowna8;
  case ScnObj::TYPE_UNKNOWN_2:
    return &unknown68;
  case 3:
    return &unknowne8;
  case ScnObj::TYPE_UNKNOWN_4:
    return &unknown128;
  case ScnObj::TYPE_UNKNOWN_5:
    return &unknown168;
  case ScnObj::TYPE_UNKNOWN_6:
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

void ScnPoolObj::tail() {
  CS lock(unknown10);
  CS listLock(unknown38);
  for (reslist<ScnObj *>::Node *node = unknown128.begin(); node != unknown128.end(); node = node->getNext()) {
    if (!node->value->m_delete) {
      node->value->tail();
    }
  }
  for (reslist<ScnObj *>::Node *node = unknowna8.begin(); node != unknowna8.end(); node = node->getNext()) {
    if (!node->value->m_delete) {
      node->value->tail();
    }
  }
  reslist<ScnObj *>::iterator it = unknown1e8.begin();
  while (it != unknown1e8.end()) {
    ScnObj *obj = *it;
    unknown1e8.erase(it++);
    if (obj->m_delete) {
      reslist<ScnObj *> *list = getList(obj->unknown10);
      reslist<ScnObj *>::iterator found = std::find<reslist<ScnObj *>::iterator, ScnObj *>(list->begin(), list->end(), obj);
      if (found != list->end()) {
        list->erase(found);
      }
      delete obj;
    }
  }
}

void ScnPoolObj::apply() {
  CS lock(unknown10);
  for (reslist<ScnObj *>::Node *node = unknown68.begin(); node != unknown68.end(); node = node->getNext()) {
    node->value->apply();
  }
  for (reslist<ScnObj *>::Node *node = unknown128.begin(); node != unknown128.end(); node = node->getNext()) {
    node->value->apply();
  }
  for (reslist<ScnObj *>::Node *node = unknown168.begin(); node != unknown168.end(); node = node->getNext()) {
    node->value->apply();
  }
  reslist<ScnObj *>::iterator it = unknowna8.begin();
  while (it != unknowna8.end()) {
    ScnObj *obj = *it++;
    if (!obj->m_delete) {
      obj->apply();
    }
  }
}

ScnObjCam *ScnPoolObj::getCam(const WinView *view) {
  if (view != nullptr) {
    for (reslist<ScnObj *>::Node *node = unknown68.begin(); node != unknown68.end(); node = node->getNext()) {
      ScnObjCam *cam = static_cast<ScnObjCam *>(node->value);
      if (unknown60->unknown28->getView(cam->m_info) == view) {
        return cam;
      }
    }
  }
  return nullptr;
}

} // namespace ml
