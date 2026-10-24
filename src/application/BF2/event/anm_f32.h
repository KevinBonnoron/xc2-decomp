#pragma once
#include "event/anm_base.h"
#include "event/curve.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include <stddef.h>

namespace event {

class AnmF32 : public AnmBase {
public:
  AnmF32();
  virtual ~AnmF32() {}
  void clear();
  void update(f32 delta);
  f32 calcEvalute(size_t index, f32 alpha) const;
  void replay();
  void append(f32 frame, f32 value, CV_TYPE cv);
  size_t count() const;
  CV_TYPE getCv(size_t index) const;
  f32 getValue(size_t index) const;
  void setValue(size_t index, f32 value);
  f32 getValue() const { return unknown108; }

private:
  mm::mtl::FixedVector<f32, KEY_COUNT> unknown78;     // Inferred role: values; original member name unknown.
  mm::mtl::FixedVector<CV_TYPE, KEY_COUNT> unknownc0; // Inferred role: cvs; original member name unknown.
  f32 unknown108;                                     // Inferred role: value; original member name unknown.
};

static_assert(sizeof(AnmF32) == 0x110, "");

} // namespace event
