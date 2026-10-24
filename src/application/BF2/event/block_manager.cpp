#include "event/block_manager.h"

#include "mtl/alloc_handle.h"

namespace event {

BlockManager::BlockManager() : unknown18(nullptr), unknown20(nullptr) {}

void BlockManager::create(mtl::ALLOC_HANDLE handle) {}

void BlockManager::destroy() {}

void BlockManager::initWtr(void *data, u32 size, mtl::ALLOC_HANDLE handle) {}

void BlockManager::initTime(void *data, u32 size, mtl::ALLOC_HANDLE handle) {}

bool BlockManager::isWtrBlock(u32 id) { return unknown28[id].isBlock(0); }

bool BlockManager::isTimeBlock(u32 id) { return unknown428[id].isBlock(0); }

} // namespace event
