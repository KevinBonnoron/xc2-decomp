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

  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference;
  int lastNumber;
  int lastMax;
  int lastMin;
  int offset;
};

static_assert(offsetof(GfMenuReferenceAdapter, reference) == 0x30, "");
static_assert(offsetof(GfMenuReferenceAdapter, lastNumber) == 0x38, "");
static_assert(offsetof(GfMenuReferenceAdapter, lastMax) == 0x3c, "");
static_assert(offsetof(GfMenuReferenceAdapter, lastMin) == 0x40, "");
static_assert(offsetof(GfMenuReferenceAdapter, offset) == 0x44, "");
static_assert(sizeof(GfMenuReferenceAdapter) == 0x48, "");

} // namespace gf
