#include "anm/anm_mirror_mapper.h"

#include <math.h>
#include <string.h>

#include "anm/anm_skeleton.h"
#include "mm_math/mm_quat.h"

namespace anm {

void MirrorMapper::canonicalize(f32 tolerance, mm::Quat *quat) {
  static const f32 s = sqrtf(2.0f) / 2.0f;
  static const mm::Quat table[24] = {
      {1.0f, 0.0f, 0.0f, 0.0f},  {0.0f, 1.0f, 0.0f, 0.0f},   {0.0f, 0.0f, 1.0f, 0.0f},  {0.0f, 0.0f, 0.0f, 1.0f},   {s, s, 0.0f, 0.0f},         {s, -s, 0.0f, 0.0f},
      {0.0f, s, s, 0.0f},        {0.0f, s, -s, 0.0f},        {0.0f, 0.0f, s, s},        {0.0f, 0.0f, s, -s},        {s, 0.0f, s, 0.0f},         {s, 0.0f, -s, 0.0f},
      {0.0f, s, 0.0f, s},        {0.0f, s, 0.0f, -s},        {s, 0.0f, 0.0f, s},        {s, 0.0f, 0.0f, -s},        {0.5f, 0.5f, 0.5f, 0.5f},   {0.5f, 0.5f, 0.5f, -0.5f},
      {0.5f, 0.5f, -0.5f, 0.5f}, {0.5f, 0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, 0.5f, 0.5f}, {0.5f, -0.5f, 0.5f, -0.5f}, {0.5f, -0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f, -0.5f},
  };
  for (u32 i = 0; i < 24; i++) {
    const mm::Quat &candidate = table[i];
    if (fabsf(quat->x * candidate.x + quat->y * candidate.y + quat->z * candidate.z + quat->w * candidate.w) >= 1.0f - tolerance) {
      *quat = candidate;
      return;
    }
  }
}

void MirrorMapper::setBonePairTable(s16 *pBonePairTable) { memcpy(unknown20.m_buffer, pBonePairTable, unknown20.size() * sizeof(s16)); }

MirrorMapper::~MirrorMapper() { unknown001(unknown18); }

} // namespace anm
