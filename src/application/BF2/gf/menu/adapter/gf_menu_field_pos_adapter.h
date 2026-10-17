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

  mm::Vec3 pos;
  bool isOutOfScreen;
  u32 handle;
  bool isFirstUpdate;
};

static_assert(offsetof(GfMenuFieldPosAdapter, pos) == 0x30, "");
static_assert(offsetof(GfMenuFieldPosAdapter, isOutOfScreen) == 0x40, "");
static_assert(offsetof(GfMenuFieldPosAdapter, handle) == 0x44, "");
static_assert(offsetof(GfMenuFieldPosAdapter, isFirstUpdate) == 0x48, "");
static_assert(sizeof(GfMenuFieldPosAdapter) == 0x50, "");

} // namespace gf
