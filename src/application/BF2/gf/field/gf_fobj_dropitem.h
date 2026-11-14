#pragma once
#include <stddef.h>

#include "gf/field/gf_dropitem_param.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;

struct GfDropitemInfo {
  u32 unknown00; // Inferred role: item id; original member name unknown.
  u16 unknown04; // Inferred role: number and percentage; original member name unknown.
  u8 _06[0x08 - 0x06];
  u32 unknown08; // Inferred role: gold; original member name unknown.
  u32 unknown0c; // Role and original member name unknown.
};

static_assert(offsetof(GfDropitemInfo, unknown08) == 0x08, "");
static_assert(sizeof(GfDropitemInfo) == 0x10, "");

class GfFobjDropitem {
public:
  struct BdatInfo {
    void create(s32 id);

    u16 unknown00; // Inferred role: sound of the drop; original member name unknown.
    u16 unknown02; // Inferred role: sound of the pickup; original member name unknown.
    u8 unknown04;  // Role and original member name unknown.
  };

  struct EmitInfo {
    EmitInfo() : unknown00(mm::Vec3::zero), unknown10(0.0f), unknown14(3.1415927f), unknown18(0.0f), unknown1c(0.0f), unknown20(0.0f), unknown50(0), unknown54(0), unknown55(false) {}
    void createDropitemInfos(u8 *bdat, s32 row);
    bool isValid() const;

    mm::Vec3 unknown00;
    f32 unknown10; // Inferred role: rotation Y; original member name unknown.
    f32 unknown14; // Role and original member name unknown.
    f32 unknown18; // Role and original member name unknown.
    f32 unknown1c; // Role and original member name unknown.
    f32 unknown20; // Role and original member name unknown.
    u8 _24[0x28 - 0x24];
    mm::mtl::Vector<GfDropitemInfo> unknown28; // Inferred role: dropitems; original member name unknown.
    u32 unknown50;                             // Role and original member name unknown.
    u8 unknown54;                              // Inferred role: parameter id; original member name unknown.
    bool unknown55;                            // Role and original member name unknown.
  };

  GfFobjDropitem(GF_OBJ_HANDLE *handle);
  virtual ~GfFobjDropitem() {}
  void bindToGfObj(GF_OBJ_HANDLE *handle) const;
  void unbindToGfObj(GF_OBJ_HANDLE *handle) const;
  void initialize();
  void update(const fw::UpdateInfo &info);
  void destroy();
  void setEventDisp(bool isDisp);
  static u32 getBdatDefineFromItemId(s32 itemId);
  static u32 getResBdatIdFromItemId(s32 itemId);
  void applyGetItem(GF_OBJ_HANDLE *target) const;
  static bool applyGetItem(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *target);
  static GF_OBJ_HANDLE *emitDropitem(u8 paramIndex, s32 itemId, f32 param);
  static GF_OBJ_HANDLE *emitDropgold(u8 paramIndex, u32 gold);
  static f32 emitDropitems(const EmitInfo &info);
  void createGottenEffect(GF_OBJ_HANDLE *target) const;
  bool canGetItem(GF_OBJ_HANDLE *target, f32 margin) const;
  bool isEnableGet() const;
  void disposeEffect();

  u16 unknown08;  // Role and original member name unknown.
  u16 unknown0a;  // Role and original member name unknown.
  bool unknown0c; // Role and original member name unknown.
  u8 _0d;
  bool unknown0e; // Role and original member name unknown.
  u8 _0f;
  GF_OBJ_HANDLE *unknown10; // Inferred role: object; original member name unknown.
  u8 _18[0x20 - 0x18];
  mm::Vec3 unknown20;            // Inferred role: velocity; original member name unknown.
  s32 unknown30;                 // Inferred role: state; original member name unknown.
  f32 unknown34;                 // Role and original member name unknown.
  f32 unknown38;                 // Role and original member name unknown.
  f32 unknown3c;                 // Role and original member name unknown.
  GfDropitemParamInst unknown40; // Inferred role: parameters of the drop; original member name unknown.
  bool unknown50;                // Role and original member name unknown.
  u8 _51[0x54 - 0x51];
  u32 unknown54; // Inferred role: effect handle; original member name unknown.
  u8 _58[0x60 - 0x58];
};

static_assert(offsetof(GfFobjDropitem::EmitInfo, unknown28) == 0x28, "");
static_assert(offsetof(GfFobjDropitem::EmitInfo, unknown50) == 0x50, "");
static_assert(offsetof(GfFobjDropitem::EmitInfo, unknown54) == 0x54, "");
static_assert(offsetof(GfFobjDropitem, unknown08) == 0x08, "");
static_assert(offsetof(GfFobjDropitem, unknown20) == 0x20, "");
static_assert(offsetof(GfFobjDropitem, unknown34) == 0x34, "");
static_assert(offsetof(GfFobjDropitem, unknown40) == 0x40, "");
static_assert(offsetof(GfFobjDropitem, unknown10) == 0x10, "");
static_assert(offsetof(GfFobjDropitem, unknown30) == 0x30, "");
static_assert(offsetof(GfFobjDropitem, unknown50) == 0x50, "");
static_assert(offsetof(GfFobjDropitem, unknown54) == 0x54, "");

// Layout from its constructor, create, dispose, update and seqWaitBeginDrop, and from GmkSalvageLocator,
// which embeds it at 0x60 and fills its CreateInfo. GfFieldTbox::isDropitemsEmitted reads m_dropitemsEmitted, and the
// destructors of GfFieldTbox and GmkSalvageLocator call dispose on their emitter.
class GfDropitemEmitter {
public:
  struct CreateInfo {
    CreateInfo() : unknown00(mm::Vec3::zero), unknown10(0.0f), unknown14(3.1415927f), unknown18(0.0f), unknown1c(0.0f), unknown20(0.0f), unknown24(0.0f), unknown28(nullptr), unknown30(0) {}

    mm::Vec3 unknown00; // Inferred role: position; original member name unknown.
    f32 unknown10;      // Inferred role: rotation Y; original member name unknown.
    f32 unknown14;      // Role and original member name unknown.
    f32 unknown18;      // Role and original member name unknown.
    f32 unknown1c;      // Inferred role: wait time before the drop; original member name unknown.
    f32 unknown20;      // Role and original member name unknown.
    f32 unknown24;      // Role and original member name unknown.
    u8 *unknown28;      // Inferred role: bdat of the dropitems; original member name unknown.
    int unknown30;      // Inferred role: row of the dropitems; original member name unknown.
  };

  GfDropitemEmitter(const CreateInfo *info = nullptr);
  ~GfDropitemEmitter() { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  void update(f32 deltaTime);
  void seqWaitBeginDrop(f32 deltaTime);
  void seqWaitEndDrop(f32 deltaTime);

  CreateInfo unknown00; // Inferred role: create info; original member name unknown.
  bool m_dropitemsEmitted;
  f32 unknown44;                             // Inferred role: elapsed time; original member name unknown.
  f32 unknown48;                             // Role and original member name unknown.
  void (GfDropitemEmitter::*unknown50)(f32); // Inferred role: sequence; original member name unknown.
};

static_assert(offsetof(GfDropitemEmitter::CreateInfo, unknown10) == 0x10, "");
static_assert(offsetof(GfDropitemEmitter::CreateInfo, unknown28) == 0x28, "");
static_assert(offsetof(GfDropitemEmitter::CreateInfo, unknown30) == 0x30, "");
static_assert(offsetof(GfDropitemEmitter, m_dropitemsEmitted) == 0x40, "");
static_assert(offsetof(GfDropitemEmitter, unknown44) == 0x44, "");
static_assert(offsetof(GfDropitemEmitter, unknown50) == 0x50, "");
static_assert(sizeof(GfDropitemEmitter) == 0x60, "");

} // namespace gf
