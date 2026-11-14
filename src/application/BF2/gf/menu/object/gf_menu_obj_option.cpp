#include "gf/menu/object/gf_menu_obj_option.h"

#include <string.h>

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_util_save_data.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x86;

GfMenuObjOption::GfMenuObjOption(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(0), unknown4c(0), unknown120(nullptr), unknown128(this), unknown3b8(false),
      unknown3bc(-1), unknown3c0(false), unknown3c1(false), unknown3c2(-1) {
  unknown120 = GfMenuCallContext::create();
}

GfMenuObjOption::~GfMenuObjOption() {
  mm::mtl::safeRelease(unknown120);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjOption::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
// __LINE__ must be 96 as in the original file: it is the line argument of operator new.
#line 96
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main.unknown10);
  {
    ui::UIObjectAcc submenu(main.unknown10, "LAY_submenu");
    ui::UISelectObjList::CreateParam param;
    param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
    unknown28 = ui::UISelectObjList::create(param);
    unknown28->pickupObject(submenu.unknown10, "LAY_submenu_item@%02d", 1);
// __LINE__ must be 112 as in the original file: it is the line argument of operator new.
#line 112
    SubMenuListener *subMenuListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SubMenuListener(this);
    subMenuListener->addRef();
    ui::UIEventManager::get()->registObjectListener(submenu.unknown10, subMenuListener);
    if (subMenuListener != nullptr) {
      subMenuListener->release();
    }
    sendOpenEvent(submenu.unknown10, 0, 0.0f);
  }
  u8 *optionName = GfDataBdat::getFP(BDAT_MENU_OPTION_NAME_MS);
  mm::mtl::FixStr<32> name;
  {
    ui::UISelectObjList::CreateParam param;
    param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
    unknown30 = ui::UISelectObjList::create(param);
  }
  {
    ui::UIObjectAcc cam(main.unknown10, "LAY_cam");
    u32 camCount = cam.countChild("LAY_cam_item@%02d", 1);
    u8 *camOption = GfDataBdat::getFP(BDAT_MNU_OPTION_CAMERA);
    if (camOption != nullptr) {
      for (u32 i = 0; i < camCount; i++) {
        if (i < static_cast<u32>(Bdat::getIdCount(camOption))) {
          u32 nameId = Bdat::getVal(camOption, "name_id", i + 1).valueU16;
          if (nameId != 0) {
            name.format("TXT_cam_item_name@%02d", i + 1);
            ui::UIObjectAcc text(cam.unknown10, name.c_str());
            text.setText(ui::UIStr(optionName, nameId));
          }
        } else {
          name.format("LAY_cam_item@%02d", i + 1);
          cam.setDispChild(false, name.c_str());
        }
      }
    }
// __LINE__ must be 157 as in the original file: it is the line argument of operator new.
#line 157
    ItemListListener *camListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemListListener(this);
    camListListener->addRef();
    ui::UIEventManager::get()->registObjectListener(cam.unknown10, camListListener);
    if (camListListener != nullptr) {
      camListListener->release();
    }
// __LINE__ must be 158 as in the original file: it is the line argument of operator new.
#line 158
    ItemSettingListener *camSettingListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemSettingListener(this);
    camSettingListener->addRef();
    ui::UIEventManager::get()->registObjectListener(cam.searchSibiling("LAY_cam_setting"), camSettingListener);
    if (camSettingListener != nullptr) {
      camSettingListener->release();
    }
  }
  {
    ui::UIObjectAcc snd(main.unknown10, "LAY_snd");
    u32 sndCount = snd.countChild("LAY_snd_item@%02d", 1);
    u8 *sndOption = GfDataBdat::getFP(BDAT_MNU_OPTION_SOUND);
    if (sndOption != nullptr) {
      for (u32 i = 0; i < sndCount; i++) {
        u32 nameId = Bdat::getVal(sndOption, "name_id", i + 1).valueU16;
        if (nameId != 0) {
          name.format("TXT_snd_item_name@%02d", i + 1);
          ui::UIObjectAcc text(snd.unknown10, name.c_str());
          text.setText(ui::UIStr(optionName, nameId));
        }
      }
    }
// __LINE__ must be 186 as in the original file: it is the line argument of operator new.
#line 186
    ItemListListener *sndListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemListListener(this);
    sndListListener->addRef();
    ui::UIEventManager::get()->registObjectListener(snd.unknown10, sndListListener);
    if (sndListListener != nullptr) {
      sndListListener->release();
    }
// __LINE__ must be 187 as in the original file: it is the line argument of operator new.
#line 187
    ItemSettingListener *sndSettingListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemSettingListener(this);
    sndSettingListener->addRef();
    ui::UIEventManager::get()->registObjectListener(snd.searchSibiling("LAY_snd_setting"), sndSettingListener);
    if (sndSettingListener != nullptr) {
      sndSettingListener->release();
    }
  }
  {
    ui::UIObjectAcc dis(main.unknown10, "LAY_dis");
// __LINE__ must be 197 as in the original file: it is the line argument of operator new.
#line 197
    ItemListListener *disListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemListListener(this);
    disListListener->addRef();
    ui::UIEventManager::get()->registObjectListener(dis.unknown10, disListListener);
    if (disListListener != nullptr) {
      disListListener->release();
    }
// __LINE__ must be 198 as in the original file: it is the line argument of operator new.
#line 198
    ItemSettingListener *disSettingListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemSettingListener(this);
    disSettingListener->addRef();
    ui::UIEventManager::get()->registObjectListener(dis.searchSibiling("LAY_dis_setting"), disSettingListener);
    if (disSettingListener != nullptr) {
      disSettingListener->release();
    }
  }
  unknown98 = *GfGameUtilSaveData::getValidOptionData();
  unknown3c0 = GfManager::isExecModeAdvertize();
  if (!unknown3c0) {
    GfMenuObjMainMenu2::setSubIndexText(0x18);
    unknown3c1 = false;
  } else {
    GfMenuObjOperationInfo::open(0, 0, 0, 0);
    unknown3c1 = true;
  }
  GfMenuObject::initialize();
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
  option.unknown04[6] = 0;
  option.unknown04[4] = 0;
  option.unknown04[5] = 0;
  option.unknown04[0] = false;
  option.unknown04[1] = false;
  option.unknown04[2] = 0;
  option.unknown04[3] = 0;
  option.unknown04[7] = true;
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

void GfMenuObjOption::ItemSettingListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    GfMenuObject::enableInput(acc.unknown10);
    GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    break;
  case GfMenuTypes::unknown003_34:
    acc.setDisp(false);
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjOption::convLevelListToOptionData(u32 type, const mm::mtl::FixedVector<Level, 32> &levels, SDataOption &option) {
  if (type == 0) {
    u8 *camera = GfDataBdat::getFP(BDAT_MNU_OPTION_CAMERA);
    u32 top = Bdat::getIdTop(camera);
    option.unknown04[0] = levels[1 - top].unknown00 == 1;
    option.unknown04[1] = levels[2 - top].unknown00 == 1;
    u8 level = levels[3 - top].unknown00;
    option.unknown04[4] = level != 0 ? level - 1 : 0;
    level = levels[4 - top].unknown00;
    option.unknown04[3] = level != 0 ? level - 1 : 0;
    level = levels[5 - top].unknown00;
    option.unknown04[5] = level != 0 ? level - 1 : 0;
    level = levels[6 - top].unknown00;
    option.unknown04[6] = level != 0 ? level - 1 : 0;
    option.unknown04[7] = levels[7 - top].unknown00 == 1;
  } else if (type == 1) {
    u8 *sound = GfDataBdat::getFP(BDAT_MNU_OPTION_SOUND);
    u32 top = Bdat::getIdTop(sound);
    option.unknown4c._1c = levels[1 - top].unknown00 == 1;
    option.unknown4c.unknown02 = getVolumeValue(levels[2 - top].unknown00, levels[2 - top].unknown01);
    option.unknown4c.unknown04 = getVolumeValue(levels[3 - top].unknown00, levels[3 - top].unknown01);
    option.unknown4c.unknown0e = getVolumeValue(levels[4 - top].unknown00, levels[4 - top].unknown01);
    option.unknown4c.unknown10 = getVolumeValue(levels[5 - top].unknown00, levels[5 - top].unknown01);
    option.unknown4c.unknown14 = getVolumeValue(levels[6 - top].unknown00, levels[6 - top].unknown01);
    option.unknown4c.unknown0a = getVolumeValue(levels[7 - top].unknown00, levels[7 - top].unknown01);
    option.unknown4c.unknown16 = getVolumeValue(levels[8 - top].unknown00, levels[8 - top].unknown01);
  } else if (type == 2) {
    u8 *disp = GfDataBdat::getFP(BDAT_MNU_OPTION_DISP);
    u32 index = 1 - Bdat::getIdTop(disp);
    option.unknown4c._1a = getGammaValue(levels[index].unknown00, levels[index].unknown01);
  }
}

void GfMenuObjOption::convOptionDataToLevelList(u32 type, const SDataOption &option) {
  unknown50.clear();
  getDefaultLevel(type, unknown50);
  if (type == 0) {
    u8 *camera = GfDataBdat::getFP(BDAT_MNU_OPTION_CAMERA);
    u32 top = Bdat::getIdTop(camera);
    unknown50[1 - top].unknown00 = option.unknown04[0] ? 1 : 2;
    unknown50[2 - top].unknown00 = option.unknown04[1] ? 1 : 2;
    unknown50[3 - top].unknown00 = option.unknown04[4] + 1;
    unknown50[4 - top].unknown00 = option.unknown04[3] + 1;
    unknown50[5 - top].unknown00 = option.unknown04[5] + 1;
    unknown50[6 - top].unknown00 = option.unknown04[6] + 1;
    unknown50[7 - top].unknown00 = option.unknown04[7] ? 1 : 2;
  } else if (type == 1) {
    u8 *sound = GfDataBdat::getFP(BDAT_MNU_OPTION_SOUND);
    u32 top = Bdat::getIdTop(sound);
    unknown50[1 - top].unknown00 = option.unknown4c._1c ? 1 : 2;
    unknown50[2 - top].unknown00 = getVolumeLevel(option.unknown4c.unknown02, unknown50[2 - top].unknown01);
    unknown50[3 - top].unknown00 = getVolumeLevel(option.unknown4c.unknown04, unknown50[3 - top].unknown01);
    unknown50[4 - top].unknown00 = getVolumeLevel(option.unknown4c.unknown0e, unknown50[4 - top].unknown01);
    unknown50[5 - top].unknown00 = getVolumeLevel(option.unknown4c.unknown10, unknown50[5 - top].unknown01);
    unknown50[6 - top].unknown00 = getVolumeLevel(option.unknown4c.unknown14, unknown50[6 - top].unknown01);
    unknown50[7 - top].unknown00 = getVolumeLevel(option.unknown4c.unknown0a, unknown50[7 - top].unknown01);
    unknown50[8 - top].unknown00 = getVolumeLevel(option.unknown4c.unknown16, unknown50[8 - top].unknown01);
  } else if (type == 2) {
    u8 *disp = GfDataBdat::getFP(BDAT_MNU_OPTION_DISP);
    u32 top = Bdat::getIdTop(disp);
    unknown50[1 - top].unknown00 = getGammaLevel(option.unknown4c._1a, unknown50[1 - top].unknown01);
  }
}

void GfMenuObjOption::refreshLevel(u32 type) {
  mm::mtl::FixStr<32> name;
  const char *typeName = nullptr;
  switch (type) {
  case 0:
    typeName = "cam";
    break;
  case 1:
    typeName = "snd";
    break;
  case 2:
    typeName = "dis";
    break;
  }
  for (u32 i = 0; i < unknown50.size(); i++) {
    if (unknown50[i].unknown01 == 2) {
      name.format("TXT_%s_item_param_on@%02d", typeName, i + 1);
      ui::UIObjectAcc on(unknown18, name.c_str());
      name.format("TXT_%s_item_param_off@%02d", typeName, i + 1);
      ui::UIObjectAcc off(unknown18, name.c_str());
      on.setDisp(unknown50[i].unknown00 == 1);
      off.setDisp(unknown50[i].unknown00 == 2);
    } else {
      name.format("IMG_%s_item_param_base@%02d", typeName, i + 1);
      ui::UIObjectAcc base(unknown18, name.c_str());
      name.format("IMG_%s_item_param_point@%02d", typeName, i + 1);
      ui::UIObjectAcc point(unknown18, name.c_str());
      if (base.isValid() && point.isValid()) {
        f32 ratio = mm::clamp(static_cast<f32>(unknown50[i].unknown00 - 1) / static_cast<f32>(unknown50[i].unknown01 - 1), 0.0f, 1.0f);
        GfMenuObjUtil::placeObjectHRatio(base.unknown10, point.unknown10, ratio, -4);
        if (type == 2 && i + 1 == 1) {
          GfMenuManager::applyGammaCorrectValue(ratio);
        }
      }
    }
  }
}

void GfMenuObjOption::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 2: {
    SDataOption *saved = GfGameUtilSaveData::getValidOptionData();
    if (unknown20->unknown3c2 != -1) {
      convLevelListToOptionData(unknown20->unknown3c2, unknown20->unknown50, unknown20->unknown98);
    }
    unknown20->unknown98.unknown4c.unknown00 = static_cast<int>(unknown20->unknown98.unknown4c.unknown02 * 0.875f);
    unknown20->unknown98.unknown4c.unknown06 = unknown20->unknown98.unknown4c.unknown00;
    unknown20->unknown98.unknown4c.unknown08 = unknown20->unknown98.unknown4c.unknown04;
    unknown20->unknown98.unknown4c.unknown12 = unknown20->unknown98.unknown4c.unknown10;
    unknown20->unknown98.unknown4c.unknown0c = unknown20->unknown98.unknown4c.unknown0a;
    unknown20->unknown98.unknown4c.unknown18 = unknown20->unknown98.unknown4c.unknown16;
    bool isSame = true;
    for (u32 i = 0; i < sizeof(saved->unknown04); i++) {
      if (saved->unknown04[i] != unknown20->unknown98.unknown04[i]) {
        isSame = false;
        break;
      }
    }
    u32 fade;
    if (isSame && !saved->unknown4c.isDirty(unknown20->unknown98.unknown4c)) {
      fade = 2;
    } else {
      *saved = unknown20->unknown98;
      GfGameUtilSaveData::flushOptionSaveData();
      unknown20->unknown128.unknown005();
      unknown20->unknown128.unknown002(&GfMenuObjOption::seqSave);
      unknown20->unknown128.unknown002(&GfMenuObjOption::seqSaveWait);
      fade = 0;
    }
    GfMenuObjUtil::setCommonFadeOut(acc.unknown10, fade, 0);
    break;
  }
  case 3:
    if (event.unknown08 == 2) {
      GfMenuObject::termCallContext(acc.unknown10);
      acc.setTerm();
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjOption>(const mm::mtl::Delegate<bool()> *);
