#include "gf/data/gf_bdat_bgm.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"

namespace gf {
namespace _gfbbg {

enum {
  BgmListfilename,
  BgmConditionConditionA,
  BgmConditionBgmIDA,
  BgmConditionConditionB,
  BgmConditionBgmIDB,
  BgmConditionConditionC,
  BgmConditionBgmIDC,
  BgmConditionConditionD,
  BgmConditionBgmIDD,
  BgmConditionPriority,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];

void initBgmListfilename(const CBdatWrapper &wrapper) { s_members[BgmListfilename] = Bdat::getMember(wrapper.data, "filename"); }

const char *getBgmListfilename(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmListfilename] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BgmListfilename], id, 7).valueString;
}

void initBgmConditionConditionA(const CBdatWrapper &wrapper) { s_members[BgmConditionConditionA] = Bdat::getMember(wrapper.data, "ConditionA"); }

u32 getBgmConditionConditionA(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionConditionA] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionConditionA], id, 2).valueU16;
}

void initBgmConditionBgmIDA(const CBdatWrapper &wrapper) { s_members[BgmConditionBgmIDA] = Bdat::getMember(wrapper.data, "BgmIDA"); }

u32 getBgmConditionBgmIDA(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionBgmIDA] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionBgmIDA], id, 2).valueU16;
}

void initBgmConditionConditionB(const CBdatWrapper &wrapper) { s_members[BgmConditionConditionB] = Bdat::getMember(wrapper.data, "ConditionB"); }

u32 getBgmConditionConditionB(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionConditionB] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionConditionB], id, 2).valueU16;
}

void initBgmConditionBgmIDB(const CBdatWrapper &wrapper) { s_members[BgmConditionBgmIDB] = Bdat::getMember(wrapper.data, "BgmIDB"); }

u32 getBgmConditionBgmIDB(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionBgmIDB] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionBgmIDB], id, 2).valueU16;
}

void initBgmConditionConditionC(const CBdatWrapper &wrapper) { s_members[BgmConditionConditionC] = Bdat::getMember(wrapper.data, "ConditionC"); }

u32 getBgmConditionConditionC(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionConditionC] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionConditionC], id, 2).valueU16;
}

void initBgmConditionBgmIDC(const CBdatWrapper &wrapper) { s_members[BgmConditionBgmIDC] = Bdat::getMember(wrapper.data, "BgmIDC"); }

u32 getBgmConditionBgmIDC(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionBgmIDC] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionBgmIDC], id, 2).valueU16;
}

void initBgmConditionConditionD(const CBdatWrapper &wrapper) { s_members[BgmConditionConditionD] = Bdat::getMember(wrapper.data, "ConditionD"); }

u32 getBgmConditionConditionD(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionConditionD] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionConditionD], id, 2).valueU16;
}

void initBgmConditionBgmIDD(const CBdatWrapper &wrapper) { s_members[BgmConditionBgmIDD] = Bdat::getMember(wrapper.data, "BgmIDD"); }

u32 getBgmConditionBgmIDD(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionBgmIDD] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionBgmIDD], id, 2).valueU16;
}

void initBgmConditionPriority(const CBdatWrapper &wrapper) { s_members[BgmConditionPriority] = Bdat::getMember(wrapper.data, "Priority"); }

u32 getBgmConditionPriority(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionPriority] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionPriority], id, 1).valueU8;
}

} // namespace _gfbbg

GfBdatBgm::GfBdatBgm() : mBgmList(nullptr), mBgmCondition(nullptr) { bdatRefresh(); }

GfBdatBgm::~GfBdatBgm() { destroyFP(); }

void GfBdatBgm::destroyFP() {
  if (mBgmList != nullptr) {
    delete mBgmList;
    mBgmList = nullptr;
  }

  if (mBgmCondition != nullptr) {
    delete mBgmCondition;
    mBgmCondition = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                       \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatBgm::createFP() {
  mBgmList = NEW_BDAT_WRAPPER(BDAT_RSC_BGM_LIST);
  mBgmCondition = NEW_BDAT_WRAPPER(BDAT_RSC_BGM_CONDITION);
}

void GfBdatBgm::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbbg::initBgmListfilename(*mBgmList);
  _gfbbg::initBgmConditionConditionA(*mBgmCondition);
  _gfbbg::initBgmConditionBgmIDA(*mBgmCondition);
  _gfbbg::initBgmConditionConditionB(*mBgmCondition);
  _gfbbg::initBgmConditionBgmIDB(*mBgmCondition);
  _gfbbg::initBgmConditionConditionC(*mBgmCondition);
  _gfbbg::initBgmConditionBgmIDC(*mBgmCondition);
  _gfbbg::initBgmConditionConditionD(*mBgmCondition);
  _gfbbg::initBgmConditionBgmIDD(*mBgmCondition);
  _gfbbg::initBgmConditionPriority(*mBgmCondition);
}

u32 GfBdatBgm::getBgmListStart() const { return Bdat::getIdTop(mBgmList->data); }

u32 GfBdatBgm::getBgmListEnd() const { return Bdat::getIdTop(mBgmList->data) + Bdat::getIdCount(mBgmList->data); }

const char *GfBdatBgm::getBgmListfilename(u32 id) const { return _gfbbg::getBgmListfilename(*mBgmList, id); }

u32 GfBdatBgm::getBgmConditionStart() const { return Bdat::getIdTop(mBgmCondition->data); }

u32 GfBdatBgm::getBgmConditionEnd() const { return Bdat::getIdTop(mBgmCondition->data) + Bdat::getIdCount(mBgmCondition->data); }

u32 GfBdatBgm::getBgmConditionConditionA(u32 id) const { return _gfbbg::getBgmConditionConditionA(*mBgmCondition, id); }

u32 GfBdatBgm::getBgmConditionBgmIDA(u32 id) const { return _gfbbg::getBgmConditionBgmIDA(*mBgmCondition, id); }

u32 GfBdatBgm::getBgmConditionConditionB(u32 id) const { return _gfbbg::getBgmConditionConditionB(*mBgmCondition, id); }

u32 GfBdatBgm::getBgmConditionBgmIDB(u32 id) const { return _gfbbg::getBgmConditionBgmIDB(*mBgmCondition, id); }

u32 GfBdatBgm::getBgmConditionConditionC(u32 id) const { return _gfbbg::getBgmConditionConditionC(*mBgmCondition, id); }

u32 GfBdatBgm::getBgmConditionBgmIDC(u32 id) const { return _gfbbg::getBgmConditionBgmIDC(*mBgmCondition, id); }

u32 GfBdatBgm::getBgmConditionConditionD(u32 id) const { return _gfbbg::getBgmConditionConditionD(*mBgmCondition, id); }

u32 GfBdatBgm::getBgmConditionBgmIDD(u32 id) const { return _gfbbg::getBgmConditionBgmIDD(*mBgmCondition, id); }

u32 GfBdatBgm::getBgmConditionPriority(u32 id) const { return _gfbbg::getBgmConditionPriority(*mBgmCondition, id); }

u32 GfBdatBgm::getBgmConditionCondition(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbbg::getBgmConditionConditionA, _gfbbg::getBgmConditionConditionB, _gfbbg::getBgmConditionConditionC, _gfbbg::getBgmConditionConditionD};
  return getters[index](*mBgmCondition, id);
}

u32 GfBdatBgm::getBgmConditionBgmID(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbbg::getBgmConditionBgmIDA, _gfbbg::getBgmConditionBgmIDB, _gfbbg::getBgmConditionBgmIDC, _gfbbg::getBgmConditionBgmIDD};
  return getters[index](*mBgmCondition, id);
}

} // namespace gf
