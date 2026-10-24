#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuFieldPosAdapter : public GfMenuAdapter {
public:
  GfMenuFieldPosAdapter(ui::UIObjectPlugin *plugin);
  ~GfMenuFieldPosAdapter() override;
  static GfMenuFieldPosAdapter *create(u32 handle, const mm::Vec3 &pos);
  void update(const fw::UpdateInfo &info) override;

  mm::Vec3 unknown30; // Inferred role: pos; original member name unknown.
  bool unknown40;     // Inferred role: out of screen; original member name unknown.
  u32 unknown44;      // Inferred role: handle; original member name unknown.
  bool unknown48;     // Inferred role: first update; original member name unknown.
};

static_assert(offsetof(GfMenuFieldPosAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuFieldPosAdapter, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuFieldPosAdapter, unknown44) == 0x44, "");
static_assert(offsetof(GfMenuFieldPosAdapter, unknown48) == 0x48, "");
static_assert(sizeof(GfMenuFieldPosAdapter) == 0x50, "");

} // namespace gf
