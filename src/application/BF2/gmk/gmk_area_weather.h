#pragma once
#include <stddef.h>

#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_phantom.h"

namespace gmk {

class GmkAreaWeatherGob;

class GmkAreaWeather : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_AREA_WEATHER;

  ~GmkAreaWeather() override { dispose(); }
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void createGmkPhantom();
  void dispose() override;

  GmkPhantom unknown50; // Inferred role: phantom; original member name unknown.
};

static_assert(offsetof(GmkAreaWeather, unknown50) == 0x50, "");
static_assert(sizeof(GmkAreaWeather) == 0xe0, "");

typedef TGmkList<GmkAreaWeather, GmkAreaWeather::BdatInfo, 0x52545741, 2, GmkAreaWeatherGob> GmkAreaWeatherList;

} // namespace gmk
