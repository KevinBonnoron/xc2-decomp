#include "ui/ui_group.h"

#include "framework/memory/framework_memory.h"
#include "ui/input/ui_input_layer.h"
#include "ui/input/ui_input_manager.h"
#include "ui/object/ui_layout_object.h"
#include "ui/ui_displayinfo.h"
#include "ui/ui_object.h"
#include "ui/ui_object_list.h"
#include "ui/ui_resource.h"
#include "ui/ui_util.h"

namespace ui {

UIGroup::UIGroup() : unknown08(nullptr), unknown10(), unknown38(), unknown60(0) {}

UIGroup::~UIGroup() { clean(); }

void UIGroup::setup(u32 size) {
  if (size == 0) {
    return;
  }
  delete unknown08;
  unknown08 = nullptr;
// __LINE__ is the line argument of the operator new call.
#line 60
  unknown08 = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectList;
  unknown10.setAllocator(UIUtil::getProgAllocator());
  unknown10.reserve(size);
  unknown38.setAllocator(UIUtil::getProgAllocator());
  unknown38.reserve(size);
}

void UIGroup::disp(bool disp) {
  if (disp) {
    unknown60 &= ~4;
  } else {
    unknown60 |= 4;
  }
}

bool UIGroup::hasObject() const { return unknown10.size() != 0; }

int UIGroup::registObject(UIObject *object, const char *name, u16 layer, UIResource *resource) {
  if (unknown08 == nullptr) {
    return 0;
  }

  RootObjInfo info;
  info.unknown44 = unknown08->regist(object, name);
  if (info.unknown44 == 0) {
    return 0;
  }

  info.unknown00 = name;
  info.unknown48 = layer;
  info.unknown50 = resource;
  info.unknown5a = false;
  info.unknown5b = false;
  info.unknown58 = 0;
  resource->addRef();
  unknown10.push_back(info);
  return info.unknown44;
}

void UIGroup::applyObject() {
  if (unknown08 == nullptr || (unknown60 & 2) != 0) {
    return;
  }

  if ((unknown60 & 4) != 0) {
    for (RootObjInfo *it = unknown10.begin(); it != unknown10.end(); ++it) {
      UIObject *object = UIUtil::getObject(it->unknown44);
      it->unknown5c = object->unknown50.unknown08;
      object->unknown50.setDisp(false);
    }
  }

  unknown08->apply();

  if ((unknown60 & 4) != 0) {
    for (RootObjInfo *it = unknown10.begin(); it != unknown10.end(); ++it) {
      UIObject *object = UIUtil::getObject(it->unknown44);
      object->unknown50.setDisp(it->unknown5c);
    }
  }
}

u32 UIGroup::searchObject(const char *name) { return unknown08 != nullptr ? unknown08->search(name) : 0; }

bool UIGroup::isActiveLayer(u16 layer) {
  for (RootObjInfo *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (it->unknown48 == layer) {
      return true;
    }
  }
  return false;
}

UIGroup::RootObjInfo *UIGroup::getRootInfo(u32 handle) {
  for (RootObjInfo *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (it->unknown44 == handle) {
      return it;
    }
  }
  return nullptr;
}

bool UIGroup::isAssignedLayer(const char *name, u32 layer) {
  u32 handle = searchObject(name);
  if (handle == 0) {
    return false;
  }
  RootObjInfo *info = getRootInfo(handle);
  if (info == nullptr) {
    return false;
  }
  return info->unknown48 == layer;
}

void UIGroup::initializeObject(const char *name) {
  u32 handle = searchObject(name);
  if (handle == 0) {
    return;
  }
  RootObjInfo *info = getRootInfo(handle);
  if (info == nullptr) {
    return;
  }
  readyReInitialize(handle);
  info->unknown5a = false;
  info->unknown5b = false;
}

void UIGroup::terminateObject(const char *name, bool isImmediate) {
  u32 handle = searchObject(name);
  if (handle == 0) {
    return;
  }
  RootObjInfo *info = getRootInfo(handle);
  if (info == nullptr) {
    return;
  }
  releaseInput(handle);
  readyTerminate(handle);
  info->unknown5a = true;
  info->unknown5b = isImmediate;
}

void UIGroup::releaseObject(const char *name) {
  u32 handle = searchObject(name);
  if (handle == 0) {
    return;
  }
  RootObjInfo *info = getRootInfo(handle);
  if (info == nullptr) {
    return;
  }
  info->unknown5b = true;
}

void UIGroup::terminateObjectAll(bool isImmediate) {
  for (RootObjInfo *it = unknown10.begin(); it != unknown10.end(); ++it) {
    releaseInput(it->unknown44);
    readyTerminate(it->unknown44);
    it->unknown5a = true;
    it->unknown5b = isImmediate;
  }
}

void UIGroup::suspend(bool suspend) {
  // The game sets bit 0 in both cases; only a suspension also sets bit 1.
  if (suspend) {
    unknown60 |= 3;
  } else {
    unknown60 |= 1;
  }
  for (InputInfo *it = unknown38.begin(); it != unknown38.end(); ++it) {
    if (it->unknown08 != 0) {
      UIInputManager::get()->releaseInputLayer(it->unknown08);
      it->unknown08 = 0;
    }
  }
}

void UIGroup::releaseInput(u32 handle) {
  for (InputInfo *it = unknown38.begin(); it != unknown38.end();) {
    if (it->unknown0c == handle) {
      if (it->unknown08 != 0) {
        UIInputManager::get()->releaseInputLayer(it->unknown08);
      }
      if (it->unknown00 != nullptr) {
        it->unknown00->release();
        it->unknown00 = nullptr;
      }
      it = unknown38.erase(it);
    } else {
      ++it;
    }
  }
}

void UIGroup::reloadText() {
  for (RootObjInfo *it = unknown10.begin(); it != unknown10.end(); ++it) {
    UIUtil::getLayoutObject(it->unknown44)->reloadText();
  }
}

} // namespace ui
