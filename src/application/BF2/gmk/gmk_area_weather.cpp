#include "gmk/gmk_area_weather.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "framework/coli/coli_object.h"
#include "gmk/gmk_set.h"
#include "mm_mtl/reference_object.h"

namespace gmk {

template bool TGmkList<GmkAreaWeather, GmkAreaWeather::BdatInfo, 1381259073u, 2u, GmkAreaWeatherGob>::initGmkBdatInfo(GmkAreaWeather::BdatInfo &, int &, const AGmkBase &);

GmkType GmkAreaWeather::getGmkType() const { return GMK_TYPE; }

bool GmkAreaWeather::isValid() const { return m_createBaseInfo.m_ownerGmkEnemyList != nullptr && m_createInfo.unknown08 != nullptr; }

void GmkAreaWeather::create(const CreateInfo &info) {
  AGmkBase::create(info);
  createGmkPhantom();
}

void GmkAreaWeather::createGmkPhantom() {
  const GmkSet *set = m_createBaseInfo.m_ownerGmkEnemyList->getCreateInfo().m_gmkSet;
  if (set != nullptr && set->m_createInfo.unknown24) {
    return;
  }
  m_gmkPhantom.create(*this, nullptr, false);
}

void GmkAreaWeather::dispose() {
  if (m_gmkPhantom.unknown78 != nullptr) {
    m_gmkPhantom.unknown78->setColiUserData(nullptr);
    m_gmkPhantom.unknown78->setListener(nullptr);
  }
  m_gmkPhantom.unknown83 = false;
  mm::mtl::safeRelease(m_gmkPhantom.unknown78);
  m_gmkPhantom.unknown70 = nullptr;
  AGmkBase::dispose();
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkAreaWeather::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkAreaWeather::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkAreaWeather::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkAreaWeather>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkAreaWeather>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkAreaWeather>::resize(size_t);
