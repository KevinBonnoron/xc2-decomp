#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/input/ui_input_layer.h"

namespace mm {
namespace mtl {
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace ui {

class UIInputPointer : public UIInputLayer {
public:
  struct SelectionSetup {
    u64 unknown00;                       // Role and original member name unknown.
    u64 unknown08;                       // Role and original member name unknown.
    mm::mtl::ReferenceObject *unknown10; // Inferred role: list; original member name unknown.
  };

  struct PointerSetup;

  UIInputPointer(u32 handle, u32 priority, const PointerSetup &setup);
  virtual ~UIInputPointer();
  void setupPointerSelection(const SelectionSetup &setup);
  void changePointerPos(const mm::Pnt<s16> &pos);
  void changeRegionScale(f32 scale);
  void changeRegionRect(const mm::Rect<s16> &rect);
  virtual const EventData *getInputEventExt();
  virtual bool hasEventExt() const;
  virtual void clearExt();
  virtual UIInputPointer *castUIInputPointer();

  u8 unknown1e0[0x1e8 - 0x1e0]; // Inferred role: pointer setup; original member names unknown.
  SelectionSetup unknown1e8;    // Inferred role: selection setup; original member name unknown.
  u16 unknown200;               // Role and original member name unknown.
  u16 unknown202;               // Role and original member name unknown.
  u32 unknown204;               // Inferred role: pointer position; original member name unknown.
  u8 unknown208[0x210 - 0x208];
  f32 unknown210; // Inferred role: pointer direction x; original member name unknown.
  f32 unknown214; // Inferred role: pointer direction y; original member name unknown.
  u8 unknown218[0x220 - 0x218];
  bool unknown220; // Inferred role: selection changed; original member name unknown.
  u8 unknown221[0x224 - 0x221];
  f32 unknown224;       // Inferred role: scale; original member name unknown.
  EventData unknown228; // Inferred role: input event; original member name unknown.
  bool unknown240;      // Inferred role: pending pointer position; original member name unknown.
  u8 unknown241[0x242 - 0x241];
  mm::Pnt<s16> unknown242; // Inferred role: pending pointer position; original member name unknown.
  bool unknown246;         // Inferred role: pending region scale; original member name unknown.
  u8 unknown247[0x248 - 0x247];
  f32 unknown248;  // Inferred role: region scale; original member name unknown.
  bool unknown24c; // Inferred role: pending region rect; original member name unknown.
  u8 unknown24d[0x24e - 0x24d];
  mm::Rect<s16> unknown24e; // Inferred role: region rect; original member name unknown.
  u8 unknown256[0x260 - 0x256];
};

static_assert(offsetof(UIInputPointer, unknown1e8) == 0x1e8, "");
static_assert(offsetof(UIInputPointer, unknown204) == 0x204, "");
static_assert(offsetof(UIInputPointer, unknown224) == 0x224, "");
static_assert(offsetof(UIInputPointer, unknown228) == 0x228, "");
static_assert(offsetof(UIInputPointer, unknown242) == 0x242, "");
static_assert(offsetof(UIInputPointer, unknown248) == 0x248, "");
static_assert(offsetof(UIInputPointer, unknown24e) == 0x24e, "");
static_assert(sizeof(UIInputPointer) == 0x260, "");

} // namespace ui
