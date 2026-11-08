#include "gf/menu/object/gf_menu_obj_option.h"

#include <string.h>

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x86;

GfMenuObjOption::GfMenuObjOption(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(0), unknown4c(0), unknown120(nullptr), unknown128(this), unknown3b8(false),
      unknown3bc(-1), unknown3c0(0), unknown3c2(0xff) {
  unknown120 = GfMenuCallContext::create();
}

GfMenuObjOption::~GfMenuObjOption() {
  mm::mtl::safeRelease(unknown120);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjOption::finalize() { GfMenuObject::finalize(); }

void GfMenuObjOption::update() {
  unknown128.unknown003();
  GfMenuObject::update();
}

int GfMenuObjOption::getVolumeValue(u8 level, u8 levelMax) {
  f32 volume = (1.0f / levelMax) * level;
  if (volume > 1.0f) {
    volume = 1.0f;
  }
  return static_cast<int>(volume * 255.0f);
}

u32 GfMenuObjOption::getGammaValue(u8 level, u8 levelMax) {
  u32 value = 0xff;
  if (level != levelMax) {
    u32 scaled = static_cast<int>((static_cast<f32>(level) / levelMax) * 256.0f);
    if (scaled < 0x100) {
      value = scaled;
    }
  }
  return value;
}

u8 GfMenuObjOption::getVolumeLevel(u8 value, u8 levelMax) {
  u8 level = levelMax;
  if (value != 0xff) {
    f32 step = 255.0f / levelMax;
    f32 volume = value / step;
    level = static_cast<int>(volume + (volume > 0.0f ? 0.5f : -0.5f));
  }
  return level;
}

u8 GfMenuObjOption::getGammaLevel(u16 value, u8 levelMax) {
  u8 level = levelMax;
  if (value != 0xff) {
    f32 ratio = value / 255.0f;
    f32 gamma = levelMax * ratio;
    level = static_cast<int>(gamma + (gamma > 0.0f ? 0.5f : -0.5f));
  }
  return level;
}

bool GfMenuObjOption::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

bool GfMenuObjOption::seqSave() {
  ui::UIObjectAcc acc(unknown18, "LAY_submenu");
  GfMenuObject::disableInput(acc.unknown10);
  GfMenuObjMainMenu2::setCloseKeyEnable(false);
  unknown3bc = GfReqCommand::reqSaveOption();
  GfMenuObjFade::dispSaving(true, 0);
  return true;
}

bool GfMenuObjOption::seqSaveWait() {
  if (!GfReqManager::isValid(unknown3bc)) {
    GfMenuObjFade::dispSaving(false, 0);
    unknown3bc = -1;
    ui::UIObjectAcc main(unknown18, "LAY_main");
    GfMenuObject::termCallContext(main.unknown10);
    main.setTerm();
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
    ui::UIObjectAcc submenu(unknown18, "LAY_submenu");
    GfMenuObject::enableInput(submenu.unknown10);
    return true;
  }
  return false;
}

void GfMenuObjOption::updateInfo(u32 index) {
  ui::UIObjectAcc acc(unknown48);
  if (acc.isValid()) {
    u8 *menuMs = GfDataBdat::getFP(BDAT_MENU_OPTION_CAP_MS);
    u32 id = Bdat::getVal(unknown40, "cap_id", index + 1).valueU16;
    acc.setText(ui::UIStr(menuMs, id));
  }
}

void GfMenuObjOption::dispItemBase(u32 type, u32 index, bool isDisp) {
  mm::mtl::FixStr<32> name;
  if (type == 0) {
    name.format("IMG_cam_item_base@%02d", index + 1);
  } else if (type == 1) {
    name.format("IMG_snd_item_base@%02d", index + 1);
  } else if (type == 2) {
    name.format("IMG_dis_item_base@%02d", index + 1);
  }
  ui::UIObjectAcc acc(unknown18, name.c_str());
  acc.setAlpha(isDisp ? 1.0f : 0.0f);
}

void GfMenuObjOption::initOptionData(SDataOption &option) {
  mm::mtl::FixedVector<Level, 32> levels;
  option._0a = 0;
  option._08 = 0;
  option._09 = 0;
  option._04 = 0;
  option._0b = true;
  memset(option._0c, 0, sizeof(option._0c));
  option.unknown4c.clear();
  getDefaultLevel(0, levels);
  convLevelListToOptionData(0, levels, option);
  getDefaultLevel(1, levels);
  convLevelListToOptionData(1, levels, option);
  getDefaultLevel(2, levels);
  u8 *disp = GfDataBdat::getFP(BDAT_MNU_OPTION_DISP);
  u32 index = 1 - Bdat::getIdTop(disp);
  option.unknown4c._1a = getGammaValue(levels[index].unknown00, levels[index].unknown01);
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjOption>(const mm::mtl::Delegate<bool()> *);
