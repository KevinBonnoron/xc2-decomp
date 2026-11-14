#include "dr/dr_mdo_grp_obj.h"

#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_ctl_nom.h"
#include "dr/dr_mdo_mat.h"
#include "mtl/mem_manager.h"

namespace ml {

DrMdoGrpObj::~DrMdoGrpObj() {
  for (int i = 0; i < unknown68; i++) {
    unknown28[i].unknown005();
  }
  if (unknown70 != nullptr) {
    mtl::MemManager::deallocate(unknown70, 0, false);
    unknown70 = nullptr;
  }
  unknown38[0].unknown005();
  unknown38[1].unknown005();
  unknown58.unknown005();
}

void DrMdoGrpObj::dispOffUpdate() {
  updateList();
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      mdl->dispOffUpdate();
    }
  }
}

void DrMdoGrpObj::shadowRender() {
  u32 groups = DrMan::s_pTop->unknown88->unknown23c;
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      if ((mdl->unknown20 & unknown038_0) && ((1 << mdl->unknown18) & groups)) {
        mdl->shadowRender();
      }
    }
  }
}

bool DrMdoGrpObj::shadowCacheRender(DrPixlShadowCacheObj &cache) {
  u32 groups = DrMan::s_pTop->unknown88->unknown23c;
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      if ((mdl->unknown20 & unknown038_0) && ((1 << mdl->unknown18) & groups)) {
        if (!mdl->shadowCacheRender(cache)) {
          return false;
        }
      }
    }
  }
  return true;
}

void DrMdoGrpObj::shadowCacheOnlyRender() {
  u32 groups = DrMan::s_pTop->unknown88->unknown23c;
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      if ((1 << mdl->unknown18) & groups) {
        mdl->shadowCacheOnlyRender();
      }
    }
  }
}

void DrMdoGrpObj::occRender() {
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      if (static_cast<DrMdoMat *>(mdl)->unknownf8 & DrMdoMat::unknown028_7) {
        mdl->occRender();
      }
    }
  }
}

void DrMdoGrpObj::callShadowCacheUpdate(u64 flags) {
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      mdl->callShadowCacheUpdate(flags);
    }
  }
}

void DrMdoGrpObj::callNomSetupRender() {
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      DrMdoCtlNom *nom = static_cast<DrMdoCtlNom *>(mdl);
      if (nom->unknownf8 & DrMdoMat::unknown028_7) {
        nom->callNomSetupRender();
      }
    }
  }
}

void DrMdoGrpObj::callZSortNomZpreePassRender() {
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      DrMdoCtlNom *nom = static_cast<DrMdoCtlNom *>(mdl);
      if (nom->unknownf8 & DrMdoMat::unknown028_7) {
        nom->callZSortNomZpreePassRender();
      }
    }
  }
}

void DrMdoGrpObj::callZSortThicknessRenderFirst() {
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      DrMdoCtlNom *nom = static_cast<DrMdoCtlNom *>(mdl);
      if (nom->unknownf8 & DrMdoMat::unknown028_7) {
        nom->callZSortThicknessRenderFirst();
      }
    }
  }
}

void DrMdoGrpObj::callZSortThicknessRenderSecond() {
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      DrMdoCtlNom *nom = static_cast<DrMdoCtlNom *>(mdl);
      if (nom->unknownf8 & DrMdoMat::unknown028_7) {
        nom->callZSortThicknessRenderSecond();
      }
    }
  }
}

void DrMdoGrpObj::callZSortNomRender() {
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      DrMdoCtlNom *nom = static_cast<DrMdoCtlNom *>(mdl);
      if (nom->unknownf8 & DrMdoMat::unknown028_7) {
        nom->callZSortNomRender();
      }
    }
  }
}

void DrMdoGrpObj::callZSortGBuffRender() {
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      DrMdoCtlNom *nom = static_cast<DrMdoCtlNom *>(mdl);
      if (nom->unknownf8 & DrMdoMat::unknown028_7) {
        nom->callZSortGBuffRender();
      }
    }
  }
}

void DrMdoGrpObj::callZSortLightPrePassRender() {
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      DrMdoCtlNom *nom = static_cast<DrMdoCtlNom *>(mdl);
      if (nom->unknownf8 & DrMdoMat::unknown028_7) {
        nom->callZSortLightPrePassRender();
      }
    }
  }
}

void DrMdoGrpObj::callZSortNomAlphaRender() {
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      DrMdoCtlNom *nom = static_cast<DrMdoCtlNom *>(mdl);
      if (nom->unknownf8 & DrMdoMat::unknown028_7) {
        nom->callZSortNomAlphaRender();
      }
    }
  }
}

void DrMdoGrpObj::callZSortNomSpAlphaRender() {
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      DrMdoCtlNom *nom = static_cast<DrMdoCtlNom *>(mdl);
      if (nom->unknownf8 & DrMdoMat::unknown028_7) {
        nom->callZSortNomSpAlphaRender();
      }
    }
  }
}

void DrMdoGrpObj::callZSortNomRefractionRender() {
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      DrMdoCtlNom *nom = static_cast<DrMdoCtlNom *>(mdl);
      if (nom->unknownf8 & DrMdoMat::unknown028_7) {
        nom->callZSortNomRefractionRender();
      }
    }
  }
}

void DrMdoGrpObj::resourceInit() {}

} // namespace ml
