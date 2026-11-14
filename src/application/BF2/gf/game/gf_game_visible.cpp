#include "gf/game/gf_game_visible.h"

#include <math.h>

#include "framework/memory/framework_memory.h"
#include "fw/fw_coli_check.h"
#include "gf/game/gf_game_obj.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/gf_com_visible.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "ml/rand.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/map.h" // IWYU pragma: keep

namespace gf {

struct GF_OBJ_HANDLE; // IWYU pragma: keep

void GfGameVisible::build(const GfSetupParam &) {
// __LINE__ must be 40 as in the original file: it is the line argument of operator new.
#line 40
  GfGameVisible *visible = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameVisible();
  if (visible != nullptr) {
    visible->setup();
  }
}

void GfGameVisible::setup() {
  unknown08.setAllocator(fw::FrameworkMemory::getAllocator(5));
  for (u32 i = 0; i < 0x400; i++) {
    unknown20.push(&unknown2030[i]);
  }
}

void GfGameVisible::destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void GfGameVisible::cleanup() {}

void GfGameVisible::update(const fw::UpdateInfo &info) {
  if (get() != nullptr) {
    get()->updateImpl(info);
  }
}

void GfGameVisible::searchObj(u32 type, const mm::Vec3 &position) {
  const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *list = GfGameObj::getList(type);
  if (!list->empty()) {
    for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::const_iterator it = list->begin(); it != list->end(); ++it) {
      GF_OBJ_HANDLE *handle = *it;
      Info *info;
      mm::mtl::Map<GF_OBJ_HANDLE *, Info *>::iterator found = unknown08.find(handle);
      if (found != unknown08.end()) {
        info = found->second;
      } else if (!unknown20.empty()) {
        info = unknown20.front();
        info->unknown00 = false;
        info->unknown01 = false;
        info->unknown02 = false;
        info->unknown04 = 0;
        GfObj *obj = GfObjUtil::getObj(handle);
        if (obj != nullptr) {
          info->unknown02 = obj->getComponent<GfComModel>() != nullptr;
        }
        unknown20.pop_front();
        unknown08.insert(mm::mtl::MapPair<GF_OBJ_HANDLE *, Info *>(handle, info));
      } else {
        continue;
      }
      if (info != nullptr) {
        info->unknown01 = true;
        info->unknown04--;
        if (info->unknown04 <= 0) {
          info->unknown00 = checkVisible(handle, position, info->unknown02);
          if (!info->unknown00 && !info->unknown02) {
            info->unknown04 = ml::mtRand(5) + 5;
          } else {
            info->unknown04 = 0;
          }
        }
      }
    }
  }
}

bool GfGameVisible::checkVisible(GF_OBJ_HANDLE *handle, const mm::Vec3 &position, bool isModel) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (isModel) {
    if (obj == nullptr) {
      return false;
    }
    GfComModel *model = obj->getComponent<GfComModel>();
    if (model != nullptr) {
      return model->isRender();
    }
  } else {
    if (obj == nullptr) {
      return false;
    }
    GfComVisible *visible = obj->getComponent<GfComVisible>();
    if (visible != nullptr) {
      if (visible->isRender()) {
        return true;
      }
      MsgPcGetLookPoint message;
      obj = GfObjUtil::getObj(handle);
      if (obj != nullptr) {
        bool isHandled = obj->sendMessage(obj, message);
        if (message.unknown20 && isHandled) {
          mm::Vec3 end = message.unknown10 - position;
          f32 distance = sqrtf(end.x * end.x + end.y * end.y + end.z * end.z);
          if (distance <= 30.0f) {
            fw::ColiCheckConfig config;
            config.unknown10 = 1;
            config.unknown08 = 0.0f;
            config.unknown0c = 0.0f;
            config.unknown14 = false;
            config.unknown15 = false;
            config.unknown04 = 0x80000000;
            config.unknown00 = fw::ColiCheckConfig::FLAG_UNKNOWN_0 | fw::ColiCheckConfig::FLAG_UNKNOWN_3;
            if (!end.unknown003()) {
              end.unknown001();
            }
            distance = fmaxf(distance - 0.1f, 0.0f);
            end.x = distance * end.x + position.x;
            end.y = distance * end.y + position.y;
            end.z = distance * end.z + position.z;
            fw::TColiCheckResult<256> result;
            fw::ColiCheck::testLineChara(result, position, end, config);
            return result.getCount() == 0;
          }
        }
      }
    }
  }
  return false;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameVisible>::~PtrSingleton();
template mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::node *
mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::insert(const mm::mtl::MapPair<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *> &value);
template void mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::erase(mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::node *nodePtr);
template void mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::free_node(mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::node *target, bool recursive);
template void mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::rebalance(mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::node *new_node);
template void mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::rebalance_after_erase(mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::GfGameVisible::Info *>::tree_type::node *current);
