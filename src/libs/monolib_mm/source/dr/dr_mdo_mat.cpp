#include "dr/dr_mdo_mat.h"

namespace ml {

void DrMdoMat::setExtraShaderSetup(const void *shader) {}

void DrMdoMat::releaseExtraShader() {}

void DrMdoMat::matCall_EmissiveTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = m_matRes->values;
  u32 offset = header->valueOffset;
  f32 *value = &values[offset + valueIndex];
  const f32 *baseValue = &m_matRes->baseValues[offset + valueIndex];
  const f32 *time = &values[header->timeValueIndex + offset];
  *value = *baseValue * *time;
}

void DrMdoMat::matCall_RgbTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = m_matRes->values;
  u32 offset = header->valueOffset;
  f32 *value = &values[offset + valueIndex];
  const f32 *baseValue = &m_matRes->baseValues[offset + valueIndex];
  const f32 *time = &values[header->timeValueIndex + offset];
  value[0] = baseValue[0] * *time;
  value[1] = baseValue[1] * *time;
  value[2] = baseValue[2] * *time;
}

void DrMdoMat::matCall_RTime(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = m_matRes->values;
  u32 offset = header->valueOffset;
  f32 *value = &values[offset + valueIndex];
  const f32 *baseValue = &m_matRes->baseValues[offset + valueIndex];
  const f32 *time = &values[header->timeValueIndex + offset];
  *value = *baseValue * *time;
}

void DrMdoMat::matCall_AccRgb1(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = m_matRes->values + (header->valueOffset + valueIndex);
  value[0] = m_matRes->shaderParm->colors[0].r;
  value[1] = m_matRes->shaderParm->colors[0].g;
  value[2] = m_matRes->shaderParm->colors[0].b;
}

void DrMdoMat::matCall_AccRgb2(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = m_matRes->values + (header->valueOffset + valueIndex);
  value[0] = m_matRes->shaderParm->colors[1].r;
  value[1] = m_matRes->shaderParm->colors[1].g;
  value[2] = m_matRes->shaderParm->colors[1].b;
}

void DrMdoMat::matCall_AccRgb3(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = m_matRes->values + (header->valueOffset + valueIndex);
  value[0] = m_matRes->shaderParm->colors[2].r;
  value[1] = m_matRes->shaderParm->colors[2].g;
  value[2] = m_matRes->shaderParm->colors[2].b;
}

void DrMdoMat::matCall_AccRgb4(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = m_matRes->values + (header->valueOffset + valueIndex);
  value[0] = m_matRes->shaderParm->colors[3].r;
  value[1] = m_matRes->shaderParm->colors[3].g;
  value[2] = m_matRes->shaderParm->colors[3].b;
}

void DrMdoMat::matCall_AccMulRgb1(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = m_matRes->values + (header->valueOffset + valueIndex);
  value[0] = m_matRes->shaderParm->colors[0].r * value[0];
  value[1] = m_matRes->shaderParm->colors[0].g * value[1];
  value[2] = m_matRes->shaderParm->colors[0].b * value[2];
}

void DrMdoMat::matCall_AccMulRgb2(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = m_matRes->values + (header->valueOffset + valueIndex);
  value[0] = m_matRes->shaderParm->colors[1].r * value[0];
  value[1] = m_matRes->shaderParm->colors[1].g * value[1];
  value[2] = m_matRes->shaderParm->colors[1].b * value[2];
}

void DrMdoMat::matCall_AccMulRgb3(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = m_matRes->values + (header->valueOffset + valueIndex);
  value[0] = m_matRes->shaderParm->colors[2].r * value[0];
  value[1] = m_matRes->shaderParm->colors[2].g * value[1];
  value[2] = m_matRes->shaderParm->colors[2].b * value[2];
}

void DrMdoMat::matCall_AccMulRgb4(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = m_matRes->values + (header->valueOffset + valueIndex);
  value[0] = m_matRes->shaderParm->colors[3].r * value[0];
  value[1] = m_matRes->shaderParm->colors[3].g * value[1];
  value[2] = m_matRes->shaderParm->colors[3].b * value[2];
}

void DrMdoMat::matCall_AccVal1(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = m_matRes->values;
  values[header->valueOffset + valueIndex] = m_matRes->shaderParm->values[0];
}

void DrMdoMat::matCall_AccVal2(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = m_matRes->values;
  values[header->valueOffset + valueIndex] = m_matRes->shaderParm->values[1];
}

void DrMdoMat::matCall_AccVal3(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = m_matRes->values;
  values[header->valueOffset + valueIndex] = m_matRes->shaderParm->values[2];
}

void DrMdoMat::matCall_AccVal4(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *values = m_matRes->values;
  values[header->valueOffset + valueIndex] = m_matRes->shaderParm->values[3];
}

void DrMdoMat::matCall_AccMulVal1(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = m_matRes->values + (header->valueOffset + valueIndex);
  value[0] = m_matRes->shaderParm->values[0] * value[0];
  value[1] = m_matRes->shaderParm->values[0] * value[1];
  value[2] = m_matRes->shaderParm->values[0] * value[2];
}

void DrMdoMat::matCall_AccMulVal2(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = m_matRes->values + (header->valueOffset + valueIndex);
  value[0] = m_matRes->shaderParm->values[1] * value[0];
  value[1] = m_matRes->shaderParm->values[1] * value[1];
  value[2] = m_matRes->shaderParm->values[1] * value[2];
}

void DrMdoMat::matCall_AccMulVal3(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = m_matRes->values + (header->valueOffset + valueIndex);
  value[0] = m_matRes->shaderParm->values[2] * value[0];
  value[1] = m_matRes->shaderParm->values[2] * value[1];
  value[2] = m_matRes->shaderParm->values[2] * value[2];
}

void DrMdoMat::matCall_AccMulVal4(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = m_matRes->values + (header->valueOffset + valueIndex);
  value[0] = m_matRes->shaderParm->values[3] * value[0];
  value[1] = m_matRes->shaderParm->values[3] * value[1];
  value[2] = m_matRes->shaderParm->values[3] * value[2];
}

void DrMdoMat::matCall_ToonId(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {
  f32 *value = m_matRes->values + (header->valueOffset + valueIndex);
  value[0] = value[1] / 255.0f;
}

void DrMdoMat::matCall_VolumeTest(const MdsMatInfoHeader *header, int valueIndex, int matIndex) {}

} // namespace ml
