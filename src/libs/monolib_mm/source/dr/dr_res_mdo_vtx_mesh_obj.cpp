#include "dr/dr_res_mdo_vtx_mesh_obj.h"

#include <string.h>

#include "dr/dr_ap_cache.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_res_mdo_vertex.h"
#include "dr/dr_res_shd.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_polygon.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_vtx_stm_out.h"
#include "grlib/cglib_vtx_vertex.h"
#include "grlib/shd_util.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

// Inferred role: uniform block of the vertex mesh written by updateUniform (the size 0x130 is given to setup by updateInit); original type name unknown.
// Evidence: updateUniform (0x710087b130) writes the four matrices with ShdMat44TransposeMat34 (twelve floats each) at 0x10, 0x40, 0x70 and 0xa0, unknownd0 (the render count less one, sub w8 at
// 0x710087b5cc) as an integer, unknownd4 as a copy of the u32 unknown84, and the other members as floats.
struct unknown001 {
  f32 unknown00;
  f32 unknown04;
  f32 unknown08;
  f32 unknown0c;
  f32 unknown10[12];
  f32 unknown40[12];
  f32 unknown70[12];
  f32 unknowna0[12];
  s32 unknownd0;
  u32 unknownd4;
  f32 unknownd8;
  f32 unknowndc;
  f32 unknowne0;
  f32 unknowne4;
  f32 unknowne8;
  f32 unknownec;
  f32 unknownf0;
  f32 unknownf4;
  f32 unknownf8;
  f32 unknownfc;
  f32 unknown100;
  f32 unknown104;
  f32 unknown108;
  f32 unknown10c;
  f32 unknown110;
  f32 unknown114;
  f32 unknown118;
  f32 unknown11c;
  f32 unknown120;
  f32 unknown124;
  f32 unknown128;
  f32 unknown12c;
};

static_assert(offsetof(unknown001, unknown10) == 0x10, "");
static_assert(offsetof(unknown001, unknown40) == 0x40, "");
static_assert(offsetof(unknown001, unknown70) == 0x70, "");
static_assert(offsetof(unknown001, unknowna0) == 0xa0, "");
static_assert(offsetof(unknown001, unknownd0) == 0xd0, "");
static_assert(offsetof(unknown001, unknownd4) == 0xd4, "");
static_assert(offsetof(unknown001, unknownd8) == 0xd8, "");
static_assert(offsetof(unknown001, unknownec) == 0xec, "");
static_assert(offsetof(unknown001, unknownf0) == 0xf0, "");
static_assert(offsetof(unknown001, unknown100) == 0x100, "");
static_assert(offsetof(unknown001, unknown110) == 0x110, "");
static_assert(offsetof(unknown001, unknown120) == 0x120, "");
static_assert(offsetof(unknown001, unknown12c) == 0x12c, "");
static_assert(sizeof(unknown001) == 0x130, "");

// The statement order is the one found to match: neither the order of the members nor the store order of the game (0x710087ab80) gives the
// game's bytes. unknown84 is stored twice because the game's 64-bit zero store at 0x80 covers it before the 40000 store.
DrResMdoVtxMeshObj::DrResMdoVtxMeshObj() {
  unknown98 = 0.0f;
  unknown94 = 0;
  unknowne0.y = 1.0f;
  unknowne0.z = 0.0f;
  unknownf0.y = 1.0f;
  unknown100 = 1.0f;
  unknownf0.z = 0.0f;
  unknown104 = 60.0f;
  unknown110 = 30;
  unknown8c = 0;
  unknown88 = 0;
  unknown80 = 0;
  unknown84 = 0;
  unknown108 = 1.2f;
  unknown10c = -0.05f;
  unknown114.r = 0.18f;
  unknown90 = 0;
  unknownf0.x = 0.0f;
  unknown114.g = 0.12f;
  unknown114.b = 0.09f;
  unknown12c = 1.0f;
  unknown120 = 0.998f;
  unknown124 = 0.3f;
  unknown78 = nullptr;
  unknown128 = 0.6f;
  unknowne0.x = 0.0f;
  unknown130 = 1.0f;
  unknown74 = 0;
  unknown70 = false;
  unknown84 = 40000;
}

void DrResMdoVtxMeshObj::updateInit(const mm::Mat44 &matrix) {
  u32 flags = unknown74;
  u32 startBit = 0x10000 << DrMan::s_nDblIdx;
  if (flags & startBit) {
    flags &= ~startBit;
    unknown74 = flags;
    unknown70 = true;
  }
  u32 stopBit = 0x40000 << DrMan::s_nDblIdx;
  bool isStop = (flags & stopBit) != 0;
  if (isStop) {
    flags &= ~stopBit;
    unknown74 = flags;
    unknown70 = false;
  }
  if (!isStop && unknown70 && unknown130 > 0.01f) {
    unknown74 = (unknown74 & ~0xd) | 1;
  } else if (unknown74 & 1) {
    unknown74 |= 8;
    if (unknown74 & 4) {
      unknown74 &= ~1;
    }
  }
  if (!(unknown74 & 1)) {
    if (unknown74 & 2) {
      releaseWork();
    }
    unknown74 &= ~0xf;
  } else if (!(unknown74 & 2)) {
    unknown10.setup(unknown84 << 5);
    unknown10.updateData();
    m_cGLibDblUniformBlock.setup(0x130);
    unknown78 = mtl::MemManager::allocate(DrMan::get()->unknown14, static_cast<size_t>(unknown84) << 3, 4, false, "no name", 0);
    unknown74 |= 2;
    memcpy(&unknowna0, &matrix, sizeof(mm::Mat44));
  }
}

DrResMdoVtxMeshObj::~DrResMdoVtxMeshObj() { releaseWork(); }

void DrResMdoVtxMeshObj::setActive(bool isActive, u32 index) {
  if (isActive) {
    if (!unknown70) {
      unknown74 |= 0x10000 << DrMan::s_nDblStockIdx;
      unknown74 &= ~(0x40000 << DrMan::s_nDblIdx);
      unknown84 = index;
    }
  } else {
    unknown74 |= 0x40000 << DrMan::s_nDblStockIdx;
    unknown74 &= ~(0x10000 << DrMan::s_nDblIdx);
  }
}

void DrResMdoVtxMeshObj::update(const mm::Mat44 &matrix, f32 param2, f32 param3) {
  updateInit(matrix);
  if ((unknown74 & 1) && unknown80 != 0) {
    updateCount(param3);
    updateUniform(matrix, param2, param3);
    memcpy(&unknowna0, &matrix, sizeof(mm::Mat44));
  }
}

void DrResMdoVtxMeshObj::updateUniform(const mm::Mat44 &matrix, f32 param2, f32 param3) {
  DrCalcViewWork *view = DrMan::get()->m_drCalcMan->m_drCalcViewWork;
  unknown001 *uniform = static_cast<unknown001 *>(m_cGLibDblUniformBlock.getBuff());
  uniform->unknown00 = unknown12c * 0.002f;
  uniform->unknown04 = 0.5f;
  uniform->unknown08 = unknown130;
  uniform->unknown0c = view->unknown180.rows[2][2];
  grlib::ShdMat44TransposeMat34(uniform->unknown10, matrix);
  grlib::ShdMat44TransposeMat34(uniform->unknown40, view->unknown00);
  grlib::ShdMat44TransposeMat34(uniform->unknown70, unknowna0);
  // The game computes the destination address (add x22, x21, #0xa0 at 0x710087b2e8) before the inverse and keeps it in a callee-saved register across the assert call.
  f32 *inverseUniform = uniform->unknowna0;
  mm::Mat44 inverse;
  inverse.unknown014(view->unknown280);
  grlib::ShdMat44TransposeMat34(inverseUniform, inverse);
  f32 scale = param2 * 0.2f * 0.033333335f;
  if (unknown94 == 0) {
    uniform->unknownd0 = 0;
    uniform->unknownd4 = 0;
  } else {
    uniform->unknownd0 = unknown94 - 1;
    uniform->unknownd4 = unknown84;
  }
  uniform->unknowne8 = 0.0f;
  uniform->unknownd8 = 0.0f;
  uniform->unknowndc = 0.0f;
  uniform->unknowne0 = 0.0f;
  uniform->unknowne4 = 0.0f;
  uniform->unknownec = 1.0f / unknown104 * param3;
  f32 velocity = scale * unknown10c * param3 * 0.1f;
  uniform->unknownf0 = unknownf0.x * velocity;
  uniform->unknownf4 = unknownf0.y * velocity;
  uniform->unknownf8 = velocity * unknownf0.z;
  uniform->unknownfc = unknown120 * param3;
  uniform->unknown100 = unknown128;
  uniform->unknown104 = param2 * -0.01f;
  uniform->unknown108 = param2 * 0.01f;
  uniform->unknown10c = 0.0f;
  uniform->unknown110 = unknown114.r;
  uniform->unknown114 = unknown114.g;
  uniform->unknown118 = unknown114.b;
  uniform->unknown11c = 1.0f;
  f32 ratio = (1.0f - unknown124) * unknown108;
  uniform->unknown120 = ratio * (scale * unknowne0.x);
  uniform->unknown124 = ratio * (scale * unknowne0.y);
  uniform->unknown128 = ratio * (scale * unknowne0.z);
  uniform->unknown12c = scale * unknown108 * unknown124;
  m_cGLibDblUniformBlock.updateData();
}

void DrResMdoVtxMeshObj::release(DrResMdoVtxMeshObj *&obj) {
  if (obj != nullptr) {
    obj->~DrResMdoVtxMeshObj();
    obj = nullptr;
  }
}

void DrResMdoVtxMeshObj::resourceInit(DrResMdoVertex *vertex) {
  unknown056 *uniformVertex = vertex->unknown70;
  unknown00 = uniformVertex->unknown00;
  unknown08 = uniformVertex->unknown08;
  unknown80 = unknown00->unknown08;
}

void DrResMdoVtxMeshObj::releaseWork() {
  unknown10.release();
  m_cGLibDblUniformBlock.release();
  if (unknown78 != nullptr) {
    mtl::MemManager::deallocate(unknown78, 0, false);
    unknown78 = nullptr;
  }
}

bool DrResMdoVtxMeshObj::isRender() const {
  if (!(unknown74 & 1)) {
    return false;
  }
  if (unknown8c == 0 && unknown94 == 0) {
    return false;
  }
  return true;
}

void DrResMdoVtxMeshObj::stmRender(bool isNode) {
  if (!isRender()) {
    return;
  }
  DrShdDataList *list = DrMan::getIns()->m_drShdMan->m_drShdDataList;
  DrResShdStreamOut *stmOut = list->getStmOutObj(7);
  grlib::CGLibPolygon::setRasterizer(1);
  u32 count = unknown80 < unknown110 ? unknown80 : unknown110;
  if (unknown94 != 0) {
    unknown94 = 0;
    // The game loads the shader once for the two declaration calls (0x710087b794), before it computes the mode, and loads it again for setupShader.
    DrShdDataObj *shader = stmOut->m_drShdDataObj;
    u32 mode = 1;
    if (isNode) {
      mode = 2;
    }
    shader->setDeclarationIdx(shader->getDeclarationOfs("CALC_MODE"), mode);
    stmOut->m_drShdDataObj->setupShader(0u);
    if (isNode) {
      list->unknown958.setStorageBuffer(1);
      list->unknown980.setStorageBuffer(2);
    }
    unknown08->setUniformBlock(stmOut->unknown08[1]);
    m_cGLibDblUniformBlock.setUniformBlock(stmOut->unknown08[0]);
    // The game takes the head count before the first call (sub at 0x710087b820); written inline the function has 185 instructions instead of 194.
    if (unknown90 + count > unknown80) {
      u32 headCount = unknown80 - unknown90;
      unknown10.setStorageBuffer(0);
      grlib::CGLibCtlVertex::setVertex(*unknown00, unknown00->unknown04 * unknown90);
      grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, headCount);
      u32 tailCount = unknown90 + count - unknown80;
      unknown10.setStorageBuffer(0);
      grlib::CGLibCtlVertex::setVertex(*unknown00);
      grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, tailCount);
    } else {
      unknown10.setStorageBuffer(0);
      grlib::CGLibCtlVertex::setVertex(*unknown00, unknown00->unknown04 * unknown90);
      grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, count);
    }
    unknown90 = (unknown90 + count) % unknown80;
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
  }
  if (unknown8c != 0) {
    DrShdDataObj *shader = stmOut->m_drShdDataObj;
    shader->setDeclarationIdx(shader->getDeclarationOfs("CALC_MODE"), 3);
    stmOut->m_drShdDataObj->setupShader(1u);
    m_cGLibDblUniformBlock.setUniformBlock(stmOut->unknown08[0]);
    if (unknown88 + unknown8c > unknown84) {
      u32 headLength = unknown84 - unknown88;
      unknown10.setStorageBuffer(0, unknown88 << 5, headLength << 5);
      grlib::CGLibCtlVertex::setUniformVertex(unknown10, 0x20, unknown88 << 5, 0, 0);
      grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, headLength);
      u32 tailLength = unknown88 + unknown8c - unknown84;
      unknown10.setStorageBuffer(0);
      grlib::CGLibCtlVertex::setUniformVertex(unknown10, 0x20, 0, 0, 0);
      grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, tailLength);
    } else {
      unknown10.setStorageBuffer(0, unknown88 << 5, unknown8c << 5);
      grlib::CGLibCtlVertex::setUniformVertex(unknown10, 0x20, unknown88 << 5, 0, 0);
      grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, unknown8c);
    }
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
  }
  grlib::CGLibPolygon::setRasterizer(0);
}

void DrResMdoVtxMeshObj::alpRender() {
  if (!(unknown74 & 1) || unknown8c == 0) {
    return;
  }
  DrAPCache *cache = DrMan::get()->m_drAPCache;
  DrShdDataList *list = DrMan::get()->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = list->getPostShdObj(0x3f);
  cache->setupCulling(DR_AP_CULL_TYPE_UNKNOWN_2);
  cache->setupDepthStencil(0, 0, 0, 2);
  cache->setupAlphaBlend(2);
  DrMan::get()->m_drPixlMan->selectGBuffRenderTarget(0xc0u);
  list->bindShdEffVtx();
  shader->setupShader(0u);
  // The game keeps the view work in a callee-saved register and takes the address of its uniform block (add at 0x710087bb24) after the offset lookup, as does DrGpuCheckRender::render.
  DrCalcViewWork *view = DrMan::get()->m_drCalcMan->m_drCalcViewWork;
  u32 staticOfs = (shader->unknown38 + shader->unknown58)->getUniformBlockOfs("U_Static");
  view->unknown7b0.setUniformBlock(staticOfs);
  u32 pamOfs = (shader->unknown38 + shader->unknown58)->getUniformBlockOfs("U_Pam");
  m_cGLibDblUniformBlock.setUniformBlock(pamOfs);
  if (unknown88 + unknown8c > unknown84) {
    // The game takes the head count before the first call (sub at 0x710087bb7c); written inline the function has 103 instructions instead of 109.
    u32 headCount = unknown84 - unknown88;
    grlib::CGLibCtlVertex::setUniformVertex(unknown10, 0x20, unknown88 << 5, 1, 1);
    list->renderEffVtx(headCount);
    u32 tailCount = unknown88 + unknown8c - unknown84;
    grlib::CGLibCtlVertex::setUniformVertex(unknown10, 0x20, 0, 1, 1);
    list->renderEffVtx(tailCount);
  } else {
    grlib::CGLibCtlVertex::setUniformVertex(unknown10, 0x20, unknown88 << 5, 1, 1);
    list->renderEffVtx(unknown8c);
  }
}

u32 DrResMdoVtxMeshObj::setup(const u8 *, u8 *) { return 0x140; }

u32 DrResMdoVtxMeshObj::calcWorkSize(const u8 *) { return 0x140; }

} // namespace ml
