#pragma once
#include <stddef.h>

#include "dir/dir_list.h"
#include "types.h"

namespace ml {
class WinView;
} // namespace ml

namespace dir {

class VwProcessMan;

// Layout evidence: VwProcess::VwProcess 0x71001415e4, VwProcess::Regist 0x7100141754 and the vtable _ZTVN3dir9VwProcessE.
class VwProcess : public ChildListNode {
public:
  VwProcess();
  ~VwProcess() override;
  virtual void Init() {}
  virtual void Term() {}
  virtual void Move() {}
  virtual void Draw() {}
  virtual void Tail() {}
  void Regist(VwProcess *parent, bool insertTop, const char *name, int priority);
  void Remove();
  bool HasChild() const;
  void Delete();

  u8 _48[0x58 - 0x48];
  u8 unknown58; // Inferred role: registered; original member name unknown.
  u8 unknown59; // Inferred role: set by Delete, the process is destroyed by the next VwProcessMan::Delete; original member name unknown.
  u8 unknown5a; // Inferred role: skips Move; original member name unknown.
  u8 unknown5b; // Inferred role: skips Draw and Tail; original member name unknown.
  u8 _5c[0x60 - 0x5c];
  VwProcessMan *unknown60; // Inferred role: manager owning the process; original member name unknown.
};

static_assert(offsetof(VwProcess, unknown58) == 0x58, "");
static_assert(offsetof(VwProcess, unknown59) == 0x59, "");
static_assert(offsetof(VwProcess, unknown5a) == 0x5a, "");
static_assert(offsetof(VwProcess, unknown5b) == 0x5b, "");
static_assert(offsetof(VwProcess, unknown60) == 0x60, "");
static_assert(sizeof(VwProcess) == 0x68, "");

// Layout evidence: VwProcessMan::VwProcessMan 0x71001418b4 and the vtable _ZTVN3dir12VwProcessManE.
class VwProcessMan {
public:
  VwProcessMan();
  virtual ~VwProcessMan();
  void Init();
  void Term();
  void Reset();
  void Delete();
  void Move();
  void Draw();
  void Tail();

  u8 unknown08;                          // Inferred role: initialized; original member name unknown.
  TChildListHeader<VwProcess> unknown10; // Inferred role: processes that are not registered; original member name unknown.
  u8 _20[0x30 - 0x20];
  TChildListHeader<VwProcess> unknown30; // Inferred role: registered root processes; original member name unknown.
};

static_assert(offsetof(VwProcessMan, unknown08) == 0x08, "");
static_assert(offsetof(VwProcessMan, unknown10) == 0x10, "");
static_assert(offsetof(VwProcessMan, unknown30) == 0x30, "");
static_assert(sizeof(VwProcessMan) == 0x40, "");

// Layout evidence: VwTaskRoot::Reset 0x7100141eb4 and VwTaskManager::Create (the object is 0x70 bytes). The constructor
// does not store a vtable of its own and VwTaskManager::Release destroys it through VwProcessMan::~VwProcessMan
// directly, so the manager is a member at offset 0 rather than a base class.
class VwTaskRoot {
public:
  VwTaskRoot();
  void Release();
  void Reset();
  void Move();
  void Draw();
  void Tail();
  void DebugDraw(ml::WinView *view);
  void DebugDrawRecursive(VwProcess *process, ml::WinView *view, int &depth);

  VwProcessMan unknown00; // Inferred role: process manager; original member name unknown.
  u8 _40[0x50 - 0x40];
  VwProcess *unknown50; // Inferred role: root process; original member name unknown.
  VwProcess *unknown58; // Inferred role: root process; original member name unknown.
  VwProcess *unknown60; // Inferred role: root process; original member name unknown.
  VwProcess *unknown68; // Inferred role: root process; original member name unknown.
};

static_assert(offsetof(VwTaskRoot, unknown50) == 0x50, "");
static_assert(offsetof(VwTaskRoot, unknown68) == 0x68, "");
static_assert(sizeof(VwTaskRoot) == 0x70, "");

class VwTaskManager {
public:
  static VwTaskRoot *Create();
  static void Release(VwTaskRoot *root);
};

} // namespace dir
