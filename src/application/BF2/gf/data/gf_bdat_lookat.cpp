#include "gf/data/gf_bdat_lookat.h"

#include "gf/game/gf_game_party.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

GfBdatLookAt::Impl::Impl() : unknown468(0.0f), unknown46c(0.0f), unknown470(0.0f) {}

GfBdatLookAt::Impl::~Impl() {}

#line 80
GfBdatLookAt::GfBdatLookAt() {
  unknown28.reset(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) Impl());
  unknown28->build();
}

#line 90
void GfBdatLookAt::bdatRefresh() {
  unknown28.reset(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) Impl());
  unknown28->build();

  if (GfGameParty::get() != nullptr) {
    for (u32 hierarchy = 0; hierarchy < 6; hierarchy++) {
      GfObj *obj = GfObjUtil::getObj(GfGameParty::getHandleByHierarchy(hierarchy));
      if (obj != nullptr) {
        MsgDebugNotifyReloadLookAtBdat message;
        sendMessage(obj, message);
      }
    }
  }
}

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

const GfBdatLookAt::unknown001 *GfBdatLookAt::Impl::getLookInfo(u32 category, u32 charaCategory) const {
  const unknown001 *info = nullptr;
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

const GfBdatLookAt::unknown001 &GfBdatLookAt::getLookInfo(u32 category, u32 charaCategory, u32 target, u32 targetRefId) const {
  static const unknown001 defaultInfo;
  const unknown001 *result = &defaultInfo;
  if (target != 8) {
    const CharactorInfo &character = getCharactorInfo(category, charaCategory);
    const CharactorInfo &targetCharacter = getCharactorInfo(target, targetRefId);
    const unknown001 *info = nullptr;
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

template void mm::mtl::Vector<gf::GfBdatLookAt::CharactorInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gf::GfBdatLookAt::CharactorInfo>::resize(size_t);
