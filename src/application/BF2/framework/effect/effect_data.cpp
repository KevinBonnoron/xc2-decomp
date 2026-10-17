#include "framework/effect/effect_data.h"

#include "eflib/effect_system_manager.h"
#include "framework/effect/effect_manager.h"

namespace fw {

void *EffectData::getHandle() const { return handle; }

const char *EffectData::getName() const { return name.c_str(); }

EffectData::EffectData(void *data, u32 size, const char *name, bool isExternal) : handle(data), name(name), isExternal(isExternal) {
  if (!this->isExternal) {
    EffectManager::get()->addData(this);
  }

  addRef();
}

EffectData::~EffectData() {
  if (!isExternal) {
    EffectManager::get()->removeData(this);
    if (effect::SystemManager::getPtr() != nullptr && handle != nullptr) {
      effect::SystemManager::getPtr()->es_free(handle);
      handle = nullptr;
    }
  }
}

} // namespace fw
