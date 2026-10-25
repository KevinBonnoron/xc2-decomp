#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class EffectPoint {
public:
  int getPointCount() const;

  u8 _00[0x0c - 0x00];
  u32 unknown0c; // Inferred role: layer; original member name unknown.
  u8 _10[0x18 - 0x10];
  u32 unknown18; // Inferred role: point count; original member name unknown.
};

static_assert(offsetof(EffectPoint, unknown0c) == 0x0c, "");
static_assert(offsetof(EffectPoint, unknown18) == 0x18, "");

struct EffectBindData {
  u32 unknown00;               // Inferred role: hash; original member name unknown.
  char unknown04[0x20 - 0x04]; // Inferred role: name; original member name unknown.
  mm::Mat44 unknown20;         // Inferred role: matrix; original member name unknown.
};

static_assert(offsetof(EffectBindData, unknown20) == 0x20, "");
static_assert(sizeof(EffectBindData) == 0x60, "");

class EffectCasterBase {
public:
  virtual ~EffectCasterBase();
  void setScl(f32 scale);
  void setMotionFrame(f32 frame);
  void setStateName(const char *name);
  void setEfpMat(mm::Mat44 &matrix, const char *name, int index);
  void changeLayer(u32 layer, u32 newLayer);

  u8 _08[0x10 - 0x08];
  EffectPoint *unknown10;         // Inferred role: point; original member name unknown.
  void *unknown18;                // Inferred role: model; original member name unknown.
  EffectBindData *unknown20;      // Inferred role: bind datas; original member name unknown.
  u32 unknown28;                  // Inferred role: bind data count; original member name unknown.
  mm::mtl::IAllocator *unknown30; // Inferred role: allocator; original member name unknown.
  u32 unknown38;                  // Inferred role: point count; original member name unknown.
  u32 unknown3c;                  // Inferred role: layer; original member name unknown.
  bool _40;
};

static_assert(offsetof(EffectCasterBase, unknown10) == 0x10, "");
static_assert(offsetof(EffectCasterBase, unknown20) == 0x20, "");
static_assert(offsetof(EffectCasterBase, unknown3c) == 0x3c, "");

class EffectCasterSend : public mm::mtl::IntrusiveListNode<EffectCasterSend> {
public:
  static const u32 BUFFER_NUM = 2;

  virtual ~EffectCasterSend();
  virtual void *getMdl();
  virtual const char *getStateName();
  virtual EffectBindData *getBindData(u32 &count);
  virtual f32 getMdlFrame();
  virtual f32 getMdlScl();
  virtual void getMdlMat(mm::Mat44 &matrix);
  virtual void getEfpMat(mm::Mat44 &matrix, const char *name);

  void tailCopy();
  EffectCasterBase *getCaster();
  bool checkCaster(EffectCasterBase *caster);
  void sendData(mm::Mat44 &matrix, const char *name, int index);
  void sendData(f32 scale);
  void sendDataFrame(f32 frame);
  void sendDataStateName(const char *name);

  mm::mtl::Vector<EffectBindData> unknown18[BUFFER_NUM]; // Inferred role: bind datas; original member name unknown.
  EffectCasterBase *m_caster;
  u8 _70[0x80 - 0x70];
  void *unknown80;                           // Inferred role: model; original member name unknown.
  f32 unknown88[BUFFER_NUM];                 // Inferred role: scales; original member name unknown.
  f32 unknown90[BUFFER_NUM];                 // Inferred role: frames; original member name unknown.
  mm::mtl::FixStr<32> unknown98[BUFFER_NUM]; // Inferred role: state names; original member name unknown.
};

static_assert(offsetof(EffectCasterSend, unknown18) == 0x18, "");
static_assert(offsetof(EffectCasterSend, m_caster) == 0x68, "");
static_assert(offsetof(EffectCasterSend, unknown80) == 0x80, "");
static_assert(offsetof(EffectCasterSend, unknown98) == 0x98, "");
static_assert(sizeof(EffectCasterSend) == 0xe0, "");

} // namespace fw
