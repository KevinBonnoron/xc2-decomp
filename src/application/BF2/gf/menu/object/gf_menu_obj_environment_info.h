#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjEnvironmentInfo : public GfMenuObject {
public:
  static void close();
  static void open();
  static void disable();
  static void enable();
  static void createAdapter(u32 handle, const char *name, u32 type);
  GfMenuObjEnvironmentInfo(u32 handle);
  ~GfMenuObjEnvironmentInfo() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
