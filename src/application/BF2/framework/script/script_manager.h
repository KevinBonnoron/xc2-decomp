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

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ml {
class FileHandleTh;
} // namespace ml

namespace fw {

struct UpdateInfo;

struct ScriptEventParam {
  enum State : int;

  int unknown00;   // Inferred role: script type; original member name unknown.
  State unknown04; // Inferred role: state; original member name unknown.
};

static_assert(sizeof(ScriptEventParam) == 0x8, "");

class IScriptEvent {
public:
  IScriptEvent();
  virtual ~IScriptEvent();
  virtual void scriptEvent(ScriptEventParam &param);
};

class ScriptManager;

class ScriptInfo : public ml::IWorkEvent {
public:
  enum State {
    STATE_UNKNOWN_0 = 0, // Inferred role: empty; original name unknown.
    STATE_UNKNOWN_1 = 1, // Inferred role: loaded; original name unknown.
    STATE_UNKNOWN_2 = 2, // Inferred role: running; original name unknown.
    STATE_UNKNOWN_3 = 3, // Inferred role: finish; original name unknown.
  };

  static const u32 FLAG_UNKNOWN_0 = 1 << 0; // Inferred role: loading; original name unknown.
  static const u32 FLAG_UNKNOWN_1 = 1 << 1; // Inferred role: loaded; original name unknown.
  static const u32 FLAG_UNKNOWN_2 = 1 << 2; // Inferred role: started; original name unknown.
  static const u32 FLAG_UNKNOWN_3 = 1 << 3; // Inferred role: linked; original name unknown.
  static const u32 FLAG_UNKNOWN_5 = 1 << 5; // Inferred role: load error; original name unknown.
  static const u32 FLAG_UNKNOWN_6 = 1 << 6; // Inferred role: active; original name unknown.

  ScriptInfo();
  ~ScriptInfo() override;
  void initialize(ScriptManager *manager, int type, void *vm, u32 size);
  void clear();
  void unlink();
  void relink();
  void load(const mm::mtl::FixStr<256> &path, ml::FILE_PRIO priority);
  void loadFromMemory(const mm::mtl::FixStr<256> &path, const char *data, size_t size);
  void start();
  void destroy();
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
  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
  // Tells whether the script is linked to its vm. ScriptInfo::destroy (1.0.0: 0x710019cf04, 26 instructions) writes the last two zero stores of clear() one by one (str xzr, [x19, #0x228];
  // str xzr, [x19, #0x220] at 0x710019cf58), which it does only when the test is optimised as a function of its own before it is inlined. The destructor is destroy() inlined (0x710019ce88, 31
  // instructions, one stp through a kept address at 0x710019cef4), so destroy is the only user.
  // Forms tried without the helper, written in destroy: the test in the `if` (27 instructions, the stp of the destructor), the negated test with the arms swapped (27), a ternary (27), the flags, the
  // file handle or the test read into a local (27), two bool locals joined in the `if` (27), unknown08 read into a local first (28), an early return after unlink() (32). unlink matches with or
  // without the helper and keeps its own test.
  bool isLinked() const { return (unknown22c & FLAG_UNKNOWN_3) != 0 && unknown08 != nullptr; }

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

class ScriptManager : public ManagerObject, public mm::mtl::PtrSingleton<ScriptManager>, public ml::IWorkEvent {
public:
  ScriptManager(mm::mtl::IAllocator *allocator, size_t count);
  ~ScriptManager();
  bool initialize() override;
  bool finalize() override;
  virtual void update(const UpdateInfo &info);
  void createScript(int type, mtl::ALLOC_HANDLE handle, size_t size);
  void createScript(int type, mm::mtl::IAllocator *allocator, size_t size);
  void destroyScript(int type, bool isForce);
  bool isScriptCreated(int type) const;
  bool isScriptLoaded(int type) const;
  bool isScriptFree(int type) const;
  void addEvent(IScriptEvent *event);
  void makeFullPath(mm::mtl::FixStr<256> &path, const char *name);
  void loadScriptFromMemory(int type, const char *name, const char *data, size_t size);
  void removeEvent(IScriptEvent *event);
  void loadScript(int type, const char *name, ml::FILE_PRIO priority);
  void notifyEvent(int type, ScriptEventParam::State state);
  u32 getTypeMax() const;

  mm::mtl::Array<ScriptInfo> unknown20;              // Inferred role: scripts; original member name unknown.
  mm::mtl::FixedQueue<IScriptEvent *, 32> unknown38; // Inferred role: events; original member name unknown.
};

static_assert(offsetof(ScriptManager, unknown20) == 0x20, "");
static_assert(offsetof(ScriptManager, unknown38) == 0x38, "");
static_assert(sizeof(ScriptManager) == 0x148, "");

} // namespace fw
