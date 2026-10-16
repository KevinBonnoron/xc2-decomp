#include "framework/resource/resource_manager.h"

#include "framework/framework.h"
#include "mm_mtl/hash.h"

namespace fw {

mtl::ALLOC_HANDLE ResourceManager::getMemSYS() { return Framework::getMemHandle(); }

mtl::ALLOC_HANDLE ResourceManager::getMemTMP() { return m_hMemoryTemp; }

void ResourceManager::setMemTMP(mtl::ALLOC_HANDLE handle) { m_hMemoryTemp = handle; }

u32 ResourceManager::getHash(const char *name) { return mm::mtl::hashStrCrc(name); }

} // namespace fw
