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
  if (s_members[BgmListfilename] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BgmListfilename], id, 7).valueString;
}

void initBgmConditionConditionA(const CBdatWrapper &wrapper) { s_members[BgmConditionConditionA] = Bdat::getMember(wrapper.data, "ConditionA"); }

u32 getBgmConditionConditionA(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionConditionA] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionConditionA], id, 2).valueU16;
}

void initBgmConditionBgmIDA(const CBdatWrapper &wrapper) { s_members[BgmConditionBgmIDA] = Bdat::getMember(wrapper.data, "BgmIDA"); }

u32 getBgmConditionBgmIDA(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionBgmIDA] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionBgmIDA], id, 2).valueU16;
}

void initBgmConditionConditionB(const CBdatWrapper &wrapper) { s_members[BgmConditionConditionB] = Bdat::getMember(wrapper.data, "ConditionB"); }

u32 getBgmConditionConditionB(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionConditionB] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionConditionB], id, 2).valueU16;
}

void initBgmConditionBgmIDB(const CBdatWrapper &wrapper) { s_members[BgmConditionBgmIDB] = Bdat::getMember(wrapper.data, "BgmIDB"); }

u32 getBgmConditionBgmIDB(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionBgmIDB] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionBgmIDB], id, 2).valueU16;
}

void initBgmConditionConditionC(const CBdatWrapper &wrapper) { s_members[BgmConditionConditionC] = Bdat::getMember(wrapper.data, "ConditionC"); }

u32 getBgmConditionConditionC(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionConditionC] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionConditionC], id, 2).valueU16;
}

void initBgmConditionBgmIDC(const CBdatWrapper &wrapper) { s_members[BgmConditionBgmIDC] = Bdat::getMember(wrapper.data, "BgmIDC"); }

u32 getBgmConditionBgmIDC(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionBgmIDC] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionBgmIDC], id, 2).valueU16;
}

void initBgmConditionConditionD(const CBdatWrapper &wrapper) { s_members[BgmConditionConditionD] = Bdat::getMember(wrapper.data, "ConditionD"); }

u32 getBgmConditionConditionD(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionConditionD] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionConditionD], id, 2).valueU16;
}

void initBgmConditionBgmIDD(const CBdatWrapper &wrapper) { s_members[BgmConditionBgmIDD] = Bdat::getMember(wrapper.data, "BgmIDD"); }

u32 getBgmConditionBgmIDD(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionBgmIDD] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionBgmIDD], id, 2).valueU16;
}

void initBgmConditionPriority(const CBdatWrapper &wrapper) { s_members[BgmConditionPriority] = Bdat::getMember(wrapper.data, "Priority"); }

u32 getBgmConditionPriority(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BgmConditionPriority] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BgmConditionPriority], id, 1).valueU8;
}

} // namespace _gfbbg

GfBdatBgm::GfBdatBgm() : m_bgmList(nullptr), m_bgmCondition(nullptr) { bdatRefresh(); }

GfBdatBgm::~GfBdatBgm() { destroyFP(); }

void GfBdatBgm::destroyFP() {
  if (m_bgmList != nullptr) {
    delete m_bgmList;
    m_bgmList = nullptr;
  }

  if (m_bgmCondition != nullptr) {
    delete m_bgmCondition;
    m_bgmCondition = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                                                                         \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatBgm::createFP() {
  m_bgmList = NEW_BDAT_WRAPPER(BDAT_RSC_BGM_LIST);
  m_bgmCondition = NEW_BDAT_WRAPPER(BDAT_RSC_BGM_CONDITION);
}

void GfBdatBgm::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbbg::initBgmListfilename(*m_bgmList);
  _gfbbg::initBgmConditionConditionA(*m_bgmCondition);
  _gfbbg::initBgmConditionBgmIDA(*m_bgmCondition);
  _gfbbg::initBgmConditionConditionB(*m_bgmCondition);
  _gfbbg::initBgmConditionBgmIDB(*m_bgmCondition);
  _gfbbg::initBgmConditionConditionC(*m_bgmCondition);
  _gfbbg::initBgmConditionBgmIDC(*m_bgmCondition);
  _gfbbg::initBgmConditionConditionD(*m_bgmCondition);
  _gfbbg::initBgmConditionBgmIDD(*m_bgmCondition);
  _gfbbg::initBgmConditionPriority(*m_bgmCondition);
}

u32 GfBdatBgm::getBgmListStart() const { return Bdat::getIdTop(m_bgmList->data); }

u32 GfBdatBgm::getBgmListEnd() const { return Bdat::getIdTop(m_bgmList->data) + Bdat::getIdCount(m_bgmList->data); }

const char *GfBdatBgm::getBgmListfilename(u32 id) const { return _gfbbg::getBgmListfilename(*m_bgmList, id); }

u32 GfBdatBgm::getBgmConditionStart() const { return Bdat::getIdTop(m_bgmCondition->data); }

u32 GfBdatBgm::getBgmConditionEnd() const { return Bdat::getIdTop(m_bgmCondition->data) + Bdat::getIdCount(m_bgmCondition->data); }

u32 GfBdatBgm::getBgmConditionConditionA(u32 id) const { return _gfbbg::getBgmConditionConditionA(*m_bgmCondition, id); }

u32 GfBdatBgm::getBgmConditionBgmIDA(u32 id) const { return _gfbbg::getBgmConditionBgmIDA(*m_bgmCondition, id); }

u32 GfBdatBgm::getBgmConditionConditionB(u32 id) const { return _gfbbg::getBgmConditionConditionB(*m_bgmCondition, id); }

u32 GfBdatBgm::getBgmConditionBgmIDB(u32 id) const { return _gfbbg::getBgmConditionBgmIDB(*m_bgmCondition, id); }

u32 GfBdatBgm::getBgmConditionConditionC(u32 id) const { return _gfbbg::getBgmConditionConditionC(*m_bgmCondition, id); }

u32 GfBdatBgm::getBgmConditionBgmIDC(u32 id) const { return _gfbbg::getBgmConditionBgmIDC(*m_bgmCondition, id); }

u32 GfBdatBgm::getBgmConditionConditionD(u32 id) const { return _gfbbg::getBgmConditionConditionD(*m_bgmCondition, id); }

u32 GfBdatBgm::getBgmConditionBgmIDD(u32 id) const { return _gfbbg::getBgmConditionBgmIDD(*m_bgmCondition, id); }

u32 GfBdatBgm::getBgmConditionPriority(u32 id) const { return _gfbbg::getBgmConditionPriority(*m_bgmCondition, id); }

u32 GfBdatBgm::getBgmConditionCondition(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbbg::getBgmConditionConditionA, _gfbbg::getBgmConditionConditionB, _gfbbg::getBgmConditionConditionC, _gfbbg::getBgmConditionConditionD};
  return getters[index](*m_bgmCondition, id);
}

u32 GfBdatBgm::getBgmConditionBgmID(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbg::getBgmConditionBgmIDA, _gfbbg::getBgmConditionBgmIDB, _gfbbg::getBgmConditionBgmIDC, _gfbbg::getBgmConditionBgmIDD};
  return getters[index](*m_bgmCondition, id);
}

} // namespace gf
