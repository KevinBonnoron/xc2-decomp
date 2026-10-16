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
  u8 _00[0x0c - 0x00];
  u32 layer;
};

static_assert(offsetof(EffectPoint, layer) == 0x0c, "");

struct EffectBindData {
  u32 hash;
  char name[0x20 - 0x04];
  mm::Mat44 matrix;
};

static_assert(offsetof(EffectBindData, matrix) == 0x20, "");
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
  EffectPoint *point;
  void *model;
  EffectBindData *bindDatas;
  u32 bindDataCount;
  mm::mtl::IAllocator *allocator;
  u32 pointCount;
  u32 layer;
  bool _40;
};

static_assert(offsetof(EffectCasterBase, point) == 0x10, "");
static_assert(offsetof(EffectCasterBase, bindDatas) == 0x20, "");
static_assert(offsetof(EffectCasterBase, layer) == 0x3c, "");

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

  EffectCasterBase *getCaster();
  bool checkCaster(EffectCasterBase *caster);
  void sendData(f32 scale);
  void sendDataFrame(f32 frame);
  void sendDataStateName(const char *name);

  mm::mtl::Vector<EffectBindData> bindDatas[BUFFER_NUM];
  EffectCasterBase *caster;
  u8 _70[0x80 - 0x70];
  void *model;
  f32 scales[BUFFER_NUM];
  f32 frames[BUFFER_NUM];
  mm::mtl::FixStr<32> stateNames[BUFFER_NUM];
};

static_assert(offsetof(EffectCasterSend, bindDatas) == 0x18, "");
static_assert(offsetof(EffectCasterSend, caster) == 0x68, "");
static_assert(offsetof(EffectCasterSend, model) == 0x80, "");
static_assert(offsetof(EffectCasterSend, stateNames) == 0x98, "");
static_assert(sizeof(EffectCasterSend) == 0xe0, "");

} // namespace fw
