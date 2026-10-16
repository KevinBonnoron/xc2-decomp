#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "types.h"
#include "ui/ui_object.h"

namespace mm {
struct Col3;
struct Mat44;
struct Vec2;
} // namespace mm

namespace ui {

class UIShape;
class UIStr;

class UIObjectAcc {
public:
  enum RectFlag {
    RECT_GLOBAL = 1 << 0,
    RECT_SCALED = 1 << 1,
  };

  UIObjectAcc(u32 handle);
  UIObjectAcc(u32 handle, const char *name);
  UIObjectAcc(const UIObjectAcc &other);
  UIObjectAcc(UIObject *object) : object(object), handle(object->handle) {}
  virtual ~UIObjectAcc();

  bool isValid() const { return object != nullptr; }

  bool isLayout() const;
  bool isText() const;
  bool isImage() const;
  bool isPolygon() const;
  void getRect(mm::Rect<s16> &rect, u16 flags) const;
  void getPos(mm::Pnt<s16> &pos) const;
  void getSize(bool scaled, s16 &width, s16 &height) const;
  void getDisplayOffs(mm::Pnt<s16> &offset) const;
  void getDisplayOffsCenter(mm::Pnt<s16> &offset) const;
  void setDisp(bool disp);
  void setDispChild(bool disp, const char *name);
  bool isDisp() const;
  bool isControl() const;
  bool isDuplicate() const;
  bool isStreamImage() const;
  bool isStreamImage2nd() const;
  bool isStreaming() const;
  bool isNotInputTarget() const;
  bool isAlwaysInLayout() const;
  bool isIgnoreSize() const;
  bool isSuspend() const;
  void setTerm();
  bool isTerm() const;
  void setSuspend(bool suspend);
  u16 getDuplicateIndex() const;
  bool isDebugDraw() const;
  void getPosCenter(mm::Pnt<s16> &pos) const;
  void getPosDraw(mm::Pnt<s16> &pos) const;
  void setPos(const mm::Pnt<s16> &pos);
  void setPosCenter(const mm::Pnt<s16> &pos);
  void getScale(mm::Vec2 &scale);
  void setScale(const mm::Vec2 &scale);
  void getRot(f32 &rot);
  void setRot(f32 rot);
  void setMatrix(const mm::Mat44 &matrix);
  void getMatrix(mm::Mat44 &matrix);
  void getAlpha(f32 &alpha);
  void setAlpha(f32 alpha);
  void setMulColor(const mm::Col3 &color);
  void getMulColor(mm::Col3 &color);
  void setMulColor(const char *name);
  void setAddColor(const mm::Col3 &color);
  void getAddColor(mm::Col3 &color);
  void setAddColor(const char *name);
  void saveDefColor();
  void loadDefColor();
  u16 getDispPriority() const;
  void setDispPriority(u16 priority);
  u8 getDispBlendType() const;
  void setDispBlendType(u8 type);
  void setTexFilterLinear();
  void setTexFilterNearest();
  const char *getName() const;
  void setDebugDraw(bool debugDraw);
  u32 getParentHandle();
  u32 countChild(const char *name, u32 length);
  u32 countActiveChild();
  u32 searchChild(const char *name);
  u32 searchDuplicatedChild(const char *name, u16 index);
  u32 searchSibiling(const char *name);
  u32 duplicate(u32 parent);
  u32 duplicateChild(const char *name);
  void availableInputTarget(bool available);
  void setScreenAdjusting(bool adjusting);
  void setAlwaysInLayout(bool alwaysInLayout);
  void setIgnoreSize(bool ignoreSize);
  bool isScreenAdjusting();
  void applyText(const char *text);
  void setText(const UIStr &text);
  void getText(UIStr &text) const;
  const char *getTextPtr() const;
  void setTextAlignH(u8 align);
  void setTextAlignV(u8 align);
  u8 getTextAlignH() const;
  u8 getTextAlignV() const;
  void setBorderWeight(f32 weight);
  f32 getBorderWeight() const;
  void setSlopeRot(f32 rot);
  f32 getSlopeRot() const;
  void setTextFacePattern(const char *name);
  void setTextFacePattern(u32 index);
  u32 getTextFacePatternIndex();
  void setImageIndex(u32 index);
  u32 getImageIndex() const;
  u32 getImageMax() const;
  void setHFlip(bool flip);
  void setVFlip(bool flip);
  void setExtType(u32 type);
  u32 getExtType();
  void setExtParam(f32 param);
  f32 getExtParam();
  bool hasAnimation();
  void startAnimation(const char *name, bool loop);
  void startAnimationFromID(u32 id, bool loop);
  void startAnimationFromIndex(u32 index, bool loop);
  void stopAnimation();
  bool isPlayingAnimation();
  u32 getAnimationMax();
  const char *getAnimationName(u32 index);
  f32 getAnimationPlaybackLength();
  f32 getAnimationPlaybackTime();
  void setAnimationPlaybackTime(f32 time);
  bool isPlaybackControl() const;
  void applyCapture();
  void setMaskObject(u32 handle);
  void setStreamImage2nd();
  void setLayout(u32 handle, const char *name);
  bool getLayoutRect(const char *name, mm::Rect<s16> &rect);
  void setLayoutViewport(mm::Rect<s16> viewport);
  void updateLayoutSize();
  bool isRenderViewMode();
  bool isOnMemoryMode();
  u32 getRenderIndex();
  u32 getOnMemoryPixelSize();
  void *getOnMemoryBuffer();
  void swapOnMemoryBuffer();
  u32 getShapeType();
  bool isShapeSimpleFace();
  bool isShapeRing();
  bool isShapeParticle();
  UIShape *getShape();
  void setParicleActivate(bool activate);
  bool isParicleActivate();

  UIObject *object;
  u32 handle;
};

static_assert(offsetof(UIObjectAcc, object) == 0x08, "");
static_assert(offsetof(UIObjectAcc, handle) == 0x10, "");
static_assert(sizeof(UIObjectAcc) == 0x18, "");

} // namespace ui
