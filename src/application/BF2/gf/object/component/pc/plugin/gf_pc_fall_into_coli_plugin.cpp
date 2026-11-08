#include "gf/object/component/pc/plugin/gf_pc_fall_into_coli_plugin.h"

#include <math.h>

#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/game/gf_game_search_obj.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/property/gf_com_property.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {
namespace pc {

FallIntoColiPlugin::FallIntoColiPlugin() : unknown0c(0.0f), unknown10(0.0f) {}

FallIntoColiPlugin::~FallIntoColiPlugin() {}

void FallIntoColiPlugin::cleanup(GfComBehaviorPc &) {
  if (unknown18 != INVALID_SEARCH_OBJ) {
    GfGameSearchObj::destroyObj(unknown18);
    unknown18 = INVALID_SEARCH_OBJ;
  }
}

void FallIntoColiPlugin::onActivate() {
  unknown0c = 0.0f;
  unknown10 = 0.0f;
}

void FallIntoColiPlugin::onDeactivate() { GfGameSearchObj::setEnable(unknown18, false); }

void FallIntoColiPlugin::update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info) {
  unknown0c += info.unknown04;
  if (unknown0c >= 10.0f) {
    if (!GfGameSearchObj::isEnable(unknown18)) {
      GfGameSearchObj::setEnable(unknown18, true);
      unknown20 = getHeight(behavior);
    }

    if (fabsf(getHeight(behavior) - unknown20) <= 1.0f) {
      unknown10 += info.unknown04;
      if (unknown10 >= 5.0f && GfGameSearchObj::getObj(unknown18)->size() != 0) {
        MsgObjectNotifyDead message(0, nullptr);
        message.unknown08 = DEAD_TYPE_UNKNOWN_7;
        StateUtil::notifyDead(behavior, message, true);
      }
    } else {
      unknown20 = getHeight(behavior);
      unknown10 = 0.0f;
    }
  }
}

f32 FallIntoColiPlugin::getHeight(GfComBehaviorPc &behavior) const {
  GfComTransform *transform = behavior.unknown08->getComponent<GfComTransform>();
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame = transform->unknown001();
  return frame->getSyncedWorldTransform().unknown00.y;
}

} // namespace pc
} // namespace gf
