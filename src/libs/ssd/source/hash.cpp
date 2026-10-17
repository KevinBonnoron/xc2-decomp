#include "ssd/ssd_hash.h"
#include "types.h"

namespace ssd {

void Hash::CalcDataHash(const void *data, u32 size) {
  u32 value = hash;
  u32 total = this->size;
  const u8 *bytes = static_cast<const u8 *>(data);
  for (u32 i = 0; i < size; i++) {
    value = (value * 137) ^ *bytes;
    bytes++;
  }
  hash = value;
  this->size = total + size;
}

void Hash::CalcTextHash(const char *text) {
  const char *end = text;
  while (*end != '\0') {
    end++;
  }
  CalcDataHash(text, end - text);
}

void Hash::CalcTextHash(const char16_t *text) {
  const char16_t *end = text;
  while (*end != u'\0') {
    end++;
  }
  CalcDataHash(text, (end - text) * sizeof(char16_t));
}

} // namespace ssd
