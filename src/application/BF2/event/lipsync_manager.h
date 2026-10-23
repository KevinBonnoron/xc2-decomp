#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace csvb {
class CCsvbData;
} // namespace csvb

namespace event {

class LipsyncRes;

class LipsyncManager : public IManager, public mm::mtl::Singleton<LipsyncManager> {
public:
  static constexpr u32 RES_COUNT = 8;

  enum {
    FLAG_EVENT = 1 << 0,
    FLAG_ACTIVE = 1 << 1,
  };

  LipsyncManager();
  virtual ~LipsyncManager() {}
  bool isActive() const;
  f32 getVolume(f32 frame) const;
  void clear();
  void load(const char *name);
  LipsyncRes *searchRes(const char *name);
  bool isLoading() const;
  void setEvent(const char *name);
  bool setTarget(const char *name);
  f32 getFrameMax() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 flags;
  mm::mtl::FixedVector<LipsyncRes *, RES_COUNT> mResList;
  LipsyncRes *mCurrentRes;
  mm::mtl::FixStr<128> mTarget;
  csvb::CCsvbData *mCsv;
};

static_assert(sizeof(LipsyncManager) == 0xf8, "");

} // namespace event
