#pragma once
#include "event/anm_base.h"
#include "event/curve.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include <stddef.h>

namespace event {

class AnmCol : public AnmBase {
public:
  AnmCol();
  virtual ~AnmCol() {}
  void clear();
  void update(f32 delta);
  mm::Col4 calcEvalute(size_t index, f32 alpha) const;
  void replay();
  void append(f32 frame, const mm::Col4 &value, CV_TYPE cv);
  size_t count() const;
  const mm::Col4 &getValue() const { return unknown1c8; }

private:
  mm::mtl::FixedVector<mm::Col4, KEY_COUNT> unknown78; // Inferred role: values; original member name unknown.
  mm::mtl::FixedVector<CV_TYPE, KEY_COUNT> unknown180; // Inferred role: cvs; original member name unknown.
  mm::Col4 unknown1c8;                                 // Inferred role: value; original member name unknown.
};

static_assert(sizeof(AnmCol) == 0x1d8, "");

} // namespace event
