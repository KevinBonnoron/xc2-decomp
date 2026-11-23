#include "dr/dr_mdo_ctl_mpf.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_base.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_ctl_mpf_auto.h"
#include "dr/dr_mdo_ctl_mpf_inst.h"
#include "dr/dr_mdo_ctl_mpf_work.h"
#include "dr/dr_mdo_ctl_nom.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_mdo_mpf_man.h"
#include "dr/dr_mdo_vertex_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_tile_parm.h"
#include "dr/dr_res_mdo_seam_wrk_pos_mpf.h"
#include "dr/dr_res_mdo_sort.h"
#include "mm_math/mm_vec3.h"
#include "mtl/mem_manager.h"

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {

// Inferred role: header of an mpf model resource; original type name unknown.
struct unknown784 {
  u8 _00[0x08];
  u32 unknown08; // Inferred role: model data offset; original member name unknown.
  u32 unknown0c; // Inferred role: material data offset; original member name unknown.
  u8 _10[0x14 - 0x10];
  u32 unknown14; // Inferred role: vertex data offset; original member name unknown.
  u8 _18[0x1c - 0x18];
  u32 unknown1c; // Inferred role: texture data offset, zero when there is none; original member name unknown.
  u8 _20[0x28 - 0x20];
  u32 unknown28; // Inferred role: mpf data offset; original member name unknown.
};

DrMdoCtlMpf::DrMdoCtlMpf(const void *data, const char *path, DrMan *drMan, int viewNum)
    : DrMdlObj(viewNum), unknown1b0(nullptr), unknown1b8(nullptr), unknown1c0(0), m_drMdoCtlMpfWork(nullptr), m_drMdoCtlMpfAuto(nullptr), m_drMdoCtlMpfInst(nullptr), m_drResMdoSeamWrkPosMpf(nullptr),
      m_drResMdoSortMpf(nullptr) {
  unknown1c = unknown037_2;
  drMan->m_drMdlMan->addMpfObj();
  m_drMan = drMan;
  const unknown784 *header = static_cast<const unknown784 *>(data);
  const u8 *bytes = static_cast<const u8 *>(data);
  // The game branches on the texture offset (cbz, 0x71007f834c) and keeps the null for the arm without textures; a ternary argument gives a csel: 42 instructions
  // against the game's 44.
  if (header->unknown1c == 0) {
    initMpfMaterial(bytes + header->unknown0c, bytes + header->unknown14, bytes + header->unknown08, nullptr, false);
  } else {
    initMpfMaterial(bytes + header->unknown0c, bytes + header->unknown14, bytes + header->unknown08, bytes + header->unknown1c, false);
  }
  setupMpf(bytes + header->unknown28);
}

DrMdoCtlMpf::~DrMdoCtlMpf() { releaseMpf(); }

void DrMdoCtlMpf::releaseMpf() {
  m_drMdoCtlMpfAuto->autoMpfRelease();
  m_drMdoCtlMpfAuto->~DrMdoCtlMpfAuto();
  m_drResMdoSortMpf->~DrResMdoSortMpf();
  if (unknown1b0 != nullptr) {
    mtl::MemManager::deallocate(unknown1b0, 0, false);
    unknown1b0 = nullptr;
  }
  if (unknown1b8 != nullptr) {
    mtl::MemManager::deallocate(unknown1b8, 0, false);
    unknown1b8 = nullptr;
  }
  releaseMat();
  m_drMan->m_drMdlMan->delMpfObj();
}

void DrMdoCtlMpf::resourceInit() { setupMpfResource(); }

void DrMdoCtlMpf::update() {
  updateAlphaCall();
  updateMpf();
  if (unknownf8 & unknown028_15) {
    m_drMan->m_drMdlMan->unknown230->unknown00 = true;
  }
  if (unknownf8 & unknown028_16) {
    m_drMan->m_drMdlMan->unknown230->unknown01 = true;
  }
}

void DrMdoCtlMpf::updateMpf() {
  m_AABBMax = mm::Vec3(1.0f, 1.0f, 1.0f);
  m_AABBMin = mm::Vec3(-1.0f, -1.0f, -1.0f);
  m_length = 100000.0f;
  unknownf8 = 0;
  unknown168 = 0;
  m_center = mm::Vec3(0.0f, 0.0f, 0.0f);
  DrMdoMpfMan *mpfMan = m_drMan->m_drMdlMan->m_drMdoMpfMan;
  if (mpfMan != nullptr) {
    mpfMan->unknown3d24 = m_frameSpd;
  }
  calcMpfRenderList();
  updateMpfMatUniformBlock();
}

// The loop repeats DrMdoCtlMpfInst::calcInstMpf (0x71007f9fc4), which the game inlines here (0x71007f9bf8 to 0x71007f9c44). The call form
// `m_drMdoCtlMpfInst->calcInstMpf(view, m_drMdoCtlMpfWork, m_drResMdoSeamWrkPosMpf)` has the same 67 instructions, but LSR biases the loop counter by 28 there (`orr w25, wzr, #0x1c`,
// `ldrh w8, [x1], #-28`) where the game keeps it at zero (`mov x24, xzr`, `ldrh w8, [x1, #28]`, 0x71007f9c28): the use-list order of the counter of the loop cloned by the inliner differs from the one
// of the loop written here (measured: the same loop IR through the backend with the order of the counter's uses changed gives either form). In calcInstMpf, `++i`, `[i++]` and `trees[i]` written twice
// instead of the `tree` local did not change the inlined loop (`[i++]` also broke the standalone function).
void DrMdoCtlMpf::calcMpfRenderList() {
  unknown1a0 = 0;
  m_drMdoCtlMpfWork->beginList();
  DrCalcViewWork *view = m_drMan->m_drCalcMan->m_drCalcViewWork;
  DrMdoMpfMan *mpfMan = m_drMan->m_drMdlMan->m_drMdoMpfMan;
  DrMdoCtlMpfInst *inst = m_drMdoCtlMpfInst;
  DrResMdoSeamWrkPosMpf *pos = m_drResMdoSeamWrkPosMpf;
  if (pos->unknown18 != 0) {
    inst->m_drMdoCtlMpfWork = m_drMdoCtlMpfWork;
    inst->m_drResMdoSeamWrkPosMpf = pos;
    for (int i = 0; i < pos->unknown18; i++) {
      // The game loads the object data (0x71007f9c1c) before the load of the node's object index (0x71007f9c28).
      const MdsMpfObjData *objects = inst->m_mdsMpfObjData;
      const MdsMpfObjTreeData *tree = &inst->m_drResMdoSeamWrkPosMpf->m_mdsMpfObjTreeData[i];
      inst->calcMpfObjTree(tree, view, objects[tree->unknown1c].unknown0c);
    }
  }
  m_drMdoCtlMpfAuto->autoMpfCalc(view->unknown9ab, true, view, m_drMdoCtlMpfWork, mpfMan);
  if (calcMpfMatSetup()) {
    mpfMan->unknown3d30 |= 2;
    m_drMan->m_drMdlMan->unknown230->unknown0c = true;
  }
}

void DrMdoCtlMpf::callZPrepassRender() {
  if ((unknownf8 & unknown028_0) == 0) {
    return;
  }
  defMpfZPreRender();
}

void DrMdoCtlMpf::callRenderMpf() {
  if ((unknownf8 & unknown028_0) == 0) {
    return;
  }
  DrMan::get()->m_drPixlTileParm->begin(DrPixlTileParm::TILE_TYPE_UNKNOWN_3);
  unknownf4 = 0;
  unknownf2 = 0;
  defMpfrender();
  DrMan::get()->m_drPixlTileParm->end(DrPixlTileParm::TILE_TYPE_UNKNOWN_3);
}

void DrMdoCtlMpf::defMpfZPreRender() {
  unknown17a = -1;
  unknownf4 = 0;
  unknownf2 = 0;
  beginSetup();
  grlib::CGLibVtxInstans *instans = m_drMan->m_drMdlMan->m_drMdoVertexMan->unknown10;
  m_drMan->m_drAPCache->setupCulling(DR_AP_CULL_TYPE_UNKNOWN_2);
  for (int i = 0; i < unknown1a4; i++) {
    if (m_drMdoCtlMpfWork->m_wkMpfObjSelect[i].m_objChk == 0) {
      continue;
    }
    // The game takes the row of the object as the flat table plus a 32-bit i * 8 (lsl w8, w21, #3; add x8, x9, w8, sxtw #3, 0x71007faa5c) and loads unknownf4 after
    // it: with the type of unknown190 retyped flat, `unknown190[i * 8 + unknownf4]` gives 73 instructions against the game's 74, so the row stays a local.
    DrResChkList **lists = &unknown190[i * 8];
    DrResChkList *list = lists[unknownf4];
    if (list == nullptr) {
      continue;
    }
    const MdsMdlTopHeader *top = &unknown30->m_mdsMdlTopHeader[i];
    const MdsMdlInfoHeader *infos = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
    while (true) {
      mpfZPrePassRender(i, infos + list->unknown00, m_drMdoCtlMpfWork, instans);
      if (list->unknown02 == 0) {
        break;
      }
      list = &unknown198[list->unknown02 - 1u];
    }
  }
}

void DrMdoCtlMpf::defMpfrender() {
  beginSetup();
  grlib::CGLibVtxInstans *instans = m_drMan->m_drMdlMan->m_drMdoVertexMan->unknown10;
  DrAPCache *cache = m_drMan->m_drAPCache;
  cache->setupCulling(DR_AP_CULL_TYPE_UNKNOWN_2);
  m_drMan->m_drPixlMan->selectGBuffRenderTarget(0x1f);
  cache->setupDepthStencil(0x18, 1, 0, 3);
  cache->setupAlphaBlend(0);
  for (int i = 0; i < unknown1a4; i++) {
    if (m_drMdoCtlMpfWork->m_wkMpfObjSelect[i].m_objChk == 0) {
      continue;
    }
    // Same row address and load order as defMpfZPreRender.
    DrResChkList **lists = &unknown190[i * 8];
    DrResChkList *list = lists[unknownf4];
    if (list == nullptr) {
      continue;
    }
    const MdsMdlTopHeader *top = &unknown30->m_mdsMdlTopHeader[i];
    const MdsMdlInfoHeader *infos = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
    while (true) {
      mpfDrawRender(i, infos + list->unknown00, m_drMdoCtlMpfWork, instans);
      if (list->unknown02 == 0) {
        break;
      }
      list = &unknown198[list->unknown02 - 1u];
    }
  }
  cache->setupAlphaBlend(0);
}

void DrMdoCtlMpf::createDisplaList() {}

} // namespace ml
