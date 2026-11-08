#pragma once
#include "gf/menu/gf_menu_many_objects.h"
#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfMenuObjChainIcon : public GfMenuObject {
public:
  // Queued by GfMenuManyObjects; the game gives it its own vtable, inheriting the dispose of the base.
  struct ChainIconInfo : GfMenuManyObjects::InfoType {};

  GfMenuObjChainIcon(u32 handle);
  ~GfMenuObjChainIcon() override;
  static void setupScreen(u32 handle, int unknown1, int unknown2, int unknown3, int unknown4);
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenParam {
    GF_OBJ_HANDLE *unknown00; // Inferred role: handle; original member name unknown.
  };

  static void open(const OpenParam &param);
  static void removeObject(ui::UIObjectAcc acc);
  static void close(u32 handle);
  static void closeAll();
};

static_assert(sizeof(GfMenuObjChainIcon::ChainIconInfo) == 0x10, "");

} // namespace gf
