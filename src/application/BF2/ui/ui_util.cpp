#include "ui/ui_util.h"

#include "framework/memory/allocator.h"
#include "framework/pointer_map.h"
#include "fw/fw_bdat_manager.h"
#include "fw/fw_debug.h"
#include "fw/fw_pad.h"
#include "layer/layer_acc_manager.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "ui/event/ui_event_manager.h"
#include "ui/input/ui_input_manager.h"
#include "ui/input/ui_pad_read.h"
#include "ui/object/ui_image_object.h"
#include "ui/object/ui_layout_object.h"
#include "ui/object/ui_text_object.h"
#include "ui/ui_displayinfo.h"
#include "ui/ui_manager.h"
#include "ui/ui_object.h"
#include "ui/ui_object_acc.h"

namespace ui {

namespace {

const u32 UI_PAD_TO_FW_PAD[] = {
    0x0,  0x4,  0x2,   0x4,   0x2,   0x8,       0x1,       0x1000,    0x4000,    0x2000,     0x8000,     0x10,       0x40,       0x400,
    0x20, 0x80, 0x800, 0x200, 0x100, 0x1000000, 0x4000000, 0x2000000, 0x8000000, 0x10000000, 0x40000000, 0x20000000, 0x80000000,
};

UICtrlCurveLinear s_curveLinear;
UICtrlCurveLinearLoop s_curveLinearLoop;
UICtrlCurveSin90 s_curveSin90;
UICtrlCurveSin180 s_curveSin180;
UICtrlCurveSin90Rev s_curveSin90Rev;
UICtrlCurveSin180Rev s_curveSin180Rev;

} // namespace

void UIUtil::initLayerLib() {
  layer::LayerAccManager manager;
  manager.setCoordinate(layer::LAYER_COORDINATE_PIXEL);
}

void UIUtil::termLayerLib() {}

void UIUtil::initObjectMap(u32 size) {
  s_ObjPtrMap.reserve(&s_ProgAllocator, size);
  s_ObjPtrMax = size;
}

mm::mtl::IAllocator *UIUtil::getProgAllocator() { return &s_ProgAllocator; }

void UIUtil::termObjectMap() {
  s_ObjPtrMap.destroy();
  s_ObjPtrMax = 0;
}

u32 UIUtil::getObjectMapRegistNum() { return s_ObjPtrMax - s_ObjPtrMap.capacity + s_ObjPtrMap.count; }

u32 UIUtil::getObjectMapRegistMax() { return s_ObjPtrMax; }

u32 UIUtil::registObject(UIObject *object) { return s_ObjPtrMap.regist(object); }

void UIUtil::releaseObject(u32 handle) {
  UIObjectAcc acc(handle);
  if (acc.isValid()) {
    if (UIInputManager::get() != nullptr && acc.isDuplicate()) {
      u32 input = UIInputManager::get()->searchInputHandle(acc.handle);
      if (input != 0) {
        UIInputManager::get()->migrateInput(input, 0);
      }
    }
    if (UIEventManager::get() != nullptr) {
      UIEventManager::get()->removeObjectListener(handle);
    }
    s_ObjPtrMap.remove(handle);
  }
}

UIObject *UIUtil::getObject(u32 handle) { return static_cast<UIObject *>(s_ObjPtrMap.getPtr(handle)); }

UILayoutObject *UIUtil::getLayoutObject(u32 handle) {
  UIObject *object = getObject(handle);
  if (object == nullptr) {
    return nullptr;
  }
  return mm::mtl::dynamicCast<UILayoutObject>(object);
}

UIImageObject *UIUtil::getImageObject(u32 handle) {
  UIObject *object = getObject(handle);
  if (object == nullptr) {
    return nullptr;
  }
  return mm::mtl::dynamicCast<UIImageObject>(object);
}

UITextObject *UIUtil::getTextObject(u32 handle) {
  UIObject *object = getObject(handle);
  if (object == nullptr) {
    return nullptr;
  }
  return mm::mtl::dynamicCast<UITextObject>(object);
}

u32 UIUtil::getHandle(const UIObject *object) { return s_ObjPtrMap.getHandle(object); }

u32 UIUtil::searchChild(u32 handle, const char *name) {
  UILayoutObject *layout = getLayoutObject(handle);
  if (layout == nullptr) {
    return 0;
  }
  return layout->searchChild(name);
}

void UIUtil::setDisp(u32 handle, bool disp) {
  UIObject *object = getObject(handle);
  if (object != nullptr) {
    object->displayInfo.setDisp(disp);
  }
}

void UIUtil::setDispChild(u32 handle, bool disp, const char *name) {
  UILayoutObject *layout = getLayoutObject(handle);
  if (layout != nullptr) {
    u32 child = layout->searchChild(name);
    if (isValid(child)) {
      setDisp(child, disp);
    }
  }
}

bool UIUtil::isValid(u32 handle) { return s_ObjPtrMap.isValid(handle); }

bool UIUtil::isTerm(u32 handle) {
  if (!isValid(handle)) {
    return false;
  }
  return getObject(handle)->isTerm();
}

void UIUtil::drawDisplayRect(const UIObjectAcc &acc, const mm::Col4 &color) {
  mm::Rect<s16> rect;
  acc.getRect(rect, UIObjectAcc::RECT_GLOBAL | UIObjectAcc::RECT_SCALED);
  if (rect.width > 0 && rect.height > 0) {
    fw::debug::drawFontColor(color);
    fw::debug::drawLineSquare2D(mm::Rect<int>(rect.x, rect.y, rect.width, rect.height), color);
    {
      mm::mtl::FixStr<32> name(acc.getName());
      if (acc.isDuplicate()) {
        name.format("%s (%03d)", acc.getName(), acc.getDuplicateIndex());
      }
      fw::debug::drawFont(rect.x, rect.y - fw::debug::drawFontGetHeight(), "[%d,%d,%d,%d:%d] %s", rect.x, rect.y, rect.width, rect.height, acc.getDispPriority(), name.c_str());
    }

    mm::Pnt<s16> pos;
    acc.getPosDraw(pos);
    rect.width = 4;
    rect.height = 4;
    rect.x = pos.x - 2;
    rect.y = pos.y - 2;
    fw::debug::drawSquare2D(mm::Rect<int>(rect.x, rect.y, rect.width, rect.height), color);
  }
}

void UIUtil::initBdatFP() {
  s_BdatFPs[UI_BDAT_RES_IMAGE] = fw::BdatManager::getFp("MNU_ResImage");
  s_BdatFPs[UI_BDAT_RES_LAYOUT] = fw::BdatManager::getFp("MNU_ResLayout");
  s_BdatFPs[UI_BDAT_RES_FONT] = fw::BdatManager::getFp("MNU_ResFont");
  s_BdatFPs[UI_BDAT_RES_FONT_STYLE] = fw::BdatManager::getFp("MNU_ResFontStyle");
  s_BdatFPs[UI_BDAT_RES_MSPROJ] = fw::BdatManager::getFp("MNU_ResMSProj");
  s_BdatFPs[UI_BDAT_MENU_MS] = fw::BdatManager::getFp("menu_ms");
  s_BdatFPs[UI_BDAT_LAYER] = fw::BdatManager::getFp("MNU_Layer");
  s_BdatFPs[UI_BDAT_INPUT_PAD] = fw::BdatManager::getFp("MNU_InputPad");
  s_BdatFPs[UI_BDAT_INPUT_WHEEL] = fw::BdatManager::getFp("MNU_InputWheel");
  s_BdatFPs[UI_BDAT_INPUT_POINTER] = fw::BdatManager::getFp("MNU_InputPointer");
  s_BdatFPs[UI_BDAT_INPUT_ACT] = fw::BdatManager::getFp("MNU_InputAct");
  s_BdatFPs[UI_BDAT_TEXT_PROPERTY] = fw::BdatManager::getFp("MNU_TextProperty");
  s_BdatFPs[UI_BDAT_COLOR_LIST] = fw::BdatManager::getFp("MNU_ColorList");
  s_BdatFPs[UI_BDAT_FACE_PATTERN_LIST] = fw::BdatManager::getFp("MNU_FacePatternList");
  s_BdatFPs[UI_BDAT_RES_MOTION] = fw::BdatManager::getFp("MNU_ResMotion");
  s_BdatFPs[UI_BDAT_RES_UIO] = fw::BdatManager::getFp("MNU_ResUio");
}

u8 *UIUtil::getBdatFP(u8 type) {
  if (type < UI_BDAT_MAX) {
    return s_BdatFPs[type];
  }
  return nullptr;
}

void UIUtil::setupAllocator(mtl::ALLOC_HANDLE parent) {
  mtl::ALLOC_HANDLE program = mtl::MemManager::create(parent, 0x500000, "MenuProgram", false, mtl::ALLOCATOR_TYPE_PROGRAM, 0x10);
  mtl::ALLOC_HANDLE resource = mtl::MemManager::create(parent, 0x4b00000, "MenuResource", false, mtl::ALLOCATOR_TYPE_RESOURCE, 0x1000);
  ml::DevGraph::setMemPoolMemHandle(resource);
  s_ProgAllocator.name = "MenuProgram";
  s_ProgAllocator.setMemHandle(program);
  s_ResAllocator.name = "MenuResource";
  s_ResAllocator.setMemHandle(resource);
}

void UIUtil::destoryAllocator() {
  mtl::ALLOC_HANDLE handle;
  handle = s_ProgAllocator.getMemHandle();
  if (handle.isValid()) {
    mtl::MemManager::erase(handle);
    s_ProgAllocator.setMemHandle(mtl::ALLOC_HANDLE());
  }

  handle = s_ResAllocator.getMemHandle();
  if (handle.isValid()) {
    ml::DevGraph::releaseMemPoolMemHandle(handle);
    mtl::MemManager::erase(handle);
    s_ResAllocator.setMemHandle(mtl::ALLOC_HANDLE());
  }
}

mm::mtl::IAllocator *UIUtil::getResourceAllocator() { return &s_ResAllocator; }

u32 UIUtil::getGroupPriority(u32 group) { return group << 5 | 1; }

u32 UIUtil::convUIPadToFWPad(int pad, bool withStick) {
  if (pad < 1 || pad > 26) {
    return 0;
  }

  u32 fwPad = UI_PAD_TO_FW_PAD[pad];
  if (withStick) {
    switch (fwPad) {
    case 0x1000:
      return 0x1001000;
    case 0x4000:
      return 0x4004000;
    case 0x2000:
      return 0x2002000;
    case 0x8000:
      return 0x8008000;
    }
  }
  return fwPad;
}

void UIUtil::mergeRect(const mm::Rect<s16> &first, const mm::Rect<s16> &second, mm::Rect<s16> &result) {
  s16 x = first.x < second.x ? first.x : second.x;
  s16 y = first.y < second.y ? first.y : second.y;
  int firstRight = first.x + first.width;
  int secondRight = second.x + second.width;
  int right = firstRight > secondRight ? firstRight : secondRight;
  int firstBottom = first.y + first.height;
  int secondBottom = second.y + second.height;
  int bottom = firstBottom > secondBottom ? firstBottom : secondBottom;
  result.x = x;
  result.width = right - x;
  result.y = y;
  result.height = bottom - y;
}

void UIUtil::setSafeMergin(u32 width, u32 height) {
  s_SafeMarginW = width;
  s_SafeMarginH = height;
}

void UIUtil::dispSafeRect() {
  layer::LayerAccManager manager;
  mm::Rect<int> rect;
  rect.x = s_SafeMarginW;
  rect.width = static_cast<int>(manager.getScreenWidth()) - s_SafeMarginW * 2;
  rect.y = s_SafeMarginH;
  rect.height = static_cast<int>(manager.getScreenHeight()) - s_SafeMarginH * 2;
  mm::Col4 color = {mm::Col3::yellow.r, mm::Col3::yellow.g, mm::Col3::yellow.b, 1.0f};
  fw::debug::drawLineSquare2D(rect, color);
}

u64 UIUtil::getUITime() { return 0; }

f32 UIUtil::timeUITimeToSec(u64 time) { return time / 1000; }

u64 UIUtil::timeSecToUITime(f32 sec) { return sec * 1000.0f; }

u32 UIUtil::getScreenWidth() {
  layer::LayerAccManager manager;
  return manager.getScreenWidth();
}

u32 UIUtil::getScreenHeight() {
  layer::LayerAccManager manager;
  return manager.getScreenHeight();
}

const UICtrlCurve *UIUtil::getCurve(CURVE_TYPE type) {
  switch (type) {
  case CURVE_TYPE_LINEAR:
    return &s_curveLinear;
  case CURVE_TYPE_LINEAR_LOOP:
    return &s_curveLinearLoop;
  case CURVE_TYPE_SIN90:
    return &s_curveSin90;
  case CURVE_TYPE_SIN180:
    return &s_curveSin180;
  case CURVE_TYPE_SIN90_REV:
    return &s_curveSin90Rev;
  case CURVE_TYPE_SIN180_REV:
    return &s_curveSin180Rev;
  default:
    return nullptr;
  }
}

const fw::PadData &UIUtil::getPadData() {
  UIManager *manager = UIManager::get();
  if (manager != nullptr && manager->padRead != nullptr) {
    return *manager->padRead->getPadData();
  }
  return *fw::PadManager::getControlPadData(0);
}

void UIUtil::setDockPos(u32 handle, u32 target, u8 dock, bool global) {
  UIObjectAcc acc(handle);
  UIObjectAcc targetAcc(target);
  u16 flags = global ? UIObjectAcc::RECT_GLOBAL | UIObjectAcc::RECT_SCALED : UIObjectAcc::RECT_SCALED;
  if (acc.isValid() && targetAcc.isValid()) {
    mm::Pnt<s16> pos;
    s16 width;
    s16 height;
    acc.getSize(true, width, height);
    width /= 2;
    height /= 2;
    mm::Rect<s16> rect;
    targetAcc.getRect(rect, flags);
    pos.x = rect.x + rect.width / 2;
    pos.y = rect.y + rect.height / 2;
    switch (dock) {
    case UI_DOCK_CENTER:
      break;
    case UI_DOCK_LEFT:
      pos.x -= rect.width / 2 + width;
      break;
    case UI_DOCK_RIGHT:
      pos.x += rect.width / 2 + width;
      break;
    case UI_DOCK_TOP:
      pos.y -= height + rect.height / 2;
      break;
    case UI_DOCK_BOTTOM:
      pos.y += height + rect.height / 2;
      break;
    default:
      return;
    }
    acc.setPosCenter(pos);
  }
}

void UIUtil::calcFitScale(u32 handle, u32 target, mm::Vec2 &scale) {
  UIObjectAcc acc(handle);
  UIObjectAcc targetAcc(target);
  s16 width;
  s16 height;
  acc.getSize(false, width, height);
  s16 targetWidth;
  s16 targetHeight;
  targetAcc.getSize(true, targetWidth, targetHeight);
  scale.x = static_cast<f32>(targetWidth) / width;
  scale.y = static_cast<f32>(targetHeight) / height;
}

} // namespace ui
