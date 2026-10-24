#include "dr/dr_mdo_mat.h"

#include "dr/dr_man.h"

namespace ml {

void DrMdoMat::setDrMan(DrMan *drMan) { m_drMan = drMan; }

void DrMdoMat::updateAlphaCall() {
  if (unknown100 & ALPHA_FLAG_SINGLE_BUFFER) {
    unknown100 &= ~(ALPHA_FLAG_UPDATED | ALPHA_FLAG_UPDATED << 1);
    return;
  }
  int index = DrMan::s_nDblIdx;
  u32 flag = ALPHA_FLAG_UPDATED << index;
  if (unknown100 & flag) {
    unknown100 &= ~flag;
    unknowne0 = unknownd0[index];
  }
}

bool DrMdoMat::isBloomMdl() const { return (unknownf8 & MDL_FLAG_BLOOM) != 0; }

bool DrMdoMat::isAlphaBloomMdl() const { return (unknownf8 & MDL_FLAG_ALPHA_BLOOM) != 0; }

u32 DrMdoMat::getVanishEffectMax() const {
  if (unknown30 == nullptr) {
    return 0;
  }
  const MdsMeshHeader *header = unknown30->unknown20;
  if (header == nullptr) {
    return 0;
  }
  if (!(header->unknown00 & MdsMeshHeader::FLAG_VANISH_EFFECT)) {
    return 0;
  }
  return header->unknown94 > 1 ? header->unknown94 : 1;
}

bool DrMdoMat::isFullScreenShadowMdl() const { return (unknownf8 & MDL_FLAG_FULL_SCREEN_SHADOW) != 0; }

MdoWrkVanishEffect *DrMdoMat::getVanishEffectWrk(u32 index, u32 bufferIndex) {
  if (unknown30 == nullptr) {
    return nullptr;
  }
  if (unknown30->unknown20 == nullptr) {
    return nullptr;
  }
  if (unknown30->unknown150 == nullptr) {
    return nullptr;
  }
  return &unknown30->unknown150[index * 3 + bufferIndex];
}

bool DrMdoMat::isVolumeMdl() const { return (unknownf8 & MDL_FLAG_VOLUME) != 0; }

void DrMdoMat::setFlagWaveOn(bool isOn) {
  if (isOn) {
    unknownfc |= DRAW_FLAG_FLAG_WAVE;
  } else {
    unknownfc &= ~DRAW_FLAG_FLAG_WAVE;
  }
}

void DrMdoMat::setExtraShaderSetup(const void *shader) {}

void DrMdoMat::releaseExtraShader() {}

void DrMdoMat::matCall_EmissiveTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  u32 offset = header->unknown40;
  f32 *value = &values[offset + valueIndex];
  const f32 *baseValue = &unknown30->unknown38[offset + valueIndex];
  const f32 *time = &values[header->unknown64 + offset];
  *value = *baseValue * *time;
}

void DrMdoMat::matCall_RgbTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  u32 offset = header->unknown40;
  f32 *value = &values[offset + valueIndex];
  const f32 *baseValue = &unknown30->unknown38[offset + valueIndex];
  const f32 *time = &values[header->unknown64 + offset];
  value[0] = baseValue[0] * *time;
  value[1] = baseValue[1] * *time;
  value[2] = baseValue[2] * *time;
}

void DrMdoMat::matCall_RTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  u32 offset = header->unknown40;
  f32 *value = &values[offset + valueIndex];
  const f32 *baseValue = &unknown30->unknown38[offset + valueIndex];
  const f32 *time = &values[header->unknown64 + offset];
  *value = *baseValue * *time;
}

void DrMdoMat::matCall_AccRgb1(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[0].r;
  value[1] = unknown30->unknown118->unknown00[0].g;
  value[2] = unknown30->unknown118->unknown00[0].b;
}

void DrMdoMat::matCall_AccRgb2(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[1].r;
  value[1] = unknown30->unknown118->unknown00[1].g;
  value[2] = unknown30->unknown118->unknown00[1].b;
}

void DrMdoMat::matCall_AccRgb3(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[2].r;
  value[1] = unknown30->unknown118->unknown00[2].g;
  value[2] = unknown30->unknown118->unknown00[2].b;
}

void DrMdoMat::matCall_AccRgb4(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[3].r;
  value[1] = unknown30->unknown118->unknown00[3].g;
  value[2] = unknown30->unknown118->unknown00[3].b;
}

void DrMdoMat::matCall_AccMulRgb1(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[0].r * value[0];
  value[1] = unknown30->unknown118->unknown00[0].g * value[1];
  value[2] = unknown30->unknown118->unknown00[0].b * value[2];
}

void DrMdoMat::matCall_AccMulRgb2(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[1].r * value[0];
  value[1] = unknown30->unknown118->unknown00[1].g * value[1];
  value[2] = unknown30->unknown118->unknown00[1].b * value[2];
}

void DrMdoMat::matCall_AccMulRgb3(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[2].r * value[0];
  value[1] = unknown30->unknown118->unknown00[2].g * value[1];
  value[2] = unknown30->unknown118->unknown00[2].b * value[2];
}

void DrMdoMat::matCall_AccMulRgb4(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown00[3].r * value[0];
  value[1] = unknown30->unknown118->unknown00[3].g * value[1];
  value[2] = unknown30->unknown118->unknown00[3].b * value[2];
}

void DrMdoMat::matCall_AccVal1(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  values[header->unknown40 + valueIndex] = unknown30->unknown118->unknown30[0];
}

void DrMdoMat::matCall_AccVal2(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  values[header->unknown40 + valueIndex] = unknown30->unknown118->unknown30[1];
}

void DrMdoMat::matCall_AccVal3(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  values[header->unknown40 + valueIndex] = unknown30->unknown118->unknown30[2];
}

void DrMdoMat::matCall_AccVal4(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  values[header->unknown40 + valueIndex] = unknown30->unknown118->unknown30[3];
}

void DrMdoMat::matCall_AccMulVal1(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown30[0] * value[0];
  value[1] = unknown30->unknown118->unknown30[0] * value[1];
  value[2] = unknown30->unknown118->unknown30[0] * value[2];
}

void DrMdoMat::matCall_AccMulVal2(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown30[1] * value[0];
  value[1] = unknown30->unknown118->unknown30[1] * value[1];
  value[2] = unknown30->unknown118->unknown30[1] * value[2];
}

void DrMdoMat::matCall_AccMulVal3(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown30[2] * value[0];
  value[1] = unknown30->unknown118->unknown30[2] * value[1];
  value[2] = unknown30->unknown118->unknown30[2] * value[2];
}

void DrMdoMat::matCall_AccMulVal4(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = unknown30->unknown118->unknown30[3] * value[0];
  value[1] = unknown30->unknown118->unknown30[3] * value[1];
  value[2] = unknown30->unknown118->unknown30[3] * value[2];
}

void DrMdoMat::matCall_CalcBloom(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = unknown30->unknownf8;
  u32 offset = header->unknown40;
  f32 *value = &values[offset + valueIndex];
  const f32 *baseValue = &unknown30->unknown38[offset + valueIndex];
  *value = *baseValue * unknownd8;
}

void DrMdoMat::matCall_ToonId(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = unknown30->unknownf8 + (header->unknown40 + valueIndex);
  value[0] = value[1] / 255.0f;
}

void DrMdoMat::matCall_VolumeTest(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {}

} // namespace ml
