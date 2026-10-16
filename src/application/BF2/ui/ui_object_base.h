#pragma once
#include <stddef.h>

#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ui_displayinfo.h"
#include "ui/ui_transform.h"

namespace ui {

enum UIObjectFlag {
  UI_OBJECT_FLAG_CONTROL = 0,
  UI_OBJECT_FLAG_TERM = 3,
  UI_OBJECT_FLAG_DUPLICATE = 4,
  UI_OBJECT_FLAG_STREAM_IMAGE = 6,
  UI_OBJECT_FLAG_STREAMING = 7,
  UI_OBJECT_FLAG_NOT_INPUT_TARGET = 9,
  UI_OBJECT_FLAG_IGNORE_ROT = 10,
  UI_OBJECT_FLAG_SCREEN_ADJUSTING = 11,
  UI_OBJECT_FLAG_ALWAYS_IN_LAYOUT = 12,
  UI_OBJECT_FLAG_IGNORE_SIZE = 13,
  UI_OBJECT_FLAG_SUSPEND = 15,
  UI_OBJECT_FLAG_STREAM_IMAGE_2ND = 17,
};

class UIObjectBase : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNodeBase {
public:
  UIObjectBase(const mm::mtl::FixStr<32> &name);
  virtual ~UIObjectBase();
  virtual void update();
  virtual void setInitialize();
  virtual void setTerm();
  void setSuspend(bool suspend);

  bool isTerm() const { return flags.test(UI_OBJECT_FLAG_TERM); }

  UITransform transform;
  UIDisplayInfo displayInfo;
  mm::mtl::BitFlag<32> flags;
  u16 duplicateIndex;
  mm::mtl::FixStr<32> name;
};

static_assert(offsetof(UIObjectBase, transform) == 0x20, "");
static_assert(offsetof(UIObjectBase, displayInfo) == 0x50, "");
static_assert(offsetof(UIObjectBase, flags) == 0x98, "");
static_assert(offsetof(UIObjectBase, duplicateIndex) == 0x9c, "");
static_assert(offsetof(UIObjectBase, name) == 0xa0, "");
static_assert(sizeof(UIObjectBase) == 0xc8, "");

} // namespace ui
