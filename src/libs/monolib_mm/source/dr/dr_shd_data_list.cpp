#include "dr/dr_shd_data_list.h"

#include <math.h>
#include <new>
#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_res_shd.h"
#include "dr/dr_shd_data_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_shd_list.h"
#include "ml/file_res_th.h"
#include "ml/scn.h"
#include "ml/work_util.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

const char *SHDLIST_SHADER_FILE = "/monolib/shader/shd_post.wishp";

void DrShdDataObj::createShader(DrShdDataList *list, int type, int index) {
  if (type == 2) {
    return;
  }
  unknown68[0] = &list->m_fetchShader[index];
  u8 next = DrShdDataList::s_etcNextVertex[index];
  unknown68[1] = next == 0xff ? nullptr : &list->m_fetchShader[next];
}

DrShdDataList::DrShdDataList(DrMan *drMan) : m_fileResTh(nullptr), m_drMan(drMan), unknown10(nullptr), m_mpfObj(nullptr) {
  memset(unknown18, 0, sizeof(unknown18));
  unknown618 = new (m_drMan->unknown0c) grlib::CGLibShdListBase<DrShdDataObj>();
  createWork();
  createShader();
}

DrShdDataList::~DrShdDataList() {
  releaseShader();
  for (int i = 0; i < 12; i++) {
    unknown638[i].release();
  }
  for (int i = 0; i < 8; i++) {
    unknown818[i].release();
  }
  unknown958.release();
  unknown980.release();
  for (int i = 0; i < 91; i++) {
    m_fetchShader[i].clearWork();
  }
  unknown9a8.unknown001();
  if (unknown618 != nullptr) {
    delete unknown618;
    unknown618 = nullptr;
  }
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// Role: the record of a shader group in the header of a shader pack (number of shaders, index of the first). Its only user is DrShdDataList::createShader (1.0.0: 0x710089b13c, 282
// instructions), which only matches with the group lookup (zero extended group index) as an inlined call: the group table is then indexed with the plain 64 bit counter and the store
// of unknown18[i] keeps the sign extended one (lsl x16, x8, #32; add x16, x19, x16, asr #29 at 0x710089b260). Forms tried without the helper, in createShader: the lookup written out in
// the loop with `static_cast<u32>(i)` 282 instructions (plain `add x16, x19, x8, lsl #3` store of unknown18[i]), with the signed `i` 281, the object taken through
// CGLibShdListBase::unknown004(i) 282 (same store), `unknown18[i]` read back as the object 282, and the object address formed again from the group in the loop 286.
inline const grlib::CGLibShdListBase<DrShdDataObj>::unknown003 *getShaderGroup(grlib::CGLibShdListBase<DrShdDataObj> *list, u32 group) {
  typedef grlib::CGLibShdListBase<DrShdDataObj> ShaderList;
  return reinterpret_cast<const ShaderList::unknown003 *>(static_cast<const u8 *>(list->unknown08) + static_cast<const ShaderList::unknown001 *>(list->unknown08)->unknown10) + group;
}

// ml::DrShdDataList::createShader() 0x710089b13c.
void DrShdDataList::createShader() {
  typedef grlib::CGLibShdListBase<DrShdDataObj> ShaderList;
  Scn *scn = Scn::get();
  if (scn != nullptr) {
    m_fileResTh = scn->allocEntryRes(SHDLIST_SHADER_FILE);
  }
  if (m_fileResTh == nullptr) {
    m_fileResTh = new (WorkUtil::getWorkMem()) FileResTh();
    m_fileResTh->loadBlock(m_drMan->unknown1c, SHDLIST_SHADER_FILE, 0x1000, 0);
  }
  unknown618->createPacShader(m_fileResTh->m_glassBreakage, 0x3ff, true);
  unknown10 = mtl::MemManager::allocate(
      m_drMan->unknown0c, sizeof(DrResShdMpf) * 38 + sizeof(DrResShdPrePass) * 42 + sizeof(DrResShdShw) * 5 + sizeof(DrResShdStreamOut) * 9 + sizeof(DrResShdObjMot) * 6, 8, false, "no name", 0);
  for (s32 i = 0; i < unknown618->unknown54; i++) {
    const ShaderList::unknown003 *group = getShaderGroup(unknown618, i);
    u32 index = group->unknown04;
    s32 count = group->unknown00;
    DrShdDataObj *object = unknown618->unknown40 + index;
    unknown18[i] = object;
    for (s32 j = 0; j < count; j++) {
      const ShaderList::unknown002 *entry =
          reinterpret_cast<const ShaderList::unknown002 *>(static_cast<const u8 *>(unknown618->unknown08) + static_cast<const ShaderList::unknown001 *>(unknown618->unknown08)->unknown08) + index;
      (object + j)->createShader(this, entry->unknown06, entry->unknown04);
      index++;
    }
  }
  m_mpfObj = static_cast<DrResShdMpf *>(unknown10);
  for (int i = 0; i < 38; i++) {
    new (&m_mpfObj[i]) DrResShdMpf(&unknown18[5][i], i);
  }
  m_prePassObj = static_cast<DrResShdPrePass *>(static_cast<void *>(static_cast<u8 *>(unknown10) + sizeof(DrResShdMpf) * 38));
  for (int i = 0; i < 42; i++) {
    new (&m_prePassObj[i]) DrResShdPrePass(&unknown18[6][i], i);
  }
  m_shwObj = static_cast<DrResShdShw *>(static_cast<void *>(static_cast<u8 *>(unknown10) + sizeof(DrResShdMpf) * 38 + sizeof(DrResShdPrePass) * 42));
  for (int i = 0; i < 5; i++) {
    new (&m_shwObj[i]) DrResShdShw(&unknown18[7][i], i);
  }
  m_stmOutObj = static_cast<DrResShdStreamOut *>(static_cast<void *>(static_cast<u8 *>(unknown10) + sizeof(DrResShdMpf) * 38 + sizeof(DrResShdPrePass) * 42 + sizeof(DrResShdShw) * 5));
  for (int i = 0; i < 9; i++) {
    new (&m_stmOutObj[i]) DrResShdStreamOut(&unknown18[4][i], i);
  }
  m_objMotBlurObj = static_cast<DrResShdObjMot *>(
      static_cast<void *>(static_cast<u8 *>(unknown10) + sizeof(DrResShdMpf) * 38 + sizeof(DrResShdPrePass) * 42 + sizeof(DrResShdShw) * 5 + sizeof(DrResShdStreamOut) * 9));
  for (int i = 0; i < 6; i++) {
    new (&m_objMotBlurObj[i]) DrResShdObjMot(&unknown18[8][i], i);
  }
}

void DrShdDataList::releaseShader() {
  if (unknown10 != nullptr) {
    unknown618->release();
    if (unknown10 != nullptr) {
      mtl::MemManager::deallocate(unknown10, 0, false);
      unknown10 = nullptr;
    }
  }
  if (m_fileResTh != nullptr) {
    m_fileResTh->Release();
    m_fileResTh = nullptr;
  }
}

void DrShdDataList::reloadShader(int type) { createShader(); }

DrShdDataObj *DrShdDataList::getDebugShdObj(int index) { return &unknown18[0][index]; }

DrShdDataObj *DrShdDataList::getSelectShdObj(int index) { return &unknown18[1][index]; }

DrShdDataObj *DrShdDataList::getShadowShdObj(int index) { return &unknown18[2][index]; }

DrShdDataObj *DrShdDataList::getPostShdObj(int index) { return &unknown18[3][index]; }

DrShdDataObj *DrShdDataList::getSteamShdObj(int index) { return &unknown18[4][index]; }

DrShdDataObj *DrShdDataList::getMpfShdObj(int index) { return &unknown18[5][index]; }

DrShdDataObj *DrShdDataList::getPreShdObj(int index) { return &unknown18[6][index]; }

DrShdDataObj *DrShdDataList::getComputeObj(int index) { return &unknown18[9][index]; }

DrShdDataObj *DrShdDataList::getCateShdObj(int category, int index) { return &unknown18[category][index]; }

DrResShdMpf *DrShdDataList::getMpfObj(int index) { return &m_mpfObj[index]; }

DrResShdPrePass *DrShdDataList::getPrePassObj(int index) { return &m_prePassObj[index]; }

DrResShdShw *DrShdDataList::getShwObj(int index) { return &m_shwObj[index]; }

DrResShdStreamOut *DrShdDataList::getStmOutObj(int index) { return &m_stmOutObj[index]; }

DrResShdObjMot *DrShdDataList::getObjMotBlurObj(int index) { return &m_objMotBlurObj[index]; }

void DrShdDataList::bindShdVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[0]); }

void DrShdDataList::bindShdSphereVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[5]); }

void DrShdDataList::bindShdSpotVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[7]); }

void DrShdDataList::bindQuadsTex() { grlib::CGLibCtlVertex::setVertex(unknown638[1]); }

void DrShdDataList::bindTriangle() { grlib::CGLibCtlVertex::setVertex(unknown638[2]); }

void DrShdDataList::bindTriangleTex() { grlib::CGLibCtlVertex::setVertex(unknown638[3]); }

void DrShdDataList::bindShdBoxVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[4]); }

void DrShdDataList::bindShdCylinderVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[6]); }

void DrShdDataList::bindShdRainDropVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[8]); }

void DrShdDataList::bindShdEffVtx() { grlib::CGLibCtlVertex::setVertex(unknown638[9]); }

void DrShdDataList::bindShdDepthCheck() { grlib::CGLibCtlVertex::setVertex(unknown638[10]); }

void DrShdDataList::bindPlaneVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[11]); }

void DrShdDataList::renderQuads() { unknown818[0].drawIndex(); }

void DrShdDataList::renderInstQuads(int instanceCount) { unknown818[0].drawInsIndex(instanceCount); }

void DrShdDataList::renderTriangle() { unknown818[1].drawIndex(); }

void DrShdDataList::renderSphere() { unknown818[3].drawIndex(); }

void DrShdDataList::renderSpotMdl() { unknown818[5].drawIndex(); }

void DrShdDataList::renderBox() { unknown818[2].drawIndex(); }

void DrShdDataList::renderCylinder() { unknown818[4].drawIndex(); }

void DrShdDataList::renderRainDrop() { unknown818[6].drawIndex(); }

void DrShdDataList::renderEffVtx(int instanceCount) { unknown818[7].drawInsIndex(instanceCount); }

void DrShdDataList::renderPoint(int count) { grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, count); }

void DrShdDataList::renderPoint(int count, int instanceCount) { grlib::CGLibCtlVertex::renderInstanceVertex(GRL_PRIMITIVE_POINTS, count, instanceCount); }

DrResFetch *DrShdDataList::getFetchShader(int index) { return &m_fetchShader[index]; }

DrResFetch *DrShdDataList::getSubFetchShader(int index) {
  u8 next = s_etcNextVertex[index];
  return next == 0xff ? nullptr : &m_fetchShader[next];
}

grlib::CGLibOneUniformBlock *DrShdDataList::getAlphaTestUniform(f32 alphaRef) {
  u32 index = static_cast<s32>(alphaRef * 10.0f);
  if (index > 10) {
    index = 10;
  }
  return &unknown9a8.m_items[index];
}

// 0x710089c2ac. The vertices are five floats each (x, y, z, u, v): 25 for the top ring, 25 for the bottom ring and 24 (the
// last of each 25 is never written) for each cap, whose centre vertices sit at y = +-1.5. The unused parameter is the
// DrMan the other geometry builders of this class take as well; the body never reads it.
void DrShdDataList::createRainDropGeometry(DrMan *drMan) {
  void *buffer;
  u32 size;
  unknown638[8].createVertexBuff(2000, 0x14);
  unknown638[8].lock(&buffer, &size);
  f32 *vertex = static_cast<f32 *>(buffer);
  for (int i = 0; i < 25; i++) {
    f32 angle = i * 15.0f * 3.1415927f / 180.0f;
    f32 x = cosf(angle);
    f32 z = sinf(angle);
    vertex[i * 5] = x;
    vertex[i * 5 + 1] = 1.0f;
    vertex[i * 5 + 2] = z;
    vertex[i * 5 + 3] = i / 24.0f;
    vertex[i * 5 + 4] = 0.25f;
    vertex[i * 5 + 125] = x;
    vertex[i * 5 + 126] = -1.0f;
    vertex[i * 5 + 127] = z;
    vertex[i * 5 + 128] = i / 24.0f;
    vertex[i * 5 + 129] = 0.75f;
    if (i != 24) {
      f32 u = (i + 0.5f) / 24.0f;
      vertex[i * 5 + 250] = 0.0f;
      vertex[i * 5 + 251] = 1.5f;
      vertex[i * 5 + 252] = 0.0f;
      vertex[i * 5 + 253] = u;
      vertex[i * 5 + 254] = 0.0f;
      vertex[i * 5 + 375] = 0.0f;
      vertex[i * 5 + 376] = -1.5f;
      vertex[i * 5 + 377] = 0.0f;
      vertex[i * 5 + 378] = u;
      vertex[i * 5 + 379] = 1.0f;
    }
  }
  unknown638[8].unlock();
  unknown818[6].createIndexBuff(0x120, GRL_PRIMITIVE_TRIANGLES, GRL_INDEX_FORMAT_U16);
  unknown818[6].lock(&buffer, &size);
  u16 *index = static_cast<u16 *>(buffer);
  // In the game's first loop the induction variable is the vertex index i + 26 and the exit compares i + 25 with 48; with
  // `i + 1` and `i + 26` written directly clang picks i + 25 instead (compared at 48 before the increment), so the next
  // vertex keeps its own local.
  int n = 0;
  for (int i = 0; i < 24; i++) {
    int next = i + 1;
    index[n++] = i;
    index[n++] = next;
    index[n++] = next + 25;
    index[n++] = i;
    index[n++] = next + 25;
    index[n++] = i + 25;
  }
  for (int i = 0; i < 24; i++) {
    int next = i + 1;
    index[n++] = i;
    index[n++] = i + 50;
    index[n++] = next;
    index[n++] = i + 25;
    index[n++] = next + 25;
    index[n++] = i + 75;
  }
  unknown818[6].unlock();
}

void DrShdDataList::createAlphaTestBlock() {
  unknown9a8.setupArray(11);
  unknown9a8.unknown0c = 0xb00;
  // Reopen 2026-11-14 (ruling 8, P4): the statements of CGLibUniformArray::unknown002 written out again, without its last store.
  // Re-measured: the call `unknown9a8.unknown002();` gives 179 instructions against the game's 178 at 0x710089c4c0 (an extra str wzr of
  // the offset). Dropping that store from the helper is no way out: the nine other users of the helper keep it in the game
  // (DrPixlShadowCacheMan::createCacheBuff, DrShdUniformBlockMan, DrShdLgtTileBasedDr::createWork, LayerObjTopDef::workIconCreate).
  grlib::CGLibMemHandle::free(unknown9a8.unknown18);
  if (unknown9a8.unknown0c != 0) {
    grlib::CGLibMemHandle::allocUniform(unknown9a8.unknown18, unknown9a8.unknown0c);
    unknown9a8.unknown10 = unknown9a8.unknown0c;
    unknown9a8.unknown0c = 0;
  }
  for (int i = 0; i < 11; i++) {
    unknown9a8.unknown0c += unknown9a8[i].setupArray(0x10, unknown9a8.unknown18, unknown9a8.unknown0c);
  }
  for (int i = 1; i < 10; i++) {
    grlib::CGLibOneUniformBlock &block = unknown9a8[i];
    f32 *data = static_cast<f32 *>(block.m_mapping);
    data[0] = i * 0.1f;
    data[1] = 0.0f;
    data[2] = 0.0f;
    data[3] = 0.0f;
    block.updateData();
  }
  grlib::CGLibOneUniformBlock &firstBlock = unknown9a8[0];
  f32 *first = static_cast<f32 *>(firstBlock.m_mapping);
  first[0] = 0.01f;
  first[1] = 0.0f;
  first[2] = 0.0f;
  first[3] = 0.0f;
  firstBlock.updateData();
  grlib::CGLibOneUniformBlock &lastBlock = unknown9a8[10];
  f32 *last = static_cast<f32 *>(lastBlock.m_mapping);
  last[0] = 0.99f;
  last[1] = 0.0f;
  last[2] = 0.0f;
  last[3] = 0.0f;
  lastBlock.updateData();
}

DrShdDataObj::DrShdDataObj() {
  unknown68[0] = nullptr;
  unknown68[1] = nullptr;
}

DrShdDataObj::~DrShdDataObj() {}

void DrShdDataObj::release() {}

void DrShdDataObj::setupShader(u32 index) { grlib::CGLibCtlShader::setShader(*this, *unknown68[index]); }

void DrShdDataObj::setupShader(DrResFetch *fetch) { grlib::CGLibCtlShader::setShader(*this, *fetch); }

void DrShdDataObj::setupComputeShader() { grlib::CGLibCtlShader::setComputeShader(*this); }

} // namespace ml

template class grlib::CGLibShdListBase<ml::DrShdDataObj>;

// clang-format off
#include "dr_shd_fetch_man.cpp"
#include "dr_shd_fetch_obj.cpp"
#include "dr_shd_lgt_man.cpp"
#include "dr_shd_lgt_obj.cpp"
#include "dr_shd_lgt_tile_based_dr.cpp"
#include "dr_shd_man.cpp"
#include "dr_shd_mdo_man.cpp"
#include "dr_shd_mdo_ext_tbl_obj.cpp"
#include "dr_shd_mdo_dec_ext_tbl.cpp"
#include "dr_shd_mdo_dec_res.cpp"
// clang-format on
