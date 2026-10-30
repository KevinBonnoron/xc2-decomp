#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace mm {
struct Vec3;
} // namespace mm

namespace ui {
class UIObjectPlugin;
class UIStr;
struct uiDateTime;
} // namespace ui

namespace gf {

struct ElapseTime;

class GfMenuRewriteNumber : public mm::mtl::ReferenceObject {
public:
  int unknown0c;  // Inferred role: number; original member name unknown.
  bool unknown10; // Inferred role: rewrite; original member name unknown.
};

static_assert(offsetof(GfMenuRewriteNumber, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuRewriteNumber, unknown10) == 0x10, "");

class GfMenuAdapter : public mm::mtl::IntrusiveListNode<GfMenuAdapter> {
public:
  // Inferred role: plugin type; original type name unknown.
  enum unknown004 {
    unknown004_0, // Inferred role: number; original name unknown.
    unknown004_1, // Inferred role: image; original name unknown.
    unknown004_2, // Inferred role: text; original name unknown.
    unknown004_3, // Inferred role: disp; original name unknown.
    unknown004_4, // Inferred role: pos; original name unknown.
    unknown004_5, // Inferred role: world pos; original name unknown.
    unknown004_6, // Inferred role: offset; original name unknown.
    unknown004_7, // Inferred role: time; original name unknown.
    unknown004_8, // Inferred role: color; original name unknown.
    unknown004_9, // Inferred role: pattern; original name unknown.
  };

  struct PluginSetup {
    unknown004 unknown00; // Inferred role: type; original member name unknown.
    int unknown04;        // Inferred role: param; original member name unknown.
    int unknown08;        // Inferred role: max; original member name unknown.
  };

  enum {
    FLAG_CHANGED = 1 << 0,
    FLAG_UPDATE_ALWAYS = 1 << 1,
  };

  // Inferred role: compare result; original type name unknown.
  enum unknown005 {
    unknown005_0, // Inferred role: same; original name unknown.
    unknown005_1, // Inferred role: less; original name unknown.
    unknown005_2, // Inferred role: greater; original name unknown.
  };

  GfMenuAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAfter, bool isUpdateAlways);
  virtual ~GfMenuAdapter();
  void setChange();
  void setUpdateAfter();
  static ui::UIObjectPlugin *createPlugin(u32 handle, const PluginSetup &setup);
  static unknown005 compare(GfMenuAdapter *adapter, GfMenuAdapter *other);
  void attachPlugin(ui::UIObjectPlugin *plugin);
  void setDispAlphaMode(bool isAlphaMode);
  void setDispReverseMode(bool isReverseMode);
  void setDispFadeMode(f32 fadeTime);
  void setDispSuspendMode(bool isSuspendMode);
  void setNumberReverseMode(bool isReverseMode);
  void setNumberInterpolateMode(f32 time);
  void setPosAdjustScreen(bool isAdjustScreen);
  void setPosAdjustSize(u32 width, u32 height);
  void setPosAdjustSizeOffs(s16 x, s16 y);
  void setPosOffsMode(u32 mode);
  void setOffsetLimit(u16 x, u16 y);
  bool checkOwner(u32 handle);
  int getNumber() const;
  int getNumberMin() const;
  int getNumberMax() const;
  void setRewriteNumber(GfMenuRewriteNumber *rewriteNumber);
  void setNumber(int number);
  void setNumberMin(int min);
  void setNumberMax(int max);
  void setText(const ui::UIStr &text);
  void setDisp(bool isDisp);
  void setPos(const mm::Pnt<s16> &pos);
  void setPosWorld(const mm::Vec3 &pos);
  void setOffsetTargetPos(const mm::Pnt<s16> &pos);
  bool isPosScreenAdjust() const;
  void setTime(const ui::uiDateTime &time);
  void setElapseTime(const ElapseTime &time);
  void setMulColor(const char *name);
  void setAddColor(const char *name);
  void setColorMode(u32 mode);
  bool isUpdateAlways() const;
  void setColor(const char *name);
  void setTextFacePattern(const char *name);
  virtual void update(const fw::UpdateInfo &info);

  ui::UIObjectPlugin *unknown18;  // Inferred role: plugin; original member name unknown.
  u32 unknown20;                  // Inferred role: flags; original member name unknown.
  u32 unknown24;                  // Inferred role: linked object; original member name unknown.
  GfMenuRewriteNumber *unknown28; // Inferred role: rewrite number; original member name unknown.
};

static_assert(offsetof(GfMenuAdapter, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuAdapter, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuAdapter, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuAdapter) == 0x30, "");

} // namespace gf
