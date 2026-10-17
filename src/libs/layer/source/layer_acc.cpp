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
#include "math.h"
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

LayerBase *LayerAccManager::createObj(const void *data) { return LayerManager::get()->m_objManager->createObj(data); }

LayerBase *LayerAccManager::createMaskObj(const void *data) { return LayerManager::get()->m_objManager->createMaskObj(data); }

LayerBase *LayerAccManager::createFontObj() { return LayerManager::get()->m_objManager->createFontObj(); }

LayerBase *LayerAccManager::createLayoutObj() { return LayerManager::get()->m_objManager->createLayoutObj(); }

LayerBase *LayerAccManager::createTexObj(const grlib::CGLibTextureBuffer &texture) {
  return LayerManager::get()->m_objManager->createTexObj(texture);
}

LayerBase *LayerAccManager::createMemObj(u32 width, u32 height, LayerMemType type) {
  return LayerManager::get()->m_objManager->createMemObj(width, height, type);
}

LayerBase *LayerAccManager::createPolyObj(u32 vertexNum, u32 indexNum, u16 width, u16 height, LayerPrimitiveType type) {
  return LayerManager::get()->m_objManager->createPolyObj(vertexNum, indexNum, width, height, type);
}

LayerBase *LayerAccManager::createFilterObj() { return LayerManager::get()->m_objManager->createFilterObj(); }

LayerBase *LayerAccManager::createFontResObj(const void *data) { return LayerManager::get()->m_fontManager->createFontResObj(data); }

LayerBase *LayerAccManager::createFontIconObj(const void *data) { return LayerManager::get()->m_fontManager->createFontIconObj(data); }

LayerBase *LayerAccManager::createFontStyleObj(const void *data) { return LayerManager::get()->m_fontManager->createStyleObj(data); }

LayerBase *LayerAccManager::createFontColorMapObj(const void *data) { return LayerManager::get()->m_fontManager->createFontColMapObj(data); }

f32 LayerAccManager::getFrameRate() const { return LayerManager::get()->m_frameRate; }

void LayerAccManager::setFrameRate(f32 rate) { LayerManager::get()->setFrameRate(rate); }

void LayerManager::setFrameRate(f32 rate) {
  m_frameRate = rate;
  m_frameTime = 1.0f / rate;
}

f32 LayerAccManager::getScreenWidth() const { return LayerManager::get()->getScreenWidth(); }

f32 LayerManager::getScreenWidth() const { return m_shdManager->m_screenWidth; }

f32 LayerAccManager::getScreenHeight() const { return LayerManager::get()->getScreenHeight(); }

f32 LayerManager::getScreenHeight() const { return m_shdManager->m_screenHeight; }

f32 LayerAccManager::getScreenSclWidth() const { return LayerManager::get()->m_screenSclWidth; }

f32 LayerAccManager::getScreenSclHeight() const { return LayerManager::get()->m_screenSclHeight; }

f32 LayerAccManager::getScreenPosWidth() const { return LayerManager::get()->m_screenPosWidth; }

f32 LayerAccManager::getScreenPosHeight() const { return LayerManager::get()->m_screenPosHeight; }

void LayerAccManager::setScreenSclWidth(f32 width) { LayerManager::get()->m_screenSclWidth = width; }

void LayerAccManager::setScreenSclHeight(f32 height) { LayerManager::get()->m_screenSclWidth = height; }

void LayerAccManager::setScreenPosWidth(f32 width) { LayerManager::get()->m_screenPosWidth = width; }

void LayerAccManager::setScreenPosHeight(f32 height) { LayerManager::get()->m_screenPosHeight = height; }

void LayerAccManager::setScreenOrgSize(f32 width, f32 height) {
  LayerShdManager *shdManager = LayerManager::get()->m_shdManager;
  shdManager->m_screenOrgWidth = width;
  shdManager->m_screenOrgHeight = height;
}

f32 LayerAccManager::getFontBorderWeight() const { return LayerManager::get()->m_fontBorderWeight; }

void LayerAccManager::setFontBorderWeight(f32 weight) { LayerManager::get()->m_fontBorderWeight = weight; }

LayerCoordinate LayerAccManager::getCoordinate() const { return LayerManager::get()->m_coordinate; }

bool LayerAccManager::getScreenPos(mm::Vec3 &screenPos, const mm::Vec3 &pos) {
  const LayerShdManager *shdManager = LayerManager::get()->m_shdManager;
  const f32(*matrix)[4] = shdManager->m_viewProjectionMatrix.rows;
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
  screenPos.x = (x * inverse + 1.0f) * (shdManager->m_screenOrgWidth * 0.5f);
  screenPos.y = (1.0f - y * inverse) * (shdManager->m_screenOrgHeight * 0.5f);
  screenPos.z = z * inverse;
  return true;
}

void LayerAccManager::setCoordinate(LayerCoordinate coordinate) { LayerManager::get()->m_coordinate = coordinate; }

f32 LayerAccManager::getGamma() const { return LayerManager::get()->m_shdManager->m_gamma; }

void LayerAccManager::setGamma(f32 gamma) { LayerManager::get()->m_shdManager->m_gamma = gamma; }

void LayerAccManager::openDebugWindow(ml::WinProc *window) {}

void LayerManager::openDebugWindow(ml::WinProc *window) {}

LayerAccAction::LayerAccAction(LayerBase *layer) : m_layer(static_cast<LayerActBase *>(layer)) {}

bool LayerAccAction::isActionData() const { return m_layer->m_actWork != nullptr; }

bool LayerAccAction::isRunning() const {
  if (m_layer->m_flags & 0x40) {
    return true;
  }

  return (m_layer->getStateFlags(LayerManager::s_nDebIdx) & 0x10000) != 0;
}

s32 LayerAccAction::getRunningActIdx() const {
  const LayerActBase *layer = m_layer;
  if (layer->m_flags & 0x40) {
    return layer->m_actWork->actionIdx;
  }

  if (layer->getStateFlags(LayerManager::s_nDebIdx) & 0x10000) {
    return layer->m_actionIdx[LayerManager::s_nDebIdx];
  }

  return -1;
}

f32 LayerAccAction::getRunningActSec() const {
  const LayerActBase *layer = m_layer;
  if ((layer->m_flags & 0x40) || (layer->getStateFlags(LayerManager::s_nDebIdx) & 0x10000)) {
    return layer->m_actWork->sec;
  }

  return 0.0f;
}

void LayerAccAction::setRunningActSec(f32 sec) {
  LayerActBase *layer = m_layer;
  if ((layer->m_flags & 0x40) || (layer->getStateFlags(LayerManager::s_nDebIdx) & 0x10000)) {
    layer->m_actWork->sec = sec;
  }
}

u32 LayerAccAction::getActionMax() const {
  const LayerActWork *work = m_layer->m_actWork;
  if (work == nullptr) {
    return 0;
  }

  return work->actionNum;
}

u32 LayerAccAction::getActionID(u32 index) const {
  const LayerActWork *work = m_layer->m_actWork;
  if (work == nullptr) {
    return -1;
  }

  if (index >= work->actionNum) {
    return -1;
  }

  return work->actions[index].id;
}

const char *LayerAccAction::getActionName(u32 index) const {
  const LayerActWork *work = m_layer->m_actWork;
  if (work == nullptr) {
    return nullptr;
  }

  if (index >= work->actionNum) {
    return nullptr;
  }

  const LyrActionData &action = work->actions[index];
  return reinterpret_cast<const char *>(work->data + (action.nameOffset + action.nameIdx));
}

f32 LayerAccAction::getActionSec(u32 index) const {
  const LayerActWork *work = m_layer->m_actWork;
  if (work == nullptr) {
    return 0.0f;
  }

  if (index >= work->actionNum) {
    return 0.0f;
  }

  return work->actions[index].sec;
}

bool LayerAccAction::actionIdx(u32 index) {
  const LayerActWork *work = m_layer->m_actWork;
  if (work == nullptr) {
    return false;
  }

  if (index >= work->actionNum) {
    return false;
  }

  m_layer->actionIdx(index);
  return true;
}

bool LayerAccAction::actionID(u32 id) {
  const LayerActWork *work = m_layer->m_actWork;
  if (work == nullptr) {
    return false;
  }

  for (s32 i = 0; i < work->actionNum; i++) {
    if (work->actions[i].id == id) {
      m_layer->actionIdx(i);
      return true;
    }
  }

  return false;
}

void LayerAccAction::actionEnd() {
  if (m_layer->m_actWork != nullptr) {
    m_layer->actionEnd();
  }
}

LayerAccObjBase::LayerAccObjBase(LayerBase *layer) : m_layer(static_cast<LayerObj *>(layer)) {}

void LayerAccObjBase::setSpace(LAYER_SPACE_TYPE space) { m_layer->m_space = space; }

void LayerAccObjBase::setPos(f32 x, f32 y) { m_layer->setPos(x, y); }

void LayerAccObjBase::setRot(f32 rot) { m_layer->setRot(rot); }

void LayerAccObjBase::setScale(f32 x, f32 y) { m_layer->setScale(x, y); }

void LayerAccObjBase::setAnchor(f32 x, f32 y) { m_layer->setAnchor(x, y); }

void LayerAccObjBase::setMulCol(const mm::Col4 &color) { m_layer->setMulCol(color); }

void LayerAccObjBase::setAddCol(const mm::Col3 &color) { m_layer->setAddCol(color); }

void LayerAccObjBase::setMatrix(const mm::Mat44 &matrix) { m_layer->setMatrix(matrix); }

void LayerAccObjBase::setUVParams(f32 u, f32 v, f32 scaleU, f32 scaleV, f32 rot) { m_layer->setUVParams(u, v, scaleU, scaleV, rot); }

void LayerAccObjBase::getUVParams(f32 &u, f32 &v, f32 &scaleU, f32 &scaleV, f32 &rot) { m_layer->getUVParams(u, v, scaleU, scaleV, rot); }

void LayerAccObjBase::getPos(f32 &x, f32 &y) const { m_layer->getPos(x, y); }

void LayerAccObjBase::getRot(f32 &rot) const { m_layer->getRot(rot); }

void LayerAccObjBase::getScale(f32 &x, f32 &y) const { m_layer->getScale(x, y); }

void LayerAccObjBase::getAnchor(f32 &x, f32 &y) const { m_layer->getAnchor(x, y); }

const mm::Col4 &LayerAccObjBase::getMulCol() const { return *m_layer->getMulCol(); }

const mm::Col3 &LayerAccObjBase::getAddCol() const { return *m_layer->getAddCol(); }

const mm::Mat44 &LayerAccObjBase::getMatrix() const { return *m_layer->getMatrix(); }

void LayerAccObjBase::setBlendType(LayerBlendType type) { m_layer->m_blendType = type; }

LayerBlendType LayerAccObjBase::getBlendType() const { return static_cast<LayerBlendType>(m_layer->m_blendType); }

void LayerAccObjBase::setTexFilterType(LayerTexFilterType type) { m_layer->m_texFilterType = type; }

LayerTexFilterType LayerAccObjBase::getTexFilterType() const { return static_cast<LayerTexFilterType>(m_layer->m_texFilterType); }

void LayerAccObjBase::setPriority(u16 priority) { m_layer->m_priority = priority; }

u16 LayerAccObjBase::getPriority() const { return m_layer->m_priority; }

void LayerAccObjBase::setDisp(bool disp) { m_layer->setDisp(disp); }

bool LayerAccObjBase::isDisp() const { return m_layer->isDisp(); }

void LayerAccObjBase::setFlip(LayerFlipType type, bool flip) { m_layer->setFlip(type, flip); }

bool LayerAccObjBase::isFlip(LayerFlipType type) const { return m_layer->isFlip(type); }

void LayerAccObjBase::setCtrlSpd(f32 speed) { m_layer->m_ctrlSpd = speed; }

f32 LayerAccObjBase::getCtrlSpd() const { return m_layer->m_ctrlSpd; }

u16 LayerAccObjBase::getPixelX() const { return m_layer->m_pixelX; }

u16 LayerAccObjBase::getPixelY() const { return m_layer->m_pixelY; }

u16 LayerAccObjBase::getPixelWidth() const { return m_layer->m_pixelWidth; }

u16 LayerAccObjBase::getPixelHeight() const { return m_layer->m_pixelHeight; }

void LayerAccObjBase::setCenterType(LayerCenterType type) { m_layer->m_centerType = type; }

LayerCenterType LayerAccObjBase::getCenterType() const { return static_cast<LayerCenterType>(m_layer->m_centerType); }

void LayerAccObjBase::setMaskObj(const LayerBase *mask) { m_layer->m_maskObj = mask; }

void LayerAccObjBase::resetMaskObj() { m_layer->m_maskObj = nullptr; }

const void *LayerAccObjBase::getResData() const { return m_layer->m_resData; }

void LayerAccObjBase::createAnimObj(u32 id) { m_layer->createAnimObj(id); }

void LayerAccObjBase::endAnime() { m_layer->endAnime(); }

void LayerAccObjBase::createSecondTex(const void *data) { m_layer->createSecondTex(data); }

void LayerAccObjBase::releaseSecondTex() { m_layer->releaseSecondTex(); }

u16 LayerAccObjBase::getSecondTexIconMax() const { return m_layer->getSecondTexIconMax(); }

void LayerAccObjBase::setSecondTexIconNum(u32 num) { m_layer->setSecondTexIconNum(num); }

u16 LayerAccObjBase::getSecondTexIconNum() const { return m_layer->getSecondTexIconNum(); }

void LayerAccObjBase::setSecondTexBlend(f32 blend) { m_layer->setSecondTexBlend(blend); }

f32 LayerAccObjBase::getSecondTexBlend() const { return m_layer->getSecondTexBlend(); }

LayerAccDefObj::LayerAccDefObj(LayerBase *layer) : LayerAccObjBase(layer) {}

void LayerAccDefObj::setParm(f32 parm) {
  if (m_layer->type == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(m_layer)->m_parm = parm;
  }
}

f32 LayerAccDefObj::getParm() const {
  if (m_layer->type == LAYER_OBJ_TYPE_OBJ) {
    return static_cast<LayerObjWork *>(m_layer)->m_parm;
  }

  return 0.0f;
}

void LayerAccDefObj::setIconNum(u16 num) {
  switch (m_layer->type) {
  case LAYER_OBJ_TYPE_OBJ:
    static_cast<LayerObjWork *>(m_layer)->m_iconNum = num;
    break;
  case LAYER_OBJ_TYPE_MASK:
    static_cast<LayerObjTopMaskObj *>(m_layer)->m_iconNum = num;
    break;
  }
}

u16 LayerAccDefObj::getIconNum() const {
  switch (m_layer->type) {
  case LAYER_OBJ_TYPE_OBJ:
    return static_cast<LayerObjWork *>(m_layer)->m_iconNum;
  case LAYER_OBJ_TYPE_MASK:
    return static_cast<LayerObjTopMaskObj *>(m_layer)->m_iconNum;
  }

  return 0;
}

u16 LayerAccDefObj::getIconMax() const {
  switch (m_layer->type) {
  case LAYER_OBJ_TYPE_OBJ:
    return static_cast<LayerObjWork *>(m_layer)->m_iconMax;
  case LAYER_OBJ_TYPE_MASK:
    return static_cast<LayerObjTopMaskObj *>(m_layer)->m_iconMax;
  }

  return 0;
}

void LayerAccDefObj::setGauge(LAYER_GAUGE gauge) {
  if (m_layer->type == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(m_layer)->m_gauge = gauge;
  }
}

LAYER_GAUGE LayerAccDefObj::getGauge() const {
  if (m_layer->type == LAYER_OBJ_TYPE_OBJ) {
    return static_cast<LAYER_GAUGE>(static_cast<LayerObjWork *>(m_layer)->m_gauge);
  }

  return LAYER_GAUGE_NONE;
}

LayerAccDefAnmObj::LayerAccDefAnmObj(LayerBase *layer) : LayerAccObjBase(layer) {}

f32 LayerAccDefAnmObj::getMaxSecond() const {
  if (m_layer->type == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(m_layer)->getMaxSecond();
  }

  return 0.0f;
}

f32 LayerAccDefAnmObj::getSecond() const {
  if (m_layer->type == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(m_layer)->getSecond();
  }

  return 0.0f;
}

void LayerAccDefAnmObj::setSecond(f32 second) {
  if (m_layer->type == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(m_layer)->setSecond(second);
  }
}

void LayerAccDefAnmObj::setLoop(bool loop) {
  if (m_layer->type == LAYER_OBJ_TYPE_OBJ) {
    if (loop) {
      m_layer->onStateFlags(0x4000);
      m_layer->offStateFlags(0x8000);
    } else {
      m_layer->onStateFlags(0x8000);
      m_layer->offStateFlags(0x4000);
    }
  }
}

bool LayerAccDefAnmObj::isLoop() const {
  if (m_layer->type == LAYER_OBJ_TYPE_OBJ) {
    return (m_layer->m_flags & 0x80) != 0;
  }

  return false;
}

void LayerAccDefAnmObj::setPause(bool pause) {
  if (m_layer->type == LAYER_OBJ_TYPE_OBJ) {
    if (pause) {
      m_layer->onStateFlags(0x1000);
      m_layer->offStateFlags(0x2000);
    } else {
      m_layer->onStateFlags(0x2000);
      m_layer->offStateFlags(0x1000);
    }
  }
}

bool LayerAccDefAnmObj::isPause() const {
  if (m_layer->type == LAYER_OBJ_TYPE_OBJ) {
    return (m_layer->m_flags & 0x200) != 0;
  }

  return false;
}

u32 LayerAccDefAnmObj::getDataType() const {
  if (m_layer->type == LAYER_OBJ_TYPE_OBJ) {
    return static_cast<LayerObjWork *>(m_layer)->m_dataType;
  }

  return 0;
}

LayerAccDefTexture::LayerAccDefTexture(LayerBase *layer) : m_layer(static_cast<LayerObjWork *>(layer)) {}

u32 LayerAccDefTexture::getTextureMax() const { return m_layer->m_textureMax; }

void LayerAccDefTexture::setTexutre(const void *data) { m_layer->setAddTexture(data, 0); }

void LayerAccDefTexture::setTexutre(grlib::CGLibTextureBuffer &texture) { m_layer->setAddTexture(texture, 0); }

void LayerAccDefTexture::resetTexutre() { m_layer->resetAddTexutre(0); }

void LayerAccDefTexture::resetAllTexutre() { m_layer->resetAddAllTexutre(); }

LayerAccMemObj::LayerAccMemObj(LayerBase *layer) : LayerAccObjBase(layer), m_memObj(static_cast<LayerObjTopMemObj *>(layer)) {}

void *LayerAccMemObj::getMemBufer() { return m_memObj->getBuffer(); }

void LayerAccMemObj::updateMemBufer() { m_memObj->updateBufer(); }

u16 LayerAccMemObj::getMemWidth() const { return m_memObj->m_width; }

u16 LayerAccMemObj::getMemHeight() const { return m_memObj->m_height; }

void LayerAccMemObj::setRender(bool render) { m_memObj->setRender(render); }

bool LayerAccMemObj::isRender() const { return m_memObj->isRender(); }

grlib::CGLibTextureBuffer *LayerAccMemObj::getTexture() { return m_memObj->m_texture; }

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

u32 LayerAccFontStyle::getStyleDataMax() const { return m_style->m_styleDataMax; }

s32 LayerAccFontStyle::getStyleIndex(const char *name) const { return m_style->getStyleIndex(name); }

const char *LayerAccFontStyle::getStyleName(u32 index) const { return m_style->getStyleName(index); }

const char *LayerAccFontStyle::getFontName(u32 index) const { return m_style->getFontName(index); }

void LayerAccFontStyle::createColorInfo(u32 num) { m_style->createColorInfo(num); }

void LayerAccFontStyle::releaseColorInfo() { m_style->releaseColorInfo(); }

void *LayerAccFontStyle::getColorInfo() { return m_style->m_colorInfo; }

void LayerAccFontStyle::createIconInfo(u32 num) { m_style->createIconInfo(num); }

void LayerAccFontStyle::releaseIconInfo() { m_style->releaseIconInfo(); }

void *LayerAccFontStyle::getIconInfo() { return m_style->m_iconInfo; }

f32 LayerAccFontStyle::getRubyScale() const { return m_style->m_rubyScale; }

void LayerAccFontStyle::setRubyScale(f32 scale) { m_style->m_rubyScale = scale; }

LayerAccFontObj::LayerAccFontObj(LayerBase *layer) : LayerAccObjBase(layer) {}

void LayerAccFontObj::setHorizontal(LayerFontHorizontal horizontal) { static_cast<LayerObjFont *>(m_layer)->m_horizontal = horizontal; }

void LayerAccFontObj::setVertical(LayerFontVertical vertical) { static_cast<LayerObjFont *>(m_layer)->m_vertical = vertical; }

void LayerAccFontObj::setDisplayArea(LayerFontDisplayArea area) { static_cast<LayerObjFont *>(m_layer)->m_displayArea = area; }

void LayerAccFontObj::setDispSetting(LayerFontSetting setting) { static_cast<LayerObjFont *>(m_layer)->m_dispSetting = setting; }

void LayerAccFontObj::setBorderWeight(f32 weight) { static_cast<LayerObjFont *>(m_layer)->setBorderWeight(weight); }

void LayerAccFontObj::setSlopeRot(f32 rot) { static_cast<LayerObjFont *>(m_layer)->setSlopeRot(rot); }

LayerFontHorizontal LayerAccFontObj::getHorizontal() const {
  return static_cast<LayerFontHorizontal>(static_cast<LayerObjFont *>(m_layer)->m_horizontal);
}

LayerFontVertical LayerAccFontObj::getVertical() const { return static_cast<LayerFontVertical>(static_cast<LayerObjFont *>(m_layer)->m_vertical); }

LayerFontDisplayArea LayerAccFontObj::getDisplayArea() const {
  return static_cast<LayerFontDisplayArea>(static_cast<LayerObjFont *>(m_layer)->m_displayArea);
}

LayerFontSetting LayerAccFontObj::getDispSetting() const {
  return static_cast<LayerFontSetting>(static_cast<LayerObjFont *>(m_layer)->m_dispSetting);
}

f32 LayerAccFontObj::getBorderWeight() const { return static_cast<LayerObjFont *>(m_layer)->getBorderWeight(); }

f32 LayerAccFontObj::getSlopeRot() const { return static_cast<LayerObjFont *>(m_layer)->getSlopeRot(); }

u16 LayerAccFontObj::getFontPixelX() const { return static_cast<LayerObjFont *>(m_layer)->m_fontPixelX; }

u16 LayerAccFontObj::getFontPixelY() const { return static_cast<LayerObjFont *>(m_layer)->m_fontPixelY; }

u16 LayerAccFontObj::getFontPixelWidth() const { return static_cast<LayerObjFont *>(m_layer)->m_fontPixelWidth; }

u16 LayerAccFontObj::getFontPixelHeight() const { return static_cast<LayerObjFont *>(m_layer)->m_fontPixelHeight; }

void LayerAccFontObj::setMsg(const char *text, const LayerBase *res, const LayerBase *style, u32 flags) {
  static_cast<LayerObjFont *>(m_layer)->setMsg(reinterpret_cast<const u8 *>(text),
                                               reinterpret_cast<const LayerFontResObj *>(res),
                                               reinterpret_cast<const LayerFontStyleObj *>(style),
                                               LayerManager::get()->m_fontManager->m_defaultIconObj,
                                               flags);
}

void LayerAccFontObj::setMsg(const wchar_t *text, const LayerBase *res, const LayerBase *style, u32 flags) {
  static_cast<LayerObjFont *>(m_layer)->setMsg(text,
                                               reinterpret_cast<const LayerFontResObj *>(res),
                                               reinterpret_cast<const LayerFontStyleObj *>(style),
                                               LayerManager::get()->m_fontManager->m_defaultIconObj,
                                               flags);
}

void LayerAccFontObj::setMsg(const char *text, const LayerBase *res, u32 flags) {
  LayerFontManager *fontManager = LayerManager::get()->m_fontManager;
  static_cast<LayerObjFont *>(m_layer)->setMsg(reinterpret_cast<const u8 *>(text),
                                               reinterpret_cast<const LayerFontResObj *>(res),
                                               fontManager->m_defaultStyleObj,
                                               fontManager->m_defaultIconObj,
                                               flags);
}

void LayerAccFontObj::setMsg(const wchar_t *text, const LayerBase *res, u32 flags) {
  LayerFontManager *fontManager = LayerManager::get()->m_fontManager;
  static_cast<LayerObjFont *>(m_layer)->setMsg(
      text, reinterpret_cast<const LayerFontResObj *>(res), fontManager->m_defaultStyleObj, fontManager->m_defaultIconObj, flags);
}

void LayerAccFontObj::setColorMap(const LayerBase *colorMap, u32 index) {
  static_cast<LayerObjFont *>(m_layer)->setColorMap(reinterpret_cast<const LayerFontIconObj *>(colorMap), index);
}

LayerAccLayoutObj::LayerAccLayoutObj(LayerBase *layer) : LayerAccObjBase(layer) {}

void LayerAccLayoutObj::setViewPortMode(bool viewPortMode) {
  if (viewPortMode) {
    m_layer->m_flags |= 0x10;
  } else {
    m_layer->m_flags &= ~0x10;
  }
}

void LayerAccLayoutObj::setViewPort(f32 x, f32 y, f32 width, f32 height) {
  LayerObjLayout *layout = static_cast<LayerObjLayout *>(m_layer);
  layout->m_viewPortX = x;
  layout->m_viewPortY = y;
  layout->m_viewPortWidth = width;
  layout->m_viewPortHeight = height;
}

void LayerAccLayoutObj::createRenderTarget(f32 x, f32 y, f32 width, f32 height, mm::Col4 clearColor) {
  static_cast<LayerObjLayout *>(m_layer)->createRenderTarget(x, y, width, height, clearColor);
}

void LayerAccLayoutObj::releaseRenderTarget() { static_cast<LayerObjLayout *>(m_layer)->releaseRenderTarget(); }

void LayerAccLayoutObj::createPriorityTbl(u32 num) {
  static_cast<LayerObjLayout *>(m_layer)->m_priorityTbls[LayerManager::s_nStkIdx] = num;
  m_layer->offStateFlags(0x800);
}

void LayerAccLayoutObj::releasePriorityTbl() {
  static_cast<LayerObjLayout *>(m_layer)->m_priorityTbls[LayerManager::s_nStkIdx] = 0;
  m_layer->onStateFlags(0x800);
}

u16 LayerAccLayoutObj::getPriorityTbl() const {
  const LayerObjLayout *layout = static_cast<LayerObjLayout *>(m_layer);
  u16 priorityTbl = layout->m_priorityTbls[LayerManager::s_nStkIdx];
  if (priorityTbl == 0) {
    priorityTbl = layout->m_priorityTbl;
  }

  return priorityTbl;
}

void LayerAccLayoutObj::setAutoAnchorMode(LAYER_ANCHOR mode) { static_cast<LayerObjLayout *>(m_layer)->m_autoAnchorMode = mode; }

LAYER_ANCHOR LayerAccLayoutObj::getAutoAnchorMode() const {
  return static_cast<LAYER_ANCHOR>(static_cast<LayerObjLayout *>(m_layer)->m_autoAnchorMode);
}

grlib::CGLibTextureBuffer *LayerAccLayoutObj::getTexture() { return static_cast<LayerObjLayout *>(m_layer)->getTexture(); }

void LayerAccLayoutObj::setRender(bool render) { static_cast<LayerObjLayout *>(m_layer)->setRender(render); }

bool LayerAccLayoutObj::isRender() const { return static_cast<LayerObjLayout *>(m_layer)->isRender(); }

LayerAccFilterObj::LayerAccFilterObj(LayerBase *layer) : LayerAccObjBase(layer) {}

u32 LayerAccFilterObj::getFilterType() const { return static_cast<LayerObjTopFilter *>(m_layer)->getFilterType(); }

void LayerAccFilterObj::selectFilterOfGaussianBlur(u32 width, u32 height) {
  static_cast<LayerObjTopFilter *>(m_layer)->createGaussianBlur(width, height);
}

void LayerAccFilterObj::setGaussianBlurParameter(f32 strength, f32 scale, u32 sampleNum, bool isHalf, u32 passNum) {
  static_cast<LayerObjTopFilter *>(m_layer)->setGaussianBlurParameter(strength, scale, sampleNum, isHalf, passNum);
}

void LayerAccFilterObj::selectFilterOfFlowMap(u32 width, u32 height, const void *data) {
  static_cast<LayerObjTopFilter *>(m_layer)->createFlowMap(width, height, data);
}

void LayerAccFilterObj::setFlowMapParameter(f32 speed, f32 strength) {
  static_cast<LayerObjTopFilter *>(m_layer)->setFlowMapParameter(speed, strength);
}

} // namespace layer
