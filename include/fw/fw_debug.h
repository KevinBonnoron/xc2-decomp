#pragma once

namespace mm {
struct Col4;
struct Mat44;
struct Vec3;
template <typename T> struct Pnt;
template <typename T> struct Rect;
} // namespace mm

namespace fw {
namespace debug {

void drawFont(int x, int y, const char *format, ...);
void drawFontColor(const mm::Col4 &color);
int drawFontGetHeight();
void drawLine(const mm::Vec3 &start, const mm::Vec3 &end, const mm::Col4 &color);
void drawSquare2D(const mm::Rect<int> &rect, const mm::Col4 &color);
void drawLineSquare2D(const mm::Rect<int> &rect, const mm::Col4 &color);
void drawLine2D(const mm::Pnt<int> &start, const mm::Pnt<int> &end, const mm::Col4 &color);
void drawCompareZ(bool isCompare);
void drawFont(int x, int y, const mm::Col4 &color, const char *format, ...);
void drawBoxLine(const mm::Mat44 &matrix, const mm::Vec3 &size, const mm::Col4 &color);

} // namespace debug
} // namespace fw
