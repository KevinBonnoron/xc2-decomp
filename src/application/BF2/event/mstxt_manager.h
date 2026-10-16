#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class MstxtRes;

class MstxtManager : public IManager, public mm::mtl::Singleton<MstxtManager> {
public:
  static constexpr u32 RES_COUNT = 16;

  MstxtManager();
  virtual ~MstxtManager() {}
  void clear();
  void load(const char *path);
  MstxtRes *search(const char *path);
  bool isLoading() const;
  bool isLoaded() const;
  void registerBdat(const char *path);
  unsigned char *getFp() const;
  int getSeatID(const char *label) const;
  const char *getText(const char *label) const;
  int getTop() const;
  int getCount() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  mm::mtl::FixedVector<MstxtRes *, RES_COUNT> mResList;
  MstxtRes *mCurrentRes;
};

static_assert(sizeof(MstxtManager) == 0xa0, "");

} // namespace event
