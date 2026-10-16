#pragma once
#include "gf/data/gf_data_map.h"
#include "types.h"

namespace event {

class EnvTransfer {
public:
  EnvTransfer();
  virtual ~EnvTransfer() {}
  void clear();
  void save();
  void load();

protected:
  u32 mHour;
  u32 mMinute;
  gf::WEATHERID mWeather;
  gf::CLOUD_SEA mCloudSea;
};

static_assert(sizeof(EnvTransfer) == 0x18, "");

} // namespace event
