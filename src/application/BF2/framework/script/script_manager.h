#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "ml/work_event.h"
#include "mm_mtl/array.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {
class FileHandleTh;
} // namespace ml

namespace fw {

struct ScriptEventParam {
  enum State : int;
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

  ~ScriptInfo();
  void destroy();
  void initialize(ScriptManager *manager, int type, void *vm, u32 size);
  void clear();
  void unlink();
  void relink();
  void start();
  void execute();
  void update();
  bool isLoaded() const;
  bool isLoading() const;
  bool isLoadErr() const;
  void sleep();
  void wakeup();
  bool isFinish() const;
  bool isEmpty() const;
  bool isActive() const;

  void *vm;
  u32 size;
  mm::mtl::FixStr<256> path;
  mm::mtl::FixStr<256> name;
  int type;
  ml::FileHandleTh *fileHandle;
  State state;
  u32 flags;
  u8 _230[0x238 - 0x230];
  ScriptManager *manager;
};

static_assert(offsetof(ScriptInfo, path) == 0x14, "");
static_assert(offsetof(ScriptInfo, name) == 0x118, "");
static_assert(offsetof(ScriptInfo, type) == 0x21c, "");
static_assert(offsetof(ScriptInfo, state) == 0x228, "");
static_assert(offsetof(ScriptInfo, manager) == 0x238, "");

class ScriptManager : public ManagerObject, public mm::mtl::PtrSingleton<ScriptManager> {
public:
  ~ScriptManager();
  bool initialize() override;
  bool isScriptCreated(int type) const;
  bool isScriptLoaded(int type) const;
  bool isScriptFree(int type) const;
  void notifyEvent(int type, ScriptEventParam::State state);
  u32 getTypeMax() const;

  u8 _18[0x20 - 0x18];
  mm::mtl::Array<ScriptInfo> scripts;
};

static_assert(offsetof(ScriptManager, scripts) == 0x20, "");

} // namespace fw
