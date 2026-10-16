#include "ui/ui_object_acc.h"

#include "layer/layer_acc_obj_base.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"
#include "ui/layout/ui_layout_data.h"
#include "ui/object/ui_image_object.h"
#include "ui/object/ui_layout_object.h"
#include "ui/object/ui_polygon_object.h"
#include "ui/object/ui_screen_object.h"
#include "ui/object/ui_text_object.h"
#include "ui/shape/ui_shape.h"
#include "ui/shape/ui_shape_particle.h"
#include "ui/ui_color_library.h"
#include "ui/ui_displayinfo.h"
#include "ui/ui_object_base.h"
#include "ui/ui_str.h"
#include "ui/ui_transform.h"
#include "ui/ui_util.h"

namespace ui {

namespace {

template <typename T, typename U> T *castIfValid(U *object) { return object != nullptr ? mm::mtl::dynamicCast<T>(object) : nullptr; }

} // namespace

UIObjectAcc::UIObjectAcc(u32 handle) : object(nullptr), handle(handle) { object = UIUtil::getObject(handle); }

UIObjectAcc::UIObjectAcc(u32 handle, const char *name) : object(nullptr), handle(0) {
  if (name != nullptr) {
    handle = UIUtil::searchChild(handle, name);
  }
  this->handle = handle;
  object = UIUtil::getObject(handle);
}

UIObjectAcc::UIObjectAcc(const UIObjectAcc &other) : object(nullptr), handle(other.handle) { object = UIUtil::getObject(handle); }

UIObjectAcc::~UIObjectAcc() { ; }

bool UIObjectAcc::isLayout() const { return object->objectType == UI_OBJECT_TYPE_LAYOUT; }

bool UIObjectAcc::isText() const { return object->objectType == UI_OBJECT_TYPE_TEXT; }

bool UIObjectAcc::isImage() const { return object->isImageType(); }

bool UIObjectAcc::isPolygon() const { return object->objectType == UI_OBJECT_TYPE_POLYGON; }

void UIObjectAcc::getPos(mm::Pnt<s16> &pos) const {
  if (object != nullptr) {
    object->getPos(pos);
  }
}

void UIObjectAcc::getSize(bool scaled, s16 &width, s16 &height) const {
  width = 0;
  height = 0;
  if (object == nullptr) {
    return;
  }

  if (scaled) {
    width = object->displayInfo.pixelWidth * object->transform.scale.x;
    height = object->displayInfo.pixelHeight * object->transform.scale.y;
  } else {
    width = object->displayInfo.pixelWidth;
    height = object->displayInfo.pixelHeight;
  }
}

void UIObjectAcc::getDisplayOffs(mm::Pnt<s16> &offset) const {
  offset.x = 0;
  offset.y = 0;
  if (object != nullptr) {
    object->getDisplayOffset(UI_DISPLAY_MODE_TOP_LEFT, offset);
  }
}

void UIObjectAcc::getDisplayOffsCenter(mm::Pnt<s16> &offset) const {
  offset.x = 0;
  offset.y = 0;
  if (object != nullptr) {
    object->getDisplayOffset(UI_DISPLAY_MODE_CENTER, offset);
  }
}

void UIObjectAcc::setDisp(bool disp) {
  if (object != nullptr) {
    object->displayInfo.setDisp(disp);
  }
}

void UIObjectAcc::setDispChild(bool disp, const char *name) {
  if (object != nullptr) {
    UIUtil::setDispChild(handle, disp, name);
  }
}

bool UIObjectAcc::isDisp() const {
  if (object == nullptr) {
    return false;
  }
  return object->displayInfo.disp;
}

bool UIObjectAcc::isControl() const {
  if (object == nullptr) {
    return false;
  }
  return object->flags.test(UI_OBJECT_FLAG_CONTROL);
}

bool UIObjectAcc::isDuplicate() const {
  if (object == nullptr) {
    return false;
  }
  return object->flags.test(UI_OBJECT_FLAG_DUPLICATE);
}

bool UIObjectAcc::isStreamImage() const {
  if (object == nullptr) {
    return false;
  }
  return object->flags.test(UI_OBJECT_FLAG_STREAM_IMAGE);
}

bool UIObjectAcc::isStreamImage2nd() const {
  if (object == nullptr) {
    return false;
  }
  return object->flags.test(UI_OBJECT_FLAG_STREAM_IMAGE_2ND);
}

bool UIObjectAcc::isStreaming() const {
  if (object == nullptr) {
    return false;
  }
  return object->flags.test(UI_OBJECT_FLAG_STREAMING);
}

bool UIObjectAcc::isNotInputTarget() const {
  if (object == nullptr) {
    return false;
  }
  return object->flags.test(UI_OBJECT_FLAG_NOT_INPUT_TARGET);
}

bool UIObjectAcc::isAlwaysInLayout() const {
  if (object == nullptr) {
    return false;
  }
  return object->flags.test(UI_OBJECT_FLAG_ALWAYS_IN_LAYOUT);
}

bool UIObjectAcc::isIgnoreSize() const {
  if (object == nullptr) {
    return false;
  }
  return object->flags.test(UI_OBJECT_FLAG_IGNORE_SIZE);
}

bool UIObjectAcc::isSuspend() const {
  if (object == nullptr) {
    return false;
  }
  return object->flags.test(UI_OBJECT_FLAG_SUSPEND);
}

void UIObjectAcc::setTerm() {
  if (object != nullptr) {
    object->setTerm();
  }
}

bool UIObjectAcc::isTerm() const {
  if (object == nullptr) {
    return true;
  }
  return object->isTerm();
}

void UIObjectAcc::setSuspend(bool suspend) {
  if (object != nullptr && !object->isTerm()) {
    object->setSuspend(suspend);
  }
}

u16 UIObjectAcc::getDuplicateIndex() const {
  if (object == nullptr) {
    return 0;
  }
  return object->duplicateIndex;
}

bool UIObjectAcc::isDebugDraw() const {
  if (object == nullptr) {
    return true;
  }
  return object->isDebugDraw();
}

void UIObjectAcc::getPosCenter(mm::Pnt<s16> &pos) const {
  if (object != nullptr) {
    object->getPosCenter(pos);
  }
}

void UIObjectAcc::getPosDraw(mm::Pnt<s16> &pos) const {
  if (object != nullptr) {
    pos = object->transform.pos;
  }
}

void UIObjectAcc::setPos(const mm::Pnt<s16> &pos) {
  if (object != nullptr) {
    object->setPos(pos);
  }
}

void UIObjectAcc::setPosCenter(const mm::Pnt<s16> &pos) {
  if (object != nullptr) {
    object->setPosCenter(pos);
  }
}

void UIObjectAcc::getScale(mm::Vec2 &scale) {
  scale.x = 0.0f;
  scale.y = 0.0f;
  if (object != nullptr) {
    scale = object->transform.scale;
  }
}

void UIObjectAcc::setScale(const mm::Vec2 &scale) {
  if (object != nullptr) {
    object->transform.setScale(scale.x, scale.y);
  }
}

void UIObjectAcc::getRot(f32 &rot) {
  rot = 0.0f;
  if (object != nullptr) {
    rot = object->transform.rot;
  }
}

void UIObjectAcc::setRot(f32 rot) {
  if (object != nullptr) {
    object->transform.rot = rot;
  }
}

void UIObjectAcc::setMatrix(const mm::Mat44 &matrix) {
  if (object != nullptr) {
    layer::LayerAccObjBase acc(object->layer);
    acc.setMatrix(matrix);
  }
}

void UIObjectAcc::getMatrix(mm::Mat44 &matrix) {
  matrix = mm::Mat44::identity;
  if (object != nullptr) {
    layer::LayerAccObjBase acc(object->layer);
    matrix = acc.getMatrix();
  }
}

void UIObjectAcc::getAlpha(f32 &alpha) {
  alpha = 0.0f;
  if (object != nullptr) {
    alpha = object->displayInfo.getMulColor().a;
  }
}

void UIObjectAcc::setAlpha(f32 alpha) {
  if (object != nullptr) {
    object->displayInfo.mulColor.a = alpha;
  }
}

void UIObjectAcc::setMulColor(const mm::Col3 &color) {
  if (object != nullptr) {
    mm::Col4 mulColor = {color.r, color.g, color.b, object->displayInfo.getMulColor().a};
    object->displayInfo.mulColor = mulColor;
  }
}

void UIObjectAcc::getMulColor(mm::Col3 &color) {
  color.r = 1.0f;
  color.g = 1.0f;
  color.b = 1.0f;
  if (object != nullptr) {
    const mm::Col4 &mulColor = object->displayInfo.getMulColor();
    color = mm::Col3(mulColor.r, mulColor.g, mulColor.b);
  }
}

void UIObjectAcc::setMulColor(const char *name) {
  if (name != nullptr && object != nullptr) {
    mm::Col4 color;
    if (UIColorLibrary::get()->find(name, color)) {
      color.a = 0.0f;
      if (object != nullptr) {
        color.a = object->displayInfo.getMulColor().a;
      }
      object->displayInfo.mulColor = color;
    }
  }
}

void UIObjectAcc::setAddColor(const mm::Col3 &color) {
  if (object != nullptr) {
    object->setAddColor(color);
  }
}

void UIObjectAcc::getAddColor(mm::Col3 &color) {
  if (object != nullptr) {
    color = object->displayInfo.getAddColor();
  }
}

void UIObjectAcc::setAddColor(const char *name) {
  if (name != nullptr && object != nullptr) {
    mm::Col4 color;
    if (UIColorLibrary::get()->find(name, color)) {
      object->setAddColor(mm::Col3(color.r, color.g, color.b));
    }
  }
}

void UIObjectAcc::saveDefColor() { object->displayInfo.saveDefColor(); }

void UIObjectAcc::loadDefColor() { object->displayInfo.loadDefColor(); }

u16 UIObjectAcc::getDispPriority() const {
  if (object == nullptr) {
    return 0;
  }
  return object->displayInfo.priority;
}

void UIObjectAcc::setDispPriority(u16 priority) {
  if (object != nullptr) {
    object->setPriority(priority);
  }
}

u8 UIObjectAcc::getDispBlendType() const {
  if (object == nullptr) {
    return 0;
  }
  return object->displayInfo.blendType;
}

void UIObjectAcc::setDispBlendType(u8 type) {
  if (object != nullptr) {
    object->setBlendType(type);
  }
}

void UIObjectAcc::setTexFilterLinear() {
  layer::LayerAccObjBase acc(object->layer);
  acc.setTexFilterType(layer::LAYER_TEX_FILTER_TYPE_LINEAR);
}

void UIObjectAcc::setTexFilterNearest() {
  layer::LayerAccObjBase acc(object->layer);
  acc.setTexFilterType(layer::LAYER_TEX_FILTER_TYPE_NEAREST);
}

const char *UIObjectAcc::getName() const {
  if (object == nullptr) {
    return "error";
  }
  return object->name.c_str();
}

void UIObjectAcc::setDebugDraw(bool) {}

u32 UIObjectAcc::getParentHandle() {
  if (object == nullptr) {
    return 0;
  }
  return object->parent;
}

u32 UIObjectAcc::countChild(const char *name, u32 length) {
  UILayoutObject *layout = castIfValid<UILayoutObject>(object);
  if (layout == nullptr) {
    return 0;
  }
  return layout->countChild(name, length);
}

u32 UIObjectAcc::countActiveChild() {
  UILayoutObject *layout = castIfValid<UILayoutObject>(object);
  if (layout == nullptr) {
    return 0;
  }
  return layout->countActiveChild();
}

u32 UIObjectAcc::searchChild(const char *name) {
  UILayoutObject *layout = castIfValid<UILayoutObject>(object);
  if (layout == nullptr) {
    return 0;
  }
  return layout->searchChild(name);
}

u32 UIObjectAcc::searchDuplicatedChild(const char *name, u16 index) {
  UILayoutObject *layout = castIfValid<UILayoutObject>(object);
  if (layout == nullptr) {
    return 0;
  }
  return layout->searchDuplicatedChild(name, index);
}

u32 UIObjectAcc::searchSibiling(const char *name) {
  if (object == nullptr) {
    return 0;
  }

  UILayoutObject *layout = castIfValid<UILayoutObject>(object->getParentPtr());
  if (layout == nullptr) {
    return 0;
  }
  return layout->searchChild(name);
}

u32 UIObjectAcc::duplicate(u32 parent) {
  if (object == nullptr) {
    return 0;
  }
  return object->duplicate(parent);
}

u32 UIObjectAcc::duplicateChild(const char *name) {
  UILayoutObject *layout = castIfValid<UILayoutObject>(object);
  if (layout == nullptr) {
    return 0;
  }

  u32 child = layout->searchChild(name);
  if (child == 0) {
    return 0;
  }
  return UIUtil::getObject(child)->duplicate(handle);
}

void UIObjectAcc::availableInputTarget(bool available) {
  if (object != nullptr) {
    object->flags.set(UI_OBJECT_FLAG_NOT_INPUT_TARGET, !available);
  }
}

void UIObjectAcc::setScreenAdjusting(bool adjusting) {
  if (object != nullptr) {
    object->flags.set(UI_OBJECT_FLAG_SCREEN_ADJUSTING, adjusting);
  }
}

void UIObjectAcc::setAlwaysInLayout(bool alwaysInLayout) {
  if (object != nullptr) {
    object->flags.set(UI_OBJECT_FLAG_ALWAYS_IN_LAYOUT, alwaysInLayout);
  }
}

bool UIObjectAcc::isScreenAdjusting() { return object->flags.test(UI_OBJECT_FLAG_SCREEN_ADJUSTING); }

void UIObjectAcc::applyText(const char *text) {
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject != nullptr) {
    textObject->applyText(text);
  }
}

void UIObjectAcc::setText(const UIStr &text) {
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject != nullptr) {
    textObject->setText(text);
  }
}

void UIObjectAcc::getText(UIStr &text) const {
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject != nullptr) {
    text.copy(textObject->text);
  }
}

const char *UIObjectAcc::getTextPtr() const {
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject == nullptr) {
    return nullptr;
  }
  return textObject->text.c_str();
}

void UIObjectAcc::setTextAlignH(u8 align) {
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject != nullptr) {
    textObject->setTextAlignH(align);
  }
}

void UIObjectAcc::setTextAlignV(u8 align) {
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject != nullptr) {
    textObject->setTextAlignV(align);
  }
}

u8 UIObjectAcc::getTextAlignH() const {
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject == nullptr) {
    return 0;
  }
  return textObject->getTextAlignH();
}

u8 UIObjectAcc::getTextAlignV() const {
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject == nullptr) {
    return 0;
  }
  return textObject->getTextAlignV();
}

void UIObjectAcc::setBorderWeight(f32 weight) {
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject != nullptr) {
    textObject->setBorderWeight(weight);
  }
}

f32 UIObjectAcc::getBorderWeight() const {
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject == nullptr) {
    return 0.0f;
  }
  return textObject->getBorderWeight();
}

void UIObjectAcc::setSlopeRot(f32 rot) {
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject != nullptr) {
    textObject->setSlopeRot(rot * mm::DEG_TO_RAD);
  }
}

f32 UIObjectAcc::getSlopeRot() const {
  f32 rot = 0.0f;
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject != nullptr) {
    rot = textObject->getSlopeRot() * mm::RAD_TO_DEG;
  }
  return rot;
}

void UIObjectAcc::setTextFacePattern(u32 index) {
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject != nullptr && isValid()) {
    textObject->setTextFacePattern(index);
  }
}

u32 UIObjectAcc::getTextFacePatternIndex() {
  UITextObject *textObject = castIfValid<UITextObject>(object);
  if (textObject == nullptr || !isValid()) {
    return 0;
  }
  return textObject->facePatternIndex;
}

void UIObjectAcc::setImageIndex(u32 index) {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image != nullptr) {
    image->setImageIndex(index);
  }
}

u32 UIObjectAcc::getImageIndex() const {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image == nullptr) {
    return 0;
  }
  return image->getImageIndex();
}

u32 UIObjectAcc::getImageMax() const {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image == nullptr) {
    return 0;
  }
  return image->getImageMax();
}

void UIObjectAcc::setHFlip(bool flip) {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image != nullptr) {
    image->setHFlip(flip);
  }
}

void UIObjectAcc::setVFlip(bool flip) {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image != nullptr) {
    image->setVFlip(flip);
  }
}

void UIObjectAcc::setExtType(u32 type) {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image != nullptr) {
    image->setExtType(type);
  }
}

u32 UIObjectAcc::getExtType() {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image == nullptr) {
    return 0;
  }
  return image->getExtType();
}

void UIObjectAcc::setExtParam(f32 param) {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image != nullptr) {
    image->setExtParam(param);
  }
}

f32 UIObjectAcc::getExtParam() {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image == nullptr) {
    return 0.0f;
  }
  return image->getExtParam();
}

bool UIObjectAcc::hasAnimation() {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image == nullptr) {
    return false;
  }
  return image->hasAnimation();
}

void UIObjectAcc::startAnimation(const char *name, bool loop) {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image != nullptr) {
    image->startAnimation(name, loop);
  }
}

void UIObjectAcc::startAnimationFromID(u32 id, bool loop) {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image != nullptr) {
    image->startAnimationFromID(id, loop);
  }
}

void UIObjectAcc::startAnimationFromIndex(u32 index, bool loop) {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image != nullptr) {
    image->startAnimationFromIndex(index, loop);
  }
}

void UIObjectAcc::stopAnimation() {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image != nullptr) {
    image->stopAnimation();
  }
}

bool UIObjectAcc::isPlayingAnimation() {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image == nullptr) {
    return false;
  }
  return image->isPlayingAnimation();
}

u32 UIObjectAcc::getAnimationMax() {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image == nullptr) {
    return 0;
  }
  return image->getAnimationMax();
}

const char *UIObjectAcc::getAnimationName(u32 index) {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image == nullptr) {
    return nullptr;
  }
  return image->getAnimationName(index);
}

f32 UIObjectAcc::getAnimationPlaybackLength() {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image == nullptr) {
    return 0.0f;
  }
  return image->getAnimationPlaybackLength();
}

f32 UIObjectAcc::getAnimationPlaybackTime() {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image == nullptr) {
    return 0.0f;
  }
  return image->getAnimationPlaybackTime();
}

void UIObjectAcc::setAnimationPlaybackTime(f32 time) {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image != nullptr) {
    image->setAnimationPlaybackTime(time);
  }
}

bool UIObjectAcc::isPlaybackControl() const {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image == nullptr) {
    return false;
  }
  return image->playbackControl;
}

void UIObjectAcc::applyCapture() {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image != nullptr) {
    image->applyCapture();
  }
}

void UIObjectAcc::setMaskObject(u32 handle) {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image != nullptr) {
    image->setMaskObject(UIUtil::getImageObject(handle));
  }
}

void UIObjectAcc::setStreamImage2nd() {
  UIImageObject *image = castIfValid<UIImageObject>(object);
  if (image != nullptr) {
    image->flags.set(UI_OBJECT_FLAG_STREAM_IMAGE_2ND);
  }
}

void UIObjectAcc::setLayout(u32 handle, const char *name) {
  UILayoutObject *layout = castIfValid<UILayoutObject>(object);
  if (layout != nullptr) {
    UILayoutData *layoutData = layout->layoutData;
    UIObject *target = UIUtil::getObject(handle);
    if (layoutData != nullptr && target != nullptr) {
      layoutData->attachLayout(name, target);
    }
  }
}

bool UIObjectAcc::getLayoutRect(const char *name, mm::Rect<s16> &rect) {
  UILayoutObject *layout = castIfValid<UILayoutObject>(object);
  if (layout == nullptr || layout->layoutData == nullptr) {
    return false;
  }
  return layout->layoutData->getLayoutRect(name, rect);
}

void UIObjectAcc::setLayoutViewport(mm::Rect<s16> viewport) {
  UILayoutObject *layout = castIfValid<UILayoutObject>(object);
  if (layout != nullptr) {
    layout->setViewport(viewport);
  }
}

void UIObjectAcc::updateLayoutSize() {
  UILayoutObject *layout = castIfValid<UILayoutObject>(object);
  if (layout != nullptr) {
    layout->updateSize();
  }
}

bool UIObjectAcc::isRenderViewMode() {
  UIScreenObject *screen = castIfValid<UIScreenObject>(object);
  if (screen == nullptr) {
    return false;
  }
  return screen->mode == UIScreenObject::MODE_RENDER_VIEW;
}

bool UIObjectAcc::isOnMemoryMode() {
  UIScreenObject *screen = castIfValid<UIScreenObject>(object);
  if (screen == nullptr) {
    return false;
  }
  return screen->mode == UIScreenObject::MODE_ON_MEMORY;
}

u32 UIObjectAcc::getRenderIndex() {
  UIScreenObject *screen = castIfValid<UIScreenObject>(object);
  if (screen == nullptr) {
    return 0;
  }
  return screen->renderIndex;
}

u32 UIObjectAcc::getOnMemoryPixelSize() {
  UIScreenObject *screen = castIfValid<UIScreenObject>(object);
  if (screen == nullptr) {
    return 0;
  }
  return screen->getOnMemoryPixelSize();
}

void *UIObjectAcc::getOnMemoryBuffer() {
  UIScreenObject *screen = castIfValid<UIScreenObject>(object);
  if (screen == nullptr) {
    return nullptr;
  }
  return screen->getOnMemoryBuffer();
}

void UIObjectAcc::swapOnMemoryBuffer() {
  UIScreenObject *screen = castIfValid<UIScreenObject>(object);
  if (screen != nullptr) {
    screen->swapOnMemoryBuffer();
  }
}

u32 UIObjectAcc::getShapeType() {
  UIPolygonObject *polygon = castIfValid<UIPolygonObject>(object);
  if (polygon == nullptr) {
    return 0;
  }
  return polygon->shapeType;
}

bool UIObjectAcc::isShapeSimpleFace() {
  UIPolygonObject *polygon = castIfValid<UIPolygonObject>(object);
  if (polygon == nullptr) {
    return false;
  }
  return polygon->shapeType == UIPolygonObject::SHAPE_TYPE_SIMPLE_FACE;
}

bool UIObjectAcc::isShapeRing() {
  UIPolygonObject *polygon = castIfValid<UIPolygonObject>(object);
  if (polygon == nullptr) {
    return false;
  }
  return polygon->shapeType == UIPolygonObject::SHAPE_TYPE_RING;
}

bool UIObjectAcc::isShapeParticle() {
  UIPolygonObject *polygon = castIfValid<UIPolygonObject>(object);
  if (polygon == nullptr) {
    return false;
  }
  return polygon->shapeType == UIPolygonObject::SHAPE_TYPE_PARTICLE;
}

UIShape *UIObjectAcc::getShape() {
  UIPolygonObject *polygon = castIfValid<UIPolygonObject>(object);
  if (polygon == nullptr) {
    return nullptr;
  }
  return polygon->shape;
}

void UIObjectAcc::setParicleActivate(bool activate) {
  if (isShapeParticle()) {
    castIfValid<UIShapeParticle>(getShape())->activate(activate);
  }
}

bool UIObjectAcc::isParicleActivate() {
  UIShapeParticle *particle = castIfValid<UIShapeParticle>(getShape());
  if (particle == nullptr) {
    return false;
  }
  return particle->isActive();
}

} // namespace ui
