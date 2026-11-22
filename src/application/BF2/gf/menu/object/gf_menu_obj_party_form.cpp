#include "gf/menu/object/gf_menu_obj_party_form.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "ui/ctrl/ui_ctrl_curve.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: animation of each selection state; original name unknown.
static const char *const unknown001[] = {"none", "select", "hold"};

// Inferred role: finds an image of a party member slot, the name formatted with the index plus one and the image kind; original name unknown.
static u32 unknown002(u32 handle, const char *format, u32 index, const char *kind) {
  mm::mtl::FixStr<32> name;
  name.format(format, index + 1, kind);
  return ui::UIObjectAcc(handle).searchChild(name.c_str());
}

// Inferred role: finds the layout of a party member slot, the name formatted with the index plus one; original name unknown. Evidence: the same sequence (string,
// temporary UIObjectAcc, searchChild) is in DriverFormListener::reciveEvent (0x71004a7180), BladeFormListener::reciveEvent (0x71004a77b4 and 0x71004a79f0) and
// initialize (0x71004a6918).
static u32 unknown003(u32 handle, const char *format, u32 index) {
  mm::mtl::FixStr<32> name;
  name.format(format, index + 1);
  return ui::UIObjectAcc(handle).searchChild(name.c_str());
}

void GfMenuObjPartyForm::selectDriver(u32 handle, u32 index, u32 state) {
  ui::UIObjectAcc image(unknown002(handle, "IMG_driver%02d_%s", index, "bg"));
  if (image.isValid()) {
    image.startAnimation(unknown001[state], false);
  }
}

void GfMenuObjPartyForm::selectBlade(u32 handle, u32 index, u32 state) {
  ui::UIObjectAcc image(unknown002(handle, "IMG_blade%02d_%s", index, "bg"));
  if (image.isValid()) {
    image.startAnimation(unknown001[state], false);
  }
}

// The game evaluates the row index twice before each notify loop (two "index < size()" assertions at 0x71004a74b0 for the first row, two more for the second, after the
// swap's own four), once for the row and once for its id, which is why the id is read again from the context.
void GfMenuObjPartyForm::swapDriver(PtFormContext *context, u32 first, u32 second) {
  u32 id = context->unknown00[first].unknown00;
  context->unknown00[first].unknown00 = context->unknown00[second].unknown00;
  context->unknown00[second].unknown00 = id;
  unknown004 &firstRow = context->unknown00[first];
  u32 firstId = context->unknown00[first].unknown00;
  for (u32 i = 0; i < firstRow.unknown08.size(); i++) {
    firstRow.unknown08[i]->changeCharData(3, firstId);
  }
  unknown004 &secondRow = context->unknown00[second];
  u32 secondId = context->unknown00[second].unknown00;
  for (u32 i = 0; i < secondRow.unknown08.size(); i++) {
    secondRow.unknown08[i]->changeCharData(3, secondId);
  }
}

// Same shape as swapDriver (0x71004a74b0) at 0x71004a7df8, on the blade rows and with the notification type 4.
void GfMenuObjPartyForm::swapBlade(PtFormContext *context, u32 first, u32 second) {
  u32 id = context->unknown100[first].unknown00;
  context->unknown100[first].unknown00 = context->unknown100[second].unknown00;
  context->unknown100[second].unknown00 = id;
  unknown004 &firstRow = context->unknown100[first];
  u32 firstId = context->unknown100[first].unknown00;
  for (u32 i = 0; i < firstRow.unknown08.size(); i++) {
    firstRow.unknown08[i]->changeCharData(4, firstId);
  }
  unknown004 &secondRow = context->unknown100[second];
  u32 secondId = context->unknown100[second].unknown00;
  for (u32 i = 0; i < secondRow.unknown08.size(); i++) {
    secondRow.unknown08[i]->changeCharData(4, secondId);
  }
}

GfMenuObjPartyForm::GfMenuObjPartyForm(u32 handle) : GfMenuObject(handle) {}

GfMenuObjPartyForm::~GfMenuObjPartyForm() {}

void GfMenuObjPartyForm::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyForm::update() { GfMenuObject::update(); }

void GfMenuObjPartyForm::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.5f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown14 = 1;
    param.unknown00 = 0.5f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjPartyForm::DriverFormListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::setupInputSelection(acc.unknown10, 0, m_ptFormContext->unknown00.size());
    m_ptFormContext->unknownd0 = -1;
    break;
  case 8: {
    u64 params = event.unknown08_u64;
    u32 index = params;
    u32 type = params >> 32;
    switch (type) {
    case 1:
      if (unknown0c == 0) {
        m_ptFormContext->unknownd0 = index;
        selectDriver(acc.unknown10, index, 2);
        unknown0c = 1;
      } else if (unknown0c == 1) {
        u32 selected = m_ptFormContext->unknownd0;
        if (selected == index) {
          GfMenuObjUtil::playSECommon(2);
          return;
        }
        swapDriver(m_ptFormContext, selected, index);
        selectDriver(acc.unknown10, m_ptFormContext->unknownd0, 0);
        m_ptFormContext->unknownd0 = -1;
        unknown0c = 0;
      }
      break;
    case 2:
      if (unknown0c == 1) {
        u32 selected = m_ptFormContext->unknownd0;
        if (index == selected) {
          selectDriver(acc.unknown10, index, 1);
        } else {
          selectDriver(acc.unknown10, selected, 0);
        }
        m_ptFormContext->unknownd0 = -1;
        unknown0c = 0;
      } else {
        GfMenuObject::returnFSSubLayer(acc.unknown10, 1);
      }
      break;
    case 3:
      GfMenuObject::closeFSLayer(acc.unknown10, true, true);
      break;
    case 9:
      if (unknown0c == 0) {
        mm::mtl::FixedVector<u16, 422> blades;
        bool hasBlade = GfDataDriver::getSetBlade(blades, m_ptFormContext->unknown00[static_cast<int>(index)].unknown00);
        if (hasBlade) {
          m_ptFormContext->unknownd0 = index;
          ui::EventData next;
          next.unknown00 = 0x21;
          GfMenuObject::sendEvent(acc.searchSibiling("LAY_blade"), next, 0.0f);
          GfMenuObject::disableInput(acc.unknown10);
          GfMenuObjUtil::playSECommonDecide();
          return;
        }
      }
      GfMenuObjUtil::playSECommon(2);
      return;
    }
    GfMenuObjUtil::playSECommonFromInput(type);
    break;
  }
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    ui::UIObjectAcc cursor(acc.unknown10, "IMG_dr_cursor");
    if (cursor.isValid()) {
      ui::UIObjectAcc driver(unknown003(acc.unknown10, "LAY_driver%02d", index));
      if (driver.isValid()) {
        GfMenuObjUtil::setDockPos(cursor.unknown10, driver.unknown10, 4, true);
        GfMenuObjUtil::addPos(cursor.unknown10, 0, -10);
        if (index != m_ptFormContext->unknownd0) {
          selectDriver(acc.unknown10, index, 1);
        }
        if (previous != 0xffffffff && previous != m_ptFormContext->unknownd0) {
          selectDriver(acc.unknown10, previous, 0);
        }
      }
    }
    break;
  }
  case 0x21:
    GfMenuObject::enableInput(acc.unknown10);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjPartyForm::BladeFormListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = 0;
    unknown10 = -1;
    break;
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    ui::UIObjectAcc cursor(acc.unknown10, "IMG_bl_cursor");
    if (cursor.isValid()) {
      ui::UIObjectAcc blade(unknown003(acc.unknown10, "LAY_blade%02d", index));
      if (blade.isValid()) {
        GfMenuObjUtil::setDockPos(cursor.unknown10, blade.unknown10, 4, true);
        GfMenuObjUtil::addPos(cursor.unknown10, 0, -10);
        if (index != m_ptFormContext->unknown180) {
          selectBlade(acc.unknown10, index, 1);
        }
        if (previous != 0xffffffff && previous != m_ptFormContext->unknown180) {
          selectBlade(acc.unknown10, previous, 0);
        }
      }
    }
    break;
  }
  case 3:
    if (unknown0c == 2) {
      ui::EventData next;
      next.unknown00 = 0x21;
      GfMenuObject::sendEvent(acc.searchSibiling("LAY_driver"), next, 0.0f);
    }
    break;
  case 8: {
    u32 type = event.unknown0c;
    switch (type) {
    case 1: {
      u32 index = event.unknown08;
      if (unknown0c == 0) {
        m_ptFormContext->unknown180 = index;
        selectBlade(acc.unknown10, index, 2);
        unknown0c = 1;
      } else if (unknown0c == 1) {
        u32 selected = m_ptFormContext->unknown180;
        if (selected == index) {
          GfMenuObjUtil::playSECommon(2);
          return;
        }
        swapBlade(m_ptFormContext, selected, index);
        // The game calls selectDriver here (bl 0x71004a740c right after swapBlade at 0x71004a7cfc), not selectBlade.
        selectDriver(acc.unknown10, m_ptFormContext->unknown180, 0);
        m_ptFormContext->unknown180 = 0xffffffff;
        unknown0c = 0;
      }
      break;
    }
    case 2:
      if (unknown0c == 0) {
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 2;
        param.unknown00 = 0.5f;
        param.unknown14 = 6;
        param.unknown11 = true;
        param.unknown18 = unknown10;
        param.unknown0c = ui::CURVE_TYPE_SIN90;
        GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
        m_ptFormContext->unknownd0 = -1;
        unknown0c = 2;
      } else if (unknown0c == 1) {
        selectBlade(acc.unknown10, m_ptFormContext->unknown180, 0);
        m_ptFormContext->unknown180 = 0xffffffff;
        unknown0c = 0;
      }
      break;
    case 3:
      GfMenuObject::closeFSLayer(acc.unknown10, true, true);
      break;
    }
    GfMenuObjUtil::playSECommonFromInput(type);
    break;
  }
  case 0x21: {
    u32 driver = m_ptFormContext->unknown00[m_ptFormContext->unknownd0].unknown00;
    m_ptFormContext->unknownd8 = driver;
    mm::mtl::FixedVector<class unknown140 *, 3> &gauges = m_ptFormContext->unknowne0;
    for (u32 i = 0; i < gauges.size(); i++) {
      gauges[i]->changeCharData(3, driver);
    }
    {
      GfMenuObjUtil::CtrlParam param;
      // Assignment order: unknown08 before unknown00, as in MainListener::reciveEvent case 1 of this file; the constructor stores then come in the game's order
      // (0x71004a7958: stp xzr,xzr before stp wzr,w8; the order unknown00, unknown08 swaps them). Event 8 case 2 also matches with either order; it uses the same one.
      param.unknown08 = 1;
      param.unknown00 = 0.5f;
      param.unknown14 = 4;
      param.unknown11 = true;
      param.unknown18 = unknown10;
      param.unknown0c = ui::CURVE_TYPE_SIN90;
      unknown10 = GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      unknown0c = 0;
    }
    {
      mm::mtl::FixedVector<u16, 422> blades;
      GfDataDriver::getSetBlade(blades, m_ptFormContext->unknownd8);
      for (u32 i = 0; i < 3; i++) {
        ui::UIObjectAcc blade(unknown003(acc.unknown10, "LAY_blade%02d", i));
        if (i < blades.size()) {
          m_ptFormContext->unknown100[i].unknown00 = blades[i];
          mm::mtl::FixedVector<class unknown140 *, 3> &adapters = m_ptFormContext->unknown100[i].unknown08;
          // The game evaluates blades[i] again here, before the loop (assertion 0x71004a7a9c, load 0x71004a7ac0), as swapBlade does for the row id (0x71004a7e4c).
          u32 bladeId = blades[i];
          for (u32 j = 0; j < adapters.size(); j++) {
            adapters[j]->changeCharData(4, bladeId);
          }
          blade.setDisp(true);
          selectBlade(acc.unknown10, i, 0);
          ui::UIObjectAcc rare(unknown002(acc.unknown10, "IMG_blade%02d_%s", i, "rare_img"));
          if (rare.isValid()) {
            rare.startAnimation(GfDataBlade::isRareBlade(blades[i]) ? "rare" : "common", false);
          }
        } else {
          blade.setDisp(false);
        }
      }
      GfMenuObject::setupInputSelection(acc.unknown10, 0, blades.size());
      selectBlade(acc.unknown10, 0, 0);
    }
    m_ptFormContext->unknown180 = 0xffffffff;
    unknown0c = 0;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
