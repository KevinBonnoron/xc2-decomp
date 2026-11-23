#include "dr/dr_mdo_ctl_seam_inst_map.h"

#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_cache_obj.h"
#include "dr/dr_res_mdo_mat.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_parm_read.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "dr/dr_res_mdo_seam_wrk_inst.h"
#include "dr/dr_res_mdo_vertex.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"

namespace ml {

DrMdoCtlSeamInstMap::DrMdoCtlSeamInstMap(int viewNum) : DrMdoCtlSeamLowMap(viewNum) {}

void DrMdoCtlSeamInstMap::changeMemInstMapParts(DrResMdoSeamWrkInst *inst) {
  MdoWrkMatRes *matRes = inst->m_mdoWrkMatRes;
  const u8 *data = inst->m_drResMdoSeamMemObj->m_buffer;
  const MdsSeamInstMapHead *head = reinterpret_cast<const MdsSeamInstMapHead *>(data);
  unknown30 = matRes;
  resetInstMapMaterial(matRes, data + head->unknown10, data + head->unknown0c, data + head->unknown44, nullptr, head->unknown24);
  if (head->unknown14 != 0) {
    changeMemFixAnim(matRes, data + head->unknown14);
  }
}

void DrMdoCtlSeamInstMap::releaseInstMap() {
  DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00;
  while (inst != nullptr) {
    DrResMdoSeamWrkInst *next = inst->unknown08;
    releaseFreeSeamInst(inst);
    inst = next;
  }
}

DrResMdoSeamWrkInst *DrMdoCtlSeamInstMap::createFreeSeamInst() { return unknown300.unknown001(); }

void DrMdoCtlSeamInstMap::releaseFreeSeamInst(DrResMdoSeamWrkInst *inst) {
  DrResMdoSeamMemObj *mem = nullptr;
  if (inst->m_mdoWrkMatRes != nullptr) {
    mem = inst->m_drResMdoSeamMemObj;
    unknownb80[inst->unknown68 >> 5] &= ~(1 << (inst->unknown68 & 0x1f));
    unknownc48 -= inst->unknown84;
    releaseInstMapSeamMat(inst->m_mdoWrkMatRes);
    inst->releaseCache(this);
    unknownc04--;
  }
  unknown300.unknown002(inst);
  if (mem != nullptr) {
    inst->m_drResMdoSeamMemObj = nullptr;
    m_drResMdoSeamMemMan.releaseFreeObj(mem);
  }
}

void DrMdoCtlSeamInstMap::callRenderSeamInstMap() { renderSeamInstMap(0); }

void DrMdoCtlSeamInstMap::callGBuffRenderSeamInstMap() { renderSeamInstMap(1); }

void DrMdoCtlSeamInstMap::callLightPrePassRenderSeamInstMap() { renderSeamInstMap(3); }

void DrMdoCtlSeamInstMap::callRefractionRenderSeamInstMap() { renderSeamInstMap(2); }

void DrMdoCtlSeamInstMap::callAlphaRenderSeamInstMap() { renderSeamInstMap(4); }

void DrMdoCtlSeamInstMap::callSpAlphaRenderSeamInstMap() { renderSeamInstMap(5); }

void DrMdoCtlSeamInstMap::createInstRenderDisplayList(const MdsMdlInfoHeader *, int, DrResMdoSeamWrkInst *, _MdoInstanceWork *, grlib::CGLibVtxInstans *, int) {}

void DrMdoCtlSeamInstMap::beginResAll(MdoWrkMatRes *matRes) {
  MdoWrkMatRes *prev = unknown30;
  unknown30 = matRes;
  unknownb38 = prev;
}

void DrMdoCtlSeamInstMap::endResAll() { unknown30 = unknownb38; }

void DrMdoCtlSeamInstMap::updateInstMap(MdoArgSeamUpdate &arg) {
  readInstMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateInstMapRenderList(arg);
    createInstMapDisplayList();
  }
}

// The game inlines DrMdoMat::updateMatFstCallBack and DrMdoSetup::updateUniformBlock here (both defined in this unit, dr_mdo_mat.cpp and dr_mdo_setup.cpp) and calls updateMatCallBack,
// updateAnim and updateTimerCalc. The counter test leaves the function on `x < 2` (cmp w10, #2 at 0x7100823aec, b.lo at 0x7100823af0); the nested `x >= 2` and `x > 1` forms are
// not the same code (tried).
void DrMdoCtlSeamInstMap::updateInstMapRenderList(MdoArgSeamUpdate &arg) {
  arg.m_drMdoCtlSeamInstMap = this;
  for (DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00; inst != nullptr; inst = inst->unknown08) {
    unknown30 = inst->m_mdoWrkMatRes;
    if (unknown30 != nullptr) {
      if (inst->updateRenderList(arg)) {
        unknownc54 += inst->unknown144;
        unknownc58 += inst->unknown148;
        updateMatFstCallBack();
        updateMatCallBack(inst->unknowna0);
        updateAnim(m_frameSpd * m_drMan->unknown1c8c, inst->unknowna0, nullptr);
        updateTimerCalc(inst->unknowna0);
        updateUniformBlock(inst->unknowna0);
      }
      if (inst->unknown152 != 0 && m_drMan->unknown1cc2) {
        unknownc7c |= 5;
      }
      if ((unknownc7c & 0x88000) == 0 && inst->unknown70 != 0) {
        m_drResMdoSeamParmRead.setStockInstMap(inst->unknown70 - 1, inst);
      }
      if (inst->unknown154 != 0 || (inst->unknown8a & 0x80) != 0) {
        unknownc7c |= 0x4000;
      }
    }
  }
  unknownca4++;
  if (unknownca4 < 2) {
    return;
  }
  if ((unknownc98 & (1ull << unknownca6)) == 0 && unknown1a == 0) {
    m_drMan->m_drPixlMan->m_drPixlShadowCacheMan->callSelectShadowCacheUpdate(1ull << unknownca6);
  }
  unknownca6++;
  if (unknownca6 >= 0x24) {
    unknownca6 = 0;
  }
  unknownca4 = 0;
}

void DrMdoCtlSeamInstMap::callShadowCacheInstUpdate(u64 flags) {
  unknownc98 &= ~flags;
  for (DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00; inst != nullptr; inst = inst->unknown08) {
    if (inst->m_mdoWrkMatRes != nullptr) {
      inst->callShadowCacheInstUpdate(flags);
    }
  }
}

void DrMdoCtlSeamInstMap::occInstRender() {
  if (!m_drMan->unknown1d6a) {
    for (DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00; inst != nullptr; inst = inst->unknown08) {
      unknown30 = inst->m_mdoWrkMatRes;
      if (unknown30 != nullptr) {
        inst->occRender();
      }
    }
  }
}

// Measured forms (1.0.0: 0x710081d8c4, 126 instructions), each checked against the game's code:
// - The billboard condition `flag 4 && info->unknown04 != 0 && pass flag 0 && !flag 17` is the only one of the 24 orders of its four terms that matches: five more orders keep 126
//   instructions with the tbz #0 test moved before the tbnz #0x11 or tbz #4 test, the others give 127 to 131 (the game tests tbz #4, tbnz #0x11, tbz #0 on the loaded words, then loads
//   info->unknown04). [INFERENCE] clang merges two adjacent header flag tests into one mask compare; the load of info->unknown04 between them stops it.
// - `arg.unknown20 = false;` before the conditional `true` is the game's `strb wzr, [sp, #0x28]` before `ldrb w9, [x21, #8]` (0x710081d984); `arg.unknown20 = info->unknown08 & 1;`
//   gives 125 instructions without that store. The byte load is how clang narrows the 16-bit read of unknown08.
// - The header count is read before arg.unknown00 (`ldp w10, w26, [x8]` before `ldr x8, [x9, #0x18]`, 0x710081d9f8); reading it after gives 127 instructions. The loop counts up to it
//   and advances arg.unknown00 (0x710081da74).
// - `m_mdsMdlTopHeader + index` and `m_materialRes + index` (pointer plus) give the game's order of loads (table pointer before the index, as dr_mdo_ctl_pos.cpp); the subscript form changes it.
void DrMdoCtlSeamInstMap::createInstZPrePassDisplayList() {
  if ((unknownc7c & 4) && !m_drMan->unknown1d6a) {
    MdoInstancePrePassArg arg;
    arg.unknown0c = 0x34;
    for (DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00; inst != nullptr; inst = inst->unknown08) {
      unknown30 = inst->m_mdoWrkMatRes;
      if (unknown30 != nullptr && inst->unknown152 != 0 && (inst->unknown8a & 0x10)) {
        inst->beginMdl();
        while (DrResMdoSeamWrkInst::unknown002 *info = inst->getMdlInfo()) {
          int count = info->unknown00 - info->unknown02;
          if (count != 0) {
            if (info->unknown0e == 0xffff) {
              unknown30->m_drResMdoVertex = inst->m_drResMdoVertex;
            } else {
              unknown30->m_drResMdoVertex = unknown220.unknown20[unknownbd0[info->unknown0e] - 1u].m_drResMdoVertex;
            }
            arg.unknown20 = false;
            if (info->unknown08 & 1) {
              arg.unknown20 = true;
            }
            arg.unknown08 = info->unknown14 + info->unknown02 * 0x34;
            arg.unknown10 = count - info->unknown04;
            arg.unknown14 = info->unknown04;
            arg.unknown18 = info->unknown06;
            unknown17c = 0xffff;
            unknown17e = 0xffff;
            unknown179 = false;
            unknown178 |= 0x10;
            unknown30->m_drResMdoVertex->beginVertexSetup();
            const MdsMdlTopHeader *top = unknown30->m_mdsMdlTopHeader + info->unknown0c;
            int headerCount = top->unknown04;
            arg.m_mdsMdlInfoHeader = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
            for (int i = 0; i < headerCount; i++, arg.m_mdsMdlInfoHeader++) {
              if ((unknown30->m_materialRes + arg.m_mdsMdlInfoHeader->unknown0e)->unknown08.a > 0.0f && !(arg.m_mdsMdlInfoHeader->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_15)) {
                if (!(arg.m_mdsMdlInfoHeader->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_14)) {
                  if ((arg.m_mdsMdlInfoHeader->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_4) && info->unknown04 != 0 && (arg.m_mdsMdlInfoHeader->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_0) &&
                      !(arg.m_mdsMdlInfoHeader->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17)) {
                    partsInstanceZPrepassBillRender(arg);
                  }
                } else if (!(arg.m_mdsMdlInfoHeader->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17)) {
                  partsInstanceZPrepassRender(arg);
                }
              }
            }
          }
        }
      }
    }
  }
}

// Measured forms (1.0.0: 0x710081e3f4, 111 instructions): the same loop as createInstZPrePassDisplayList for the thickness pass. `count` is a local because the game keeps the
// instance count of the mdl info in a register for the test and for arg.unknown10 (ldrh w28); the two flag bits of unknown8a are tested as one mask compare (0x110).
void DrMdoCtlSeamInstMap::createInstThicknessPassDisplayList(bool isFirst) {
  if (!m_drMan->unknown1d6a) {
    MdoInstancePrePassArg arg;
    arg.unknown0c = 0x34;
    arg.unknown21 = isFirst;
    for (DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00; inst != nullptr; inst = inst->unknown08) {
      unknown30 = inst->m_mdoWrkMatRes;
      if (unknown30 != nullptr && (inst->unknown8a & 0x110) == 0x110) {
        inst->beginMdl();
        while (DrResMdoSeamWrkInst::unknown002 *info = inst->getMdlInfo()) {
          int count = info->unknown00;
          if (count != 0) {
            if (info->unknown0e == 0xffff) {
              unknown30->m_drResMdoVertex = inst->m_drResMdoVertex;
            } else {
              unknown30->m_drResMdoVertex = unknown220.unknown20[unknownbd0[info->unknown0e] - 1u].m_drResMdoVertex;
            }
            arg.unknown20 = false;
            unknown17c = 0xffff;
            unknown17e = 0xffff;
            unknown179 = false;
            unknown178 |= 0x10;
            unknown30->m_drResMdoVertex->beginVertexSetup();
            const MdsMdlTopHeader *top = unknown30->m_mdsMdlTopHeader + info->unknown0c;
            int headerCount = top->unknown04;
            arg.m_mdsMdlInfoHeader = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
            arg.unknown08 = info->unknown14;
            arg.unknown10 = count;
            arg.unknown14 = 0;
            arg.unknown18 = 0;
            for (int i = 0; i < headerCount; i++, arg.m_mdsMdlInfoHeader++) {
              if ((unknown30->m_materialRes + arg.m_mdsMdlInfoHeader->unknown0e)->unknown08.a > 0.0f && (arg.m_mdsMdlInfoHeader->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_15) &&
                  (arg.m_mdsMdlInfoHeader->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_14) && !(arg.m_mdsMdlInfoHeader->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17)) {
                partsInstanceThicknessRender(arg);
              }
            }
          }
        }
      }
    }
  }
}

void DrMdoCtlSeamInstMap::callShadowMapRenderSeamInstMap(DrPixlShadowObj *shadow) {
  if (!m_drMan->unknown1d6a) {
    changeSeamMatInfo();
    for (DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00; inst != nullptr; inst = inst->unknown08) {
      unknown30 = inst->m_mdoWrkMatRes;
      if (unknown30 != nullptr && (inst->unknown8a & 0x10) != 0) {
        inst->seachDefShadowInstMapRender(shadow, this);
      }
    }
  }
}

void DrMdoCtlSeamInstMap::renderInstShadowCacheRender(DrResMdoSeamWrkInst *inst, const mm::Mat44 &matrix, u32 index, const MdsMdlTopHeader *top) {
  if (index == 0xffff) {
    unknown30->m_drResMdoVertex = inst->m_drResMdoVertex;
  } else {
    // The game loads the halfword, subtracts in 32 bits (sub w9, w9, #1 at 0x7100824310) and zero-extends the result in umaddl (0x7100824318).
    // `unknownbd0[index] - 1` (a signed int) gives 51 instructions against the game's 52; `static_cast<u32>(unknownbd0[index]) - 1` matches too.
    unknown30->m_drResMdoVertex = unknown220.unknown20[unknownbd0[index] - 1u].m_drResMdoVertex;
  }
  unknown30->m_drResMdoVertex->beginVertexSetup();
  grlib::CGLibEtcUniformBlock uniform;
  grlib::ShdMat44TransposeMat44(reinterpret_cast<f32 *>(uniform.getBuff()), matrix);
  uniform.updateData(sizeof(mm::Mat44));
  unknown170 = &uniform;
  unknown178 |= 2;
  partsPosShadowRender(top);
  partsPosNukiShadowRender(top);
}

void DrMdoCtlSeamInstMap::callInstShadowCacheRender(DrPixlShadowCacheObj &cache) {
  if ((unknownc98 & cache.unknown8e8) != 0 || m_drMan->unknown1d6a) {
    return;
  }
  changeSeamMatInfo();
  bool isRetry = false;
  for (DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00; inst != nullptr; inst = inst->unknown08) {
    unknown30 = inst->m_mdoWrkMatRes;
    if (unknown30 != nullptr) {
      if (inst->unknown8a & 0x10) {
        isRetry |= inst->seachShadowInstMapRender(cache, this);
      } else {
        isRetry = true;
      }
    }
  }
  if (isRetry) {
    unknownc98 &= ~cache.unknown8e8;
  } else {
    unknownc98 |= cache.unknown8e8;
  }
}

// Measured forms (1.0.0: 0x7100823b60, 121 instructions): the pass flags of every mdl info are merged into unknownf8 one test at a time; the first chain also leaves a flag
// (`isAlpha`: the pass flag 1 or 6 selected unknown028_4 or unknown028_5) that picks unknown028_16 (alpha bloom) instead of unknown028_15 (bloom) for the mdl info flag 3.
void DrMdoCtlSeamInstMap::createInstMapDisplayList() {
  for (DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00; inst != nullptr; inst = inst->unknown08) {
    unknown30 = inst->m_mdoWrkMatRes;
    if (unknown30 != nullptr && inst->unknown74 != 0 && (inst->unknown8a & 0x10)) {
      inst->beginMdl();
      while (DrResMdoSeamWrkInst::unknown002 *info = inst->getMdlInfo()) {
        const MdsMdlTopHeader *top = unknown30->m_mdsMdlTopHeader + info->unknown0c;
        int count = top->unknown04;
        const MdsMdlInfoHeader *header = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
        for (int i = 0; i < count; i++, header++) {
          const MdsMatInfoHeader *mat = unknown30->unknown28 + header->unknown0e;
          bool isAlpha = false;
          if (header->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_0) {
            unknownf8 |= unknown028_0;
            if (header->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_15) {
              unknownf8 |= unknown028_6;
              inst->unknown8a |= 0x100;
            }
            if (header->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_1) {
              unknownf8 |= unknown028_4;
              isAlpha = true;
            }
          } else if (header->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_1) {
            unknownf8 |= unknown028_4;
            isAlpha = true;
          } else if (header->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_6) {
            unknownf8 |= unknown028_5;
            isAlpha = true;
          }
          if (header->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_3) {
            unknownf8 |= unknown028_1;
          }
          if (header->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_2) {
            unknownf8 |= unknown028_2;
          }
          if (header->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_5) {
            unknownf8 |= unknown028_3;
          }
          if (header->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_3) {
            if (isAlpha) {
              unknownf8 |= unknown028_16;
            } else {
              unknownf8 |= unknown028_15;
            }
          }
          if (header->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_25) {
            unknownf8 |= unknown028_18;
          }
          if (mat->unknown08 & MdsMatInfoHeader::unknown030_14) {
            unknownf8 |= unknown028_19;
          }
          if (mat->unknown04 & MdsMatInfoHeader::unknown015_23) {
            if (header->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_6) {
              unknownf8 |= unknown028_9;
            } else {
              unknownf8 |= unknown028_8;
            }
          }
        }
      }
    }
  }
}

} // namespace ml
