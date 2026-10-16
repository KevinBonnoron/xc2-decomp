#pragma once
#include <stddef.h>

#include "event/chara_weight_item.h"
#include "event/curve.h"
#include "event/memory_manager.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
class GfObj;
} // namespace gf
namespace mm {
struct Vec3;
} // namespace mm

namespace event {

class CharaObj;

class CharaWeightPlayer {
public:
  static constexpr size_t ITEM_COUNT = 12;

  CharaWeightPlayer();
  virtual ~CharaWeightPlayer() {}
  void create(gf::GF_OBJ_HANDLE *handle, CharaObj *chara);
  void destroy();
  void update(f32 delta);
  void render(const mm::Vec3 &position, f32 height);
  CharaWeightItem *searchItem(const char *stat);

  void easeIn(gf::AnimLayer layer, const char *stat, f32 frame, f32 weight, f32 speed, CV_TYPE cv, WeightLayer weightLayer) {
    CharaWeightItem *item = searchItem(stat);
    if (item == nullptr) {
      gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
      if (obj == nullptr) {
        return;
      }
      item = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaWeightItem();
      item->create(obj, layer, stat, stat);
      mItems.push_back(item);
    }
    item->easeIn(frame, weight, speed, cv, weightLayer);
  }

  void easeOut(gf::AnimLayer layer, const char *stat, f32 frame, CV_TYPE cv, WeightLayer weightLayer);
  void setAddWeight(const char *stat, f32 weight, WeightLayer weightLayer);

private:
  gf::GF_OBJ_HANDLE *handle;
  CharaObj *mChara;
  mm::mtl::FixedVector<CharaWeightItem *, ITEM_COUNT> mItems;
};

static_assert(sizeof(CharaWeightPlayer) == 0x80, "");

} // namespace event
