#include "gmk/gmk_area_weather.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "framework/coli/coli_object.h"
#include "gmk/gmk_set.h"
#include "mm_mtl/reference_object.h"

namespace gmk {

template bool TGmkList<GmkAreaWeather, GmkAreaWeather::BdatInfo, 1381259073u, 2u, GmkAreaWeatherGob>::initGmkBdatInfo(GmkAreaWeather::BdatInfo &, int &, const AGmkBase &);

GmkType GmkAreaWeather::getGmkType() const { return GMK_TYPE; }

bool GmkAreaWeather::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkAreaWeather::create(const CreateInfo &info) {
  AGmkBase::create(info);
  createGmkPhantom();
}

void GmkAreaWeather::createGmkPhantom() {
  const GmkSet *set = unknown08.unknown00->getCreateInfo().unknown08;
  if (set != nullptr && set->unknown10.unknown24) {
    return;
  }
  unknown50.create(*this, nullptr, false);
}

void GmkAreaWeather::dispose() {
  if (unknown50.unknown78 != nullptr) {
    unknown50.unknown78->setColiUserData(nullptr);
    unknown50.unknown78->setListener(nullptr);
  }
  unknown50.unknown83 = false;
  mm::mtl::safeRelease(unknown50.unknown78);
  unknown50.unknown70 = nullptr;
  AGmkBase::dispose();
}

} // namespace gmk
