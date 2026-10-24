#include "ui/object/ui_screen_object.h"

#include "framework/memory/framework_memory.h"
#include "fw/fw_model_object.h"
#include "layer/layer_acc_layout_obj.h"
#include "layer/layer_acc_mem_obj.h"
#include "layer/layer_obj_manager.h"
#include "ml/scn.h"
#include "mm_mtl/reference_object.h"
#include "scn/scn_render_dr_sys.h"
#include "scn/scn_render_dr_sys_parm_acc.h"
#include "ui/object/ui_layout_object.h"

namespace ui {

UIScreenObject::UIScreenObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name)
    : UIObject(layer, name, UI_OBJECT_TYPE_SCREEN), unknown108(MODE_RENDER_VIEW), renderIndex(0), _114(), unknown118(nullptr) {}

UIScreenObject::~UIScreenObject() {
  if (unknown108 == MODE_RENDER_VIEW) {
    mm::mtl::safeRelease(unknown118);
  }
  if (unknown108 == MODE_ON_MEMORY && onMemoryInfo.unknown00 >= 1 && onMemoryInfo.unknown00 <= 4) {
    ml::ScnRenderDrSysParmAcc(ml::Scn::get()->unknown38, 0).resetModelTexture(static_cast<u8>(onMemoryInfo.unknown00 - 1));
  }
}

UIScreenObject *UIScreenObject::create(UILayoutObject *parent, ml::ScnRenderDrViewCtrl *viewCtrl, fw::ModelObject *model, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator) {
  layer::LayerAccLayoutObj layoutAcc(parent->unknownc8);
  layer::LayerBase *layer = layoutAcc.createTexObj(*viewCtrl->unknown20);
  if (layer == nullptr) {
    return nullptr;
  }

// __LINE__ is the line argument of the operator new call.
#line 79
  UIScreenObject *screen = new (allocator, 16, __FILE__, __LINE__) UIScreenObject(layer, name.c_str());
  if (screen != nullptr) {
    screen->unknown108 = MODE_RENDER_VIEW;
    screen->renderIndex = viewCtrl->unknown08;
    screen->unknown118 = model;
    if (model != nullptr) {
      model->addRef();
    }
  }
  return screen;
}

UIScreenObject *UIScreenObject::createOnMemory(UILayoutObject *parent, u32 width, u32 height, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator, const OnMemoryInfo &info) {
  layer::LayerAccLayoutObj layoutAcc(parent->unknownc8);
  layer::LayerBase *layer = layoutAcc.createMemObj(width, height, static_cast<layer::LayerMemType>(info.unknown01));
  if (layer == nullptr) {
    return nullptr;
  }

// __LINE__ is the line argument of the operator new call.
#line 116
  UIScreenObject *screen = new (allocator, 16, __FILE__, __LINE__) UIScreenObject(layer, name.c_str());
  if (screen != nullptr) {
    screen->unknown108 = MODE_ON_MEMORY;
  }
  if (info.unknown00 >= 1 && info.unknown00 <= 4) {
    ml::ScnRenderDrSysParmAcc parmAcc(ml::Scn::get()->unknown38, 0);
    layer::LayerAccMemObj memAcc(layer);
    u8 index = info.unknown00 - 1;
    ml::ScnRenderDrMdlTexture texture;
    texture.unknown00 = memAcc.getTexture();
    texture.unknown08 = index;
    texture.unknown0c = true;
    parmAcc.setModelTexture(texture);
    memAcc.setRender(false);
  }
  screen->onMemoryInfo = info;
  return screen;
}

u32 UIScreenObject::getOnMemoryPixelSize() const {
  if (unknown108 != MODE_ON_MEMORY) {
    return 0;
  }
  switch (onMemoryInfo.unknown01) {
  case 1:
    return 3;
  case 2:
    return 2;
  case 3:
    return 1;
  default:
    return 0;
  }
}

void *UIScreenObject::getOnMemoryBuffer() const {
  if (unknown108 != MODE_ON_MEMORY) {
    return nullptr;
  }
  return layer::LayerAccMemObj(unknownc8).getMemBufer();
}

void UIScreenObject::swapOnMemoryBuffer() {
  if (unknown108 == MODE_ON_MEMORY) {
    layer::LayerAccMemObj(unknownc8).updateMemBufer();
  }
}

const mm::mtl::RTTI *UIScreenObject::getRTTI() const { return &m_rtti; }

u32 UIScreenObject::duplicateImpl(u32 parent) { return 0; }

} // namespace ui
