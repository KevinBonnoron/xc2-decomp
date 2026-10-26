#pragma once
#include <stddef.h>

#include "dr/dr_man.h"
#include "framework/manager_object.h"
#include "ml/work_event.h"
#include "mm_mtl/array.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ml {
class FileHandleTh;
} // namespace ml

namespace fw {

struct ScriptEventParam {
  enum State : int;

  int unknown00;   // Inferred role: script type; original member name unknown.
  State unknown04; // Inferred role: state; original member name unknown.
};

static_assert(sizeof(ScriptEventParam) == 0x8, "");

class IScriptEvent {
public:
  virtual ~IScriptEvent();
  virtual void scriptEvent(ScriptEventParam &param);
};

class ScriptManager;

class ScriptInfo : public ml::IWorkEvent {
public:
  enum State {
    STATE_EMPTY = 0,
    STATE_LOADED = 1,
    STATE_FINISH = 3,
  };

  static const u32 FLAG_LOADING = 1 << 0;
  static const u32 FLAG_LOADED = 1 << 1;
  static const u32 FLAG_STARTED = 1 << 2;
  static const u32 FLAG_LINKED = 1 << 3;
  static const u32 FLAG_LOAD_ERROR = 1 << 5;
  static const u32 FLAG_ACTIVE = 1 << 6;

  ScriptInfo();
  ~ScriptInfo() override;
  void initialize(ScriptManager *manager, int type, void *vm, u32 size);
  void clear();
  void unlink();
  void relink();
  void start();
  void execute();
  void update();
  void waitLoad();
  bool OnFileEvent(ml::EventFileTh *event) override;
  bool isLoaded() const;
  bool isLoading() const;
  bool isLoadErr() const;
  void sleep();
  void wakeup();
  bool isFinish() const;
  bool isEmpty() const;
  bool isActive() const;

  void *unknown08;                 // Inferred role: vm; original member name unknown.
  u32 unknown10;                   // Inferred role: size; original member name unknown.
  mm::mtl::FixStr<256> unknown14;  // Inferred role: path; original member name unknown.
  mm::mtl::FixStr<256> unknown118; // Inferred role: name; original member name unknown.
  int unknown21c;                  // Inferred role: type; original member name unknown.
  ml::FileHandleTh *unknown220;    // Inferred role: file handle; original member name unknown.
  State unknown228;                // Inferred role: state; original member name unknown.
  u32 unknown22c;                  // Inferred role: flags; original member name unknown.
  mm::mtl::IAllocator *unknown230; // Inferred role: script memory allocator; original member name unknown.
  ScriptManager *unknown238;       // Inferred role: manager; original member name unknown.
};

static_assert(offsetof(ScriptInfo, unknown14) == 0x14, "");
static_assert(offsetof(ScriptInfo, unknown118) == 0x118, "");
static_assert(offsetof(ScriptInfo, unknown21c) == 0x21c, "");
static_assert(offsetof(ScriptInfo, unknown228) == 0x228, "");
static_assert(offsetof(ScriptInfo, unknown230) == 0x230, "");
static_assert(offsetof(ScriptInfo, unknown238) == 0x238, "");

class ScriptManager : public ManagerObject, public mm::mtl::PtrSingleton<ScriptManager> {
public:
  ~ScriptManager();
  bool initialize() override;
  void createScript(int type, mm::mtl::IAllocator *allocator, size_t size);
  void destroyScript(int type, bool isForce);
  bool isScriptCreated(int type) const;
  bool isScriptLoaded(int type) const;
  bool isScriptFree(int type) const;
  void removeEvent(IScriptEvent *event);
  void loadScript(int type, const char *name, ml::FILE_PRIO priority);
  void notifyEvent(int type, ScriptEventParam::State state);
  u32 getTypeMax() const;

  u8 _18[0x20 - 0x18];
  mm::mtl::Array<ScriptInfo> unknown20;              // Inferred role: scripts; original member name unknown.
  mm::mtl::FixedQueue<IScriptEvent *, 32> unknown38; // Inferred role: events; original member name unknown.
};

static_assert(offsetof(ScriptManager, unknown20) == 0x20, "");
static_assert(offsetof(ScriptManager, unknown38) == 0x38, "");
static_assert(sizeof(ScriptManager) == 0x148, "");

} // namespace fw
