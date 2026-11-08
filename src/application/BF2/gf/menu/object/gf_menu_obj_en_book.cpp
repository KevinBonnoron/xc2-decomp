#include "gf/menu/object/gf_menu_obj_en_book.h"

#include "bdat.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_en_book.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_model_view.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_msg_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
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
    unknown40->setup(getAllocator(ALLOCATOR_DEFAULT), param);
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

} // namespace gf
