#include "gf/menu/object/gf_menu_obj_bl_kizuna_ring.h"

#include "gf/game/gf_game_voice.h"
#include "gf/menu/adapter/gf_menu_achievement_adapter.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x6a;

// Inferred role: menu id; original name unknown.
constexpr u32 unknown002 = 0x22;

GfMenuObjBlKizunaRing::GfMenuObjBlKizunaRing(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(0), unknown3c(0), unknown40(-1), unknown48(nullptr), unknown50(0), unknown58(nullptr), unknown198(0), unknown1a0(this),
      unknown430(0), unknown434(0), unknown438(0), unknown43c(0), unknown440(nullptr), unknown448(nullptr), unknown450(0), unknown454(0), unknown458(nullptr), unknown460(0),
      unknown468(reinterpret_cast<GF_SCOM_HANDLE *>(-1)) {
  unknown58 = GfMenuCallContext::create();
}

GfMenuObjBlKizunaRing::~GfMenuObjBlKizunaRing() {
  mm::mtl::safeRelease(unknown58);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown440);
  mm::mtl::safeRelease(unknown448);
}

void GfMenuObjBlKizunaRing::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  OpenParam &data = layerParam.get<OpenParam>();
  data.unknown00 = param.unknown00;
  data.unknown04 = param.unknown04;
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown002), layerParam);
}

void GfMenuObjBlKizunaRing::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlKizunaRing::update() {
  unknown1a0.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBlKizunaRing::openForMercenary(u32 handle, u32 blade, u16 group) {
  OpenParam param;
  param.unknown00 = 1;
  param.unknown04 = blade;
  registOpenParam(param);
  changeFSSubLayer(handle, group, getMenuLayerID(unknown002), true);
}

bool GfMenuObjBlKizunaRing::isLockPos(int index) { return index % 10 == 0; }

bool GfMenuObjBlKizunaRing::isScreenLR(u32 screen) { return screen < 4; }

void GfMenuObjBlKizunaRing::setupMain(ui::UIObjectAcc &acc) {
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_face@01"), 3, 0, false);
  u32 background = acc.searchChild("IMG_bl_name_bg");
  u32 name = acc.searchChild("TXT_bl_name");
  GfMenuCharDataAdapter::createFromReferenceBlade(name, 2, 0, false);
  GfMenuObjUtil::FitOption option;
  GfMenuObjUtil::createFitPlugin(background, name, 42, 16, option);
}

void GfMenuObjBlKizunaRing::setupCircle(ui::UIObjectAcc &) {}

void GfMenuObjBlKizunaRing::setupBladeSkillInfo(ui::UIObjectAcc &acc) {
  GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild("TXT_stocknum"), 16, 0, 0, 0, true);
  GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild("TXT_stockmax"), 17, 0, 0, 0, false);
}

void GfMenuObjBlKizunaRing::setupSkillSimple(ui::UIObjectAcc &acc) {
  GfMenuAdapterManager::beginAddAfter();
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_skillname"), 2, 0, 0, 1, false);
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("IMG_skillicon"), 11, 0, 0, 1, false);
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("IMG_skachicon"), 12, 0, 0, 1, false);
  GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjBlKizunaRing::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjBlKizunaRing::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBlKizunaRing::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjBlKizunaRing::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

bool GfMenuObjBlKizunaRing::seqWait() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc base(acc.searchChild("LAY_kizunaring_base"));
  enableInput(base.unknown10);
  return true;
}

bool GfMenuObjBlKizunaRing::seqEnd() {
  ui::UIObjectAcc acc(unknown18);
  refreshRing(acc);
  ui::UIObjectAcc cursor(acc.searchChild("IMG_kizunacursor"));
  cursor.setDisp(true);
  cursor.startAnimation("loop", false);
  enableInput(acc.searchChild("LAY_kizunaring_base"));
  if (unknown438 == 0) {
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
  }
  unknown140(acc.searchChild("LAY_kizunaring"), GfMenuTypes::unknown003_33, 0, 0.0f);
  return true;
}

bool GfMenuObjBlKizunaRing::seqWaitVoice() {
  u32 result = GfGameVoice::getResult(unknown458);
  if (result == VOICE_RESULT_UNKNOWN_1 || result == VOICE_RESULT_PLAY) {
    return false;
  }
  ui::UIObjectAcc acc(unknown18);
  unknown140(acc.searchChild("LAY_main"), GfMenuTypes::unknown003_33, 0, 0.0f);
  return true;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjBlKizunaRing, 8>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBlKizunaRing>(const mm::mtl::Delegate<bool()> *);
