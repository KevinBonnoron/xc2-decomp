#include "dr/dr_pixl_occ_query.h"

#include "dr/dr_ap_gx_type.h"

namespace ml {

void DrPixlOccQuery::end() { DrAPGxType::endOccQuery(); }

} // namespace ml
