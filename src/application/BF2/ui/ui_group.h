#pragma once
#include <stddef.h>

#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace ui {

class UIInputLayer;
class UIObject;
class UIObjectList;
class UIResource;

class UIGroup {
public:
  struct RootObjInfo;
  struct InputInfo;

  UIGroup();
  virtual ~UIGroup();
  void clean();
  void setup(u32 size);
  void releaseInput(u32 handle);
  void disp(bool disp);
  void updateObject(const fw::UpdateInfo &info);
  void applyObject();
  void registObject(UIObject *object, const char *name, u16 layer, UIResource *resource);
  void initializeObject(const char *name);
  u32 searchObject(const char *name);
  RootObjInfo *getRootInfo(u32 handle);
  void readyReInitialize(u32 handle);
  void terminateObject(const char *name, bool isImmediate);
  void readyTerminate(u32 handle);
  void terminateObjectAll(bool isImmediate);
  void releaseObject(const char *name);
  bool isActiveLayer(u16 layer);
  bool isAssignedLayer(const char *name, u32 layer);
  void attachInput(const char *name, UIInputLayer *input);
  void suspend(bool suspend);
  void resume();
  void reloadText();
  u32 getLoadedResourceSize();
  bool hasObject() const;

  UIObjectList *objectList;
  mm::mtl::Vector<RootObjInfo> rootObjects;
  mm::mtl::Vector<InputInfo> inputs;
  u32 flags;
};

static_assert(offsetof(UIGroup, objectList) == 0x08, "");
static_assert(offsetof(UIGroup, rootObjects) == 0x10, "");
static_assert(offsetof(UIGroup, inputs) == 0x38, "");
static_assert(offsetof(UIGroup, flags) == 0x60, "");
static_assert(sizeof(UIGroup) == 0x68, "");

} // namespace ui
