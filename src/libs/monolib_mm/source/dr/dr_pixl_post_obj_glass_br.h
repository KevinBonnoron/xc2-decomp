#pragma once
#include <stddef.h>

#include "dr/dr_ini_sys.h"
#include "dr/dr_pixl_post_obj.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {
class DrMan;
class DrPixlMan;
class DrPixlPostMan;

class DrPixlPostObjGlassBr : public DrPixlPostObj {
public:
  // Inferred role: one glass shard; original type name unknown. Evidence: posInt and update walk the array allocated by setup with a stride of 0x40.
  struct unknown001 {
    mm::Vec3 unknown00; // Inferred role: position; original member name unknown.
    mm::Vec3 unknown10; // Inferred role: velocity; original member name unknown.
    mm::Vec3 unknown20; // Inferred role: rotation axis; original member name unknown.
    f32 unknown30;      // Inferred role: rotation angle; original member name unknown.
    f32 unknown34;      // Inferred role: rotation speed; original member name unknown.
  };

  enum Flag {
    FLAG_UNKNOWN_0 = 1 << 0,
    FLAG_UNKNOWN_1 = 1 << 1,
    FLAG_UNKNOWN_2 = 1 << 2,
    FLAG_UNKNOWN_3 = 1 << 3,
  };

  DrPixlPostObjGlassBr(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjGlassBr();
  void update();
  void render();
  void release();
  void setup();
  void posInt();
  void renderCaputre();
  void renderGlass();

  grlib::CGLibVtxVertex m_cGLibVtxVertex;             // Inferred role: vertex; original member name unknown.
  grlib::CGLibVtxIndex m_cGLibVtxIndex;               // Inferred role: index; original member name unknown.
  grlib::CGLibVtlMemPool m_cGLibVtlMemPool;           // Inferred role: memory pool; original member name unknown.
  grlib::CGLibRenderTarget m_cGLibRenderTarget;       // Inferred role: render target; original member name unknown.
  grlib::CGLibDblUniformBlock m_cGLibDblUniformBlock; // Inferred role: uniform block; original member name unknown.
  u8 _498[0x4a0 - 0x498];
  mm::Mat44 unknown4a0; // Inferred role: projection matrix, written by posInt and uploaded by update; original member name unknown.
  void *unknown4e0;     // Inferred role: unused data; original member name unknown.
  s32 unknown4e8;       // Inferred role: unused value; original member name unknown.
  u8 _4ec[0x4f0 - 0x4ec];
  DrIniSys::unknown004 *unknown4f0; // Inferred role: glass breakage data, from DrIniSys::getGlassBreakage; original member name unknown.
  unknown001 *unknown4f8;           // Inferred role: work buffer of glass shards; original member name unknown.
  s32 unknown500;                   // Inferred role: shard count; original member name unknown.
  f32 unknown504;                   // Inferred role: depth offset of the projection; original member name unknown.
  u32 unknown508;                   // Inferred role: state flags; original member name unknown.
  f32 unknown50c;                   // Inferred role: elapsed time; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjGlassBr, m_cGLibVtxVertex) == 0x18, "");
static_assert(offsetof(DrPixlPostObjGlassBr, m_cGLibVtxIndex) == 0x40, "");
static_assert(offsetof(DrPixlPostObjGlassBr, m_cGLibVtlMemPool) == 0x68, "");
static_assert(offsetof(DrPixlPostObjGlassBr, m_cGLibRenderTarget) == 0x98, "");
static_assert(offsetof(DrPixlPostObjGlassBr, m_cGLibDblUniformBlock) == 0x460, "");
static_assert(offsetof(DrPixlPostObjGlassBr, unknown4a0) == 0x4a0, "");
static_assert(offsetof(DrPixlPostObjGlassBr, unknown4e0) == 0x4e0, "");
static_assert(offsetof(DrPixlPostObjGlassBr, unknown4f0) == 0x4f0, "");
static_assert(offsetof(DrPixlPostObjGlassBr, unknown4f8) == 0x4f8, "");
static_assert(offsetof(DrPixlPostObjGlassBr, unknown500) == 0x500, "");
static_assert(offsetof(DrPixlPostObjGlassBr, unknown508) == 0x508, "");
static_assert(offsetof(DrPixlPostObjGlassBr::unknown001, unknown10) == 0x10, "");
static_assert(offsetof(DrPixlPostObjGlassBr::unknown001, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjGlassBr::unknown001, unknown30) == 0x30, "");
static_assert(offsetof(DrPixlPostObjGlassBr::unknown001, unknown34) == 0x34, "");
static_assert(sizeof(DrPixlPostObjGlassBr::unknown001) == 0x40, "");

} // namespace ml
