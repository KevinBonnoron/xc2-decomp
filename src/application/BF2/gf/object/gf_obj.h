#pragma once
#include <stddef.h>

#include "framework/framework.h"
#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "framework/pointer_map.h"
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;
struct GFOBJ_INFO;

enum {
  OBJ_STATE_UPDATING = 0,
  OBJ_STATE_UPDATE_ENABLE = 1,
};

enum {
  OBJ_ATTRIBUTE_TARGET_MASK = 0x7,
};

enum {
  MSG_DEBUG_ACTIVATE_OBJECT_WINDOW = 0x1000001,
  MSG_DEBUG_DEACTIVATE_OBJECT_WINDOW = 0x1000002,
};

struct MsgDebugActivateObjectWindow : fw::Message {};

struct MsgDebugDeactivateObjectWindow : fw::Message {};

class GfObj : public fw::UpdatableObject, public fw::MessageObject {
public:
  static mm::mtl::RTTI m_rtti;

  GfObj(u32 type, const fw::HandlePtr<fw::UpdatableObject> &handle, u32 layer);
  virtual ~GfObj();
  virtual void update(const fw::UpdateInfo &info);
  virtual void onEvent(const fw::ObjectEvent &event);
  static const char *getTypeName(u32 type);
  virtual bool recieveMessage(fw::MessageObject *sender, fw::Message &message);
  void procMsgActivateObjectDebugWindow(fw::MessageObject *sender, MsgDebugActivateObjectWindow &message);
  void procMsgDeactivateObjectDebugWindow(fw::MessageObject *sender, MsgDebugDeactivateObjectWindow &message);
  void setUpdateComponent(bool isUpdate);
  virtual const mm::mtl::RTTI *getRTTI() const;

  GF_OBJ_HANDLE *unknownf8; // Inferred role: handle; original member name unknown.
  GFOBJ_INFO *unknown100;   // Inferred role: info; original member name unknown.
  u8 _108[0x110 - 0x108];
  u32 unknown110;                     // Inferred role: attribute; original member name unknown.
  mm::mtl::unknown027<32> unknown114; // Inferred role: flags; original member name unknown.
  bool unknown118;                    // Inferred role: exec update; original member name unknown.
};

static_assert(offsetof(GfObj, unknownf8) == 0xf8, "");
static_assert(offsetof(GfObj, unknown100) == 0x100, "");
static_assert(offsetof(GfObj, unknown110) == 0x110, "");
static_assert(offsetof(GfObj, unknown118) == 0x118, "");

class GfObjLayerSpeed {
public:
  struct Info {
    Info() : unknown00(false), unknown04(1.0f) {}

    bool unknown00; // Inferred role: request; original member name unknown.
    f32 unknown04;  // Inferred role: speed; original member name unknown.
  };

  static void initialize();
  static void finalize();
  static void reqApplyModelLayerSpeed(u32 layer, f32 speed);
  static bool isRequest(u32 layer);
  static f32 getSpeed(u32 layer);
  static void cleanup();

private:
  static Info s_info[fw::Framework::LAYER_MAX];
};

static_assert(sizeof(GfObjLayerSpeed::Info) == 0x8, "");

} // namespace gf
