#pragma once
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIShape {
public:
  static mm::mtl::RTTI m_rtti;

  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~UIShape();
  virtual void update(u32 frame);
};

} // namespace ui
