#include "dr/dr_mdo_ctl_nom.h"

#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_mdo_shd_obj.h"
#include "dr/dr_res_mdo_vtx_mesh_obj.h"

namespace ml {

void DrMdoCtlNom::updateShdMdl() {
  if (unknown1d0 != nullptr && unknown1d0->update(unknown30->unknown88)) {
    unknown20 &= ~0x60;
  }
}

void DrMdoCtlNom::callZSortLightPrePassRender() {
  if ((unknownf8 & unknown028_3) == 0) {
    return;
  }
  nomCallRender(3);
}

void DrMdoCtlNom::callZSortNomAlphaRender() {
  if ((unknownf8 & unknown028_4) != 0) {
    nomCallRender(4);
  }
  if (unknown1d8 != nullptr) {
    unknown1d8->alpRender();
  }
}

void DrMdoCtlNom::callZSortNomSpAlphaRender() {
  if ((unknownf8 & unknown028_5) == 0) {
    return;
  }
  nomCallRender(5);
}

void DrMdoCtlNom::callZSortGBuffRender() {
  if ((unknownf8 & unknown028_1) == 0) {
    return;
  }
  nomCallRender(1);
}

void DrMdoCtlNom::callZSortNomRefractionRender() {
  if ((unknownf8 & unknown028_2) == 0) {
    return;
  }
  nomCallRender(2);
}

void DrMdoCtlNom::callLastAlphaNomRender() {
  if ((unknownf8 & unknown028_25) == 0) {
    return;
  }
  lastAlphaCallRender();
}

void DrMdoCtlNom::callFastAlphaNomRender() {
  if ((unknownf8 & unknown028_26) == 0) {
    return;
  }
  fastAlphaCallRender();
}

void DrMdoCtlNom::callCldBackAlphaNomRender() {
  if ((unknownf8 & unknown028_27) == 0) {
    return;
  }
  cldBackAlphaCallRender();
}

} // namespace ml
