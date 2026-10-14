#pragma once
#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_OBJ_HANDLE;
struct GFOBJ_INFO;

class GfObj : public fw::UpdatableObject, public fw::MessageObject {
public:
  static mm::mtl::RTTI m_rtti;

  GF_OBJ_HANDLE *handle;
  GFOBJ_INFO *info;
  u8 _108[0x110 - 0x108];
  u32 attribute;
};

static_assert(offsetof(GfObj, handle) == 0xf8, "");
static_assert(offsetof(GfObj, info) == 0x100, "");
static_assert(offsetof(GfObj, attribute) == 0x110, "");

} // namespace gf
