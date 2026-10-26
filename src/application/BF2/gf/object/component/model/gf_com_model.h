#pragma once
#include <stddef.h>

#include "framework/reference_frame.h"
#include "gf/object/component/gf_component.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace anm {
class ExtraTruckBuffer;
class Pose;
class Skeleton;
} // namespace anm
namespace fw {
class ModelObject;
class MessageObject;
} // namespace fw
namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct MsgObjectNotifyDamage;
struct MsgObjectNotifyDead;

class GfComModel : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 1;

  bool isRender() const;
  bool isVolumeFadeForUser() const;
  void procMsgObjectNotifyDead(fw::MessageObject *sender, MsgObjectNotifyDead &message);
  void procMsgObjectNotifyDamage(fw::MessageObject *sender, MsgObjectNotifyDamage &message);
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void setModelScale(f32 scale);

  u8 _10[0x18 - 0x10];
  fw::ModelObject *unknown18;                          // Inferred role: model object; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown20; // Inferred role: reference frame; original member name unknown.
  const anm::Skeleton *unknown28;                      // Inferred role: skeleton; original member name unknown.
  anm::Pose *unknown30;                                // Inferred role: pose; original member name unknown.
  anm::ExtraTruckBuffer *unknown38;                    // Inferred role: extra truck buffer; original member name unknown.
};

static_assert(offsetof(GfComModel, unknown18) == 0x18, "");
static_assert(offsetof(GfComModel, unknown20) == 0x20, "");
static_assert(offsetof(GfComModel, unknown28) == 0x28, "");
static_assert(offsetof(GfComModel, unknown30) == 0x30, "");
static_assert(offsetof(GfComModel, unknown38) == 0x38, "");

} // namespace gf
