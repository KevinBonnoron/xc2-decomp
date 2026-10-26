#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
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
  struct RootObjInfo {
    mm::mtl::FixStr<64> unknown00; // Inferred role: name; original member name unknown.
    u32 unknown44;                 // Inferred role: object handle; original member name unknown.
    u16 unknown48;                 // Inferred role: layer; original member name unknown.
    u8 _4a[0x50 - 0x4a];
    UIResource *unknown50; // Inferred role: resource; original member name unknown.
    u16 unknown58;         // Role and original member name unknown.
    bool unknown5a;        // Inferred role: terminated; original member name unknown.
    bool unknown5b;        // Inferred role: immediate; original member name unknown.
    bool unknown5c;        // Inferred role: disp; original member name unknown.
  };
  struct InputInfo {
    UIInputLayer *unknown00; // Inferred role: input layer; original member name unknown.
    u32 unknown08;           // Inferred role: input handle; original member name unknown.
    u32 unknown0c;           // Inferred role: object handle; original member name unknown.
  };

  UIGroup();
  virtual ~UIGroup();
  void clean();
  void setup(u32 size);
  void releaseInput(u32 handle);
  void disp(bool disp);
  void updateObject(const fw::UpdateInfo &info);
  void applyObject();
  int registObject(UIObject *object, const char *name, u16 layer, UIResource *resource);
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

static_assert(offsetof(UIGroup::RootObjInfo, unknown44) == 0x44, "");
static_assert(offsetof(UIGroup::RootObjInfo, unknown48) == 0x48, "");
static_assert(offsetof(UIGroup::RootObjInfo, unknown50) == 0x50, "");
static_assert(offsetof(UIGroup::RootObjInfo, unknown58) == 0x58, "");
static_assert(offsetof(UIGroup::RootObjInfo, unknown5a) == 0x5a, "");
static_assert(sizeof(UIGroup::RootObjInfo) == 0x60, "");
static_assert(sizeof(UIGroup::InputInfo) == 0x10, "");
static_assert(offsetof(UIGroup, unknown08) == 0x08, "");
static_assert(offsetof(UIGroup, unknown10) == 0x10, "");
static_assert(offsetof(UIGroup, unknown38) == 0x38, "");
static_assert(offsetof(UIGroup, unknown60) == 0x60, "");
static_assert(sizeof(UIGroup) == 0x68, "");

} // namespace ui
