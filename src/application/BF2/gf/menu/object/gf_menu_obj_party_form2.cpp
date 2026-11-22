#include "gf/menu/object/gf_menu_obj_party_form2.h"

#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_blade_data_adapter.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_field_skill_adapter.h"
#include "gf/menu/adapter/gf_menu_game_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/list/gf_menu_field_skill_list.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h" // IWYU pragma: keep
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: layout names of the positions of the three blades of the driver detail; original name unknown.
static const char *const unknown002[] = {"1st_blade_position", "2nd_blade_position", "3rd_blade_position"};

GfMenuObjPartyForm2::GfMenuObjPartyForm2(u32 handle)
    : GfMenuObject(handle), unknown38(false), unknown40(), unknown60(0xff), unknown64(0xff), unknown68(this), unknown2f8(0), unknown2fc(-1), unknown300(-1), unknown304(-1), unknown308(0),
      m_menuCallContext(nullptr), m_menuFieldSkillList(nullptr) {}

GfMenuObjPartyForm2::~GfMenuObjPartyForm2() {}

void GfMenuObjPartyForm2::update() {
  unknown68.unknown003();
  GfMenuObject::update();
}

void GfMenuObjPartyForm2::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(0xe), layerParam);
}

u32 GfMenuObjPartyForm2::getCursorID(u32 index) {
  u32 id = 0x61;
  if (index == 1) {
    id = 0x62;
  }
  if (index != 0) {
    return id;
  }
  return 0x61;
}

void GfMenuObjPartyForm2::finalize() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(m_menuFieldSkillList);
  mm::mtl::safeRelease(unknown320);
  mm::mtl::safeRelease(unknown40[0].unknown08);
  mm::mtl::safeRelease(unknown40[0].unknown00);
  mm::mtl::safeRelease(unknown40[1].unknown08);
  mm::mtl::safeRelease(unknown40[1].unknown00);
  GfMenuObject::finalize();
}

void GfMenuObjPartyForm2::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    // Each {} block below ends a lifetime: the game shares one stack slot (sp+0x78) between the layer parameter, the party setup, the list parameter and the name, and one (sp+0x50)
    // between the plate, the detail and the field skill object (ruling of 2026-11-13 #3).
    {
      GfMenuTypes::Param layerParam;
      if (getFSLayerParam(unknown20, layerParam)) {
        unknown2f8 = layerParam.get<OpenParam>().unknown00;
      }
    }
    {
      GfMenuDriverList::PartySetup setup;
      setup.unknown18 = false;
      setup.m_setupParam.unknown08 = 3;
      setup.unknown14 = GfPartySelect::LIST_TYPE_UNKNOWN_0;
      unknown28 = GfMenuDriverList::create();
      unknown28->setupFromParty(setup);
      if (unknown28->getSize() == 1) {
        unknown38 = true;
      }
      setup.m_setupParam.unknown08 = 2;
      setup.unknown14 = GfPartySelect::LIST_TYPE_UNKNOWN_1;
      unknown30 = GfMenuDriverList::create();
      unknown30->setupFromParty(setup);
    }
    {
      // The game stores the zero before the allocator (str xzr, [sp, #0x78] before the getAllocator call).
      ui::UISelectObjList::CreateParam createParam = {};
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown40[0].unknown00 = ui::UISelectObjList::create(createParam);
      unknown40[1].unknown00 = ui::UISelectObjList::create(createParam);
    }
    {
      ui::UIObjectAcc plate(main.unknown10, "LAY_plate");
      ui::UIObjectAcc current(main.unknown10, "LAY_current");
      ui::UIObjectAcc reserve(main.unknown10, "LAY_reserve");
      mm::mtl::FixStr<32> name;
      mm::Rect<s16> rect;
      for (u32 i = 0; i < 3; i++) {
        ui::UIObjectAcc driver(plate.duplicate(current.unknown10));
        name.format("driver%02d", i + 1);
        main.getLayoutRect(name.c_str(), rect);
        mm::Pnt<s16> pos;
        pos.x = rect.x;
        pos.y = rect.y;
        driver.setPos(pos);
        driver.setDisp(true);
        setupPlate(driver.unknown10, unknown28, i, true);
        if (unknown28->getContents(i).unknown00 != 0) {
          unknown40[0].unknown00->addObject(driver.unknown10);
          unknown40[1].unknown00->addObject(driver.unknown10);
        }
      }
      for (u32 i = 0; i < 2; i++) {
        ui::UIObjectAcc driver(plate.duplicate(reserve.unknown10));
        name.format("driver%02d", i + 4);
        main.getLayoutRect(name.c_str(), rect);
        mm::Pnt<s16> pos;
        pos.x = rect.x;
        pos.y = rect.y;
        driver.setPos(pos);
        driver.setDisp(true);
        setupPlate(driver.unknown10, unknown30, i, false);
        if (unknown30->getContents(i).unknown00 != 0) {
          unknown40[1].unknown00->addObject(driver.unknown10);
        }
      }
    }
// __LINE__ must be 217 as in the original file: it is the line argument of operator new.
#line 217
    MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
    if (mainListener != nullptr) {
      mainListener->release();
    }
// __LINE__ must be 218 as in the original file: it is the line argument of operator new.
#line 218
    DrSelListener *drSelListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DrSelListener(this);
    drSelListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_dr_sel"), drSelListener);
    if (drSelListener != nullptr) {
      drSelListener->release();
    }
// __LINE__ must be 219 as in the original file: it is the line argument of operator new.
#line 219
    DrDetailListener *drDetailListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DrDetailListener(this);
    drDetailListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_dr_detail"), drDetailListener);
    if (drDetailListener != nullptr) {
      drDetailListener->release();
    }
// __LINE__ must be 220 as in the original file: it is the line argument of operator new.
#line 220
    FieldSkillListener *fieldSkillListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) FieldSkillListener(this);
    fieldSkillListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_field_skill"), fieldSkillListener);
    if (fieldSkillListener != nullptr) {
      fieldSkillListener->release();
    }
    {
      ui::UICtrlCursorSelect::CursorSetting cursorSetting;
      cursorSetting.unknown18 = 5;
      mm::mtl::FixStr<32> name;
      name.format("IMG_cursor_%c", 0x61);
      unknown40[0].unknown08 = ui::UICtrlCursorSelect::create(main.searchChild(name.c_str()), cursorSetting, unknown40[0].unknown00);
      name.format("IMG_cursor_%c", 0x62);
      unknown40[1].unknown08 = ui::UICtrlCursorSelect::create(main.searchChild(name.c_str()), cursorSetting, unknown40[1].unknown00);
    }
    if (unknown30->getSize() >= 3) {
      int left = GfMenuObjUtil::getBtnIconNumber(0x10);
      ui::UIObjectAcc(main.unknown10, "IMG_btn_L").setImageIndex(GfMenuBdat::getIconImageIndex(left));
      int right = GfMenuObjUtil::getBtnIconNumber(0x20);
      ui::UIObjectAcc(main.unknown10, "IMG_btn_R").setImageIndex(GfMenuBdat::getIconImageIndex(right));
    } else {
      ui::UIObjectAcc(main.unknown10, "LAY_reserve_btn").setDisp(false);
    }
    {
      ui::UIObjectAcc detail(main.unknown10, "LAY_dr_detail");
      if (detail.isValid()) {
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("IMG_dr_detail_bustup"), 0x1c, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_dr_detail_name"), 2, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_dr_detail_lv_num"), 1, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("IMG_dr_detail_hp_bar"), 0, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_dr_detail_hp_num"), 0, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_dr_detail_hp_max"), 0, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_st_atk_damage_num"), 7, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_st_def_phys_num"), 4, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_st_def_ether_num"), 4, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_st_prob_critical_num"), 8, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_st_prob_guard_num"), 6, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_st_base_strength_num"), 0xd, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_st_base_ether_num"), 0xe, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_st_base_dex_num"), 0xf, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_st_base_agility_num"), 0x10, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("TXT_st_base_luck_num"), 0x11, 0, false);
        GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild("LAY_bl_win"), 0x1e, 0, false)->unknown80 = 0xffffffff;
        ui::UIObjectAcc bladeInfo(detail.unknown10, "LAY_blade_info");
        mm::mtl::FixStr<32> name;
        for (u32 i = 0; i < 3; i++) {
          ui::UIObjectAcc unit(bladeInfo.duplicateChild("LAY_blade_info_unit"));
          GfMenuCharDataAdapter::createFromReferenceBlade(unit.searchChild("IMG_blade_info_face"), 3, i, false);
          GfMenuCharDataAdapter::createFromReferenceBlade(unit.searchChild("IMG_blade_wepon_base"), 0x29, i, false);
          name.format("TXT_blade_set_name%02d", i + 1);
          GfMenuCharDataAdapter::createFromReferenceBlade(detail.searchChild(name.c_str()), 2, i, false);
          // The game formats the name twice in a row, the first result is never used (0x71004a8ce4, then 0x71004a8d14); without the first call the function has 975 instructions against 979.
          name.format("LAY_blade_set%02d", i + 1);
          GfMenuCharDataAdapter::createFromReferenceDriver(unit.searchChild("TXT_blade_role"), 0x1e, 0, false)->unknown80 = i;
          name.format("LAY_blade_set%02d", i + 1);
          GfMenuCharDataAdapter::createFromReferenceDriver(detail.searchChild(name.c_str()), 0x1e, 0, false)->unknown80 = i;
          detail.setLayout(unit.unknown10, unknown002[i]);
          unit.setDisp(true);
        }
        for (u32 i = 0; i < 3; i++) {
          name.format("IMG_arts_icon%02d", i + 1);
          GfMenuBladeDataAdapter::createFromReference(detail.searchChild(name.c_str()), 1, 0, 0, false)->unknown68 = i;
        }
      }
    }
    {
      ui::UIObjectAcc fieldSkill(main.unknown10, "LAY_field_skill");
      if (fieldSkill.isValid()) {
        {
          ui::UIListInfoBase::SetupParam listParam;
          m_menuFieldSkillList = GfMenuFieldSkillList::create();
          if (m_menuFieldSkillList != nullptr) {
            listParam.unknown08 = 0xf;
            m_menuFieldSkillList->setup(getAllocator(ALLOCATOR_UNKNOWN_0), listParam);
            m_menuFieldSkillList->addFieldSkillFromParty();
          }
        }
        mm::mtl::FixStr<32> name;
        ui::UISelectObjList::CreateParam createParam;
        createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
        unknown320 = ui::UISelectObjList::create(createParam);
        if (unknown320 != nullptr) {
          unknown320->pickupObject(fieldSkill.unknown10, "LAY_fs_item@%02d", 1);
        }
        for (u32 i = 0; i < unknown320->getSize(); i++) {
          ui::UIObjectAcc item(unknown320->getObject(i));
          if (item.isValid()) {
            name.format("TXT_fs_item_name@%02d", i + 1);
            // The game reads the handle of the item after createFromList (ldur w8 before str [x0, #0x24]), not before it as the one-line assignment does.
            GfMenuFieldSkillAdapter *adapter = GfMenuFieldSkillAdapter::createFromList(item.searchChild(name.c_str()), 0, m_menuFieldSkillList, i);
            adapter->unknown24 = item.unknown10;
            name.format("TXT_fs_item_lv_num@%02d", i + 1);
            GfMenuFieldSkillAdapter::createFromList(item.searchChild(name.c_str()), 1, m_menuFieldSkillList, i);
          }
        }
        if (m_menuFieldSkillList->getSize() > m_menuFieldSkillList->getPageSize()) {
          u32 pages = m_menuFieldSkillList->getSize() / m_menuFieldSkillList->getPageSize();
          if (m_menuFieldSkillList->getSize() % m_menuFieldSkillList->getPageSize() != 0) {
            pages++;
          }
          GfMenuReference::setReferenceNumber(0, 1);
          GfMenuGameAdapter::create(fieldSkill.searchChild("TXT_fs_page_num"), 9, true)->unknown50 = 0;
          GfMenuReference::setReferenceNumber(1, pages);
          GfMenuGameAdapter::create(fieldSkill.searchChild("TXT_fs_page_max"), 9, true)->unknown50 = 1;
          setupInputSelection(fieldSkill.unknown10, 0, pages);
        } else {
          fieldSkill.setDispChild(false, "LAY_fs_page_info");
        }
      }
    }
    GfMenuObject::initialize();
  }
}

void GfMenuObjPartyForm2::setupPlate(u32 plate, GfMenuDriverList *list, u32 index, bool isNumber) {
  ui::UIObjectAcc acc(plate);
  if (acc.isValid()) {
    int driver = GfMenuObjUtil::convMenuDriverID(list->getContents(index).unknown00);
    ui::UIObjectAcc(acc.unknown10, "LAY_plate_dr_info").setDisp(driver != 0);
    if (driver == 0) {
      ui::UIObjectAcc(acc.unknown10, "IMG_bustup").setDisp(false);
    } else {
      ui::UIObjectAcc(acc.unknown10, "IMG_bustup").setImageIndex(driver - 1);
    }
    if (isNumber) {
      ui::UIObjectAcc(acc.unknown10, "IMG_number").setImageIndex(index);
    } else {
      ui::UIObjectAcc(acc.unknown10, "LAY_order").setDisp(false);
    }
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild("TXT_dr_name"), 2, list, index, false);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild("IMG_bl_icon"), 0x1b, list, index, false);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild("TXT_lv_num"), 1, list, index, false);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild("TXT_hp_num"), 0, list, index, false);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild("TXT_hp_max"), 0, list, index, false);
    if (unknown38) {
      acc.setMulColor("gray");
    }
    if (index == 0) {
      ui::UIObjectAcc(acc.unknown10, "IMG_lock").setDisp(true);
    } else {
      ui::UIObjectAcc(acc.unknown10, "IMG_lock").setDisp(false);
    }
  }
}

bool GfMenuObjPartyForm2::seqStartOpen() {
  unknown2fc = -1;
  ui::UIObjectAcc(unknown18, "LAY_current").setDisp(false);
  ui::UIObjectAcc(unknown18, "LAY_reserve").setDisp(false);
  ui::UIObjectAcc drSel(unknown18, "LAY_dr_sel");
  disableInput(drSel.unknown10);
  disableFSSwitching();
  return true;
}

bool GfMenuObjPartyForm2::seqAppearTitle() {
  if (unknown2fc == -1) {
    ui::UIObjectAcc title(unknown18, "LAY_title");
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 1;
    param.unknown04 = 0;
    unknown2fc = GfMenuObjUtil::startPresetCtrl(title.unknown10, param);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2fc)) {
    return false;
  }
  unknown2fc = -1;
  return true;
}

bool GfMenuObjPartyForm2::seqAppearFrame() {
  if (unknown2fc == -1) {
    ui::UIObjectAcc frame(unknown18, "LAY_frame");
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 3;
    param.unknown04 = 0;
    unknown2fc = GfMenuObjUtil::startPresetCtrl(frame.unknown10, param);
    ui::UIObjectAcc(unknown18, "LAY_dr_sel").setDisp(true);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2fc)) {
    return false;
  }
  unknown2fc = -1;
  return true;
}

bool GfMenuObjPartyForm2::seqAppearPlate() {
  if (unknown2fc == -1) {
    {
      ui::UIObjectAcc current(unknown18, "LAY_current");
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown10 = 0;
      param.unknown00 = 1;
      param.unknown04 = 0;
      unknown2fc = GfMenuObjUtil::startPresetCtrl(current.unknown10, param);
    }
    {
      ui::UIObjectAcc reserve(unknown18, "LAY_reserve");
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown10 = 0;
      param.unknown00 = 0;
      param.unknown04 = 0;
      GfMenuObjUtil::startPresetCtrl(reserve.unknown10, param);
    }
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2fc)) {
    return false;
  }
  unknown2fc = -1;
  return true;
}

bool GfMenuObjPartyForm2::seqAnnounceChange() {
  if (m_menuCallContext != nullptr) {
    return m_menuCallContext->isTerm();
  }
  m_menuCallContext = GfMenuCallContext::create();
  GfMenuObjCommonText::open(m_menuCallContext, 0xd, 0);
  return false;
}

bool GfMenuObjPartyForm2::seqWaitOpenEnd() {
  changeCursorMode(0);
  {
    ui::UIObjectAcc drSel(unknown18, "LAY_dr_sel");
    enableInput(drSel.unknown10);
    GfMenuObjOperationInfo::open(drSel.unknown10, 0, 0, 0);
  }
  enableFSSwitching();
  return true;
}

void GfMenuObjPartyForm2::swapDriver(u32 index, u32 other) {
  if (index < unknown28->getSize()) {
    if (other < unknown28->getSize()) {
      unknown28->swapContents(index, other);
    } else {
      unknown28->swapContents(index, unknown30, other - unknown28->getSize());
    }
  }
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  if (acc.isValid()) {
    ui::UISelectObjList *list = unknown40[1].unknown00;
    {
      ui::UIObjectAcc first(list->getObject(index), "IMG_bustup");
      ui::UIObjectAcc second(list->getObject(other), "IMG_bustup");
      u32 firstImage = first.getImageIndex();
      u32 secondImage = second.getImageIndex();
      first.setImageIndex(secondImage);
      second.setImageIndex(firstImage);
    }
    {
      ui::UIObjectAcc first(list->getObject(index), "IMG_lock");
      ui::UIObjectAcc second(list->getObject(other), "IMG_lock");
      bool firstDisp = first.isDisp();
      bool secondDisp = second.isDisp();
      first.setDisp(secondDisp);
      second.setDisp(firstDisp);
    }
  }
}

bool GfMenuObjPartyForm2::seqStartSwap() {
  ui::UIObjectAcc drSel(unknown18, "LAY_dr_sel");
  disableInput(drSel.unknown10);
  disableFSSwitching();
  GfMenuObjOperationInfo::setDisp(false);
  {
    mm::mtl::FixStr<32> name;
    name.format("LAY_cursor_%c", 0x61);
    drSel.setDispChild(false, name.c_str());
    name.format("LAY_cursor_%c", 0x62);
    drSel.setDispChild(false, name.c_str());
  }
  drSel.setDispChild(false, "IMG_head_cursor");
  ui::UIObjectAcc plate(unknown40[unknown64].unknown00->getSelectObject());
  unknown300 = -1;
  unknown304 = -1;
  unknown308 = plate.getDispPriority();
  return true;
}

bool GfMenuObjPartyForm2::seqTakePlate() {
  if (unknown300 == -1 && unknown304 == -1) {
    ui::UIObjectAcc taken(unknown40[unknown64].unknown00->getSelectObject());
    ui::UIObjectAcc target(unknown40[unknown60].unknown00->getSelectObject());
    taken.setDispPriority(unknown308 + 1);
    target.setDispPriority(unknown308 + 2);
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x80000;
    param.unknown00 = 0.25f;
    param.unknown2c = 1.1f;
    param.unknown0c = 1;
    param.unknown14 = 4;
    unknown300 = GfMenuObjUtil::startCtrl(taken.unknown10, param, nullptr);
    unknown304 = GfMenuObjUtil::startCtrl(target.unknown10, param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown300)) {
    return false;
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown304)) {
    return false;
  }
  unknown300 = -1;
  unknown304 = -1;
  return true;
}

bool GfMenuObjPartyForm2::seqMovePlate() {
  if (unknown300 == -1 && unknown304 == -1) {
    ui::UIObjectAcc taken(unknown40[unknown64].unknown00->getSelectObject());
    ui::UIObjectAcc target(unknown40[unknown60].unknown00->getSelectObject());
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x80;
    param.unknown00 = 0.5f;
    param.unknown0c = 1;
    param.unknown14 = 4;
    mm::Pnt<s16> pos;
    target.getPos(pos);
    param.unknown26 = pos;
    param.unknown18 = unknown300;
    unknown300 = GfMenuObjUtil::startCtrl(taken.unknown10, param, nullptr);
    taken.getPos(pos);
    param.unknown26 = pos;
    param.unknown18 = unknown304;
    unknown304 = GfMenuObjUtil::startCtrl(target.unknown10, param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown300)) {
    return false;
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown304)) {
    return false;
  }
  unknown300 = -1;
  unknown304 = -1;
  return true;
}

bool GfMenuObjPartyForm2::seqPutPlate() {
  if (unknown300 == -1 && unknown304 == -1) {
    ui::UIObjectAcc taken(unknown40[unknown64].unknown00->getSelectObject());
    ui::UIObjectAcc target(unknown40[unknown60].unknown00->getSelectObject());
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x80000;
    param.unknown00 = 0.25f;
    param.unknown2c = 1.0f;
    param.unknown0c = 1;
    param.unknown14 = 4;
    param.unknown18 = unknown300;
    unknown300 = GfMenuObjUtil::startCtrl(taken.unknown10, param, nullptr);
    param.unknown18 = unknown304;
    unknown304 = GfMenuObjUtil::startCtrl(target.unknown10, param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown300)) {
    return false;
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown304)) {
    return false;
  }
  GfMenuObjUtil::setCtrlDefault(unknown300);
  GfMenuObjUtil::releaseCtrl(unknown300);
  GfMenuObjUtil::setCtrlDefault(unknown304);
  GfMenuObjUtil::releaseCtrl(unknown304);
  ui::UIObjectAcc taken(unknown40[unknown64].unknown00->getSelectObject());
  ui::UIObjectAcc target(unknown40[unknown60].unknown00->getSelectObject());
  taken.setDispPriority(unknown308);
  target.setDispPriority(unknown308);
  swapDriver(unknown40[unknown64].unknown00->getIndex(false), unknown40[unknown60].unknown00->getIndex(false));
  return true;
}

bool GfMenuObjPartyForm2::seqWaitSwapEnd() {
  changeCursorMode(0);
  ui::UIObjectAcc drSel(unknown18, "LAY_dr_sel");
  enableInput(drSel.unknown10);
  enableFSSwitching();
  GfMenuObjOperationInfo::setDisp(true);
  return true;
}

void GfMenuObjPartyForm2::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    m_menuObjPartyForm2->unknown68.unknown002(&GfMenuObjPartyForm2::seqStartOpen);
    m_menuObjPartyForm2->unknown68.unknown002(&GfMenuObjPartyForm2::seqAppearTitle);
    m_menuObjPartyForm2->unknown68.unknown002(&GfMenuObjPartyForm2::seqAppearFrame);
    m_menuObjPartyForm2->unknown68.unknown002(&GfMenuObjPartyForm2::seqAppearPlate);
    if (m_menuObjPartyForm2->unknown2f8 == 1) {
      m_menuObjPartyForm2->unknown68.unknown002(&GfMenuObjPartyForm2::seqAnnounceChange);
    }
    m_menuObjPartyForm2->unknown68.unknown002(&GfMenuObjPartyForm2::seqWaitOpenEnd);
    break;
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    // Ruling 2026-11-13 #4, 0x71004a9944: the game stores unknown08 (2) before unknown00 (0.5f), the order of the other `startCtrl` callers on main; with unknown00 first the `orr`/`str` order
    // differs.
    param.unknown08 = 2;
    param.unknown00 = 0.5f;
    param.unknown14 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case 0x40: {
    u32 driver = event.unknown08;
    GfMenuReference::setReferenceDriverID(0, driver);
    GfMenuReference::setReferenceBladeIDFromDriver(driver);
    GfMenuObject::disableInput(acc.searchChild("LAY_dr_sel"));
    ui::EventData request;
    request.unknown00 = 0x21;
    GfMenuObject::sendEvent(acc.searchChild("LAY_dr_detail"), request, 0.0f);
    break;
  }
  case 0x41:
  case 0x43:
    GfMenuObject::enableInput(acc.searchChild("LAY_dr_sel"));
    break;
  case 0x42: {
    GfMenuObject::disableInput(acc.searchChild("LAY_dr_sel"));
    ui::EventData request;
    request.unknown00 = 0x21;
    GfMenuObject::sendEvent(acc.searchChild("LAY_field_skill"), request, 0.0f);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjPartyForm2::DrDetailListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 8:
    if (event.unknown0c != 9) {
      break;
    }
    {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x400002;
      param.unknown0c = 1;
      param.unknown00 = 0.5f;
      param.unknown04 = 2;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    // fall through
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x200001;
    param.unknown0c = 1;
    param.unknown00 = 0.5f;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    } else if (event.unknown08 == 2) {
      ui::UIObjectAcc parent(acc.getParentHandle());
      ui::EventData request;
      request.unknown00 = 0x41;
      GfMenuObject::sendEvent(parent.unknown10, request, 0.0f);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjPartyForm2::FieldSkillListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 8:
    if (event.unknown0c != 9) {
      break;
    }
    {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x400002;
      param.unknown0c = 1;
      param.unknown00 = 0.5f;
      param.unknown04 = 2;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    // fall through
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x200001;
    param.unknown0c = 1;
    param.unknown00 = 0.5f;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    } else if (event.unknown08 == 2) {
      ui::UIObjectAcc parent(acc.getParentHandle());
      ui::EventData request;
      request.unknown00 = 0x41;
      GfMenuObject::sendEvent(parent.unknown10, request, 0.0f);
    }
    break;
  case 6: {
    int page = event.unknown08;
    ui::UIListInfoBase *list = m_menuObjPartyForm2->m_menuFieldSkillList;
    list->setIndex(list->getPageSize() * page);
    GfMenuReference::setReferenceNumber(0, page + 1);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjPartyForm2::DrSelListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case 2:
    if (m_menuObjPartyForm2->unknown28 != nullptr && m_menuObjPartyForm2->unknown30 != nullptr) {
      mm::mtl::FixedVector<u16, 16> drivers;
      for (u32 i = 0; i < m_menuObjPartyForm2->unknown28->getSize(); i++) {
        drivers.push_back(m_menuObjPartyForm2->unknown28->getContents(i).unknown00);
      }
      for (u32 i = 0; i < m_menuObjPartyForm2->unknown30->getSize(); i++) {
        drivers.push_back(m_menuObjPartyForm2->unknown30->getContents(i).unknown00);
      }
      GfMenuObjUtil::setupPartyDriver(drivers);
      GfMenuObjOperationInfo::close();
      acc.setTerm();
    }
    break;
  case 6:
    if (m_menuObjPartyForm2->unknown60 != 0xff) {
      // The game loads the page before the ring list (ldr w1 before ldr x0 of setIndex).
      u32 index = event.unknown08;
      m_menuObjPartyForm2->unknown40[m_menuObjPartyForm2->unknown60].unknown00->setIndex(index);
      u32 object = m_menuObjPartyForm2->unknown40[m_menuObjPartyForm2->unknown60].unknown00->getSelectObject();
      GfMenuObjUtil::setDockPos(acc.searchChild("IMG_head_cursor"), object, 3, true);
    }
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 8: {
    // The game keeps the button in a register across the calls of the arms and passes it to playSECommonFromInput.
    u32 input = event.unknown0c;
    switch (input) {
    case 1:
      if (m_menuObjPartyForm2->unknown38) {
        GfMenuObjUtil::playSECommon(2);
        return;
      }
      if (m_menuObjPartyForm2->unknown60 == 0) {
        m_menuObjPartyForm2->changeCursorMode(1);
      } else if (m_menuObjPartyForm2->unknown60 == 1) {
        if (m_menuObjPartyForm2->unknown40[m_menuObjPartyForm2->unknown64].unknown00->getIndex(false) == m_menuObjPartyForm2->unknown40[m_menuObjPartyForm2->unknown60].unknown00->getIndex(false)) {
          GfMenuObjUtil::playSECommon(2);
          return;
        }
        m_menuObjPartyForm2->unknown68.unknown002(&GfMenuObjPartyForm2::seqStartSwap);
        m_menuObjPartyForm2->unknown68.unknown002(&GfMenuObjPartyForm2::seqTakePlate);
        m_menuObjPartyForm2->unknown68.unknown002(&GfMenuObjPartyForm2::seqMovePlate);
        m_menuObjPartyForm2->unknown68.unknown002(&GfMenuObjPartyForm2::seqPutPlate);
        m_menuObjPartyForm2->unknown68.unknown002(&GfMenuObjPartyForm2::seqWaitSwapEnd);
      }
      break;
    case 2:
      if (m_menuObjPartyForm2->unknown60 == 0) {
        if (m_menuObjPartyForm2->unknown2f8 == 0) {
          GfMenuObject::returnFSSubLayer(acc.unknown10, 1);
        } else {
          GfMenuObject::closeFSLayer(acc.unknown10, true, true);
        }
      } else if (m_menuObjPartyForm2->unknown64 != 0xff) {
        m_menuObjPartyForm2->changeCursorMode(m_menuObjPartyForm2->unknown64);
      }
      break;
    case 9:
      if (m_menuObjPartyForm2->unknown30->getSize() > 2) {
        if (m_menuObjPartyForm2->unknown30->getIndex(false) < 2) {
          m_menuObjPartyForm2->unknown30->setIndex(2);
        } else if (m_menuObjPartyForm2->unknown30->getIndex(false) + 1 < m_menuObjPartyForm2->unknown30->getSize()) {
          m_menuObjPartyForm2->unknown30->setIndex(m_menuObjPartyForm2->unknown30->getIndex(false) + 1);
        }
      }
      break;
    case 10:
      if (m_menuObjPartyForm2->unknown30->getSize() > 2 && m_menuObjPartyForm2->unknown30->getIndex(false) > 1) {
        m_menuObjPartyForm2->unknown30->setIndex(m_menuObjPartyForm2->unknown30->getIndex(false) - 1);
      }
      break;
    case 0xb: {
      ui::UIObjectAcc parent(acc.getParentHandle());
      ui::EventData request;
      int index = m_menuObjPartyForm2->unknown40[m_menuObjPartyForm2->unknown60].unknown00->getIndex(false);
      int size = m_menuObjPartyForm2->unknown28->getSize();
      // The game reloads the current list after the getSize call and shares it between the two arms.
      GfMenuDriverList *current = m_menuObjPartyForm2->unknown28;
      u32 driver;
      if (index < size) {
        driver = current->getContents(index).unknown00;
      } else {
        // The game calls getSize on the current list before it loads the reserve list.
        u32 rest = index - current->getSize();
        driver = m_menuObjPartyForm2->unknown30->getContents(rest).unknown00;
      }
      request.unknown00 = 0x40;
      request.unknown08 = driver;
      GfMenuObject::sendEvent(parent.unknown10, request, 0.0f);
      break;
    }
    case 0xc: {
      ui::UIObjectAcc parent(acc.getParentHandle());
      ui::EventData request;
      request.unknown00 = 0x42;
      GfMenuObject::sendEvent(parent.unknown10, request, 0.0f);
      break;
    }
    }
    GfMenuObjUtil::playSECommonFromInput(input);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjPartyForm2>(const mm::mtl::Delegate<bool()> *);
