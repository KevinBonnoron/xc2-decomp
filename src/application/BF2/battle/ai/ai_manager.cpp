// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/battle/ai/ai_manager.cpp.
#include "battle/ai/ai_manager.h"

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

namespace ai {

void AiManager::init() {
  AiScriptDataManager::init();
  AiScriptManager::init();
  gf::GfObjManager::addListener(this, gf::IGfObjListener::OBJEVT_UNKNOWN_0);
}

void AiManager::destroy() {
  gf::GfObjManager::removeListener(this);
  _clear();
  AiScriptDataManager::destroy();
  AiScriptManager::destroy();
}

void AiManager::update(const fw::UpdateInfo &info) {
  for (mm::mtl::FixedList<AiData *, unknown001>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    (*it)->update(info);
  }
  AiScriptDataManager::update(info);
  AiScriptManager::update(info);
}

void AiManager::regist(gf::GF_OBJ_HANDLE *handle, int id) {
  // __LINE__ must be 61 as in the original file: it is an argument of operator new.
#line 61
  AiData *data = new (fw::Framework::getAllocator(), 0x10, __FILE__, __LINE__) AiData;
  data->setHandle(handle);
  data->setId(id);
  data->init();
  unknown10.push_back(data);
  AiScriptManager::start(AiScriptDataManager::getScriptName(id));
}

AiData *AiManager::getDataFromHandle(gf::GF_OBJ_HANDLE *handle) {
  for (mm::mtl::FixedList<AiData *, unknown001>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    AiData *data = *it;
    if (data->getHandle() == handle) {
      return data;
    }
  }
  return nullptr;
}

// The game keeps `cmp w25, w19; cinc w25, w25, ne; b.eq` (the count increment speculated into the match block) only with the result written after the loop (0x7100002ea0): `return data` inside the
// loop keeps the increment in a block of its own (46 instructions, first difference at +0x7c), as do `num++ == index`, `if (num != index) num++; else return data;` and a `continue` (56).
AiData *AiManager::getDataFromId(int id, int index) {
  AiData *result = nullptr;
  int num = 0;
  for (mm::mtl::FixedList<AiData *, unknown001>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    AiData *data = *it;
    if (data->getId() == id) {
      if (num == index) {
        result = data;
        break;
      }
      num++;
    }
  }
  return result;
}

int AiManager::getNumFromId(int id) {
  int num = 0;
  for (mm::mtl::FixedList<AiData *, unknown001>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    if ((*it)->getId() == id) {
      num++;
    }
  }
  return num;
}

void AiManager::_clear() {
  for (mm::mtl::FixedList<AiData *, unknown001>::iterator it = unknown10.begin(); it != unknown10.end();) {
    AiScriptManager::end(AiScriptDataManager::getScriptName((*it)->getId()));
    // The game tests the data pointer after the dereference: it stores the null before erase's argument setup.
    if (*it != nullptr) {
      delete *it;
      *it = nullptr;
    }
    it = unknown10.erase(it);
  }
}

void AiManager::unregist(gf::GF_OBJ_HANDLE *handle) {
  for (mm::mtl::FixedList<AiData *, unknown001>::iterator it = unknown10.begin(); it != unknown10.end();) {
    if ((*it)->getHandle() == handle) {
      AiScriptManager::end(AiScriptDataManager::getScriptName((*it)->getId()));
      // As in _clear: the game stores the null before erase's argument setup.
      if (*it != nullptr) {
        delete *it;
        *it = nullptr;
      }
      it = unknown10.erase(it);
    } else {
      ++it;
    }
  }
}

void AiManager::listenerGfObj(OBJEVT event, gf::GF_OBJ_HANDLE *handle, u32) {
  if (event == gf::IGfObjListener::OBJEVT_UNKNOWN_3) {
    unregist(handle);
  }
}

} // namespace ai

template mm::mtl::FixedList<ai::AiData *, 128>::iterator mm::mtl::FixedList<ai::AiData *, 128>::erase(mm::mtl::FixedList<ai::AiData *, 128>::iterator it);
