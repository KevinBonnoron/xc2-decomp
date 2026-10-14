#include "gf/data/gf_data_blade_arts.h"
#include "bdat.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_msg.h"

namespace gf {

const char *GfDataBladeArts::getName(u32 arts) {
  u8 *bdat;
  u32 textId;
  if (getName(bdat, textId, arts)) {
    const char *name = Bdat::getMSText(bdat, textId);
    if (name != nullptr) {
      return name;
    }
  }

  return GfBdatBtl::get()->getArtsBlDebugName(arts);
}

bool GfDataBladeArts::getName(u8 *&bdat, u32 &textId, u32 arts) {
  textId = GfBdatBtl::get()->getArtsBlName(arts);
  bdat = GfBdatMsg::getFpBlArtsMs();
  return textId != 0;
}

u32 GfDataBladeArts::getIcon(u32 arts) {
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  if (arts >= bdatBattle->getArtsBlStart() && arts < bdatBattle->getArtsBlEnd()) {
    return bdatBattle->getArtsBlUI(arts);
  }

  return 0;
}

bool GfDataBladeArts::getCaption(u8 *&bdat, u32 &textId, u32 arts) {
  textId = GfBdatBtl::get()->getArtsBlCaption(arts);
  bdat = GfBdatMsg::getFpBlArtsMs();
  return textId != 0;
}

u32 GfDataBladeArts::getEnhance(u32 arts, u32 level) { return GfBdatBtl::get()->getArtsBlEnhance(arts, level - 1); }

bool GfDataBladeArts::getEnhanceCaption(u8 *&bdat, u32 &textId, u32 arts, u32 level) {
  u32 enhance = GfBdatBtl::get()->getArtsBlEnhance(arts, level - 1);
  if (enhance == 0) {
    return false;
  }

  textId = GfBdatBtl::get()->getBTL_EnhanceCaption(enhance);
  bdat = GfBdatMsg::getFpBtlEnhanceCap();
  return textId != 0;
}

bool GfDataBladeArts::getExName(u8 *&bdat, u32 &textId, u32 arts) {
  textId = GfBdatBtl::get()->getArtsBlSpName(arts);
  bdat = GfBdatMsg::getFpBlSpArtsMs();
  return textId != 0;
}

const char *GfDataBladeArts::getExName(u32 arts) {
  u8 *bdat;
  u32 textId;
  if (getExName(bdat, textId, arts)) {
    const char *name = Bdat::getMSText(bdat, textId);
    if (name != nullptr) {
      return name;
    }
  }

  return GfBdatBtl::get()->getArtsBlSpDebugName(arts);
}

bool GfDataBladeArts::getExCaption(u8 *&bdat, u32 &textId, u32 arts) {
  textId = GfBdatBtl::get()->getArtsBlSpCaption(arts);
  bdat = GfBdatMsg::getFpBlSpArtsMs();
  return textId != 0;
}

} // namespace gf
