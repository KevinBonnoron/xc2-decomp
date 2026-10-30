#include "gmk/gmk_squad.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "gmk/gmk_set.h"

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
  if (m_bindedGmkSquadLeader == nullptr) {
    return false;
  }
  if (!m_bindedGmkSquadLeader->isValid()) {
    return false;
  }
  const IGmkList *list = m_bindedGmkSquadLeader->getBindedSquadMemberList();
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

GmkSquadLeader *GmkSquad::getBindedGmkSquadLeader() const {
  if (m_bindedGmkSquadLeader == nullptr) {
    return nullptr;
  }
  if (!m_bindedGmkSquadLeader->isValid()) {
    return nullptr;
  }
  const IGmkList *list = m_bindedGmkSquadLeader->getBindedSquadMemberList();
  if (list == nullptr || list->getInstNum() == 0 || unknown70 == 0) {
    return nullptr;
  }
  return m_bindedGmkSquadLeader;
}

void GmkSquad::removeGmkSquadNavi(GmkSquadNavi *navi) {
  if (navi != nullptr && navi->intoNode()) {
    unknownf0[navi->unknown28] = false;
    unknown88.erase(navi);
    navi->unknown002();
  }
}

void GmkSquadNavi::dispose() {
  if (unknown10 != nullptr && unknown18 != gf::INVALID_HANDLE) {
    unknown10->removeGmkSquadNavi(this);
    unknown002();
  }
}

u32 GmkSquadNavi::getMemberDefType() const {
  GmkSquadLeader *leader = unknown10->getBindedGmkSquadLeader();
  if (leader == nullptr) {
    return 0;
  }
  return leader->getData()->unknown00;
}

bool GmkSquadNavi::getPosRotY(mm::Vec3 &position, f32 &rotY) const {
  if (unknown001() && unknown10->isValid()) {
    unknown10->getPosRotY(position, rotY, unknown28);
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
  if (unknown20.y < height) {
    return false;
  }
  f32 x = naviPosition.x - position.x;
  f32 z = naviPosition.z - position.z;
  f32 distSq = x * x + z * z;
  return !(unknown20.x * unknown20.x < distSq);
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
