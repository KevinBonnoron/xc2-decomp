#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"

namespace ui {

class UIInputPad;
class UIInputPointer;
class UIInputWheel;

class IUIInputSelectionChecker {
public:
  virtual bool isEnableSelect(u32 handle, int index) = 0;
};

class UIInputLayer : public mm::mtl::ReferenceObject {
public:
  struct InputAction {
    u16 unknown00;    // Inferred role: pad; original member name unknown.
    u16 unknown02;    // Inferred role: act id; original member name unknown.
    u16 unknown04[4]; // Inferred role: text; original member name unknown.
    bool unknown0c;   // Inferred role: repeat; original member name unknown.
    bool unknown0d;   // Inferred role: enable; original member name unknown.
  };

  struct InputSetup {
    mm::mtl::FixedVector<InputAction, 27> unknown00; // Inferred role: actions; original member name unknown.
  };

  UIInputLayer(u32 handle, u32 priority, const InputSetup &setup);
  virtual ~UIInputLayer();
  bool update();
  void setupSelection(int index, u32 size);
  void resetSelection();
  bool changeSelect(int index, u8 cause);
  bool isEnableSelect(int index);
  void setActionEnable(u16 actId, bool enable);
  bool getActionEnable(u16 actId);
  virtual const EventData *getInputEventExt() = 0;
  virtual bool hasEventExt() const;
  virtual void clear();
  virtual void clearExt();
  virtual UIInputPad *castUIInputPad();
  virtual UIInputWheel *castUIInputWheel();
  virtual UIInputPointer *castUIInputPointer();
  virtual bool updateImpl() = 0;

  u32 unknown0c;                        // Inferred role: priority; original member name unknown.
  EventData unknown10;                  // Inferred role: event; original member name unknown.
  EventData unknown28;                  // Inferred role: action event; original member name unknown.
  u32 unknown40;                        // Inferred role: handle; original member name unknown.
  u32 unknown44;                        // Inferred role: select size; original member name unknown.
  int unknown48;                        // Inferred role: select index; original member name unknown.
  bool unknown4c;                       // Inferred role: select enable; original member name unknown.
  InputSetup unknown50;                 // Inferred role: setup; original member name unknown.
  IUIInputSelectionChecker *unknown1d8; // Inferred role: selection checker; original member name unknown.
};

static_assert(sizeof(UIInputLayer::InputAction) == 0x0e, "");
static_assert(sizeof(UIInputLayer::InputSetup) == 0x188, "");
static_assert(offsetof(UIInputLayer, unknown0c) == 0x0c, "");
static_assert(offsetof(UIInputLayer, unknown10) == 0x10, "");
static_assert(offsetof(UIInputLayer, unknown28) == 0x28, "");
static_assert(offsetof(UIInputLayer, unknown40) == 0x40, "");
static_assert(offsetof(UIInputLayer, unknown44) == 0x44, "");
static_assert(offsetof(UIInputLayer, unknown48) == 0x48, "");
static_assert(offsetof(UIInputLayer, unknown4c) == 0x4c, "");
static_assert(offsetof(UIInputLayer, unknown50) == 0x50, "");
static_assert(offsetof(UIInputLayer, unknown1d8) == 0x1d8, "");
static_assert(sizeof(UIInputLayer) == 0x1e0, "");

} // namespace ui
