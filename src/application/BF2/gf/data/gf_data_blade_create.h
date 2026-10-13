#pragma once
#include "types.h"

namespace gf {

class GfDataBladeCreate {
public:
  static u32 getRareBladeAppearType();
  static void setRareBladeAppearType(u32 rareBladeAppearType);

  static void addAssurePoint(u32 amount);
  static u32 getAssurePoint();
  static void resetAssurePoint();

  static void addAssureCount(u32 amount);
  static u32 getAssureCount();
  static void resetAssureCount();
};

} // namespace gf
