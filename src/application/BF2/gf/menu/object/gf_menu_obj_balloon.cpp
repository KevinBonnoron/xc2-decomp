#include "gf/menu/object/gf_menu_obj_balloon.h"

#include <string.h>

#include "gf/data/gf_data_save.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/call/gf_menu_call_manager.h"
#include "gf/menu/gf_menu_reference_item.h"
#include "gf/menu/gf_menu_str_linker.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/text/ui_tag_parser.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

// Inferred role: layouts duplicated by openCommon; original name unknown.
static const char *const unknown001[] = {"LAY_talk_main", "LAY_select_main"};

// Inferred role: feeling tag value and its color; original name unknown.
struct unknown002 {
  const char *unknown00;
  const char *unknown08;
};

namespace gf {

GfMenuObjBalloon::GfMenuObjBalloon(u32 handle) : GfMenuObject(handle), unknown28(0), unknown30(0), unknown38(nullptr), unknown40(nullptr), unknown78(this), unknown1d8(false), unknown1dc(0xffffffff) {
  unknown60.assign(mm::mtl::IntrusivePtr<GfMenuReferenceItem>());
}

GfMenuObjBalloon::~GfMenuObjBalloon() {
  unknown60.assign(mm::mtl::IntrusivePtr<GfMenuReferenceItem>());
  unknown48.clear();
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
}

void GfMenuObjBalloon::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBalloon::update() {
  unknown78.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBalloon::resetFeeling(ui::UIObjectAcc &acc) { acc.setAddColor("black"); }

void GfMenuObjBalloon::setFeeling(ui::UIObjectAcc &acc, const ui::UIStr &string) {
  unknown002 feelings[] = {{"Normal", "black"}, {"Anger", "red"}, {"Think", "yellow"}};
  const char *color = "black";
  const char *kind = ui::UITagParser::get()->parseTagParam(string.c_str(), "ML:Feeling", "kind");
  if (kind != nullptr) {
    for (u32 i = 0; i < 3; i++) {
      if (strcmp(kind, feelings[i].unknown00) == 0) {
        color = feelings[i].unknown08;
        break;
      }
    }
  }
  acc.setAddColor(color);
}

u32 GfMenuObjBalloon::getFeeling(const ui::UIStr &string) {
  const char *kind = ui::UITagParser::get()->parseTagParam(string.c_str(), "ML:Feeling", "kind");
  if (kind == nullptr) {
    return 0;
  }
  if (strcmp(kind, "Normal") == 0) {
    return 0;
  }
  if (strcmp(kind, "Anger") == 0) {
    return 1;
  }
  if (strcmp(kind, "Think") == 0) {
    return 2;
  }
  return 0;
}

u32 GfMenuObjBalloon::openCommon(GfMenuCallContext *context, u32 call, GF_OBJ_HANDLE *handle, const MenuOffset &offset, u32 type, bool isAutoTalk) {
  u32 object = GfMenuObject::getAttachedObject(call);
  if (ui::UIObjectAcc(object).isValid()) {
    if (!ui::UIObjectAcc(object).isTerm()) {
      u32 child = ui::UIObjectAcc(object).duplicateChild(unknown001[type]);
      if (ui::UIObjectAcc(child).isValid()) {
        setup(child, handle, offset, false, type, isAutoTalk);
        if (context != nullptr) {
          GfMenuObject::startCallContext(context, call, child);
        }
        return child;
      }
    }
  }
  return 0;
}

bool GfMenuObjBalloon::seqSave() {
  unknown1dc = GfReqCommand::reqSave(SAVESLOT_DEFAULT);
  GfMenuObjFade::dispSaving(true, 0);
  return true;
}

bool GfMenuObjBalloon::seqSaveWait() {
  if (!GfReqManager::isValid(unknown1dc)) {
    GfMenuObjFade::dispSaving(false, 0);
    unknown1dc = -1;
    ui::UIObjectAcc acc(unknown18, "LAY_select");
    GfMenuObject::addResultCallContext(acc.unknown10, 2, 0);
    return true;
  }
  return false;
}

void GfMenuObjBalloon::nextEvent(GfMenuCallContext *context, const NextParam &param) {
  if (context->isActive() && (context->unknown10 & 0xfffffffe) == 2) {
    u32 object = GfMenuObject::getAttachedObject(2);
    u32 handle = context->unknown14;
    if (ui::UIUtil::isValid(handle)) {
      GfMenuObject::nextCallContext(context, 3);
      u16 id = GfMenuObject::registString(ui::UIStr(param.unknown00, param.unknown08));
      ui::EventData event;
      event.unknown00 = 0x104;
      event.unknown08 = id;
      event.unknown14 = ui::UIObjectAcc(handle).getDuplicateIndex();
      GfMenuObject::sendEvent(object, event, 0.0f);
    }
  }
}

void GfMenuObjBalloon::close(GfMenuCallContext *context, bool isImmediate) {
  if (!context->isActive()) {
    return;
  }
  if (context->isTerm()) {
    return;
  }
  u32 object = 0;
  switch (context->unknown10) {
  case 2:
  case 3:
    object = GfMenuObject::getAttachedObject(2);
    break;
  case 4:
    object = GfMenuObject::getAttachedObject(4);
    break;
  case 5:
    object = GfMenuObject::getAttachedObject(5);
    break;
  case 7:
    object = GfMenuObject::getAttachedObject(7);
    break;
  case 8:
    object = GfMenuObject::getAttachedObject(8);
    break;
  case 9:
    object = GfMenuObject::getAttachedObject(9);
    break;
  }
  u32 handle = context->unknown14;
  if (ui::UIUtil::isValid(handle)) {
    GfMenuObject::nextCallContext(context, 6);
    ui::EventData event;
    event.unknown00 = 0x103;
    event.unknown10 = isImmediate;
    event.unknown14 = ui::UIObjectAcc(handle).getDuplicateIndex();
    GfMenuObject::sendEvent(object, event, 0.0f);
  }
}

void GfMenuObjBalloon::openEventSelectBox(GfMenuCallContext *context, const OpenSelectBoxParam &param) {
  if (context->getState() == GfMenuCallContext::STATE_IDLE && param.unknown18.size() != 0) {
    u32 object = GfMenuObject::getAttachedObject(7);
    u16 id = GfMenuObject::registString(ui::UIStr(param.unknown00, param.unknown08));
    for (int i = 0; i < static_cast<int>(param.unknown18.size()); i++) {
      GfMenuCallManager::get()->unknown228.addSelectString(ui::UIStr(param.unknown10, param.unknown18[i]));
    }
    if (context != nullptr) {
      GfMenuObject::startCallContext(context, 7, object);
    }
    ui::EventData event;
    event.unknown00 = 0x105;
    event.unknown08 = id;
    GfMenuObject::sendEvent(object, event, 0.0f);
    ui::UIObjectAcc(object).setSuspend(false);
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBalloon>(const mm::mtl::Delegate<bool()> *);
template void mm::mtl::FixedArray<mm::mtl::IntrusivePtr<gf::GfMenuReferenceItem>, 3>::assign(const mm::mtl::IntrusivePtr<gf::GfMenuReferenceItem> &);
template mm::mtl::FixedArray<mm::mtl::IntrusivePtr<gf::GfMenuReferenceItem>, 3>::~FixedArray();
