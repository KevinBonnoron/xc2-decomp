#include "ui/object/ui_text_object.h"

#include "framework/memory/framework_memory.h"
#include "layer/layer_acc_font_obj.h"
#include "layer/layer_acc_layout_obj.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/rtti.h"
#include "ui/font/ui_font_manager.h"
#include "ui/object/ui_layout_object.h"
#include "ui/text/ui_tag_parser.h"
#include "ui/ui_displayinfo.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_transform.h"
#include "ui/ui_util.h"

namespace ui {

UITextObject::UITextObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name) : UIObject(layer, name, UI_OBJECT_TYPE_TEXT), style(0xffff), facePatternIndex(0xffffffff) {}

UITextObject::~UITextObject() { ; }

UITextObject *UITextObject::create(UILayoutObject *parent, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator) {
  layer::LayerAccLayoutObj layoutAcc(parent->layer);
  layer::LayerBase *layer = layoutAcc.createFontObj();
  if (layer == nullptr) {
    return nullptr;
  }

  layer::LayerAccFontObj fontAcc(layer);
  fontAcc.setDisplayArea(static_cast<layer::LayerFontDisplayArea>(1));
  fontAcc.setBorderWeight(0.5f);
  fontAcc.setSlopeRot(0.20943952f);
// __LINE__ is the line argument of the operator new call.
#line 80
  return new (allocator, 16, __FILE__, __LINE__) UITextObject(layer, name.c_str());
}

void UITextObject::applyText(const char *text) {
  u16 style = this->style;
  layer::LayerAccFontObj acc(layer);
  u16 width = displayInfo.pixelWidth;
  u16 height = displayInfo.pixelHeight;
  if (style != 0xffff) {
    UIFontManager::FontRes *font = UIFontManager::get()->getFontResFromStyle(style);
    if (font == nullptr) {
      return;
    }
    acc.setMsg(text, font->res, style);
  } else {
    acc.setMsg(text);
  }

  importDisplaySize(displayInfo, layer);
  if (displayInfo.displayMode == UI_DISPLAY_MODE_CENTER) {
    s16 x = transform.getPos().x - width / 2;
    s16 y = transform.getPos().y - height / 2;
    transform.setPos(x + displayInfo.pixelWidth / 2, y + displayInfo.pixelHeight / 2);
  }
}

void UITextObject::setText(const UIStr &text) {
  if (!text.isValid()) {
    return;
  }

  baseText.copy(text);
  if (style == 0xffff) {
    style = text.getStyle();
  }
  if (baseText.isValid() && baseText.c_str() != nullptr) {
    UITagParser *parser = UITagParser::get();
    parser->option = text.option;
    parser->parse(getBaseText());
    this->text.deepcopy(UIStr(UITagParser::get()->getResult(), false));
    if (this->text.isValid() && this->text.c_str() != nullptr) {
      applyText(this->text.c_str());
    }
  }
}

const char *UITextObject::getBaseText() { return baseText.isValid() ? baseText.c_str() : nullptr; }

void UITextObject::getStyleSize(u16 &width, u16 &height) {
  width = 0;
  height = 0;
  if (layer != nullptr) {
    layer::LayerAccFontObj acc(layer);
    width = acc.getPixelWidth();
    height = acc.getPixelHeight();
  }
}

void UITextObject::setTextAlignH(u8 align) {
  if (layer == nullptr) {
    return;
  }
  layer::LayerAccFontObj acc(layer);
  switch (align) {
  case 0:
    acc.setDisplayArea(static_cast<layer::LayerFontDisplayArea>(0));
    acc.setHorizontal(static_cast<layer::LayerFontHorizontal>(0));
    break;
  case 1:
    acc.setDisplayArea(static_cast<layer::LayerFontDisplayArea>(0));
    acc.setHorizontal(static_cast<layer::LayerFontHorizontal>(1));
    break;
  case 2:
    acc.setDisplayArea(static_cast<layer::LayerFontDisplayArea>(0));
    acc.setHorizontal(static_cast<layer::LayerFontHorizontal>(2));
    break;
  default:
    acc.setDisplayArea(static_cast<layer::LayerFontDisplayArea>(1));
    acc.setHorizontal(static_cast<layer::LayerFontHorizontal>(0));
    break;
  }
}

void UITextObject::setTextAlignV(u8 align) {
  if (layer == nullptr) {
    return;
  }
  layer::LayerAccFontObj acc(layer);
  switch (align) {
  case 0:
    acc.setVertical(static_cast<layer::LayerFontVertical>(0));
    break;
  case 1:
    acc.setVertical(static_cast<layer::LayerFontVertical>(1));
    break;
  case 2:
    acc.setVertical(static_cast<layer::LayerFontVertical>(2));
    break;
  default:
    acc.setVertical(static_cast<layer::LayerFontVertical>(0));
    break;
  }
}

u8 UITextObject::getTextAlignH() {
  if (layer == nullptr) {
    return 0;
  }
  u32 horizontal = layer::LayerAccFontObj(layer).getHorizontal();
  return horizontal < 3 ? horizontal : 0;
}

u8 UITextObject::getTextAlignV() {
  if (layer == nullptr) {
    return 0;
  }
  u32 vertical = layer::LayerAccFontObj(layer).getVertical();
  return vertical < 3 ? vertical : 0;
}

void UITextObject::setBorderWeight(f32 weight) { layer::LayerAccFontObj(layer).setBorderWeight(weight + 0.5f); }

f32 UITextObject::getBorderWeight() { return layer::LayerAccFontObj(layer).getBorderWeight() - 0.5f; }

void UITextObject::setSlopeRot(f32 rot) { layer::LayerAccFontObj(layer).setSlopeRot(rot + 0.20943952f); }

f32 UITextObject::getSlopeRot() { return layer::LayerAccFontObj(layer).getSlopeRot() + -0.20943952f; }

void UITextObject::setTextFacePattern(u32 index) {
  layer::LayerAccFontObj(layer).setColorMap(UIFontManager::get()->colorMap, index);
  facePatternIndex = index;
}

void UITextObject::reloadText() {
  if (baseText.type != UIStr::TYPE_MSTXT) {
    return;
  }

  UITagParser::get()->option = baseText.option;
  UITagParser::get()->parse(getBaseText());
  text.deepcopy(UIStr(UITagParser::get()->getResult(), false));
  applyText(text.c_str());
  UIObjectPlugin *plugin = plugins;
  if (plugin != nullptr && plugin->getRTTI()->isKindOf(&UIObjectPlugin::m_rtti)) {
    UIObjectAcc acc(handle);
    plugin->reload(acc);
  }
}

void UITextObject::apply() { UIObject::apply(); }

void UITextObject::getTransformPosOffs(mm::Vec2 &offset) {
  offset.x = 0.0f;
  offset.y = 0.0f;
  UIFontManager::StyleInfo info;
  if (UIFontManager::get()->getFontStyleInfo(style, info)) {
    offset.y -= static_cast<s32>(info.offsetY * 4.0f);
  }
}

void UITextObject::getDisplayOffset(u16 mode, mm::Pnt<s16> &offset) const {
  UIObject::getDisplayOffset(mode, offset);
  layer::LayerAccFontObj acc(layer);
  offset.x += acc.getFontPixelX();
  offset.y += acc.getFontPixelY();
}

u32 UITextObject::duplicateImpl(u32 parent) {
  UILayoutObject *layout = UIUtil::getLayoutObject(parent);
  if (layout == nullptr) {
    return 0;
  }

  UITextObject *textObject = create(layout, name.c_str(), UIUtil::getProgAllocator());
  if (textObject == nullptr) {
    return 0;
  }

  textObject->addRef();
  textObject->setTextAlignH(getTextAlignH());
  textObject->setTextAlignV(getTextAlignV());
  textObject->setBorderWeight(getBorderWeight());
  textObject->setSlopeRot(getSlopeRot());
  textObject->style = style;
  if (facePatternIndex != 0xffffffff) {
    textObject->setTextFacePattern(facePatternIndex);
  }
  textObject->setText(baseText);
  u32 handle = layout->addChild(parent, textObject);
  textObject->release();
  return handle;
}

const mm::mtl::RTTI *UITextObject::getRTTI() const { return &m_rtti; }

} // namespace ui
