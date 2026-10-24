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

UITextObject::UITextObject(layer::LayerBase *layer, const mm::mtl::FixStr<32> &name) : UIObject(layer, name, UI_OBJECT_TYPE_TEXT), unknown138(0xffff), unknown13c(0xffffffff) {}

UITextObject::~UITextObject() { ; }

UITextObject *UITextObject::create(UILayoutObject *parent, const mm::mtl::FixStr<32> &name, mm::mtl::IAllocator *allocator) {
  layer::LayerAccLayoutObj layoutAcc(parent->unknownc8);
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
  u16 style = this->unknown138;
  layer::LayerAccFontObj acc(unknownc8);
  u16 width = unknown50.unknown2c;
  u16 height = unknown50.unknown2e;
  if (style != 0xffff) {
    UIFontManager::FontRes *font = UIFontManager::get()->getFontResFromStyle(style);
    if (font == nullptr) {
      return;
    }
    acc.setMsg(text, font->unknown08, style);
  } else {
    acc.setMsg(text);
  }

  importDisplaySize(unknown50, unknownc8);
  if (unknown50.unknown09 == UI_DISPLAY_MODE_CENTER) {
    s16 x = unknown20.getPos().x - width / 2;
    s16 y = unknown20.getPos().y - height / 2;
    unknown20.setPos(x + unknown50.unknown2c / 2, y + unknown50.unknown2e / 2);
  }
}

void UITextObject::setText(const UIStr &text) {
  if (!text.isValid()) {
    return;
  }

  unknown108.copy(text);
  if (unknown138 == 0xffff) {
    unknown138 = text.getStyle();
  }
  if (unknown108.isValid() && unknown108.c_str() != nullptr) {
    UITagParser *parser = UITagParser::get();
    parser->unknownb8 = text.unknown12;
    parser->parse(getBaseText());
    this->unknown120.deepcopy(UIStr(UITagParser::get()->getResult(), false));
    if (this->unknown120.isValid() && this->unknown120.c_str() != nullptr) {
      applyText(this->unknown120.c_str());
    }
  }
}

const char *UITextObject::getBaseText() { return unknown108.isValid() ? unknown108.c_str() : nullptr; }

void UITextObject::getStyleSize(u16 &width, u16 &height) {
  width = 0;
  height = 0;
  if (unknownc8 != nullptr) {
    layer::LayerAccFontObj acc(unknownc8);
    width = acc.getPixelWidth();
    height = acc.getPixelHeight();
  }
}

void UITextObject::setTextAlignH(u8 align) {
  if (unknownc8 == nullptr) {
    return;
  }
  layer::LayerAccFontObj acc(unknownc8);
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
  if (unknownc8 == nullptr) {
    return;
  }
  layer::LayerAccFontObj acc(unknownc8);
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
  if (unknownc8 == nullptr) {
    return 0;
  }
  u32 horizontal = layer::LayerAccFontObj(unknownc8).getHorizontal();
  return horizontal < 3 ? horizontal : 0;
}

u8 UITextObject::getTextAlignV() {
  if (unknownc8 == nullptr) {
    return 0;
  }
  u32 vertical = layer::LayerAccFontObj(unknownc8).getVertical();
  return vertical < 3 ? vertical : 0;
}

void UITextObject::setBorderWeight(f32 weight) { layer::LayerAccFontObj(unknownc8).setBorderWeight(weight + 0.5f); }

f32 UITextObject::getBorderWeight() { return layer::LayerAccFontObj(unknownc8).getBorderWeight() - 0.5f; }

void UITextObject::setSlopeRot(f32 rot) { layer::LayerAccFontObj(unknownc8).setSlopeRot(rot + 0.20943952f); }

f32 UITextObject::getSlopeRot() { return layer::LayerAccFontObj(unknownc8).getSlopeRot() + -0.20943952f; }

void UITextObject::setTextFacePattern(u32 index) {
  layer::LayerAccFontObj(unknownc8).setColorMap(UIFontManager::get()->unknown98, index);
  unknown13c = index;
}

void UITextObject::reloadText() {
  if (unknown108.unknown10 != UIStr::TYPE_MSTXT) {
    return;
  }

  UITagParser::get()->unknownb8 = unknown108.unknown12;
  UITagParser::get()->parse(getBaseText());
  unknown120.deepcopy(UIStr(UITagParser::get()->getResult(), false));
  applyText(unknown120.c_str());
  UIObjectPlugin *plugin = unknowne0;
  if (plugin != nullptr && plugin->getRTTI()->isKindOf(&UIObjectPlugin::m_rtti)) {
    UIObjectAcc acc(unknowne8);
    plugin->reload(acc);
  }
}

void UITextObject::apply() { UIObject::apply(); }

void UITextObject::getTransformPosOffs(mm::Vec2 &offset) {
  offset.x = 0.0f;
  offset.y = 0.0f;
  UIFontManager::StyleInfo info;
  if (UIFontManager::get()->getFontStyleInfo(unknown138, info)) {
    offset.y -= static_cast<s32>(info.unknown04 * 4.0f);
  }
}

void UITextObject::getDisplayOffset(u16 mode, mm::Pnt<s16> &offset) const {
  UIObject::getDisplayOffset(mode, offset);
  layer::LayerAccFontObj acc(unknownc8);
  offset.x += acc.getFontPixelX();
  offset.y += acc.getFontPixelY();
}

u32 UITextObject::duplicateImpl(u32 parent) {
  UILayoutObject *layout = UIUtil::getLayoutObject(parent);
  if (layout == nullptr) {
    return 0;
  }

  UITextObject *textObject = create(layout, unknowna0.c_str(), UIUtil::getProgAllocator());
  if (textObject == nullptr) {
    return 0;
  }

  textObject->addRef();
  textObject->setTextAlignH(getTextAlignH());
  textObject->setTextAlignV(getTextAlignV());
  textObject->setBorderWeight(getBorderWeight());
  textObject->setSlopeRot(getSlopeRot());
  textObject->unknown138 = unknown138;
  if (unknown13c != 0xffffffff) {
    textObject->setTextFacePattern(unknown13c);
  }
  textObject->setText(unknown108);
  u32 handle = layout->addChild(parent, textObject);
  textObject->release();
  return handle;
}

const mm::mtl::RTTI *UITextObject::getRTTI() const { return &m_rtti; }

} // namespace ui
