#pragma once
#include "event/i_manager.h"
#include "event/scheduler.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class ScheManager : public IManager, public mm::mtl::Singleton<ScheManager> {
public:
  static constexpr u32 SCHEDULER_UNKNOWN_16 = 16; // Inferred role: scheduler count; original name unknown.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: fld2evt flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: evt2idle flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: evt2fld flag; original name unknown.
  };

  ScheManager();
  virtual ~ScheManager() {}
  void create();
  void destroy();
  void init();
  void push(gf::GF_OBJ_HANDLE *handle, u32 type);
  void update();
  bool isExist(gf::GF_OBJ_HANDLE *handle);
  void play(Scheduler::ORDER order, gf::GF_OBJ_HANDLE *handle);
  void setUse(Scheduler::USE use, bool isUse, gf::GF_OBJ_HANDLE *handle);
  bool chkUse(Scheduler::USE use, gf::GF_OBJ_HANDLE *handle);
  bool isPlay(Scheduler::ORDER order, gf::GF_OBJ_HANDLE *handle);
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 unknown10;                                                     // Inferred role: flags; original member name unknown.
  mm::mtl::FixedVector<Scheduler *, SCHEDULER_UNKNOWN_16> unknown18; // Inferred role: schedulers; original member name unknown.
};

static_assert(sizeof(ScheManager) == 0xa0, "");

} // namespace event
