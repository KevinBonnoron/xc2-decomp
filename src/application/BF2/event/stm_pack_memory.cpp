#include "event/stm_pack_memory.h"

#include "event/memory_manager.h"
#include "mm_mtl/singleton.h"
#include "mtl/mem_manager.h"

namespace event {

StmPackMemory::StmPackMemory(mtl::ALLOC_HANDLE handle)
    : flags(0), handle(handle), mBuffer(nullptr), mPageCount(0), mFreePage(0), mLoadPage(0), mFileIndex(0), mNextPrio(0), mDataSize(0), mReadSize(0), mCutCount(0), mLoadStream(0), mCurrentStream(0) {}

void StmPackMemory::loadStream(const char *name, const char *headerPath, const char *dataPath) {
  Stream *stream = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle()) Stream(name);
  stream->mHeader.create(handle, headerPath);
  stream->mData.create(dataPath);
  mStreams.push_back(stream);
}

void StmPackMemory::changeStream(const char *name) {
  for (size_t i = 0; i < mStreams.size(); i++) {
    if (__builtin_strcmp(mStreams[i]->mName.c_str(), name) == 0) {
      mCurrentStream = i;
      return;
    }
  }
}

void StmPackMemory::stopStream() { flags |= FLAG_STOP; }

bool StmPackMemory::isBusy() {
  for (size_t i = 0; i < mStreams.size(); i++) {
    if (mStreams[i]->mData.isBusy()) {
      return true;
    }
  }
  return false;
}

StmPackMemory::~StmPackMemory() {
  mFileIndex = 0;
  mFreePage = 0;
  mLoadPage = 0;
  mResList.clear();
  mtl::MemManager::deallocate(mBuffer, 0, false);
  for (size_t i = 0; i < mStreams.size(); i++) {
    Stream *stream = mStreams[i];
    stream->mData.destroy();
    stream->mHeader.destroy();
    delete stream;
  }
  mStreams.clear();
}

void StmPackMemory::update() {
  if (!(flags & FLAG_ALLOCATED)) {
    for (size_t i = 0; i < mStreams.size(); i++) {
      if (mStreams[i]->mHeader.isLoading()) {
        return;
      }
    }
    if (!getCurrentStream()->mData.open()) {
      return;
    }
    mPageCount = mtl::MemManager::maxAllocSize(handle) / PAGE_SIZE - 2;
    mBuffer = mtl::MemManager::allocate(handle, mPageCount * PAGE_SIZE, PAGE_SIZE, false, "no name", 0);
    flags |= FLAG_ALLOCATED;
  }
  if (!(flags & FLAG_ALLOCATED)) {
    return;
  }
  freeCut();
  if (flags & FLAG_WAIT_CUT) {
    if (waitCut()) {
      flags &= ~FLAG_WAIT_CUT;
    }
  } else if (!(flags & FLAG_STOP)) {
    if (loadCut()) {
      flags |= FLAG_WAIT_CUT;
    }
  }
}

void StmPackMemory::freeCut() {
  if (mResList.empty()) {
    return;
  }
  StmPackRes &res = mResList.front();
  if (!(res.flags & StmPackRes::FLAG_FREE) || res.mRefCount > 0 || (res.mDelay >= 0 && res.mDelay-- != 0)) {
    if (res.mStream >= mCurrentStream) {
      return;
    }
  }
  size_t lastPage = res.mLastPage;
  mResList.erase(mResList.begin());
  if (mResList.empty()) {
    mFreePage = lastPage;
  } else {
    mFreePage = mResList.front().mFirstPage;
  }
}

bool StmPackMemory::waitCut() {
  if (getLoadStream()->mData.isBusy()) {
    return false;
  }
  for (size_t i = 0; i < mResList.size(); i++) {
    mResList[i].loadCompleate();
  }
  if (mFileIndex < getLoadStream()->mHeader.getCount()) {
    mNextPrio = getLoadStream()->mHeader.getPrio(mFileIndex);
  } else {
    mNextPrio = 9999999;
  }
  return true;
}

void StmPackMemory::render(const mm::Rect<int> &rect, f32 frame) {}

void *StmPackMemory::adr(const char *path, size_t *size) {
  for (StmPackRes *res = mResList.begin(); res != mResList.end(); res++) {
    if (res->isLoading() || res->mStream != mCurrentStream) {
      continue;
    }
    for (size_t i = res->mFirstFile; i <= res->mLastFile; i++) {
      if (__builtin_strcmp(path, getCurrentStream()->mHeader.getPath(i)) == 0) {
        res->mRefCount++;
        if (size != nullptr) {
          *size = getCurrentStream()->mHeader.getDataSize(i);
        }
        return res->getFileAdr(getCurrentStream()->mHeader.getDataOfs(i));
      }
    }
  }
  return nullptr;
}

void StmPackMemory::free(void *adr, int frame) {
  for (StmPackRes *res = mResList.begin(); res != mResList.end(); res++) {
    if (res->isLoading()) {
      continue;
    }
    if (reinterpret_cast<size_t>(res->mBuffer) <= reinterpret_cast<size_t>(adr) && reinterpret_cast<size_t>(adr) < res->mSize + reinterpret_cast<size_t>(res->mBuffer)) {
      res->flags |= StmPackRes::FLAG_FREE;
      res->mRefCount--;
      return;
    }
  }
}

bool StmPackMemory::isFailure() const { return getLoadStream()->mHeader.isFailure() || getLoadStream()->mData.isFailure(); }

// The symbol at 0x71000a4ec8 reads +0x58e8, +0x58f0 and +0x5840;
// check confirms the code match, while the original member names remain unknown.
bool StmPackMemory::isLoadingPrio(f32 prio) const {
  if (mLoadStream <= mCurrentStream) {
    if (static_cast<f32>(mNextPrio) <= prio) {
      return true;
    }
  }
  return false;
}

} // namespace event
