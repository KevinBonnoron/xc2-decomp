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
    u16 pad;
    u16 actId;
    u16 text[4];
    bool repeat;
    bool enable;
  };

  struct InputSetup {
    mm::mtl::FixedVector<InputAction, 27> actions;
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

  u32 priority;
  EventData event;
  EventData actionEvent;
  u32 handle;
  u32 selectSize;
  int selectIndex;
  bool selectEnable;
  InputSetup setup;
  IUIInputSelectionChecker *selectionChecker;
};

static_assert(sizeof(UIInputLayer::InputAction) == 0x0e, "");
static_assert(sizeof(UIInputLayer::InputSetup) == 0x188, "");
static_assert(offsetof(UIInputLayer, priority) == 0x0c, "");
static_assert(offsetof(UIInputLayer, event) == 0x10, "");
static_assert(offsetof(UIInputLayer, actionEvent) == 0x28, "");
static_assert(offsetof(UIInputLayer, handle) == 0x40, "");
static_assert(offsetof(UIInputLayer, selectSize) == 0x44, "");
static_assert(offsetof(UIInputLayer, selectIndex) == 0x48, "");
static_assert(offsetof(UIInputLayer, selectEnable) == 0x4c, "");
static_assert(offsetof(UIInputLayer, setup) == 0x50, "");
static_assert(offsetof(UIInputLayer, selectionChecker) == 0x1d8, "");
static_assert(sizeof(UIInputLayer) == 0x1e0, "");

} // namespace ui
