#pragma once
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace event {

class CharaObj;

class Group {
public:
  static constexpr u32 CHARA_COUNT = 128;

  Group();
  virtual ~Group() {}
  bool empty() const { return unknown08.empty(); }
  void clear();
  void push(const CharaObj *chara);
  void pop(const CharaObj *chara);
  void update(bool isUpdateDir);
  void updatePos_Radius();
  void updateDir();

private:
  mm::mtl::FixedVector<const CharaObj *, CHARA_COUNT> unknown08; // Inferred role: charas; original member name unknown.
  mm::Vec3 unknown410;                                           // Inferred role: pos; original member name unknown.
  f32 unknown420;                                                // Inferred role: radius; original member name unknown.
  f32 unknown424;                                                // Inferred role: dir; original member name unknown.
};

static_assert(sizeof(Group) == 0x430, "");

} // namespace event
