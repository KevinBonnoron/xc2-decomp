#include "event/block_manager.h"

#include "mtl/alloc_handle.h"

namespace event {

BlockManager::BlockManager() : mWtrData(nullptr), mTimeData(nullptr) {}

void BlockManager::create(mtl::ALLOC_HANDLE handle) {}

void BlockManager::destroy() {}

void BlockManager::initWtr(void *data, u32 size, mtl::ALLOC_HANDLE handle) {}

void BlockManager::initTime(void *data, u32 size, mtl::ALLOC_HANDLE handle) {}

bool BlockManager::isWtrBlock(u32 id) { return mWtrs[id].isBlock(0); }

bool BlockManager::isTimeBlock(u32 id) { return mTimes[id].isBlock(0); }

} // namespace event
