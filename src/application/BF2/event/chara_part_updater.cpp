#include "event/chara_part_updater.h"

#include "gf/object/gf_obj_handle.h"

namespace event {

CharaPartUpdater::CharaPartUpdater() : unknown08(gf::INVALID_HANDLE), unknown10(nullptr) {}

void CharaPartUpdater::create(gf::GF_OBJ_HANDLE *handle, gf::GfEvtModel *model) {
  this->unknown08 = handle;
  unknown10 = model;
}

void CharaPartUpdater::destroy() {
  unknown08 = gf::INVALID_HANDLE;
  unknown10 = nullptr;
  unknown18.clear();
}

void CharaPartUpdater::update(f32 delta) { updateRequest(); }

void CharaPartUpdater::eraseRequest(TYPE type, const char *name) {
  for (unknown001 *it = unknown18.begin(); it != unknown18.end(); ++it) {
    if (it->unknown00 == type && __builtin_strcmp(it->unknown08, name) == 0) {
      unknown18.erase(it);
      return;
    }
  }
}

void CharaPartUpdater::setExtDisp(const char *name, bool isDisp) {
  if (unknown18.size() >= REQUEST_COUNT) {
    unknown18.erase(unknown18.begin());
  }
  eraseRequest(TYPE_EXT_DISP, name);
  unknown001 request;
  request.unknown00 = TYPE_EXT_DISP;
  request.unknown08 = name;
  request.unknown10 = isDisp ? 1.0f : 0.0f;
  unknown18.push_back(request);
  updateRequest();
}

void CharaPartUpdater::setExtDispWeapon(const char *name, bool isDisp) {
  if (unknown18.size() >= REQUEST_COUNT) {
    unknown18.erase(unknown18.begin());
  }
  eraseRequest(TYPE_EXT_DISP, name);
  unknown001 request;
  request.unknown00 = TYPE_EXT_DISP_WEAPON;
  request.unknown08 = name;
  request.unknown10 = isDisp ? 1.0f : 0.0f;
  unknown18.push_back(request);
  updateRequest();
}

void CharaPartUpdater::setExtParam(const char *name, f32 value) {
  if (unknown18.size() >= REQUEST_COUNT) {
    unknown18.erase(unknown18.begin());
  }
  eraseRequest(TYPE_EXT_PARAM, name);
  unknown001 request;
  request.unknown00 = TYPE_EXT_PARAM;
  request.unknown08 = name;
  request.unknown10 = value;
  unknown18.push_back(request);
  updateRequest();
}

} // namespace event
