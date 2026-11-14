#include "gf/menu/object/gf_menu_obj_en_book.h"

#include "bdat.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_en_book.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_model_view.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_msg_list.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

GfMenuObjEnBook::GfMenuObjEnBook(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(0), unknown2c(0), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr),
      unknown60(nullptr), unknown68(nullptr), unknown70(nullptr), unknown78(nullptr), unknown80(nullptr), unknown88(0), unknown90(this), unknown320(false) {
  unknown40 = GfMenuMsgList::create();
  unknown50 = GfMenuMsgList::create();
  unknown60 = GfMenuIDList::create();
  unknown68 = GfMenuIDList::create();
}

GfMenuObjEnBook::~GfMenuObjEnBook() {
  mm::mtl::safeRelease(unknown78);
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(unknown60);
  mm::mtl::safeRelease(unknown58);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown30);
}

void GfMenuObjEnBook::finalize() {
  if (unknown80 != nullptr) {
    delete unknown80;
    unknown80 = nullptr;
  }
  GfMenuObject::finalize();
}

void GfMenuObjEnBook::update() {
  unknown90.unknown003();
  if (unknown80 != nullptr) {
    unknown80->update();
  }
  GfMenuObject::update();
}

void GfMenuObjEnBook::setupMapIDList() {}

void GfMenuObjEnBook::setupEnBookIDList() {
  unknown68->clear();
  switch (unknown24) {
  case 0: {
    u8 *bdat = GfDataBdat::getFP(BDAT_BTL_EN_BOOK);
    u32 top = Bdat::getIdTop(bdat);
    for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
      MenuID id = {top + i};
      Bdat::uVal enemy = Bdat::getVal(bdat, "BaseEnemyID", id.unknown00);
      if (enemy.valueU16 && GfDataEnemy::getRscIdByArrangeId(enemy.valueU16) != 0) {
        unknown68->addContents(id);
      }
    }
    break;
  }
  case 1: {
    GfBdatRsc *bdatRsc = GfBdatRsc::get();
    u8 *bdat = GfDataBdat::getFP(BDAT_BTL_EN_BOOK);
    u32 top = Bdat::getIdTop(bdat);
    for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
      MenuID id = {top + i};
      Bdat::uVal enemy = Bdat::getVal(bdat, "BaseEnemyID", id.unknown00);
      if (enemy.valueU16) {
        u32 rsc = GfDataEnemy::getRscIdByArrangeId(enemy.valueU16);
        if (rsc != 0 && bdatRsc->getRscEnTypeFamily(rsc) == unknown28) {
          u32 genus = bdatRsc->getRscEnTypeGenus(rsc);
          if (bdatRsc->getRscEnGenusNAME(genus) == unknown2c) {
            unknown68->addContents(id);
          }
        }
      }
    }
    break;
  }
  }
}

void GfMenuObjEnBook::refreshEnBookList() {
  ui::UIStr text;
  mm::mtl::FixStr<32> name;
  u32 index = unknown68->getIndex(true);
  GfDataBdat::getFP(BDAT_BTL_EN_BOOK);
  for (u32 i = 0; i < unknown70->getSize(); i++) {
    ui::UIObjectAcc item(unknown70->getObject(i));
    if (i < unknown68->getSize()) {
      u32 id = unknown68->getContents(i).unknown00;
      bool isMasked = !isBattled(id);
      item.setDisp(true);
      name.format("TXT_en_list_item_name@%02d", i + 1);
      {
        ui::UIObjectAcc label(item.unknown10, name.c_str());
        if (i == index) {
          GfMenuObjUtil::setColMulandAdd(label.unknown10, "txt_highlight");
        } else {
          label.loadDefColor();
        }
      }
      name.format("LAY_en_list_item_name@%02d", i + 1);
      item.setDispChild(!isMasked, name.c_str());
      name.format("TXT_en_list_item_mask@%02d", i + 1);
      item.setDispChild(isMasked, name.c_str());
      name.format("IMG_en_list_item_icon@%02d", i + 1);
      ui::UIObjectAcc icon(item.unknown10, name.c_str());
      icon.setImageIndex(isDefeated(id));
    } else {
      item.setDisp(false);
    }
  }
}

bool GfMenuObjEnBook::isBattled(u32 id) {
  u8 *bdat = GfDataBdat::getFP(BDAT_BTL_EN_BOOK);
  if (bdat != nullptr) {
    return GfDataEnBook::isAttackFlag(Bdat::getVal(bdat, "BaseEnemyID", id).valueU16);
  }
  return false;
}

bool GfMenuObjEnBook::isDefeated(u32 id) {
  u8 *bdat = GfDataBdat::getFP(BDAT_BTL_EN_BOOK);
  if (bdat != nullptr) {
    return GfDataEnBook::getDefeatNum(Bdat::getVal(bdat, "BaseEnemyID", id).valueU16) != 0;
  }
  return false;
}

void GfMenuObjEnBook::deleteCurEnemyModel() {
  if (unknown88 != 0) {
    unknown80->delGfObj(OBJECT_TYPE_ENEMY, unknown88);
    unknown88 = 0;
  }
}

bool GfMenuObjEnBook::seqWaitLoading() { return !unknown80->isLoading(); }

bool GfMenuObjEnBook::seqStartTop() {
  ui::UIObjectAcc acc(unknown18, "LAY_top");
  sendOpenEvent(acc.unknown10, 0, 0.0f);
  return true;
}

void GfMenuObjEnBook::setupFamilyMsgList() {
  ui::UIObjectAcc acc(unknown18, "LAY_type_sel_cate");
  u8 *bdat = unknown40->unknown68;
  {
    u32 count = acc.countChild("LAY_type_sel_cate_item@%02d", 1);
    ui::UIListInfoBase::SetupParam param;
    param.unknown08 = count;
    param.unknown10 = true;
    unknown40->setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
    unknown40->clear();
  }
  for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
    MsgID id = {};
    id.unknown00 = Bdat::getIdTop(bdat) + i;
    unknown40->addContents(id);
  }
}

void GfMenuObjEnBook::refreshFamilyList() {
  ui::UIStr text;
  mm::mtl::FixStr<32> name;
  u32 index = unknown40->getIndex(true);
  for (u32 i = 0; i < unknown48->getSize(); i++) {
    ui::UIObjectAcc item(unknown48->getObject(i));
    if (i < unknown40->getSize()) {
      item.setDisp(true);
      unknown40->getMsg(i, text, true);
      name.format("TXT_type_sel_cate_item@%02d", i + 1);
      ui::UIObjectAcc label(item.unknown10, name.c_str());
      label.setText(text);
      if (i == index) {
        GfMenuObjUtil::setColMulandAdd(label.unknown10, "txt_highlight");
      } else {
        label.loadDefColor();
      }
    } else {
      item.setDisp(false);
    }
  }
}

void GfMenuObjEnBook::setupGenusMsgList() {
  u8 *bdat = GfDataBdat::getFP(BDAT_BTL_EN_BOOK);
  if (bdat == nullptr) {
    return;
  }
  u32 top = Bdat::getIdTop(bdat);
  {
    ui::UIListInfoBase::SetupParam param;
    param.unknown08 = unknown58->getSize();
    param.unknown10 = true;
    unknown50->setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
    unknown50->clear();
  }
  GfBdatRsc *bdatRsc = GfBdatRsc::get();
  for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
    Bdat::uVal enemy = Bdat::getVal(bdat, "BaseEnemyID", top + i);
    if (enemy.valueU16) {
      u32 rsc = GfDataEnemy::getRscIdByArrangeId(enemy.valueU16);
      if (bdatRsc->getRscEnTypeFamily(rsc) == unknown28) {
        u32 genus = bdatRsc->getRscEnTypeGenus(rsc);
        MsgID id = {};
        id.unknown00 = bdatRsc->getRscEnGenusNAME(genus);
        bool found = false;
        for (u32 j = 0; j < unknown50->getSize(); j++) {
          if (unknown50->getContents(j).unknown00 == id.unknown00) {
            found = true;
            break;
          }
        }
        if (!found) {
          unknown50->addContents(id);
        }
      }
    }
  }
}

void GfMenuObjEnBook::refreshGenusMsgList() {
  ui::UIStr text;
  mm::mtl::FixStr<32> name;
  u32 index = unknown50->getIndex(true);
  for (u32 i = 0; i < unknown58->getSize(); i++) {
    ui::UIObjectAcc item(unknown58->getObject(i));
    if (i < unknown50->getSize()) {
      item.setDisp(true);
      unknown50->getMsg(i, text, true);
      name.format("TXT_type_sel_fam_item@%02d", i + 1);
      ui::UIObjectAcc label(item.unknown10, name.c_str());
      label.setText(text);
      if (i == index) {
        GfMenuObjUtil::setColMulandAdd(label.unknown10, "txt_highlight");
      } else {
        label.loadDefColor();
      }
    } else {
      item.setDisp(false);
    }
  }
}

bool GfMenuObjEnBook::seqDeleteEnmey() {
  if (unknown68->getSize() != 0) {
    u32 book = unknown68->getContents(unknown68->getIndex(false)).unknown00;
    u32 enemy = GfBdatChrEnArrange::get()->getBTL_EnBookBaseEnemyID(book);
    if (unknown88 == enemy) {
      return true;
    }
  }
  deleteCurEnemyModel();
  return !unknown80->isLoading();
}

bool GfMenuObjEnBook::seqCreateEnmey() {
  if (!unknown320) {
    u32 book = unknown68->getContents(unknown68->getIndex(false)).unknown00;
    u32 enemy = GfBdatChrEnArrange::get()->getBTL_EnBookBaseEnemyID(book);
    if (unknown88 == enemy) {
      return true;
    }
    fw::Transform transform;
    transform.unknown00 = mm::Vec3::zero;
    transform.unknown10 = mm::Quat::identity;
    transform.unknown00.x = 1.5f;
    unknown80->addEnemyObject(enemy, transform);
    unknown88 = enemy;
    unknown320 = true;
  } else if (!unknown80->isLoading()) {
    unknown320 = false;
    return true;
  }
  return false;
}

bool GfMenuObjEnBook::seqFadeOutEnmey() {
  if (!unknown320) {
    if (unknown88 == 0) {
      return true;
    }
    GfMenuModelView::CtrlParam param(unknown80->findGfObj(OBJECT_TYPE_ENEMY, unknown88), 0.25f, false);
    param.setMoveAlpha(0.0f);
    unknown80->startObjectCtrl(param);
    unknown320 = true;
  }
  if (!unknown80->isObjectCtrlBusy(unknown80->findGfObj(OBJECT_TYPE_ENEMY, unknown88))) {
    unknown320 = false;
    return true;
  }
  return false;
}

void GfMenuObjEnBook::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
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

void GfMenuObjEnBook::TopListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjOperationInfo::setGuideText(0x3a, 0);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(0);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
      GfMenuObject::setupInputSelectionFromList(acc.unknown10, *unknown20->unknown30);
    }
    break;
  case 6: {
    u32 index = event.unknown08;
    if (index != -1) {
      mm::mtl::FixStr<32> name;
      if (event.unknown0c != -1) {
        name.format("IMG_top_item_base@%02d", event.unknown0c + 1);
        ui::UIObjectAcc(acc.unknown10, name.c_str()).startAnimation("idol", false);
      }
      unknown20->unknown30->setIndex(index);
      name.format("IMG_top_item_base@%02d", index + 1);
      ui::UIObjectAcc(acc.unknown10, name.c_str()).startAnimation("sellect", false);
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      u32 index = event.unknown08;
      unknown20->unknown24 = index;
      switch (index) {
      case 0:
        GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(4), 0, 0.0f);
        break;
      case 1:
        GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(1), 0, 0.0f);
        break;
      case 2:
        GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(3), 0, 0.0f);
        break;
      default:
        return;
      }
      GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
      GfMenuObject::disableFSInput();
    } else if (event.unknown0c == 2) {
      GfMenuObject::returnFSSubLayer(unknown20);
    } else {
      break;
    }
    GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown00 = 6;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEnBook::IndexListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 0;
    param.unknown00 = 6;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown00 = 6;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEnBook::FamilySelListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(1);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
      GfMenuObject::setupInputSelectionFromList(acc.unknown10, *unknown20->unknown40);
    }
    break;
  case 6:
    if (event.unknown08 != -1) {
      unknown20->unknown40->setIndex(event.unknown08);
      unknown20->refreshFamilyList();
    }
    break;
  case 8:
    if (event.unknown0c == 1) {
      unknown20->unknown28 = unknown20->unknown40->getContents(unknown20->unknown40->getIndex(false)).unknown00 - 1;
      GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(2), 0, 0.0f);
    } else if (event.unknown0c == 2) {
      GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(0), 0, 0.0f);
      GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
      GfMenuObject::disableFSInput();
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    }
    break;
  case GfMenuTypes::unknown003_33: {
    int type = event.unknown08;
    if (type != 2) {
      u32 open = 0;
      if (type != 4) {
        unknown20->unknown40->setIndex(0);
        unknown20->refreshFamilyList();
        open = 1;
      }
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown00 = 6;
      param.unknown04 = 0;
      param.unknown10 = open;
      GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    } else {
      GfMenuObject::enableFSInput(1);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    }
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown00 = 6;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEnBook::GenusSelListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(2);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
      GfMenuObject::setupInputSelectionFromList(acc.unknown10, *unknown20->unknown50);
    }
    break;
  case 6:
    if (event.unknown08 != -1) {
      unknown20->unknown50->setIndex(event.unknown08);
      unknown20->refreshGenusMsgList();
    }
    break;
  case 8:
    if (event.unknown0c == 1) {
      unknown20->unknown2c = unknown20->unknown50->getContents(unknown20->unknown50->getIndex(false)).unknown00;
      GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(4), 2, 0.0f);
      GfMenuObject::sendCloseEvent(GfMenuObject::getFSInputObject(1), 0, 0.0f);
    } else if (event.unknown0c == 2) {
      GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(1), 2, 0.0f);
    } else {
      break;
    }
    GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
    GfMenuObject::disableFSInput();
    GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    break;
  case GfMenuTypes::unknown003_33: {
    int type = event.unknown08;
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    if (type != 4) {
      unknown20->setupGenusMsgList();
      unknown20->refreshGenusMsgList();
    }
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown00 = 6;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEnBook::LocationSelListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
  case 8:
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 0;
    param.unknown00 = 6;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown00 = 6;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEnBook::EnListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(4);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
      GfMenuObject::setupInputSelectionFromList(acc.unknown10, *unknown20->unknown68);
    }
    break;
  case 6:
    if (event.unknown08 != 0xffffffff) {
      unknown20->unknown68->setIndex(event.unknown08);
      unknown20->refreshEnBookList();
      u32 id = unknown20->unknown68->getContents(unknown20->unknown68->getIndex(false)).unknown00;
      unknown20->unknown90.unknown005();
      unknown20->unknown90.unknown002(&GfMenuObjEnBook::seqDeleteEnmey);
      if (unknown20->isBattled(id)) {
        unknown20->unknown90.unknown004(10);
        unknown20->unknown90.unknown002(&GfMenuObjEnBook::seqCreateEnmey);
      }
    }
    break;
  case 8:
    if (event.unknown0c == 1) {
      if (!unknown20->isBattled(unknown20->unknown68->getContents(unknown20->unknown68->getIndex(false)).unknown00)) {
        break;
      }
      GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(5), 0, 0.0f);
    } else if (event.unknown0c == 2) {
      GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(unknown0c), 4, 0.0f);
      if (unknown0c == 2) {
        GfMenuObject::sendOpenEvent(GfMenuObject::getFSInputObject(1), 4, 0.0f);
      }
      unknown20->unknown90.unknown002(&GfMenuObjEnBook::seqFadeOutEnmey);
      unknown20->unknown90.unknown002(&GfMenuObjEnBook::seqDeleteEnmey);
      GfMenuObjOperationInfo::setGuideText(0x3a, 0);
    } else {
      break;
    }
    GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
    GfMenuObject::disableFSInput();
    GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    break;
  case GfMenuTypes::unknown003_33: {
    u32 mode = event.unknown08;
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    unknown20->setupEnBookIDList();
    unknown20->refreshEnBookList();
    unknown0c = mode;
    GfMenuObjOperationInfo::setGuideText(0x3b, 0);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 1;
    param.unknown10 = 2;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case 0x100: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEnBook::DetailListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(5);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
      if (unknown20->isDefeated(unknown20->unknown68->getContents(unknown20->unknown68->getIndex(false)).unknown00)) {
        GfMenuObject::setupInputSelection(acc.unknown10, 0, unknown20->unknown78->getSize());
      } else {
        GfMenuObject::setupInputSelection(acc.unknown10, 0, unknown20->unknown78->getSize() - 1);
      }
    }
    break;
  case 6: {
    u32 index = event.unknown08;
    if (index != 0xffffffff) {
      if (event.unknown0c != 0xffffffff) {
        ui::UIObjectAcc old(unknown20->unknown78->getObject(event.unknown0c));
        old.setDisp(false);
      }
      unknown20->unknown78->setIndex(index);
      ui::UIObjectAcc current(unknown20->unknown78->getSelectObject());
      current.setDisp(true);
    }
    break;
  }
  case 8:
    if (event.unknown0c == 2) {
      ui::EventData closeEvent;
      closeEvent.unknown00 = 0x100;
      GfMenuObject::sendEvent(GfMenuObject::getFSInputObject(4), closeEvent, 0.0f);
      GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
      GfMenuObject::disableFSInput();
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    }
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    unknown20->unknown78->setIndex(0);
    ui::UIObjectAcc current(unknown20->unknown78->getSelectObject());
    current.setDisp(true);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown00 = 6;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf
