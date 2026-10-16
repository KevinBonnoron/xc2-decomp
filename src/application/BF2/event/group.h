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
  bool empty() const { return mCharas.empty(); }
  void clear();
  void push(const CharaObj *chara);
  void pop(const CharaObj *chara);
  void update(bool isUpdateDir);
  void updatePos_Radius();
  void updateDir();

private:
  mm::mtl::FixedVector<const CharaObj *, CHARA_COUNT> mCharas;
  mm::Vec3 mPos;
  f32 mRadius;
  f32 mDir;
};

static_assert(sizeof(Group) == 0x430, "");

} // namespace event
