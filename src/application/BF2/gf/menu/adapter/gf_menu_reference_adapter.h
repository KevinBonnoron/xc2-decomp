#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuReferenceAdapter : public GfMenuAdapter {
public:
  GfMenuReferenceAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuReferenceAdapter() override;
  static GfMenuReferenceAdapter *create(u32 handle, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown30; // Inferred role: reference; original member name unknown.
  int unknown38;                                          // Inferred role: last number; original member name unknown.
  int unknown3c;                                          // Inferred role: last max; original member name unknown.
  int unknown40;                                          // Inferred role: last min; original member name unknown.
  int unknown44;                                          // Inferred role: offset; original member name unknown.
};

static_assert(offsetof(GfMenuReferenceAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuReferenceAdapter, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuReferenceAdapter, unknown3c) == 0x3c, "");
static_assert(offsetof(GfMenuReferenceAdapter, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuReferenceAdapter, unknown44) == 0x44, "");
static_assert(sizeof(GfMenuReferenceAdapter) == 0x48, "");

} // namespace gf
