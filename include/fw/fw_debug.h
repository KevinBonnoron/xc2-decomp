#pragma once

namespace mm {
struct Col4;
template <typename T> struct Rect;
} // namespace mm

namespace fw {
namespace debug {

void drawFont(int x, int y, const char *format, ...);
void drawFontColor(const mm::Col4 &color);
int drawFontGetHeight();
void drawSquare2D(const mm::Rect<int> &rect, const mm::Col4 &color);
void drawLineSquare2D(const mm::Rect<int> &rect, const mm::Col4 &color);

} // namespace debug
} // namespace fw
