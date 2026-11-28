#include <stddef.h>

#include "lms/lms_impl.h"

// First translation unit of the message library (see lms_impl.h): the allocator that ms::MsWrapper hands over with
// LMS_SetMemFuncs and the byte helpers.

namespace {

// Inferred role: allocator functions of the library; original type name unknown. LMS_SetMemFuncs stores both with one
// `stp` (0x7100984db8), and LMSi_Free reads the second from `table + 8` (0x7100984dd4).
struct unknown003 {
  void *(*unknown00)(size_t size);  // Inferred role: allocate; original member name unknown.
  void (*unknown08)(void *pointer); // Inferred role: deallocate; original member name unknown.
};

static_assert(offsetof(unknown003, unknown08) == 0x08, "");

// Inferred role: the allocator table, in the game's bss at 0x7101bd9cc8; original name unknown.
unknown003 unknown004;

} // namespace

extern "C" {

void LMS_SetMemFuncs(void *(*allocate)(size_t size), void (*deallocate)(void *pointer)) {
  unknown004.unknown00 = allocate;
  unknown004.unknown08 = deallocate;
}

void *LMSi_Malloc(size_t size) { return unknown004.unknown00(size); }

void LMSi_Free(void *pointer) { unknown004.unknown08(pointer); }

int LMSi_MemCmp(const char *a, const char *b, int size) {
  for (int i = 0; i < size; i++) {
    if (a[i] != b[i]) {
      return 0;
    }
  }
  return 1;
}

void LMSi_MemCopy(char *destination, const char *source, int size) {
  for (int i = 0; i < size; i++) {
    destination[i] = source[i];
  }
}
}
