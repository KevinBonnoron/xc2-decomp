#include "framework/effect/effect_data.h"

#include "eflib/effect_system_manager.h"
#include "framework/effect/effect_manager.h"

namespace fw {

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
