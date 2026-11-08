#include "gf/menu/object/gf_menu_obj_lvup_main.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_sound_manager.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/sound/gf_sound.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjLvupMain::GfMenuObjLvupMain(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(0xff), unknown50(this), unknown2e0(false), unknown2e4(0), unknown2f0(nullptr),
      unknown2f8(nullptr), unknown300(false) {
  unknown2f0 = GfMenuCallContext::create();
  unknown2f8 = GfMenuCallContext::create();
}

GfMenuObjLvupMain::~GfMenuObjLvupMain() {
  mm::mtl::safeRelease(unknown2f0);
  mm::mtl::safeRelease(unknown2f8);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjLvupMain::finalize() { GfMenuObject::finalize(); }

void GfMenuObjLvupMain::update() {
  unknown50.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjLvupMain::seqClose2() {
  unknown304 = GfMenuObjUtil::playJingle(4);
  unknown50.unknown002(&GfMenuObjLvupMain::seqClose3);
  return true;
}

bool GfMenuObjLvupMain::seqClose3() {
  bool isEnd;
  if (GfSound::get() == nullptr || !GfSound::get()->isPlaying(unknown304)) {
    GfMenuSoundManager::fadeInFieldBgm(2.0f);
    GfMenuObjOperationInfo::close();
    isEnd = true;
    closeFSLayer(unknown18, true, true);
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjLvupMain::seqEndLevelUp() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  u32 index = unknown30->getIndex(true);
  mm::mtl::FixStr<32> name;
  name.format("IMG_lv_lvup_eff@%02d", index + 1);
  ui::UIObjectAcc effect(main.unknown10, name.c_str());
  bool isEnd;
  if (!effect.isPlayingAnimation()) {
    sendOpenEvent(main.searchChild("LAY_lv_driverset"), 0, 0.0f);
    refreshLevelUpInfo();
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjLvupMain::seqExecLevelUp() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  u32 index = unknown30->getIndex(true) + 1;
  mm::mtl::FixStr<32> name;
  name.format("IMG_lv_lvup_eff@%02d", index);
  ui::UIObjectAcc effect(main.unknown10, name.c_str());
  effect.startAnimation("fade_in", false);
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x10000000;
  param.unknown50 = "mnu061_levelup";
  param.unknown58 = "fade_in";
  param.unknown11 = true;
  param.unknown14 = 10;
  name.format("TXT_lv_lvup_text@%02d", index);
  ui::UIObjectAcc text(main.unknown10, name.c_str());
  GfMenuObjUtil::startCtrl(text.unknown10, param, nullptr);
  param.unknown08 = 0x10000000;
  param.unknown50 = "mnu061_levelup_shadow";
  param.unknown58 = "fade_in";
  param.unknown11 = true;
  param.unknown14 = 10;
  name.format("IMG_lv_lvup_text_bg@%02d", index);
  ui::UIObjectAcc background(main.unknown10, name.c_str());
  GfMenuObjUtil::startCtrl(background.unknown10, param, nullptr);
  GfMenuObjUtil::playJingle(5);
  return true;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjLvupMain, 8>>(const mm::mtl::Delegate<bool()> *);
