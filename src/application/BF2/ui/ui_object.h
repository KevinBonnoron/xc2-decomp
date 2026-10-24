#pragma once
#include <stddef.h>

#include "layer/layer_acc_obj_base.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_list.h"
#include "types.h"
#include "ui/ui_object_base.h"
#include "ui/ui_object_param.h"

namespace layer {
class LayerBase;
}

namespace mm {
struct Col3;
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIDisplayInfo;
class UIObjectPlugin;
class UITransform;

enum UIObjectType {
  UI_OBJECT_TYPE_TEXT = 1,
  UI_OBJECT_TYPE_IMAGE = 2,
  UI_OBJECT_TYPE_LAYOUT = 3,
  UI_OBJECT_TYPE_SCREEN = 4,
  UI_OBJECT_TYPE_POLYGON = 5,
};

enum UIDisplayMode {
  UI_DISPLAY_MODE_TOP_LEFT = 0,
  UI_DISPLAY_MODE_CENTER = 1,
};

class UIObject : public UIObjectBase {
public:
  static mm::mtl::RTTI m_rtti;

  UIObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name, u32 type);
  virtual ~UIObject();
  virtual void update();
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual void apply();
  virtual void getDisplayOffset(u16 mode, mm::Pnt<s16> &offset) const;
  virtual void getTransformPosOffs(mm::Vec2 &offset) {
    offset.x = 0.0f;
    offset.y = 0.0f;
  }
  virtual u32 duplicateImpl(u32 parent) = 0;

  UIObject *getParentPtr() const;
  void updatePlugin();
  void applyTransform(const UIObjectParam::AdditionalParam &param);
  void applyDisplayInfo(const UIObjectParam::AdditionalParam &param);
  void setParent(u32 parent);
  void getPos(mm::Pnt<s16> &pos) const;
  void getPosCenter(mm::Pnt<s16> &pos) const;
  void setPos(const mm::Pnt<s16> &pos);
  void setPosCenter(const mm::Pnt<s16> &pos);
  void resetDirty();
  void attachPlugin(UIObjectPlugin *plugin);
  bool isPluginOwner(UIObjectPlugin *plugin) const;
  void registAdditionalParam(UIObjectParam *param);
  void unregistAdditionalParam(UIObjectParam *param);
  void switchDisplayMode(u16 mode);
  void setBlendType(u16 type);
  void setPriority(u16 priority);
  void setAddColor(const mm::Col3 &color);
  u32 duplicate(u32 parent);
  void setDebugDraw(bool debugDraw);
  bool isDebugDraw() const;

  static void importTransform(UITransform &transform, layer::LayerBase *layer);
  static void importDisplaySize(UIDisplayInfo &displayInfo, layer::LayerBase *layer);
  static void importDisplayInfo(UIDisplayInfo &displayInfo, layer::LayerBase *layer);

  bool isImageType() const { return unknownd8 == UI_OBJECT_TYPE_IMAGE || unknownd8 == UI_OBJECT_TYPE_SCREEN || unknownd8 == UI_OBJECT_TYPE_POLYGON; }

  layer::LayerBase *unknownc8;                     // Inferred role: layer; original member name unknown.
  layer::LayerAccObjBase unknownd0;                // Inferred role: layer acc; original member name unknown.
  u16 unknownd8;                                   // Inferred role: object type; original member name unknown.
  u16 unknownda;                                   // Inferred role: duplicate count; original member name unknown.
  u32 unknowndc;                                   // Inferred role: parent; original member name unknown.
  UIObjectPlugin *unknowne0;                       // Inferred role: plugins; original member name unknown.
  u32 unknowne8;                                   // Inferred role: handle; original member name unknown.
  u32 unknownec;                                   // Inferred role: name hash; original member name unknown.
  mm::mtl::IntrusiveList<UIObjectParam> unknownf0; // Inferred role: params; original member name unknown.
};

static_assert(offsetof(UIObject, unknownc8) == 0xc8, "");
static_assert(offsetof(UIObject, unknownd0) == 0xd0, "");
static_assert(offsetof(UIObject, unknownd8) == 0xd8, "");
static_assert(offsetof(UIObject, unknownda) == 0xda, "");
static_assert(offsetof(UIObject, unknowndc) == 0xdc, "");
static_assert(offsetof(UIObject, unknowne0) == 0xe0, "");
static_assert(offsetof(UIObject, unknowne8) == 0xe8, "");
static_assert(offsetof(UIObject, unknownec) == 0xec, "");
static_assert(offsetof(UIObject, unknownf0) == 0xf0, "");
static_assert(sizeof(UIObject) == 0x108, "");

} // namespace ui
