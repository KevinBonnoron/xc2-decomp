#include "dr/dr_ibl_man.h"

#include "dr/dr_ibl_obj.h"
#include "dr/dr_man.h"
#include "mtl/alloc_handle.h"

// The game builds the collision access in this unit, before this file (0x7edd14): DrIBLObj::initialize, the DrIBLObj destructor and DrIBLObj::update inline its functions.
#include "dr_ibl_coli_acc.cpp"

namespace ml {

DrIBLMan::DrIBLMan(DrMan *man, int index) : unknown00(man), unknown08(index), unknown910(nullptr) {}

DrIBLMan::~DrIBLMan() {
  for (mm::mtl::FixedList<DrIBLObj *, 32>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (*it != nullptr) {
      delete *it;
      *it = nullptr;
    }
  }
  for (int i = 0; i < 2; i++) {
    for (mm::mtl::FixedList<DrIBLObj *, 32>::iterator it = unknown250[i].begin(); it != unknown250[i].end(); ++it) {
      if (*it != nullptr) {
        delete *it;
        *it = nullptr;
      }
    }
  }
}

void DrIBLMan::update() {
  for (mm::mtl::FixedList<DrIBLObj *, 32>::iterator it = unknown6d0.begin(); it != unknown6d0.end(); ++it) {
    if (*it != nullptr) {
      delete *it;
    }
  }
  unknown6d0.clear();
  for (mm::mtl::FixedList<DrIBLObj *, 32>::iterator it = unknown250[DrMan::s_nDblIdx].begin(); it != unknown250[DrMan::s_nDblIdx].end(); ++it) {
    DrIBLObj *obj = *it;
    if ((obj->unknown58 & 2) == 0) {
      obj->initialize(unknown00);
    }
    unknown10.push_back(obj);
  }
  unknown250[DrMan::s_nDblIdx].clear();
  for (mm::mtl::FixedList<DrIBLObj *, 32>::iterator it = unknown10.begin(); it != unknown10.end();) {
    DrIBLObj *obj = *it;
    if ((obj->unknown58 & 2) != 0) {
      unknown6d0.push_back(obj);
      it = unknown10.erase(it);
    } else {
      ++it;
    }
  }
  unknown910 = nullptr;
  for (mm::mtl::FixedList<DrIBLObj *, 32>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    DrIBLObj *obj = *it;
    if ((obj->unknown58 & 1) != 0) {
      obj->update();
      if (obj->hasValidIBL() && obj->unknown5c != 0) {
        if (unknown910 == nullptr || unknown910->getPriority() < obj->getPriority()) {
          unknown910 = obj;
        }
      }
    }
  }
}

bool DrIBLMan::isValid() const { return unknown910 != nullptr; }

void DrIBLMan::releaseObj(DrIBLObj *obj) { obj->unknown58 |= 2; }

DrIBLObj *DrIBLMan::createObj(const void *data) {
  DrIBLObj *obj = new (DrMan::get()->unknown0c) DrIBLObj(data);
  unknown250[DrMan::s_nDblStockIdx].push_back(obj);
  return obj;
}

grlib::CGLibTextureBuffer *DrIBLMan::getAlbedoTexture() const {
  if (unknown910 != nullptr) {
    return unknown910->getAlbedoTexture();
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrIBLMan::getNormalTexture() const {
  if (unknown910 != nullptr) {
    return unknown910->getNormalTexture();
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrIBLMan::debug_getAlbedoTexture(u32 index) const {
  if (!unknown10.empty()) {
    return (*unknown10.begin())->debug_getAlbedoTexture(index);
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrIBLMan::debug_getNormalTexture(u32 index) const {
  if (!unknown10.empty()) {
    return (*unknown10.begin())->debug_getNormalTexture(index);
  }
  return nullptr;
}

} // namespace ml

// The game builds these files in one unit with this one.
#include "dr_ibl_obj.cpp"
