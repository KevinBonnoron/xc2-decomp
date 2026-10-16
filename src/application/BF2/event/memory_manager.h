#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/noncopyable.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace event {

class MemoryManager : public IManager, public mm::mtl::NoncopyableBase {
public:
  static constexpr u32 TXTBUF_COUNT = 512;

  enum {
    FLAG_DISP = 1 << 0,
  };

  MemoryManager();
  virtual ~MemoryManager() {}
  void create();
  void destroy();
  void login();
  void clear();
  void destroyTxtbuf(const char *txtbuf);
  void clearHighestMemHeap();
  void update();
  void render();
  static mtl::ALLOC_HANDLE getFwProcMem();
  u32 getSysMemSize() const;
  u32 getResMemSize() const;
  char *createTxtbuf(const char *text);
  bool isActive() const;
  bool isEnough() const;
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

  const mtl::ALLOC_HANDLE &getSysHandle() const { return mSysHandle; }
  const mtl::ALLOC_HANDLE &getResHandle() const { return mResHandle; }

private:
  u32 flags;
  u32 mTxtbufState;
  u32 mIsLargeEvent;
  mtl::ALLOC_HANDLE mStaticHandle;
  mtl::ALLOC_HANDLE mSysHandle;
  mtl::ALLOC_HANDLE mResHandle;
  mtl::ALLOC_HANDLE mMotstmHandle;
  u32 mStaticSize;
  u32 mSysSize;
  u32 mResSize;
  u32 mMotstmSize;
  mm::mtl::FixedVector<char *, TXTBUF_COUNT> mTxtbufs;
  u64 mHighestSysHeap;
  u64 mHighestResHeap;
  u32 mTxtbufTotalSize;
};

static_assert(sizeof(MemoryManager) == 0x1060, "");

} // namespace event
