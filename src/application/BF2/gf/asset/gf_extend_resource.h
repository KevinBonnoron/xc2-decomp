#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

// Extension object stored per asset (AssetPackInfo::setExtendResource). The game has no destructor or getRTTI
// symbol for it, only m_rtti: its virtual functions are inline.
class GfExtendResource {
public:
  static mm::mtl::RTTI m_rtti;

  explicit GfExtendResource(u32 kind) : unknown08(kind) {}
  virtual ~GfExtendResource() {}
  virtual const mm::mtl::RTTI *getRTTI() const { return &m_rtti; }

  u32 unknown08; // Inferred role: kind of extension, 1 for GfExtendPacking (its constructor); original member name unknown.
};

static_assert(offsetof(GfExtendResource, unknown08) == 0x08, "");
static_assert(sizeof(GfExtendResource) == 0x10, "");

} // namespace gf
