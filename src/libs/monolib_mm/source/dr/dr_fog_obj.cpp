#include "dr/dr_fog_obj.h"
#include "dr/dr_fog_obj_gbl.h"

namespace ml {

DrFogObj::DrFogObj(DrMan *man)
    : unknown08(nullptr), unknown10(nullptr), unknown18(man), unknown20(0.5f, 0.5f, 0.5f), unknown2c(0.0f, 0.0f, 0.0f), unknown38(0.0f, 0.0f, 0.0f), unknown44(0.1f), unknown48(10000.0f),
      unknown4c(1.0f), unknown50(1.0f), unknown54(1.0f), unknown58(1.0f), unknown5c(1.0f), unknown60(0.0f), unknown64(1.0f) {}

DrFogObjGbl::DrFogObjGbl(DrMan *man) : DrFogObj(man) {}

void DrFogObjGbl::update() {}

} // namespace ml
