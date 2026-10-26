#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfMenuObjActionWindow : public GfMenuObject {
public:
  struct OpenParam {
    GF_OBJ_HANDLE *unknown00; // Inferred role: target handle; original member name unknown.
    u32 unknown08;            // Inferred role: pad key; original member name unknown.
  };

  static void openBattle(const OpenParam &param);
  static void closeBattle();
  GfMenuObjActionWindow(u32 handle);
  ~GfMenuObjActionWindow() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  void eventHudSceneChange(u32 scene) override;
};

} // namespace gf
