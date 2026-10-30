#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfMenuObjEnemyStatus : public GfMenuObject {
public:
  struct OpenParam {
    GF_OBJ_HANDLE *unknown00; // Inferred role: enemy handle; original member name unknown.
  };

  static void open(const OpenParam &param);
  static void close();
  static void disp(bool isDisp);
  void initialize() override;
  void finalize() override;
};

} // namespace gf
