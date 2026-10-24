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

  UIObjectList *unknown08;                // Inferred role: object list; original member name unknown.
  mm::mtl::Vector<RootObjInfo> unknown10; // Inferred role: root objects; original member name unknown.
  mm::mtl::Vector<InputInfo> unknown38;   // Inferred role: inputs; original member name unknown.
  u32 unknown60;                          // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(UIGroup, unknown08) == 0x08, "");
static_assert(offsetof(UIGroup, unknown10) == 0x10, "");
static_assert(offsetof(UIGroup, unknown38) == 0x38, "");
static_assert(offsetof(UIGroup, unknown60) == 0x60, "");
static_assert(sizeof(UIGroup) == 0x68, "");

} // namespace ui
