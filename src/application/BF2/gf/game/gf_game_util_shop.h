#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

struct ShopTaskInfo {
  ShopTaskInfo() : unknown48(0) {}

  mm::mtl::FixedVector<u32, 16> unknown00; // Inferred role: task sets of the change shop; original member name unknown.
  u32 unknown48;                           // Inferred role: change shop table; original member name unknown.
};

class GfGameUtilShop {
public:
  static void execPayInn(u32 shop, u32 money, bool isDouble);
  static u32 getNeedMoneyForInn(u32 shop);
  static bool getChangeTask(ShopTaskInfo &info, u32 shop);
};

} // namespace gf
