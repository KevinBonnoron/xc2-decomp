#include "event/stm_pack_res.h"

namespace event {

StmPackRes::StmPackRes()
    : mRefCount(0), flags(0), mDelay(2), mBuffer(nullptr), mSize(0), mDataOfs(0), mFirstFile(0), mLastFile(0), mFirstPage(0), mLastPage(0), mPrio(0),
      mStream(0) {}

bool StmPackRes::isLoading() const { return (flags & FLAG_LOADING) != 0; }

void StmPackRes::loadCompleate() { flags &= ~FLAG_LOADING; }

void *StmPackRes::getFileAdr(size_t dataOfs) const { return reinterpret_cast<void *>((dataOfs - mDataOfs) + reinterpret_cast<size_t>(mBuffer)); }

} // namespace event
