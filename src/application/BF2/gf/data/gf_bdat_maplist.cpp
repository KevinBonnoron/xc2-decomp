#include "gf/data/gf_bdat_maplist.h"
#include "bdat.h"

namespace gf {
namespace _gfbml {

enum {
  Maplistresource,
  Maplistselect,
  MaplistrscGmkId,
  Maplistene_disp_r,
  Maplistene_disp_h,
  Maplistene_release_r,
  Maplistene_release_h,
  Maplistwa_type,
  Maplistwa_pop_rate,
  Maplistwa_time_BNS,
  Maplistwa_end_time,
  Maplistwb_type,
  Maplistwb_pop_rate,
  Maplistwb_time_BNS,
  Maplistwb_end_time,
  Maplistwc_type,
  Maplistwc_pop_rate,
  Maplistwc_time_BNS,
  Maplistwc_end_time,
  Maplistwd_type,
  Maplistwd_pop_rate,
  Maplistwd_time_BNS,
  Maplistwd_end_time,
  Maplistwind_mor,
  Maplistwind_non,
  Maplistwind_eve,
  Maplistwind_nit,
  Maplistwind_mnit,
  Maplistwind_emor,
  Maplistwind_WA,
  Maplistwind_WB,
  Maplistwind_WC,
  Maplistwind_WD,
  MaplistweatherATR,
  Mapliste_repoptime,
  Maplistm_repoptime,
  MaplistmapATR,
  Maplistwa_ON_cndID,
  Maplistwa_OFF_cndID,
  Maplistwb_ON_cndID,
  Maplistwb_OFF_cndID,
  Maplistwc_ON_cndID,
  Maplistwc_OFF_cndID,
  Maplistwd_ON_cndID,
  Maplistwd_OFF_cndID,
  MapliststopTIME_cndID,
  Maplistebb_ON_cndID,
  Maplistebb_inn_cndID,
  Maplistebb_pop_rate,
  Maplistst_allOFF_cndID,
  Maplistst_OFF_cndID,
  Maplistbgm_cndID,
  Maplistname_cndID,
  MaplistnameID,
  Maplistchange_nameID,
  MaplistmapON_cndID,
  MaplisttextID,
  Mapliste_balloondisp_r,
  Maplistzone,
  WeatherInfomsg,
  WeatherInfoeff,
  WeatherInfosnd,
  WeatherInfosndBegin,
  TimeInfomsg,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];

void initMaplistresource(const CBdatWrapper &wrapper) { s_members[Maplistresource] = Bdat::getMember(wrapper.data, "resource"); }

const char *getMaplistresource(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistresource] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[Maplistresource], id, 7).valueString;
}

void initMaplistselect(const CBdatWrapper &wrapper) { s_members[Maplistselect] = Bdat::getMember(wrapper.data, "select"); }

const char *getMaplistselect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistselect] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[Maplistselect], id, 7).valueString;
}

void initMaplistrscGmkId(const CBdatWrapper &wrapper) { s_members[MaplistrscGmkId] = Bdat::getMember(wrapper.data, "rscGmkId"); }

u32 getMaplistrscGmkId(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MaplistrscGmkId] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MaplistrscGmkId], id, 3).valueU32;
}

void initMaplistene_disp_r(const CBdatWrapper &wrapper) { s_members[Maplistene_disp_r] = Bdat::getMember(wrapper.data, "ene_disp_r"); }

u32 getMaplistene_disp_r(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistene_disp_r] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistene_disp_r], id, 1).valueU8;
}

void initMaplistene_disp_h(const CBdatWrapper &wrapper) { s_members[Maplistene_disp_h] = Bdat::getMember(wrapper.data, "ene_disp_h"); }

u32 getMaplistene_disp_h(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistene_disp_h] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistene_disp_h], id, 1).valueU8;
}

void initMaplistene_release_r(const CBdatWrapper &wrapper) { s_members[Maplistene_release_r] = Bdat::getMember(wrapper.data, "ene_release_r"); }

u32 getMaplistene_release_r(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistene_release_r] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistene_release_r], id, 1).valueU8;
}

void initMaplistene_release_h(const CBdatWrapper &wrapper) { s_members[Maplistene_release_h] = Bdat::getMember(wrapper.data, "ene_release_h"); }

u32 getMaplistene_release_h(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistene_release_h] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistene_release_h], id, 1).valueU8;
}

void initMaplistwa_type(const CBdatWrapper &wrapper) { s_members[Maplistwa_type] = Bdat::getMember(wrapper.data, "wa_type"); }

u32 getMaplistwa_type(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwa_type] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwa_type], id, 1).valueU8;
}

void initMaplistwa_pop_rate(const CBdatWrapper &wrapper) { s_members[Maplistwa_pop_rate] = Bdat::getMember(wrapper.data, "wa_pop_rate"); }

u32 getMaplistwa_pop_rate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwa_pop_rate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwa_pop_rate], id, 1).valueU8;
}

void initMaplistwa_time_BNS(const CBdatWrapper &wrapper) { s_members[Maplistwa_time_BNS] = Bdat::getMember(wrapper.data, "wa_time_BNS"); }

u32 getMaplistwa_time_BNS(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwa_time_BNS] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwa_time_BNS], id, 2).valueU16;
}

void initMaplistwa_end_time(const CBdatWrapper &wrapper) { s_members[Maplistwa_end_time] = Bdat::getMember(wrapper.data, "wa_end_time"); }

u32 getMaplistwa_end_time(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwa_end_time] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwa_end_time], id, 1).valueU8;
}

void initMaplistwb_type(const CBdatWrapper &wrapper) { s_members[Maplistwb_type] = Bdat::getMember(wrapper.data, "wb_type"); }

u32 getMaplistwb_type(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwb_type] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwb_type], id, 1).valueU8;
}

void initMaplistwb_pop_rate(const CBdatWrapper &wrapper) { s_members[Maplistwb_pop_rate] = Bdat::getMember(wrapper.data, "wb_pop_rate"); }

u32 getMaplistwb_pop_rate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwb_pop_rate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwb_pop_rate], id, 1).valueU8;
}

void initMaplistwb_time_BNS(const CBdatWrapper &wrapper) { s_members[Maplistwb_time_BNS] = Bdat::getMember(wrapper.data, "wb_time_BNS"); }

u32 getMaplistwb_time_BNS(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwb_time_BNS] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwb_time_BNS], id, 2).valueU16;
}

void initMaplistwb_end_time(const CBdatWrapper &wrapper) { s_members[Maplistwb_end_time] = Bdat::getMember(wrapper.data, "wb_end_time"); }

u32 getMaplistwb_end_time(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwb_end_time] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwb_end_time], id, 1).valueU8;
}

void initMaplistwc_type(const CBdatWrapper &wrapper) { s_members[Maplistwc_type] = Bdat::getMember(wrapper.data, "wc_type"); }

u32 getMaplistwc_type(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwc_type] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwc_type], id, 1).valueU8;
}

void initMaplistwc_pop_rate(const CBdatWrapper &wrapper) { s_members[Maplistwc_pop_rate] = Bdat::getMember(wrapper.data, "wc_pop_rate"); }

u32 getMaplistwc_pop_rate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwc_pop_rate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwc_pop_rate], id, 1).valueU8;
}

void initMaplistwc_time_BNS(const CBdatWrapper &wrapper) { s_members[Maplistwc_time_BNS] = Bdat::getMember(wrapper.data, "wc_time_BNS"); }

u32 getMaplistwc_time_BNS(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwc_time_BNS] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwc_time_BNS], id, 2).valueU16;
}

void initMaplistwc_end_time(const CBdatWrapper &wrapper) { s_members[Maplistwc_end_time] = Bdat::getMember(wrapper.data, "wc_end_time"); }

u32 getMaplistwc_end_time(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwc_end_time] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwc_end_time], id, 1).valueU8;
}

void initMaplistwd_type(const CBdatWrapper &wrapper) { s_members[Maplistwd_type] = Bdat::getMember(wrapper.data, "wd_type"); }

u32 getMaplistwd_type(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwd_type] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwd_type], id, 1).valueU8;
}

void initMaplistwd_pop_rate(const CBdatWrapper &wrapper) { s_members[Maplistwd_pop_rate] = Bdat::getMember(wrapper.data, "wd_pop_rate"); }

u32 getMaplistwd_pop_rate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwd_pop_rate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwd_pop_rate], id, 1).valueU8;
}

void initMaplistwd_time_BNS(const CBdatWrapper &wrapper) { s_members[Maplistwd_time_BNS] = Bdat::getMember(wrapper.data, "wd_time_BNS"); }

u32 getMaplistwd_time_BNS(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwd_time_BNS] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwd_time_BNS], id, 2).valueU16;
}

void initMaplistwd_end_time(const CBdatWrapper &wrapper) { s_members[Maplistwd_end_time] = Bdat::getMember(wrapper.data, "wd_end_time"); }

u32 getMaplistwd_end_time(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwd_end_time] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwd_end_time], id, 1).valueU8;
}

void initMaplistwind_mor(const CBdatWrapper &wrapper) { s_members[Maplistwind_mor] = Bdat::getMember(wrapper.data, "wind_mor"); }

u32 getMaplistwind_mor(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwind_mor] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwind_mor], id, 1).valueU8;
}

void initMaplistwind_non(const CBdatWrapper &wrapper) { s_members[Maplistwind_non] = Bdat::getMember(wrapper.data, "wind_non"); }

u32 getMaplistwind_non(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwind_non] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwind_non], id, 1).valueU8;
}

void initMaplistwind_eve(const CBdatWrapper &wrapper) { s_members[Maplistwind_eve] = Bdat::getMember(wrapper.data, "wind_eve"); }

u32 getMaplistwind_eve(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwind_eve] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwind_eve], id, 1).valueU8;
}

void initMaplistwind_nit(const CBdatWrapper &wrapper) { s_members[Maplistwind_nit] = Bdat::getMember(wrapper.data, "wind_nit"); }

u32 getMaplistwind_nit(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwind_nit] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwind_nit], id, 1).valueU8;
}

void initMaplistwind_mnit(const CBdatWrapper &wrapper) { s_members[Maplistwind_mnit] = Bdat::getMember(wrapper.data, "wind_mnit"); }

u32 getMaplistwind_mnit(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwind_mnit] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwind_mnit], id, 1).valueU8;
}

void initMaplistwind_emor(const CBdatWrapper &wrapper) { s_members[Maplistwind_emor] = Bdat::getMember(wrapper.data, "wind_emor"); }

u32 getMaplistwind_emor(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwind_emor] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwind_emor], id, 1).valueU8;
}

void initMaplistwind_WA(const CBdatWrapper &wrapper) { s_members[Maplistwind_WA] = Bdat::getMember(wrapper.data, "wind_WA"); }

u32 getMaplistwind_WA(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwind_WA] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwind_WA], id, 1).valueU8;
}

void initMaplistwind_WB(const CBdatWrapper &wrapper) { s_members[Maplistwind_WB] = Bdat::getMember(wrapper.data, "wind_WB"); }

u32 getMaplistwind_WB(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwind_WB] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwind_WB], id, 1).valueU8;
}

void initMaplistwind_WC(const CBdatWrapper &wrapper) { s_members[Maplistwind_WC] = Bdat::getMember(wrapper.data, "wind_WC"); }

u32 getMaplistwind_WC(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwind_WC] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwind_WC], id, 1).valueU8;
}

void initMaplistwind_WD(const CBdatWrapper &wrapper) { s_members[Maplistwind_WD] = Bdat::getMember(wrapper.data, "wind_WD"); }

u32 getMaplistwind_WD(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwind_WD] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwind_WD], id, 1).valueU8;
}

void initMaplistweatherATR(const CBdatWrapper &wrapper) { s_members[MaplistweatherATR] = Bdat::getMember(wrapper.data, "weatherATR"); }

u32 getMaplistweatherATR(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MaplistweatherATR] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MaplistweatherATR], id, 1).valueU8;
}

void initMapliste_repoptime(const CBdatWrapper &wrapper) { s_members[Mapliste_repoptime] = Bdat::getMember(wrapper.data, "e_repoptime"); }

u32 getMapliste_repoptime(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Mapliste_repoptime] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Mapliste_repoptime], id, 1).valueU8;
}

void initMaplistm_repoptime(const CBdatWrapper &wrapper) { s_members[Maplistm_repoptime] = Bdat::getMember(wrapper.data, "m_repoptime"); }

u32 getMaplistm_repoptime(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistm_repoptime] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistm_repoptime], id, 1).valueU8;
}

void initMaplistmapATR(const CBdatWrapper &wrapper) { s_members[MaplistmapATR] = Bdat::getMember(wrapper.data, "mapATR"); }

u32 getMaplistmapATR(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MaplistmapATR] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MaplistmapATR], id, 1).valueU8;
}

void initMaplistwa_ON_cndID(const CBdatWrapper &wrapper) { s_members[Maplistwa_ON_cndID] = Bdat::getMember(wrapper.data, "wa_ON_cndID"); }

u32 getMaplistwa_ON_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwa_ON_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwa_ON_cndID], id, 2).valueU16;
}

void initMaplistwa_OFF_cndID(const CBdatWrapper &wrapper) { s_members[Maplistwa_OFF_cndID] = Bdat::getMember(wrapper.data, "wa_OFF_cndID"); }

u32 getMaplistwa_OFF_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwa_OFF_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwa_OFF_cndID], id, 2).valueU16;
}

void initMaplistwb_ON_cndID(const CBdatWrapper &wrapper) { s_members[Maplistwb_ON_cndID] = Bdat::getMember(wrapper.data, "wb_ON_cndID"); }

u32 getMaplistwb_ON_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwb_ON_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwb_ON_cndID], id, 2).valueU16;
}

void initMaplistwb_OFF_cndID(const CBdatWrapper &wrapper) { s_members[Maplistwb_OFF_cndID] = Bdat::getMember(wrapper.data, "wb_OFF_cndID"); }

u32 getMaplistwb_OFF_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwb_OFF_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwb_OFF_cndID], id, 2).valueU16;
}

void initMaplistwc_ON_cndID(const CBdatWrapper &wrapper) { s_members[Maplistwc_ON_cndID] = Bdat::getMember(wrapper.data, "wc_ON_cndID"); }

u32 getMaplistwc_ON_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwc_ON_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwc_ON_cndID], id, 2).valueU16;
}

void initMaplistwc_OFF_cndID(const CBdatWrapper &wrapper) { s_members[Maplistwc_OFF_cndID] = Bdat::getMember(wrapper.data, "wc_OFF_cndID"); }

u32 getMaplistwc_OFF_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwc_OFF_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwc_OFF_cndID], id, 2).valueU16;
}

void initMaplistwd_ON_cndID(const CBdatWrapper &wrapper) { s_members[Maplistwd_ON_cndID] = Bdat::getMember(wrapper.data, "wd_ON_cndID"); }

u32 getMaplistwd_ON_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwd_ON_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwd_ON_cndID], id, 2).valueU16;
}

void initMaplistwd_OFF_cndID(const CBdatWrapper &wrapper) { s_members[Maplistwd_OFF_cndID] = Bdat::getMember(wrapper.data, "wd_OFF_cndID"); }

u32 getMaplistwd_OFF_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistwd_OFF_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistwd_OFF_cndID], id, 2).valueU16;
}

void initMapliststopTIME_cndID(const CBdatWrapper &wrapper) { s_members[MapliststopTIME_cndID] = Bdat::getMember(wrapper.data, "stopTIME_cndID"); }

u32 getMapliststopTIME_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MapliststopTIME_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MapliststopTIME_cndID], id, 2).valueU16;
}

void initMaplistebb_ON_cndID(const CBdatWrapper &wrapper) { s_members[Maplistebb_ON_cndID] = Bdat::getMember(wrapper.data, "ebb_ON_cndID"); }

u32 getMaplistebb_ON_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistebb_ON_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistebb_ON_cndID], id, 2).valueU16;
}

void initMaplistebb_inn_cndID(const CBdatWrapper &wrapper) { s_members[Maplistebb_inn_cndID] = Bdat::getMember(wrapper.data, "ebb_inn_cndID"); }

u32 getMaplistebb_inn_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistebb_inn_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistebb_inn_cndID], id, 2).valueU16;
}

void initMaplistebb_pop_rate(const CBdatWrapper &wrapper) { s_members[Maplistebb_pop_rate] = Bdat::getMember(wrapper.data, "ebb_pop_rate"); }

u32 getMaplistebb_pop_rate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistebb_pop_rate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistebb_pop_rate], id, 1).valueU8;
}

void initMaplistst_allOFF_cndID(const CBdatWrapper &wrapper) { s_members[Maplistst_allOFF_cndID] = Bdat::getMember(wrapper.data, "st_allOFF_cndID"); }

u32 getMaplistst_allOFF_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistst_allOFF_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistst_allOFF_cndID], id, 2).valueU16;
}

void initMaplistst_OFF_cndID(const CBdatWrapper &wrapper) { s_members[Maplistst_OFF_cndID] = Bdat::getMember(wrapper.data, "st_OFF_cndID"); }

u32 getMaplistst_OFF_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistst_OFF_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistst_OFF_cndID], id, 2).valueU16;
}

void initMaplistbgm_cndID(const CBdatWrapper &wrapper) { s_members[Maplistbgm_cndID] = Bdat::getMember(wrapper.data, "bgm_cndID"); }

u32 getMaplistbgm_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistbgm_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistbgm_cndID], id, 2).valueU16;
}

void initMaplistname_cndID(const CBdatWrapper &wrapper) { s_members[Maplistname_cndID] = Bdat::getMember(wrapper.data, "name_cndID"); }

u32 getMaplistname_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistname_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistname_cndID], id, 2).valueU16;
}

void initMaplistnameID(const CBdatWrapper &wrapper) { s_members[MaplistnameID] = Bdat::getMember(wrapper.data, "nameID"); }

u32 getMaplistnameID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MaplistnameID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MaplistnameID], id, 2).valueU16;
}

void initMaplistchange_nameID(const CBdatWrapper &wrapper) { s_members[Maplistchange_nameID] = Bdat::getMember(wrapper.data, "change_nameID"); }

u32 getMaplistchange_nameID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistchange_nameID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistchange_nameID], id, 2).valueU16;
}

void initMaplistmapON_cndID(const CBdatWrapper &wrapper) { s_members[MaplistmapON_cndID] = Bdat::getMember(wrapper.data, "mapON_cndID"); }

u32 getMaplistmapON_cndID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MaplistmapON_cndID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MaplistmapON_cndID], id, 2).valueU16;
}

void initMaplisttextID(const CBdatWrapper &wrapper) { s_members[MaplisttextID] = Bdat::getMember(wrapper.data, "textID"); }

u32 getMaplisttextID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[MaplisttextID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[MaplisttextID], id, 2).valueU16;
}

void initMapliste_balloondisp_r(const CBdatWrapper &wrapper) { s_members[Mapliste_balloondisp_r] = Bdat::getMember(wrapper.data, "e_balloondisp_r"); }

u32 getMapliste_balloondisp_r(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Mapliste_balloondisp_r] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Mapliste_balloondisp_r], id, 1).valueU8;
}

void initMaplistzone(const CBdatWrapper &wrapper) { s_members[Maplistzone] = Bdat::getMember(wrapper.data, "zone"); }

u32 getMaplistzone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Maplistzone] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Maplistzone], id, 1).valueU8;
}

void initWeatherInfomsg(const CBdatWrapper &wrapper) { s_members[WeatherInfomsg] = Bdat::getMember(wrapper.data, "msg"); }

u32 getWeatherInfomsg(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[WeatherInfomsg] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[WeatherInfomsg], id, 2).valueU16;
}

void initWeatherInfoeff(const CBdatWrapper &wrapper) { s_members[WeatherInfoeff] = Bdat::getMember(wrapper.data, "eff"); }

const char *getWeatherInfoeff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[WeatherInfoeff] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[WeatherInfoeff], id, 7).valueString;
}

void initWeatherInfosnd(const CBdatWrapper &wrapper) { s_members[WeatherInfosnd] = Bdat::getMember(wrapper.data, "snd"); }

const char *getWeatherInfosnd(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[WeatherInfosnd] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[WeatherInfosnd], id, 7).valueString;
}

void initWeatherInfosndBegin(const CBdatWrapper &wrapper) { s_members[WeatherInfosndBegin] = Bdat::getMember(wrapper.data, "sndBegin"); }

const char *getWeatherInfosndBegin(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[WeatherInfosndBegin] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[WeatherInfosndBegin], id, 7).valueString;
}

void initTimeInfomsg(const CBdatWrapper &wrapper) { s_members[TimeInfomsg] = Bdat::getMember(wrapper.data, "msg"); }

u32 getTimeInfomsg(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TimeInfomsg] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TimeInfomsg], id, 2).valueU16;
}

} // namespace _gfbml

u32 GfBdatMaplist::getMaplistStart() const { return Bdat::getIdTop(mMaplist->data); }

const char *GfBdatMaplist::getMaplistresource(u32 id) const { return _gfbml::getMaplistresource(*mMaplist, id); }

const char *GfBdatMaplist::getMaplistselect(u32 id) const { return _gfbml::getMaplistselect(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistrscGmkId(u32 id) const { return _gfbml::getMaplistrscGmkId(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistene_disp_r(u32 id) const { return _gfbml::getMaplistene_disp_r(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistene_disp_h(u32 id) const { return _gfbml::getMaplistene_disp_h(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistene_release_r(u32 id) const { return _gfbml::getMaplistene_release_r(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistene_release_h(u32 id) const { return _gfbml::getMaplistene_release_h(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwa_type(u32 id) const { return _gfbml::getMaplistwa_type(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwa_pop_rate(u32 id) const { return _gfbml::getMaplistwa_pop_rate(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwa_time_BNS(u32 id) const { return _gfbml::getMaplistwa_time_BNS(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwa_end_time(u32 id) const { return _gfbml::getMaplistwa_end_time(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwb_type(u32 id) const { return _gfbml::getMaplistwb_type(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwb_pop_rate(u32 id) const { return _gfbml::getMaplistwb_pop_rate(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwb_time_BNS(u32 id) const { return _gfbml::getMaplistwb_time_BNS(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwb_end_time(u32 id) const { return _gfbml::getMaplistwb_end_time(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwc_type(u32 id) const { return _gfbml::getMaplistwc_type(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwc_pop_rate(u32 id) const { return _gfbml::getMaplistwc_pop_rate(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwc_time_BNS(u32 id) const { return _gfbml::getMaplistwc_time_BNS(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwc_end_time(u32 id) const { return _gfbml::getMaplistwc_end_time(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwd_type(u32 id) const { return _gfbml::getMaplistwd_type(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwd_pop_rate(u32 id) const { return _gfbml::getMaplistwd_pop_rate(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwd_time_BNS(u32 id) const { return _gfbml::getMaplistwd_time_BNS(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwd_end_time(u32 id) const { return _gfbml::getMaplistwd_end_time(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwind_mor(u32 id) const { return _gfbml::getMaplistwind_mor(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwind_non(u32 id) const { return _gfbml::getMaplistwind_non(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwind_eve(u32 id) const { return _gfbml::getMaplistwind_eve(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwind_nit(u32 id) const { return _gfbml::getMaplistwind_nit(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwind_mnit(u32 id) const { return _gfbml::getMaplistwind_mnit(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwind_emor(u32 id) const { return _gfbml::getMaplistwind_emor(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwind_WA(u32 id) const { return _gfbml::getMaplistwind_WA(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwind_WB(u32 id) const { return _gfbml::getMaplistwind_WB(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwind_WC(u32 id) const { return _gfbml::getMaplistwind_WC(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwind_WD(u32 id) const { return _gfbml::getMaplistwind_WD(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistweatherATR(u32 id) const { return _gfbml::getMaplistweatherATR(*mMaplist, id); }

u32 GfBdatMaplist::getMapliste_repoptime(u32 id) const { return _gfbml::getMapliste_repoptime(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistm_repoptime(u32 id) const { return _gfbml::getMaplistm_repoptime(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistmapATR(u32 id) const { return _gfbml::getMaplistmapATR(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwa_ON_cndID(u32 id) const { return _gfbml::getMaplistwa_ON_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwa_OFF_cndID(u32 id) const { return _gfbml::getMaplistwa_OFF_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwb_ON_cndID(u32 id) const { return _gfbml::getMaplistwb_ON_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwb_OFF_cndID(u32 id) const { return _gfbml::getMaplistwb_OFF_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwc_ON_cndID(u32 id) const { return _gfbml::getMaplistwc_ON_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwc_OFF_cndID(u32 id) const { return _gfbml::getMaplistwc_OFF_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwd_ON_cndID(u32 id) const { return _gfbml::getMaplistwd_ON_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistwd_OFF_cndID(u32 id) const { return _gfbml::getMaplistwd_OFF_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMapliststopTIME_cndID(u32 id) const { return _gfbml::getMapliststopTIME_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistebb_ON_cndID(u32 id) const { return _gfbml::getMaplistebb_ON_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistebb_inn_cndID(u32 id) const { return _gfbml::getMaplistebb_inn_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistebb_pop_rate(u32 id) const { return _gfbml::getMaplistebb_pop_rate(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistst_allOFF_cndID(u32 id) const { return _gfbml::getMaplistst_allOFF_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistst_OFF_cndID(u32 id) const { return _gfbml::getMaplistst_OFF_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistbgm_cndID(u32 id) const { return _gfbml::getMaplistbgm_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistname_cndID(u32 id) const { return _gfbml::getMaplistname_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistnameID(u32 id) const { return _gfbml::getMaplistnameID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistchange_nameID(u32 id) const { return _gfbml::getMaplistchange_nameID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistmapON_cndID(u32 id) const { return _gfbml::getMaplistmapON_cndID(*mMaplist, id); }

u32 GfBdatMaplist::getMaplisttextID(u32 id) const { return _gfbml::getMaplisttextID(*mMaplist, id); }

u32 GfBdatMaplist::getMapliste_balloondisp_r(u32 id) const { return _gfbml::getMapliste_balloondisp_r(*mMaplist, id); }

u32 GfBdatMaplist::getMaplistzone(u32 id) const { return _gfbml::getMaplistzone(*mMaplist, id); }

u32 GfBdatMaplist::getWeatherInfoStart() const { return Bdat::getIdTop(mWeatherInfo->data); }

u32 GfBdatMaplist::getWeatherInfomsg(u32 id) const { return _gfbml::getWeatherInfomsg(*mWeatherInfo, id); }

const char *GfBdatMaplist::getWeatherInfoeff(u32 id) const { return _gfbml::getWeatherInfoeff(*mWeatherInfo, id); }

const char *GfBdatMaplist::getWeatherInfosnd(u32 id) const { return _gfbml::getWeatherInfosnd(*mWeatherInfo, id); }

const char *GfBdatMaplist::getWeatherInfosndBegin(u32 id) const { return _gfbml::getWeatherInfosndBegin(*mWeatherInfo, id); }

u32 GfBdatMaplist::getTimeInfoStart() const { return Bdat::getIdTop(mTimeInfo->data); }

u32 GfBdatMaplist::getTimeInfomsg(u32 id) const { return _gfbml::getTimeInfomsg(*mTimeInfo, id); }

} // namespace gf
