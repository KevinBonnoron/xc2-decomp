#pragma once

namespace mm {
template <typename T> struct Pnt;
template <typename T> struct Rect;
struct Vec3;
} // namespace mm

namespace ml {

class DebDraw;
class Scn;
class WinView;

class ScnUtil {
public:
  static bool setPerspective(const Scn *scn, DebDraw *debDraw, const WinView *view);
  static bool checkLineRect(const mm::Vec3 &start, const mm::Vec3 &end, const mm::Rect<int> &rect);
  static bool checkPointPos4(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third, const mm::Vec3 &fourth, const mm::Pnt<int> &point);
  static bool isCrossLine(const mm::Pnt<int> &a, const mm::Pnt<int> &b, const mm::Pnt<int> &c, const mm::Pnt<int> &d);
};

} // namespace ml
