#include "gmk/gmk_acc.h"

#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_set.h"

namespace gmk {

void GmkAcc::CreateInfo::validate(const AGmkBase &gmk) {
  IGmkList *list = gmk.unknown08.unknown00;
  unknown00 = list->getCreateInfo().unknown08->unknown10.unknown04;
  unknown04 = gmk.getGmkType();
  u32 num = list->getInstNum();
  for (u32 i = 0; i < num; i++) {
    if (list->getInst(i) == &gmk) {
      unknown08 = i;
    }
  }
}

void GmkAcc::create(const CreateInfo &info) {
  dispose();
  unknown18 = info;
  if (info.unknown0c) {
    update();
  }
  GmkAccManager::get()->addGmkAcc(this);
}

void GmkAcc::create(const CreateInfoByBdatId &info) {
  dispose();
  unknown28 = info;
  if (info.unknown08) {
    update();
  }
  GmkAccManager::get()->addGmkAcc(this);
}

bool GmkAcc::isValid() const { return unknown38 != nullptr && unknown38->isValid(); }

void GmkAcc::dispose() {
  if (GmkAccManager::get() != nullptr) {
    GmkAccManager::get()->removeGmkAcc(this);
  }
  unknown38 = nullptr;
  unknown28 = CreateInfoByBdatId();
  unknown18 = CreateInfo();
}

void GmkAcc::update() {
  if (GmkAccManager::get() == nullptr || isValid()) {
    return;
  }
  if (unknown18.isValid()) {
    unknown38 = GmkManager::get()->findGmkInstByGmkInstIndex(unknown18.unknown00, unknown18.unknown04, unknown18.unknown08);
  } else if (unknown28.isValid()) {
    unknown38 = GmkManager::get()->findFirstGmkInstByBdatId(unknown28.unknown00, unknown28.unknown04);
  }
}

void GmkAccManager::addGmkAcc(GmkAcc *acc) {
  if (acc->isValid()) {
    unknown20.push_back(acc);
  } else {
    unknown08.push_back(acc);
  }
}

void GmkAccManager::removeGmkAcc(GmkAcc *acc) {
  if (acc == nullptr || (!acc->unknown18.isValid() && !acc->unknown28.isValid())) {
    return;
  }
  if (acc->isValid()) {
    unknown20.erase(acc);
  } else {
    unknown08.erase(acc);
  }
}

GmkAccManager::~GmkAccManager() {
  for (mm::mtl::IntrusiveList<GmkAcc>::iterator it = unknown20.begin(); it != unknown20.end(); ++it) {
    it.get()->unknown38 = nullptr;
  }
  for (mm::mtl::IntrusiveList<GmkAcc>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    it.get()->unknown38 = nullptr;
  }
}

void GmkAccManager::update() {
  for (mm::mtl::IntrusiveList<GmkAcc>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    GmkAcc *acc = it.get();
    acc->update();
    if (acc->isValid()) {
      it = unknown08.erase(it);
      --it;
      unknown20.push_back(acc);
    }
  }
}

void GmkAccManager::invalidateAccs(const IGmkList &list) {
  if (get() == nullptr) {
    return;
  }
  for (mm::mtl::IntrusiveList<GmkAcc>::iterator it = get()->unknown08.begin(); it != get()->unknown08.end(); ++it) {
    if (it.get()->unknown38 != nullptr && it.get()->unknown38->unknown08.unknown00 == &list) {
      it.get()->unknown38 = nullptr;
    }
  }
  list.getGmkType();
  for (mm::mtl::IntrusiveList<GmkAcc>::iterator it = get()->unknown20.begin(); it != get()->unknown20.end(); ++it) {
    GmkAcc *acc = it.get();
    if (acc->unknown38->unknown08.unknown00 == &list) {
      acc->unknown38 = nullptr;
      it = get()->unknown20.erase(it);
      --it;
      get()->unknown08.push_back(acc);
    }
  }
}

} // namespace gmk
