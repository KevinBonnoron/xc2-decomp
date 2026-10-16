#pragma once
#include <stddef.h>

namespace mm {
namespace mtl {

unsigned int nthHashSize(unsigned int index);
unsigned int hash32Mix(unsigned int key);
unsigned int hash64Mix(unsigned long key);
unsigned int hashFloatMix(float key);
unsigned int hashDoubleMix(double key);
unsigned int hashPointerMix(const void *key);
unsigned int hashCrc(const char *data, size_t size);
unsigned int hash32Crc(unsigned int key);
unsigned int hash64Crc(unsigned long key);
unsigned int hashFloatCrc(float key);
unsigned int hashDoubleCrc(double key);
unsigned int hashPointerCrc(const void *key);
unsigned int hashStrCrc(const char *string);
unsigned int hashSetCrc(const char *data, size_t size, unsigned int seed);
int JumpConsistentHash(unsigned long key, int bucketCount);

} // namespace mtl
} // namespace mm
