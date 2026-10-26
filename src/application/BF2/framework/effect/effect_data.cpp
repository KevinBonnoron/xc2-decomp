#include "framework/effect/effect_data.h"

#include "eflib/effect_system_manager.h"
#include "framework/effect/effect_manager.h"
#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "ml/path_util.h"

namespace fw {

namespace {

// Inferred role: header of an effect data block; original name unknown.
struct unknown001 {
  u32 unknown00;
  u32 unknown04;
};

} // namespace

EffectData *EffectData::createFromMemory(void *data, u32 size, const char *name, bool isExternal) {
  mm::mtl::FixStr<128> path;
  ml::PathUtil::getFsaPath(path, name);
  if (static_cast<unknown001 *>(data)->unknown04 >> 20 == 0) {
    if (!isExternal) {
      if (effect::SystemManager::getPtr()->es_regist(data, size) == 0) {
        return nullptr;
      }
    }

#line 43
    return new (Framework::getAllocator(), 16, __FILE__, __LINE__) EffectData(data, size, path.c_str(), isExternal);
  }

  return nullptr;
}

void *EffectData::getHandle() const { return m_handle; }

const char *EffectData::getName() const { return m_name.c_str(); }

EffectData::EffectData(void *data, u32 size, const char *name, bool isExternal) : m_handle(data), m_name(name), unknown9c(isExternal) {
  if (!this->unknown9c) {
    EffectManager::get()->addData(this);
  }

  addRef();
}

EffectData::~EffectData() {
  if (!unknown9c) {
    EffectManager::get()->removeData(this);
    if (effect::SystemManager::getPtr() != nullptr && m_handle != nullptr) {
      effect::SystemManager::getPtr()->es_free(m_handle);
      m_handle = nullptr;
    }
  }
}

} // namespace fw
