#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;
struct MsgObjectNotifyAsmCallback;
enum OPTMNT : u32;

enum {
  MSG_OBJECT_FORCE_WEAPON_MOUNT = 0x1000040,
};

// Layout from GfObjUtil::resetWeaponMotion (0x71005afca0), which sends it to the weapons of an object.
struct MsgObjectForceWeaponMount : fw::Message {
  MsgObjectForceWeaponMount(OPTMNT type, GF_OBJ_HANDLE *owner) : fw::Message(MSG_OBJECT_FORCE_WEAPON_MOUNT, 0x40), unknown08(type), unknown10(owner) {}

  OPTMNT unknown08;         // Inferred role: weapon mount option; original member name unknown.
  GF_OBJ_HANDLE *unknown10; // Inferred role: owner of the weapon motion; original member name unknown.
};

static_assert(offsetof(MsgObjectForceWeaponMount, unknown08) == 0x08, "");
static_assert(offsetof(MsgObjectForceWeaponMount, unknown10) == 0x10, "");

class GfComBehaviorWeapon : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgObjectNotifyAsmCallback(fw::MessageObject *sender, MsgObjectNotifyAsmCallback &message);
  void procMsgObjectOnChangeWeapon(fw::MessageObject *sender, MsgObjectForceWeaponMount &message);
  GfComBehaviorWeapon();
  ~GfComBehaviorWeapon() override;
  void update(const fw::UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;
  void changeLayer(u32 oldLayer, u32 newLayer) override;

  mm::mtl::Vector<const char *> unknown98; // Inferred role: pending asm commands; original member name unknown.
};

static_assert(offsetof(GfComBehaviorWeapon, unknown98) == 0x98, "");
static_assert(sizeof(GfComBehaviorWeapon) == 0xc0, "");

} // namespace gf
