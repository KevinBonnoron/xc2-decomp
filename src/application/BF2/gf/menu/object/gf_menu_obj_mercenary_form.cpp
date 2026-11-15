#include "gf/menu/object/gf_menu_obj_mercenary_form.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/game/gf_game_voice.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_mission_adapter.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/object/gf_menu_obj_cmn_status.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_mercenary_top.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_sort.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjMercenaryForm::GfMenuObjMercenaryForm(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(nullptr), unknown30(nullptr), unknown78(nullptr), unknown80(nullptr), unknown98(nullptr), unknowna0(nullptr), unknowna8(nullptr),
      unknownb0(nullptr), unknownb8(nullptr), unknown100(0), unknown104(0), unknown108(this), unknown430(false), unknown438(this), unknown8f0(false), unknown8f8(nullptr) {
  for (int i = 0; i < 8; i++) {
    unknownc0[i] = unknown160();
  }
  unknownb8 = GfMenuCallContext::create();
}

GfMenuObjMercenaryForm::~GfMenuObjMercenaryForm() {
  for (int i = 0; i < 8; i++) {
    unknownc0[i] = nullptr;
  }
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknownb8);
  mm::mtl::safeRelease(unknownb0);
  mm::mtl::safeRelease(unknowna8);
  mm::mtl::safeRelease(unknowna0);
  mm::mtl::safeRelease(unknown98);
  mm::mtl::safeRelease(unknown80);
  mm::mtl::safeRelease(unknown78);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown88);
  mm::mtl::safeRelease(unknown90);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(unknown50[0]);
  mm::mtl::safeRelease(unknown50[1]);
  mm::mtl::safeRelease(unknown50[2]);
}

void GfMenuObjMercenaryForm::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  mm::mtl::FixStr<32> name;
  unknown24 = GfMenuReference::getReferenceTeamID();
  unknown28 = GfMenuBladeList::create();
  unknown30 = GfMenuBladeList::create();
  {
    // Braced scope (ruling 3): the game keeps the parameters of these setup calls in the stack slot shared with the
    // TeamSetup and the cursor settings below.
    ui::UIListInfoBase::SetupParam bladeParam;
    bladeParam.unknown08 = 6;
    unknown28->setup(getAllocator(ALLOCATOR_UNKNOWN_0), bladeParam);
    unknown38 = GfMenuBladeList::create();
    bladeParam.unknown08 = 6;
    unknown38->setup(getAllocator(ALLOCATOR_UNKNOWN_0), bladeParam);
    unknown40 = GfMenuBladeList::create();
    bladeParam.unknown08 = 6;
    unknown40->setup(getAllocator(ALLOCATOR_UNKNOWN_0), bladeParam);
    unknown48 = GfMenuBladeList::create();
    bladeParam.unknown08 = 6;
    unknown48->setup(getAllocator(ALLOCATOR_UNKNOWN_0), bladeParam);
  }
  {
    GfMenuBladeList::TeamSetup setup;
    setup.unknown14 = 3;
    setup.unknown00.unknown08 = 3;
    setup.unknown00.unknown0c = 5;
    setup.unknown1c = false;
    unknown30->clear();
    unknown30->setupFromTeam(setup);
  }
  u16 sortId = GfMenuObjSort::getSortID(0xe, 0);
  if (sortId >= 4 && sortId <= 6) {
    unknown30->sort(sortId, true);
  } else {
    unknown30->sort(sortId, false);
  }
  {
    ui::UIObjectAcc form(main.unknown10, "LAY_form");
// __LINE__ must be 226 as in the original file: it is the line argument of operator new.
#line 226
    FormListener *formListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) FormListener(this);
    formListener->addRef();
    ui::UIEventManager::get()->registObjectListener(form.unknown10, formListener);
    if (formListener != nullptr) {
      formListener->release();
    }
  }
  GfMenuAdapterManager::beginAddAfter();
  {
    ui::UIObjectAcc unit(main.unknown10, "LAY_form_unit_bl");
    {
      ui::UISelectObjList::CreateParam createParam;
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown78 = ui::UISelectObjList::create(createParam);
    }
    unknown78->pickupObject(unit.unknown10, "LAY_form_unit_bl_face@%02d", 1);
    {
      ui::UICtrlCursorSelect::CursorSetting setting;
      setting.setType(0);
      setting.unknown18 = 0;
      unknown80 = ui::UICtrlCursorSelect::create(main.searchChild("IMG_form_unit_bl_cursor"), setting, unknown78);
    }
    for (u32 i = 0; i < unknown78->getSize(); i++) {
      name.format("IMG_form_unit_bl_face@%02d", i + 1);
      GfMenuCharDataAdapter::createFromBladeList(unit.searchChild(name.c_str()), 3, unknown28, i, false);
      name.format("IMG_form_unit_bl_info_elem@%02d", i + 1);
      GfMenuCharDataAdapter::createFromBladeList(unit.searchChild(name.c_str()), 0x2a, unknown28, i, false);
      name.format("IMG_form_unit_bl_info_wpn@%02d", i + 1);
      GfMenuCharDataAdapter::createFromBladeList(unit.searchChild(name.c_str()), 0x29, unknown28, i, false);
    }
// __LINE__ must be 263 as in the original file: it is the line argument of operator new.
#line 263
    UnitListener *unitListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) UnitListener(this);
    unitListener->addRef();
    ui::UIEventManager::get()->registObjectListener(unit.unknown10, unitListener);
    if (unitListener != nullptr) {
      unitListener->release();
    }
    setFSInputObject(1, unit.unknown10);
  }
// __LINE__ must be 271 as in the original file: it is the line argument of operator new.
#line 271
  ApplyListener *applyListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ApplyListener(this);
  applyListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_form_apply"), applyListener);
  if (applyListener != nullptr) {
    applyListener->release();
  }
  {
    ui::UIObjectAcc list(main.unknown10, "LAY_form_list_bl");
    {
      ui::UISelectObjList::CreateParam createParam;
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown98 = ui::UISelectObjList::create(createParam);
    }
    unknown98->pickupObject(list.unknown10, "LAY_form_lsit_bl_face@%02d", 1);
    {
      ui::UICtrlCursorSelect::CursorSetting setting;
      setting.setType(0);
      setting.unknown18 = 0;
      unknowna0 = ui::UICtrlCursorSelect::create(main.searchChild("IMG_form_list_bl_cursor"), setting, unknown98);
    }
    for (u32 i = 0; i < unknown98->getSize(); i++) {
      name.format("IMG_form_list_bl_face@%02d", i + 1);
      GfMenuCharDataAdapter *adapter = GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.c_str()), 3, unknown30, i, false);
      if (adapter != nullptr) {
        adapter->setSlotList(unknown28);
      }
      name.format("IMG_form_list_bl_info_elem@%02d", i + 1);
      GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.c_str()), 0x2a, unknown30, i, false);
      name.format("IMG_form_list_bl_info_wpn@%02d", i + 1);
      GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.c_str()), 0x29, unknown30, i, false);
    }
// __LINE__ must be 312 as in the original file: it is the line argument of operator new.
#line 312
    ListListener *listListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
    listListener->addRef();
    ui::UIEventManager::get()->registObjectListener(list.unknown10, listListener);
    if (listListener != nullptr) {
      listListener->release();
    }
    setFSInputObject(2, list.unknown10);
    GfMenuObjUtil::createVScrollBarPlugin(list.searchChild("IMG_form_list_bl_scroll_bar"), unknown30, "IMG_form_list_bl_scroll_base", true);
  }
  {
    ui::UIObjectAcc mission(main.unknown10, "LAY_form_mission");
    for (u32 i = 0; i < 3; i++) {
      name.format("IMG_form_mis_cond_icon@%02d", i + 1);
      GfMenuMissionAdapter *adapter = GfMenuMissionAdapter::createFromReferenceMission(mission.searchChild(name.c_str()), 0x12, i, false);
      if (adapter != nullptr) {
        name.format("LAY_form_mis_cond@%02d", i + 1);
        adapter->unknown24 = mission.searchChild(name.c_str());
      }
      name.format("TXT_form_mis_cond_txt@%02d", i + 1);
      GfMenuMissionAdapter::createFromReferenceMission(mission.searchChild(name.c_str()), 0x11, i, false);
      u32 text = mission.searchChild(name.c_str());
      if (text != 0) {
        name.format("TXT_form_mis_cond_val@%02d", i + 1);
        GfMenuMissionAdapter::createFromReferenceMission(mission.searchChild(name.c_str()), 0x13, i, false);
        GfMenuObjUtil::createDockPlugin(mission.searchChild(name.c_str()), text, 1, mm::Pnt<s16>(12, 0), 0);
        name.format("TXT_form_mis_cond_lv@%02d", i + 1);
        GfMenuMissionAdapter::createFromReferenceMission(mission.searchChild(name.c_str()), 0x14, i, false);
        GfMenuObjUtil::createDockPlugin(mission.searchChild(name.c_str()), text, 1, mm::Pnt<s16>(12, 0), 0);
        name.format("TXT_form_mis_cond_num@%02d", i + 1);
        GfMenuReferenceAdapter::create(mission.searchChild(name.c_str()), unknownc0[i], true);
        name.format("TXT_form_mis_cond_max@%02d", i + 1);
        GfMenuMissionAdapter::createFromReferenceMission(mission.searchChild(name.c_str()), 0x16, i, false);
      }
    }
    for (u32 i = 0; i < 3; i++) {
      name.format("TXT_form_mis_fs_name@%02d", i + 1);
      GfMenuMissionAdapter *adapter = GfMenuMissionAdapter::createFromReferenceMission(mission.searchChild(name.c_str()), 0x10, i, false);
      if (adapter != nullptr) {
        name.format("LAY_form_mis_fs@%02d", i + 1);
        adapter->unknown24 = mission.searchChild(name.c_str());
      }
      name.format("TXT_form_mis_fs_bl_num@%02d", i + 1);
      GfMenuReferenceAdapter::create(mission.searchChild(name.c_str()), unknownc0[i + 4], true);
    }
  }
  {
    ui::UIObjectAcc leader(main.unknown10, "LAY_leader");
// __LINE__ must be 395 as in the original file: it is the line argument of operator new.
#line 395
    LeaderListener *leaderListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LeaderListener(this);
    leaderListener->addRef();
    ui::UIEventManager::get()->registObjectListener(leader.unknown10, leaderListener);
    if (leaderListener != nullptr) {
      leaderListener->release();
    }
    setFSInputObject(4, leader.unknown10);
    {
      ui::UISelectObjList::CreateParam createParam;
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown88 = ui::UISelectObjList::create(createParam);
    }
    {
      ui::UICtrlCursorSelect::CursorSetting setting;
      setting.setType(0);
      setting.unknown18 = 0;
      unknown90 = ui::UICtrlCursorSelect::create(main.searchChild("IMG_leader_sel_list_bl_cursor"), setting, unknown88);
    }
    GfMenuCharDataAdapter::createFromReferenceBlade(leader.searchChild("TXT_leader_sel_index_name"), 2, 0, false);
    GfMenuCharDataAdapter::createFromReferenceBlade(leader.searchChild("TXT_leader_sel_info_name"), 0x58, 0, false);
    for (u32 i = 0; i < unknown78->getSize(); i++) {
      name.format("IMG_leader_sel_list_bl_face@%02d", i + 1);
      GfMenuCharDataAdapter::createFromBladeList(leader.searchChild(name.c_str()), 3, unknown28, i, false);
    }
  }
  GfMenuAdapterManager::endAddAfter();
  {
    ui::UIObjectAcc start(main.unknown10, "LAY_start");
    for (u32 i = 1; i < 6; i++) {
      name.format("IMG_mis_start_bl@%02d", i);
      GfMenuCharDataAdapter::createFromBladeList(start.searchChild(name.c_str()), 0x36, unknown28, i, false);
    }
// __LINE__ must be 440 as in the original file: it is the line argument of operator new.
#line 440
    StartListener *startListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) StartListener(this);
    startListener->addRef();
    ui::UIEventManager::get()->registObjectListener(start.unknown10, startListener);
    if (startListener != nullptr) {
      startListener->release();
    }
  }
  {
    ui::UIObjectAcc blImg(main.unknown10, "LAY_bl_img");
    GfMenuCharDataAdapter::createFromReferenceBlade(blImg.searchChild("IMG_leader_bl_img"), 0x36, 0, false);
// __LINE__ must be 453 as in the original file: it is the line argument of operator new.
#line 453
    BlImgListener *blImgListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) BlImgListener(this);
    blImgListener->addRef();
    ui::UIEventManager::get()->registObjectListener(blImg.unknown10, blImgListener);
    if (blImgListener != nullptr) {
      blImgListener->release();
    }
  }
  {
    ui::UIObjectAcc preset(main.unknown10, "LAY_preset");
    {
      ui::UISelectObjList::CreateParam createParam;
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknowna8 = ui::UISelectObjList::create(createParam);
    }
    // The game passes the handle of LAY_main, not the one of LAY_preset, to pickupObject (1.0.0: 0x7100491d88 loads the saved main handle from the stack).
    unknowna8->pickupObject(main.unknown10, "LAY_preset_bl_base@%02d", 1);
    {
      ui::UICtrlCursorSelect::CursorSetting setting;
      setting.setType(0);
      setting.unknown18 = 0;
      unknownb0 = ui::UICtrlCursorSelect::create(main.searchChild("IMG_preset_cursor"), setting, unknowna8);
    }
    {
      ui::UIListInfoBase::SetupParam presetParam;
      unknown68 = GfMenuIDList::create();
      presetParam.unknown08 = 3;
      unknown68->setup(getAllocator(ALLOCATOR_UNKNOWN_0), presetParam);
      for (u32 i = 0; i < 8; i++) {
        unknown68->addContents(MenuID{i});
      }
    }
    GfMenuObjUtil::createVScrollBarPlugin(preset.searchChild("IMG_preset_scroll_bar"), unknown68, "IMG_preset_scroll_base", false);
    // The game's preheader (1.0.0: 0x7100491ee0-0x7100491f00) keeps the addresses of the face and wpn formats and the constants 0x39 and 0x29 in registers. The for forms tried (u32, int and size_t
    // counter, `!= 3`, `<= 2`, a while with an entry test) all end with another preheader (the for with a u32 counter rematerialises 0x29 in the body); only the do-while matches.
    u32 i = 0;
    do {
      {
        ui::UIListInfoBase::SetupParam presetBladeParam;
        presetBladeParam.unknown08 = 6;
        unknown50[i] = GfMenuBladeList::create();
        unknown50[i]->setup(getAllocator(ALLOCATOR_UNKNOWN_0), presetBladeParam);
      }
      name.format("TXT_preset_bl_no@%02d", i + 1);
      GfMenuReferenceAdapter::create(preset.searchChild(name.c_str()), unknownc0[i + 4], false);
      for (u32 j = 0; j < 6; j++) {
        name.format("IMG_preset_bl_face@%02d%02d", i + 1, j + 1);
        GfMenuCharDataAdapter::createFromBladeList(preset.searchChild(name.c_str()), 3, unknown50[i], j, false);
        GfMenuCharDataAdapter::createFromBladeList(preset.searchChild(name.c_str()), 0x49, unknown50[i], j, false);
        name.format("IMG_preset_bl_info_elem@%02d%02d", i + 1, j + 1);
        GfMenuCharDataAdapter::createFromBladeList(preset.searchChild(name.c_str()), 0x2a, unknown50[i], j, false);
        GfMenuCharDataAdapter::createFromBladeList(preset.searchChild(name.c_str()), 0x39, unknown50[i], j, false);
        name.format("IMG_preset_bl_info_wpn@%02d%02d", i + 1, j + 1);
        GfMenuCharDataAdapter::createFromBladeList(preset.searchChild(name.c_str()), 0x29, unknown50[i], j, false);
      }
      i++;
    } while (i < 3);
// __LINE__ must be 524 as in the original file: it is the line argument of operator new.
#line 524
    PresetListener *presetListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PresetListener(this);
    presetListener->addRef();
    ui::UIEventManager::get()->registObjectListener(preset.unknown10, presetListener);
    if (presetListener != nullptr) {
      presetListener->release();
    }
    setFSInputObject(3, preset.unknown10);
  }
  refreshBladeInfo();
// __LINE__ must be 532 as in the original file: it is the line argument of operator new.
#line 532
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  sendOpenEvent(main.searchChild("LAY_form_list_bl"), 0, 0.0f);
  disableFSInput();
  GfMenuObject::initialize();
}

void GfMenuObjMercenaryForm::sendOpenEvent(u32 handle, int type, f32 delay) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_form_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = type;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_33;
  GfMenuObject::sendEvent(handle, event, delay);
}

void GfMenuObjMercenaryForm::sendCloseEvent(u32 handle, int type, f32 delay) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_form_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = type;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_34;
  GfMenuObject::sendEvent(handle, event, delay);
}

void GfMenuObjMercenaryForm::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMercenaryForm::update() {
  unknown108.unknown003();
  unknown438.unknown003();
  if (unknown104 != 0) {
    unknown104--;
  }
  GfMenuObject::update();
}

void GfMenuObjMercenaryForm::refreshBladeInfo() {
  {
    ui::UIObjectAcc info(unknown18, "LAY_form_list_bl_info");
    u32 count = info.countChild("LAY_form_list_bl_info@%02d", 1);
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < count; i++) {
      name.format("IMG_form_list_bl_info_elem@%02d", i + 1);
      info.setDispChild(true, name.c_str());
      name.format("LAY_form_list_bl_info_wpn@%02d", i + 1);
      info.setDispChild(false, name.c_str());
    }
  }
  {
    ui::UIObjectAcc info(unknown18, "LAY_form_unit_bl_info");
    u32 count = info.countChild("LAY_form_unit_bl_info@%02d", 1);
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < count; i++) {
      name.format("IMG_form_unit_bl_info_elem@%02d", i + 1);
      info.setDispChild(true, name.c_str());
      name.format("LAY_form_unit_bl_info_wpn@%02d", i + 1);
      info.setDispChild(false, name.c_str());
    }
  }
}

void GfMenuObjMercenaryForm::setDetailBladePos(u32 handle) {
  ui::UIObjectAcc detail(unknown18, "LAY_form_bl_detail_bl");
  if (handle == 0) {
    detail.setDisp(false);
  } else {
    ui::UIObjectAcc blade(handle);
    mm::Rect<s16> rect;
    blade.getRect(rect, 1);
    mm::Pnt<s16> pos;
    pos.x = rect.x;
    pos.y = rect.y;
    detail.setPos(pos);
    detail.setDisp(true);
  }
}

void GfMenuObjMercenaryForm::updateReserveBlade(u32 index) {
  u32 blade = unknown30->getContents(index).unknown00;
  GfMenuReference::setReferenceBladeID(0, blade);
  updateBladeCount(blade != 0, true);
  refreshBladeList();
}

bool GfMenuObjMercenaryForm::chkTempUnlink(u32 blade) { return mm::mtl::find(unknown598.begin(), unknown598.end(), static_cast<u16>(blade)) != unknown598.end(); }

void GfMenuObjMercenaryForm::addTempUnlink(u32 blade) {
  if (!chkTempUnlink(blade)) {
    unknown598.push_back(blade);
  }
}

void GfMenuObjMercenaryForm::delTempUnlink(u32 blade) {
  u16 *it = mm::mtl::find(unknown598.begin(), unknown598.end(), static_cast<u16>(blade));
  if (it != unknown598.end()) {
    unknown598.erase(it);
  }
}

bool GfMenuObjMercenaryForm::chkUnitBladeList(u32 blade) {
  for (u32 i = 0; i < unknown28->getSize(); i++) {
    if (unknown28->getContents(i).unknown00 == blade) {
      return true;
    }
  }
  return false;
}

bool GfMenuObjMercenaryForm::seqDepartureNotice() {
  bool isEnd;
  if (!unknown430) {
    GfMenuManager::openCommonWindow(0x25);
    isEnd = false;
    unknown430 = true;
  } else {
    isEnd = !GfMenuManager::isOpenCommonWindow();
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqStartActiveFS() {
  ui::UIObjectAcc base(unknown18, "IMG_start_fs_base");
  bool isEnd;
  if (!unknown430) {
    ui::UIObjectAcc fs(unknown18, "LAY_start_fs");
    fs.setDisp(true);
    base.startAnimation("start", false);
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r");
    GfMenuObjUtil::startCtrl(unknown18, param, "LAY_start_fs_on");
    unknown430 = true;
    isEnd = false;
  } else if (!base.isPlayingAnimation()) {
    unknown430 = false;
    unknown108.unknown002(&GfMenuObjMercenaryForm::seqOpenActiveFS);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqOpenActiveFS() {
  ui::UIObjectAcc base(unknown18, "IMG_start_fs_base");
  bool isEnd;
  if (!unknown430) {
    ui::UIObjectAcc fs(unknown18, "LAY_start_fs");
    fs.setDispChild(false, "LAY_start_fs_on");
    base.startAnimation("result", false);
    unknown430 = true;
    isEnd = false;
  } else if (!base.isPlayingAnimation()) {
    unknown430 = false;
    unknown108.unknown002(&GfMenuObjMercenaryForm::seqDispActiveFS);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqDispActiveFS() {
  ui::UIObjectAcc base(unknown18, "IMG_start_fs_base");
  bool isEnd;
  if (!unknown430) {
    base.startAnimation("fade_in_info", false);
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r");
    GfMenuObjUtil::startCtrl(unknown18, param, "LAY_start_fs_info");
    isEnd = false;
    unknown430 = true;
  } else if (!base.isPlayingAnimation()) {
    unknown108.unknown004(90);
    unknown108.unknown002(&GfMenuObjMercenaryForm::seqEndActiveFS);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqEndActiveFS() {
  ui::UIObjectAcc fs(unknown18, "LAY_start_fs");
  fs.setDisp(false);
  unknown108.unknown002(&GfMenuObjMercenaryForm::seqLeaveBlade);
  return true;
}

bool GfMenuObjMercenaryForm::seqPresetEnd() {
  ui::UIObjectAcc preset(unknown18, "LAY_preset");
  sendCloseEvent(preset.unknown10, 0, 0.0f);
  sendOpenEvent(preset.searchSibiling("LAY_form_menu"), 0, 0.0f);
  return true;
}

bool GfMenuObjMercenaryForm::seqRevertBladeSet() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown430) {
    GfMenuManager::openCommonWindow(200);
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    returnFSSubLayer(this);
    isEnd = true;
    unknown430 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqReturnMissionSelect() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown430) {
    GfMenuManager::openCommonWindow(0x9f);
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    s16 result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
      if (unknown598.empty()) {
        returnFSSubLayer(this);
      } else {
        unknown108.unknown002(&GfMenuObjMercenaryForm::seqRevertBladeSet);
      }
    } else {
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
      sendOpenEvent(main.searchSibiling("LAY_form_list_bl"), 0, 0.0f);
    }
    isEnd = true;
    unknown430 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqConfirmRemoveBladeSet() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown430) {
    GfMenuManager::openCommonWindow(199);
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    s16 result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
      addTempUnlink(unknown30->getContents(unknown30->getIndex(false)).unknown00);
      addUnitBladeList(unknown30->getContents(unknown30->getIndex(false)).unknown00);
    }
    sendOpenEvent(main.searchSibiling("LAY_form_list_bl"), 0, 0.0f);
    isEnd = true;
    unknown430 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

void GfMenuObjMercenaryForm::addUnitBladeList(u32 blade) {
  if (chkUnitBladeList(blade)) {
    return;
  }
  MenuBladeInfo info;
  info.unknown00 = blade;
  info.unknown04 = GfDataBlade::getCreator(blade);
  unknown28->addContents(info);
  updateBladeCount(false, true);
  SCOM_FIELD_VOICE::createMercenariesIn(info.unknown00);
}

bool GfMenuObjMercenaryForm::seqOpenImage() {
  ui::UIObjectAcc image(unknown18, "IMG_leader_bl_img");
  bool isEnd;
  if (!image.isStreaming()) {
    ui::UIObjectAcc layout(unknown18, "LAY_bl_img");
    u32 blade = GfMenuReference::getReferenceBladeID(0);
    layout.setLayout(image.unknown10, "character");
    GfMenuObjUtil::ImageParam imageParam;
    if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
      mm::Vec2 scale;
      image.getScale(scale);
      scale.x = imageParam.unknown04 * scale.x;
      scale.y = imageParam.unknown04 * scale.y;
      image.setScale(scale);
      GfMenuObjUtil::addPos(image.unknown10, imageParam.unknown00, imageParam.unknown02);
    }
    image.setAlpha(1.0f);
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r");
    param.unknown14 = 8;
    param.unknown11 = true;
    GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    image.setAlpha(0.0f);
    GfMenuObjUtil::playSE("se_fld_allmap_503");
    isEnd = true;
  } else {
    image.setAlpha(0.0f);
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqDepartureStart() {
  unknown430 = false;
  unknown108.unknown002(&GfMenuObjMercenaryForm::seqApperBlade);
  unknown8f8 = SCOM_FIELD_VOICE::createMercenariesLeader(GfMenuReference::getReferenceBladeID(0));
  return true;
}

bool GfMenuObjMercenaryForm::seqApperBlade() {
  if (unknown8f8 != nullptr) {
    if (GfGameVoice::getResult(unknown8f8) >= 3) {
      unknown8f8 = nullptr;
    } else {
      return false;
    }
  }
  ui::UIObjectAcc image(unknown18, "LAY_bl_img");
  bool isEnd;
  if (!unknown430) {
    {
      ui::EventData event;
      event.unknown00 = 0x100;
      sendEvent(image.unknown10, event, 0.0f);
    }
    {
      ui::UIObjectAcc start(unknown18, "LAY_start");
      mm::mtl::FixStr<32> name;
      mm::mtl::FixStr<32> anime;
      for (u32 i = 0; i < unknown78->getSize(); i++) {
        u32 blade = unknown28->getContents(i + 1).unknown00;
        name.format("IMG_mis_start_bl@%02d", i + 1);
        {
          ui::UIObjectAcc bladeImage(start.unknown10, name.c_str());
          start.setLayout(bladeImage.unknown10, "mnu090_anim_sub_1");
          GfMenuObjUtil::ImageParam imageParam;
          if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
            mm::Vec2 scale;
            bladeImage.getScale(scale);
            scale.x = imageParam.unknown04 * scale.x;
            scale.y = imageParam.unknown04 * scale.y;
            bladeImage.setScale(scale);
            GfMenuObjUtil::addPos(bladeImage.unknown10, imageParam.unknown00, imageParam.unknown02);
          }
        }
        anime.format("mnu090_anim_sub_%d", i + 1);
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x10000000;
        param.unknown50 = anime.c_str();
        param.unknown58 = "start";
        GfMenuObjUtil::startCtrl(unknown78->getObject(i), param, nullptr);
      }
    }
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(image.unknown10))) {
    SCOM_FIELD_VOICE::createMercenariesStart(unknown28->getContents(0).unknown00);
    unknown108.unknown004(60);
    unknown108.unknown002(&GfMenuObjMercenaryForm::seqLeaveBlade);
    isEnd = true;
    unknown430 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqDepartureEnd() {
  bool isEnd;
  if (!unknown430) {
    GfMenuManager::openCommonWindow(0x25);
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    ui::UIObjectAcc start(unknown18, "LAY_start");
    sendCloseEvent(start.unknown10, 0, 0.0f);
    u32 team = GfMenuReference::getReferenceTeamID();
    u32 mission = GfMenuReference::getReferenceMissionID();
    for (u32 i = 0; i < unknown28->getSize(); i++) {
      GfGameMercenaries::addTeamMember(team, unknown28->getContents(i).unknown00);
    }
    GfGameMercenaries::orderMission(team, mission);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqLeaveBlade() {
  ui::UIObjectAcc image(unknown18, "LAY_bl_img");
  bool isEnd;
  if (!unknown430) {
    {
      ui::EventData event;
      event.unknown00 = 0x101;
      sendEvent(image.unknown10, event, 0.0f);
    }
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < unknown78->getSize(); i++) {
      name.format("mnu090_anim_sub_%d", i + 1);
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x10000000;
      param.unknown50 = name.c_str();
      param.unknown58 = "end";
      GfMenuObjUtil::startCtrl(unknown78->getObject(i), param, nullptr);
    }
    {
      ui::UIObjectAcc effect(unknown18, "IMG_start_eff");
      effect.setDisp(true);
      effect.startAnimation("end", false);
    }
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(image.unknown10))) {
    unknown108.unknown002(&GfMenuObjMercenaryForm::seqDepartureEnd);
    isEnd = true;
    unknown430 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqPresetSave() {
  bool isEnd;
  if (!unknown430) {
    GfMenuManager::openCommonWindow(0x43);
    isEnd = false;
    unknown430 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    s16 result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
      u32 index = unknown68->getIndex(true);
      GfMenuBladeList *list = unknown50[index];
      unknown121 *preset = GfDataMercenaries::getPreset(index);
      MenuBladeInfo info;
      info.unknown00 = 0;
      info.unknown04 = 0;
      list->clear();
      for (u32 i = 0; i < 6 && i < unknown28->getSize(); i++) {
        u16 blade = unknown28->getContents(i).unknown00;
        preset->unknown00[i] = blade;
        info.unknown00 = blade;
        if (blade != 0) {
          info.unknown04 = GfDataBlade::getCreator(blade);
        } else {
          info.unknown04 = blade;
        }
        list->addContents(info);
      }
    }
    unknown108.unknown004(30);
    unknown108.unknown002(&GfMenuObjMercenaryForm::seqPresetEnd);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryForm::seqPresetLoad() {
  u32 index = unknown68->getIndex(true);
  unknown121 *preset = GfDataMercenaries::getPreset(index);
  MenuBladeInfo info;
  info.unknown00 = 0;
  info.unknown04 = 0;
  unknown28->clear();
  for (u32 i = 0; i < 6; i++) {
    u16 blade = preset->unknown00[i];
    u32 creator = 0;
    if (blade == 0) {
      info.unknown00 = blade;
    } else if (GfMenuObjUtil::isBladeSelectable(blade, nullptr)) {
      info.unknown00 = blade;
      creator = GfDataBlade::getCreator(blade);
    } else {
      info.unknown00 = 0;
    }
    info.unknown04 = creator;
    unknown28->addContents(info);
  }
  unknown108.unknown002(&GfMenuObjMercenaryForm::seqPresetEnd);
  return true;
}

void GfMenuObjMercenaryForm::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 0;
    param.unknown00 = 6;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case 2: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown00 = 6;
    param.unknown0c = true;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMercenaryForm::FormListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown0c = 0;
    unknown10 = 0;
    GfMenuObjOperationInfo::setGuideText(0x25, 0);
    GfMenuObjCmnStatus::openBlStatus(0, -1);
    break;
  case 3:
    if (event.unknown08 == 0) {
      break;
    }
    if (event.unknown08 == 2) {
      unknown20->sendOpenEvent(acc.searchSibiling("LAY_leader"), 0, 0.0f);
    }
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case GfMenuTypes::unknown003_258: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown04 = 1;
    param.unknown00 = 6;
    param.unknown10 = 2;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    GfMenuObjCmnStatus::closeBlStatus();
    break;
  }
  case GfMenuTypes::unknown003_259: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown04 = 0;
    param.unknown00 = 6;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    unknown20->sendOpenEvent(acc.searchChild("LAY_form_list_bl"), 1, 0.0f);
    GfMenuObjOperationInfo::setGuideText(0x25, 0);
    GfMenuObjCmnStatus::openBlStatus(0, -1);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMercenaryForm::ApplyListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    acc.setDisp(true);
    ui::UIObjectAcc base(acc.unknown10, "IMG_form_apply_base");
    base.startAnimation("non", false);
    acc.setDispChild(false, "LAY_form_apply_caption");
    unknown0c = 0;
    break;
  }
  case 0xc:
    if (unknown0c == 1) {
      ui::UIObjectAcc base(acc.unknown10, "IMG_form_apply_base");
      base.startAnimation("loop", false);
    }
    break;
  case GfMenuTypes::unknown003_33:
    if (unknown0c == 0) {
      ui::UIObjectAcc caption(acc.unknown10, "LAY_form_apply_caption");
      caption.setDisp(true);
      caption.setAlpha(1.0f);
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_in_r");
      param.unknown11 = true;
      param.unknown14 = 8;
      GfMenuObjUtil::startCtrl(caption.unknown10, param, nullptr);
      {
        ui::UIObjectAcc base(acc.unknown10, "IMG_form_apply_base");
        base.startAnimation("start", false);
        GfMenuObject::hookAnimationEvent(acc.unknown10, base.unknown10);
      }
      acc.setDisp(true);
      unknown0c = 1;
    }
    break;
  case GfMenuTypes::unknown003_34: {
    ui::UIObjectAcc base(acc.unknown10, "IMG_form_apply_base");
    base.startAnimation("non", false);
    {
      ui::UIObjectAcc caption(acc.unknown10, "LAY_form_apply_caption");
      int ctrl = GfMenuObjUtil::getCtrlID(caption.unknown10);
      if (ctrl != -1) {
        GfMenuObjUtil::stopCtrl(ctrl);
      }
      caption.setDisp(false);
    }
    unknown0c = 0;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMercenaryForm::BlImgListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case 3:
    break;
  case GfMenuTypes::unknown003_33:
    if (GfMenuReference::getReferenceBladeID(0) != 0) {
      acc.setDisp(true);
      acc.setAlpha(1.0f);
      unknown20->unknown438.unknown005();
      unknown20->unknown438.unknown002(&GfMenuObjMercenaryForm::seqOpenImage);
    }
    break;
  case GfMenuTypes::unknown003_34: {
    ui::UIObjectAcc image(acc.unknown10, "IMG_leader_bl_img");
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_r");
    param.unknown14 = 2;
    param.unknown11 = true;
    GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    break;
  }
  case GfMenuTypes::unknown003_256: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "mnu090_anim_leader";
    param.unknown58 = "start";
    param.unknown11 = true;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObjUtil::playSE(0xf);
    break;
  }
  case GfMenuTypes::unknown003_257: {
    {
      mm::Vec2 scale = {1.0f, 1.0f};
      acc.setScale(scale);
    }
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "mnu090_anim_leader";
    param.unknown58 = "end";
    param.unknown11 = true;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObjUtil::playSE("se_fld_allmap_503");
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMercenaryForm::StartListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_34: {
    GfMenuObjMercenaryTop::OpenParam param;
    param.unknown00 = 0;
    GfMenuObjMercenaryTop::registOpenParam(param);
    GfMenuObject::returnFSSubLayer(acc.unknown10, 2);
    break;
  }
  case GfMenuTypes::unknown003_33: {
    {
      GfMenuBladeList *blades = unknown20->unknown28;
      MenuBladeInfo info = blades->getContents(blades->getIndex(false));
      blades = unknown20->unknown28;
      blades->contents.erase(blades->getIndex(false) + blades->contents.begin());
      blades->subSize(1);
      blades->contentsChanged = true;
      blades = unknown20->unknown28;
      if (blades->getSize() == 0) {
        blades->addContents(info);
      } else {
        blades->contents.insert(blades->contents.begin(), info);
        blades->addSize(1);
        blades->contentsChanged = true;
      }
    }
    mm::mtl::FixStr<32> name;
    unknown20->unknown78->clear();
    for (u32 i = 0; i < 5; i++) {
      if (i < unknown20->unknown28->getSize() - 1) {
        name.format("LAY_mis_start_bl@%02d", i + 1);
        unknown20->unknown78->addObject(acc.searchChild(name.c_str()));
      }
      acc.setDispChild(false, name.c_str());
    }
    acc.setDisp(true);
    unknown20->unknown108.unknown005();
    unknown20->unknown108.unknown002(&GfMenuObjMercenaryForm::seqDepartureStart);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
