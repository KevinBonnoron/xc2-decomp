#include "event/object_camera.h"

namespace event {

void ObjectCamera::start() {}

void ObjectCamera::setCutName(const char *name) { mCutName = name; }

bool ObjectCamera::OnBouRectSelect(const IBouCallback::SelectParam &param) { return false; }

} // namespace event
