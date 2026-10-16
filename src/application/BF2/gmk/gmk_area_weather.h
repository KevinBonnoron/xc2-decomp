#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkAreaWeatherGob;

class GmkAreaWeather : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_AREA_WEATHER;

  ~GmkAreaWeather() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;

  u8 _48[0xe0 - 0x48];
};

static_assert(sizeof(GmkAreaWeather) == 0xe0, "");

typedef TGmkList<GmkAreaWeather, GmkAreaWeather::BdatInfo, 0x52545741, 2, GmkAreaWeatherGob> GmkAreaWeatherList;

} // namespace gmk
