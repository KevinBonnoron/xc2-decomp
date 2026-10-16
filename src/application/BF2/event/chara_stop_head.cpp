#include "event/chara_stop_head.h"

#include "gf/object/gf_obj_util.h"

namespace event {

ICmd::RESULT CharaStopHead::update(const Param &param) {
  gf::GfObjUtil::getObj(handle);
  return RESULT_END;
}

} // namespace event
