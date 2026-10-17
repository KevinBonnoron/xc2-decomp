#include "event/chara_mount.h"

#include "gf/event/gf_evt_model.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace event {

void CharaMount::init() {}

void CharaMount::term() {
  if (model != nullptr && parent != nullptr) {
    gf::GfComTransform *transform = gf::GfObjUtil::getObj(model->handle)->getComponent<gf::GfComTransform>();
    model->resetMount(parent);
    transform->setPosition(position);
    transform->setRotation(rotation);
    parent = nullptr;
  }
}

} // namespace event
