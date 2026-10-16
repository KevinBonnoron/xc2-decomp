#include "framework/object/component_object.h"

#include "framework/object/updatable_object.h"

namespace fw {

u32 ComponentObject::getLayer() const { return owner->layer; }

} // namespace fw
