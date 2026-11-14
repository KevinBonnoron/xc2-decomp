#include "scn/scn_debug_manipu_trans_2d.h"

#include "ml/attr_transform.h"
#include "ml/cache_draw.h"
#include "ml/event_view.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "ml/scn_util.h"
#include "ml/threadval.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"

namespace ml {

ScnDebugManipuTrans2D::ScnDebugManipuTrans2D(Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale) : ScnDebugManipuObj(SCNMANIPU_UNKNOWN_3, scn, matrix, scale) {
  unknown368 = 4;
  ScnObjCam *cam = scn->getCam(-1);
  if (cam != nullptr) {
    mm::Vec3 screen;
    ScnCamUtil::getScreenPos(screen, cam, false, mm::Vec3::zero);
    f32 x = screen.x > 0.0f ? 0.5f : -0.5f;
    f32 px = static_cast<int>(screen.x + x);
    screen.x = px;
    f32 y = screen.y > 0.0f ? 0.5f : -0.5f;
    y = static_cast<int>(screen.y + y);
    unknownb0.m_front->unknown00.unknown00 = mm::Vec3(px, y, 0.0f);
    unknownb0.m_back->unknown00.unknown00 = mm::Vec3(px, y, 0.0f);
  }
  unknown360 = 0;
  unknown364 = 0;
}

ScnDebugManipuTrans2D::~ScnDebugManipuTrans2D() {}

void ScnDebugManipuTrans2D::setRadius(f32 radius) {}

int ScnDebugManipuTrans2D::getSelectedAxisArrowPick(EventView *event, const mm::Vec3 &position) {
  mm::Rect<int> rect(event->unknown08.x - 5, event->unknown08.y - 5, 10, 10);
  mm::Vec3 axisX = position;
  mm::Vec3 axisY = position;
  axisX.x += 96.0f;
  axisY.y -= 96.0f;
  if (ScnUtil::checkLineRect(axisX, position, rect) && (unknown14 & 1) == 0) {
    return 1;
  }
  if (ScnUtil::checkLineRect(axisY, position, rect)) {
    return (unknown14 & 2) == 0 ? 2 : 0;
  }
  return 0;
}

int ScnDebugManipuTrans2D::getSelectedAxisPlanePick(EventView *event, const mm::Vec3 &position) {
  mm::Vec3 first = position;
  first.x -= 12.0f;
  first.y -= 12.0f;
  mm::Vec3 second = position;
  second.x -= 12.0f;
  second.y += 12.0f;
  mm::Vec3 third = position;
  third.x += 12.0f;
  third.y += 12.0f;
  mm::Vec3 fourth = position;
  fourth.x += 12.0f;
  fourth.y -= 12.0f;
  if (ScnUtil::checkPointPos4(first, second, third, fourth, event->unknown08)) {
    return unknown368;
  }
  return 0;
}

bool ScnDebugManipuTrans2D::checkMouseButtonUp(EventView *event) {
  if (!unknown20) {
    return false;
  }
  unknown368 = 4;
  if (unknown18 != 0) {
    unknown18 = 0;
    return true;
  }
  return false;
}

bool ScnDebugManipuTrans2D::checkMouseMove(EventView *event) {
  if (!unknown20) {
    return false;
  }
  if (unknown18 != 0) {
    unknown360 = event->unknown10.x;
    unknown364 = event->unknown10.y;
    if (unknown18 == 1) {
      unknown364 = 0;
    } else if (unknown18 == 2) {
      unknown360 = 0;
    }
    unknownb0.m_back->unknown00.unknown00 = mm::Vec3(unknown360, unknown364, 0.0f) + unknownb0.m_back->unknown00.unknown10;
    unknownb0.m_back->unknown00.update();
    return true;
  }
  return false;
}

void ScnDebugManipuTrans2D::update() {}

void ScnDebugManipuTrans2D::renderArrowAxisX(DebDraw *debDraw, s16 x, s16 y, int size, const mm::Col4 *color) {
  s16 endX = x + size;
  f32 scaledLength = size * 0.25f;
  s16 length = static_cast<int>(scaledLength + (scaledLength > 0.0f ? 0.5f : -0.5f));
  f32 scaledHalf = size * 0.05f;
  s16 half = static_cast<int>(scaledHalf + (scaledHalf > 0.0f ? 0.5f : -0.5f));
  debDraw->setOrtho();
  debDraw->setZComp(false);
  if (color == nullptr) {
    debDraw->setCol(mm::Col3::red, 1.0f);
  } else {
    debDraw->setCol(*color);
  }
  debDraw->renderLine(x, y, endX, y);
  debDraw->begin(6, 3);
  debDraw->add(endX - length, half + y);
  debDraw->add(endX - length, y - half);
  debDraw->add(endX, y);
  debDraw->end();
}

void ScnDebugManipuTrans2D::renderArrowAxisY(DebDraw *debDraw, s16 x, s16 y, int size, const mm::Col4 *color) {
  s16 endY = y - size;
  f32 scaledHalf = size * 0.05f;
  s16 half = static_cast<int>(scaledHalf + (scaledHalf > 0.0f ? 0.5f : -0.5f));
  f32 scaledLength = size * 0.25f;
  s16 length = static_cast<int>(scaledLength + (scaledLength > 0.0f ? 0.5f : -0.5f));
  debDraw->setOrtho();
  debDraw->setZComp(false);
  if (color == nullptr) {
    debDraw->setCol(mm::Col3::green, 1.0f);
  } else {
    debDraw->setCol(*color);
  }
  debDraw->renderLine(x, y, x, endY);
  debDraw->begin(6, 3);
  debDraw->add(x - half, endY + length);
  debDraw->add(half + x, endY + length);
  debDraw->add(x, endY);
  debDraw->end();
}

} // namespace ml
