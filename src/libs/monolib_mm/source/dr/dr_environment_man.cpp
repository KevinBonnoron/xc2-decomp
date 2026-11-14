#include "dr/dr_environment_man.h"

#include <math.h>
#include <string.h>

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_clip_work_view_plane.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_env_coli_man.h"
#include "dr/dr_environment_anim.h"
#include "dr/dr_environment_lgt_list.h"
#include "dr/dr_environment_obj.h"
#include "dr/dr_environment_obj_lgt.h"
#include "dr/dr_environment_tex.h"
#include "dr/dr_environment_time.h"
#include "dr/dr_fog_man.h"
#include "dr/dr_fog_obj_gbl.h"
#include "dr/dr_ini_sys.h"
#include "dr/dr_light_man.h"
#include "dr/dr_light_obj.h"
#include "dr/dr_light_obj_local_ibl.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_res_wrk_clip_list.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"
#include "ml/file_res_th.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

void DrEnvironmentObj::release() { unknown8c |= FLAG_UNKNOWN_30 << DrMan::s_nDblStockIdx; }

DrEnvironmentObj::DrEnvironmentObj(DrMan *drMan, DrLightMan *lightMan, DrFogMan *fogMan)
    : unknown08(nullptr), unknown10(nullptr), unknown18(drMan), unknown20(lightMan), unknown28(fogMan), unknown70(0.0f, 0.0f, 0.0f), m_frame(0.0f), m_frameSpd(1.0f), m_maxFrame(0.0f), unknown8c(0),
      unknown90(0) {
  m_matrix = mm::Mat44::identity;
}

void DrEnvironmentMan::releaseObj(DrEnvironmentObj *obj) { obj->release(); }

void DrEnvironmentMan::releaseAll() {
  unknown2100(unknown28[0], unknown28[1]);
  unknown2100(unknown28[2], unknown28[3]);
  unknown2100(unknown58, unknown60);
  unknown2100(unknown48, unknown50);
}

DrEnvironmentMan::DrEnvironmentMan(DrMan *drMan, DrLightMan *lightMan, DrFogMan *fogMan, int screen)
    : unknown00(drMan), unknown08(lightMan), unknown10(fogMan), unknown20(screen), unknown28(), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr), unknown60(nullptr), unknown68(nullptr) {
  unknown18 = new (drMan->unknown0c) DrEnvColiMan(drMan);
}

DrEnvironmentMan::~DrEnvironmentMan() {
  if (unknown68 != nullptr) {
    FileResTh *res = unknown00->unknown70->unknown890;
    if (res != nullptr) {
      res->Release();
    }
  }
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  releaseAll();
}

void DrEnvironmentMan::updateCameraLight() {
  if (unknown20 != 0) {
    return;
  }
  if (unknown00->unknown1da0) {
    if (unknown68 == nullptr) {
      FileResTh *res = unknown00->unknown70->unknown890;
      res->AddRef();
      unknown68 = createObj(res->unknownc8);
    }
    unknown68->unknown8c &= ~DrEnvironmentObj::FLAG_UNKNOWN_0;
  } else if (unknown68 != nullptr) {
    unknown68->unknown8c |= DrEnvironmentObj::FLAG_UNKNOWN_0;
  }
}

void DrEnvironmentMan::renderLgt() {
  for (DrEnvironmentObj *obj = unknown48; obj != nullptr; obj = obj->unknown10) {
    obj->renderLgt();
  }
}

void DrEnvironmentMan::setZoneObj(DrEnvironmentObj *obj, bool isOn) {
  if (isOn) {
    for (DrEnvironmentObj *current = unknown48; current != nullptr; current = current->unknown10) {
      if (current->unknown8c & DrEnvironmentObj::FLAG_UNKNOWN_1) {
        current->unknown8c &= ~DrEnvironmentObj::FLAG_UNKNOWN_0;
      }
    }
  } else {
    for (DrEnvironmentObj *current = unknown48; current != nullptr; current = current->unknown10) {
      if (current->unknown8c & DrEnvironmentObj::FLAG_UNKNOWN_1) {
        current->unknown8c |= DrEnvironmentObj::FLAG_UNKNOWN_0;
      }
    }
  }
}

f32 DrEnvironmentObj::getFrame() const { return m_frame; }

f32 DrEnvironmentObj::getMaxFrame() const { return m_maxFrame; }

void DrEnvironmentObj::setFrameSpd(f32 speed) { m_frameSpd = speed; }

f32 DrEnvironmentObj::getFrameSpd() { return m_frameSpd; }

DrEnvironmentObjLgt::~DrEnvironmentObjLgt() { releaseLgt(); }

void DrEnvironmentObjLgt::releaseLgt() {
  if (unknown1fc != 0) {
    if (unknown1e8 != 0 && unknown1b0 != nullptr) {
      for (int i = 0; i < unknown1e8; i++) {
        unknown1b0[i].~DrLightObjAmb();
      }
    }
    if (unknown1ec != 0 && unknown1b8 != nullptr) {
      for (int i = 0; i < unknown1ec; i++) {
        unknown1b8[i].~DrLightObjDir();
      }
    }
    if (unknown1f0 != 0 && unknown1c0 != nullptr) {
      for (int i = 0; i < unknown1f0; i++) {
        unknown1c0[i].~DrLightObjPnt();
      }
    }
    if (unknown1f4 != 0 && unknown1c8 != nullptr) {
      for (int i = 0; i < unknown1f4; i++) {
        unknown1c8[i].~DrLightObjSpt();
      }
    }
    if (unknown1f8 != 0 && unknown1d0 != nullptr) {
      for (int i = 0; i < unknown1f8; i++) {
        unknown1d0[i].~DrLightObjLocalIBL();
      }
    }
    unknown1fc = 0;
  }
  if (unknown200 != 0) {
    for (int i = 0; i < unknown200; i++) {
      unknown1d8[i].~DrFogObjGbl();
    }
    unknown200 = 0;
  }
  unknown98.releaseTexture();
  if (unknown180 != nullptr) {
    mtl::MemManager::deallocate(unknown180, 0, false);
    unknown180 = nullptr;
  }
}

void DrEnvironmentObjLgt::resourceInit() { setupLgt(unknown150); }

void DrEnvironmentObjLgt::setupFog(DrFogObjGbl *fog, const LgtGlbFogObj *data) {
  fog->unknown20 = mm::Col3(data->unknown00[0], data->unknown00[1], data->unknown00[2]);
  fog->unknown2c = mm::Col3(data->unknown0c[0], data->unknown0c[1], data->unknown0c[2]);
  fog->unknown38 = mm::Col3(data->unknown18[0], data->unknown18[1], data->unknown18[2]);
  fog->unknown44 = data->unknown24;
  fog->unknown48 = data->unknown28;
  fog->unknown4c = data->unknown2c;
  fog->unknown50 = data->unknown50;
  fog->unknown4c = data->unknown2c;
  fog->unknown54 = data->unknown30;
  fog->unknown58 = data->unknown34;
  fog->unknown5c = data->unknown38;
  fog->unknown60 = data->unknown3c;
  fog->unknown64 = data->unknown40;
}

void DrEnvironmentObjLgt::setupAmbient(DrEnvironmentLgtList *list, DrLightObjAmb *light, const LgtObjData *data, int screen) {
  mm::Col3 color(data->unknown0c[0], data->unknown0c[1], data->unknown0c[2]);
  f32 intensity = data->unknown18;
  light->unknown30 = mm::Col3(color.r * intensity, color.g * intensity, color.b * intensity);
  list->m_lightObj = light;
  if (data->unknown00 != 0) {
    const unknown003 *amb = reinterpret_cast<const unknown003 *>(reinterpret_cast<const u8 *>(unknown158) + data->unknown00);
    DrPixlPostParm *postParm = unknown18->unknown120[screen];
    postParm->unknown1064 = amb->unknown00;
  }
}

void DrEnvironmentObjLgt::setupDirectinal(DrEnvironmentLgtList *list, DrLightObjDir *light, const LgtObjData *data, const LgtPosData *pos) {
  const unknown002 *dir = reinterpret_cast<const unknown002 *>(reinterpret_cast<const u8 *>(unknown158) + data->unknown00);
  if (data->unknown08 & 0x80000) {
    light->unknown80.a = dir->unknown01 * 0.01f;
  }
  if (dir->unknown02 == 1) {
    light->setSoftShadow(true);
  }
  mm::Col3 color(data->unknown18 * data->unknown0c[0], data->unknown18 * data->unknown0c[1], data->unknown18 * data->unknown0c[2]);
  light->unknown80.r = color.r;
  light->unknown80.g = color.g;
  light->unknown80.b = color.b;
  light->setMat(pos->unknown00);
  light->unknown90 = dir->unknown04;
  list->m_lightObj = light;
}

void DrEnvironmentObjLgt::setupPoint(DrEnvironmentLgtList *list, DrLightObjPnt *light, const LgtObjData *data, const LgtPosData *pos) {
  const unknown004 *pnt = reinterpret_cast<const unknown004 *>(reinterpret_cast<const u8 *>(unknown158) + data->unknown00);
  mm::Col3 color(data->unknown0c[0], data->unknown0c[1], data->unknown0c[2]);
  f32 intensity = data->unknown18;
  light->unknown90 = mm::Col3(color.r * intensity, color.g * intensity, color.b * intensity);
  light->setMat(pos->unknown00);
  light->unknownb0 = pnt->unknown08;
  light->m_size = pos->unknown4c;
  light->unknownac = pnt->unknown0c;
  light->unknowna4 = data->unknown24 == 0.0f ? 1.0f : data->unknown24;
  if (data->unknown08 & 0x10) {
    light->setAmbModeOn(true);
  }
  if (pnt->unknown00 == 1) {
    light->setSoftShadow(true);
  }
  if (data->unknown08 & 0x10000000) {
    light->setSubtractOn(true);
  }
  list->m_lightObj = light;
}

void DrEnvironmentObjLgt::setupSpot(DrEnvironmentLgtList *list, DrLightObjSpt *light, const LgtObjData *data, const LgtPosData *pos) {
  const unknown005 *spt = reinterpret_cast<const unknown005 *>(reinterpret_cast<const u8 *>(unknown158) + data->unknown00);
  mm::Col3 color(data->unknown0c[0], data->unknown0c[1], data->unknown0c[2]);
  f32 intensity = data->unknown18;
  light->unknownb0 = mm::Col3(color.r * intensity, color.g * intensity, color.b * intensity);
  light->setMat(pos->unknown00);
  light->m_size = pos->unknown4c;
  light->unknownbc = spt->unknown10;
  light->unknownd0 = spt->unknown0c;
  f32 value = spt->unknown1c;
  if (value <= 0.0f) {
    value = 4.0f;
  }
  light->unknownd8 = value;
  light->unknownc8 = data->unknown24 == 0.0f ? 1.0f : data->unknown24;
  if (data->unknown08 & 0x10) {
    light->setAmbModeOn(true);
  }
  if (spt->unknown00 == 1) {
    light->setSoftShadow(true);
  }
  if (data->unknown08 & 0x1000) {
    light->setCharShadow(true);
  }
  if (data->unknown08 & 0x2000) {
    light->setBaseMapShadow(true);
  }
  if (data->unknown08 & 0x4000) {
    light->setInstMapShadow(true);
  }
  if (data->unknown08 & 0x8000) {
    light->setInstSelMapShadow(true);
  }
  if (data->unknown08 & 0x10000000) {
    light->setSubtractOn(true);
  }
  light->unknowndc = spt->unknown20;
  light->unknowne0 = spt->unknown08;
  light->unknowne4 = spt->unknown14;
  list->m_lightObj = light;
}

void DrEnvironmentObjLgt::changeMemCall(const void *data) {
  unknown158 = static_cast<const LgtFileHeader *>(data);
  const LgtFileHeader *header = static_cast<const LgtFileHeader *>(data);
  const u8 *base = static_cast<const u8 *>(data);
  if (header->unknown08 != 0) {
    const unknown010 *objTable = reinterpret_cast<const unknown010 *>(base + header->unknown08);
    const LgtObjData *obj = reinterpret_cast<const LgtObjData *>(base + objTable->unknown04);
    unknown160 = obj;
    if (header->unknown20 != 0) {
      unknowne0.changeMemAnim(base, header->unknown20);
    } else if (objTable->unknown28 != 0) {
      unknowne0.changeMemAnim(base, objTable->unknown28);
    }
    const unknown011 *posTable = reinterpret_cast<const unknown011 *>(base + header->unknown0c);
    const LgtPosData *pos = reinterpret_cast<const LgtPosData *>(base + posTable->unknown04);
    unknown170 = reinterpret_cast<const LgtPosTreeRange *>(base + posTable->unknown0c);
    int lightNum = posTable->unknown00;
    for (int i = 0; i < lightNum; i++, obj++, pos++) {
      unknown198[i].m_lgtObjData = obj;
      unknown198[i].m_lgtPosData = pos;
    }
  }
  if (header->unknown14 != 0) {
    const u8 *file = reinterpret_cast<const u8 *>(unknown158);
    unknown168 = reinterpret_cast<const LgtGlbFogObj *>(file + reinterpret_cast<const unknown001 *>(file + header->unknown14)->unknown00);
  }
  if (header->unknown28 & 0x10000) {
    unknown190->changeMemCall(reinterpret_cast<const u8 *>(unknown158), header->unknown2c);
  }
  unknowna8.changeMemEnvTimeData(header, reinterpret_cast<const u8 *>(unknown158));
  if (header->unknown24 != 0) {
    const u8 *file = reinterpret_cast<const u8 *>(unknown158);
    unknown178 = reinterpret_cast<const unknown008 *>(file + reinterpret_cast<const unknown012 *>(file + header->unknown24)->unknown04);
  }
}

void DrEnvironmentObjLgt::setupBox(DrEnvironmentLgtList *list, DrLightObjSpt *light, const LgtObjData *data, const LgtPosData *pos) {}

void DrEnvironmentObjLgt::setupCapsule(DrEnvironmentLgtList *list, DrLightObjSpt *light, const LgtObjData *data, const LgtPosData *pos) {}

void DrEnvironmentObjLgt::setFrame(f32 frame) {
  m_frame = frame;
  unknowne0.setFrame(frame);
}

void DrEnvironmentObjLgt::update() {
  if (unknown8c & FLAG_UNKNOWN_0) {
    unknown007();
    DrEnvironmentLgtList **lists = unknown1a8;
    for (int i = 0; i < unknown1e4; i++, lists++) {
      DrEnvironmentLgtList *list = *lists;
      (this->*s_pCallEnvRelase[list->m_lgtObjData->unknown04])(list->m_lightObj);
    }
  } else {
    DrMan *drMan = unknown18;
    DrPixlPostParm *postParm = drMan->unknown120[drMan->unknown1c98];
    unknowna8.unknown14 = drMan->unknown1cac;
    int weather = unknown208;
    unknown208 = postParm->unknown107c;
    unknowna8.setWeatherNum(drMan, weather != unknown208, unknown150);
    unknown204 = 0;
    if (unknown1fc != 0) {
      updatePosLgt();
    }
    if (unknown200 != 0) {
      updateFog();
    }
  }
}

void DrEnvironmentObjLgt::updatePosLgt() {
  u32 size = (unknown1fc / 32 + 1) * sizeof(u32);
  memset(unknown188, 0, size + (32 - size % 32) % 32);
  unknown007();
  if (unknown190 != nullptr) {
    unknown190->update(unknown18->unknown580->unknown18);
  }
  DrCalcViewWork *viewWork = unknown18->unknown580->unknown10;
  m_frame += m_frameSpd;
  if (m_maxFrame < m_frame) {
    m_frame = 0.0f;
  }
  unknown210.x = viewWork->unknown400.x - unknown70.x;
  unknown210.y = viewWork->unknown400.y - unknown70.y;
  unknown210.z = viewWork->unknown400.z - unknown70.z;
  if (unknown8c & FLAG_UNKNOWN_3) {
    setupCalcMatrix();
    calcLgtPos(viewWork);
  } else {
    if (unknown70.x != unknown220.x || unknown70.y != unknown220.y || unknown70.z != unknown220.z) {
      unknown220.x = unknown70.x;
      unknown220.y = unknown70.y;
      unknown220.z = unknown70.z;
      setupOfsPos();
    }
    calcTreePos(unknown170, viewWork);
  }
  DrEnvironmentLgtList **lists = unknown1a8;
  for (int i = 0; i < unknown1e4; i++, lists++) {
    DrEnvironmentLgtList *list = *lists;
    if (!(unknown188[list->unknown1c >> 5] & (1 << (list->unknown1c & 31)))) {
      (this->*s_pCallEnvRelase[list->m_lgtObjData->unknown04])(list->m_lightObj);
    }
  }
  if (unknown204 & 2) {
    unknown20->unknown12c = unknown230;
  }
}

void DrEnvironmentObjLgt::updateFog() {
  if (unknown200 > 0) {
    const u8 *data = reinterpret_cast<const u8 *>(unknown158);
    DrCalcViewWork *viewWork = unknown18->unknown580->unknown10;
    const unknown001 *table = reinterpret_cast<const unknown001 *>(data + unknown158->unknown14);
    const LgtGlbFogObj *fog = reinterpret_cast<const LgtGlbFogObj *>(data + table->unknown00);
    for (int i = 0; i < unknown200; i++, fog++) {
      (this->*s_pCallFogCall[fog->unknown4a])(&unknown1d8[i], viewWork, fog);
    }
  }
  unknown28->m_fogOn = true;
}

void DrEnvironmentObjLgt::calcLgtPos(DrCalcViewWork *viewWork) {
  for (int i = 0; i < unknown1fc; i++) {
    calcLgtObj(i, viewWork);
  }
}

void DrEnvironmentObjLgt::calcTreePos(const LgtPosTreeRange *range, DrCalcViewWork *viewWork) {
  int lightNum = range->unknown22;
  const int *lights = reinterpret_cast<const int *>(reinterpret_cast<const u8 *>(unknown158) + range->unknown1c);
  for (int i = 0; i < lightNum; i++, lights++) {
    calcLgtObj(*lights, viewWork);
  }
  int childNum = range->unknown20;
  const u16 *children = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown158) + range->unknown18);
  for (int i = 0; i < childNum; i++, children++) {
    const LgtPosTreeRange *child = unknown170 + *children;
    if (child->unknown00[0] < unknown210.x || child->unknown0c[0] > unknown210.x || child->unknown00[1] < unknown210.y || child->unknown0c[1] > unknown210.y || child->unknown00[2] < unknown210.z ||
        child->unknown0c[2] > unknown210.z) {
      continue;
    }
    calcTreePos(child, viewWork);
  }
}

void DrEnvironmentObjLgt::calcLgtObj(int index, DrCalcViewWork *viewWork) {
  DrEnvironmentLgtList *list = &unknown198[index];
  const LgtObjData *data = list->m_lgtObjData;
  if (data->unknown08 & 0x10000) {
    u16 anim = data->unknown28;
    const DrEnvironmentAnim::unknown001 *animRange = &unknowne0.unknown00[anim];
    f32 &frame = unknowne0.unknown30[anim];
    frame += m_frameSpd;
    if (frame > animRange->unknown0c) {
      frame = animRange->unknown0c - frame + animRange->unknown08;
    }
  }
  if (data->unknown08 & 0x400) {
    list->unknown18 = 1.0f;
  } else if (!(this->*s_pCallEnvChk[data->unknown04])(list, viewWork, data)) {
    return;
  }
  if ((this->*s_pCallCalcEnv[data->unknown04])(list, viewWork)) {
    unknown188[index >> 5] |= 1 << (index & 31);
    list->m_lightObj->update(unknown20);
    unknown1a0[unknown1e0] = list;
    unknown1e0++;
  }
}

void DrEnvironmentObjLgt::renderLgt() {
  if (unknown8c & FLAG_UNKNOWN_0) {
    return;
  }
  if (unknown1fc != 0 && unknown1e0 != 0) {
    DrShdLgtMan *shdLgtMan = unknown18->unknown80->unknown18;
    DrEnvironmentLgtList **lists = unknown1a0;
    for (int i = 0; i < unknown1e0; i++, lists++) {
      DrEnvironmentLgtList *list = *lists;
      DrLightObj *light = list->m_lightObj;
      (this->*s_pCallLgtRender[list->m_lgtObjData->unknown04])(light, shdLgtMan);
    }
  }
}

void DrEnvironmentObjLgt::debugRenderLgt() {
  if (unknown1fc != 0 && unknown1e0 != 0) {
    renderLgt();
  }
}

void DrEnvironmentObjLgt::debugRenderLgt2D() {
  if (!(unknown8c & FLAG_UNKNOWN_0) && unknown1fc != 0) {
    DrShdLgtMan *shdLgtMan = unknown18->unknown80->unknown18;
    if (unknown8c & FLAG_UNKNOWN_20) {
      for (int i = 0; i < unknown1fc; i++) {
        DrEnvironmentLgtList *list = &unknown198[i];
        DrLightObj *light = list->m_lightObj;
        (this->*s_pCallLgtRender2D[list->m_lgtObjData->unknown04])(light, shdLgtMan);
      }
    }
  }
}

bool DrEnvironmentObjLgt::callback_Chk_Ambinet_Directional(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data) {
  if (data->unknown08 & 1) {
    const LgtPosData *pos = list->m_lgtPosData;
    f32 x = unknown210.x - pos->unknown50[0];
    f32 y = unknown210.y - pos->unknown50[1];
    f32 z = unknown210.z - pos->unknown50[2];
    if (x * x + y * y + z * z > pos->unknown5c * pos->unknown5c) {
      return false;
    }
  }
  if (data->unknown22 != 0 && (unknown8c & FLAG_UNKNOWN_2) && unknown90 != data->unknown22) {
    return false;
  }
  list->unknown18 = 1.0f;
  return true;
}

bool DrEnvironmentObjLgt::callback_Chk_Point(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data) {
  const LgtPosData *pos = list->m_lgtPosData;
  if (pos->unknown60 != 0) {
    int clipIdx = pos->unknown60 - 1;
    if (unknown190->unknown18[clipIdx >> 5] & (1 << (clipIdx & 31))) {
      return false;
    }
  }
  if (unknown006(pos->unknown62)) {
    return false;
  }
  if (data->unknown08 & 1) {
    f32 x = unknown210.x - pos->unknown50[0];
    f32 y = unknown210.y - pos->unknown50[1];
    f32 z = unknown210.z - pos->unknown50[2];
    f32 distSq = x * x + y * y + z * z;
    f32 range = pos->unknown5c + pos->unknown4c;
    if (distSq > range * range) {
      return false;
    }
    f32 fadeStart = range * 0.75f;
    if (distSq > fadeStart * fadeStart) {
      list->unknown18 = 1.0f - (sqrtf(distSq) - fadeStart) / (range - fadeStart);
    } else {
      list->unknown18 = 1.0f;
    }
  } else {
    list->unknown18 = 1.0f;
  }
  if (data->unknown22 != 0 && (unknown8c & FLAG_UNKNOWN_2) && unknown90 != data->unknown22) {
    return false;
  }
  DrLightObjPnt *light = static_cast<DrLightObjPnt *>(list->m_lightObj);
  if (data->unknown08 & 0x40000) {
    unknowne0.calcAnimTransPnt(light, data, unknown70);
  }
  const mm::Vec3 &position = light->m_pos;
  return viewWork->unknown4e0.clipTest(position, pos->unknown4c);
}

bool DrEnvironmentObjLgt::callback_Chk_Spot(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data) {
  const LgtPosData *pos = list->m_lgtPosData;
  if (pos->unknown60 != 0) {
    int clipIdx = pos->unknown60 - 1;
    if (unknown190->unknown18[clipIdx >> 5] & (1 << (clipIdx & 31))) {
      return false;
    }
  }
  if (unknown006(pos->unknown62)) {
    return false;
  }
  if (data->unknown08 & 1) {
    f32 x = unknown210.x - pos->unknown50[0];
    f32 y = unknown210.y - pos->unknown50[1];
    f32 z = unknown210.z - pos->unknown50[2];
    f32 distSq = x * x + y * y + z * z;
    f32 range = pos->unknown5c + pos->unknown4c;
    if (distSq > range * range) {
      return false;
    }
    f32 fadeStart = range * 0.75f;
    if (distSq > fadeStart * fadeStart) {
      list->unknown18 = 1.0f - (sqrtf(distSq) - fadeStart) / (range - fadeStart);
    } else {
      list->unknown18 = 1.0f;
    }
  } else {
    list->unknown18 = 1.0f;
  }
  if (data->unknown22 != 0 && (unknown8c & FLAG_UNKNOWN_2) && unknown90 != data->unknown22) {
    return false;
  }
  DrLightObjSpt *light = static_cast<DrLightObjSpt *>(list->m_lightObj);
  if (data->unknown08 & 0x40000) {
    unknowne0.calcAnimTransSpt(light, data, unknown70);
  }
  const mm::Vec3 &position = light->m_pos;
  return viewWork->unknown4e0.clipTest(position, pos->unknown4c);
}

bool DrEnvironmentObjLgt::callback_Chk_non(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data) { return false; }

bool DrEnvironmentObjLgt::callback_Chk_LocalIBL(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data) {
  const LgtPosData *pos = list->m_lgtPosData;
  DrLightObjLocalIBL *light = static_cast<DrLightObjLocalIBL *>(list->m_lightObj);
  list->unknown18 = 1.0f;
  if (unknown006(pos->unknown62)) {
    return false;
  }
  const mm::Vec3 &position = light->unknown110;
  return viewWork->unknown4e0.clipTest(position, light->unknown120);
}

bool DrEnvironmentObjLgt::callback_Calc_Non(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork) { return true; }

bool DrEnvironmentObjLgt::callback_Calc_LocalIBL(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork) { return true; }

void DrEnvironmentObjLgt::callback_Ren_Non(DrLightObj *light, DrShdLgtMan *shdLgtMan) {}

void DrEnvironmentObjLgt::callback_Ren_Point(DrLightObj *light, DrShdLgtMan *shdLgtMan) {
  DrAPGxType::setupCullingFront();
  DrAPGxType::setupDepthContl(true, true, 3);
  DrAPGxType::setupBlend(0);
  shdLgtMan->renderDebugPnt(static_cast<DrLightObjPnt *>(light));
}

void DrEnvironmentObjLgt::callback_Ren_Spot(DrLightObj *light, DrShdLgtMan *shdLgtMan) {
  DrAPGxType::setupCullingFront();
  DrAPGxType::setupDepthContl(true, true, 3);
  DrAPGxType::setupBlend(0);
  shdLgtMan->renderDebugSpt(static_cast<DrLightObjSpt *>(light));
}

void DrEnvironmentObjLgt::callback_Ren2D_Non(DrLightObj *light, DrShdLgtMan *shdLgtMan) {}

void DrEnvironmentObjLgt::callback_Ren2D_LocalIBL(DrLightObj *light, DrShdLgtMan *shdLgtMan) {
  DrMan *drMan = unknown18;
  int height = drMan->unknown5b8->unknown1c;
  f32 scale = drMan->unknown120[drMan->unknown1c98]->getToneMapOn() ? unknown18->unknown78->unknown7f0->unknown188 : 1.0f;
  const grlib::CGLibTextureBuffer *texture = static_cast<DrLightObjLocalIBL *>(light)->unknown40;
  if (texture != nullptr) {
    for (u32 face = 0; face < 6; face++) {
      unknown18->unknown78->debugRenderCube(*texture, face, 0, false, 5 + face * 129, height - 133, 128, 128, false, scale);
    }
  }
}

void DrEnvironmentObjLgt::callback_Relase_Non(DrLightObj *light) {}

void DrEnvironmentObjLgt::callback_Relase_Point(DrLightObj *light) {
  if (light->isShadowLight()) {
    static_cast<DrLightObjPnt *>(light)->deletePntShadow();
  }
}

void DrEnvironmentObjLgt::callback_Relase_Spot(DrLightObj *light) {
  if (light->isShadowLight()) {
    static_cast<DrLightObjSpt *>(light)->deleteSptShadow();
  }
}

void (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallEnvRelase[])(DrLightObj *light) = {
    &DrEnvironmentObjLgt::callback_Relase_Non,
    &DrEnvironmentObjLgt::callback_Relase_Non,
    &DrEnvironmentObjLgt::callback_Relase_Point,
    &DrEnvironmentObjLgt::callback_Relase_Spot,
    &DrEnvironmentObjLgt::callback_Relase_Non,
    &DrEnvironmentObjLgt::callback_Relase_Non,
    &DrEnvironmentObjLgt::callback_Relase_Non,
};

bool (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallEnvChk[])(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data) = {
    &DrEnvironmentObjLgt::callback_Chk_Ambinet_Directional,
    &DrEnvironmentObjLgt::callback_Chk_Ambinet_Directional,
    &DrEnvironmentObjLgt::callback_Chk_Point,
    &DrEnvironmentObjLgt::callback_Chk_Spot,
    &DrEnvironmentObjLgt::callback_Chk_non,
    &DrEnvironmentObjLgt::callback_Chk_non,
    &DrEnvironmentObjLgt::callback_Chk_LocalIBL,
};

bool (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallCalcEnv[])(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork) = {
    &DrEnvironmentObjLgt::callback_Calc_Ambient,
    &DrEnvironmentObjLgt::callback_Calc_Directional,
    &DrEnvironmentObjLgt::callback_Calc_Point,
    &DrEnvironmentObjLgt::callback_Calc_Spot,
    &DrEnvironmentObjLgt::callback_Calc_Non,
    &DrEnvironmentObjLgt::callback_Calc_Non,
    &DrEnvironmentObjLgt::callback_Calc_LocalIBL,
};

void (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallLgtRender[])(DrLightObj *light, DrShdLgtMan *shdLgtMan) = {
    &DrEnvironmentObjLgt::callback_Ren_Non,
    &DrEnvironmentObjLgt::callback_Ren_Non,
    &DrEnvironmentObjLgt::callback_Ren_Point,
    &DrEnvironmentObjLgt::callback_Ren_Spot,
    &DrEnvironmentObjLgt::callback_Ren_Non,
    &DrEnvironmentObjLgt::callback_Ren_Non,
    &DrEnvironmentObjLgt::callback_Ren_Non,
};

void (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallLgtRender2D[])(DrLightObj *light, DrShdLgtMan *shdLgtMan) = {
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_LocalIBL,
};

void (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallFogCall[])(DrFogObjGbl *fog, DrCalcViewWork *viewWork, const LgtGlbFogObj *data) = {
    &DrEnvironmentObjLgt::callback_Fog_Gbl,
};

} // namespace ml

// The game builds these files in one unit with this one (0x71007dad8c to 0x71007f0994): the light list (0x71007df6e0) sits between the animation block and this file's, the fog manager
// (0x71007e6eac to 0x71007e76c0) between this file's functions and the light manager's.
// clang-format off
#include "dr_environment_anim.cpp"
#include "dr_environment_lgt_list.cpp"
#include "dr_environment_tex.cpp"
#include "dr_environment_time.cpp"
#include "dr_fog_man.cpp"
#include "dr_light_obj.cpp"
// clang-format on
// DrLightMan inlines functions of the light objects (isCullON, constructors): keep their definitions visible in this unit.
#include "dr_light_man.cpp"
