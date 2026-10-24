#include "event/chara_mount.h"

#include "gf/event/gf_evt_model.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace event {

void CharaMount::init() {}

void CharaMount::term() {
  if (unknown08 != nullptr && unknown10 != nullptr) {
    gf::GfComTransform *transform = gf::GfObjUtil::getObj(unknown08->unknown20)->getComponent<gf::GfComTransform>();
    unknown08->resetMount(unknown10);
    transform->setPosition(unknown20);
    transform->setRotation(unknown30);
    unknown10 = nullptr;
  }
}

} // namespace event
