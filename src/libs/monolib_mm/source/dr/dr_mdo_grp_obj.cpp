#include "dr/dr_mdo_grp_obj.h"

#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdl_obj.h"
#include "dr/dr_mdo_ctl_dammy.h"
#include "dr/dr_mdo_ctl_nom.h"
#include "dr/dr_mdo_mat.h"
#include "ml/critical_section.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

// The game zeroes the three lists before the DrResMdoSortGrp constructor call (0x71007cf634..0x71007cf640, hence the value-initialised members) and
// stores zero in each of them again at the end (0x71007cf6f4..0x71007cf6fc, ruling 5 / P3: redundant stores the asm shows).
DrMdoGrpObj::DrMdoGrpObj(int viewNum, u32 num) : DrMdlBase(viewNum), unknown38(), unknown58(), m_drResMdoSortGrp(this) {
  unknown1c = unknown037_5;
  s32 count = num;
  if (count < 0) {
    count = 1;
  }
  if (count > 0xff) {
    count = 0xff;
  }
  unknown68 = count;
  unknown6c = 0;
  void *work = mtl::MemManager::allocate(DrMan::get()->unknown10, unknown68 * (sizeof(DrResChankList<DrMdlBase>) + sizeof(DrResChankList<DrMdlBase> *)), 0x10, false, "no name", 0);
  unknown70 = work;
  unknown28 = static_cast<DrResChankList<DrMdlBase> *>(work);
  unknown30 = static_cast<DrResChankList<DrMdlBase> **>(static_cast<void *>(unknown28 + unknown68));
  for (int i = 0; i < unknown68; i++) {
    DrResChankList<DrMdlBase> *list = &unknown28[i];
    list->unknown00 = nullptr;
    list->unknown08 = nullptr;
  }
  // Redundant zero stores of the three lists (0x71007cf6f4: stp xzr, xzr at +0x58, +0x48, +0x38, ruling 5 / P3).
  unknown58.unknown00 = nullptr;
  unknown58.unknown08 = nullptr;
  unknown38[1].unknown00 = nullptr;
  unknown38[1].unknown08 = nullptr;
  unknown38[0].unknown00 = nullptr;
  unknown38[0].unknown08 = nullptr;
}

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

DrMdlObj *DrMdoGrpObj::createMdl(const void *data, const char *name, u32 index) {
  CS lock(DrMan::getCriticalSection());
  DrMdlObj *mdl;
  if (DrMdlMan::headerChek(data) == 1) {
    mdl = new (DrMan::s_pTop->unknown10) DrMdoCtlNom(data, name, DrMan::s_pTop, unknown1a);
  } else {
    mdl = new (DrMan::s_pTop->unknown10) DrMdoCtlDammy(data, DrMan::s_pTop, unknown1a);
  }
  mdl->m_disp |= unknown038_2;
  // The game compares the group count with the index as signed (0x71007cf9b0) and stores the clamped index in the 16-bit group member (0x71007cf9bc).
  if (unknown68 <= static_cast<s32>(index)) {
    index = unknown68 - 1;
  }
  mdl->unknown1e = index;
  mdl->unknownfc |= DrMdoMat::unknown027_27;
  unknown38[DrMan::s_nDblStockIdx].unknown004(mdl);
  return mdl;
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
  u32 groups = DrMan::s_pTop->m_drMdlMan->unknown23c;
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      if ((mdl->m_disp & unknown038_0) && ((1 << mdl->m_groups) & groups)) {
        mdl->shadowRender();
      }
    }
  }
}

bool DrMdoGrpObj::shadowCacheRender(DrPixlShadowCacheObj &cache) {
  u32 groups = DrMan::s_pTop->m_drMdlMan->unknown23c;
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      if ((mdl->m_disp & unknown038_0) && ((1 << mdl->m_groups) & groups)) {
        if (!mdl->shadowCacheRender(cache)) {
          return false;
        }
      }
    }
  }
  return true;
}

void DrMdoGrpObj::shadowCacheOnlyRender() {
  u32 groups = DrMan::s_pTop->m_drMdlMan->unknown23c;
  for (int i = 0; i < unknown6c; i++) {
    for (DrMdlBase *mdl = unknown30[i]->unknown00; mdl != nullptr; mdl = mdl->unknown10) {
      if ((1 << mdl->m_groups) & groups) {
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
