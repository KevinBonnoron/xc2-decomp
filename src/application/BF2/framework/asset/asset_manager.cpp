#include "framework/asset/asset_manager.h"

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "mm_mtl/hash.h"

namespace fw {

mtl::ALLOC_HANDLE AssetManager::getMemSYS() { return Framework::getMemHandle(); }

mtl::ALLOC_HANDLE AssetManager::getMemTMP() { return FrameworkMemory::getMem(3); }

u32 AssetManager::getHash(const char *name) { return mm::mtl::hashStrCrc(name); }

} // namespace fw
