#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "framework/reference_frame.h" // IWYU pragma: keep
#include "gf/field/gf_big_obj_unique.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
class ColiMoveObject;
class ColiObject;
} // namespace fw

namespace gmk {
class GmkRouteNavi;
} // namespace gmk

namespace gf {

class GfMenuCallContext;

struct MsgPcFieldNotifySkillEvent : fw::Message {
  explicit MsgPcFieldNotifySkillEvent(u32 event) : fw::Message(0x100001d, 0x40), unknown08(event) {}

  u32 unknown08; // Inferred role: event, 0 removes the icon of the jump or warp point; original member name unknown.
};

static_assert(offsetof(MsgPcFieldNotifySkillEvent, unknown08) == 0x08, "");

// Layout from its constructor (0x710052a63c), destructor, setup and cleanup: the moving collision at 0x98, the route navi
// at 0xa0, the target info menu context at 0xa8, the big object at 0xb0 and the look point frame at 0xc0.
class GfComBehaviorGmk : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  void procMsgPcFieldNotifyAction(fw::MessageObject *sender, MsgPcFieldNotifyAction &message);
  void procMsgPcFieldGetAccessType(fw::MessageObject *sender, MsgPcFieldGetAccessType &message);
  void procMsgPcGetLookPoint(fw::MessageObject *sender, MsgPcGetLookPoint &message);
  void procMsgPcFieldNotifySkillEvent(fw::MessageObject *sender, MsgPcFieldNotifySkillEvent &message);
  void cleanup();
  void createMenuObj();
  void disposeMenuObj();
  void setActivateCollison(bool isActivate);
  fw::ColiMoveObject *getColiObject() const;

  fw::ColiObject *unknown98;                           // Inferred role: moving collision; original member name unknown.
  gmk::GmkRouteNavi *unknowna0;                        // Inferred role: route navi; original member name unknown.
  GfMenuCallContext *unknowna8;                        // Inferred role: target info menu context; original member name unknown.
  GfBigObjUnique unknownb0;                            // Inferred role: big object; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknownc0; // Inferred role: look point frame; original member name unknown.
};

static_assert(offsetof(GfComBehaviorGmk, unknown98) == 0x98, "");
static_assert(offsetof(GfComBehaviorGmk, unknowna0) == 0xa0, "");
static_assert(offsetof(GfComBehaviorGmk, unknowna8) == 0xa8, "");
static_assert(offsetof(GfComBehaviorGmk, unknownb0) == 0xb0, "");
static_assert(offsetof(GfComBehaviorGmk, unknownc0) == 0xc0, "");
static_assert(sizeof(GfComBehaviorGmk) == 0xc8, "");

} // namespace gf
