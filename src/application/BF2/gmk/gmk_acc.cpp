#include "gmk/gmk_acc.h"

#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_set.h"

namespace gmk {

GmkAcc::GmkAcc() : m_createInfo(), m_createInfoByBdatId(), m_aGmkBase(nullptr) {}

GmkAcc::GmkAcc(const CreateInfo &info) : m_createInfo(), m_createInfoByBdatId(), m_aGmkBase(nullptr) { create(info); }

GmkAcc::GmkAcc(const CreateInfoByBdatId &info) : m_createInfo(), m_createInfoByBdatId(), m_aGmkBase(nullptr) { create(info); }

GmkAcc::GmkAcc(const GmkAcc &other) : m_createInfo(), m_createInfoByBdatId(), m_aGmkBase(nullptr) {
  if (other.m_createInfo.isValid()) {
    create(other.m_createInfo);
  } else if (other.m_createInfoByBdatId.isValid()) {
    create(other.m_createInfoByBdatId);
  }
}

void GmkAcc::CreateInfo::validate(const AGmkBase &gmk) {
  IGmkList *list = gmk.m_createBaseInfo.m_ownerGmkEnemyList;
  unknown00 = list->getCreateInfo().m_gmkSet->m_createInfo.unknown04;
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
  m_createInfo = info;
  if (info.unknown0c) {
    update();
  }
  GmkAccManager::get()->addGmkAcc(this);
}

void GmkAcc::create(const CreateInfoByBdatId &info) {
  dispose();
  m_createInfoByBdatId = info;
  if (info.unknown08) {
    update();
  }
  GmkAccManager::get()->addGmkAcc(this);
}

bool GmkAcc::isValid() const { return m_aGmkBase != nullptr && m_aGmkBase->isValid(); }

void GmkAcc::dispose() {
  if (GmkAccManager::get() != nullptr) {
    GmkAccManager::get()->removeGmkAcc(this);
  }
  m_aGmkBase = nullptr;
  m_createInfoByBdatId = CreateInfoByBdatId();
  m_createInfo = CreateInfo();
}

void GmkAcc::update() {
  if (GmkAccManager::get() == nullptr || isValid()) {
    return;
  }
  if (m_createInfo.isValid()) {
    m_aGmkBase = GmkManager::get()->findGmkInstByGmkInstIndex(m_createInfo.unknown00, m_createInfo.unknown04, m_createInfo.unknown08);
  } else if (m_createInfoByBdatId.isValid()) {
    m_aGmkBase = GmkManager::get()->findFirstGmkInstByBdatId(m_createInfoByBdatId.unknown00, m_createInfoByBdatId.unknown04);
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
  if (acc == nullptr || (!acc->m_createInfo.isValid() && !acc->m_createInfoByBdatId.isValid())) {
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
    it.get()->m_aGmkBase = nullptr;
  }
  for (mm::mtl::IntrusiveList<GmkAcc>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    it.get()->m_aGmkBase = nullptr;
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
    if (it.get()->m_aGmkBase != nullptr && it.get()->m_aGmkBase->m_createBaseInfo.m_ownerGmkEnemyList == &list) {
      it.get()->m_aGmkBase = nullptr;
    }
  }
  list.getGmkType();
  for (mm::mtl::IntrusiveList<GmkAcc>::iterator it = get()->unknown20.begin(); it != get()->unknown20.end(); ++it) {
    GmkAcc *acc = it.get();
    if (acc->m_aGmkBase->m_createBaseInfo.m_ownerGmkEnemyList == &list) {
      acc->m_aGmkBase = nullptr;
      it = get()->unknown20.erase(it);
      --it;
      get()->unknown08.push_back(acc);
    }
  }
}

} // namespace gmk
