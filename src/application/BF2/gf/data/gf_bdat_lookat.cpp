#include "gf/data/gf_bdat_lookat.h"

namespace gf {

GfBdatLookAt::Impl::Impl() : unknown468(0.0f), unknown46c(0.0f), unknown470(0.0f) {}

GfBdatLookAt::Impl::~Impl() {}

const GfBdatLookAt::CharactorInfo *GfBdatLookAt::Impl::getCharactorInfo(u32 category, u32 refId) const {
  const CategoryTable &table = unknown000[category];
  if (table.unknown2c) {
    int index = refId - table.unknown28;
    if (index >= 0 && static_cast<size_t>(index) < table.unknown00.size()) {
      return &table.unknown00[index];
    }
  }
  return nullptr;
}

const GfBdatLookAt::LookInfo *GfBdatLookAt::Impl::getLookInfo(u32 category, u32 charaCategory) const {
  const LookInfo *info = nullptr;
  if (charaCategory < 5 && category < 3) {
    info = &unknown300[category][charaCategory];
  }
  return info;
}

const GfBdatLookAt::CharactorInfo &GfBdatLookAt::getCharactorInfo(u32 category, u32 refId) const {
  static const CharactorInfo defaultInfo;
  const CharactorInfo *info = nullptr;
  if (unknown28) {
    info = unknown28->getCharactorInfo(category, refId);
  }
  if (info != nullptr) {
    return *info;
  }
  return defaultInfo;
}

const GfBdatLookAt::LookInfo &GfBdatLookAt::getLookInfo(u32 category, u32 charaCategory, u32 target, u32 targetRefId) const {
  static const LookInfo defaultInfo;
  const LookInfo *result = &defaultInfo;
  if (target != 8) {
    const CharactorInfo &character = getCharactorInfo(category, charaCategory);
    const CharactorInfo &targetCharacter = getCharactorInfo(target, targetRefId);
    const LookInfo *info = nullptr;
    if (unknown28) {
      info = unknown28->getLookInfo(character.unknown00, targetCharacter.unknown02);
    }
    if (info != nullptr) {
      result = info;
    }
  }
  return *result;
}

f32 GfBdatLookAt::getMaxRadius() {
  if (unknown28) {
    return unknown28->unknown468;
  }
  return 50.0f;
}

f32 GfBdatLookAt::getMaxUpper() {
  if (unknown28) {
    return unknown28->unknown46c;
  }
  return 5.0f;
}

f32 GfBdatLookAt::getMaxLower() {
  if (unknown28) {
    return unknown28->unknown470;
  }
  return 5.0f;
}

u16 GfBdatLookAt::getCharaType(u32 category, u32 refId) {
  if (unknown28) {
    return getCharactorInfo(category, refId).unknown02;
  }
  return 0;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfBdatLookAt>::~PtrSingleton();
