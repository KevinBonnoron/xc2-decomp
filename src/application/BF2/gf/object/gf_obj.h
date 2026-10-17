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

  GF_OBJ_HANDLE *handle;
  GFOBJ_INFO *info;
  u8 _108[0x110 - 0x108];
  u32 attribute;
  mm::mtl::BitFlag<32> flags;
  bool isExecUpdate;
};

static_assert(offsetof(GfObj, handle) == 0xf8, "");
static_assert(offsetof(GfObj, info) == 0x100, "");
static_assert(offsetof(GfObj, attribute) == 0x110, "");
static_assert(offsetof(GfObj, isExecUpdate) == 0x118, "");

class GfObjLayerSpeed {
public:
  struct Info {
    Info() : request(false), speed(1.0f) {}

    bool request;
    f32 speed;
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
