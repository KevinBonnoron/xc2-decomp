#include <math.h>
#include <stddef.h>
#include <string.h>

#include "grlib/cglib_render_target.h"
#include "layer/layer_acc_action.h"
#include "layer/layer_acc_def_obj.h"
#include "layer/layer_acc_def_texture.h"
#include "layer/layer_acc_filter_obj.h"
#include "layer/layer_acc_font_obj.h"
#include "layer/layer_acc_font_style.h"
#include "layer/layer_acc_format.h"
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
#include "layer/layer_obj_list.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_top_filter.h"
#include "layer/layer_obj_top_mask_obj.h"
#include "layer/layer_obj_top_mem_obj.h"
#include "layer/layer_obj_top_poly_obj.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_obj_work.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_view_port.h"
#include "ml/critical_section.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/vector.h"
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
class LayerStrInfo;

LayerAccManager::LayerAccManager() {}

LayerBase *LayerAccManager::createObj(const void *data) { return LayerManager::get()->m_layerObjManager->createObj(data); }

LayerBase *LayerAccManager::createMaskObj(const void *data) { return LayerManager::get()->m_layerObjManager->createMaskObj(data); }

LayerBase *LayerAccManager::createFontObj() { return LayerManager::get()->m_layerObjManager->createFontObj(); }

LayerBase *LayerAccManager::createLayoutObj() { return LayerManager::get()->m_layerObjManager->createLayoutObj(); }

LayerBase *LayerAccManager::createTexObj(const grlib::CGLibTextureBuffer &texture) { return LayerManager::get()->m_layerObjManager->createTexObj(texture); }

LayerBase *LayerAccManager::createMemObj(u32 width, u32 height, LayerMemType type) { return LayerManager::get()->m_layerObjManager->createMemObj(width, height, type); }

LayerBase *LayerAccManager::createPolyObj(u32 vertexNum, u32 indexNum, u16 width, u16 height, LayerPrimitiveType type) {
  return LayerManager::get()->m_layerObjManager->createPolyObj(vertexNum, indexNum, width, height, type);
}

LayerBase *LayerAccManager::createFilterObj() { return LayerManager::get()->m_layerObjManager->createFilterObj(); }

LayerBase *LayerAccManager::createFontResObj(const void *data) { return LayerManager::get()->m_layerFontManager->createFontResObj(data); }

LayerBase *LayerAccManager::createFontIconObj(const void *data) { return LayerManager::get()->m_layerFontManager->createFontIconObj(data); }

LayerBase *LayerAccManager::createFontStyleObj(const void *data) { return LayerManager::get()->m_layerFontManager->createStyleObj(data); }

LayerBase *LayerAccManager::createFontColorMapObj(const void *data) { return LayerManager::get()->m_layerFontManager->createFontColMapObj(data); }

f32 LayerAccManager::getFrameRate() const { return LayerManager::get()->m_frameRate; }

void LayerAccManager::setFrameRate(f32 rate) { LayerManager::get()->setFrameRate(rate); }

void LayerManager::setFrameRate(f32 rate) {
  m_frameRate = rate;
  unknown80 = 1.0f / rate;
}

f32 LayerAccManager::getScreenWidth() const { return LayerManager::get()->getScreenWidth(); }

f32 LayerManager::getScreenWidth() const { return m_layerShdManager->m_screenWidth; }

f32 LayerAccManager::getScreenHeight() const { return LayerManager::get()->getScreenHeight(); }

f32 LayerManager::getScreenHeight() const { return m_layerShdManager->m_screenHeight; }

f32 LayerAccManager::getScreenSclWidth() const { return LayerManager::get()->unknown90; }

f32 LayerAccManager::getScreenSclHeight() const { return LayerManager::get()->m_screenSclHeight; }

f32 LayerAccManager::getScreenPosWidth() const { return LayerManager::get()->m_screenPosWidth; }

f32 LayerAccManager::getScreenPosHeight() const { return LayerManager::get()->m_screenPosHeight; }

void LayerAccManager::setScreenSclWidth(f32 width) { LayerManager::get()->unknown90 = width; }

void LayerAccManager::setScreenSclHeight(f32 height) { LayerManager::get()->unknown90 = height; }

void LayerAccManager::setScreenPosWidth(f32 width) { LayerManager::get()->m_screenPosWidth = width; }

void LayerAccManager::setScreenPosHeight(f32 height) { LayerManager::get()->m_screenPosHeight = height; }

void LayerAccManager::setScreenOrgSize(f32 width, f32 height) {
  LayerShdManager *shdManager = LayerManager::get()->m_layerShdManager;
  shdManager->unknown550 = width;
  shdManager->unknown554 = height;
}

f32 LayerAccManager::getFontBorderWeight() const { return LayerManager::get()->m_fontBorderWeight; }

void LayerAccManager::setFontBorderWeight(f32 weight) { LayerManager::get()->m_fontBorderWeight = weight; }

LayerCoordinate LayerAccManager::getCoordinate() const { return LayerManager::get()->m_coordinate; }

bool LayerAccManager::getScreenPos(mm::Vec3 &screenPos, const mm::Vec3 &pos) {
  const LayerShdManager *shdManager = LayerManager::get()->m_layerShdManager;
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

void LayerAccManager::setCoordinate(LayerCoordinate coordinate) { LayerManager::get()->m_coordinate = coordinate; }

f32 LayerAccManager::getGamma() const { return LayerManager::get()->m_layerShdManager->m_gamma; }

void LayerAccManager::setGamma(f32 gamma) { LayerManager::get()->m_layerShdManager->m_gamma = gamma; }

void LayerAccManager::openDebugWindow(ml::WinProc *window) {}

void LayerManager::openDebugWindow(ml::WinProc *window) {}

namespace {

struct unknown001 {
  u32 unknown00; // Inferred role: magic; original member name unknown.
  u32 unknown04; // Inferred role: version; original member name unknown.
  u32 unknown08; // Inferred role: flags; original member name unknown.
  u8 _0c[0x18 - 0x0c];
  u32 unknown18; // Inferred role: offset of the entry table; original member name unknown.
  u8 _1c[0x24 - 0x1c];
  u32 unknown24; // Inferred role: extra data; original member name unknown.
};

static_assert(offsetof(unknown001, unknown08) == 0x08, "");
static_assert(offsetof(unknown001, unknown18) == 0x18, "");
static_assert(offsetof(unknown001, unknown24) == 0x24, "");

} // namespace

LayerAccFormat::LayerAccFormat() : unknown00(0), unknown04(false), unknown05(false), unknown06(false) {}

LayerAccFormat::LayerAccFormat(const void *data) : unknown00(0), unknown04(false), unknown05(false), unknown06(false) { setLayerData(data); }

void LayerAccFormat::setLayerData(const void *data) {
  const unknown001 *header = static_cast<const unknown001 *>(data);
  switch (header->unknown00) {
  case 0x4448414c:
    if (header->unknown04 == 0x2711) {
      unknown00 = 1;
      if (header->unknown08 & 0x20) {
        unknown05 = true;
      }
      if (header->unknown24 != 0) {
        unknown04 = true;
      }
      if (*reinterpret_cast<const u16 *>(static_cast<const u8 *>(data) + header->unknown18) >= 2) {
        unknown06 = true;
      }
      return;
    }
    break;
  case 0x5350414c:
    if (header->unknown04 == 0x2711) {
      unknown00 = 2;
      return;
    }
    break;
  case 0x5446414c:
    if (header->unknown04 == 0x2711) {
      unknown00 = 3;
      unknown04 = true;
      return;
    }
    break;
  case 0x5453414c:
    if (header->unknown04 == 0x2711) {
      unknown00 = 4;
      return;
    }
    break;
  }
  unknown00 = 0;
}

LayerAccAction::LayerAccAction(LayerBase *layer) : m_layer(static_cast<LayerActBase *>(layer)) {}

bool LayerAccAction::isActionData() const { return m_layer->unknown250 != nullptr; }

bool LayerAccAction::isRunning() const {
  if (m_layer->unknowna8 & 0x40) {
    return true;
  }

  return (m_layer->getStateFlags(LayerManager::s_nDebIdx) & 0x10000) != 0;
}

const char *LayerAccAction::getRunningActName() const {
  const LayerActBase *layer = m_layer;
  if (layer->unknowna8 & 0x40) {
    const unknown084 *work = layer->unknown250;
    const LyrActionData *action = work->m_lyrActionData + work->unknown20;
    return reinterpret_cast<const char *>(work->unknown00 + (action->unknown0c + action->unknown14));
  }

  if (layer->getStateFlags(LayerManager::s_nDebIdx) & 0x10000) {
    const unknown084 *work = layer->unknown250;
    const LyrActionData *action = work->m_lyrActionData + layer->unknown1d8[LayerManager::s_nDebIdx];
    return reinterpret_cast<const char *>(work->unknown00 + (action->unknown0c + action->unknown14));
  }

  return nullptr;
}

u32 LayerAccAction::getRunningActID() const {
  const LayerActBase *layer = m_layer;
  if (layer->unknowna8 & 0x40) {
    const unknown084 *work = layer->unknown250;
    const LyrActionData *action = work->m_lyrActionData + work->unknown20;
    return action->unknown08;
  }

  if (layer->getStateFlags(LayerManager::s_nDebIdx) & 0x10000) {
    const unknown084 *work = layer->unknown250;
    const LyrActionData *action = work->m_lyrActionData + layer->unknown1d8[LayerManager::s_nDebIdx];
    return action->unknown08;
  }

  return -1;
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
  const unknown084 *work = m_layer->unknown250;
  if (work == nullptr) {
    return 0;
  }

  return work->unknown10;
}

u32 LayerAccAction::getActionID(u32 index) const {
  const unknown084 *work = m_layer->unknown250;
  if (work == nullptr) {
    return -1;
  }

  if (index >= work->unknown10) {
    return -1;
  }

  return work->m_lyrActionData[index].unknown08;
}

const char *LayerAccAction::getActionName(u32 index) const {
  const unknown084 *work = m_layer->unknown250;
  if (work == nullptr) {
    return nullptr;
  }

  if (index >= work->unknown10) {
    return nullptr;
  }

  const LyrActionData &action = work->m_lyrActionData[index];
  return reinterpret_cast<const char *>(work->unknown00 + (action.unknown0c + action.unknown14));
}

f32 LayerAccAction::getActionSec(u32 index) const {
  const unknown084 *work = m_layer->unknown250;
  if (work == nullptr) {
    return 0.0f;
  }

  if (index >= work->unknown10) {
    return 0.0f;
  }

  return work->m_lyrActionData[index].unknown18;
}

bool LayerAccAction::actionIdx(u32 index) {
  const unknown084 *work = m_layer->unknown250;
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
  const unknown084 *work = m_layer->unknown250;
  if (work == nullptr) {
    return false;
  }

  for (s32 i = 0; i < work->unknown10; i++) {
    if (work->m_lyrActionData[i].unknown08 == id) {
      m_layer->actionIdx(i);
      return true;
    }
  }

  return false;
}

bool LayerAccAction::actionName(const char *name) {
  const unknown084 *work = m_layer->unknown250;
  if (work != nullptr) {
    for (s32 i = 0; i < work->unknown10; i++) {
      const LyrActionData &action = work->m_lyrActionData[i];
      if (strcmp(name, reinterpret_cast<const char *>(work->unknown00 + (action.unknown0c + action.unknown14))) == 0) {
        m_layer->actionIdx(i);
        return true;
      }
    }
  }

  return false;
}

void LayerAccAction::actionEnd() {
  if (m_layer->unknown250 != nullptr) {
    m_layer->actionEnd();
  }
}

LayerAccObjBase::LayerAccObjBase(LayerBase *layer) : m_layerObj(static_cast<LayerObj *>(layer)) {}

void LayerAccObjBase::setSpace(LAYER_SPACE_TYPE space) { m_layerObj->m_space = space; }

void LayerAccObjBase::setPos(f32 x, f32 y) { m_layerObj->setPos(x, y); }

void LayerAccObjBase::setRot(f32 rot) { m_layerObj->setRot(rot); }

void LayerAccObjBase::setScale(f32 x, f32 y) { m_layerObj->setScale(x, y); }

void LayerAccObjBase::setAnchor(f32 x, f32 y) { m_layerObj->setAnchor(x, y); }

void LayerAccObjBase::setMulCol(const mm::Col4 &color) { m_layerObj->setMulCol(color); }

void LayerAccObjBase::setAddCol(const mm::Col3 &color) { m_layerObj->setAddCol(color); }

void LayerAccObjBase::setMatrix(const mm::Mat44 &matrix) { m_layerObj->setMatrix(matrix); }

void LayerAccObjBase::setUVParams(f32 u, f32 v, f32 scaleU, f32 scaleV, f32 rot) { m_layerObj->setUVParams(u, v, scaleU, scaleV, rot); }

void LayerAccObjBase::getUVParams(f32 &u, f32 &v, f32 &scaleU, f32 &scaleV, f32 &rot) { m_layerObj->getUVParams(u, v, scaleU, scaleV, rot); }

void LayerAccObjBase::getPos(f32 &x, f32 &y) const { m_layerObj->getPos(x, y); }

void LayerAccObjBase::getRot(f32 &rot) const { m_layerObj->getRot(rot); }

void LayerAccObjBase::getScale(f32 &x, f32 &y) const { m_layerObj->getScale(x, y); }

void LayerAccObjBase::getAnchor(f32 &x, f32 &y) const { m_layerObj->getAnchor(x, y); }

const mm::Col4 &LayerAccObjBase::getMulCol() const { return *m_layerObj->getMulCol(); }

const mm::Col3 &LayerAccObjBase::getAddCol() const { return *m_layerObj->getAddCol(); }

const mm::Mat44 &LayerAccObjBase::getMatrix() const { return *m_layerObj->getMatrix(); }

void LayerAccObjBase::setBlendType(LayerBlendType type) { m_layerObj->m_blendType = type; }

LayerBlendType LayerAccObjBase::getBlendType() const { return static_cast<LayerBlendType>(m_layerObj->m_blendType); }

void LayerAccObjBase::setTexFilterType(LayerTexFilterType type) { m_layerObj->m_texFilterType = type; }

LayerTexFilterType LayerAccObjBase::getTexFilterType() const { return static_cast<LayerTexFilterType>(m_layerObj->m_texFilterType); }

void LayerAccObjBase::setPriority(u16 priority) { m_layerObj->m_priority = priority; }

u16 LayerAccObjBase::getPriority() const { return m_layerObj->m_priority; }

void LayerAccObjBase::setDisp(bool disp) { m_layerObj->setDisp(disp); }

bool LayerAccObjBase::isDisp() const { return m_layerObj->isDisp(); }

void LayerAccObjBase::setFlip(LayerFlipType type, bool flip) { m_layerObj->setFlip(type, flip); }

bool LayerAccObjBase::isFlip(LayerFlipType type) const { return m_layerObj->isFlip(type); }

void LayerAccObjBase::setCtrlSpd(f32 speed) { m_layerObj->m_ctrlSpd = speed; }

f32 LayerAccObjBase::getCtrlSpd() const { return m_layerObj->m_ctrlSpd; }

u16 LayerAccObjBase::getPixelX() const { return m_layerObj->m_layerResRenderInfo.m_pixelX; }

u16 LayerAccObjBase::getPixelY() const { return m_layerObj->m_layerResRenderInfo.m_pixelY; }

u16 LayerAccObjBase::getPixelWidth() const { return m_layerObj->m_layerResRenderInfo.m_pixelWidth; }

u16 LayerAccObjBase::getPixelHeight() const { return m_layerObj->m_layerResRenderInfo.m_pixelHeight; }

void LayerAccObjBase::setCenterType(LayerCenterType type) { m_layerObj->m_layerResRenderInfo.m_centerType = type; }

LayerCenterType LayerAccObjBase::getCenterType() const { return static_cast<LayerCenterType>(m_layerObj->m_layerResRenderInfo.m_centerType); }

void LayerAccObjBase::setMaskObj(const LayerBase *mask) { m_layerObj->m_maskObj = mask; }

void LayerAccObjBase::resetMaskObj() { m_layerObj->m_maskObj = nullptr; }

const void *LayerAccObjBase::getResData() const { return m_layerObj->m_resData; }

void LayerAccObjBase::createAnimObj(u32 id) { m_layerObj->createAnimObj(id); }

void LayerAccObjBase::endAnime() { m_layerObj->endAnime(); }

void LayerAccObjBase::createSecondTex(const void *data) { m_layerObj->createSecondTex(data); }

void LayerAccObjBase::releaseSecondTex() { m_layerObj->releaseSecondTex(); }

u16 LayerAccObjBase::getSecondTexIconMax() const { return m_layerObj->getSecondTexIconMax(); }

void LayerAccObjBase::setSecondTexIconNum(u32 num) { m_layerObj->setSecondTexIconNum(num); }

u16 LayerAccObjBase::getSecondTexIconNum() const { return m_layerObj->getSecondTexIconNum(); }

void LayerAccObjBase::setSecondTexBlend(f32 blend) { m_layerObj->setSecondTexBlend(blend); }

f32 LayerAccObjBase::getSecondTexBlend() const { return m_layerObj->getSecondTexBlend(); }

LayerAccDefObj::LayerAccDefObj(LayerBase *layer) : LayerAccObjBase(layer) {}

void LayerAccDefObj::setParm(f32 parm) {
  if (m_layerObj->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(m_layerObj)->unknown2a0 = parm;
  }
}

f32 LayerAccDefObj::getParm() const {
  if (m_layerObj->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    return static_cast<LayerObjWork *>(m_layerObj)->unknown2a0;
  }

  return 0.0f;
}

void LayerAccDefObj::setIconNum(u16 num) {
  switch (m_layerObj->unknown18) {
  case LAYER_OBJ_TYPE_OBJ:
    static_cast<LayerObjWork *>(m_layerObj)->unknown2a4 = num;
    break;
  case LAYER_OBJ_TYPE_MASK:
    static_cast<LayerObjTopMaskObj *>(m_layerObj)->unknown2d0 = num;
    break;
  }
}

u16 LayerAccDefObj::getIconNum() const {
  switch (m_layerObj->unknown18) {
  case LAYER_OBJ_TYPE_OBJ:
    return static_cast<LayerObjWork *>(m_layerObj)->unknown2a4;
  case LAYER_OBJ_TYPE_MASK:
    return static_cast<LayerObjTopMaskObj *>(m_layerObj)->unknown2d0;
  }

  return 0;
}

u16 LayerAccDefObj::getIconMax() const {
  switch (m_layerObj->unknown18) {
  case LAYER_OBJ_TYPE_OBJ:
    return static_cast<LayerObjWork *>(m_layerObj)->unknown2a6;
  case LAYER_OBJ_TYPE_MASK:
    return static_cast<LayerObjTopMaskObj *>(m_layerObj)->unknown2d2;
  }

  return 0;
}

void LayerAccDefObj::setGauge(LAYER_GAUGE gauge) {
  if (m_layerObj->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(m_layerObj)->unknown2a8 = gauge;
  }
}

LAYER_GAUGE LayerAccDefObj::getGauge() const {
  if (m_layerObj->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    return static_cast<LAYER_GAUGE>(static_cast<LayerObjWork *>(m_layerObj)->unknown2a8);
  }

  return LAYER_GAUGE_NONE;
}

LayerAccDefAnmObj::LayerAccDefAnmObj(LayerBase *layer) : LayerAccObjBase(layer) {}

f32 LayerAccDefAnmObj::getMaxSecond() const {
  if (m_layerObj->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(m_layerObj)->getMaxSecond();
  }

  return 0.0f;
}

f32 LayerAccDefAnmObj::getSecond() const {
  if (m_layerObj->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(m_layerObj)->getSecond();
  }

  return 0.0f;
}

void LayerAccDefAnmObj::setSecond(f32 second) {
  if (m_layerObj->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    static_cast<LayerObjWork *>(m_layerObj)->setSecond(second);
  }
}

void LayerAccDefAnmObj::setLoop(bool loop) {
  if (m_layerObj->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    if (loop) {
      m_layerObj->onStateFlags(0x4000);
      m_layerObj->offStateFlags(0x8000);
    } else {
      m_layerObj->onStateFlags(0x8000);
      m_layerObj->offStateFlags(0x4000);
    }
  }
}

bool LayerAccDefAnmObj::isLoop() const {
  if (m_layerObj->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    return (m_layerObj->unknowna8 & 0x80) != 0;
  }

  return false;
}

void LayerAccDefAnmObj::setPause(bool pause) {
  if (m_layerObj->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    if (pause) {
      m_layerObj->onStateFlags(0x1000);
      m_layerObj->offStateFlags(0x2000);
    } else {
      m_layerObj->onStateFlags(0x2000);
      m_layerObj->offStateFlags(0x1000);
    }
  }
}

bool LayerAccDefAnmObj::isPause() const {
  if (m_layerObj->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    return (m_layerObj->unknowna8 & 0x200) != 0;
  }

  return false;
}

u32 LayerAccDefAnmObj::getDataType() const {
  if (m_layerObj->unknown18 == LAYER_OBJ_TYPE_OBJ) {
    return static_cast<LayerObjWork *>(m_layerObj)->unknown2ac;
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

u32 LayerAccMemObj::getMemWidth() const { return m_memObj->m_memWidth; }

u32 LayerAccMemObj::getMemHeight() const { return m_memObj->m_memHeight; }

void LayerAccMemObj::setRender(bool render) { m_memObj->setRender(render); }

bool LayerAccMemObj::isRender() const { return m_memObj->isRender(); }

grlib::CGLibTextureBuffer *LayerAccMemObj::getTexture() { return m_memObj->m_cGLibRenderTarget.unknown70; }

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

unknown085 LayerAccFontStyle::getStyleInfo(u32 index) const {
  unknown085 info;
  u32 max = m_style->m_styleDataMax;
  info.unknown00 = m_style->unknown20;
  info.unknown08 = m_style->m_lyrFontStyleData;
  if (index < max) {
    info.unknown08 += index;
  }
  return info;
}

s32 LayerAccFontStyle::getStyleIndex(const char *name) const { return m_style->getStyleIndex(name); }

const char *LayerAccFontStyle::getStyleName(u32 index) const { return m_style->getStyleName(index); }

const char *LayerAccFontStyle::getFontName(u32 index) const { return m_style->getFontName(index); }

mm::mtl::Vector<layer::LayerStrInfo> *LayerAccFontStyle::createColorInfo(u32 num) { return m_style->createColorInfo(num); }

void LayerAccFontStyle::releaseColorInfo() { m_style->releaseColorInfo(); }

void *LayerAccFontStyle::getColorInfo() { return m_style->m_colorInfo; }

mm::mtl::Vector<layer::LayerStrInfo> *LayerAccFontStyle::createIconInfo(u32 num) { return m_style->createIconInfo(num); }

void LayerAccFontStyle::releaseIconInfo() { m_style->releaseIconInfo(); }

void *LayerAccFontStyle::getIconInfo() { return m_style->m_iconInfo; }

f32 LayerAccFontStyle::getRubyScale() const { return m_style->m_rubyScale; }

void LayerAccFontStyle::setRubyScale(f32 scale) { m_style->m_rubyScale = scale; }

LayerAccFontObj::LayerAccFontObj(LayerBase *layer) : LayerAccObjBase(layer) {}

void LayerAccFontObj::setHorizontal(LayerFontHorizontal horizontal) { static_cast<LayerObjFont *>(m_layerObj)->m_horizontal = horizontal; }

void LayerAccFontObj::setVertical(LayerFontVertical vertical) { static_cast<LayerObjFont *>(m_layerObj)->m_vertical = vertical; }

void LayerAccFontObj::setDisplayArea(LayerFontDisplayArea area) { static_cast<LayerObjFont *>(m_layerObj)->m_displayArea = area; }

void LayerAccFontObj::setDispSetting(LayerFontSetting setting) { static_cast<LayerObjFont *>(m_layerObj)->m_dispSetting = setting; }

void LayerAccFontObj::setBorderWeight(f32 weight) { static_cast<LayerObjFont *>(m_layerObj)->setBorderWeight(weight); }

void LayerAccFontObj::setSlopeRot(f32 rot) { static_cast<LayerObjFont *>(m_layerObj)->setSlopeRot(rot); }

LayerFontHorizontal LayerAccFontObj::getHorizontal() const { return static_cast<LayerFontHorizontal>(static_cast<LayerObjFont *>(m_layerObj)->m_horizontal); }

LayerFontVertical LayerAccFontObj::getVertical() const { return static_cast<LayerFontVertical>(static_cast<LayerObjFont *>(m_layerObj)->m_vertical); }

LayerFontDisplayArea LayerAccFontObj::getDisplayArea() const { return static_cast<LayerFontDisplayArea>(static_cast<LayerObjFont *>(m_layerObj)->m_displayArea); }

LayerFontSetting LayerAccFontObj::getDispSetting() const { return static_cast<LayerFontSetting>(static_cast<LayerObjFont *>(m_layerObj)->m_dispSetting); }

f32 LayerAccFontObj::getBorderWeight() const { return static_cast<LayerObjFont *>(m_layerObj)->getBorderWeight(); }

f32 LayerAccFontObj::getSlopeRot() const { return static_cast<LayerObjFont *>(m_layerObj)->getSlopeRot(); }

u16 LayerAccFontObj::getFontPixelX() const { return static_cast<LayerObjFont *>(m_layerObj)->m_fontPixelX; }

u16 LayerAccFontObj::getFontPixelY() const { return static_cast<LayerObjFont *>(m_layerObj)->m_fontPixelY; }

u16 LayerAccFontObj::getFontPixelWidth() const { return static_cast<LayerObjFont *>(m_layerObj)->m_fontPixelWidth; }

u16 LayerAccFontObj::getFontPixelHeight() const { return static_cast<LayerObjFont *>(m_layerObj)->m_fontPixelHeight; }

void LayerAccFontObj::setMsg(const char *text, const LayerBase *res, const LayerBase *style, u32 flags) {
  static_cast<LayerObjFont *>(m_layerObj)
      ->setMsg(reinterpret_cast<const u8 *>(text),
               reinterpret_cast<const LayerFontResObj *>(res),
               reinterpret_cast<const LayerFontStyleObj *>(style),
               LayerManager::get()->m_layerFontManager->m_layerFontIconObj,
               flags);
}

void LayerAccFontObj::setMsg(const wchar_t *text, const LayerBase *res, const LayerBase *style, u32 flags) {
  static_cast<LayerObjFont *>(m_layerObj)
      ->setMsg(text, reinterpret_cast<const LayerFontResObj *>(res), reinterpret_cast<const LayerFontStyleObj *>(style), LayerManager::get()->m_layerFontManager->m_layerFontIconObj, flags);
}

void LayerAccFontObj::setMsg(const char *text, const LayerBase *res, u32 flags) {
  LayerFontManager *fontManager = LayerManager::get()->m_layerFontManager;
  static_cast<LayerObjFont *>(m_layerObj)
      ->setMsg(reinterpret_cast<const u8 *>(text), reinterpret_cast<const LayerFontResObj *>(res), fontManager->m_layerFontStyleObj, fontManager->m_layerFontIconObj, flags);
}

void LayerAccFontObj::setMsg(const wchar_t *text, const LayerBase *res, u32 flags) {
  LayerFontManager *fontManager = LayerManager::get()->m_layerFontManager;
  static_cast<LayerObjFont *>(m_layerObj)->setMsg(text, reinterpret_cast<const LayerFontResObj *>(res), fontManager->m_layerFontStyleObj, fontManager->m_layerFontIconObj, flags);
}

void LayerAccFontObj::setMsg(const char *text) {
  LayerObjFont *object = static_cast<LayerObjFont *>(m_layerObj);
  const LayerFontResObj *res = object->m_layerFontResObj;
  const LayerFontStyleObj *style = object->m_layerFontStyleObj;
  const LayerFontIconObj *icon = object->unknown288;
  u32 flags = object->unknown298;
  if (style == nullptr) {
    style = LayerManager::get()->m_layerFontManager->m_layerFontStyleObj;
  }
  if (res == nullptr) {
    res = reinterpret_cast<const LayerFontResObj *>(LayerManager::get()->m_layerFontManager->m_layerFontIconObj);
  }
  if (icon == nullptr) {
    icon = LayerManager::get()->m_layerFontManager->m_layerFontIconObj;
  }
  object->setMsg(reinterpret_cast<const u8 *>(text), res, style, icon, flags);
}

void LayerAccFontObj::setMsg(const wchar_t *text) {
  LayerObjFont *object = static_cast<LayerObjFont *>(m_layerObj);
  const LayerFontResObj *res = object->m_layerFontResObj;
  const LayerFontStyleObj *style = object->m_layerFontStyleObj;
  const LayerFontIconObj *icon = object->unknown288;
  u32 flags = object->unknown298;
  if (style == nullptr) {
    style = LayerManager::get()->m_layerFontManager->m_layerFontStyleObj;
  }
  if (res == nullptr) {
    res = reinterpret_cast<const LayerFontResObj *>(LayerManager::get()->m_layerFontManager->m_layerFontIconObj);
  }
  if (icon == nullptr) {
    icon = LayerManager::get()->m_layerFontManager->m_layerFontIconObj;
  }
  object->setMsg(text, res, style, icon, flags);
}

void LayerAccFontObj::setColorMap(const LayerBase *colorMap, u32 index) { static_cast<LayerObjFont *>(m_layerObj)->setColorMap(reinterpret_cast<const LayerFontIconObj *>(colorMap), index); }

LayerAccLayoutObj::LayerAccLayoutObj(LayerBase *layer) : LayerAccObjBase(layer) {}

void LayerAccLayoutObj::setViewPortMode(bool viewPortMode) {
  if (viewPortMode) {
    m_layerObj->unknowna8 |= 0x10;
  } else {
    m_layerObj->unknowna8 &= ~0x10;
  }
}

void LayerAccLayoutObj::setViewPort(f32 x, f32 y, f32 width, f32 height) {
  LayerObjLayout *layout = static_cast<LayerObjLayout *>(m_layerObj);
  layout->unknown2a0.unknown10.unknown00 = x;
  layout->unknown2a0.unknown10.unknown04 = y;
  layout->unknown2a0.unknown10.unknown08 = width;
  layout->unknown2a0.unknown10.unknown0c = height;
}

void LayerAccLayoutObj::createRenderTarget(f32 x, f32 y, f32 width, f32 height, mm::Col4 clearColor) { static_cast<LayerObjLayout *>(m_layerObj)->createRenderTarget(x, y, width, height, clearColor); }

void LayerAccLayoutObj::releaseRenderTarget() { static_cast<LayerObjLayout *>(m_layerObj)->releaseRenderTarget(); }

void LayerAccLayoutObj::createPriorityTbl(u32 num) {
  static_cast<LayerObjLayout *>(m_layerObj)->unknown2a0.unknown24[LayerManager::s_nStkIdx] = num;
  m_layerObj->offStateFlags(0x800);
}

void LayerAccLayoutObj::releasePriorityTbl() {
  static_cast<LayerObjLayout *>(m_layerObj)->unknown2a0.unknown24[LayerManager::s_nStkIdx] = 0;
  m_layerObj->onStateFlags(0x800);
}

u16 LayerAccLayoutObj::getPriorityTbl() const {
  const LayerObjLayout *layout = static_cast<LayerObjLayout *>(m_layerObj);
  u16 priorityTbl = layout->unknown2a0.unknown24[LayerManager::s_nStkIdx];
  if (priorityTbl == 0) {
    priorityTbl = layout->unknown2a0.unknown28;
  }

  return priorityTbl;
}

void LayerAccLayoutObj::setAutoAnchorMode(LAYER_ANCHOR mode) { static_cast<LayerObjLayout *>(m_layerObj)->unknown2a0.m_autoAnchorMode = mode; }

LAYER_ANCHOR LayerAccLayoutObj::getAutoAnchorMode() const { return static_cast<LAYER_ANCHOR>(static_cast<LayerObjLayout *>(m_layerObj)->unknown2a0.m_autoAnchorMode); }

grlib::CGLibTextureBuffer *LayerAccLayoutObj::getTexture() { return static_cast<LayerObjLayout *>(m_layerObj)->getTexture(); }

void LayerAccLayoutObj::setRender(bool render) { static_cast<LayerObjLayout *>(m_layerObj)->setRender(render); }

bool LayerAccLayoutObj::isRender() const { return static_cast<LayerObjLayout *>(m_layerObj)->isRender(); }

LayerBase *LayerAccLayoutObj::createObj(const void *data) {
  ml::CS lock(LayerObjManager::getCriticalSection());
  LayerBase *object = LayerObjManager::createStaticObj(data);
  static_cast<LayerObjList *>(m_layerObj)->unknown270[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerAccLayoutObj::createMaskObj(const void *data) {
  ml::CS lock(LayerObjManager::getCriticalSection());
  LayerBase *object = LayerObjManager::createStaticMaskObj(data);
  static_cast<LayerObjList *>(m_layerObj)->unknown270[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerAccLayoutObj::createLayoutObj() {
  ml::CS lock(LayerObjManager::getCriticalSection());
  LayerBase *object = LayerObjManager::createStaticLayoutObj();
  static_cast<LayerObjList *>(m_layerObj)->unknown270[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerAccLayoutObj::createFontObj() {
  ml::CS lock(LayerObjManager::getCriticalSection());
  LayerBase *object = LayerObjManager::createStaticFontObj();
  static_cast<LayerObjList *>(m_layerObj)->unknown270[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerAccLayoutObj::createFilterObj() {
  ml::CS lock(LayerObjManager::getCriticalSection());
  LayerBase *object = LayerObjManager::createStaticFilterObj();
  static_cast<LayerObjList *>(m_layerObj)->unknown270[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerAccLayoutObj::createTexObj(const grlib::CGLibTextureBuffer &texture) {
  ml::CS lock(LayerObjManager::getCriticalSection());
  LayerBase *object = LayerObjManager::createStaticTexObj(texture);
  static_cast<LayerObjList *>(m_layerObj)->unknown270[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerAccLayoutObj::createMemObj(u32 width, u32 height, LayerMemType type) {
  ml::CS lock(LayerObjManager::getCriticalSection());
  LayerBase *object = LayerObjManager::createStaticMemObj(width, height, type);
  static_cast<LayerObjList *>(m_layerObj)->unknown270[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerAccLayoutObj::createPolyObj(u32 width, u32 height, u16 vertexNum, u16 indexNum, LayerPrimitiveType type) {
  ml::CS lock(LayerObjManager::getCriticalSection());
  LayerBase *object = LayerObjManager::createStaticPolyObj(width, height, vertexNum, indexNum, type);
  static_cast<LayerObjList *>(m_layerObj)->unknown270[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerAccFilterObj::LayerAccFilterObj(LayerBase *layer) : LayerAccObjBase(layer) {}

u32 LayerAccFilterObj::getFilterType() const { return static_cast<LayerObjTopFilter *>(m_layerObj)->getFilterType(); }

void LayerAccFilterObj::selectFilterOfGaussianBlur(u32 width, u32 height) { static_cast<LayerObjTopFilter *>(m_layerObj)->createGaussianBlur(width, height); }

void LayerAccFilterObj::setGaussianBlurParameter(f32 strength, f32 scale, u32 sampleNum, bool isHalf, u32 passNum) {
  static_cast<LayerObjTopFilter *>(m_layerObj)->setGaussianBlurParameter(strength, scale, sampleNum, isHalf, passNum);
}

void LayerAccFilterObj::selectFilterOfFlowMap(u32 width, u32 height, const void *data) { static_cast<LayerObjTopFilter *>(m_layerObj)->createFlowMap(width, height, data); }

void LayerAccFilterObj::setFlowMapParameter(f32 speed, f32 strength) { static_cast<LayerObjTopFilter *>(m_layerObj)->setFlowMapParameter(speed, strength); }

} // namespace layer

// The game builds the binary layout in the layer acc unit: LayerAcc and LayerAccLayoutBinary functions alternate in one contiguous range with no other unit
// between (LayerAcc 0x71008f7bc4 to 0x71008f94c0, LayerAccLayoutBinary 0x71008f957c to 0x71008f9c48, then LayerAccFilterObj 0x71008f9d68 to 0x71008f9d94).
#include "layer_acc_layout_binary.cpp"
