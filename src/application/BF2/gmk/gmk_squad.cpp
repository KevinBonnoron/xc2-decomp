#include "gmk/gmk_squad.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "framework/memory/framework_memory.h"
#include "gmk/gmk_set.h"
#include "ml/rand.h"
#include "mm_math/mm_quat.h"
#include <math.h>

namespace gmk {

template bool TGmkList<GmkSquadLeader, GmkSquadLeader::BdatInfo, 1145852243u, 2u, GmkSquadLeaderGobCustom>::initGmkBdatInfo(GmkSquadLeader::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkSquadMember, GmkSquadMember::BdatInfo, 1112363347u, 1u, GmkSquadMemberGobCustom>::initGmkBdatInfo(GmkSquadMember::BdatInfo &, int &, const AGmkBase &);

GmkType GmkSquadLeader::getGmkType() const { return GMK_TYPE; }

bool GmkSquadLeader::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkSquadLeader::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkSquadLeader::dispose() { AGmkBase::dispose(); }

void GmkSquadLeader::debugDraw() const {}

void GmkSquadLeader::debugUpdateMmf() {}

const IGmkList *GmkSquadLeader::getBindedSquadMemberList() const { return unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_SQUAD_MEMBER]; }

GmkType GmkSquadMember::getGmkType() const { return GMK_TYPE; }

bool GmkSquadMember::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkSquadMember::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkSquadMember::dispose() { AGmkBase::dispose(); }

void GmkSquadMember::debugUpdateMmf() {}

bool GmkSquad::isValid() const {
  if (unknown003() == nullptr) {
    return false;
  }
  if (!unknown003()->isValid()) {
    return false;
  }
  const IGmkList *list = unknown003()->getBindedSquadMemberList();
  if (list == nullptr || list->getInstNum() == 0) {
    return false;
  }
  return unknown70 != 0;
}

void GmkSquad::update(f32 deltaTime) {
  if (unknown78) {
    (this->*unknown78)(deltaTime);
  }
}

void GmkSquad::getPosRotY(mm::Vec3 &position, f32 &rotY, u32 index) const {
  position = unknowna0[index];
  rotY = unknownc8[index];
}

const GmkSquadLeader *GmkSquad::getBindedGmkSquadLeader() const {
  if (unknown003() == nullptr) {
    return nullptr;
  }
  if (!unknown003()->isValid()) {
    return nullptr;
  }
  const IGmkList *list = unknown003()->getBindedSquadMemberList();
  if (list == nullptr || list->getInstNum() == 0 || unknown70 == 0) {
    return nullptr;
  }
  return unknown003();
}

void GmkSquad::addGmkSquadNavi(GmkSquadNavi *navi) {
  if (unknown88.end() != unknown88.unknown002(unknown88.begin(), unknown88.end(), navi)) {
    return;
  }
  for (size_t i = 0; i < unknownf0.size(); i++) {
    if (!unknownf0[i]) {
      unknownf0[i] = true;
      navi->unknown28 = static_cast<int>(i);
      bool isInserted = false;
      for (mm::mtl::IntrusiveList<GmkSquadNavi>::iterator it = unknown88.begin(); it != unknown88.end(); ++it) {
        if (navi->unknown28 < it.get()->unknown28) {
          unknown88.insert(it, navi);
          isInserted = true;
          break;
        }
      }
      if (!isInserted) {
        unknown88.push_back(navi);
      }
      if (navi->unknown001() && navi->unknown28 == 0) {
        updatePosRotY(true);
      }
      return;
    }
  }
}

void GmkSquad::removeGmkSquadNavi(GmkSquadNavi *navi) {
  if (navi != nullptr && navi->intoNode()) {
    unknownf0[navi->unknown28] = false;
    unknown88.erase(navi);
    navi->unknown002();
  }
}

void GmkSquadNavi::create(const CreateInfo &info) {
  dispose();
  unknown10 = info;
  unknown10.unknown00->addGmkSquadNavi(this);
}

void GmkSquadNavi::dispose() {
  if (unknown10.unknown00 != nullptr && unknown10.unknown08 != gf::unknown020) {
    unknown10.unknown00->removeGmkSquadNavi(this);
    unknown002();
  }
}

u32 GmkSquadNavi::getMemberDefType() const {
  const GmkSquadLeader *leader = unknown10.unknown00->getBindedGmkSquadLeader();
  if (leader == nullptr) {
    return 0;
  }
  return leader->getData()->unknown00;
}

bool GmkSquadNavi::getPosRotY(mm::Vec3 &position, f32 &rotY) const {
  if (unknown001() && unknown10.unknown00->isValid()) {
    unknown10.unknown00->getPosRotY(position, rotY, unknown28);
    position += unknown30;
    return true;
  }
  return false;
}

bool GmkSquadNavi::isArrived(const mm::Vec3 &position) const {
  mm::Vec3 naviPosition;
  f32 rotY;
  if (!getPosRotY(naviPosition, rotY)) {
    return false;
  }
  f32 height = naviPosition.y - position.y;
  if (unknown10.unknown14 < height) {
    return false;
  }
  f32 x = naviPosition.x - position.x;
  f32 z = naviPosition.z - position.z;
  f32 distSq = x * x + z * z;
  return !(unknown10.unknown10 * unknown10.unknown10 < distSq);
}

void GmkSquad::updateMemberPosRotY_MemberDef_Circle(u32 index) {
  const GmkSquadLeader::Data *data = unknown003()->getData();
  const mm::Vec3 &center = unknowna0[0];
  f32 rotY = unknownc8[0];
  f32 halfAngle = ml::mtRandf1() * 6.2831855f * 0.5f;
  mm::Quat rotation;
  rotation.x = 0.0f;
  rotation.y = sinf(halfAngle);
  rotation.z = 0.0f;
  rotation.w = cosf(halfAngle);
  f32 distance = ml::mtRandf1(0.5f, 1.0f) * data->unknown04;
  mm::Vec3 offset = rotation.rotate(mm::Vec3::unitZ) * (distance * unknown2c);
  unknowna0[index] = offset + center;
  unknownc8[index] = rotY;
}

void GmkSquadNavi::update(const UpdateInfo &info) {
  GmkSquad *squad = unknown10.unknown00;
  if (!unknown001() || !squad->isValid()) {
    return;
  }
  if (squad->unknown003() != nullptr && squad->unknown003()->getData()->unknown00 == 2 && unknown28 != 0 && isArrived(info.position)) {
    unknown10.unknown00->updateMemberPosRotY_MemberDef_Circle(unknown28);
  }
}

GmkSquad::GmkSquad(const CreateInfo *info) : unknown2c(1.0f), unknown70(0), unknown78(nullptr) {
  if (info != nullptr) {
    create(*info);
  }
}

void GmkSquad::create(const CreateInfo &info) {
  dispose();
  if (GmkManager::get()->findGmkSet(info.unknown00) == nullptr) {
    return;
  }
  unknown20 = info;
  GmkAcc::CreateInfo accInfo;
  accInfo.unknown00 = info.unknown00;
  accInfo.unknown04 = GMK_TYPE_SQUAD_LEADER;
  accInfo.unknown08 = info.unknown04;
  m_bindedGmkSquadLeader.create(accInfo);
  unknown78 = &GmkSquad::seqInit;
  GmkSquadManager::get()->addGmkSquad(this);
}

void GmkSquad::dispose() {
  while (!unknown88.empty()) {
    unknown88.begin().get()->dispose();
  }
  GmkSquadManager::get()->removeGmkSquad(this);
  unknownf0.destroy();
  unknownc8.destroy();
  unknowna0.destroy();
  unknown70 = 0;
  unknown78 = nullptr;
  m_bindedGmkSquadLeader.dispose();
  unknown20 = CreateInfo();
}

void GmkSquad::seqInit(f32 deltaTime) {
  if (unknown003() == nullptr || !unknown003()->isValid()) {
    return;
  }
  const GmkSquadLeader *leader = unknown003();
  if (leader == nullptr) {
    return;
  }
  const IGmkList *list = leader->getBindedSquadMemberList();
  if (list == nullptr || list->getInstNum() == 0) {
    return;
  }
  const GmkSquadLeader::Data *data = leader->getData();
  switch (data->unknown00) {
  case 1:
    unknown70 = data->unknown0c + 1 - data->unknown08;
    break;
  case 2:
    unknown70 = unknown20.unknown08;
    break;
  }
  unknowna0.destroy();
  unknowna0.setAllocator(fw::FrameworkMemory::getAllocator(5));
  unknowna0.reserve(unknown70, 16);
  for (u32 i = 0; i < unknown70; i++) {
    unknowna0.push_back(mm::Vec3::zero);
  }
  unknownc8.destroy();
  unknownc8.setAllocator(fw::FrameworkMemory::getAllocator(5));
  unknownc8.reserve(unknown70);
  for (u32 i = 0; i < unknown70; i++) {
    unknownc8.push_back(0.0f);
  }
  updatePosRotY(false);
  unknownf0.destroy();
  unknownf0.setAllocator(fw::FrameworkMemory::getAllocator(5));
  unknownf0.reserve(unknown70);
  for (u32 i = 0; i < unknown70; i++) {
    unknownf0.push_back(false);
  }
  unknown78 = &GmkSquad::seqUpdate;
}

void GmkSquad::seqUpdate(f32 deltaTime) {
  if (isValid()) {
    updatePosRotY(false);
  } else {
    unknown78 = &GmkSquad::seqInit;
  }
}

void GmkSquadManager::update(f32 deltaTime) {
  for (mm::mtl::IntrusiveList<GmkSquad>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    it->update(deltaTime);
  }
}

void GmkSquadManager::addGmkSquad(GmkSquad *squad) {
  if (unknown08.end() == unknown08.unknown002(unknown08.begin(), unknown08.end(), squad)) {
    unknown08.push_back(squad);
  }
}

void GmkSquadManager::removeGmkSquad(GmkSquad *squad) {
  if (squad == nullptr) {
    return;
  }
  mm::mtl::IntrusiveList<GmkSquad>::iterator last = unknown08.end();
  for (mm::mtl::IntrusiveList<GmkSquad>::iterator it = unknown08.begin(); it != last; ++it) {
    if (it.get() == squad) {
      // The game tests the found squad against the end of the list again (cmp, b.eq at 0x71006158d0), although the loop condition already excludes it.
      if (last.get() != squad) {
        unknown08.erase(squad);
      }
      break;
    }
  }
}

void GmkSquadManager::clearGmkSquads() {
  for (mm::mtl::IntrusiveList<GmkSquad>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    it->release();
  }
  unknown08.clear();
}

void GmkSquadManager::debugDraw() const {
  for (mm::mtl::IntrusiveList<GmkSquad>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    it->debugDraw();
  }
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkSquadLeader::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSquadLeader::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSquadLeader::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkSquadLeader>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSquadMember::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSquadMember::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSquadMember::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkSquadMember>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSquadLeader>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSquadLeader>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkSquadMember>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkSquadMember>::resize(size_t);
template mm::mtl::PtrSingleton<gmk::GmkSquadManager>::~PtrSingleton();
