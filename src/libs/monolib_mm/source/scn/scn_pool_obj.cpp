#include "ml/scn_pool_obj.h"

#include "ml/scn.h"
#include "ml/scn_obj.h"
#include "ml/scn_obj_light.h"
#include "ml/scn_obj_model.h"
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

bool ScnPoolObj::release(ScnObj *obj) {
  CS lock(unknown10);
  CS listLock(unknown38);
  obj->setDelete();
  if (obj->unknown10 == ScnObj::TYPE_UNKNOWN_1) {
    static_cast<ScnObjModel *>(obj)->setDisp(false);
  }
  reslist<ScnObj *>::iterator found = std::find<reslist<ScnObj *>::iterator, ScnObj *>(unknown1e8.begin(), unknown1e8.end(), obj);
  // The game compares the node with the end node as base pointers and inserts at the position found (0x7100740b58): the new node gets
  // next = end, while the links of the position are read through the iterator. With `found == unknown1e8.end()` or push_back every link
  // goes through the end node (76 instructions each time, other registers).
  if (found.unknown00 == unknown1e8.m_end) {
    unknown1e8.insert(found, obj);
  }
  return true;
}

void ScnPoolObj::release(u16 type) {
  CS lock(unknown10);
  if (type != 0) {
    CS listLock(unknown38);
    reslist<ScnObj *> *list = getList(type);
    if (list != nullptr) {
      for (reslist<ScnObj *>::iterator it = list->begin(); it != list->end(); ++it) {
        ScnObj *obj = *it;
        obj->setDelete();
        reslist<ScnObj *>::iterator found = std::find<reslist<ScnObj *>::iterator, ScnObj *>(unknown1e8.begin(), unknown1e8.end(), obj);
        // As release(ScnObj *): the node is compared with the end node as base pointers (0x7100754b28).
        if (found.unknown00 == unknown1e8.m_end) {
          unknown1e8.insert(found, obj);
        }
      }
      list->clear();
    }
  }
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

ScnObjCam *ScnPoolObj::getCam(int screen) {
  CS lock(unknown38);
  for (reslist<ScnObj *>::iterator it = unknown68.begin(); it != unknown68.end(); ++it) {
    ScnObjCam *cam = static_cast<ScnObjCam *>(*it);
    if (cam->m_info == screen) {
      return cam;
    }
  }
  // The released object is read through the iterator each time: the game's own copy of this function (0x7100742a6c) tests the type and the
  // screen with two loads in two blocks, and its inlined copies (ScnCamMan::apply, 0x71007429a0) with one 64-bit load. A local pointer for
  // the object gives the 64-bit load here too (48 instructions against 46).
  for (reslist<ScnObj *>::iterator it = unknown1e8.begin(); it != unknown1e8.end(); ++it) {
    if ((*it)->unknown10 == ScnObj::TYPE_UNKNOWN_2 && static_cast<ScnObjCam *>(*it)->m_info == screen) {
      return static_cast<ScnObjCam *>(*it);
    }
  }
  return nullptr;
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
