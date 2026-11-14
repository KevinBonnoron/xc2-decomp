#include "gf/field/gf_field_collect.h"

#include <math.h>

#include "bdat.h"
#include "framework/reference_frame.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_field_skill.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_collection.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "mm_mtl/intrusive_ptr.h"

namespace gf {

// Inferred role: achievement statistics ids; original enum and enumerator names unknown.
enum unknown001 {
  unknown001_65 = 0x41,
  unknown001_66 = 0x42,
};

GfFieldCollect::GfFieldCollect(const GfSetupParam &param) : unknown19(false), unknown20(unknown020), unknown1c0(0.0f), unknown1c4(0.0f), unknown1c8(0) { create(param); }

void GfFieldCollect::seqEnd(f32) {}

void GfFieldCollect::create(const GfSetupParam &) {
  unknown08 = &GfFieldCollect::seqEnd;
  unknown18 = true;
}

GfFieldCollect::~GfFieldCollect() {}

bool GfFieldCollect::isDropitemsEmitted() const {
  u32 count = unknown30.size();
  for (u32 i = 0; i < count; i++) {
    if (!unknown30[i].m_dropitemsEmitted) {
      return false;
    }
  }
  return true;
}

void GfFieldCollect::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_UNKNOWN_1) {
    end();
  }
}

void GfFieldCollect::end() {
  unknown30.clear();
  unknown20 = unknown020;
  unknown08 = &GfFieldCollect::seqEnd;
}

void GfFieldCollect::createDropitemEmitter(const GfDropitemEmitter::CreateInfo &info) {
  unknown30.push_back(GfDropitemEmitter());
  unknown30.back().create(info);
}

void GfFieldCollect::dispose() {
  end();
  if (unknown18) {
    unknown18 = false;
  }
}

void GfFieldCollect::update(f32 deltaTime) {
  size_t count = get()->unknown30.size();
  for (size_t i = 0; i < count; i++) {
    get()->unknown30[i].update(deltaTime);
  }
  if (unknown08) {
    (this->*unknown08)(deltaTime);
  }
}

void GfFieldCollect::build(const GfSetupParam &param) {
  // __LINE__ must be 185 as in the original file: it is the line argument of operator new.
#line 185
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfFieldCollect(param);
}

void GfFieldCollect::destroy() {
  GfFieldCollect *collect = get();
  collect->dispose();
  delete collect;
}

void GfFieldCollect::update(const fw::UpdateInfo &info) {
  if (get() != nullptr && get()->unknown18) {
    get()->update(info.unknown04);
  }
}

void GfFieldCollect::seqWaitUIEnd(f32) {
  if (GfMenuFieldSkill::isRunning()) {
    return;
  }
  unknown19 = true;
  SCOM_ACHIEV_INC::addTotalCount(unknown001_65, 1);
  SCOM_ACHIEV_INC::create(unknown001_65, 1, 0);
  SCOM_ACHIEV_INC::create(unknown001_66, 1, 0);
  unknown08 = &GfFieldCollect::seqDo;
}

void GfFieldCollect::seqDo(f32) {
  unknown08 = &GfFieldCollect::seqWaitDrop;
  GfDropitemEmitter::CreateInfo info;
  gmk::GmkCollection *collection = static_cast<gmk::GmkCollection *>(gmk::getBindedGmkInst(unknown20));
  if (collection != nullptr) {
    GfObjAcc acc(get()->unknown20);
    info.unknown00 = acc.getObj()->getComponent<GfComTransform>()->getPosition();
    info.unknown00.y += collection->getData()->unknown04;
    const mm::Mat44 &matrix = acc.getObj()->getComponent<GfComTransform>()->unknown001()->getSyncedWorldMatrix();
    info.unknown10 = atan2f(matrix.rows[2][0], matrix.rows[2][2]);
    if (collection->getData()->unknown00 == 1) {
      info.unknown14 = 3.1415927f;
    } else if (collection->getData()->unknown00 == 2) {
      info.unknown14 = 1.5707964f;
    }
    u8 *collectionBdat = collection->getBindedBdatFp();
    info.unknown28 = collectionBdat;
    info.unknown30 = collection->unknown20.unknown18;
    info.unknown20 = gmk::toBdatF32(Bdat::getValCheck(collectionBdat, "initWaitTime", info.unknown30, gmk::BDAT_TYPE_UNKNOWN_8));
    info.unknown24 = gmk::toBdatF32(Bdat::getValCheck(collectionBdat, "initWaitTimeRand", info.unknown30, gmk::BDAT_TYPE_UNKNOWN_8));
  }
  createDropitemEmitter(info);
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_WILDCARD_DATA);
  f32 waitTime = Bdat::getValCheck(bdat, 0, 5, gmk::BDAT_TYPE_UNKNOWN_8).valueF32;
  f32 distance = Bdat::getValCheck(bdat, 0, 6, gmk::BDAT_TYPE_UNKNOWN_8).valueF32;
  for (u32 i = 0; i < unknown1d0.size(); i++) {
    info.unknown1c += waitTime;
    info.unknown18 = distance * (i + 1);
    createDropitemEmitter(info);
  }
}

void GfFieldCollect::seqWaitDrop(f32) {
  if (!isDropitemsEmitted()) {
    return;
  }
  gmk::GmkCollection *collection = static_cast<gmk::GmkCollection *>(gmk::getBindedGmkInst(unknown20));
  if (collection != nullptr) {
    collection->disposeIcon(true);
  }
  unknown08 = &GfFieldCollect::seqEnd;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldCollect>::~PtrSingleton();
template float mm::mtl::Delegate<float(float, float, float)>::staticFuncInvoker(const mm::mtl::Delegate<float(float, float, float)> *, float, float, float);
