#include "event/mdlstm_obj.h"

#include "event/model_obj.h"
#include "event/model_util.h"

namespace event {

MdlstmObj::MdlstmObj()
    : unknown08(0), unknown0c(STATE_NONE), unknown10(0.0f), _98(0), _9c(0), _a0(0), _a4(false), _a5(false), _a8(0), _b0(nullptr), _b8(nullptr), _c0(nullptr), _c8(nullptr), _d0(nullptr),
      unknownd8(nullptr), unknowne0(nullptr) {}

void MdlstmObj::destroy() { finishFree(); }

void MdlstmObj::finishLoaded() { unknown0c = STATE_LOADED; }

void MdlstmObj::finishDelay() { unknown0c = STATE_DELAY; }

void MdlstmObj::finishBusy() {
  ModelUtil::setupRenderState(unknowne0->getHandle());
  unknown0c = STATE_BUSY;
}

void MdlstmObj::load() { unknown0c = STATE_LOAD; }

void MdlstmObj::dispose() {
  unknown0c = STATE_DISPOSE;
  unknowne8 = 1;
}

bool MdlstmObj::isLoaded() const { return unknown0c > STATE_LOADING; }

bool MdlstmObj::isDisposeable(ModelObj *model) const { return unknown0c == STATE_ACTIVE && unknowne0 == model; }

bool MdlstmObj::isActive() const { return unknown0c != STATE_NONE; }

bool MdlstmObj::isLoading(f32 threshold) const {
  if (unknown10 <= threshold && static_cast<u32>(unknown0c - STATE_INIT) < 6) {
    return true;
  }
  return false;
}

bool MdlstmObj::isBuildable(const char *name, u32 value) const {
  if (unknown0c != STATE_BUSY || !(unknown08 & 1) || _a8 != value)
    return false;
  return __builtin_strcmp(unknown14.c_str(), name) == 0;
}

bool MdlstmObj::isBuildable(MODEL_TYPE type, u32 id, u32 value) const {
  if (unknown0c != STATE_BUSY || (unknown08 & 1) || _a8 != value || _98 != static_cast<u32>(type) || _9c != id) {
    return false;
  }
  return true;
}

bool MdlstmObj::checkByHandle(gf::GF_OBJ_HANDLE *handle) const {
  if (unknownd8 != nullptr && unknownd8->getHandle() == handle) {
    return true;
  }
  if (unknowne0 != nullptr && unknowne0->getHandle() == handle) {
    return true;
  }
  return false;
}

} // namespace event
