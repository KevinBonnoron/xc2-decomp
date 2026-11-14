#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace event {

class RandCalc {
public:
  static constexpr u32 TALK_UNKNOWN_1024 = 1024; // Inferred role: talk count; original name unknown.

  static int calc(int type);
  static void listup(mm::mtl::FixedVector<int, TALK_UNKNOWN_1024> &list);
  static void listupType(mm::mtl::FixedVector<int, TALK_UNKNOWN_1024> &list, mm::mtl::FixedVector<int, TALK_UNKNOWN_1024> &source, int type);
  static void listupParty(mm::mtl::FixedVector<int, TALK_UNKNOWN_1024> &list, mm::mtl::FixedVector<int, TALK_UNKNOWN_1024> &source);
  static void listupRand(mm::mtl::FixedVector<int, TALK_UNKNOWN_1024> &list, mm::mtl::FixedVector<int, TALK_UNKNOWN_1024> &source);
  static bool exist(int id);
  static void dump(mm::mtl::FixedVector<int, TALK_UNKNOWN_1024> &list);
};

} // namespace event
