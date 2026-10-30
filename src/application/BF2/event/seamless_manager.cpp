#include "event/seamless_manager.h"

#include <stddef.h>

#include "event/debug_manager.h"
#include "event/frame_manager.h"
#include "event/manager.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "ml/scn.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "scn/scn_render_dr_sys_parm_acc.h"

namespace event {

static constexpr f32 SEAM_POINT_KEEP_FRAME = 5.0f;

SeamlessManager::SeamlessManager() : unknown10(0), unknown14(0) {}

void SeamlessManager::clear() {
  if ((unknown10 & FLAG_READ_ENABLE) != 0) {
    setReadEnable(false, nullptr);
  }
  unknown540.clear();
  unknown20.clear();
  unknown10 = 0;
}

void SeamlessManager::setReadEnable(bool isEnable, const mm::Vec3 *pos) {
  if (isEnable) {
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->unknown38, 0);
    parmAcc.setSeamMapAddPosMode(true);
    parmAcc.setSeamMapReadPos(*pos);
    unknown10 |= FLAG_READ_ENABLE;
  } else {
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->unknown38, 0);
    parmAcc.setSeamMapAddPosMode(false);
    unknown10 &= ~FLAG_READ_ENABLE;
  }
}

void SeamlessManager::update() {
  if (unknown540.empty()) {
    return;
  }
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  while (!unknown540.empty() && unknown540.front().unknown00 + SEAM_POINT_KEEP_FRAME <= info.unknown00) {
    unknown540.erase(unknown540.begin());
    unknown10 &= ~FLAG_SEAM;
  }
  if (unknown540.empty()) {
    return;
  }
  unknown2550 = unknown540.front().unknown10;
  unknown10 = (unknown10 & ~(FLAG_FIRST | FLAG_SEAM)) | FLAG_SEAM;
  setReadEnable(true, &unknown2550);
}

void SeamlessManager::render() {
  if (!isDisp() || (unknown10 & (FLAG_FIRST | FLAG_SEAM)) == 0) {
    return;
  }
  int x = ml::DevGraph::getRootWidth() - 415;
  fw::debug::drawSquare2D(mm::Rect<s32>(x, 120, 225, 40), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(x, 120, 225, 40), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  if ((unknown10 & FLAG_FIRST) != 0) {
    fw::debug::drawFont(x + 5, 125, "SEAMLESS(FIRST)");
  } else {
    fw::debug::drawFont(x + 5, 125, "SEAMLESS");
  }
  fw::debug::drawFont(x + 10, 140, "pos:");
  if ((unknown10 & FLAG_FIRST) != 0) {
    fw::debug::drawFont(x + 50, 140, "%.2f %.2f %.2f", unknown530.x, unknown530.y, unknown530.z);
  } else {
    fw::debug::drawFont(x + 50, 140, "%.2f %.2f %.2f", unknown2550.x, unknown2550.y, unknown2550.z);
  }
}

void SeamlessManager::addFirstSeamPoint(const char *name, const PosAxis &axis) {
  for (FirstKey *it = unknown20.begin(); it != unknown20.end(); ++it) {
    if (__builtin_strcmp(it->unknown00.c_str(), name) == 0) {
      it->unknown20 = axis;
      it->unknown40 = axis.calcPos();
      return;
    }
  }
  FirstKey key(name, axis, axis.calcPos());
  unknown20.push_back(key);
}

void SeamlessManager::readFirstSeamPoint(const char *name) {
  for (size_t i = 0; i < unknown20.size(); i++) {
    if (__builtin_strcmp(unknown20[i].unknown00.c_str(), name) == 0) {
      unknown20[i].unknown40 = unknown20[i].unknown20.calcPos();
      unknown530 = unknown20[i].unknown40;
      unknown10 = (unknown10 & ~(FLAG_FIRST | FLAG_SEAM)) | FLAG_FIRST;
      setReadEnable(true, &unknown530);
      return;
    }
  }
  unknown10 &= ~FLAG_FIRST;
}

void SeamlessManager::readNextSeamPoint(const char *name) {
  if (unknown20.empty()) {
    return;
  }
  for (size_t i = 0; i < unknown20.size() - 1; i++) {
    if (__builtin_strcmp(unknown20[i].unknown00.c_str(), name) == 0) {
      unknown530 = unknown20[i + 1].unknown40;
      unknown10 = (unknown10 & ~(FLAG_FIRST | FLAG_SEAM)) | FLAG_FIRST;
      mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("read next seam point");
      setReadEnable(true, &unknown530);
      return;
    }
  }
  unknown10 &= ~FLAG_FIRST;
}

void SeamlessManager::addSeamPoint(f32 frame, const PosAxis &axis) {
  if (!unknown540.empty()) {
    if (frame <= unknown540.front().unknown00) {
      unknown540.clear();
    } else if (unknown540.size() >= SEAM_POINT_COUNT) {
      unknown540.erase(unknown540.begin());
    }
  }
  unknown540.push_back(unknown001(frame, axis.calcPos()));
}

bool SeamlessManager::isActiveSeamPoint() const { return !unknown540.empty(); }

void SeamlessManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= DISP_FLAG_DISP;
  } else {
    unknown14 &= ~DISP_FLAG_DISP;
  }
}

bool SeamlessManager::isDisp() const { return (unknown14 & DISP_FLAG_DISP) != 0; }

void SeamlessManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER:
    render();
    break;
  default:
    break;
  }
}

} // namespace event
