#include "ptlib/material/particle_material_manager.h"

#include <new>

#include "grlib/cglib_tex_swizzle.h"
#include "grlib/cglib_texture.h"
#include "mm/mm_std_base.h"
#include "ptlib/particle_system.h"

namespace ptlib {
namespace material {

namespace {
MaterialManager *s_instance;
} // namespace

void MaterialManager::initSub() {
  unknown0000.clear();
  unknown4008.clear();
#line 99
  unknown8020 = static_cast<MaterialTexture *>(ParticleManager::sysAlloc(sizeof(MaterialTexture) * 2048, 0x10, __FILE__, __LINE__));
  if (unknown8020 != nullptr) {
    for (int i = 0; i < 2048; i++) {
      new (&unknown8020[i]) MaterialTexture;
      unknown0000.push_back(&unknown8020[i]);
    }
  }
}

void MaterialManager::init() {
#line 35
  MM_ASSERT(!getPtr());
  s_instance = static_cast<MaterialManager *>(ParticleManager::sysAlloc(sizeof(MaterialManager), 0x10, __FILE__, __LINE__));
  if (s_instance != nullptr) {
    new (s_instance) MaterialManager;
    s_instance->initSub();
  }
}

void MaterialManager::termSub(bool isAll) {
  if (isAll) {
    for (MaterialBase **it = unknown0000.begin(); it != unknown0000.end(); ++it) {
      (*it)->~MaterialBase();
    }
    for (MaterialBase **it = unknown4008.begin(); it != unknown4008.end(); ++it) {
      (*it)->~MaterialBase();
    }
    unknown0000.clear();
    unknown4008.clear();
    if (unknown8020 != nullptr) {
      ParticleManager::sysFree(unknown8020);
      unknown8020 = nullptr;
    }
  } else {
    for (MaterialBase **it = unknown4008.begin(); it != unknown4008.end();) {
      MaterialBase *material = *it;
      if (!material->unknown3c) {
        material->~MaterialBase();
        unknown0000.push_back(material);
        it = unknown4008.erase(it);
      } else {
        ++it;
      }
    }
  }
}

void MaterialManager::term() {
#line 49
  MM_ASSERT(getPtr());
  getPtr()->termSub(true);
  getPtr()->~MaterialManager();
  ParticleManager::sysFree(getPtr());
  getPtr() = nullptr;
}

void MaterialManager::allClear(bool isAll) { termSub(isAll); }

void MaterialManager::addActiveMaterial(MaterialBase *material) {
  efAstMsg("!m_aActiveMaterial.find(pMaterial)", "double registration error!!!");
  unknown4008.push_back(material);
}

MaterialBase *MaterialManager::getFreeMaterial() {
  if (unknown0000.empty()) {
    return nullptr;
  }
  MaterialBase *material = unknown0000.front();
  unknown0000.erase(unknown0000.begin());
  return material;
}

MaterialBase *MaterialManager::getMaterial(eMaterialType type, void *data, u32 size, u8 *owner) {
  for (MaterialBase **it = unknown4008.begin(); it != unknown4008.end(); ++it) {
    MaterialBase *material = *it;
    if (material->unknown10 == type && material->unknown20 == data && material->unknown28 == size) {
      return material;
    }
  }
  return nullptr;
}

MaterialBase *MaterialManager::getMaterialByHash(const u32 &hash) {
  for (MaterialBase **it = unknown4008.begin(); it != unknown4008.end(); ++it) {
    if ((*it)->unknown0c == hash) {
      return *it;
    }
  }
  return nullptr;
}

MaterialBase *MaterialManager::getMaterialByKey(const int &key, void *owner) {
  for (MaterialBase **it = unknown4008.begin(); it != unknown4008.end(); ++it) {
    MaterialBase *material = *it;
    if (material->unknown08 == key) {
      if (material->unknown18 == nullptr || material->unknown18 == owner) {
        return material;
      }
      if (material->unknown3c) {
        return material;
      }
    }
  }
  return nullptr;
}

namespace {

// Inferred role: drops a reference of an active material and frees the material at the last one; original name unknown.
inline bool unknown001(MaterialManager &manager, MaterialBase **&it) {
  (*it)->unknown38--;
  efAstMsg("(m_refCnt < 0)", "refCount minus!!!");
  MaterialBase *material = *it;
  if (material->unknown38 == 0) {
    material->~MaterialBase();
    it = manager.unknown4008.erase(it);
    manager.unknown0000.push_back(material);
    return true;
  }
  return false;
}

} // namespace

void MaterialManager::destroyMateriaByHash(const u32 &hash) {
  for (MaterialBase **it = unknown4008.begin(); it != unknown4008.end();) {
    if ((*it)->unknown0c == hash && unknown001(*this, it)) {
      continue;
    }
    ++it;
  }
}

void MaterialManager::destroyMateriaByKey(const int &key, void *owner) {
  for (MaterialBase **it = unknown4008.begin(); it != unknown4008.end();) {
    if ((*it)->unknown08 == key && !(*it)->unknown3c && (*it)->unknown18 == owner && unknown001(*this, it)) {
      continue;
    }
    ++it;
  }
}

void MaterialManager::destroyMateriaByKey(void *material, void *owner) {
  for (MaterialBase **it = unknown4008.begin(); it != unknown4008.end();) {
    if (*it == material && !(*it)->unknown3c && (*it)->unknown18 == owner && unknown001(*this, it)) {
      continue;
    }
    ++it;
  }
}

MaterialBase *MaterialManager::createTexture(void *data, u32 size, bool isResident, int format) {
  MaterialTexture *texture = static_cast<MaterialTexture *>(getFreeMaterial());
  if (texture != nullptr) {
    texture->unknown0c = unknown8010;
    grlib::CGLibTexSwizzle swizzle;
    switch (format) {
    case 4:
      swizzle = {2, 2, 2, 2};
      break;
    case 5:
      swizzle = {2, 2, 2, 1};
      break;
    case 6:
      swizzle = {1, 1, 1, 2};
      break;
    default:
      swizzle = {2, 3, 4, 5};
      break;
    }
    grlib::CGLibTexture::createTextureImagePtrs(texture->unknown40, data, size, isResident, &swizzle, false);
    if (texture->unknown40.isTexture3D()) {
      texture->unknown3d = true;
    }
  }
  return texture;
}

u32 MaterialManager::getMaterialNum() { return unknown4008.size(); }

MaterialBase *MaterialManager::getMaterialByIdx(u32 index) {
  if (index < unknown4008.size()) {
    return unknown4008[index];
  }
  return nullptr;
}

MaterialManager *&MaterialManager::getPtr() { return s_instance; }

bool MaterialManager::isValid() { return getPtr() != nullptr; }

MaterialManager *MaterialManager::get() {
#line 62
  MM_ASSERT(getPtr());
  return getPtr();
}

} // namespace material
} // namespace ptlib
