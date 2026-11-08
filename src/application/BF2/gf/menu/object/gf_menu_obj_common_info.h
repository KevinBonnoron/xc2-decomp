#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_many_objects.h"
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjCommonInfo : public GfMenuObject {
public:
  class ParamBase;

  // Queued by GfMenuManyObjects. The game's sendOpen calls two virtuals of the parameter at 0x10 to get the texts.
  struct CommonInfo : GfMenuManyObjects::InfoType {
    ParamBase *unknown10; // Inferred role: parameter of the popup; original member name unknown.
  };

  GfMenuObjCommonInfo(u32 handle);
  ~GfMenuObjCommonInfo() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void close(u32);
  static void closeAll();
  static void pausePickup();
  static void continuePickup();
};

static_assert(offsetof(GfMenuObjCommonInfo::CommonInfo, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuObjCommonInfo::CommonInfo) == 0x18, "");

} // namespace gf
