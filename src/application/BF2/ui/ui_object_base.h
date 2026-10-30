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
  UI_OBJECT_FLAG_LISTENER = 1,
  UI_OBJECT_FLAG_TERM = 3,
  UI_OBJECT_FLAG_DUPLICATE = 4,
  UI_OBJECT_FLAG_STREAM_IMAGE = 6,
  UI_OBJECT_FLAG_STREAMING = 7,
  UI_OBJECT_FLAG_NOT_INPUT_TARGET = 9,
  UI_OBJECT_FLAG_IGNORE_ROT = 10,
  UI_OBJECT_FLAG_SCREEN_ADJUSTING = 11,
  UI_OBJECT_FLAG_ALWAYS_IN_LAYOUT = 12,
  UI_OBJECT_FLAG_IGNORE_SIZE = 13,
  UI_OBJECT_FLAG_MASK = 14,
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

  bool isTerm() const { return unknown98.test(UI_OBJECT_FLAG_TERM); }

  UITransform unknown20;             // Inferred role: transform; original member name unknown.
  UIDisplayInfo unknown50;           // Inferred role: display info; original member name unknown.
  mm::mtl::unknown027<32> unknown98; // Inferred role: flags; original member name unknown.
  u16 unknown9c;                     // Inferred role: duplicate index; original member name unknown.
  mm::mtl::FixStr<32> unknowna0;     // Inferred role: name; original member name unknown.
};

static_assert(offsetof(UIObjectBase, unknown20) == 0x20, "");
static_assert(offsetof(UIObjectBase, unknown50) == 0x50, "");
static_assert(offsetof(UIObjectBase, unknown98) == 0x98, "");
static_assert(offsetof(UIObjectBase, unknown9c) == 0x9c, "");
static_assert(offsetof(UIObjectBase, unknowna0) == 0xa0, "");
static_assert(sizeof(UIObjectBase) == 0xc8, "");

} // namespace ui
