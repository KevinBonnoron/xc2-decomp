#pragma once
#include "gf/data/gf_data_map.h"
#include "types.h"

namespace gf {

class GfFieldWeather {
public:
  static u32 getCurrentMapWeatherBit(bool isPrevious);
  static void setMapWeatherID(WEATHERID weather);
  static CLOUD_SEA getCloudSea(u32 map);
};

} // namespace gf
