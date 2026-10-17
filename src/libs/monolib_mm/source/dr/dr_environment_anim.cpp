#include "dr/dr_environment_anim.h"

#include "dr/dr_fog_obj_gbl.h"
#include "dr/dr_light_obj.h"

namespace ml {

DrEnvironmentAnim::DrEnvironmentAnim() {
  m_frames = nullptr;
  m_animNum = 0;
}

u32 DrEnvironmentAnim::getAnimWork(const u8 *data, u32 offset) {
  if (offset != 0) {
    return *reinterpret_cast<const u32 *>(data + offset) * 4;
  }
  return 0;
}

void DrEnvironmentAnim::setupAnmVal(const f32 *values) {
  m_anmVal[2] = values[0];
  m_anmVal[1] = values[1];
  m_anmVal[0] = values[2];
}

void DrEnvironmentAnim::envlgt_amb_color_R(const LgtAnimInf *inf, f32 frame) { m_color.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_amb_color_G(const LgtAnimInf *inf, f32 frame) { m_color.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_amb_color_B(const LgtAnimInf *inf, f32 frame) { m_color.b = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_amb_color_Intensity(const LgtAnimInf *inf, f32 frame) { m_intensity = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_amb_non(const LgtAnimInf *inf, f32 frame) {}

inline f32 DrEnvironmentAnim::getHermiteAttr(const LgtAnimInf *inf, f32 frame) {
  if (inf->startFrame >= frame) {
    return m_hermiteKeys[inf->keyIndex].value;
  }
  if (inf->endFrame <= frame) {
    return m_hermiteKeys[inf->keyIndex + inf->keyNum - 1].value;
  }
  const LgtHermiteKey *key = &m_hermiteKeys[inf->keyIndex + 1];
  for (int i = 1; i < inf->keyNum; i++, key++) {
    f32 keyFrame = key->frame;
    if (frame < keyFrame) {
      const LgtHermiteKey *prev = key - 1;
      f32 prevFrame = prev->frame;
      f32 length = keyFrame - prevFrame;
      f32 t = (frame - prevFrame) / length;
      f32 t2 = t * t;
      f32 t3 = t * t2;
      f32 h00 = 2.0f * t3 - 3.0f * t2 + 1.0f;
      f32 h10 = t3 - 2.0f * t2 + t;
      f32 h01 = 3.0f * t2 - 2.0f * t3;
      f32 h11 = t3 - t2;
      return prev->value * h00 + prev->outSlope * h10 + key->value * h01 + key->inSlope * h11;
    }
  }
  return 0.0f;
}

void DrEnvironmentAnim::envlgt_dir_color_R(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) { m_color.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_dir_color_G(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) { m_color.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_dir_color_B(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) { m_color.b = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_dir_color_Intensity(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) {
  m_intensity = getHermiteAttr(inf, frame);
}

void DrEnvironmentAnim::envlgt_dir_spe_Intensity(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_dir_non(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_dir_texonoff(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_dir_texofsX(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_dir_texofsY(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_dir_size(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_dir_rotz(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) { m_anmVal[2] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_dir_roty(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) { m_anmVal[1] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_dir_rotx(DrLightObjDir *light, const LgtAnimInf *inf, f32 frame) { m_anmVal[0] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_color_R(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { m_color.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_color_G(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { m_color.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_color_B(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { m_color.b = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_color_Intensity(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) {
  m_intensity = getHermiteAttr(inf, frame);
}

void DrEnvironmentAnim::envlgt_pnt_spe_Intensity(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) {
  light->m_speIntensity = getHermiteAttr(inf, frame);
}

void DrEnvironmentAnim::envlgt_pnt_non(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_pnt_texonoff(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_pnt_texofsX(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_pnt_texofsY(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_pnt_size(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { light->m_size = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_rotz(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { m_anmVal[2] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_roty(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { m_anmVal[1] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_pnt_rotx(DrLightObjPnt *light, const LgtAnimInf *inf, f32 frame) { m_anmVal[0] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_color_R(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { m_color.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_color_G(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { m_color.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_color_B(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { m_color.b = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_color_Intensity(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) {
  m_intensity = getHermiteAttr(inf, frame);
}

void DrEnvironmentAnim::envlgt_spt_spe_Intensity(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) {
  light->m_speIntensity = getHermiteAttr(inf, frame);
}

void DrEnvironmentAnim::envlgt_spt_angle(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { light->m_angle = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_texonoff(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_spt_texofsX(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_spt_texofsY(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) {}

void DrEnvironmentAnim::envlgt_spt_size(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { light->m_size = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_rotz(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { m_anmVal[2] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_roty(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { m_anmVal[1] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_spt_rotx(DrLightObjSpt *light, const LgtAnimInf *inf, f32 frame) { m_anmVal[0] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_trans_posx(const LgtAnimInf *inf, f32 frame) { m_anmVal[0] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_trans_posy(const LgtAnimInf *inf, f32 frame) { m_anmVal[1] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envlgt_trans_posz(const LgtAnimInf *inf, f32 frame) { m_anmVal[2] = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_R(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { m_color.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_G(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { m_color.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_B(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { m_color.b = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_sideR(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { m_sideColor.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_sideG(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { m_sideColor.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_sideB(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { m_sideColor.b = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_near(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { fog->m_near = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_far(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { fog->m_far = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_str(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { fog->m_str = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_pow(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { fog->m_pow = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_sunR(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { m_sunColor.r = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_sunG(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { m_sunColor.g = getHermiteAttr(inf, frame); }

void DrEnvironmentAnim::envfog_parm_color_sunB(DrFogObjGbl *fog, const LgtAnimInf *inf, f32 frame) { m_sunColor.b = getHermiteAttr(inf, frame); }

u16 DrEnvironmentAnim::getBitAttr(const LgtAnimInf *inf, f32 frame) {
  if (inf->startFrame >= frame) {
    return m_bitKeys[inf->keyIndex].value;
  }
  if (inf->endFrame <= frame) {
    return m_bitKeys[inf->keyIndex + inf->keyNum - 1].value;
  }
  const LgtBitKey *key = &m_bitKeys[inf->keyIndex + 1];
  for (int i = 1; i < inf->keyNum; i++, key++) {
    f32 keyFrame = key->frame;
    if (frame < keyFrame) {
      return key[-1].value;
    }
  }
  return 0;
}

} // namespace ml
