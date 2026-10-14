#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatMaplist : public mm::mtl::PtrSingleton<GfBdatMaplist>, public GfBdatRefresh {
public:
  u32 getMaplistStart() const;
  const char *getMaplistresource(u32 id) const;
  const char *getMaplistselect(u32 id) const;
  u32 getMaplistrscGmkId(u32 id) const;
  u32 getMaplistene_disp_r(u32 id) const;
  u32 getMaplistene_disp_h(u32 id) const;
  u32 getMaplistene_release_r(u32 id) const;
  u32 getMaplistene_release_h(u32 id) const;
  u32 getMaplistwa_type(u32 id) const;
  u32 getMaplistwa_pop_rate(u32 id) const;
  u32 getMaplistwa_time_BNS(u32 id) const;
  u32 getMaplistwa_end_time(u32 id) const;
  u32 getMaplistwb_type(u32 id) const;
  u32 getMaplistwb_pop_rate(u32 id) const;
  u32 getMaplistwb_time_BNS(u32 id) const;
  u32 getMaplistwb_end_time(u32 id) const;
  u32 getMaplistwc_type(u32 id) const;
  u32 getMaplistwc_pop_rate(u32 id) const;
  u32 getMaplistwc_time_BNS(u32 id) const;
  u32 getMaplistwc_end_time(u32 id) const;
  u32 getMaplistwd_type(u32 id) const;
  u32 getMaplistwd_pop_rate(u32 id) const;
  u32 getMaplistwd_time_BNS(u32 id) const;
  u32 getMaplistwd_end_time(u32 id) const;
  u32 getMaplistwind_mor(u32 id) const;
  u32 getMaplistwind_non(u32 id) const;
  u32 getMaplistwind_eve(u32 id) const;
  u32 getMaplistwind_nit(u32 id) const;
  u32 getMaplistwind_mnit(u32 id) const;
  u32 getMaplistwind_emor(u32 id) const;
  u32 getMaplistwind_WA(u32 id) const;
  u32 getMaplistwind_WB(u32 id) const;
  u32 getMaplistwind_WC(u32 id) const;
  u32 getMaplistwind_WD(u32 id) const;
  u32 getMaplistweatherATR(u32 id) const;
  u32 getMapliste_repoptime(u32 id) const;
  u32 getMaplistm_repoptime(u32 id) const;
  u32 getMaplistmapATR(u32 id) const;
  u32 getMaplistwa_ON_cndID(u32 id) const;
  u32 getMaplistwa_OFF_cndID(u32 id) const;
  u32 getMaplistwb_ON_cndID(u32 id) const;
  u32 getMaplistwb_OFF_cndID(u32 id) const;
  u32 getMaplistwc_ON_cndID(u32 id) const;
  u32 getMaplistwc_OFF_cndID(u32 id) const;
  u32 getMaplistwd_ON_cndID(u32 id) const;
  u32 getMaplistwd_OFF_cndID(u32 id) const;
  u32 getMapliststopTIME_cndID(u32 id) const;
  u32 getMaplistebb_ON_cndID(u32 id) const;
  u32 getMaplistebb_inn_cndID(u32 id) const;
  u32 getMaplistebb_pop_rate(u32 id) const;
  u32 getMaplistst_allOFF_cndID(u32 id) const;
  u32 getMaplistst_OFF_cndID(u32 id) const;
  u32 getMaplistbgm_cndID(u32 id) const;
  u32 getMaplistname_cndID(u32 id) const;
  u32 getMaplistnameID(u32 id) const;
  u32 getMaplistchange_nameID(u32 id) const;
  u32 getMaplistmapON_cndID(u32 id) const;
  u32 getMaplisttextID(u32 id) const;
  u32 getMapliste_balloondisp_r(u32 id) const;
  u32 getMaplistzone(u32 id) const;
  u32 getWeatherInfoStart() const;
  u32 getWeatherInfomsg(u32 id) const;
  const char *getWeatherInfoeff(u32 id) const;
  const char *getWeatherInfosnd(u32 id) const;
  const char *getWeatherInfosndBegin(u32 id) const;
  u32 getTimeInfoStart() const;
  u32 getTimeInfomsg(u32 id) const;

  u32 getMaplistw_ON_cndID(u32 map, u32 weather) const;
  u32 getMaplistw_OFF_cndID(u32 map, u32 weather) const;
  u32 getMaplistw_time_BNS(u32 map, u32 weather) const;
  u32 getMaplistw_end_time(u32 map, u32 weather) const;
  u32 getMaplistw_pop_rate(u32 map, u32 weather) const;
  u32 getMaplistw_type(u32 map, u32 weather) const;

private:
  CBdatWrapper *unknown10; // Inferred label: mMaplist; original member name unknown.
  CBdatWrapper *unknown18; // Inferred label: mWeatherInfo; original member name unknown.
  CBdatWrapper *unknown20; // Inferred label: mTimeInfo; original member name unknown.
};

} // namespace gf
