#include "event/effect_util.h"

#include "bdat.h"

namespace event {

const char *EffectUtil::getAttrName(u32 id) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_attrtype"), "name", id, 7)); }

} // namespace event
