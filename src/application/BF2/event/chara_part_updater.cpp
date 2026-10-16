#include "event/chara_part_updater.h"

#include "gf/object/gf_obj_handle.h"

namespace event {

CharaPartUpdater::CharaPartUpdater() : handle(gf::INVALID_HANDLE), mModel(nullptr) {}

void CharaPartUpdater::create(gf::GF_OBJ_HANDLE *handle, gf::GfEvtModel *model) {
  this->handle = handle;
  mModel = model;
}

void CharaPartUpdater::destroy() {
  handle = gf::INVALID_HANDLE;
  mModel = nullptr;
  mRequests.clear();
}

void CharaPartUpdater::update(f32 delta) { updateRequest(); }

void CharaPartUpdater::eraseRequest(TYPE type, const char *name) {
  for (Request *it = mRequests.begin(); it != mRequests.end(); ++it) {
    if (it->type == type && __builtin_strcmp(it->name, name) == 0) {
      mRequests.erase(it);
      return;
    }
  }
}

void CharaPartUpdater::setExtDisp(const char *name, bool isDisp) {
  if (mRequests.size() >= REQUEST_COUNT) {
    mRequests.erase(mRequests.begin());
  }
  eraseRequest(TYPE_EXT_DISP, name);
  Request request;
  request.type = TYPE_EXT_DISP;
  request.name = name;
  request.value = isDisp ? 1.0f : 0.0f;
  mRequests.push_back(request);
  updateRequest();
}

void CharaPartUpdater::setExtDispWeapon(const char *name, bool isDisp) {
  if (mRequests.size() >= REQUEST_COUNT) {
    mRequests.erase(mRequests.begin());
  }
  eraseRequest(TYPE_EXT_DISP, name);
  Request request;
  request.type = TYPE_EXT_DISP_WEAPON;
  request.name = name;
  request.value = isDisp ? 1.0f : 0.0f;
  mRequests.push_back(request);
  updateRequest();
}

void CharaPartUpdater::setExtParam(const char *name, f32 value) {
  if (mRequests.size() >= REQUEST_COUNT) {
    mRequests.erase(mRequests.begin());
  }
  eraseRequest(TYPE_EXT_PARAM, name);
  Request request;
  request.type = TYPE_EXT_PARAM;
  request.name = name;
  request.value = value;
  mRequests.push_back(request);
  updateRequest();
}

} // namespace event
