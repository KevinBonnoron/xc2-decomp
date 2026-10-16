#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

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
  u8 : 1;
  u8 isUpdateEnable : 1;
  u8 _115[0x118 - 0x115];
  bool isExecUpdate;
};

static_assert(offsetof(GfObj, handle) == 0xf8, "");
static_assert(offsetof(GfObj, info) == 0x100, "");
static_assert(offsetof(GfObj, attribute) == 0x110, "");
static_assert(offsetof(GfObj, isExecUpdate) == 0x118, "");

} // namespace gf
