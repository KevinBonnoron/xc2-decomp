#include "gf/menu/object/gf_menu_obj_blade_kizuna_ring.h"

#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_object.h"
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

void GfMenuObjBladeKizunaRing::open() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_33); }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBladeKizunaRing>(const mm::mtl::Delegate<bool()> *);
