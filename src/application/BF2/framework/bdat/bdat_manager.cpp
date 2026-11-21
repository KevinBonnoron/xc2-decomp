#include <string.h>

#include "bdat.h"
#include "dr/dr_man.h"
#include "framework/lang_util.h"
#include "framework/memory/framework_memory.h"
#include "fw/fw_bdat_manager.h"
#include "ml/dev_file_th.h"
#include "ml/file_res_th.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/hash.h"
#include "mm_mtl/map.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace fw {

struct UpdateInfo;

const ml::FILE_PRIO FILE_PRIO_UNKNOWN_10 = static_cast<ml::FILE_PRIO>(10); // Inferred role: bdat file prio; original name unknown.

bool BdatManager::Impl::isMsgFile(const char *name) { return __builtin_strstr(name, "_ms.") != nullptr; }

// Inferred role: whether the entry already holds this file in the current language; original function name unknown. The game repeats
// it inline in loadBdat (0x7100153048) and loadBdatFromMemory (0x7100153920), and one helper matches both. The `lang` local places the
// getLangFolder call before the entry address: with the call inside the strcmp arguments (in the helper too) loadBdat has 175
// instructions against the game's 174 (first difference at +0x2c).
static bool unknown001(const BdatManager::Impl::BdatInfo &info, const char *name) {
  if (strcmp(info.unknown108.c_str(), name) != 0) {
    return false;
  }
  const char *lang = LangUtil::getLangFolder().c_str();
  return strcmp(info.unknown12c.c_str(), lang) == 0;
}

bool BdatManager::Impl::loadBdat(int id, mtl::ALLOC_HANDLE handle, const char *path) {
  BdatInfo &info = unknown128[id];
  if (isExistBdat(id)) {
    if (unknown001(info, path)) {
      return true;
    }
    unregistBdat(id);
  }
  mm::mtl::FixStr<256> fullPath = unknown08;
  makePath(fullPath, path);
  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, fullPath.c_str());
  ml::FileResTh *res = new (FrameworkMemory::getMem(5)) ml::FileResTh();
  if (res != nullptr) {
    if (!res->load(handle, fileName.c_str(), 0, FILE_PRIO_UNKNOWN_10)) {
      res->Release();
      res = nullptr;
    } else {
      info.unknown00 = STATE_UNKNOWN_1;
      info.unknown04 = fileName;
      info.unknown108 = path;
      info.unknown140 = mm::mtl::hashStrCrc(info.unknown108.c_str());
      info.unknown148 = nullptr;
      info.unknown150 = handle;
      info.unknown158 = res;
      info.unknown12c = LangUtil::getLangFolder().c_str();
    }
  }
  return res != nullptr;
}

bool BdatManager::Impl::reloadBdat(int id) {
  BdatInfo &info = unknown128[id];
  if (!isExistBdat(id)) {
    return false;
  }
  BdatInfo old(info);
  unregistBdat(id);
  mm::mtl::FixStr<256> fullPath = unknown08;
  makePath(fullPath, old.unknown108.c_str());
  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, fullPath.c_str());
  ml::FileResTh *res = new (FrameworkMemory::getMem(5)) ml::FileResTh();
  if (res == nullptr) {
    return false;
  }
  if (!res->loadBlock(old.unknown150, fileName.c_str(), 0, 0)) {
    res->Release();
    return false;
  }
  info.unknown00 = STATE_UNKNOWN_2;
  info.unknown04 = fileName;
  info.unknown108 = old.unknown108;
  info.unknown140 = mm::mtl::hashStrCrc(info.unknown108.c_str());
  info.unknown148 = nullptr;
  info.unknown150 = old.unknown150;
  info.unknown158 = res;
  info.unknown12c = LangUtil::getLangFolder().c_str();
  updateLayer(id, info);
  return true;
}

bool BdatManager::Impl::loadBdatFromMemory(int id, mtl::ALLOC_HANDLE handle, void *data, size_t size, const char *name) {
  BdatInfo &info = unknown128[id];
  if (isExistBdat(id)) {
    if (unknown001(info, name)) {
      return true;
    }
    unregistBdat(id);
  }
  mm::mtl::FixStr<256> fullPath = unknown08;
  makePath(fullPath, name);
  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, fullPath.c_str());
  void *buffer = mtl::MemManager::allocate(handle, size, 16, false, "no name", 0);
  // The game computes the result right after the allocation and keeps it in a register (cset at 0x7100153a58, then the branch); written
  // as `buffer == nullptr` and `return buffer != nullptr` the function has 182 instructions against the game's 185.
  bool loaded = buffer != nullptr;
  if (!loaded) {
    info.unknown158 = nullptr;
    info.unknown148 = nullptr;
    info.unknown00 = STATE_UNKNOWN_0;
    info.unknown150 = mtl::ALLOC_HANDLE();
    info.unknown140 = 0;
    info.unknown160 = false;
    info.unknown04.clear();
    info.unknown108.clear();
    info.unknown12c.clear();
  } else {
    memcpy(buffer, data, size);
    info.unknown00 = STATE_UNKNOWN_2;
    info.unknown04 = fileName;
    info.unknown108 = name;
    info.unknown140 = mm::mtl::hashStrCrc(info.unknown108.c_str());
    info.unknown148 = buffer;
    info.unknown150 = handle;
    info.unknown158 = nullptr;
    info.unknown12c = LangUtil::getLangFolder().c_str();
    updateLayer(id, info);
  }
  return loaded;
}

void BdatManager::Impl::loadBdatFromMemory(int id, void *data) {
  BdatInfo &info = unknown128[id];
  info.unknown04.clear();
  info.unknown108.clear();
  info.unknown00 = STATE_UNKNOWN_2;
  info.unknown140 = 0;
  info.unknown148 = data;
  info.unknown150 = mtl::ALLOC_HANDLE();
  info.unknown158 = nullptr;
  info.unknown12c = LangUtil::getLangFolder().c_str();
  info.unknown160 = true;
  updateLayer(id, info);
}

BdatManager::Impl::~Impl() {
  for (int i = 0; i < BDAT_UNKNOWN_16; i++) {
    unregistBdat(i);
  }
}

void BdatManager::Impl::unregistBdat(const char *name) {
  int id = find(name);
  if (id >= 0) {
    unregistBdat(id);
  }
}

bool BdatManager::Impl::isExistBdat(int id) const { return unknown128[id].unknown158 != nullptr || unknown128[id].unknown148 != nullptr; }

bool BdatManager::Impl::isEnableBdat(int id) const {
  if (!isExistBdat(id)) {
    return false;
  }

  return unknown128[id].unknown00 == STATE_UNKNOWN_3;
}

unsigned char *BdatManager::Impl::getFp(const char *name) {
  mm::mtl::Map<u32, SheetFpInfo>::iterator it = unknown110.find(mm::mtl::hashStrCrc(name));
  if (it == unknown110.end()) {
    return nullptr;
  }
  return it->second.unknown68;
}

void BdatManager::Impl::update(const UpdateInfo &info) {
  for (int i = 0; i < BDAT_UNKNOWN_16; i++) {
    updateLayer(i, unknown128[i]);
  }
}

void BdatManager::update(const UpdateInfo &info) {
  if (!isFinalized()) {
    // Impl::update, defined in this file, never reads its info parameter, so the game never sets x1 for the tail call
    // (0x7100154240): the compiler erased the argument (ruling 2026-11-13 #6). The original expression cannot be checked;
    // info, the parameter of this function, is the plausible one.
    unknown18->update(info);
  }
}

unsigned char *BdatManager::getFp(const char *name) { return get()->unknown18->getFp(name); }

bool BdatManager::initialize() { return true; }

bool BdatManager::finalize() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }

  return true;
}

void BdatManager::setBasePath(const char *path) { get()->unknown18->unknown08 = path; }

const char *BdatManager::getLocale() { return LangUtil::getLangFolder().c_str(); }

bool BdatManager::loadBdat(int id, mtl::ALLOC_HANDLE handle, const char *path) { return get()->unknown18->loadBdat(id, handle, path); }

void BdatManager::reloadBdat(int id) { get()->unknown18->reloadBdat(id); }

void BdatManager::loadBdatFromMemory(int id, mtl::ALLOC_HANDLE handle, void *data, size_t size, const char *name) { get()->unknown18->loadBdatFromMemory(id, handle, data, size, name); }

void BdatManager::loadBdatFromMemory(int id, void *data) { get()->unknown18->loadBdatFromMemory(id, data); }

void BdatManager::unregistBdat(int id) { get()->unknown18->unregistBdat(id); }

void BdatManager::unregistBdat(const char *name) { get()->unknown18->unregistBdat(name); }

bool BdatManager::isExistBdat(int id) { return get()->unknown18->isExistBdat(id); }

bool BdatManager::isEnableBdat(int id) { return get()->unknown18->isEnableBdat(id); }

unsigned char *BdatManager::getFp(int table, int id) { return Bdat::getFP(table, id); }

} // namespace fw

typedef mm::mtl::Map<u32, fw::BdatManager::Impl::SheetFpInfo>::tree_type unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template void unknown101::erase(unknown101::node *);
template void unknown101::rebalance_after_erase(unknown101::node *);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<u32, fw::BdatManager::Impl::SheetFpInfo> &);
template void unknown101::rebalance(unknown101::node *);
