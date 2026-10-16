#pragma once
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/map.h"
#include "types.h"

namespace ui {

class UITagConv {
public:
  typedef mm::mtl::FixedVector<mm::mtl::MapPair<const char *, const char *>, 8> ParamList;

  virtual ~UITagConv() {}
  virtual const char *getTagName() = 0;
  virtual const char *convBegin(const ParamList &params, u16 id) = 0;
  virtual const char *convEnd() { return nullptr; }
};

} // namespace ui
