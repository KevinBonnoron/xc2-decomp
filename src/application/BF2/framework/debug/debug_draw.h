#pragma once
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "types.h"

namespace mm {
struct Col4;
struct Mat44;
struct Vec3;
} // namespace mm

namespace fw {

class PrimCapsule;
class PrimSphere;

namespace debug {

bool drawFont(int x, int y, const mm::Col4 &color, const char *format, ...);
bool drawFont(int x, int y, const char *format, ...);
bool drawFontColor(const mm::Col4 &color);
f32 drawFontGetWidth(const char *format, ...);
f32 drawFontGetHeight();
bool drawFontScale(f32 x, f32 y);
bool drawLine(const mm::Vec3 &start, const mm::Vec3 &end, const mm::Col4 &color);
bool drawLine2D(const mm::Pnt<int> &start, const mm::Pnt<int> &end, const mm::Col4 &color);
bool drawSquare2D(const mm::Pnt<int> &start, const mm::Pnt<int> &end, const mm::Col4 &color);
bool drawSquare2D(const mm::Rect<int> &rect, const mm::Col4 &color);
bool drawLineSquare2D(const mm::Pnt<int> &start, const mm::Pnt<int> &end, const mm::Col4 &color);
bool drawLineSquare2D(const mm::Rect<int> &rect, const mm::Col4 &color);
bool drawSphere(const mm::Mat44 &matrix, f32 radius, const mm::Col4 &color, u32 division);
bool drawSphere(const PrimSphere &sphere, const mm::Col4 &color, u32 division);
bool drawSphereLine(const mm::Mat44 &matrix, f32 radius, const mm::Col4 &color, u32 division);
bool drawSphereLine(const PrimSphere &sphere, const mm::Col4 &color, u32 division);
bool drawPlaneSphere(const mm::Mat44 &matrix, f32 radius, const mm::Col4 &color, u32 division);
bool drawPlaneSphereLine(const mm::Mat44 &matrix, f32 radius, const mm::Col4 &color, u32 division);
bool drawCone(const mm::Mat44 &matrix, f32 radius, f32 height, const mm::Col4 &color, u32 division);
bool drawConeLine(const mm::Mat44 &matrix, f32 radius, f32 height, const mm::Col4 &color, u32 division);
bool drawCylinder(const mm::Mat44 &matrix, f32 radius, f32 height, const mm::Col4 &color, u32 division);
bool drawCylinderLine(const mm::Mat44 &matrix, f32 radius, f32 height, const mm::Col4 &color, u32 division);
bool drawCapsule(const mm::Mat44 &matrix, f32 radius, f32 height, const mm::Col4 &color, u32 division);
bool drawCapsule(const PrimCapsule &capsule, const mm::Col4 &color, u32 division);
bool drawCapsuleLine(const mm::Mat44 &matrix, f32 radius, f32 height, const mm::Col4 &color, u32 division);
bool drawCapsuleLine(const PrimCapsule &capsule, const mm::Col4 &color, u32 division);
bool drawSquare(const mm::Mat44 &matrix, f32 width, f32 height, const mm::Col4 &color);
bool drawSquareLine(const mm::Mat44 &matrix, f32 width, f32 height, const mm::Col4 &color);
bool drawGrid(const mm::Vec3 &center, int count, f32 spacing, const mm::Col4 &color);
bool drawCircleLine(const mm::Mat44 &matrix, f32 radius, const mm::Col4 &color);
bool drawCircleLine2D(const mm::Pnt<int> &center, f32 radius, const mm::Col4 &color, u32 division, const mm::Mat44 &matrix);
bool drawCircle2D(const mm::Pnt<int> &center, f32 radius, const mm::Col4 &color, u32 division, const mm::Mat44 &matrix);
bool drawPoint2D(const mm::Pnt<int> &position, f32 size, const mm::Col4 &color);
bool drawOvalLine(const mm::Mat44 &matrix, f32 width, f32 height, const mm::Col4 &color);
bool drawAxis(const mm::Mat44 &matrix, f32 length);
bool drawArrow(const mm::Vec3 &start, const mm::Vec3 &end, const mm::Col4 &color);
bool drawCamera(const mm::Mat44 &matrix, const mm::Col4 &color);
bool drawTriangle2D(const mm::Pnt<int> &first, const mm::Pnt<int> &second, const mm::Pnt<int> &third, const mm::Col4 &color);
bool drawTriangle(const mm::Mat44 &matrix, const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third, const mm::Col4 &color);
bool drawCompareZ(bool isEnable);

} // namespace debug
} // namespace fw
