#include "event/res_pack_manager.h"

#include <stddef.h>

#include "event/memory_manager.h"
#include "event/res_pack.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

ResPackManager::ResPackManager() {}

void ResPackManager::clear() {
  for (ResPack **it = mPacks.begin(); it != mPacks.end(); it++) {
    ResPack *pack = *it;
    pack->clear();
    delete pack;
  }
  mPacks.clear();
}

void ResPackManager::update() {
  for (size_t i = 0; i < mPacks.size(); i++) {
    mPacks[i]->update();
  }
}

void ResPackManager::draw() {
  for (size_t i = 0; i < mPacks.size(); i++) {
    mPacks[i]->draw();
  }
}

void ResPackManager::load(mtl::ALLOC_HANDLE handle, const char *path, IResPackEvent *event) {
  ResPack *pack = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle()) ResPack();
  pack->load(handle, path, event);
  mPacks.push_back(pack);
}

bool ResPackManager::isLoading() const {
  for (size_t i = 0; i < mPacks.size(); i++) {
    if (mPacks[i]->isLoading()) {
      return true;
    }
  }
  return false;
}

} // namespace event
