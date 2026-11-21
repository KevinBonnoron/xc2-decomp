#include "framework/effect/effect_pack.h"

#include "mtl/alloc_handle.h"
#include <unordered_map>

#include "eflib/effect_system_manager.h"
#include "framework/effect/effect_data.h"
#include "ml/path_util.h"

namespace fw {

namespace {

// Inferred role: header of a block in an effect pack, blocks are chained by relative offsets; original name unknown.
struct unknown001 {
  u32 unknown00;
  u32 unknown04;
  u8 unknown08;
  u8 _09[0x0c - 0x09];
  u32 unknown0c;
};

static_assert(offsetof(unknown001, unknown0c) == 0x0c, "");

// Inferred helper: the next block of the chain, or nullptr; original name unknown.
unknown001 *unknown002(unknown001 *block) {
  if (block->unknown0c == 0) {
    return nullptr;
  }

  return reinterpret_cast<unknown001 *>(reinterpret_cast<u8 *>(block) + block->unknown0c);
}

} // namespace

u32 EffectPack::getEfbNum(void *data) {
  unknown001 *block = static_cast<unknown001 *>(data);
  if (block->unknown08 == 'a') {
    u32 count = 0;
    while ((block = unknown002(block)) != nullptr) {
      count++;
    }
    return count;
  }

  return 0;
}
EffectPack *EffectPack::createFromMemory(void *data, u32 size, const char *name, bool isCopy) {
  mm::mtl::FixStr<128> path;
  ml::PathUtil::getFsaPath(path, name);
  EffectPack *pack = EffectManager::get()->findPack(path.c_str());
  if (pack != nullptr) {
    pack->addRef();
    return pack;
  }
  if (data != nullptr && static_cast<unknown001 *>(data)->unknown04 >> 20 == 0) {
    EffectManager *manager = EffectManager::get();
    if (manager != nullptr) {
      pack = new (manager->unknown2c) EffectPack(manager->unknown2c, data, size, path.c_str(), isCopy);
      if (pack != nullptr) {
        return pack;
      }
    }
  }
  return nullptr;
}

EffectPack::~EffectPack() {
  for (EffectManager::DataMap::iterator it = unknown18.begin(); it != unknown18.end(); ++it) {
    it->second->release();
  }

  unknown18.clear();
  if (unknown10 != nullptr) {
    effect::SystemManager::getPtr()->es_pack_free(reinterpret_cast<u64>(unknown10));
    unknown10 = nullptr;
  }

  EffectManager::get()->removePack(this);
}

void *EffectPack::searchEfb(const char *name) const {
  if (unknown10 != nullptr) {
    mm::mtl::FixStr<128> path;
    ml::PathUtil::getFsaPath(path, name);
    EffectManager::DataMap::const_iterator it = unknown18.find(std::string(path.c_str()));
    if (it != unknown18.end()) {
      if (it->second == nullptr) {
        return nullptr;
      }

      return it->second->getHandle();
    }
  }

  return nullptr;
}

EffectData *EffectPack::searchData(const char *name) const {
  if (unknown10 == nullptr) {
    return nullptr;
  }

  mm::mtl::FixStr<128> path;
  ml::PathUtil::getFsaPath(path, name);
  EffectManager::DataMap::const_iterator it = unknown18.find(std::string(path.c_str()));
  if (it != unknown18.end()) {
    return it->second;
  }

  return nullptr;
}

} // namespace fw
