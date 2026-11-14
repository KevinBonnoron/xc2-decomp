#pragma once
#include <stddef.h>

#include "ml/dev_base.h"
#include "ml/reslist.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace ml {
class DevFontLayer;
enum FONT_STYLE : int;
class WorkObj;

// Only the vtable slots called by DevFont are known.
class IDevFontInfo {
public:
  virtual ~IDevFontInfo() {}
  virtual FONT_STYLE unknown10() const = 0; // Inferred role: font style; original name unknown.
  virtual void unknown18() = 0;             // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
  virtual void unknown20() = 0;             // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
  virtual void unknown28() = 0;             // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
  virtual void unknown30() = 0;             // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
  virtual void unknown38() = 0;             // Inferred role: per-frame update, called for every font by DevFont::wkUpdate (0x71007116d4); original name unknown.
  virtual void unknown40() = 0;             // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
  virtual bool unknown48() const = 0;       // Inferred role: font skipped by getFont when set; original name unknown.
  virtual bool unknown50() = 0;             // Inferred role: tells DevFont::wkUpdate (0x710071170c) to delete the font; original name unknown.
};

class FontLayer {
public:
  FontLayer();
  virtual ~FontLayer();
  void font(int x, int y, const char *format, ...);
  void fontColor(const mm::Col4 &color);
  void fontBack(const mm::Col4 &color);
  void fontShadow(bool isShadow);
  void fontFlush(bool isFlush);
  void fontScale(f32 x, f32 y);
  void fontStyle(FONT_STYLE style);
  void fontZ(u32 z);
  void fontSetMaxQue(u32 maxQue);
  u32 fontGef32gth(const char *text) const; // The name is the game's own (_ZNK2ml9FontLayer12fontGef32gthEPKc, 0x710072169c), not a typo of this reconstruction.
  u32 fontGetWidth(const char *text) const;
  u32 fontGetHeight() const;
  const mm::Col4 &fontGetColor() const;

  DevFontLayer *unknown08; // Inferred role: layer work created by DevFont::createLayer; original member name unknown.
};

class DevFont : public FontLayer, public DevBase, public mm::mtl::PtrSingleton<DevFont> {
public:
  DevFont(const char *name, WorkObj *parent);
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  void wkUpdate() override;
  void wkTail() override;
  virtual bool createFont() = 0;
  virtual bool releaseFont() = 0;
  static bool isInitialized();
  static DevFontLayer *createLayer(const FontLayer *layer);
  static bool releaseLayer(const FontLayer *layer);
  DevFontLayer *getFontLayer(const FontLayer *layer);
  const DevFontLayer *getFontLayer(const FontLayer *layer) const;
  static void fontLayerSetMaxQue(const FontLayer *layer, u32 maxQue);
  static void fontLayer(const FontLayer *layer, int x, int y, const char *text);
  static u32 fontLayerGetWidth(const FontLayer *layer, const char *text);
  static u32 fontLayerGetHeight(const FontLayer *layer);
  static const mm::Col4 &fontLayerGetColor(const FontLayer *layer);
  static void fontLayerColor(const FontLayer *layer, const mm::Col4 &color);
  static void fontLayerBack(const FontLayer *layer, const mm::Col4 &color);
  static void fontLayerShadow(const FontLayer *layer, bool isShadow);
  static void fontLayerFlush(const FontLayer *layer, bool isFlush);
  static void fontLayerScale(const FontLayer *layer, f32 x, f32 y);
  static void fontLayerStyle(const FontLayer *layer, FONT_STYLE style);
  static void fontLayerZ(const FontLayer *layer, u32 z);
  static IDevFontInfo *getFont(FONT_STYLE style);
  static bool isStyleValid(FONT_STYLE style);
  static bool createFont(FONT_STYLE style, void *data);

  reslist<IDevFontInfo *> unknown1c8; // Inferred role: font infos; original member name unknown.
};

static_assert(offsetof(DevFont, unknown1c8) == 0x1c8, "");
static_assert(sizeof(DevFont) == 0x208, "");

} // namespace ml
