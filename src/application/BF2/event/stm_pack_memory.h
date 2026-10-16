#pragma once
#include <stddef.h>

#include "event/i_stm_memory.h"
#include "event/stm_pack_data.h"
#include "event/stm_pack_header.h"
#include "event/stm_pack_res.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace event {

class StmPackMemory : public IStmMemory {
public:
  static constexpr u32 RES_COUNT = 256;
  static constexpr u32 STREAM_COUNT = 16;
  static constexpr size_t PAGE_SIZE = 0x1000;

  enum {
    FLAG_ALLOCATED = 1 << 0,
    FLAG_WAIT_CUT = 1 << 1,
    FLAG_STOP = 1 << 2,
  };

  struct Stream {
    Stream(const char *name) : mName(name) {}

    mm::mtl::FixStr<128> mName;
    StmPackHeader mHeader;
    StmPackData mData;
  };

  StmPackMemory(mtl::ALLOC_HANDLE handle);
  void loadStream(const char *name, const char *headerPath, const char *dataPath);
  void changeStream(const char *name);
  void stopStream();
  bool isBusy();
  virtual ~StmPackMemory();
  virtual void update();
  void freeCut();
  bool loadCut();
  bool waitCut();
  virtual void render(const mm::Rect<int> &rect, f32 frame);
  bool loadCut(void *buffer, size_t size, size_t firstPage, size_t &nextPage);
  void loadCut(void *buffer, size_t size, size_t firstFile, size_t lastFile, size_t firstPage, size_t lastPage, int prio);
  virtual void *adr(const char *path, size_t *size);
  virtual void free(void *adr, int frame);
  virtual bool isLoadingPrio(f32 prio) const;
  virtual bool isFailure() const;

private:
  Stream *getLoadStream() { return mStreams[mLoadStream]; }
  const Stream *getLoadStream() const { return mStreams[mLoadStream]; }
  Stream *getCurrentStream() { return mStreams[mCurrentStream]; }

  u32 flags;
  mtl::ALLOC_HANDLE handle;
  void *mBuffer;
  size_t mPageCount;
  size_t mFreePage;
  size_t mLoadPage;
  mm::mtl::FixedVector<StmPackRes, RES_COUNT> mResList;
  size_t mFileIndex;
  u32 mNextPrio;
  size_t mDataSize;
  size_t mReadSize;
  u32 mCutCount;
  mm::mtl::FixedVector<Stream *, STREAM_COUNT> mStreams;
  size_t mLoadStream;
  size_t mCurrentStream;
};

static_assert(sizeof(StmPackMemory::Stream) == 0x130, "");
static_assert(sizeof(StmPackMemory) == 0x58f8, "");

} // namespace event
