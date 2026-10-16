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

SeamlessManager::SeamlessManager() : flags(0), dispFlags(0) {}

void SeamlessManager::clear() {
  if ((flags & FLAG_READ_ENABLE) != 0) {
    setReadEnable(false, nullptr);
  }
  seamPoints.clear();
  firstKeys.clear();
  flags = 0;
}

void SeamlessManager::setReadEnable(bool isEnable, const mm::Vec3 *pos) {
  if (isEnable) {
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->renderDrSys, 0);
    parmAcc.setSeamMapAddPosMode(true);
    parmAcc.setSeamMapReadPos(*pos);
    flags |= FLAG_READ_ENABLE;
  } else {
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->renderDrSys, 0);
    parmAcc.setSeamMapAddPosMode(false);
    flags &= ~FLAG_READ_ENABLE;
  }
}

void SeamlessManager::update() {
  if (seamPoints.empty()) {
    return;
  }
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  while (!seamPoints.empty() && seamPoints.front().frame + SEAM_POINT_KEEP_FRAME <= info.frame) {
    seamPoints.erase(seamPoints.begin());
    flags &= ~FLAG_SEAM;
  }
  if (seamPoints.empty()) {
    return;
  }
  currentPos = seamPoints.front().pos;
  flags = (flags & ~(FLAG_FIRST | FLAG_SEAM)) | FLAG_SEAM;
  setReadEnable(true, &currentPos);
}

void SeamlessManager::render() {
  if (!isDisp() || (flags & (FLAG_FIRST | FLAG_SEAM)) == 0) {
    return;
  }
  int x = ml::DevGraph::getRootWidth() - 415;
  fw::debug::drawSquare2D(mm::Rect<s32>(x, 120, 225, 40), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(x, 120, 225, 40), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  if ((flags & FLAG_FIRST) != 0) {
    fw::debug::drawFont(x + 5, 125, "SEAMLESS(FIRST)");
  } else {
    fw::debug::drawFont(x + 5, 125, "SEAMLESS");
  }
  fw::debug::drawFont(x + 10, 140, "pos:");
  if ((flags & FLAG_FIRST) != 0) {
    fw::debug::drawFont(x + 50, 140, "%.2f %.2f %.2f", readPos.x, readPos.y, readPos.z);
  } else {
    fw::debug::drawFont(x + 50, 140, "%.2f %.2f %.2f", currentPos.x, currentPos.y, currentPos.z);
  }
}

void SeamlessManager::addFirstSeamPoint(const char *name, const PosAxis &axis) {
  for (FirstKey *it = firstKeys.begin(); it != firstKeys.end(); ++it) {
    if (__builtin_strcmp(it->name.c_str(), name) == 0) {
      it->axis = axis;
      it->pos = axis.calcPos();
      return;
    }
  }
  FirstKey key(name, axis, axis.calcPos());
  firstKeys.push_back(key);
}

void SeamlessManager::readFirstSeamPoint(const char *name) {
  for (size_t i = 0; i < firstKeys.size(); i++) {
    if (__builtin_strcmp(firstKeys[i].name.c_str(), name) == 0) {
      firstKeys[i].pos = firstKeys[i].axis.calcPos();
      readPos = firstKeys[i].pos;
      flags = (flags & ~(FLAG_FIRST | FLAG_SEAM)) | FLAG_FIRST;
      setReadEnable(true, &readPos);
      return;
    }
  }
  flags &= ~FLAG_FIRST;
}

void SeamlessManager::readNextSeamPoint(const char *name) {
  if (firstKeys.empty()) {
    return;
  }
  for (size_t i = 0; i < firstKeys.size() - 1; i++) {
    if (__builtin_strcmp(firstKeys[i].name.c_str(), name) == 0) {
      readPos = firstKeys[i + 1].pos;
      flags = (flags & ~(FLAG_FIRST | FLAG_SEAM)) | FLAG_FIRST;
      mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("read next seam point");
      setReadEnable(true, &readPos);
      return;
    }
  }
  flags &= ~FLAG_FIRST;
}

void SeamlessManager::addSeamPoint(f32 frame, const PosAxis &axis) {
  if (!seamPoints.empty()) {
    if (frame <= seamPoints.front().frame) {
      seamPoints.clear();
    } else if (seamPoints.size() >= SEAM_POINT_COUNT) {
      seamPoints.erase(seamPoints.begin());
    }
  }
  seamPoints.push_back(SeamPoint(frame, axis.calcPos()));
}

bool SeamlessManager::isActiveSeamPoint() const { return !seamPoints.empty(); }

void SeamlessManager::setDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_DISP;
  } else {
    dispFlags &= ~DISP_FLAG_DISP;
  }
}

bool SeamlessManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

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
