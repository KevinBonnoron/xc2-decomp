#pragma once
#include <stddef.h>

#include "framework/coli/coli_object.h"
#include "gf/object/component/gf_component.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComCollider : public GfComponent, public fw::IColiEventListener {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 4;

  void enter(const EnterInfo &info) override;
  void leave(const LeaveInfo &info) override;

  mm::mtl::Vector<fw::ColiObject *> colis;
};

static_assert(offsetof(GfComCollider, colis) == 0x18, "");

} // namespace gf
