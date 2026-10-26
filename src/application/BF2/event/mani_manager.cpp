#include "event/mani_manager.h"

#include "event/i_mani_callback.h"
#include "event/manager.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "ml/event_view.h"
#include "ml/scn.h"
#include "ml/win_view.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "scn/scn_debug.h"

namespace event {

ManiManager::ManiManager()
    : unknown22030(MANI_TYPE_POS), unknown22040(mm::Mat44::identity), unknown22080(mm::Mat44::identity), unknown220c0(mm::Mat44::identity), unknown22100(mm::Mat44::identity),
      unknown22140(mm::Mat44::identity) {}

void ManiManager::adjestPosY(mm::Vec3 &position) {
  mm::Vec3 result = position;
  mm::Vec3 start;
  start.x = position.x;
  start.y = position.y + 1.0f;
  start.z = position.z;
  if (fw::ColiCheck::getSnapPos(result, start, 6.0f, 0xffffffff)) {
    position = result;
  }
}

bool ManiManager::exist(mm::mtl::FixedVector<Item, ITEM_COUNT> &items, IManiCallback *callback) {
  for (u32 i = 0; i < items.size(); i++) {
    if (items[i].unknown00 == callback) {
      return true;
    }
  }
  return false;
}

void ManiManager::create() {
  if (!unknown18.test(FLAG_ATTACHED)) {
    Manager::get()->getScn()->getView(-1)->attachWorkEvent(this, false);
    unknown18.set(FLAG_ATTACHED);
  }
  unknown20.clear();
}

void ManiManager::clear() {
  clearManipulate();
  if (unknown18.test(FLAG_ATTACHED)) {
    Manager::get()->getScn()->getView(-1)->detachWorkEvent(this);
    unknown18.set(FLAG_ATTACHED, false);
  }
  unknown20.clear();
  unknown18.clear();
}

void ManiManager::update() {
  if (unknown18.test(FLAG_ENABLE) && unknown1c.test(DEBUG_FLAG_ENABLE) && unknown18.test(FLAG_ACTIVE)) {
    updateManipulate();
  }
}

void ManiManager::clearManipulate() {
  unknown20.clear();
  unknown22030 = MANI_TYPE_POS;
  Manager::get()->getScn()->unknown30->clrManipulator();
  unknown18.set(FLAG_ACTIVE, false);
}

void ManiManager::render() {
  if (!unknown18.test(FLAG_ENABLE) || !unknown1c.test(DEBUG_FLAG_ENABLE)) {
    return;
  }
  for (Item *it = unknown20.begin(); it != unknown20.end(); ++it) {
    IManiCallback::RenderParam param;
    param.unknown00 = mm::Col4(0.8f, 1.0f, 0.8f, 0.5f);
    it->unknown00->OnManiRender(param);
  }
  if (unknown20.empty()) {
    return;
  }
  int width = ml::DevGraph::getRootWidth();
  fw::debug::drawSquare2D(mm::Rect<s32>(width - 160, 145, 150, 25), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(width - 160, 145, 150, 25), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  int textX = width - 155;
  if (unknown22030 == MANI_TYPE_POS) {
    fw::debug::drawFontColor(mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  } else {
    fw::debug::drawFontColor(mm::Col4(0.8f, 0.8f, 0.8f, 1.0f));
  }
  fw::debug::drawFont(textX, 150, "W:Pos");
  textX = width - 110;
  if (unknown22030 == MANI_TYPE_ROT) {
    fw::debug::drawFontColor(mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  } else {
    fw::debug::drawFontColor(mm::Col4(0.8f, 0.8f, 0.8f, 1.0f));
  }
  fw::debug::drawFont(textX, 150, "E:Rot");
  textX = width - 65;
  if (unknown22030 == MANI_TYPE_TAR) {
    fw::debug::drawFontColor(mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  } else {
    fw::debug::drawFontColor(mm::Col4(0.8f, 0.8f, 0.8f, 1.0f));
  }
  fw::debug::drawFont(textX, 150, "R:Tar");
}

void ManiManager::setEnable(bool isEnable) {
  if (isEnable) {
    unknown18.set(FLAG_ENABLE, true);
  } else {
    clearManipulate();
    unknown18.set(FLAG_ENABLE, false);
  }
}

void ManiManager::setAdjestPosEnable(bool isEnable) { unknown18.set(FLAG_ADJEST_POS, isEnable); }

bool ManiManager::isAdjestPosEnable() const { return unknown18.test(FLAG_ADJEST_POS); }

void ManiManager::setDebugEnable(bool isEnable) { unknown1c.set(DEBUG_FLAG_ENABLE, isEnable); }

bool ManiManager::OnKeyDown(ml::EventView *view) {
  if (!unknown18.test(FLAG_ENABLE) || !unknown1c.test(DEBUG_FLAG_ENABLE) || !unknown18.test(FLAG_ACTIVE)) {
    return false;
  }
  switch (view->unknown33) {
  case 'E':
    changeManipulate(MANI_TYPE_ROT);
    return true;
  case 'Q':
    clearManipulate();
    return true;
  case 'R':
    changeManipulate(MANI_TYPE_TAR);
    return true;
  case 'W':
    changeManipulate(MANI_TYPE_POS);
    return true;
  }
  return false;
}

void ManiManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER:
    render();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  default:
    break;
  }
}

bool ManiManager::OnMouseButtonDown(ml::EventView *view) { return false; }

} // namespace event
