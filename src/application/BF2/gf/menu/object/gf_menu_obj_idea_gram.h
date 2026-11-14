#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;
struct SDataIdea;

class GfMenuObjIdeaGram : public GfMenuObject {
public:
  struct OpenParam {
    u32 unknown00;         // Inferred role: object holding the layout of the displayed idea gram; original member name unknown.
    const char *unknown08; // Inferred role: layout name; original member name unknown.
    u32 unknown10;         // Inferred role: event parameter; original member name unknown.
  };

  class MainListener : public ui::UIObjectListener {
  public:
    MainListener() : _0c(), _20() {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    u8 _20[0x68 - 0x20];
  };

  GfMenuObjIdeaGram(u32 handle);
  ~GfMenuObjIdeaGram() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void open(GfMenuCallContext *context, const OpenParam &param);
  static void close(GfMenuCallContext *context, f32 time);
  static void setIdeaPoint(GfMenuCallContext *context, u8 type, u32 point);
  static void setIdeaPointFromDriver(GfMenuCallContext *context, u32 driver);
  static void setIdeaPointFromData(GfMenuCallContext *context, const SDataIdea &data);
  static void setIdeaPointFromBlade(GfMenuCallContext *context, u32 blade);
  static void addIdeaPoint(GfMenuCallContext *context, u8 type, int value, bool flag);
  static void addIdeaLevel(GfMenuCallContext *context, u8 type, int value, bool flag);
};

static_assert(offsetof(GfMenuObjIdeaGram::OpenParam, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjIdeaGram::OpenParam, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuObjIdeaGram::MainListener) == 0x68, "");

} // namespace gf
