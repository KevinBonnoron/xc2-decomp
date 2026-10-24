#pragma once
#include "types.h"
#include <stddef.h>

namespace event {

class StmPackRes {
public:
  enum {
    FLAG_LOADING = 1 << 0,
    FLAG_FREE = 1 << 1,
  };

  StmPackRes();
  StmPackRes(void *buffer, size_t size, size_t dataOfs, size_t firstFile, size_t lastFile, size_t firstPage, size_t lastPage, int prio, int cut, size_t stream);
  bool isLoading() const;
  void loadCompleate();
  void *getFileAdr(size_t dataOfs) const;

  s32 mRefCount;
  u32 flags;
  s32 mDelay;
  void *mBuffer;
  size_t mSize;
  size_t mDataOfs;
  size_t mFirstFile;
  size_t mLastFile;
  size_t mFirstPage;
  size_t mLastPage;
  int mPrio;
  int mCut;
  size_t mStream;
};

static_assert(sizeof(StmPackRes) == 0x58, "");

} // namespace event
