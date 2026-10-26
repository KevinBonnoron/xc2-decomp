#include "event/dof_manager.h"

#include "bdat.h"
#include "event/manager.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "ml/scn.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "scn/scn_render_dr_sys_parm_acc.h"

namespace event {

namespace {

f32 getValF32(unsigned char *bdat, const char *name, int id) {
  Bdat::Value value;
  value.valueU32 = Bdat::getValCheck(bdat, name, id, 8);
  return value.valueF32;
}

} // namespace

void DofManager::render() {
  if (!(unknown10 & DISP_FLAG_DISP)) {
    return;
  }
  ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->unknown38, 0);
  int width = ml::DevGraph::getRootWidth();
  int rectX = width - 200;
  int height = ml::DevGraph::getRootHeight();
  int rectY = height - 275;
  fw::debug::drawSquare2D(mm::Rect<s32>(rectX, rectY, 180, 210), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(rectX, rectY, 180, 210), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  int titleX = width - 195;
  fw::debug::drawFont(titleX, height - 270, "DOF");
  if (!parmAcc.isDOFAutoFocus()) {
    fw::debug::drawFont(titleX, height - 270, "         [distance]");
  } else {
    fw::debug::drawFont(titleX, height - 270, "         [simple]");
  }
  if (parmAcc.isDOF()) {
    int x = width - 190;
    int y = height - 253;
    if (!parmAcc.isDOFAutoFocus()) {
      fw::debug::drawFont(x, y, "axis:     %s", getAxisName(m_axis));
      fw::debug::drawFont(x, height - 236, "dist:     %.2f", parmAcc.getDoFDistance());
      fw::debug::drawFont(x, height - 219, "range:    %.2f", parmAcc.getDoFRange());
    } else {
      if (parmAcc.getDOFFocusNum() < 1) {
        fw::debug::drawFont(x, y, "foNo:     AUTO");
      } else {
        fw::debug::drawFont(x, y, "foNo:     %d", parmAcc.getDOFFocusNum());
      }
      fw::debug::drawFont(x, height - 236, "foMin:    %.2f", parmAcc.getDOFFocusMin());
    }
    fw::debug::drawFont(titleX, height - 190, "DETAIL");
    if (*unknown50 != '\0') {
      fw::debug::drawFont(titleX, height - 190, "         [%s]", unknown50);
    }
    fw::debug::drawFont(x, height - 173, "pixel:    %.2f", parmAcc.getDoFPixlRatio());
    fw::debug::drawFont(x, height - 156, "lens:     %.2f", parmAcc.getDoFLens());
    fw::debug::drawFont(x, height - 139, "strength: %.2f", parmAcc.getDoFStrength());
    fw::debug::drawFont(x, height - 122, "blend:    %.2f", parmAcc.getDoFBlend());
    fw::debug::drawFont(x, height - 105, "pixelLv:  %d", parmAcc.getDofPixlLv());
    fw::debug::drawFont(x, height - 88, "hlv:  %s", parmAcc.isDofHLvMode() ? "ON" : "OFF");
  }
}

const char *DofManager::getAxisName(int axis) {
  if (axis < 3) {
    if (axis == 1) {
      return "CAM";
    }
    if (axis == 2) {
      return "SAY";
    }
    return "NONE";
  }
  if (static_cast<u32>(axis) > mm::mtl::Singleton<ObjectManager>::getPtr()->getCharaCount() + 3) {
    return "NONE";
  }
  ObjectChara *chara = mm::mtl::Singleton<ObjectManager>::getPtr()->getChara(axis - 3);
  if (chara == nullptr) {
    return "ERR";
  }
  return chara->getName();
}

DofManager::DofManager()
    : unknown10(0), unknown14(0), m_axis(1), m_dist(0.0f), unknown20(0.0f), unknown24(5.0f), unknown28(false), unknown2c(0), unknown30(0.1f), unknown34(5.0f), unknown38(0.6f), unknown3c(4.0f),
      unknown40(1.0f), unknown44(0), unknown48(false), unknown50("") {}

void DofManager::stop() {
  unsigned char *bdat = Bdat::getFP("EVT_dof");
  unknown14 = 0;
  m_axis = 1;
  m_dist = getValF32(bdat, "dist", Bdat::getIdTop(bdat));
  unknown20 = getValF32(bdat, "dist", Bdat::getIdTop(bdat));
  unknown24 = getValF32(bdat, "range", Bdat::getIdTop(bdat));
  unknown28 = false;
  unknown2c = 0;
  unknown30 = 0.1f;
  unknown34 = getValF32(bdat, "pixel", Bdat::getIdTop(bdat));
  unknown38 = getValF32(bdat, "lens", Bdat::getIdTop(bdat));
  unknown3c = getValF32(bdat, "strength", Bdat::getIdTop(bdat));
  unknown40 = getValF32(bdat, "blend", Bdat::getIdTop(bdat));
  unknown44 = static_cast<s16>(Bdat::getValCheck(bdat, "pixelLv", Bdat::getIdTop(bdat), 5));
  unknown48 = static_cast<s16>(Bdat::getValCheck(bdat, "hlv", Bdat::getIdTop(bdat), 5)) > 0;
  unknown50 = "";
  ml::Scn *scn = Manager::get()->getScn();
  if (scn != nullptr) {
    ml::ScnRenderDrSysParmAcc parmAcc(scn->unknown38, 0);
    parmAcc.setDOF(false);
    parmAcc.setDOFOverride(true);
    parmAcc.setDoFDistance(unknown20);
    parmAcc.setDoFRange(unknown24);
    parmAcc.setDOFAutoFocus(unknown28);
    parmAcc.setDOFFocusNum(unknown2c);
    parmAcc.setDOFFocusMin(unknown30);
    parmAcc.setDoFPixlRatio(unknown34);
    parmAcc.setDoFLens(unknown38);
    parmAcc.setDoFStrength(unknown3c);
    parmAcc.setDoFBlend(unknown40);
    parmAcc.setDofPixlLv(unknown44);
    parmAcc.setDofHLvMode(unknown48);
  }
}

void DofManager::clear() { stop(); }

void DofManager::update() {
  if (!(unknown14 & FLAG_ENABLE)) {
    return;
  }
  if (unknown28) {
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->unknown38, 0);
    parmAcc.setDOF(true);
    parmAcc.setDOFOverride(true);
    parmAcc.setDoFDistance(0.0f);
    parmAcc.setDoFRange(0.0f);
    parmAcc.setDOFAutoFocus(true);
    parmAcc.setDOFFocusNum(unknown2c);
    parmAcc.setDOFFocusMin(unknown30);
    parmAcc.setDoFPixlRatio(unknown34);
    parmAcc.setDoFLens(unknown38);
    parmAcc.setDoFStrength(unknown3c);
    parmAcc.setDoFBlend(unknown40);
    parmAcc.setDofPixlLv(unknown44);
    parmAcc.setDofHLvMode(unknown48);
  } else {
    if (m_axis == 0) {
      return;
    }
    if (unknown14 & FLAG_CHANGED) {
      unknown20 = calcDist(m_axis, m_dist);
    }
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->unknown38, 0);
    parmAcc.setDOF(true);
    parmAcc.setDOFOverride(true);
    parmAcc.setDoFDistance(unknown20);
    parmAcc.setDoFRange(unknown24);
    parmAcc.setDOFAutoFocus(false);
    parmAcc.setDOFFocusNum(0);
    parmAcc.setDOFFocusMin(0.0f);
    parmAcc.setDoFPixlRatio(unknown34);
    parmAcc.setDoFLens(unknown38);
    parmAcc.setDoFStrength(unknown3c);
    parmAcc.setDoFBlend(unknown40);
    parmAcc.setDofPixlLv(unknown44);
    parmAcc.setDofHLvMode(unknown48);
  }
  unknown14 &= ~FLAG_CHANGED;
}

void DofManager::play(int axis, f32 dist, f32 range, f32 pixel, f32 lens, f32 strength, f32 blend, int pixelLv, bool isHlv, const char *name) {
  unknown14 |= FLAG_ENABLE | FLAG_CHANGED;
  m_axis = axis;
  m_dist = dist;
  unknown20 = dist;
  unknown24 = range;
  unknown28 = false;
  unknown34 = pixel;
  unknown38 = lens;
  unknown3c = strength;
  unknown40 = blend;
  unknown44 = pixelLv;
  unknown48 = isHlv;
  unknown50 = name;
}

void DofManager::play(int axis, int id) {
  unsigned char *bdat = Bdat::getFP("EVT_dof");
  play(axis,
       getValF32(bdat, "dist", id),
       getValF32(bdat, "range", id),
       getValF32(bdat, "pixel", id),
       getValF32(bdat, "lens", id),
       getValF32(bdat, "strength", id),
       getValF32(bdat, "blend", id),
       static_cast<s16>(Bdat::getValCheck(bdat, "pixelLv", id, 5)),
       static_cast<s16>(Bdat::getValCheck(bdat, "hlv", id, 5)) > 0,
       reinterpret_cast<const char *>(Bdat::getValCheck(bdat, "name", id, 7)));
}

void DofManager::playSimple(int focusNum, f32 focusMin, f32 pixel, f32 lens, f32 strength, f32 blend, int pixelLv, bool isHlv, const char *name) {
  unknown28 = true;
  unknown14 |= FLAG_ENABLE | FLAG_CHANGED;
  unknown2c = focusNum;
  unknown30 = focusMin;
  unknown34 = pixel;
  unknown38 = lens;
  unknown3c = strength;
  unknown40 = blend;
  unknown44 = pixelLv;
  unknown48 = isHlv;
  unknown50 = name;
}

void DofManager::playSimple(int focusNum, int id) {
  unsigned char *bdat = Bdat::getFP("EVT_dof");
  playSimple(focusNum,
             getValF32(bdat, "foMin", id),
             getValF32(bdat, "pixel", id),
             getValF32(bdat, "lens", id),
             getValF32(bdat, "strength", id),
             getValF32(bdat, "blend", id),
             static_cast<s16>(Bdat::getValCheck(bdat, "pixelLv", id, 5)),
             static_cast<s16>(Bdat::getValCheck(bdat, "hlv", id, 5)) > 0,
             reinterpret_cast<const char *>(Bdat::getValCheck(bdat, "name", id, 7)));
}

void DofManager::setEnable(bool isEnable) { setFlag(FLAG_ENABLE | FLAG_CHANGED, isEnable); }

bool DofManager::isEnable() const { return (unknown14 & FLAG_ENABLE) != 0; }

void DofManager::setAxis(int axis) {
  setChanged();
  m_axis = axis;
  unknown28 = false;
}

int DofManager::getAxis() const { return m_axis; }

void DofManager::setDist(f32 dist) {
  setChanged();
  m_dist = dist;
  unknown28 = false;
}

f32 DofManager::getDist() const { return m_dist; }

void DofManager::setRange(f32 range) {
  setChanged();
  unknown24 = range;
  unknown28 = false;
}

void DofManager::setFocusNum(int focusNum) {
  setChanged();
  unknown28 = true;
  unknown2c = focusNum;
}

void DofManager::setFocusMin(f32 focusMin) {
  setChanged();
  unknown28 = true;
  unknown30 = focusMin;
}

void DofManager::setPixel(f32 pixel) {
  setChanged();
  unknown34 = pixel;
}

void DofManager::setLens(f32 lens) {
  setChanged();
  unknown38 = lens;
}

void DofManager::setStrength(f32 strength) {
  setChanged();
  unknown3c = strength;
}

void DofManager::setBlend(f32 blend) {
  setChanged();
  unknown40 = blend;
}

void DofManager::setPixelLv(int pixelLv) {
  setChanged();
  unknown44 = pixelLv;
}

void DofManager::setHlv(bool isHlv) {
  setChanged();
  unknown48 = isHlv;
}

void DofManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown10 |= DISP_FLAG_DISP;
  } else {
    unknown10 &= ~DISP_FLAG_DISP;
  }
}

bool DofManager::isDisp() const { return (unknown10 & DISP_FLAG_DISP) != 0; }

void DofManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER_POST:
    render();
    break;
  default:
    break;
  }
  if (type == MSG_TYPE_CLEAR) {
    clear();
  }
}

} // namespace event
