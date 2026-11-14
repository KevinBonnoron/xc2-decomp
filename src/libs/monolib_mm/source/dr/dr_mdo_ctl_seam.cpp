#include "dr/dr_mdo_ctl_seam.h"

#include <string.h>

#include "cloud/cloud_man.h"
#include "cloud/cloud_mdl_data_obj.h"
#include "dr/dr_ap_cache.h"
#include "dr/dr_calc_clip_obj.h"
#include "dr/dr_calc_cp_plane_obj.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_env_coli_obj.h"
#include "dr/dr_environment_obj.h"
#include "dr/dr_global_ibl_man.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_base.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_ctl.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_res_etc_tex_list.h"
#include "dr/dr_res_mdo_inst_mdl_info.h"
#include "dr/dr_res_mdo_mat.h"
#include "dr/dr_res_mdo_pos_add_list.h"
#include "dr/dr_res_mdo_seam_coli.h"
#include "dr/dr_res_mdo_seam_read.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "dr/dr_res_mdo_sort.h"
#include "grlib/cglib_tri_uniform_block.h"
#include "grlib/cglib_uniform_array.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/mem_manager.h"

namespace ml {

DrMdoCtlSeam::DrMdoCtlSeam(int viewNum)
    : DrMdlObj(viewNum), unknown3e0(nullptr), unknown3e8(nullptr), unknown3f0(nullptr), unknown3f8(nullptr), unknown400(nullptr), unknown408(nullptr), unknown410(nullptr), unknown418(nullptr),
      unknown630(nullptr), unknown638(nullptr), unknown658(nullptr), unknown6d8(nullptr), unknownb30(nullptr), unknownb40(nullptr), unknownc00(0), unknownc02(0), unknownc04(0), unknownc06(0),
      unknownc08(0), unknownc0a(0), unknownc0c(0), unknownc0e(0), unknownc10(0), unknownc12(0), unknownc14(0), unknownc16(0), unknownc18(0), unknownc1a(0), unknownc1c(0), unknownc1e(0), unknownc20(0),
      unknownc22(0), unknownc24(0), unknownc26(0), unknownc28(0), unknownc2e(0), unknownc2f(0), unknownc30(0), unknownc34(0), unknownc38(0), unknownc3c(0), unknownc40(0), unknownc44(0), unknownc48(0),
      unknownc4c(0), unknownc50(0), unknownc54(0), unknownc58(0), unknownc5c(0), unknownc60(0), unknownc64(0), unknownc68(0), unknownc6c(0), unknownc70(0), unknownc74(0), unknownc78(0), unknownc7c(0),
      unknownc80(0), unknownc84(0), unknownc88(1), unknownc90(0), unknownc98(0), unknownca0(0), unknownca2(0), unknownca4(0), unknownca6(0), unknowncc8(false), unknown14b0(0), unknown14c0(0),
      unknown14c8(0) {
  m_coliListMax[0] = 0;
  m_coliListMax[1] = 0;
  unknowncac = 0;
  for (int i = 0; i < 4; i++) {
    unknowncae[i] = -1;
    unknowncb8[i] = 0;
  }
  unknown1c = unknown037_3;
  unknown420.clear();
  unknown528.clear();
}

void *DrMdoCtlSeam::getColiListTbl() { return m_coliListTbl[DrMan::s_nDblIdx]; }

u32 DrMdoCtlSeam::getColiListMax() { return m_coliListMax[DrMan::s_nDblIdx]; }

u32 DrMdoCtlSeam::isRead(int index) const {
  if (((unknownc7c >> 28) & 1) == 0) {
    return unknowncd0.unknown4a & (1 << index);
  }
  return 0;
}

void DrMdoCtlSeam::setErrCode(int code, int param) { unknown004(code, param); }

void DrMdoCtlSeam::releaseFreeSeamTexture(DrResMdoSeamTexture *texture, bool isAll) {
  if (isAll) {
    texture->release();
    unknown1b0.unknown002(texture);
  } else {
    DrResMdoSeamMemObj *mem = texture->unknown88;
    DrResMdoSeamMemObj *heightMem = texture->unknown90;
    unknownbe0[texture->unknown9e] = 0;
    texture->release();
    texture->unknown88 = nullptr;
    unknown1b0.unknown002(texture);
    if (mem != nullptr) {
      unknown6e0.releaseFreeObj(mem);
    }
    if (heightMem != nullptr) {
      unknown6e0.releaseFreeObj(heightMem);
    }
  }
}

int DrMdoCtlSeam::calcSemaAlignment(u32 size, u32 alignment) { return unknown005(size, alignment); }

void DrMdoCtlSeam::releaseFreeSeamMemObj(DrResMdoSeamMemObj *mem) { unknown6e0.releaseFreeObj(mem); }

void DrMdoCtlSeam::releaseFreeSeamTexList(DrResMdoSeamTexList *texList, bool isAll) {
  if (isAll) {
    texList->release();
    unknown1e8.unknown002(texList);
  } else {
    DrResMdoSeamMemObj *mem = texList->unknown18;
    unknownbf0[texList->unknown3c] = 0;
    texList->release();
    texList->unknown18 = nullptr;
    unknown1e8.unknown002(texList);
    if (mem != nullptr) {
      unknown6e0.releaseFreeObj(mem);
    }
  }
}

void DrMdoCtlSeam::releaseSeam() {
  resourceRelease();
  unknown698.release();
  if (unknown638 != nullptr) {
    DrResMdoInstMdlInfo::release(unknown638);
  }
  if (unknown630 != nullptr) {
    unknown630->release();
    unknown630 = nullptr;
  }
  if (unknown3e8 != nullptr) {
    unknown3e8->~DrResMdoSortSeamAll();
  }
  if (unknown3f0 != nullptr) {
    unknown3f0->~DrResMdoSortSeamEnvMap();
  }
  unknown3e8 = nullptr;
  unknown3f0 = nullptr;
  unknown1b0.unknown003();
  unknown1e8.unknown003();
  unknown220.unknown003();
  unknown258.unknown003();
  unknown290.unknown003();
  unknown2c8.unknown003();
  unknown300.unknown003();
  unknown338.unknown003();
  unknown370.unknown003();
  unknown3a8.unknown003();
  unknown6e0.releaseMem();
  if (unknownb28 != nullptr) {
    unknownb28->unknown001();
    unknownb28 = nullptr;
  }
  DevGraph::releaseMemPoolBuffer(unknownb40);
  if (unknownb48 != nullptr) {
    mtl::MemManager::deallocate(unknownb48, 0, false);
    unknownb48 = nullptr;
  }
  if (unknownb40 != nullptr) {
    mtl::MemManager::deallocate(unknownb40, 0, false);
    unknownb40 = nullptr;
  }
  unknowncd0.release();
  m_drMan->unknown88->delMpfObj();
  if (m_drMan->unknown1e00 != nullptr) {
    m_drMan->unknown1e00->_64 = 1.0f;
  }
}

void DrMdoCtlSeam::resourceRelease() {
  if (unknown638 != nullptr) {
    unknown638->releaseCall();
  }
  if (unknownb30 != nullptr) {
    unknownb30->release();
    unknownb30 = nullptr;
  }
  if (unknown3f8 != nullptr) {
    unknown3f8->release();
    unknown3f8 = nullptr;
  }
  if (unknown400 != nullptr) {
    unknown400->release();
    unknown400 = nullptr;
  }
  if (unknown408 != nullptr) {
    unknown408->release();
    unknown408 = nullptr;
  }
  if (unknown658 != nullptr) {
    unknown658->release();
    unknown658 = nullptr;
  }
  if (unknown418 != nullptr) {
    unknown418->release();
    unknown418 = nullptr;
  }
  DrGlobalIBLMan *globalIBLMan = m_drMan->unknown160[unknown1a];
  for (DrGlobalIBLPack *pack : unknown420) {
    globalIBLMan->releaseObj(pack);
  }
  unknown420.clear();
  for (DrEnvironmentObj *environment : unknown528) {
    if (environment != nullptr) {
      environment->release();
    }
  }
  unknown528.clear();
}

bool DrMdoCtlSeam::calcBegin() {
  unknownc7c &= ~0x29441d;
  unknownf8 = 0;
  unknown168 = 0;
  unknownc84 = 0;
  u32 deleteCall = 0x40000000 << DrMan::s_nDblIdx;
  if (deleteCall & unknownc7c) {
    unknownc7c &= ~deleteCall;
    unknownc7c |= 0x10000000;
  }
  bool isCalc = false;
  bool isDisp = false;
  if (((unknownc7c >> 18) & 1) == 0) {
    if (++unknownc18 > 3) {
      unknownc7c |= 0x40000;
    }
  } else if (((unknownc7c >> 28) & 1) == 0) {
    isCalc = true;
    isDisp = true;
  } else {
    isCalc = true;
    unknownc16++;
    if (!unknowncd0.isRead()) {
      unknowncd0.release();
      if (unknownc16 > 3) {
        unknown20 |= unknown038_3 | unknown038_3 << 1;
      }
    }
    unknownc7c |= 0x80000;
    if (((unknownc7c >> 12) & 1) == 0) {
      unknownc7c |= 0x1000;
      if (unknown1a == 0) {
        m_drMan->unknown78->unknown800->delShadowCacheUpdate();
      }
    }
    if (unknownc16 > 1) {
      unknownc7c |= 0x20000000;
      if (unknownc16 != 2) {
        unknowncc8 = true;
      }
    }
  }
  DrCalcViewWork *viewWork = m_drMan->unknown580->unknown10;
  if (unknown638 != nullptr) {
    DrResMdlInstMdlArg arg;
    arg.unknown00 = &viewWork->unknown400;
    arg.unknown10 = isDisp;
    arg.unknown14 = unknown1a;
    arg.unknown18 = unknowndc;
    arg.unknown08 = unknownd30.unknown40 == 0 ? nullptr : unknownd30.unknown10;
    unknown638->update(arg);
  }
  if (unknownb30 != nullptr) {
    unknownb30->setCallDisp(isDisp);
  }
  if (unknown1a == 0 && ((unknownc7c >> 28) & 1) == 0) {
    f32 first = 1141.0f;
    f32 second = -761.0f;
    f32 third = 0.0f;
    if (unknown1a8->unknown80 != 0) {
      const unknown751 *table = reinterpret_cast<const unknown751 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown80);
      const unknown750 *area = reinterpret_cast<const unknown750 *>(reinterpret_cast<const u8 *>(table) + table->unknown04);
      for (int i = 0; i < table->unknown00; i++, area++) {
        if (viewWork->unknown400.x > area->unknown08[0] || viewWork->unknown400.y > area->unknown08[1] || viewWork->unknown400.z > area->unknown08[2] || viewWork->unknown400.x < area->unknown14[0] ||
            viewWork->unknown400.y < area->unknown14[1] || viewWork->unknown400.z < area->unknown14[2]) {
          continue;
        }
        first = area->unknown00;
        second = area->unknown04;
        third = area->unknown20;
        break;
      }
    }
    DrMan *drMan = m_drMan;
    if (!drMan->unknown1d8e) {
      DrPixlPostParm *postParm = drMan->unknown120[drMan->unknown1c98];
      postParm->unknown10d4 = first;
      postParm->unknown10d8 = second;
      postParm->unknown10dc = third;
    }
  }
  return isCalc;
}

void DrMdoCtlSeam::calcEnd() {
  bool isRenderSafe = false;
  if (unknownc7c & 0x10000) {
    unknownc7c &= ~0x8000;
    unknownc12 = 0;
  } else if (++unknownc12 > 4) {
    unknownc12 = 4;
    unknownc7c |= 0x8000;
    isRenderSafe = true;
  } else {
    unknownc7c &= ~0x8000;
  }
  if (isRenderSafe) {
    unknownc7c &= ~0x20000;
    unknownc14 = 0;
  } else {
    unknownc14++;
    if (unknownc14 >= 900) {
      unknownc14 = 900;
      unknownc7c |= 0x20000;
    } else {
      unknownc7c &= ~0x20000;
    }
  }
  if (unknownc7c & 0x20000) {
    unknownc7c |= 0x8000;
    unknownc12 = 4;
  }
  if (unknownc7c & 0x200000) {
    unknownc7c |= 0x400000;
    unknownc2a = 30;
  }
  bool isReadSafe = false;
  if (unknownc7c & 0x400) {
    unknownc7c &= ~0x800;
    unknownc0e = 0;
  } else if (++unknownc0e > 4) {
    unknownc0e = 4;
    unknownc7c |= 0x800;
    isReadSafe = true;
  } else {
    unknownc7c &= ~0x800;
  }
  if (isReadSafe) {
    unknownc7c &= ~0x100000;
    unknownc10 = 0;
  } else {
    unknownc10++;
    if (unknownc10 >= 900) {
      unknownc10 = 900;
      unknownc7c |= 0x100000;
    } else {
      unknownc7c &= ~0x100000;
    }
  }
  if (unknownc7c & 0x100000) {
    unknownc7c |= 0x800;
    unknownc0e = 4;
  }
  if (unknownc7c & 0x800) {
    m_drMan->setSeamMapStmOk(false);
  } else {
    m_drMan->setSeamMapStmOk(true);
  }
}

void DrMdoCtlSeam::updateTexutreSeam() {
  if (unknowncc8) {
    DrResMdoSeamTexture::SEAMRES_HEIGHT_CNTMAX = 3;
    DrResMdoSeamTexture::SEAMRES_NOM_CNTMAX = 10;
    DrResMdoSeamTexList::setListCnt(10);
  } else {
    if (unknownd30.unknown40 == 0) {
      DrResMdoSeamTexList::setListCnt(60);
      DrResMdoSeamTexture::SEAMRES_NOM_CNTMAX = 120;
    } else {
      DrResMdoSeamTexList::setListCnt(10);
      DrResMdoSeamTexture::SEAMRES_NOM_CNTMAX = 10;
    }
    if (unknownc7c & 0x20) {
      DrResMdoSeamTexture::SEAMRES_HEIGHT_CNTMAX = 3;
    } else {
      DrResMdoSeamTexture::SEAMRES_HEIGHT_CNTMAX = 60;
    }
  }
  DrResMdoSeamTexture *texture = unknown1b0.unknown10.unknown00;
  if (unknowncc8) {
    while (texture != nullptr) {
      DrResMdoSeamTexture *next = texture->unknown08;
      releaseFreeSeamTexture(texture, false);
      texture = next;
    }
    unknownc34 = 0;
  } else {
    while (texture != nullptr) {
      DrResMdoSeamTexture *next;
      if (texture->update()) {
        next = texture->unknown08;
        const MdsSeamOfsTexTblData *table = reinterpret_cast<const MdsSeamOfsTexTblData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown5c);
        unknownc34 -= table[texture->unknown9e].unknown04;
        if (texture->unknowna3 == 1) {
          unknownc34 -= table[texture->unknown9e].unknown0c;
        }
        releaseFreeSeamTexture(texture, false);
      } else {
        if (texture->unknowna1) {
          const MdsSeamOfsTexTblData *table = reinterpret_cast<const MdsSeamOfsTexTblData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown5c);
          const MdsSeamOfsTexTblData *data = &table[texture->unknown9e];
          if (texture->unknowna3 == 1) {
            texture->changeMemTexture(calcSemaAlignment(data->unknown0c, 0x1000), data->unknown04);
          } else {
            texture->changeMemTexture(data->unknown04);
          }
        } else if (texture->unknowna3 == 1 && texture->updateHeight()) {
          const MdsSeamOfsTexTblData *table = reinterpret_cast<const MdsSeamOfsTexTblData *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown5c);
          texture->unknowna3 = 0;
          const MdsSeamOfsTexTblData *data = &table[texture->unknown9e];
          u32 heightSize = data->unknown0c;
          int alignedSize = calcSemaAlignment(heightSize, 0x1000);
          unknownc34 -= heightSize;
          DrResMdoSeamMemObj *mem = texture->unknown88;
          texture->unknown88 = unknown6e0.createParentFreeObj(mem, alignedSize);
          texture->resetTexture(data->unknown04);
          unknown6e0.releaseFreeObj(mem);
        }
        next = texture->unknown08;
      }
      texture = next;
    }
  }
  DrResMdoSeamTexList *texList = unknown1e8.unknown10.unknown00;
  if (unknowncc8) {
    while (texList != nullptr) {
      DrResMdoSeamTexList *next = texList->unknown08;
      releaseFreeSeamTexList(texList, false);
      texList = next;
    }
    unknownc34 = 0;
  } else {
    while (texList != nullptr) {
      bool isEnd = texList->update(&unknownd30);
      DrResMdoSeamTexList *next = texList->unknown08;
      if (isEnd) {
        const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown94);
        unknownc34 -= table[texList->unknown3c].unknown04;
        releaseFreeSeamTexList(texList, false);
      }
      texList = next;
    }
  }
}

void DrMdoCtlSeam::updateVertexSeam() {
  if (unknowncc8) {
    DrResMdoSeamVertex::SEAMRES_CNTMAX = 10;
    DrResMdoSeamVertex *vertex = unknown220.unknown10.unknown00;
    while (vertex != nullptr) {
      DrResMdoSeamVertex *next = vertex->unknown08;
      releaseFreeSeamVertex(vertex, false);
      vertex = next;
    }
    unknownc38 = 0;
  } else {
    if (unknownd30.unknown40 == 0) {
      DrResMdoSeamVertex::SEAMRES_CNTMAX = 60;
    } else {
      DrResMdoSeamVertex::SEAMRES_CNTMAX = 10;
    }
    DrResMdoSeamVertex *vertex = unknown220.unknown10.unknown00;
    while (vertex != nullptr) {
      if (vertex->update()) {
        DrResMdoSeamVertex *next = vertex->unknown08;
        const unknown136 *table = reinterpret_cast<const unknown136 *>(reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknown54);
        unknownc38 -= table[vertex->unknown2c].unknown04;
        releaseFreeSeamVertex(vertex, false);
        vertex = next;
      } else {
        if (vertex->unknown2e != 0) {
          vertex->changeMemVertex();
        }
        vertex = vertex->unknown08;
      }
    }
  }
}

void DrMdoCtlSeam::releaseFreeSeamVertex(DrResMdoSeamVertex *vertex, bool isAll) {
  if (isAll) {
    vertex->release();
    unknown220.unknown002(vertex);
  } else {
    DrResMdoSeamMemObj *mem = vertex->unknown18;
    unknownbd0[vertex->unknown2c] = 0;
    vertex->release();
    vertex->unknown18 = nullptr;
    unknown220.unknown002(vertex);
    if (mem != nullptr) {
      unknown6e0.releaseFreeObj(mem);
    }
  }
}

DrResMdoSeamMemObj *DrMdoCtlSeam::createFreeSeamMemObj4K(u32 size) {
  u32 alignedSize = calcSemaAlignment(size, 0x1000);
  return unknown6e0.createFreeObj(alignedSize);
}

DrResMdoSeamMemObj *DrMdoCtlSeam::createFreeSeamMemObjBack4K(u32 size) {
  u32 alignedSize = calcSemaAlignment(size, 0x1000);
  return unknown6e0.createBackFreeObj(alignedSize);
}

DrResMdoSeamTexture *DrMdoCtlSeam::createFreeSeamTexture() { return unknown1b0.unknown001(); }

DrResMdoSeamTexList *DrMdoCtlSeam::createFreeSeamTexList() { return unknown1e8.unknown001(); }

DrResMdoSeamVertex *DrMdoCtlSeam::createFreeSeamVertex() { return unknown220.unknown001(); }

DrResMdoSeamColi *DrMdoCtlSeam::createFreeSeamCollision() { return unknown258.unknown001(); }

void DrMdoCtlSeam::releaseFreeSeamCollision(DrResMdoSeamColi *coli, bool isAll) {
  if (isAll) {
    unknown258.unknown002(coli);
  } else {
    DrResMdoSeamMemObj *mem = coli->m_cache;
    unknownbb0[coli->unknown40 >> 5] &= ~(1 << (coli->unknown40 & 0x1f));
    unknownc0a--;
    if ((coli->unknown42 & 0x400) == 0) {
      if ((coli->unknown42 & 0x800) == 0) {
        unknownc30--;
        if (unknownc30 < 0) {
          unknownc30 = 0;
        }
      } else {
        unknownc2e--;
        if (unknownc2e < 0) {
          unknownc2e = 0;
        }
      }
    } else {
      unknownc2f--;
      if (unknownc2f < 0) {
        unknownc2f = 0;
      }
    }
    int size = coli->unknown38;
    coli->release();
    unknown258.unknown002(coli);
    if (mem != nullptr) {
      unknownc3c -= size;
      unknown6e0.releaseFreeObj(mem);
    }
  }
}

void DrMdoCtlSeam::seamZPrePassBegin() {
  unknownf2 = 0;
  unknown001();
  m_drMan->unknown5c0->setupCulling(DR_AP_CULL_TYPE_UNKNOWN_2);
}

void DrMdoCtlSeam::seamZPrePassEnd() {}

void DrMdoCtlSeam::seamThicknessPassBegin(bool isFirst) {
  unknownf2 = 0;
  unknown001();
  if (isFirst) {
    m_drMan->unknown5c0->beginThicknessRenderFirst();
  } else {
    m_drMan->unknown5c0->beginThicknessRenderSecond();
  }
  m_drMan->unknown5c0->setupCulling(isFirst ? DR_AP_CULL_TYPE_UNKNOWN_1 : DR_AP_CULL_TYPE_UNKNOWN_0);
}

void DrMdoCtlSeam::seamThicknessPassEnd(bool value) {}

bool DrMdoCtlSeam::calcNormSeamMapMaterial(u32 *bits) {
  u32 size = (unknown30->unknown30 / 32) * 4 + 4;
  memset(bits, 0, size);
  bool isChanged = false;
  DrResMdoMat *mat = unknown30->unknownc0;
  for (int i = 0; i < unknown30->unknown30; i++, mat++) {
    if (mat->unknown08.a <= 0.0f) {
      if ((mat->unknown1c & 1) != 0) {
        mat->unknown1c &= ~1;
        isChanged = true;
      }
    } else {
      bits[i >> 5] |= 1 << (i & 0x1f);
      if ((mat->unknown1c & 1) == 0) {
        mat->unknown1c |= 1;
        isChanged = true;
      }
    }
  }
  return isChanged;
}

void DrMdoCtlSeam::calcSeamMapRender(int renderType, u32 flags) {
  unknownf4 = renderType;
  unknownf2 = unknown098[renderType];
  beginSetup();
  const DrResMdoMat *mats = unknown30->unknownc0;
  const MdsMdlTopHeader *entry = unknown30->unknown168;
  for (int i = 0; i < unknown30->unknown170; i++, entry++) {
    const MdsMdlInfoHeader *header = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + entry->unknown00);
    int count = entry->unknown04;
    for (int j = 0; j < count; j++, header++) {
      if ((header->unknown04 & flags) != 0 && mats[header->unknown0e].unknown08.a > 0.0f) {
        partsDefRender(header, 0, 0, false);
      }
    }
  }
}

} // namespace ml

// The game builds these files in one unit with this one (0x71007f0d14 to 0x7100836bb4), in this order; this file's own functions (0x7100819e84 to 0x710081c050) sit between dr_mdo_ctl_dammy.cpp and
// dr_mdo_ctl_seam_all.cpp.
// clang-format off
#include "dr_mdo_ctl.cpp"
#include "dr_mdo_ctl_cld_mdl.cpp"
#include "dr_mdo_ctl_mpf.cpp"
#include "dr_mdo_ctl_mpf_auto.cpp"
#include "dr_mdo_ctl_mpf_inst.cpp"
#include "dr_mdo_ctl_mpf_work.cpp"
#include "dr_mdo_ctl_nom.cpp"
#include "dr_mdo_ctl_pos.cpp"
#include "dr_mdo_ctl_dammy.cpp"
#include "dr_mdo_ctl_seam_all.cpp"
#include "dr_mdo_ctl_seam_base_map.cpp"
#include "dr_mdo_ctl_seam_env_map.cpp"
#include "dr_mdo_ctl_seam_inst_map.cpp"
#include "dr_mdo_ctl_seam_light.cpp"
#include "dr_mdo_ctl_seam_low_map.cpp"
#include "dr_mdo_ctl_seam_mpf_map.cpp"
#include "dr_mdo_ctl_seam_read.cpp"
#include "dr_mdo_mat.cpp"
#include "dr_mdo_anim.cpp"
#include "dr_mdo_nom_after_image.cpp"
#include "../util/ml_halton.cpp"
#include "dr_mdo_mpf_man.cpp"
#include "dr_mdo_node.cpp"
#include "dr_mdo_setup.cpp"
#include "dr_mdo_sml_shadow_man.cpp"
#include "dr_mdo_tex_simple_man.cpp"
#include "dr_mdo_texture_man.cpp"
#include "dr_mdo_vertex_man.cpp"
#include "dr_mdo_zsort.cpp"
// clang-format on
