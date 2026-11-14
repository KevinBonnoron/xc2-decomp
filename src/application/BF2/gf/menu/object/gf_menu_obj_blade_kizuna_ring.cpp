#include "gf/menu/object/gf_menu_obj_blade_kizuna_ring.h"

#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_achievement_adapter.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5a;

GfMenuObjBladeKizunaRing::GfMenuObjBladeKizunaRing(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown3c(0), unknown3e(0), unknown40(false), unknown44(0), unknown48(-1), unknown4c(0), unknown50(1.0f), unknown190(this) {}

GfMenuObjBladeKizunaRing::~GfMenuObjBladeKizunaRing() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
}

void GfMenuObjBladeKizunaRing::initialize() {
  ui::UIObjectAcc acc(unknown18);
  ui::UISelectObjList::CreateParam param;
  param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown28 = ui::UISelectObjList::create(param);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 111 as in the original file: it is the line argument of operator new.
#line 111
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main);
  u32 ring = acc.searchChild("LAY_ring");
// __LINE__ must be 117 as in the original file: it is the line argument of operator new.
#line 117
  RingListener *ringListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) RingListener(this);
  ringListener->addRef();
  ui::UIEventManager::get()->registObjectListener(ring, ringListener);
  if (ringListener != nullptr) {
    ringListener->release();
  }
  attachExternalCall(unknown001, ring);
  u32 detail = acc.searchChild("LAY_detail");
// __LINE__ must be 122 as in the original file: it is the line argument of operator new.
#line 122
  DetailListener *detailListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DetailListener(this);
  detailListener->addRef();
  ui::UIEventManager::get()->registObjectListener(detail, detailListener);
  if (detailListener != nullptr) {
    detailListener->release();
  }
  attachExternalCall(unknown001, detail);
  GfMenuObject::initialize();
}

void GfMenuObjBladeKizunaRing::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeKizunaRing::update() {
  unknown190.unknown003();
  GfMenuObject::update();
}

int GfMenuObjBladeKizunaRing::getAchievementList(mm::mtl::FixedVector<Achievement, 50> &list) {
  u32 blade = GfMenuReference::getReferenceBladeID(0);
  list.clear();
  for (u32 i = 0; i < 5; i++) {
    u32 level = i + 1;
    for (u32 line = 0; line < 10; line++) {
      if (GfKizunaringBlade::getReleaseAchievement(blade, line, level) == 3) {
        if (line == 9) {
          for (u32 other = 0; other < 9; other++) {
            if (GfKizunaringBlade::getReleaseAchievement(blade, other, level) == 1) {
              list.push_back(Achievement(other, level, 1));
            }
          }
        }
        list.push_back(Achievement(line, level, 3));
      }
    }
  }
  return list.size();
}

bool GfMenuObjBladeKizunaRing::seqComplete() {
  ui::UIObjectAcc acc(unknown18);
  mm::mtl::FixStr<32> name;
  u32 blade = GfMenuReference::getReferenceBladeID(0);
  switch (unknown4c) {
  case 1:
    if (!unknown58.empty()) {
      name.format("IMG_ring_acv@%02d%02d", unknown58.back().unknown02, unknown58.back().unknown00 + 1);
      u32 icon = acc.searchChild(name.c_str());
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x40000000;
      param.unknown0c = 4;
      param.unknown00 = 0.4f;
      param.unknown38 = 1.0f;
      unknown48 = GfMenuObjUtil::startCtrl(icon, param, nullptr);
      unknown4c = 2;
      return false;
    } else {
      ui::UIObjectAcc root(unknown18);
      sendEvent(root.searchChild("LAY_ring"), GfMenuTypes::unknown003_33, 0);
      unknown4c = 0;
      return true;
    }
  case 2: {
    if (GfMenuObjUtil::isBusyCtrl(unknown48)) {
      return false;
    }
    Achievement achievement = unknown58.back();
    unknown58.pop_back();
    if (achievement.unknown04 == 3) {
      GfKizunaringBlade::releaseAchievement(blade, achievement.unknown00, achievement.unknown02);
    } else {
      GfKizunaringBlade::orderAchievement(blade, achievement.unknown00, achievement.unknown02);
    }
    unknown4c = 1;
    return false;
  }
  default:
    return true;
  }
}

void GfMenuObjBladeKizunaRing::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjBladeKizunaRing::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBladeKizunaRing::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjBladeKizunaRing::close() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjBladeKizunaRing::setupName(ui::UIObjectAcc &acc) { GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_name"), 2, 0, false); }

void GfMenuObjBladeKizunaRing::setupDetail(ui::UIObjectAcc &acc) {
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_detail_title"), 2, 0, 0, 1, true);
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_detail_task"), 3, 0, 0, 1, true);
}

void GfMenuObjBladeKizunaRing::setupRing(ui::UIObjectAcc &acc, ui::UISelectObjList *list) {
  mm::mtl::FixStr<32> name;
  list->clear();
  for (int level = 1; level <= 5; level++) {
    for (int line = 0; line < 10; line++) {
      name.format("IMG_ring_acv@%02d%02d", level, line + 1);
      u32 icon = acc.searchChild(name.c_str());
      GfMenuAchievementAdapter::createFromReferenceBlade(icon, 0, 0, line, level, true);
      list->addObject(icon);
    }
  }
  ui::UIObjectAcc face(acc.unknown10, "IMG_ring_face");
  GfMenuCharDataAdapter::createFromReferenceBlade(face.unknown10, 3, 0, false);
  face.availableInputTarget(false);
  list->addObject(face.unknown10);
}

void GfMenuObjBladeKizunaRing::open() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjBladeKizunaRing::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuReference::setReferenceBladeID(0, 0x3e9);
    GfMenuReference::setReferenceNumber(0, 0);
    GfMenuReference::setReferenceNumber(1, 1);
    setupName(acc);
    acc.setDisp(false);
    unknown163(handle, GfMenuTypes::unknown003_33, 0);
    break;
  case 2:
    GfMenuObjOperationInfo::close();
    acc.setDisp(false);
    acc.setTerm();
    break;
  case 3:
    if (event.unknown08 == 1) {
      if (getAchievementList(unknown20->unknown58) == 0) {
        unknown163(acc.searchChild("LAY_ring"), GfMenuTypes::unknown003_33, 0);
      } else {
        unknown20->unknown4c = 1;
        unknown20->unknown190.unknown005();
        unknown20->unknown190.unknown002(&GfMenuObjBladeKizunaRing::seqComplete);
      }
    } else if (event.unknown08 == 2) {
      GfMenuObject::returnFSSubLayer(handle, 1);
    }
    break;
  case GfMenuTypes::unknown003_33:
    GfMenuObjOperationInfo::open(acc.searchChild("LAY_ring"), 0, 0, 0);
    setFadeIn(handle);
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObjOperationInfo::close();
    setFadeOut(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBladeKizunaRing>(const mm::mtl::Delegate<bool()> *);
