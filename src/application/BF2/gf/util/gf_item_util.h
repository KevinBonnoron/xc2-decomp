#pragma once
#include "types.h"

namespace gf {

class GfItemUtil {
public:
  static u32 getItemBoxCount(u32 item);
  static u32 getCountByItemCategory(u32 category);
  static void addItemBox(u32 item, int count);
  static u32 getEnableStock(u32 item);
};

} // namespace gf
