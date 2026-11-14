#include "dr/dr_mdo_anim.h"

#include <math.h>
#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_res_etc_params.h"
#include "dr/dr_res_mdo_mat.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"

namespace ml {

void DrMdoAnim::changeMemFixAnim(MdoWrkMatRes *matRes, const void *data) {
  const unknown025 *anim = static_cast<const unknown025 *>(data);
  const u8 *base = static_cast<const u8 *>(data);
  matRes->unknown50 = base;
  matRes->unknown58 = reinterpret_cast<const MdsFixAnmInf *>(base + anim->unknown14);
  matRes->unknown60 = reinterpret_cast<const unknown013 *>(base + anim->unknown1c);
  matRes->unknown68 = base + anim->unknown24;
}

void DrMdoAnim::setupFixAnim(const void *data) {
  const unknown025 *anim = static_cast<const unknown025 *>(data);
  unknown30->unknown50 = static_cast<const u8 *>(data);
  unknown30->unknown58 = reinterpret_cast<const MdsFixAnmInf *>(unknown30->unknown50 + anim->unknown14);
  unknown30->unknown60 = reinterpret_cast<const unknown013 *>(unknown30->unknown50 + anim->unknown1c);
  unknown30->unknown68 = unknown30->unknown50 + anim->unknown24;
}

void DrMdoAnim::updateAnimEnd(f32 frame, const u32 *flags, DrResEtcPamObj *pamObj) {
  const u8 *data = unknown30->unknown50;
  if (data == nullptr) {
    return;
  }
  const unknown025 *header = reinterpret_cast<const unknown025 *>(data);
  const unknown016 *ranges = reinterpret_cast<const unknown016 *>(data + header->unknown04);
  const MdsFixAnmCate *cates = reinterpret_cast<const MdsFixAnmCate *>(data + header->unknown0c);
  const MdsMatInfoHeader *matInfo = unknown30->unknown28;
  for (int i = 0; i < unknown30->unknown30; i++, matInfo++) {
    if ((flags[i >> 5] & (1 << (i & 31))) && (matInfo->unknown04 & (MdsMatInfoHeader::unknown015_16 | MdsMatInfoHeader::unknown015_18))) {
      f32 *values = unknown30->unknownf8 + matInfo->unknown40;
      if (matInfo->unknown04 & MdsMatInfoHeader::unknown015_16) {
        const unknown016 *range = &ranges[matInfo->unknown30];
        u32 num = range->unknown02;
        const MdsFixAnmCate *cate = &cates[range->unknown00];
        for (u32 j = 0; j < num; j++, cate++) {
          f32 *work = values + cate->unknown06;
          memcpy(work, unknown30->unknown38 + (matInfo->unknown40 + cate->unknown06), sizeof(f32) * 8);
          calcAnim(cate, &unknown30->unknownc0[i], pamObj, work, frame);
        }
      }
      if (matInfo->unknown04 & MdsMatInfoHeader::unknown015_18) {
        const unknown016 *range = &ranges[matInfo->unknown38];
        u32 num = range->unknown02;
        const MdsFixAnmCate *cate = &cates[range->unknown00];
        for (u32 j = 0; j < num; j++, cate++) {
          calcAnim(cate, &unknown30->unknownc0[i], pamObj, values, frame);
        }
      }
    }
  }
}

void DrMdoAnim::calcAnim(const MdsFixAnmCate *cate, DrResMdoMat *mat, DrResEtcPamObj *pamObj, f32 *work, f32 frame) {
  const MdsFixAnmInf *inf = &unknown30->unknown58[cate->unknown02];
  f32 *frames = &unknown30->unknown100[cate->unknown02];
  for (int i = 0; i < cate->unknown04; i++, inf++, frames++) {
    f32 value;
    if (inf->unknown00_30) {
      value = pamObj->unknown10[inf->unknown04].getParams();
      if (inf->unknown00_29) {
        value = 1.0f - value;
        if (value < 0.0f) {
          value = 0.0f;
        } else if (value > 1.0f) {
          value = 1.0f;
        }
      }
    } else {
      if (inf->unknown00_31) {
        *frames = m_drMan->unknown1cac * 240.0f;
      } else {
        *frames += frame;
        if (*frames > inf->unknown0e - 1) {
          *frames = inf->unknown0e - *frames + inf->unknown0c;
        }
      }
      value = getHermiteAttr(inf, *frames);
    }
    s_pCallAnim[inf->unknown08 & 0xffff](mat, &work[inf->unknown08 >> 16], value);
  }
}

f32 DrMdoAnim::getHermiteAttr(const MdsFixAnmInf *inf, f32 frame) {
  u32 first = inf->unknown00_0;
  f32 startFrame = inf->unknown0c;
  if (frame <= startFrame) {
    return unknown30->unknown60[first].unknown08;
  }
  f32 endFrame = inf->unknown0e;
  int num = inf->unknown04;
  if (frame >= endFrame) {
    return unknown30->unknown60[first + num - 1].unknown08;
  }
  const unknown013 *key = &unknown30->unknown60[first + 1];
  for (int i = 1; i < num; i++, key++) {
    f32 keyFrame = key->unknown0c;
    if (frame < keyFrame) {
      const unknown013 *prev = key - 1;
      if (prev->unknown0e & 1) {
        return prev->unknown08;
      }
      f32 prevFrame = prev->unknown0c;
      f32 length = keyFrame - prevFrame;
      f32 t = (frame - prevFrame) / length;
      f32 t2 = t * t;
      f32 t3 = t * t2;
      f32 h00 = 2.0f * t3 - 3.0f * t2 + 1.0f;
      f32 h10 = t3 - 2.0f * t2 + t;
      f32 h01 = 3.0f * t2 - 2.0f * t3;
      f32 h11 = t3 - t2;
      return prev->unknown08 * h00 + prev->unknown00 * h10 + key->unknown08 * h01 + key->unknown04 * h11;
    }
  }
  return 0.0f;
}

void DrMdoAnim::calcAnimFrameOnly(const MdsFixAnmCate *cate, f32 frame) {
  const MdsFixAnmInf *inf = &unknown30->unknown58[cate->unknown02];
  f32 *frames = &unknown30->unknown100[cate->unknown02];
  for (int i = 0; i < cate->unknown04; i++, inf++, frames++) {
    if (!inf->unknown00_30 && !inf->unknown00_31) {
      *frames += frame;
      if (*frames > inf->unknown0e - 1) {
        *frames = inf->unknown0e - *frames + inf->unknown0c;
      }
    }
  }
}

void DrMdoAnim::setMatAnimFrame(const MdsFixAnmCate *cate, f32 frame) {
  f32 *frames = &unknown30->unknown100[cate->unknown02];
  for (int i = 0; i < cate->unknown04; i++, frames++) {
    *frames = frame;
  }
}

void DrMdoAnim::setMatAnmFrme(f32 frame) {
  const u8 *data = unknown30->unknown50;
  if (data == nullptr) {
    return;
  }
  const unknown025 *header = reinterpret_cast<const unknown025 *>(data);
  const unknown016 *ranges = reinterpret_cast<const unknown016 *>(data + header->unknown04);
  const MdsFixAnmCate *cates = reinterpret_cast<const MdsFixAnmCate *>(data + header->unknown0c);
  const MdsMatInfoHeader *matInfo = unknown30->unknown28;
  for (int i = 0; i < unknown30->unknown30; i++, matInfo++) {
    if (matInfo->unknown04 & (MdsMatInfoHeader::unknown015_16 | MdsMatInfoHeader::unknown015_17 | MdsMatInfoHeader::unknown015_18 | MdsMatInfoHeader::unknown015_19)) {
      if (matInfo->unknown04 & MdsMatInfoHeader::unknown015_16) {
        const unknown016 *range = &ranges[matInfo->unknown30];
        u32 num = range->unknown02;
        const MdsFixAnmCate *cate = &cates[range->unknown00];
        for (u32 j = 0; j < num; j++, cate++) {
          setMatAnimFrame(cate, frame);
        }
      }
      if (matInfo->unknown04 & MdsMatInfoHeader::unknown015_18) {
        const unknown016 *range = &ranges[matInfo->unknown38];
        u32 num = range->unknown02;
        const MdsFixAnmCate *cate = &cates[range->unknown00];
        for (u32 j = 0; j < num; j++, cate++) {
          setMatAnimFrame(cate, frame);
        }
      }
      if (matInfo->unknown04 & MdsMatInfoHeader::unknown015_19) {
        const unknown016 *range = &ranges[matInfo->unknown3c];
        u32 num = range->unknown02;
        const MdsFixAnmCate *cate = &cates[range->unknown00];
        for (u32 j = 0; j < num; j++, cate++) {
          setMatAnimFrame(cate, frame);
        }
      }
      if (matInfo->unknown04 & MdsMatInfoHeader::unknown015_17) {
        const unknown016 *range = &ranges[matInfo->unknown34];
        u32 num = range->unknown02;
        const MdsFixAnmCate *cate = &cates[range->unknown00];
        for (u32 j = 0; j < num; j++, cate++) {
          setMatAnimFrame(cate, frame);
        }
      }
    }
  }
}

f32 DrMdoAnim::getNodeAnmHermiteAttr(const MdsMdlNodeAnmInfo *info, f32 frame) {
  const unknown014 *keys = reinterpret_cast<const unknown014 *>(reinterpret_cast<const u8 *>(unknown30->unknown148->unknown00) + info->unknown0c);
  if (frame <= info->unknown04) {
    return keys[0].unknown08;
  }
  int num = info->unknown10;
  if (frame >= info->unknown08) {
    return keys[num - 1].unknown08;
  }
  const unknown014 *key = &keys[1];
  for (int i = 1; i < num; i++, key++) {
    f32 keyFrame = key->unknown0c;
    if (frame < keyFrame) {
      const unknown014 *prev = key - 1;
      if (prev->unknown0f & 1) {
        return prev->unknown08;
      }
      f32 prevFrame = prev->unknown0c;
      f32 length = keyFrame - prevFrame;
      f32 t = (frame - prevFrame) / length;
      f32 t2 = t * t;
      f32 t3 = t * t2;
      f32 h00 = 2.0f * t3 - 3.0f * t2 + 1.0f;
      f32 h10 = t3 - 2.0f * t2 + t;
      f32 h01 = 3.0f * t2 - 2.0f * t3;
      f32 h11 = t3 - t2;
      return prev->unknown08 * h00 + prev->unknown00 * h10 + key->unknown08 * h01 + key->unknown04 * h11;
    }
  }
  return 0.0f;
}

void DrMdoAnim::animcall_UV_Scr_U(DrResMdoMat *mat, f32 *work, f32 value) { work[0] = value; }

void DrMdoAnim::animcall_UV_Scr_V(DrResMdoMat *mat, f32 *work, f32 value) { work[5] = value; }

void DrMdoAnim::animcall_UV_Trans_U(DrResMdoMat *mat, f32 *work, f32 value) { work[3] = value; }

void DrMdoAnim::animcall_UV_Trans_V(DrResMdoMat *mat, f32 *work, f32 value) { work[7] = value; }

void DrMdoAnim::animcall_UV_Rot(DrResMdoMat *mat, f32 *work, f32 value) {
  f32 rad = value * mm::DEG_TO_RAD;
  f32 scaleU = work[0];
  f32 scaleV = work[5];
  f32 s = sinf(rad);
  f32 c = cosf(rad);
  work[0] = scaleU * c;
  work[1] = scaleV * s;
  work[4] = -(scaleU * s);
  work[5] = scaleV * c;
  work[3] += c * -0.5f - s * 0.5f + 0.5f;
  work[7] += s * 0.5f + c * -0.5f + 0.5f;
}

void DrMdoAnim::animcall_WorkFloat1(DrResMdoMat *mat, f32 *work, f32 value) { work[0] = value; }

void DrMdoAnim::animcall_MatAlpha(DrResMdoMat *mat, f32 *work, f32 value) { mat->setAlpha(value); }

void DrMdoAnim::animcall_MatColorR(DrResMdoMat *mat, f32 *work, f32 value) { mat->unknown08.r = value; }

void DrMdoAnim::animcall_MatColorG(DrResMdoMat *mat, f32 *work, f32 value) { mat->unknown08.g = value; }

void DrMdoAnim::animcall_MatColorB(DrResMdoMat *mat, f32 *work, f32 value) { mat->unknown08.b = value; }

void DrMdoAnim::anmNodeParm_TranX(mm::Vec3 *transform, f32 value) { transform[0].x = value; }

void DrMdoAnim::anmNodeParm_TranY(mm::Vec3 *transform, f32 value) { transform[0].y = value; }

void DrMdoAnim::anmNodeParm_TranZ(mm::Vec3 *transform, f32 value) { transform[0].z = value; }

void DrMdoAnim::anmNodeParm_RotX(mm::Vec3 *transform, f32 value) { transform[1].x = value; }

void DrMdoAnim::anmNodeParm_RotY(mm::Vec3 *transform, f32 value) { transform[1].y = value; }

void DrMdoAnim::anmNodeParm_RotZ(mm::Vec3 *transform, f32 value) { transform[1].z = value; }

void DrMdoAnim::anmNodeParm_SclX(mm::Vec3 *transform, f32 value) { transform[2].x = value; }

void DrMdoAnim::anmNodeParm_SclY(mm::Vec3 *transform, f32 value) { transform[2].y = value; }

void DrMdoAnim::anmNodeParm_SclZ(mm::Vec3 *transform, f32 value) { transform[2].z = value; }

} // namespace ml
