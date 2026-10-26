#include <math.h>

#include "layer/layer_acc_action.h"
#include "layer/layer_acc_def_obj.h"
#include "layer/layer_acc_def_texture.h"
#include "layer/layer_acc_filter_obj.h"
#include "layer/layer_acc_font_obj.h"
#include "layer/layer_acc_font_style.h"
#include "layer/layer_acc_layout_obj.h"
#include "layer/layer_acc_manager.h"
#include "layer/layer_acc_mem_obj.h"
#include "layer/layer_acc_obj_base.h"
#include "layer/layer_acc_poly_obj.h"
#include "layer/layer_act_base.h"
#include "layer/layer_base.h"
#include "layer/layer_font_manager.h"
#include "layer/layer_font_style_obj.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_font.h"
#include "layer/layer_obj_layout.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_top_filter.h"
#include "layer/layer_obj_top_mask_obj.h"
#include "layer/layer_obj_top_mem_obj.h"
#include "layer/layer_obj_top_poly_obj.h"
#include "layer/layer_obj_work.h"
#include "layer/layer_shd_manager.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib
namespace ml {
class WinProc;
} // namespace ml
namespace mm {
struct Col3;
} // namespace mm

namespace layer {
class LayerFontIconObj;
class LayerFontResObj;

LayerAccManager::LayerAccManager() {}

LayerBase *LayerAccManager::createObj(const void *data) { return LayerManager::get()->unknown60->createObj(data); }

LayerBase *LayerAccManager::createMaskObj(const void *data) { return LayerManager::get()->unknown60->createMaskObj(data); }

LayerBase *LayerAccManager::createFontObj() { return LayerManager::get()->unknown60->createFontObj(); }

LayerBase *LayerAccManager::createLayoutObj() { return LayerManager::get()->unknown60->createLayoutObj(); }

LayerBase *LayerAccManager::createTexObj(const grlib::CGLibTextureBuffer &texture) { return LayerManager::get()->unknown60->createTexObj(texture); }

LayerBase *LayerAccManager::createMemObj(u32 width, u32 height, LayerMemType type) { return LayerManager::get()->unknown60->createMemObj(width, height, type); }

LayerBase *LayerAccManager::createPolyObj(u32 vertexNum, u32 indexNum, u16 width, u16 height, LayerPrimitiveType type) {
  return LayerManager::get()->unknown60->createPolyObj(vertexNum, indexNum, width, height, type);
}

LayerBase *LayerAccManager::createFilterObj() { return LayerManager::get()->unknown60->createFilterObj(); }

LayerBase *LayerAccManager::createFontResObj(const void *data) { return LayerManager::get()->unknown68->createFontResObj(data); }

LayerBase *LayerAccManager::createFontIconObj(const void *data) { return LayerManager::get()->unknown68->createFontIconObj(data); }

LayerBase *LayerAccManager::createFontStyleObj(const void *data) { return LayerManager::get()->unknown68->createStyleObj(data); }

LayerBase *LayerAccManager::createFontColorMapObj(const void *data) { return LayerManager::get()->unknown68->createFontColMapObj(data); }

f32 LayerAccManager::getFrameRate() const { return LayerManager::get()->unknown7c; }

void LayerAccManager::setFrameRate(f32 rate) { LayerManager::get()->setFrameRate(rate); }

void LayerManager::setFrameRate(f32 rate) {
  unknown7c = rate;
  unknown80 = 1.0f / rate;
}

f32 LayerAccManager::getScreenWidth() const { return LayerManager::get()->getScreenWidth(); }

f32 LayerManager::getScreenWidth() const { return unknown58->unknown530; }

f32 LayerAccManager::getScreenHeight() const { return LayerManager::get()->getScreenHeight(); }

f32 LayerManager::getScreenHeight() const { return unknown58->unknown534; }

f32 LayerAccManager::getScreenSclWidth() const { return LayerManager::get()->unknown90; }

f32 LayerAccManager::getScreenSclHeight() const { return LayerManager::get()->unknown94; }

f32 LayerAccManager::getScreenPosWidth() const { return LayerManager::get()->unknown88; }

f32 LayerAccManager::getScreenPosHeight() const { return LayerManager::get()->unknown8c; }

void LayerAccManager::setScreenSclWidth(f32 width) { LayerManager::get()->unknown90 = width; }

void LayerAccManager::setScreenSclHeight(f32 height) { LayerManager::get()->unknown90 = height; }

void LayerAccManager::setScreenPosWidth(f32 width) { LayerManager::get()->unknown88 = width; }

void LayerAccManager::setScreenPosHeight(f32 height) { LayerManager::get()->unknown8c = height; }

void LayerAccManager::setScreenOrgSize(f32 width, f32 height) {
  LayerShdManager *shdManager = LayerManager::get()->unknown58;
  shdManager->unknown550 = width;
  shdManager->unknown554 = height;
}

f32 LayerAccManager::getFontBorderWeight() const { return LayerManager::get()->unknown84; }

void LayerAccManager::setFontBorderWeight(f32 weight) { LayerManager::get()->unknown84 = weight; }

LayerCoordinate LayerAccManager::getCoordinate() const { return LayerManager::get()->unknown9c; }

bool LayerAccManager::getScreenPos(mm::Vec3 &screenPos, const mm::Vec3 &pos) {
  const LayerShdManager *shdManager = LayerManager::get()->unknown58;
  const f32(*matrix)[4] = shdManager->unknown4a0.rows;
  f32 posX = pos.x;
  f32 posY = pos.y;
  f32 posZ = pos.z;
  f32 x = posX * matrix[0][0] + posY * matrix[1][0] + posZ * matrix[2][0] + matrix[3][0];
  f32 y = posX * matrix[0][1] + posY * matrix[1][1] + posZ * matrix[2][1] + matrix[3][1];
  f32 z = posX * matrix[0][2] + posY * matrix[1][2] + posZ * matrix[2][2] + matrix[3][2];
  f32 w = posX * matrix[0][3] + posY * matrix[1][3] + posZ * matrix[2][3] + matrix[3][3];
  if (z < 0.000001f) {
    return false;
  }

  if (fabsf(w) <= 0.000001f) {
    return false;
  }

  f32 inverse = 1.0f / w;
  screenPos.x = (x * inverse + 1.0f) * (shdManager->unknown550 * 0.5f);
  screenPos.y = (1.0f - y * inverse) * (shdManager->unknown554 * 0.5f);
  screenPos.z = z * inverse;
  return true;
}

void LayerAccManager::setCoordinate(LayerCoordinate coordinate) { LayerManager::get()->unknown9c = coordinate; }

f32 LayerAccManager::getGamma() const { return LayerManager::get()->unknown58->unknown578; }

void LayerAccManager::setGamma(f32 gamma) { LayerManager::get()->unknown58->unknown578 = gamma; }

void LayerAccManager::openDebugWindow(ml::WinProc *window) {}

void LayerManager::openDebugWindow(ml::WinProc *window) {}

LayerAccAction::LayerAccAction(LayerBase *layer) : m_layer(static_cast<LayerActBase *>(layer)) {}

bool LayerAccAction::isActionData() const { return m_layer->unknown250 != nullptr; }

bool LayerAccAction::isRunning() const {
  if (m_layer->unknowna8 & 0x40) {
    return true;
  }

  return (m_layer->getStateFlags(LayerManager::s_nDebIdx) & 0x10000) != 0;
}

s32 LayerAccAction::getRunningActIdx() const {
  const LayerActBase *layer = m_layer;
  if (layer->unknowna8 & 0x40) {
    return layer->unknown250->unknown20;
  }

  if (layer->getStateFlags(LayerManager::s_nDebIdx) & 0x10000) {
    return layer->unknown1d8[LayerManager::s_nDebIdx];
  }

  return -1;
}

f32 LayerAccAction::getRunningActSec() const {
  const LayerActBase *layer = m_layer;
  if ((layer->unknowna8 & 0x40) || (layer->getStateFlags(LayerManager::s_nDebIdx) & 0x10000)) {
    return layer->unknown250->unknown14;
  }

  return 0.0f;
}

void LayerAccAction::setRunningActSec(f32 sec) {
  LayerActBase *layer = m_layer;
  if ((layer->unknowna8 & 0x40) || (layer->getStateFlags(LayerManager::s_nDebIdx) & 0x10000)) {
    layer->unknown250->unknown14 = sec;
  }
}

u32 LayerAccAction::getActionMax() const {
  const LayerActWork *work = m_layer->unknown250;
  if (work == nullptr) {
    return 0;
  }

  return work->unknown10;
}

u32 LayerAccAction::getActionID(u32 index) const {
  const LayerActWork *work = m_layer->unknown250;
  if (work == nullptr) {
    return -1;
  }

  if (index >= work->unknown10) {
    return -1;
  }

  return work->unknown08[index].unknown08;
}

const char *LayerAccAction::getActionName(u32 index) const {
  const LayerActWork *work = m_layer->unknown250;
  if (work == nullptr) {
    return nullptr;
  }

  if (index >= work->unknown10) {
    return nullptr;
  }

  const LyrActionData &action = work->unknown08[index];
  return reinterpret_cast<const char *>(work->unknown00 + (action.unknown0c + action.unknown14));
}

f32 LayerAccAction::getActionSec(u32 index) const {
  const LayerActWork *work = m_layer->unknown250;
  if (work == nullptr) {
    return 0.0f;
  }

  if (index >= work->unknown10) {
    return 0.0f;
  }

  return work->unknown08[index].unknown18;
}

bool LayerAccAction::actionIdx(u32 index) {
  const LayerActWork *work = m_layer->unknown250;
  if (work == nullptr) {
    return false;
  }

  if (index >= work->unknown10) {
    return false;
  }

  m_layer->actionIdx(index);
  return true;
}

bool LayerAccAction::actionID(u32 id) {
  const LayerActWork *work = m_layer->unknown250;
  if (work == nullptr) {
    return false;
  }

  for (s32 i = 0; i < work->unknown10; i++) {
    if (work->unknown08[i].unknown08 == id) {
      m_layer->actionIdx(i);
      return true;
    }
  }

  return false;
}

void LayerAccAction::actionEnd() {
  if (m_layer->unknown250 != nullptr) {
    m_layer->actionEnd();
  }
}

LayerAccObjBase::LayerAccObjBase(LayerBase *layer) : unknown00(static_cast<LayerObj *>(layer)) {}

void LayerAccObjBase::setSpace(LAYER_SPACE_TYPE space) { unknown00->unknownc3 = space; }

void LayerAccObjBase::setPos(f32 x, f32 y) { unknown00->setPos(x, y); }

void LayerAccObjBase::setRot(f32 rot) { unknown00->setRot(rot); }

void LayerAccObjBase::setScale(f32 x, f32 y) { unknown00->setScale(x, y); }

void LayerAccObjBase::setAnchor(f32 x, f32 y) { unknown00->setAnchor(x, y); }

void LayerAccObjBase::setMulCol(const mm::Col4 &color) { unknown00->setMulCol(color); }

void LayerAccObjBase::setAddCol(const mm::Col3 &color) { unknown00->setAddCol(color); }

void LayerAccObjBase::setMatrix(const mm::Mat44 &matrix) { unknown00->setMatrix(matrix); }

void LayerAccObjBase::setUVParams(f32 u, f32 v, f32 scaleU, f32 scaleV, f32 rot) { unknown00->setUVParams(u, v, scaleU, scaleV, rot); }

void LayerAccObjBase::getUVParams(f32 &u, f32 &v, f32 &scaleU, f32 &scaleV, f32 &rot) { unknown00->getUVParams(u, v, scaleU, scaleV, rot); }

void LayerAccObjBase::getPos(f32 &x, f32 &y) const { unknown00->getPos(x, y); }

void LayerAccObjBase::getRot(f32 &rot) const { unknown00->getRot(rot); }

void LayerAccObjBase::getScale(f32 &x, f32 &y) const { unknown00->getScale(x, y); }

void LayerAccObjBase::getAnchor(f32 &x, f32 &y) const { unknown00->getAnchor(x, y); }

const mm::Col4 &LayerAccObjBase::getMulCol() const { return *unknown00->getMulCol(); }

const mm::Col3 &LayerAccObjBase::getAddCol() const { return *unknown00->getAddCol(); }

const mm::Mat44 &LayerAccObjBase::getMatrix() const { return *unknown00->getMatrix(); }

void LayerAccObjBase::setBlendType(LayerBlendType type) { unknown00->unknownc4 = type; }

LayerBlendType LayerAccObjBase::getBlendType() const { return static_cast<LayerBlendType>(unknown00->unknownc4); }

void LayerAccObjBase::setTexFilterType(LayerTexFilterType type) { unknown00->unknownc6 = type; }

LayerTexFilterType LayerAccObjBase::getTexFilterType() const { return static_cast<LayerTexFilterType>(unknown00->unknownc6); }

void LayerAccObjBase::setPriority(u16 priority) { unknown00->unknownc0 = priority; }

u16 LayerAccObjBase::getPriority() const { return unknown00->unknownc0; }

void LayerAccObjBase::setDisp(bool disp) { unknown00->setDisp(disp); }

bool LayerAccObjBase::isDisp() const { return unknown00->isDisp(); }

void LayerAccObjBase::setFlip(LayerFlipType type, bool flip) { unknown00->setFlip(type, flip); }

bool LayerAccObjBase::isFlip(LayerFlipType type) const { return unknown00->isFlip(type); }

void LayerAccObjBase::setCtrlSpd(f32 speed) { unknown00->unknown1f4 = speed; }

f32 LayerAccObjBase::getCtrlSpd() const { return unknown00->unknown1f4; }

u16 LayerAccObjBase::getPixelX() const { return unknown00->unknown190; }

u16 LayerAccObjBase::getPixelY() const { return unknown00->unknown192; }

u16 LayerAccObjBase::getPixelWidth() const { return unknown00->unknown194; }

u16 LayerAccObjBase::getPixelHeight() const { return unknown00->unknown196; }

void LayerAccObjBase::setCenterType(LayerCenterType type) { unknown00->unknown198 = type; }

LayerCenterType LayerAccObjBase::getCenterType() const { return static_cast<LayerCenterType>(unknown00->unknown198); }

void LayerAccObjBase::setMaskObj(const LayerBase *mask) { unknown00->unknown240 = mask; }

void LayerAccObjBase::resetMaskObj() { unknown00->unknown240 = nullptr; }

const void *LayerAccObjBase::getResData() const { return unknown00->unknownb8; }

void LayerAccObjBase::createAnimObj(u32 id) { unknown00->createAnimObj(id); }

void LayerAccObjBase::endAnime() { unknown00->endAnime(); }

void LayerAccObjBase::createSecondTex(const void *data) { unknown00->createSecondTex(data); }

void LayerAccObjBase::releaseSecondTex() { unknown00->releaseSecondTex(); }

u16 LayerAccObjBase::getSecondTexIconMax() const { return unknown00->getSecondTexIconMax(); }

void LayerAccObjBase::setSecondTexIconNum(u32 num) { unknown00->setSecondTexIconNum(num); }

u16 LayerAccObjBase::getSecondTexIconNum() const { return unknown00->getSecondTexIconNum(); }

void LayerAccObjBase::setSecondTexBlend(f32 blend) { unknown00->setSecondTexBlend(blend); }

f32 LayerAccObjBase::getSecondTexBlend() const { return unknown00->getSecondTexBlend(); }

LayerAccDefObj::LayerAccDefObj(LayerBase *layer) : LayerAccObjBase(layer) {}

void LayerAccDefObj::setParm(f32 parm) {
  if (unknown00->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(unknown00)->unknown2a0 = parm;
  }
}

f32 LayerAccDefObj::getParm() const {
  if (unknown00->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    return static_cast<LayerObjWork *>(unknown00)->unknown2a0;
  }

  return 0.0f;
}

void LayerAccDefObj::setIconNum(u16 num) {
  switch (unknown00->unknown18) {
  case LAYER_OBJ_TYPE_OBJ:
    static_cast<LayerObjWork *>(unknown00)->unknown2a4 = num;
    break;
  case LAYER_OBJ_TYPE_MASK:
    static_cast<LayerObjTopMaskObj *>(unknown00)->unknown2d0 = num;
    break;
  }
}

u16 LayerAccDefObj::getIconNum() const {
  switch (unknown00->unknown18) {
  case LAYER_OBJ_TYPE_OBJ:
    return static_cast<LayerObjWork *>(unknown00)->unknown2a4;
  case LAYER_OBJ_TYPE_MASK:
    return static_cast<LayerObjTopMaskObj *>(unknown00)->unknown2d0;
  }

  return 0;
}

u16 LayerAccDefObj::getIconMax() const {
  switch (unknown00->unknown18) {
  case LAYER_OBJ_TYPE_OBJ:
    return static_cast<LayerObjWork *>(unknown00)->unknown2a6;
  case LAYER_OBJ_TYPE_MASK:
    return static_cast<LayerObjTopMaskObj *>(unknown00)->unknown2d2;
  }

  return 0;
}

void LayerAccDefObj::setGauge(LAYER_GAUGE gauge) {
  if (unknown00->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(unknown00)->unknown2a8 = gauge;
  }
}

LAYER_GAUGE LayerAccDefObj::getGauge() const {
  if (unknown00->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    return static_cast<LAYER_GAUGE>(static_cast<LayerObjWork *>(unknown00)->unknown2a8);
  }

  return LAYER_GAUGE_NONE;
}

LayerAccDefAnmObj::LayerAccDefAnmObj(LayerBase *layer) : LayerAccObjBase(layer) {}

f32 LayerAccDefAnmObj::getMaxSecond() const {
  if (unknown00->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(unknown00)->getMaxSecond();
  }

  return 0.0f;
}

f32 LayerAccDefAnmObj::getSecond() const {
  if (unknown00->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(unknown00)->getSecond();
  }

  return 0.0f;
}

void LayerAccDefAnmObj::setSecond(f32 second) {
  if (unknown00->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(unknown00)->setSecond(second);
  }
}

void LayerAccDefAnmObj::setLoop(bool loop) {
  if (unknown00->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    if (loop) {
      unknown00->onStateFlags(0x4000);
      unknown00->offStateFlags(0x8000);
    } else {
      unknown00->onStateFlags(0x8000);
      unknown00->offStateFlags(0x4000);
    }
  }
}

bool LayerAccDefAnmObj::isLoop() const {
  if (unknown00->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    return (unknown00->unknowna8 & 0x80) != 0;
  }

  return false;
}

void LayerAccDefAnmObj::setPause(bool pause) {
  if (unknown00->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    if (pause) {
      unknown00->onStateFlags(0x1000);
      unknown00->offStateFlags(0x2000);
    } else {
      unknown00->onStateFlags(0x2000);
      unknown00->offStateFlags(0x1000);
    }
  }
}

bool LayerAccDefAnmObj::isPause() const {
  if (unknown00->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    return (unknown00->unknowna8 & 0x200) != 0;
  }

  return false;
}

u32 LayerAccDefAnmObj::getDataType() const {
  if (unknown00->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    return static_cast<LayerObjWork *>(unknown00)->unknown2ac;
  }

  return 0;
}

LayerAccDefTexture::LayerAccDefTexture(LayerBase *layer) : m_layer(static_cast<LayerObjWork *>(layer)) {}

u32 LayerAccDefTexture::getTextureMax() const { return m_layer->unknown288; }

void LayerAccDefTexture::setTexutre(const void *data) { m_layer->setAddTexture(data, 0); }

void LayerAccDefTexture::setTexutre(grlib::CGLibTextureBuffer &texture) { m_layer->setAddTexture(texture, 0); }

void LayerAccDefTexture::resetTexutre() { m_layer->resetAddTexutre(0); }

void LayerAccDefTexture::resetAllTexutre() { m_layer->resetAddAllTexutre(); }

LayerAccMemObj::LayerAccMemObj(LayerBase *layer) : LayerAccObjBase(layer), m_memObj(static_cast<LayerObjTopMemObj *>(layer)) {}

void *LayerAccMemObj::getMemBufer() { return m_memObj->getBuffer(); }

void LayerAccMemObj::updateMemBufer() { m_memObj->updateBufer(); }

u32 LayerAccMemObj::getMemWidth() const { return m_memObj->unknown740; }

u32 LayerAccMemObj::getMemHeight() const { return m_memObj->unknown744; }

void LayerAccMemObj::setRender(bool render) { m_memObj->setRender(render); }

bool LayerAccMemObj::isRender() const { return m_memObj->isRender(); }

grlib::CGLibTextureBuffer *LayerAccMemObj::getTexture() { return m_memObj->unknown2e8; }

LayerAccPolyObj::LayerAccPolyObj(LayerBase *layer) : LayerAccObjBase(layer), m_polyObj(static_cast<LayerObjTopPolyObj *>(layer)) {}

void LayerAccPolyObj::LockVertex() { m_polyObj->LockVertex(); }

void LayerAccPolyObj::setVertex(u32 index, const LayerPolyVertex &vertex) { m_polyObj->setVertex(index, vertex); }

void LayerAccPolyObj::UnlockVertex() { m_polyObj->UnlockVertex(); }

void LayerAccPolyObj::LockIndex() { m_polyObj->LockIndex(); }

void LayerAccPolyObj::setIndex(u32 index, u16 vertexIndex) { m_polyObj->setIndex(index, vertexIndex); }

void LayerAccPolyObj::UnlockIndex() { m_polyObj->UnlockIndex(); }

void LayerAccPolyObj::setIndexInfo(u16 start, u16 num) { m_polyObj->setIndexInfo(start, num); }

void LayerAccPolyObj::setTexutre(const void *data) { m_polyObj->setTexutre(data); }

void LayerAccPolyObj::setTexutre(grlib::CGLibTextureBuffer &texture) { m_polyObj->setTexutre(texture); }

void LayerAccPolyObj::resetTexutre() { m_polyObj->resetTexutre(); }

LayerAccFontStyle::LayerAccFontStyle(LayerBase *layer) : m_style(static_cast<LayerFontStyleObj *>(layer)) {}

u32 LayerAccFontStyle::getStyleDataMax() const { return m_style->unknown28; }

s32 LayerAccFontStyle::getStyleIndex(const char *name) const { return m_style->getStyleIndex(name); }

const char *LayerAccFontStyle::getStyleName(u32 index) const { return m_style->getStyleName(index); }

const char *LayerAccFontStyle::getFontName(u32 index) const { return m_style->getFontName(index); }

void LayerAccFontStyle::createColorInfo(u32 num) { m_style->createColorInfo(num); }

void LayerAccFontStyle::releaseColorInfo() { m_style->releaseColorInfo(); }

void *LayerAccFontStyle::getColorInfo() { return m_style->unknown48; }

void LayerAccFontStyle::createIconInfo(u32 num) { m_style->createIconInfo(num); }

void LayerAccFontStyle::releaseIconInfo() { m_style->releaseIconInfo(); }

void *LayerAccFontStyle::getIconInfo() { return m_style->unknown50; }

f32 LayerAccFontStyle::getRubyScale() const { return m_style->unknown40; }

void LayerAccFontStyle::setRubyScale(f32 scale) { m_style->unknown40 = scale; }

LayerAccFontObj::LayerAccFontObj(LayerBase *layer) : LayerAccObjBase(layer) {}

void LayerAccFontObj::setHorizontal(LayerFontHorizontal horizontal) { static_cast<LayerObjFont *>(unknown00)->unknown2a8 = horizontal; }

void LayerAccFontObj::setVertical(LayerFontVertical vertical) { static_cast<LayerObjFont *>(unknown00)->unknown2ac = vertical; }

void LayerAccFontObj::setDisplayArea(LayerFontDisplayArea area) { static_cast<LayerObjFont *>(unknown00)->unknown2b0 = area; }

void LayerAccFontObj::setDispSetting(LayerFontSetting setting) { static_cast<LayerObjFont *>(unknown00)->unknown2b4 = setting; }

void LayerAccFontObj::setBorderWeight(f32 weight) { static_cast<LayerObjFont *>(unknown00)->setBorderWeight(weight); }

void LayerAccFontObj::setSlopeRot(f32 rot) { static_cast<LayerObjFont *>(unknown00)->setSlopeRot(rot); }

LayerFontHorizontal LayerAccFontObj::getHorizontal() const { return static_cast<LayerFontHorizontal>(static_cast<LayerObjFont *>(unknown00)->unknown2a8); }

LayerFontVertical LayerAccFontObj::getVertical() const { return static_cast<LayerFontVertical>(static_cast<LayerObjFont *>(unknown00)->unknown2ac); }

LayerFontDisplayArea LayerAccFontObj::getDisplayArea() const { return static_cast<LayerFontDisplayArea>(static_cast<LayerObjFont *>(unknown00)->unknown2b0); }

LayerFontSetting LayerAccFontObj::getDispSetting() const { return static_cast<LayerFontSetting>(static_cast<LayerObjFont *>(unknown00)->unknown2b4); }

f32 LayerAccFontObj::getBorderWeight() const { return static_cast<LayerObjFont *>(unknown00)->getBorderWeight(); }

f32 LayerAccFontObj::getSlopeRot() const { return static_cast<LayerObjFont *>(unknown00)->getSlopeRot(); }

u16 LayerAccFontObj::getFontPixelX() const { return static_cast<LayerObjFont *>(unknown00)->unknown2a0; }

u16 LayerAccFontObj::getFontPixelY() const { return static_cast<LayerObjFont *>(unknown00)->unknown2a2; }

u16 LayerAccFontObj::getFontPixelWidth() const { return static_cast<LayerObjFont *>(unknown00)->unknown2a4; }

u16 LayerAccFontObj::getFontPixelHeight() const { return static_cast<LayerObjFont *>(unknown00)->unknown2a6; }

void LayerAccFontObj::setMsg(const char *text, const LayerBase *res, const LayerBase *style, u32 flags) {
  static_cast<LayerObjFont *>(unknown00)->setMsg(
      reinterpret_cast<const u8 *>(text), reinterpret_cast<const LayerFontResObj *>(res), reinterpret_cast<const LayerFontStyleObj *>(style), LayerManager::get()->unknown68->unknown68, flags);
}

void LayerAccFontObj::setMsg(const wchar_t *text, const LayerBase *res, const LayerBase *style, u32 flags) {
  static_cast<LayerObjFont *>(unknown00)->setMsg(
      text, reinterpret_cast<const LayerFontResObj *>(res), reinterpret_cast<const LayerFontStyleObj *>(style), LayerManager::get()->unknown68->unknown68, flags);
}

void LayerAccFontObj::setMsg(const char *text, const LayerBase *res, u32 flags) {
  LayerFontManager *fontManager = LayerManager::get()->unknown68;
  static_cast<LayerObjFont *>(unknown00)->setMsg(reinterpret_cast<const u8 *>(text), reinterpret_cast<const LayerFontResObj *>(res), fontManager->unknown70, fontManager->unknown68, flags);
}

void LayerAccFontObj::setMsg(const wchar_t *text, const LayerBase *res, u32 flags) {
  LayerFontManager *fontManager = LayerManager::get()->unknown68;
  static_cast<LayerObjFont *>(unknown00)->setMsg(text, reinterpret_cast<const LayerFontResObj *>(res), fontManager->unknown70, fontManager->unknown68, flags);
}

void LayerAccFontObj::setColorMap(const LayerBase *colorMap, u32 index) { static_cast<LayerObjFont *>(unknown00)->setColorMap(reinterpret_cast<const LayerFontIconObj *>(colorMap), index); }

LayerAccLayoutObj::LayerAccLayoutObj(LayerBase *layer) : LayerAccObjBase(layer) {}

void LayerAccLayoutObj::setViewPortMode(bool viewPortMode) {
  if (viewPortMode) {
    unknown00->unknowna8 |= 0x10;
  } else {
    unknown00->unknowna8 &= ~0x10;
  }
}

void LayerAccLayoutObj::setViewPort(f32 x, f32 y, f32 width, f32 height) {
  LayerObjLayout *layout = static_cast<LayerObjLayout *>(unknown00);
  layout->unknown2b0 = x;
  layout->unknown2b4 = y;
  layout->unknown2b8 = width;
  layout->unknown2bc = height;
}

void LayerAccLayoutObj::createRenderTarget(f32 x, f32 y, f32 width, f32 height, mm::Col4 clearColor) { static_cast<LayerObjLayout *>(unknown00)->createRenderTarget(x, y, width, height, clearColor); }

void LayerAccLayoutObj::releaseRenderTarget() { static_cast<LayerObjLayout *>(unknown00)->releaseRenderTarget(); }

void LayerAccLayoutObj::createPriorityTbl(u32 num) {
  static_cast<LayerObjLayout *>(unknown00)->unknown2c4[LayerManager::s_nStkIdx] = num;
  unknown00->offStateFlags(0x800);
}

void LayerAccLayoutObj::releasePriorityTbl() {
  static_cast<LayerObjLayout *>(unknown00)->unknown2c4[LayerManager::s_nStkIdx] = 0;
  unknown00->onStateFlags(0x800);
}

u16 LayerAccLayoutObj::getPriorityTbl() const {
  const LayerObjLayout *layout = static_cast<LayerObjLayout *>(unknown00);
  u16 priorityTbl = layout->unknown2c4[LayerManager::s_nStkIdx];
  if (priorityTbl == 0) {
    priorityTbl = layout->unknown2c8;
  }

  return priorityTbl;
}

void LayerAccLayoutObj::setAutoAnchorMode(LAYER_ANCHOR mode) { static_cast<LayerObjLayout *>(unknown00)->unknown2c0 = mode; }

LAYER_ANCHOR LayerAccLayoutObj::getAutoAnchorMode() const { return static_cast<LAYER_ANCHOR>(static_cast<LayerObjLayout *>(unknown00)->unknown2c0); }

grlib::CGLibTextureBuffer *LayerAccLayoutObj::getTexture() { return static_cast<LayerObjLayout *>(unknown00)->getTexture(); }

void LayerAccLayoutObj::setRender(bool render) { static_cast<LayerObjLayout *>(unknown00)->setRender(render); }

bool LayerAccLayoutObj::isRender() const { return static_cast<LayerObjLayout *>(unknown00)->isRender(); }

LayerAccFilterObj::LayerAccFilterObj(LayerBase *layer) : LayerAccObjBase(layer) {}

u32 LayerAccFilterObj::getFilterType() const { return static_cast<LayerObjTopFilter *>(unknown00)->getFilterType(); }

void LayerAccFilterObj::selectFilterOfGaussianBlur(u32 width, u32 height) { static_cast<LayerObjTopFilter *>(unknown00)->createGaussianBlur(width, height); }

void LayerAccFilterObj::setGaussianBlurParameter(f32 strength, f32 scale, u32 sampleNum, bool isHalf, u32 passNum) {
  static_cast<LayerObjTopFilter *>(unknown00)->setGaussianBlurParameter(strength, scale, sampleNum, isHalf, passNum);
}

void LayerAccFilterObj::selectFilterOfFlowMap(u32 width, u32 height, const void *data) { static_cast<LayerObjTopFilter *>(unknown00)->createFlowMap(width, height, data); }

void LayerAccFilterObj::setFlowMapParameter(f32 speed, f32 strength) { static_cast<LayerObjTopFilter *>(unknown00)->setFlowMapParameter(speed, strength); }

} // namespace layer
