#include "gf/game/auto_talk/gf_auto_talk.h"

#include "bdat.h"
#include "framework/memory/framework_memory.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/field/gf_field_gimmick.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/object/gf_menu_obj_balloon.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_mob/gmk_mob.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/rtti.h"

namespace gf {
struct GF_OBJ_HANDLE;

// Cause of the u16 tests here and in GfDataEvent::getMapjumpID, gmk::hasEyeBlink and GfMenuObjUtil::playBGM: Bdat::getValCheck returns 64 bits and the game tests a u16
// column with `and w8, w0, #0xffff; cbz w8` (0x71002fe854, 0x71002fe894), the compare of an i16 value. A zero test of the u16 (`if (unknown0a)`, `!next`) keeps that i16
// compare, while `!= 0` is promoted to int and gives `and x8, x0, #0xffff; cbz x8`. The loop (0x71002fe87c-0x71002fe8a8, 91 instructions in all) keeps its branches (cbz, add,
// cmp, mov, b.gt) only with `next` declared before the do-while (inside, clang if-converts the body into tst/csel/cinc) and the bound written `count > i` (`i < count`
// swaps the operands of the cmp).
void GfAutoTalk::BdatInfo::create(const CBdatWrapper &bdat, int id) {
  dispose();
  unknown00 = bdat.getValCheck("MOBID", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown02 = bdat.getValCheck("Range", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown04 = bdat.getValCheck("Condition", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown06 = bdat.getValCheck("Text", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown08 = bdat.getValCheck("Ontime", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown0a = bdat.getValCheck("BeforeID", id, gmk::BDAT_TYPE_UNKNOWN_2);
  if (unknown0a) {
    int count = Bdat::getIdCount(bdat.unknown00);
    int i = 0;
    u16 before = unknown0a;
    u16 next;
    do {
      next = bdat.getValCheck("BeforeID", before, gmk::BDAT_TYPE_UNKNOWN_2);
      if (!next) {
        break;
      }
      before = next;
      i++;
    } while (count > i);
    unknown02 = bdat.getValCheck("Range", before, gmk::BDAT_TYPE_UNKNOWN_2);
    unknown04 = bdat.getValCheck("Condition", before, gmk::BDAT_TYPE_UNKNOWN_2);
  }
}

void GfAutoTalk::BdatInfo::dispose() { unknown00 = 0; }

GfAutoTalk::GfAutoTalk(const CreateInfo *info) : m_distHvCond(), m_menuCallContext(nullptr), unknown80(false), unknown84(0.0f) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfAutoTalk::create(const CreateInfo &info) {
  dispose();
  m_createInfo = info;
  m_bdatInfo.create(info.unknown00, info.unknown10);
  if (m_bdatInfo.unknown001()) {
    m_distHvCond.set(m_bdatInfo.unknown02, m_bdatInfo.unknown02);
    gmk::GmkAcc::CreateInfoByBdatId accInfo;
    accInfo.unknown00 = gmk::GMK_TYPE_MOB;
    accInfo.unknown04 = m_bdatInfo.unknown00;
    m_gmkAcc.create(accInfo);
  } else {
    dispose();
  }
}

bool GfAutoTalk::isValid() const {
  if (m_createInfo.unknown00 != nullptr && m_createInfo.unknown08 != nullptr && m_createInfo.unknown10 > 0) {
    return m_gmkAcc.isValid();
  }
  return false;
}

bool GfAutoTalk::isDispEnd() const {
  if (unknown80) {
    if (unknown84 > 0.0f) {
      return false;
    }
    return true;
  }
  return false;
}

void GfAutoTalk::dispose() {
  disposeMenuObj();
  unknown84 = 0.0f;
  unknown80 = false;
  m_gmkAcc.dispose();
  m_bdatInfo.dispose();
  m_createInfo = CreateInfo();
}

void GfAutoTalk::disposeMenuObj() {
  if (m_menuCallContext != nullptr) {
    GfMenuObjBalloon::close(m_menuCallContext, true);
    mm::mtl::safeRelease(m_menuCallContext);
  }
}

void GfAutoTalk::update(f32 deltaTime) {
  if (!isValid()) {
    return;
  }
  updateMenuObj();
  if (unknown80 && unknown84 > 0.0f) {
    unknown84 -= deltaTime;
    if (unknown84 <= 0.0f) {
      disposeMenuObj();
    }
  }
  const gmk::GmkMob *mob = static_cast<const gmk::GmkMob *>(m_gmkAcc.m_aGmkBase);
  u32 num = mob->m_gmkMobInsts.unknowna8->size();
  if (num != 0) {
    bool canDisp = canDispText();
    if (unknown80 != canDisp) {
      unknown80 = canDisp;
      if (canDisp) {
        unknown84 = m_bdatInfo.unknown08;
        createMenuObj();
      } else {
        unknown84 = 0.0f;
        disposeMenuObj();
      }
    }
  }
}

void GfAutoTalk::updateMenuObj() {
  if (m_menuCallContext != nullptr && (m_menuCallContext->isTerm() || !GfGameManager::isAutoTalkOK())) {
    disposeMenuObj();
  }
}

bool GfAutoTalk::canDispText() const {
  if (!GfGameManager::isAutoTalkOK()) {
    return false;
  }
  if (m_bdatInfo.unknown04 != 0 && !GfGameCond::isGameCond(m_bdatInfo.unknown04)) {
    return false;
  }
  if (!m_gmkAcc.isValid()) {
    return false;
  }
  if (m_bdatInfo.unknown0a != 0) {
    const GfAutoTalk *before = GfAutoTalkManager::get()->findGfAutoTalkByBdatId(m_createInfo.unknown00, m_bdatInfo.unknown0a);
    if (before != nullptr && !before->isDispEnd()) {
      return false;
    }
  }
  if (!m_distHvCond.isMatch(m_gmkAcc.m_aGmkBase->m_createBaseInfo.m_xform->unknown00)) {
    return false;
  }
  const mm::mtl::Vector<GF_OBJ_HANDLE *> &handles = *static_cast<const gmk::GmkMob *>(m_gmkAcc.m_aGmkBase)->m_gmkMobInsts.unknowna8;
  u32 num = handles.size();
  if (num == 0) {
    return false;
  }
  GfObjAcc acc(handles[0]);
  if (!acc.isValid()) {
    return false;
  }
  if (!acc.isDisp(static_cast<OBJDISP>(0))) {
    return false;
  }
  if (acc.isMultiBindWaiting()) {
    return false;
  }
  return acc.getObj() != nullptr;
}

void GfAutoTalk::createMenuObj() {
  disposeMenuObj();
  m_menuCallContext = GfMenuCallContext::create();
  GfMenuObjBalloon::OpenParam param;
  param.unknown00 = m_createInfo.unknown08;
  param.unknown08 = m_bdatInfo.unknown06;
  const gmk::GmkMob *mob = static_cast<const gmk::GmkMob *>(m_gmkAcc.m_aGmkBase);
  param.m_GF_OBJ_HANDLE = (*mob->m_gmkMobInsts.unknowna8)[0];
  int mobId = mm::mtl::dynamicCast<GfObjSetupMob>(GfObjManager::getObjInfo(param.m_GF_OBJ_HANDLE)->unknown30)->unknown10;
  if (mobId > 0) {
    GfMenuBdat::getMenuOffset(static_cast<u16>(Bdat::getValCheck(GfDataBdat::getFP(BDAT_RSC_MOB_LIST), "OffsetID", mobId, gmk::BDAT_TYPE_UNKNOWN_2)), param.m_menuOffset);
  } else {
    param.m_menuOffset.unknown10 = nullptr;
    param.m_menuOffset.unknown00 = mm::Vec3::zero;
  }
  GfMenuObjBalloon::openAutoTalk(m_menuCallContext, param);
}

const GfAutoTalk *GfAutoTalkManager::findGfAutoTalkByBdatId(u8 *bdat, int id) const {
  for (mm::mtl::IntrusiveList<GfAutoTalkList>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    const GfAutoTalkList *list = it.get();
    if (list->m_createInfo.unknown08 == bdat) {
      u32 index = id - Bdat::getIdTop(bdat);
      return &list->unknown30[index];
    }
  }
  return nullptr;
}

GfAutoTalkList::GfAutoTalkList(const CreateInfo *info) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfAutoTalkList::create(const CreateInfo &info) {
  dispose();
  m_createInfo = info;
  u8 *bdat = info.unknown08;
  int count = Bdat::getIdCount(bdat);
  unknown30.setAllocator(fw::FrameworkMemory::getAllocator(5));
  unknown30.reserve(count);
  unknown30.resize(count);
  int top = Bdat::getIdTop(bdat);
  for (int i = 0; i < count; i++) {
    GfAutoTalk::CreateInfo talkInfo;
    talkInfo.unknown00 = info.unknown08;
    talkInfo.unknown08 = info.unknown10;
    talkInfo.unknown10 = top + i;
    unknown30[i].create(talkInfo);
  }
}

void GfAutoTalkList::dispose() {
  size_t num = unknown30.size();
  for (size_t i = 0; i < num; i++) {
    unknown30[i].dispose();
  }
  unknown30.clear();
  m_createInfo = CreateInfo();
}

void GfAutoTalkList::update(f32 deltaTime) {
  if (m_createInfo.unknown00 > 0 && m_createInfo.unknown08 != nullptr && m_createInfo.unknown10 != nullptr) {
    size_t num = unknown30.size();
    for (size_t i = 0; i < num; i++) {
      unknown30[i].update(deltaTime);
    }
  }
}

GfAutoTalkManager::GfAutoTalkManager(const GfSetupParam &) : unknown28(nullptr) { GfEvent::addEventCallback(this); }

void GfAutoTalkManager::build(const GfSetupParam &param) {
  // __LINE__ must be 470 as in the original file: it is the line argument of operator new.
#line 470
  GfAutoTalkManager *manager = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfAutoTalkManager(param);
  manager->create();
}

void GfAutoTalkManager::create() {
  clearAutoTalkLists();
  unknown28 = &GfAutoTalkManager::seqInit;
}

void GfAutoTalkManager::destroy() { delete get(); }

bool GfAutoTalkManager::isInitialized() { return get() != nullptr; }

void GfAutoTalkManager::update(const fw::UpdateInfo &info) {
  GfAutoTalkManager *manager = get();
  if (manager != nullptr) {
    manager->update(info.unknown04);
  }
}

void GfAutoTalkManager::update(f32 deltaTime) {
  if (nullptr != unknown28) {
    (this->*unknown28)(deltaTime);
  }
}

void GfAutoTalkManager::dispose() {
  clearAutoTalkLists();
  unknown28 = nullptr;
}

void GfAutoTalkManager::seqInit(f32) {
  if (!GfFieldGimmick::isGmkSetReady()) {
    return;
  }
  const mm::mtl::Vector<gmk::GmkSet *> &sets = gmk::GmkManager::get()->unknownf358;
  size_t num = sets.size();
  for (size_t i = 0; i < num; i++) {
    createAutoTalkList(sets[i]->m_createInfo.unknown04);
  }
  unknown28 = &GfAutoTalkManager::seqUpdate;
}

void GfAutoTalkManager::clearAutoTalkLists() {
  while (!unknown10.empty()) {
    GfAutoTalkList *list = unknown10.begin().get();
    unknown10.erase(list);
    delete list;
  }
}

bool GfAutoTalkManager::createAutoTalkList(int gmkSet) {
  disposeAutoTalkList(gmkSet);
  GfAutoTalkList::CreateInfo info;
  info.unknown00 = gmkSet;
  u8 *bdat = gmk::GmkManager::get()->unknown190;
  const char *name = reinterpret_cast<const char *>(Bdat::getValCheck(bdat, "autoTalk", gmkSet, gmk::BDAT_TYPE_UNKNOWN_7));
  if (name == nullptr || *name == '\0') {
    return false;
  }
  info.unknown08 = Bdat::getFP(name);
  if (info.unknown08 == nullptr) {
    return false;
  }
  name = reinterpret_cast<const char *>(Bdat::getValCheck(bdat, "autoTalk_ms", gmkSet, gmk::BDAT_TYPE_UNKNOWN_7));
  if (name == nullptr || *name == '\0') {
    return false;
  }
  info.unknown10 = Bdat::getFP(name);
  if (info.unknown10 == nullptr) {
    return false;
  }
  if (info.unknown00 > 0 && info.unknown08 != nullptr && info.unknown10 != nullptr) {
    // __LINE__ must be 584 as in the original file: it is the line argument of operator new.
#line 584
    unknown10.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfAutoTalkList(&info));
    return true;
  }
  return false;
}

void GfAutoTalkManager::disposeAutoTalkList(int gmkSet) {
  for (mm::mtl::IntrusiveList<GfAutoTalkList>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    GfAutoTalkList *list = it.get();
    if (list->m_createInfo.unknown00 == gmkSet) {
      unknown10.erase(list);
      delete list;
      return;
    }
  }
}

void GfAutoTalkManager::seqUpdate(f32 deltaTime) {
  for (mm::mtl::IntrusiveList<GfAutoTalkList>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    it.get()->update(deltaTime);
  }
}

void GfAutoTalkManager::gevReloadBdat(RELOAD_BDAT reload, u32) {
  if (reload == RELOAD_BDAT_UNKNOWN_1) {
    create();
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfAutoTalkManager>::~PtrSingleton();
