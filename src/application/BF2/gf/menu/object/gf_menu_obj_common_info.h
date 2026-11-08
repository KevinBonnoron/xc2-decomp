#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_many_objects.h"
#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjCommonInfo : public GfMenuObject {
public:
  class ParamBase {
  public:
    ParamBase() : unknown08(0) {}
    virtual ~ParamBase() {}
    virtual ui::UIStr getTitleString() const = 0;
    virtual ui::UIStr getContentsString() const = 0;

    u32 unknown08; // Inferred role: kind of parameter; original member name unknown.
  };

  class ParamAchivement : public ParamBase {
  public:
    ParamAchivement() : unknown0c(0), unknown10(0), unknown14(0) {}
    ~ParamAchivement() override {}
    ui::UIStr getTitleString() const override;
    ui::UIStr getContentsString() const override;

    u32 unknown0c; // Inferred role: achievement parameter; original member name unknown.
    u32 unknown10; // Inferred role: achievement parameter; original member name unknown.
    u32 unknown14; // Inferred role: achievement parameter; original member name unknown.
  };

  // Queued by GfMenuManyObjects. The game's sendOpen calls two virtuals of the parameter at 0x10 to get the texts.
  struct CommonInfo : GfMenuManyObjects::InfoType {
    ParamBase *unknown10; // Inferred role: parameter of the popup; original member name unknown.
  };

  GfMenuObjCommonInfo(u32 handle);
  ~GfMenuObjCommonInfo() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static ParamBase *createParamAchivement(u32 param0, u32 param1, u32 param2);
  static void removeObject(ui::UIObjectAcc acc);
  static void sendOpen(u32 handle, const CommonInfo &info);
  static u32 open(GfMenuCallContext *context, ParamBase *param);
  static void close(u32);
  static void closeAll();
  static void pausePickup();
  static void continuePickup();
};

static_assert(offsetof(GfMenuObjCommonInfo::CommonInfo, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuObjCommonInfo::CommonInfo) == 0x18, "");

} // namespace gf
