#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatMaplist : public mm::mtl::PtrSingleton<GfBdatMaplist> {
public:
  u32 getMaplistnameID(u32 map) const;
  u32 getMaplistzone(u32 map) const;
  const char *getMaplistresource(u32 map) const;
  u32 getMaplistw_ON_cndID(u32 map, u32 weather) const;
  u32 getMaplistw_OFF_cndID(u32 map, u32 weather) const;
  u32 getMaplistw_time_BNS(u32 map, u32 weather) const;
  u32 getMaplistw_end_time(u32 map, u32 weather) const;
  u32 getMaplistw_pop_rate(u32 map, u32 weather) const;
  u32 getMaplistw_type(u32 map, u32 weather) const;
  u32 getTimeInfomsg(u32 time) const;
  u32 getWeatherInfomsg(u32 weatherType) const;
  const char *getWeatherInfoeff(u32 weatherType) const;
  const char *getWeatherInfosnd(u32 weatherType) const;
  const char *getWeatherInfosndBegin(u32 weatherType) const;
};

} // namespace gf
