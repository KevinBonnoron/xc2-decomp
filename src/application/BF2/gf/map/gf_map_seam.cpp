#include "gf/map/gf_map_seam.h"

#include "fw/fw_model_object.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "mm_mtl/rtti.h"
#include "scn/scn_obj_model_dr_sys.h"

namespace gf {

MapSeam::~MapSeam() {}

void MapSeam::create(GF_ASSET_HANDLE *handle) {
  if (unknown00 == INVALID_HANDLE) {
    GF_OBJ_HANDLE *objHandle = GfAssetManager::getObj(handle);
    GFOBJ_INFO *info = GfObjManager::getObjInfo(objHandle);
    if (info != nullptr && info->unknown30 != nullptr) {
      GfObj *obj = info->unknown18;
      if (info->unknown30->unknown08 == obj->unknown28 && obj->unknown28 == OBJECT_TYPE_MAP) {
        GfObjSetupMap *setup = mm::mtl::dynamicCast<GfObjSetupMap>(info->unknown30);
        if (setup != nullptr && setup->unknown75) {
          unknown00 = objHandle;
        }
      }
    }
  }
}

void MapSeam::destroy() { unknown00 = INVALID_HANDLE; }

ml::ScnObjModel *MapSeam::getModel() const {
  GfObjAcc acc(unknown00);
  if (acc.isValidModel()) {
    return acc.getObj()->getComponent<GfComModel>()->unknown18->getInterface();
  }
  return nullptr;
}

ml::DrMdlObj *MapSeam::getDrModel() const {
  if (unknown00 != INVALID_HANDLE) {
    return static_cast<ml::ScnObjModelDrSys *>(getModel())->unknown3d8;
  }
  return nullptr;
}

} // namespace gf
