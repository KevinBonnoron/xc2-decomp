#include "ml/halton.h"

namespace ml {

float vdC_Hammersley(int index, int base) {
  float result = 0.0f;
  if (index > 0) {
    float digit = 1.0f / base;
    do {
      int next = index / base;
      result += digit * (index - next * base);
      digit = 1.0f / base * digit;
      index = next;
    } while (index > 0);
  }
  return result;
}

void hammersley(float *out, int count) {
  for (int i = 0; i < count; i++) {
    out[i * 2] = (float)i / (float)count;
    if (i < 1) {
      out[i * 2 + 1] = 0.0f;
    } else {
      float digit = 0.5f;
      float result = 0.0f;
      int k = i;
      int cur;
      do {
        cur = k;
        k = cur / 2;
        result += digit * (cur % 2);
        digit *= 0.5f;
      } while (cur > 1);
      out[i * 2 + 1] = result;
    }
  }
}

float vdC_Halton(int index, int base) {
  float result = 0.0f;
  if (index > 0) {
    float digit = 1.0f / base;
    do {
      int next = index / base;
      result += digit * (index - next * base);
      digit = 1.0f / base * digit;
      index = next;
    } while (index > 0);
  }
  return result;
}

} // namespace ml
