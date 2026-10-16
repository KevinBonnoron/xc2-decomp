#pragma once
#include "event/i_manager.h"
#include "event/scheduler.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class ScheManager : public IManager, public mm::mtl::Singleton<ScheManager> {
public:
  static constexpr u32 SCHEDULER_COUNT = 16;

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
  bool isPlay(Scheduler::ORDER order, gf::GF_OBJ_HANDLE *handle) {
    if (handle == gf::INVALID_HANDLE) {
      for (Scheduler **it = mSchedulers.begin(); it != mSchedulers.end(); it++) {
        if ((*it)->isPlay(order)) {
          return true;
        }
      }
    } else {
      for (Scheduler **it = mSchedulers.begin(); it != mSchedulers.end(); it++) {
        if ((*it)->getHandle() == handle && (*it)->isPlay(order)) {
          return true;
        }
      }
    }
    return false;
  }
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 flags;
  mm::mtl::FixedVector<Scheduler *, SCHEDULER_COUNT> mSchedulers;
};

static_assert(sizeof(ScheManager) == 0xa0, "");

} // namespace event
