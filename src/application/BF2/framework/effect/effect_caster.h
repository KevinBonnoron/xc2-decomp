#pragma once
#include <stddef.h>

#include "eflib/effect_callback.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace ml {
class DrMdlObj;
class ScnObjModelDrSys;
} // namespace ml

namespace mm {
namespace mtl {
class IAllocator;
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace fw {

struct UpdateInfo;
class EffectCasterBase;
class EffectPoint;

class EffectCasterSend : public effect::IEffectCallBack, public mm::mtl::IntrusiveListNode<EffectCasterSend> {
public:
  static const u32 BUFFER_NUM = 2;

  struct MtxAndName {
    u32 unknown00;               // Inferred role: hash; original member name unknown.
    char unknown04[0x20 - 0x04]; // Inferred role: name; original member name unknown.
    mm::Mat44 unknown20;         // Inferred role: matrix; original member name unknown.
  };

  explicit EffectCasterSend(mm::mtl::IAllocator *allocator);
  virtual ~EffectCasterSend();
  virtual ml::DrMdlObj *getMdl();
  virtual const char *getStateName();
  virtual MtxAndName *getBindData(u32 &count);
  virtual f32 getMdlFrame();
  virtual f32 getMdlScl();
  virtual bool getMdlMat(mm::Mat44 &matrix);
  virtual bool getEfpMat(mm::Mat44 &matrix, const char *name);

  void tailCopy();
  EffectCasterBase *getCaster();
  bool checkCaster(EffectCasterBase *caster);
  void sendData(mm::Mat44 &matrix, const char *name, int index);
  void sendData(f32 scale);
  void sendDataFrame(f32 frame);
  void sendDataStateName(const char *name);

  mm::mtl::Vector<MtxAndName> unknown18[BUFFER_NUM]; // Inferred role: bind datas; original member name unknown.
  EffectCasterBase *m_caster;
  EffectPoint *unknown70;         // Inferred role: point; original member name unknown.
  mm::mtl::IAllocator *unknown78; // Inferred role: allocator; original member name unknown.
  ml::DrMdlObj *unknown80;        // Inferred role: model; original member name unknown.
  f32 m_mdlScl[BUFFER_NUM];
  f32 m_mdlFrame[BUFFER_NUM];
  mm::mtl::FixStr<32> unknown98[BUFFER_NUM]; // Inferred role: state names; original member name unknown.
};

static_assert(offsetof(EffectCasterSend::MtxAndName, unknown20) == 0x20, "");
static_assert(sizeof(EffectCasterSend::MtxAndName) == 0x60, "");
static_assert(offsetof(EffectCasterSend, unknown18) == 0x18, "");
static_assert(offsetof(EffectCasterSend, m_caster) == 0x68, "");
static_assert(offsetof(EffectCasterSend, unknown70) == 0x70, "");
static_assert(offsetof(EffectCasterSend, unknown78) == 0x78, "");
static_assert(offsetof(EffectCasterSend, unknown80) == 0x80, "");
static_assert(offsetof(EffectCasterSend, unknown98) == 0x98, "");
static_assert(sizeof(EffectCasterSend) == 0xe0, "");

class EffectCasterBase {
public:
  EffectCasterBase(const EffectPoint *point, u32 layer);
  // Inferred role: per frame update; original name unknown.
  virtual void unknown001(const UpdateInfo &info) = 0;
  // Inferred role: update after the effect system update; original name unknown.
  virtual void unknown002(const UpdateInfo &info) = 0;
  virtual ~EffectCasterBase();
  void setScl(f32 scale);
  void setMotionFrame(f32 frame);
  void setStateName(const char *name);
  void setEfpMat(mm::Mat44 &matrix, const char *name, int index);
  void changeLayer(u32 layer, u32 newLayer);
  static void tail();

  static mm::mtl::FixedVector<EffectCasterBase *, 256> s_casterList;

  mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> unknown08; // Inferred role: unknown reference object; original type and member name unknown.
  EffectPoint *unknown10;                                    // Inferred role: point; original member name unknown.
  ml::ScnObjModelDrSys *unknown18;                           // Inferred role: model; original member name unknown.
  EffectCasterSend::MtxAndName *unknown20;                   // Inferred role: bind datas; original member name unknown.
  u32 unknown28;                                             // Inferred role: bind data count; original member name unknown.
  mm::mtl::IAllocator *unknown30;                            // Inferred role: allocator; original member name unknown.
  u32 unknown38;                                             // Inferred role: point count; original member name unknown.
  u32 unknown3c;                                             // Inferred role: layer; original member name unknown.
  bool _40;
};

static_assert(offsetof(EffectCasterBase, unknown08) == 0x08, "");
static_assert(offsetof(EffectCasterBase, unknown10) == 0x10, "");
static_assert(offsetof(EffectCasterBase, unknown18) == 0x18, "");
static_assert(offsetof(EffectCasterBase, unknown20) == 0x20, "");
static_assert(offsetof(EffectCasterBase, unknown3c) == 0x3c, "");

} // namespace fw
