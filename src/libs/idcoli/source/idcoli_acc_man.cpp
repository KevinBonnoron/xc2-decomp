#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {
class WinProc;
} // namespace ml

namespace idcoli {

IDColiAccMan::IDColiAccMan() {}

IDColiObj *IDColiAccMan::createColiGrand(const void *binary) { return IDColiManager::get()->createColiGrand(binary); }

IDColiObj *IDColiAccMan::createColiCharacter() { return IDColiManager::get()->createColiCharacter(); }

IDColiObj *IDColiAccMan::createColiPhantom() { return IDColiManager::get()->createColiPhantom(); }

bool IDColiAccMan::getGrandAABB(mm::Vec3 &max, mm::Vec3 &min) const {
  IDColiManager *manager = IDColiManager::get();
  max = mm::Vec3(-10000.0f, -10000.0f, -10000.0f);
  min = mm::Vec3(10000.0f, 10000.0f, 10000.0f);
  IDColiObj *object = manager->unknown08[0].m_head;
  if (object != nullptr) {
    for (; object != nullptr; object = object->unknown10) {
      static_cast<IDColiObjGrand *>(object)->getGrandAABB(max, min);
    }

    return true;
  }

  max = mm::Vec3(100.0f, 100.0f, 100.0f);
  min = mm::Vec3(-100.0f, -100.0f, -100.0f);
  return false;
}

int IDColiAccMan::isGblId(u32 id) { return IDColiManager::get()->isGblId(id); }

void IDColiAccMan::setGblId(u32 id, bool isClear) { IDColiManager::get()->setGblId(id, isClear); }

void *IDColiAccMan::getGblIdTbl() { return IDColiManager::get()->getGblIdTbl(); }

void IDColiAccMan::setSubNum(u32 num) { IDColiManager::get()->unknownf0 = num; }

void IDColiAccMan::openDebugWindow(ml::WinProc *window) {}

void IDColiAccMan::debugDrawCharacter(bool isDraw) {}

void IDColiAccMan::debugDrawGrand(bool isDraw) {}

void IDColiAccMan::debugDrawPhantom(bool isDraw) {}

} // namespace idcoli
