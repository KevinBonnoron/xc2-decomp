#include "dr/dr_res_anm.h"

namespace ml {

DrResAnm::~DrResAnm() {}

f32 DrResAnm::calcAnm(f32 frame, const _AOM_DataHead *head) {
  const unknown001 *keys = reinterpret_cast<const unknown001 *>(head + 1);
  if (frame <= head->unknown00) {
    return keys[0].unknown04;
  }
  if (frame >= head->unknown04) {
    return keys[head->unknown08 - 1].unknown04;
  }
  int last = head->unknown08 - 1;
  f32 value = keys[last].unknown04;
  const unknown001 *key = keys;
  for (int i = 0; i < last; i++, key++) {
    if (key[0].unknown00 <= frame && frame < key[1].unknown00) {
      return key[0].unknown04;
    }
  }
  return value;
}

f32 DrResAnm::calcAnmLiner(f32 frame, const _AOM_DataHead *head) {
  const unknown001 *keys = reinterpret_cast<const unknown001 *>(head + 1);
  if (frame <= head->unknown00) {
    return keys[0].unknown04;
  }
  if (frame >= head->unknown04) {
    return keys[head->unknown08 - 1].unknown04;
  }
  int last = head->unknown08 - 1;
  f32 value = keys[last].unknown04;
  const unknown001 *key = keys;
  for (int i = 0; i < last; i++, key++) {
    if (key[0].unknown00 <= frame && frame < key[1].unknown00) {
      f32 rate = (frame - key[0].unknown00) / (key[1].unknown00 - key[0].unknown00);
      return (1.0f - rate) * key[0].unknown04 + rate * key[1].unknown04;
    }
  }
  return value;
}

f32 DrResAnm::calcAnmRot(f32 *values, f32 frame, const _AOM_DataHead *head) {
  const unknown001 *keys = reinterpret_cast<const unknown001 *>(head + 1);
  if (frame <= head->unknown00) {
    f32 value = keys[0].unknown04;
    values[0] = value;
    values[1] = value;
    return 0.0f;
  }
  int last = head->unknown08 - 1;
  f32 value = keys[last].unknown04;
  if (frame >= head->unknown04) {
    values[0] = value;
    values[1] = value;
    return 0.0f;
  }
  const unknown001 *key = keys;
  for (int i = 0; i < last; i++, key++) {
    if (key[0].unknown00 <= frame && frame < key[1].unknown00) {
      values[0] = key[0].unknown04;
      values[1] = key[1].unknown04;
      return (frame - key[0].unknown00) / (key[1].unknown00 - key[0].unknown00);
    }
  }
  values[0] = value;
  values[1] = value;
  return 0.0f;
}

} // namespace ml
