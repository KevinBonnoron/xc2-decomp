#include "event/cam_free.h"

#include <math.h>

#include "event/manager.h"
#include "ml/dev_keyboard.h"
#include "ml/event_view.h"
#include "ml/scn.h"
#include "ml/threadval.h"
#include "ml/win_view.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"

namespace event {

CamFree::CamFree(bool isFocal) : CamBase(isFocal), unknown48(0), unknown4c(0), unknown50(CTRL_MODE_UNKNOWN_0), unknown54(5.0f) {}

CamFree::~CamFree() {
  if ((unknown48 & 1) != 0) {
    Manager::get()->getScn()->getView(-1)->detachWorkEvent(this);
  }
}

void CamFree::update(const FrameInfo &info) {}

void CamFree::setActive(bool isActive) {
  if (((unknown48 & 1) != 0) != isActive) {
    ml::WinView *view = Manager::get()->getScn()->getView(-1);
    if (isActive) {
      view->attachWorkEvent(this, false);
      unknown48 |= 1;
    } else {
      view->detachWorkEvent(this);
      unknown48 &= ~1;
    }
  }
}

bool CamFree::OnMouseButtonDown(ml::EventView *view) {
  bool isKeyDown = (view->unknown28 & 1) != 0;
  u32 flags = unknown4c & ~8;
  if (isKeyDown) {
    flags = unknown4c | 8;
  }
  unknown4c = flags;
  if ((view->buttons & 4) != 0) {
    unknown4c |= 1;
  }
  if ((view->buttons & 2) != 0) {
    unknown4c |= 2;
  }
  if ((view->buttons & 1) != 0) {
    unknown4c |= 4;
  }
  return unknown001();
}

bool CamFree::OnMouseButtonUp(ml::EventView *view) {
  if ((view->buttons & 4) != 0) {
    unknown4c &= ~1;
  }
  if ((view->buttons & 2) != 0) {
    unknown4c &= ~2;
  }
  if ((view->buttons & 1) != 0) {
    unknown4c &= ~4;
  }
  return unknown001();
}

void CamFree::ctrlTrack(const mm::Pnt<int> &mouse) {
  f32 speed = unknown54 * 0.2f;
  f32 scale = speed > 1.0f ? speed * 20.0f : speed;
  mm::Vec3 move;
  getScreenMove2TargetMove(move, mouse);
  mm::Vec3 offset = move * scale;
  unknown10 = unknown10 + offset;
  unknown20 = unknown20 + offset;
}

bool CamFree::OnKeyUp(ml::EventView *view) {
  if ((view->unknown28 & 1) == 0) {
    return false;
  }
  unknown4c &= ~8;
  unknown50 = CTRL_MODE_UNKNOWN_0;
  return true;
}

bool CamFree::OnMouseMove(ml::EventView *view) {
  if ((ml::DevKeyboard::getVkHold() & 1) == 0) {
    return false;
  }
  // Cases in the order of the blocks of the game (0x71000afa7c: tumble 0x71000afac8, dolly 0x71000afad8, track, inlined, 0x71000afae8): the compares come out as 1, 2 and 3 with ctrlTumble as the
  // fall-through. Ascending case order, an if/else chain and `return true` in each case all give 68 instructions against 66 (checked).
  switch (unknown50) {
  case CTRL_MODE_UNKNOWN_3:
    ctrlTumble(view->unknown10);
    break;
  case CTRL_MODE_UNKNOWN_1:
    ctrlDolly(view->unknown10);
    break;
  case CTRL_MODE_UNKNOWN_2:
    ctrlTrack(view->unknown10);
    break;
  default:
    return false;
  }
  return true;
}

void CamFree::getViewInvertMatrix(mm::Mat44 &matrix) const {
  mm::Vec3 rotation = getRot();
  f32 sinX = sinf(rotation.x);
  f32 cosX = cosf(rotation.x);
  f32 sinY = sinf(rotation.y);
  f32 cosY = cosf(rotation.y);
  f32 sinZ = sinf(rotation.z);
  f32 cosZ = cosf(rotation.z);
  // The columns are written one after the other (1.0.0: 0x71000b09d0): written row by row the 90 instructions are scheduled differently from the first fmul on (measured).
  matrix.rows[0][0] = sinX * sinY * sinZ + cosY * cosZ;
  matrix.rows[1][0] = sinX * sinY * cosZ - cosY * sinZ;
  matrix.rows[2][0] = cosX * sinY;
  matrix.rows[0][1] = cosX * sinZ;
  matrix.rows[1][1] = cosX * cosZ;
  matrix.rows[2][1] = -sinX;
  matrix.rows[0][2] = sinX * cosY * sinZ - sinY * cosZ;
  matrix.rows[1][2] = sinY * sinZ + sinX * cosY * cosZ;
  matrix.rows[2][2] = cosX * cosY;
  matrix.rows[0][3] = 0.0f;
  matrix.rows[1][3] = 0.0f;
  matrix.rows[2][3] = 0.0f;
  matrix.rows[3][0] = 0.0f;
  matrix.rows[3][1] = 0.0f;
  matrix.rows[3][2] = 0.0f;
  matrix.rows[3][3] = 1.0f;
  // Single-use local: the game reads the position (one 64-bit load for x and y, then z) after the rotation stores (1.0.0: 0x71000b0a4c); setTrans(unknown10) loads it earlier
  // (first difference at +0xc4, 91 instructions against 90, measured).
  mm::Vec3 pos = unknown10;
  matrix.setTrans(pos);
}

void CamFree::getFrustum(mm::Mat44 &matrix) const {
  ml::ScnObjCam *cam = Manager::get()->getScn()->getCam(-1);
  f32 top = unknown38 * tanf(cam->unknown70.m_front->unknown1e8 * mm::DEG_TO_RAD * 0.5f);
  f32 bottom = -top;
  f32 left = top * -1.777f;
  f32 right = top * 1.777f;
  f32 nearClip = cam->unknown70.m_front->unknown1f4;
  f32 farClip = cam->unknown70.m_front->unknown1f8;
  // Temporary matrix: writing the elements straight into the output gives 65 instructions with the
  // divisions scheduled differently (1.0.0: 0x71000b0f5c); building a local and assigning it matches.
  mm::Mat44 result;
  result.rows[0][0] = (nearClip + nearClip) / (top - bottom);
  result.rows[0][1] = 0.0f;
  result.rows[0][2] = 0.0f;
  result.rows[0][3] = 0.0f;
  result.rows[1][0] = 0.0f;
  result.rows[1][1] = (nearClip + nearClip) / (right - left);
  result.rows[1][2] = 0.0f;
  result.rows[1][3] = 0.0f;
  result.rows[2][0] = -(top + bottom) / (top - bottom);
  result.rows[2][1] = -(right + left) / (right - left);
  result.rows[2][2] = nearClip / (farClip - nearClip);
  result.rows[2][3] = 1.0f;
  result.rows[3][0] = 0.0f;
  result.rows[3][1] = 0.0f;
  result.rows[3][2] = -(nearClip * farClip) / (farClip - nearClip);
  result.rows[3][3] = 0.0f;
  matrix = result;
}

} // namespace event
