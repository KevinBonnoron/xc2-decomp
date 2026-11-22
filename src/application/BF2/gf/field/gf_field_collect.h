#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "gf/field/gf_fobj_dropitem.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

// Layout from its constructor (0x71002d5b08), the destructor, start, createDropitemEmitter and the seq* functions.
class GfFieldCollect : public mm::mtl::PtrSingleton<GfFieldCollect> {
public:
  typedef void (GfFieldCollect::*Sequence)(f32 deltaTime);

  GfFieldCollect(const GfSetupParam &param);
  void seqEnd(f32 deltaTime);
  void create(const GfSetupParam &param);
  ~GfFieldCollect();
  bool isDropitemsEmitted() const;
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  void end();
  void start(GF_OBJ_HANDLE *handle);
  void createDropitemEmitter(const GfDropitemEmitter::CreateInfo &info);
  void dispose();
  void update(f32 deltaTime);
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  void seqWaitUIEnd(f32 deltaTime);
  void seqDo(f32 deltaTime);
  void seqWaitDrop(f32 deltaTime);

  Sequence unknown08;                                   // Inferred role: sequence; original member name unknown.
  bool unknown18;                                       // Inferred role: created; original member name unknown.
  bool unknown19;                                       // Inferred role: field skill window closed; original member name unknown.
  GF_OBJ_HANDLE *m_GF_OBJ_HANDLE;                       // Inferred role: collection point object; original member name unknown.
  mm::mtl::FixedVector<GfDropitemEmitter, 4> unknown30; // Inferred role: dropitem emitters; original member name unknown.
  f32 unknown1c0;                                       // Inferred role: elapsed time; original member name unknown.
  f32 unknown1c4;                                       // Inferred role: wait time before the field skill check; original member name unknown.
  u16 unknown1c8;                                       // Inferred role: FSID of the collection point; original member name unknown.
  mm::mtl::FixedVector<u32, 3> unknown1d0;              // Inferred role: blades whose field skill succeeded; original member name unknown.
};

static_assert(offsetof(GfFieldCollect, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldCollect, unknown18) == 0x18, "");
static_assert(offsetof(GfFieldCollect, m_GF_OBJ_HANDLE) == 0x20, "");
static_assert(offsetof(GfFieldCollect, unknown30) == 0x30, "");
static_assert(offsetof(GfFieldCollect, unknown1c0) == 0x1c0, "");
static_assert(offsetof(GfFieldCollect, unknown1c8) == 0x1c8, "");
static_assert(offsetof(GfFieldCollect, unknown1d0) == 0x1d0, "");
static_assert(sizeof(GfFieldCollect) == 0x1f0, "");

} // namespace gf
