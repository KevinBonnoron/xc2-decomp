#include "framework/debug/debug_draw.h"

#include <stdarg.h>
#include <stdio.h>

#include "framework/primitive.h"
#include "ml/cache_draw.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"

namespace fw {
namespace debug {

static const u32 FONT_BUFFER_SIZE = 0x400;
static const u32 CIRCLE_DIVISION = 16;

static void makeTranslation(mm::Mat44 &matrix, const mm::Vec3 &position) {
  mm::Vec3 translation = position;
  matrix.rows[0][0] = 1.0f;
  matrix.rows[0][1] = 0.0f;
  matrix.rows[0][2] = 0.0f;
  matrix.rows[0][3] = 0.0f;
  matrix.rows[1][0] = 0.0f;
  matrix.rows[1][1] = 1.0f;
  matrix.rows[1][2] = 0.0f;
  matrix.rows[1][3] = 0.0f;
  matrix.rows[2][0] = 0.0f;
  matrix.rows[2][1] = 0.0f;
  matrix.rows[2][2] = 1.0f;
  matrix.rows[2][3] = 0.0f;
  matrix.rows[3][0] = translation.x;
  matrix.rows[3][1] = translation.y;
  matrix.rows[3][2] = translation.z;
  matrix.rows[3][3] = 1.0f;
}

bool drawFont(int x, int y, const mm::Col4 &color, const char *format, ...) {
  char text[FONT_BUFFER_SIZE];
  va_list arguments;
  va_start(arguments, format);
  vsnprintf(text, FONT_BUFFER_SIZE - 1, format, arguments);
  va_end(arguments);
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->fontShadow(true);
  result &= cacheDraw->fontColor(color);
  result &= cacheDraw->font(x, y, text);
  return result;
}

bool drawFont(int x, int y, const char *format, ...) {
  char text[FONT_BUFFER_SIZE];
  va_list arguments;
  va_start(arguments, format);
  vsnprintf(text, FONT_BUFFER_SIZE - 1, format, arguments);
  va_end(arguments);
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->fontShadow(true);
  result &= cacheDraw->font(x, y, text);
  return result;
}

bool drawFontColor(const mm::Col4 &color) { return ml::DebDraw::getCacheDraw()->fontColor(color); }

f32 drawFontGetWidth(const char *format, ...) {
  char text[FONT_BUFFER_SIZE];
  va_list arguments;
  va_start(arguments, format);
  vsnprintf(text, FONT_BUFFER_SIZE - 1, format, arguments);
  va_end(arguments);
  return ml::DevGraph::fontGetWidth(text, ml::FONT_STYLE_NORMAL, ml::DebDraw::getCacheDraw()->unknown6054);
}

f32 drawFontGetHeight() { return ml::DevGraph::fontGetHeight(ml::FONT_STYLE_NORMAL, ml::DebDraw::getCacheDraw()->unknown6058); }

bool drawFontScale(f32 x, f32 y) { return ml::DebDraw::getCacheDraw()->fontScale(x, y); }

bool drawLine(const mm::Vec3 &start, const mm::Vec3 &end, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setMatrix(mm::Mat44::identity);
  result &= cacheDraw->setCol(color);
  result &= cacheDraw->renderLine(start, end);
  return result;
}

bool drawLine2D(const mm::Pnt<int> &start, const mm::Pnt<int> &end, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setMatrix(mm::Mat44::identity);
  result &= cacheDraw->setCol(color);
  result &= cacheDraw->renderLine(start, end);
  return result;
}

bool drawSquare2D(const mm::Pnt<int> &start, const mm::Pnt<int> &end, const mm::Col4 &color) {
  mm::Rect<int> rect;
  rect.x = start.x;
  rect.y = start.y;
  rect.width = end.x;
  rect.height = end.y;
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setMatrix(mm::Mat44::identity);
  result &= cacheDraw->setCol(color);
  result &= cacheDraw->renderRectFill(rect);
  return result;
}

bool drawSquare2D(const mm::Rect<int> &rect, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setMatrix(mm::Mat44::identity);
  result &= cacheDraw->setCol(color);
  result &= cacheDraw->renderRectFill(rect);
  return result;
}

bool drawLineSquare2D(const mm::Pnt<int> &start, const mm::Pnt<int> &end, const mm::Col4 &color) {
  mm::Rect<int> rect;
  rect.x = start.x;
  rect.y = start.y;
  rect.width = end.x;
  rect.height = end.y;
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setMatrix(mm::Mat44::identity);
  result &= cacheDraw->setCol(color);
  result &= cacheDraw->renderRect(rect);
  return result;
}

bool drawLineSquare2D(const mm::Rect<int> &rect, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setMatrix(mm::Mat44::identity);
  result &= cacheDraw->setCol(color);
  result &= cacheDraw->renderRect(rect);
  return result;
}

bool drawSphere(const mm::Mat44 &matrix, f32 radius, const mm::Col4 &color, u32 division) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool isZWrite = cacheDraw->unknown6070;
  if (color.a < 1.0f && isZWrite) {
    cacheDraw->setZWrite(false);
  }

  bool result = cacheDraw->setMatrix(matrix);
  result &= cacheDraw->setCol(color);
  result &= cacheDraw->renderRealSphereFill(radius, division);
  if (isZWrite && color.a < 1.0f) {
    cacheDraw->setZWrite(true);
  }

  return result;
}

bool drawSphere(const PrimSphere &sphere, const mm::Col4 &color, u32 division) {
  mm::Mat44 matrix;
  makeTranslation(matrix, sphere.unknown00);
  return drawSphere(matrix, sphere.unknown10, color, division);
}

bool drawSphereLine(const mm::Mat44 &matrix, f32 radius, const mm::Col4 &color, u32 division) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setMatrix(matrix);
  result &= cacheDraw->setCol(color);
  result &= cacheDraw->renderRealSphere(radius, division);
  return result;
}

bool drawSphereLine(const PrimSphere &sphere, const mm::Col4 &color, u32 division) {
  mm::Mat44 matrix;
  makeTranslation(matrix, sphere.unknown00);
  return drawSphereLine(matrix, sphere.unknown10, color, division);
}

bool drawPlaneSphere(const mm::Mat44 &matrix, f32 radius, const mm::Col4 &color, u32 division) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  mm::Vec3 position(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
  bool isZWrite = cacheDraw->unknown6070;
  if (color.a < 1.0f && isZWrite) {
    cacheDraw->setZWrite(false);
  }

  bool result = cacheDraw->setMatrix(mm::Mat44::identity);
  result &= cacheDraw->setCol(color);
  result &= cacheDraw->renderSphereFill(position, radius, division);
  if (isZWrite && color.a < 1.0f) {
    cacheDraw->setZWrite(true);
  }

  return result;
}

bool drawPlaneSphereLine(const mm::Mat44 &matrix, f32 radius, const mm::Col4 &color, u32 division) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  mm::Vec3 position(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
  bool result = cacheDraw->setMatrix(mm::Mat44::identity);
  result &= cacheDraw->setCol(color);
  result &= cacheDraw->renderSphere(position, radius, division);
  return result;
}

bool drawCone(const mm::Mat44 &matrix, f32 radius, f32 height, const mm::Col4 &color, u32 division) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool isZWrite = cacheDraw->unknown6070;
  if (color.a < 1.0f && isZWrite) {
    cacheDraw->setZWrite(false);
  }

  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(matrix);
  result &= cacheDraw->renderConeFill(radius, height, division);
  if (isZWrite && color.a < 1.0f) {
    cacheDraw->setZWrite(true);
  }

  return result;
}

bool drawConeLine(const mm::Mat44 &matrix, f32 radius, f32 height, const mm::Col4 &color, u32 division) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(matrix);
  result &= cacheDraw->renderCone(radius, height, division);
  return result;
}

bool drawCylinder(const mm::Mat44 &matrix, f32 radius, f32 height, const mm::Col4 &color, u32 division) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool isZWrite = cacheDraw->unknown6070;
  if (color.a < 1.0f && isZWrite) {
    cacheDraw->setZWrite(false);
  }

  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(matrix);
  result &= cacheDraw->renderCylinderFill(radius, height, division);
  if (isZWrite && color.a < 1.0f) {
    cacheDraw->setZWrite(true);
  }

  return result;
}

bool drawCylinderLine(const mm::Mat44 &matrix, f32 radius, f32 height, const mm::Col4 &color, u32 division) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(matrix);
  result &= cacheDraw->renderCylinder(radius, height, division);
  return result;
}

bool drawCapsule(const mm::Mat44 &matrix, f32 radius, f32 height, const mm::Col4 &color, u32 division) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool isZWrite = cacheDraw->unknown6070;
  if (color.a < 1.0f && isZWrite) {
    cacheDraw->setZWrite(false);
  }

  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(matrix);
  result &= cacheDraw->renderCapsuleFill(radius, height, division);
  if (isZWrite && color.a < 1.0f) {
    cacheDraw->setZWrite(true);
  }

  return result;
}

bool drawCapsule(const PrimCapsule &capsule, const mm::Col4 &color, u32 division) {
  mm::Mat44 matrix;
  capsule.getMat(matrix);
  return drawCapsule(matrix, capsule.getHeight(), capsule.unknown30, color, division);
}

bool drawCapsuleLine(const mm::Mat44 &matrix, f32 radius, f32 height, const mm::Col4 &color, u32 division) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(matrix);
  result &= cacheDraw->renderCapsule(radius, height, division);
  return result;
}

bool drawCapsuleLine(const PrimCapsule &capsule, const mm::Col4 &color, u32 division) {
  mm::Mat44 matrix;
  capsule.getMat(matrix);
  return drawCapsuleLine(matrix, capsule.getHeight(), capsule.unknown30, color, division);
}

bool drawSquare(const mm::Mat44 &matrix, f32 width, f32 height, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool isZWrite = cacheDraw->unknown6070;
  if (color.a < 1.0f && isZWrite) {
    cacheDraw->setZWrite(false);
  }

  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(matrix);
  result &= cacheDraw->renderSquareFill(width, height);
  if (isZWrite && color.a < 1.0f) {
    cacheDraw->setZWrite(true);
  }

  return result;
}

bool drawSquareLine(const mm::Mat44 &matrix, f32 width, f32 height, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(matrix);
  result &= cacheDraw->renderSquare(width, height);
  return result;
}

bool drawGrid(const mm::Vec3 &center, int count, f32 spacing, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  cacheDraw->setMatrix(mm::Mat44::identity);
  cacheDraw->setCol(color);
  bool result = true;
  f32 half = static_cast<f32>(count) * spacing;
  for (int i = -count; i <= count; i++) {
    f32 offset = static_cast<f32>(i) * spacing;
    mm::Vec3 start(offset + center.x, center.y + 0.0f, center.z - half);
    mm::Vec3 end(offset + center.x, center.y + 0.0f, half + center.z);
    result &= cacheDraw->renderLine(start, end);
  }

  for (int i = -count; i <= count; i++) {
    f32 offset = static_cast<f32>(i) * spacing;
    mm::Vec3 start(center.x - half, center.y + 0.0f, offset + center.z);
    mm::Vec3 end(half + center.x, center.y + 0.0f, offset + center.z);
    result &= cacheDraw->renderLine(start, end);
  }

  return result;
}

bool drawCircleLine(const mm::Mat44 &matrix, f32 radius, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  cacheDraw->setMatrix(mm::Mat44::identity);
  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->renderCircle(matrix, radius, CIRCLE_DIVISION);
  return result;
}

bool drawCircleLine2D(const mm::Pnt<int> &center, f32 radius, const mm::Col4 &color, u32 division, const mm::Mat44 &matrix) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(matrix);
  mm::Vec3 position(static_cast<f32>(center.x), static_cast<f32>(center.y), 0.0f);
  result &= cacheDraw->renderCircle2D(position, radius, division);
  return result;
}

bool drawCircle2D(const mm::Pnt<int> &center, f32 radius, const mm::Col4 &color, u32 division, const mm::Mat44 &matrix) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(matrix);
  mm::Vec3 position(static_cast<f32>(center.x), static_cast<f32>(center.y), 0.0f);
  result &= cacheDraw->renderCircle2DFill(position, radius, division);
  return result;
}

bool drawPoint2D(const mm::Pnt<int> &position, f32 size, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(mm::Mat44::identity);
  mm::Vec3 point(static_cast<f32>(position.x), static_cast<f32>(position.y), 0.0f);
  result &= cacheDraw->renderPoint2D(point, size);
  return result;
}

bool drawOvalLine(const mm::Mat44 &matrix, f32 width, f32 height, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(matrix);
  result &= cacheDraw->renderOval(width, height);
  return result;
}

bool drawAxis(const mm::Mat44 &matrix, f32 length) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setMatrix(matrix);
  result &= cacheDraw->renderAxis(length);
  return result;
}

bool drawArrow(const mm::Vec3 &start, const mm::Vec3 &end, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(mm::Mat44::identity);
  result &= cacheDraw->renderArrow(start, end);
  return result;
}

bool drawCamera(const mm::Mat44 &matrix, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setCol(color);
  result &= cacheDraw->setMatrix(matrix);
  result &= cacheDraw->renderCamera();
  return result;
}

bool drawTriangle2D(const mm::Pnt<int> &first, const mm::Pnt<int> &second, const mm::Pnt<int> &third, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool result = cacheDraw->setMatrix(mm::Mat44::identity);
  result &= cacheDraw->setCol(color);
  result &= cacheDraw->renderTriangle2DFill(first, second, third);
  return result;
}

bool drawTriangle(const mm::Mat44 &matrix, const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third, const mm::Col4 &color) {
  ml::CacheDraw *cacheDraw = ml::DebDraw::getCacheDraw();
  bool isZWrite = cacheDraw->unknown6070;
  if (color.a < 1.0f && isZWrite) {
    cacheDraw->setZWrite(false);
  }

  bool result = cacheDraw->setMatrix(matrix);
  result &= cacheDraw->setCol(color);
  result &= cacheDraw->renderTriangleFill(first, second, third);
  if (isZWrite && color.a < 1.0f) {
    cacheDraw->setZWrite(true);
  }

  return result;
}

bool drawCompareZ(bool isEnable) { return ml::DebDraw::getCacheDraw()->setZComp(isEnable); }

} // namespace debug
} // namespace fw
