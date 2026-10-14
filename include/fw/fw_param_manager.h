#pragma once
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {

class ParamList : public mm::mtl::ReferenceObject {
public:
  struct Entry {
    u8 _00[0x08 - 0x00];
    const void *param;
  };

  u32 count;
  Entry *entries;
};

static_assert(offsetof(ParamList, count) == 0x0c, "");
static_assert(offsetof(ParamList, entries) == 0x10, "");

class ParamManager : public mm::mtl::PtrSingleton<ParamManager> {
public:
  u8 _08[0x438 - 0x08];
  mm::mtl::IntrusivePtr<ParamList> formationParamList;
  u8 _440[0x468 - 0x440];
  mm::mtl::IntrusivePtr<ParamList> uniqueMotionParamList;
};

static_assert(offsetof(ParamManager, formationParamList) == 0x438, "");
static_assert(offsetof(ParamManager, uniqueMotionParamList) == 0x468, "");

} // namespace fw
