#include "dr/dr_light_obj_global_ibl.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_res_use_query_obj.h"
#include "grlib/cglib_ctl_vertex.h"

namespace ml {
class DrPixlOccQuery;

int DrLightObjGlobalIBL::getPriority() const { return m_priority; }

void DrLightObjGlobalIBL::bindVertex(u32 index) {
  unknown70 = index;
  grlib::CGLibCtlVertex::setVertex(unknown20[index].unknown00);
}

void DrLightObjGlobalIBL::drawVertex() { unknown20[unknown70].unknown28.drawIndex(); }

void DrLightObjGlobalIBL::beginOccQuery() {
  DrPixlOccQuery *occQuery = DrMan::getIns()->unknown78->unknown7f8;
  unknown20[unknown70].unknown110->begin(occQuery);
}

void DrLightObjGlobalIBL::endOccQuery() { unknown20[unknown70].unknown110->end(); }

} // namespace ml
