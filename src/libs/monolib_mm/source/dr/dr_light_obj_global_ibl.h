#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_pixl_counter.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace ml {

class DrGlobalIBLPack;
class DrResUseQueryObj;

class DrLightObjGlobalIBL {
public:
  static const int TEXTURE_UNKNOWN_7 = 7; // Inferred role: maximum number of textures; original name unknown.
  static const int SH_TERM_UNKNOWN_4 = 4; // Inferred role: number of spherical harmonics terms; original name unknown.

  // Layout from the implicit copy constructor (1.0.0: 0x71007dac18): it copies the vertex and the index as raw bytes,
  // two matrices with the Mat44 alignment check, one float, three Vec3 component by component, the bytes 0x110-0x11e
  // at once, three vectors of four floats and the last 0x88 bytes at once. The default constructor is inlined in
  // mm::mtl::Vector<MeshData>::extend (0x71007daa78): it clears m_drResUseQueryObj and unknown118 between the member constructors.
  struct MeshData {
    MeshData() : m_drResUseQueryObj(nullptr), unknown118(false) {}
    ~MeshData() { m_cGLibPixlCounter.release(); }

    grlib::CGLibVtxVertex m_cGLibVtxVertex;     // Inferred role: vertex; original member name unknown.
    grlib::CGLibVtxIndex m_cGLibVtxIndex;       // Inferred role: index; original member name unknown.
    mm::Mat44 unknown50;                        // Inferred role: proxy to world matrix; original member name unknown.
    mm::Mat44 unknown90;                        // Inferred role: world to proxy matrix (isInRange); original member name unknown.
    f32 unknownd0;                              // Inferred role: bounding radius (update); original member name unknown.
    mm::Vec3 unknowne0;                         // Inferred role: bounding box minimum (isInRange); original member name unknown.
    mm::Vec3 unknownf0;                         // Inferred role: bounding box maximum (isInRange); original member name unknown.
    mm::Vec3 unknown100;                        // Inferred role: bounding box center (update); original member name unknown.
    DrResUseQueryObj *m_drResUseQueryObj;       // Inferred role: occlusion query; original member name unknown.
    bool unknown118;                            // Inferred role: flag cleared with the occlusion query; original member name unknown.
    bool unknown119;                            // Inferred role: camera inside the mesh range, set by update; original member name unknown.
    u8 unknown11a;                              // Inferred role: unknown, set by initializeFromBuffer; original member name unknown.
    u8 unknown11b;                              // Inferred role: proxy shape type, 0 to 3 (isInRange); original member name unknown.
    u8 unknown11c;                              // Inferred role: unknown, set by initializeFromBuffer; original member name unknown.
    bool unknown11d;                            // Inferred role: unknown, bit 0 of a mesh value (initializeFromBuffer); original member name unknown.
    mm::Vec4 unknown120;                        // Inferred role: unknown, set by initializeFromBuffer; original member name unknown.
    mm::Vec4 unknown130;                        // Inferred role: unknown, set by initializeFromBuffer; original member name unknown.
    mm::Vec4 unknown140;                        // Inferred role: unknown, set by initializeFromBuffer; original member name unknown.
    grlib::CGLibDblUniformBlock unknown150;     // Inferred role: uniform block; original member name unknown.
    grlib::CGLibDblUniformBlock unknown188;     // Inferred role: uniform block; original member name unknown.
    grlib::CGLibPixlCounter m_cGLibPixlCounter; // Inferred role: pixel counter; original member name unknown.
  };

  DrLightObjGlobalIBL();
  ~DrLightObjGlobalIBL();
  void update();
  int getPriority() const;
  void bindVertex(u32 index);
  void drawVertex();
  void beginOccQuery();
  void endOccQuery();
  f32 calcSimilarity(const DrLightObjGlobalIBL &other) const;

  DrGlobalIBLPack *m_drGlobalIBLPack; // Inferred role: owner pack, set by initializeFromBuffer; original member name unknown.
  int m_version;                      // Inferred role: version; named after the game accessor ml::DrRequetIBL::getVersion.
  int m_priority;
  u32 unknown10;                       // Inferred role: index in the pack, set by initializeFromBuffer; original member name unknown.
  int m_textureNum;                    // Inferred role: texture num; named after the game accessor ml::DrRequetIBL::getTextureNum.
  u32 unknown18;                       // Inferred role: value read from the object data by initializeFromBuffer; original member name unknown.
  mm::mtl::Vector<MeshData> unknown20; // Inferred role: meshes; original member name unknown.
  f32 unknown48;                       // Inferred role: range value passed to the clip test of update; original member name unknown.
  mm::Vec3 unknown50;                  // Inferred role: bounding box minimum (isInRange); original member name unknown.
  mm::Vec3 unknown60;                  // Inferred role: bounding box maximum (isInRange); original member name unknown.
  u32 unknown70;                       // Inferred role: current mesh index; original member name unknown.
  u8 _74[0x78 - 0x74];
  grlib::CGLibTextureBuffer m_texture[TEXTURE_UNKNOWN_7]; // Inferred role: textures; named after the game accessor ml::DrRequetIBL::getTexture.
  u8 _388[0x390 - 0x388];
  mm::Vec3 unknown390;          // Inferred role: position, set by initializeFromBuffer; original member name unknown.
  mm::Col3 m_additionalAmbient; // Inferred role: additional ambient; named after the game accessor ml::DrRequetIBL::getAdditionalAmbient.
  u8 _3ac[0x3b0 - 0x3ac];
  f32 m_skyIntensity;                                          // Inferred role: sky intensity; named after the game accessor ml::DrRequetIBL::getSkyIntensity.
  f32 m_dirLightIntensity;                                     // Inferred role: dir light intensity; named after the game accessor ml::DrRequetIBL::getDirLightIntensity.
  u64 unknown3b8;                                              // Inferred role: frame count of the last IBL request (DrShdLgtGlobalIBL::updateView); original member name unknown.
  int unknown3c0;                                              // Inferred role: occlusion query result summed by update; original member name unknown.
  bool unknown3c4;                                             // Inferred role: visible flag (DrShdLgtGlobalIBL::updateView); original member name unknown.
  mm::Mat44 unknown3d0;                                        // Inferred role: world to proxy space matrix (DrShdLgtGlobalIBL::updateUB_ToProxySpace); original member name unknown.
  mm::Vec4 unknown410[SH_TERM_UNKNOWN_4];                      // Inferred role: similarity values, one vector per sh term; original member name unknown.
  f32 unknown450[TEXTURE_UNKNOWN_7][SH_TERM_UNKNOWN_4][9];     // Inferred role: sh terms; original member name unknown.
  mm::Mat44 unknown840[TEXTURE_UNKNOWN_7 * SH_TERM_UNKNOWN_4]; // Inferred role: sh matrices; original member name unknown.
};

static_assert(offsetof(DrLightObjGlobalIBL, m_version) == 0x08, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_priority) == 0x0c, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_textureNum) == 0x14, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown48) == 0x48, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown50) == 0x50, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown60) == 0x60, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown390) == 0x390, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown3b8) == 0x3b8, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown3c0) == 0x3c0, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown3c4) == 0x3c4, "");
static_assert(sizeof(DrLightObjGlobalIBL::MeshData) == 0x1e0, "");
static_assert(offsetof(DrLightObjGlobalIBL::MeshData, m_cGLibVtxIndex) == 0x28, "");
static_assert(offsetof(DrLightObjGlobalIBL::MeshData, m_drResUseQueryObj) == 0x110, "");
static_assert(offsetof(DrLightObjGlobalIBL::MeshData, unknown50) == 0x50, "");
static_assert(offsetof(DrLightObjGlobalIBL::MeshData, unknown90) == 0x90, "");
static_assert(offsetof(DrLightObjGlobalIBL::MeshData, unknownd0) == 0xd0, "");
static_assert(offsetof(DrLightObjGlobalIBL::MeshData, unknowne0) == 0xe0, "");
static_assert(offsetof(DrLightObjGlobalIBL::MeshData, unknown100) == 0x100, "");
static_assert(offsetof(DrLightObjGlobalIBL::MeshData, unknown11d) == 0x11d, "");
static_assert(offsetof(DrLightObjGlobalIBL::MeshData, unknown120) == 0x120, "");
static_assert(offsetof(DrLightObjGlobalIBL::MeshData, unknown150) == 0x150, "");
static_assert(offsetof(DrLightObjGlobalIBL::MeshData, m_cGLibPixlCounter) == 0x1c0, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown20) == 0x20, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown70) == 0x70, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_texture) == 0x78, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_additionalAmbient) == 0x3a0, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_skyIntensity) == 0x3b0, "");
static_assert(offsetof(DrLightObjGlobalIBL, m_dirLightIntensity) == 0x3b4, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown3d0) == 0x3d0, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown410) == 0x410, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown450) == 0x450, "");
static_assert(offsetof(DrLightObjGlobalIBL, unknown840) == 0x840, "");

} // namespace ml
