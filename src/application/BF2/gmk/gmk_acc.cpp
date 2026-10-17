#include "gmk/gmk_acc.h"

#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_set.h"

namespace gmk {

void GmkAcc::CreateInfo::validate(const AGmkBase &gmk) {
  IGmkList *list = gmk.baseInfo.list;
  gmkSetId = list->getCreateInfo().set->createInfo.gmkSetId;
  type = gmk.getGmkType();
  u32 num = list->getInstNum();
  for (u32 i = 0; i < num; i++) {
    if (list->getInst(i) == &gmk) {
      index = i;
    }
  }
}

void GmkAcc::create(const CreateInfo &info) {
  dispose();
  createInfo = info;
  if (info.isUpdateImmediate) {
    update();
  }
  GmkAccManager::get()->addGmkAcc(this);
}

void GmkAcc::create(const CreateInfoByBdatId &info) {
  dispose();
  createInfoByBdatId = info;
  if (info.isUpdateImmediate) {
    update();
  }
  GmkAccManager::get()->addGmkAcc(this);
}

bool GmkAcc::isValid() const { return gmk != nullptr && gmk->isValid(); }

void GmkAcc::dispose() {
  if (GmkAccManager::get() != nullptr) {
    GmkAccManager::get()->removeGmkAcc(this);
  }
  gmk = nullptr;
  createInfoByBdatId = CreateInfoByBdatId();
  createInfo = CreateInfo();
}

void GmkAcc::update() {
  if (GmkAccManager::get() == nullptr || isValid()) {
    return;
  }
  if (createInfo.isValid()) {
    gmk = GmkManager::get()->findGmkInstByGmkInstIndex(createInfo.gmkSetId, createInfo.type, createInfo.index);
  } else if (createInfoByBdatId.isValid()) {
    gmk = GmkManager::get()->findFirstGmkInstByBdatId(createInfoByBdatId.type, createInfoByBdatId.bdatId);
  }
}

void GmkAccManager::addGmkAcc(GmkAcc *acc) {
  if (acc->isValid()) {
    validAccs.push_back(acc);
  } else {
    invalidAccs.push_back(acc);
  }
}

void GmkAccManager::removeGmkAcc(GmkAcc *acc) {
  if (acc == nullptr || (!acc->createInfo.isValid() && !acc->createInfoByBdatId.isValid())) {
    return;
  }
  if (acc->isValid()) {
    validAccs.erase(acc);
  } else {
    invalidAccs.erase(acc);
  }
}

GmkAccManager::~GmkAccManager() {
  for (mm::mtl::IntrusiveList<GmkAcc>::iterator it = validAccs.begin(); it != validAccs.end(); ++it) {
    it.get()->gmk = nullptr;
  }
  for (mm::mtl::IntrusiveList<GmkAcc>::iterator it = invalidAccs.begin(); it != invalidAccs.end(); ++it) {
    it.get()->gmk = nullptr;
  }
}

void GmkAccManager::update() {
  for (mm::mtl::IntrusiveList<GmkAcc>::iterator it = invalidAccs.begin(); it != invalidAccs.end(); ++it) {
    GmkAcc *acc = it.get();
    acc->update();
    if (acc->isValid()) {
      it = invalidAccs.erase(it);
      --it;
      validAccs.push_back(acc);
    }
  }
}

void GmkAccManager::invalidateAccs(const IGmkList &list) {
  if (get() == nullptr) {
    return;
  }
  for (mm::mtl::IntrusiveList<GmkAcc>::iterator it = get()->invalidAccs.begin(); it != get()->invalidAccs.end(); ++it) {
    if (it.get()->gmk != nullptr && it.get()->gmk->baseInfo.list == &list) {
      it.get()->gmk = nullptr;
    }
  }
  list.getGmkType();
  for (mm::mtl::IntrusiveList<GmkAcc>::iterator it = get()->validAccs.begin(); it != get()->validAccs.end(); ++it) {
    GmkAcc *acc = it.get();
    if (acc->gmk->baseInfo.list == &list) {
      acc->gmk = nullptr;
      it = get()->validAccs.erase(it);
      --it;
      get()->invalidAccs.push_back(acc);
    }
  }
}

} // namespace gmk
