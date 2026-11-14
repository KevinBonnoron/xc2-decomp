#pragma once

namespace mm {

template <typename T> struct Pnt {
  Pnt() {}
  Pnt(T x, T y) : x(x), y(y) {}
  Pnt(const Pnt &other) : x(other.x), y(other.y) {}

  // Inferred: no game symbol (inlined everywhere). ml::ScnObjCam::setSize (0x7100742938) compares its size member with a Pnt<int> through
  // references to the ints: clang 3.9 gives the loads the alignment of this struct (4) and so cannot merge the two members of the 16-aligned
  // RENDER_INFO into one 64-bit load. With the members compared directly (`a.x != b.x || a.y != b.y`) setSize has the game's 26
  // instructions but one 64-bit load and a shift (ldr x10 at +0x4, lsr at +0x14) instead of the two 32-bit loads; with the two plain
  // assignments instead of `set` as well, 23 instructions.
  bool operator!=(const Pnt &other) const { return x != other.x || y != other.y; }

  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
  // No game symbol (inlined). Single user: ml::ScnObjCam::setSize (0x7100742938), which copies the two ints one by one
  // (the second is read again after the first store) and tests them afterwards. The game keeps the two stores of the aspect apart there
  // (two tail calls to updateViewMatrix) and merges them in the copy inlined in ml::ScnCamMan::update (0x71007418ac): that needs the copy
  // to come from an inlined member, so that the test of the second int is only folded by GVN, after MergedLoadStoreMotion has run. Forms
  // tried: the two assignments written in setSize (23 instructions against 26, stores merged), updateViewMatrix called in both branches
  // (setSize matches, ScnCamMan::update gets 110 against 108), a user operator= (matches both, but Rect<T> keeps Pnt in a union and 17
  // functions copy a Pnt as one load and store).
  void set(const Pnt &other) {
    x = other.x;
    y = other.y;
  }

  static const Pnt zero; // Name from the game symbol _ZN2mm3PntIiE4zeroE; also in torna and xc1de.

  T x;
  T y;
};

} // namespace mm
