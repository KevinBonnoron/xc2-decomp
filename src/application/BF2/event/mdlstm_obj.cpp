#include "event/mdlstm_obj.h"

#include "event/model_obj.h"
#include "event/model_util.h"

namespace event {

MdlstmObj::MdlstmObj()
    : flags(0), state(STATE_NONE), frame(0.0f), _98(0), _9c(0), _a0(0), _a4(false), _a5(false), _a8(0), _b0(nullptr), _b8(nullptr), _c0(nullptr),
      _c8(nullptr), _d0(nullptr), mReuseModel(nullptr), mModel(nullptr) {}

void MdlstmObj::finishLoaded() { state = STATE_LOADED; }

void MdlstmObj::finishDelay() { state = STATE_DELAY; }

void MdlstmObj::finishBusy() {
  ModelUtil::setupRenderState(mModel->getHandle());
  state = STATE_BUSY;
}

void MdlstmObj::load() { state = STATE_LOAD; }

void MdlstmObj::dispose() {
  state = STATE_DISPOSE;
  mDisposeDelay = 1;
}

bool MdlstmObj::isLoaded() const { return state > STATE_LOADING; }

bool MdlstmObj::isDisposeable(ModelObj *model) const { return state == STATE_ACTIVE && mModel == model; }

bool MdlstmObj::isActive() const { return state != STATE_NONE; }

bool MdlstmObj::isLoading(f32 threshold) const {
  if (frame <= threshold && static_cast<u32>(state - STATE_INIT) < 6) {
    return true;
  }
  return false;
}

bool MdlstmObj::isBuildable(const char *name, u32 value) const {
  if (state != STATE_BUSY || !(flags & 1) || _a8 != value)
    return false;
  return __builtin_strcmp(path.c_str(), name) == 0;
}

bool MdlstmObj::checkByHandle(gf::GF_OBJ_HANDLE *handle) const {
  if (mReuseModel != nullptr && mReuseModel->getHandle() == handle) {
    return true;
  }
  if (mModel != nullptr && mModel->getHandle() == handle) {
    return true;
  }
  return false;
}

} // namespace event
