#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace event {

class RandCalc {
public:
  static constexpr u32 TALK_COUNT = 1024;

  static int calc(int type);
  static void listup(mm::mtl::FixedVector<int, TALK_COUNT> &list);
  static void listupType(mm::mtl::FixedVector<int, TALK_COUNT> &list, mm::mtl::FixedVector<int, TALK_COUNT> &source, int type);
  static void listupParty(mm::mtl::FixedVector<int, TALK_COUNT> &list, mm::mtl::FixedVector<int, TALK_COUNT> &source);
  static void listupRand(mm::mtl::FixedVector<int, TALK_COUNT> &list, mm::mtl::FixedVector<int, TALK_COUNT> &source);
  static bool exist(int id);
  static void dump(mm::mtl::FixedVector<int, TALK_COUNT> &list);
};

} // namespace event
