#include "framework/pointer_map.h"
#include "fw/fw_model_object.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_append_info.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_volume_fade.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace fw {
class UpdatableObject;
} // namespace fw

namespace gf {
struct GF_ASSET_HANDLE;
struct GF_MOUNT_HANDLE;

GFOBJ_MOUNT::GFOBJ_MOUNT() : m_GF_MOUNT_HANDLE(reinterpret_cast<GF_MOUNT_HANDLE *>(-1)), unknown08(-1) {}

GFOBJ_MOUNT::~GFOBJ_MOUNT() { m_appendInfo.unknown001(); }

GFOBJ_INFO::GFOBJ_INFO()
    : unknown00(0), unknown02(0), unknown04(4), unknown06(0), unknown08(unknown020), m_GF_ASSET_HANDLE(reinterpret_cast<GF_ASSET_HANDLE *>(-1)), unknown18(nullptr), unknown30(nullptr), unknown48(0),
      unknown88(unknown020), unknown90(unknown020), m_objProperty(nullptr), unknowna0(mm::Vec3::unit), unknownb0(-1), m_volumeFade(nullptr) {
  unknownb8.assign(GFOBJ_MOUNT());
  for (u32 i = 0; i < 3; i++) {
    unknown70[i] = 0;
  }
}

GFOBJ_INFO::~GFOBJ_INFO() {
  if (m_volumeFade != nullptr) {
    delete m_volumeFade;
    m_volumeFade = nullptr;
  }
  unknown20 = fw::HandlePtr<fw::UpdatableObject>();
  if (unknown30 != nullptr) {
    delete unknown30;
    unknown30 = nullptr;
  }
  if (m_objProperty != nullptr) {
    delete m_objProperty;
    m_objProperty = nullptr;
  }
  unknown00 = 0;
  unknown08 = unknown020;
  m_GF_ASSET_HANDLE = reinterpret_cast<GF_ASSET_HANDLE *>(-1);
  unknown18 = nullptr;
  for (u32 i = 0; i < 3; i++) {
    unknown70[i] = 0;
  }
  unknown88 = unknown020;
  unknown90 = unknown020;
}

void GFOBJ_INFO::createVolumeFade(GfComModel *model) {
  if (model == nullptr || model->unknown18 == nullptr || model->unknown18->getInterface() == nullptr) {
    return;
  }
  if (m_volumeFade != nullptr) {
    delete m_volumeFade;
    m_volumeFade = nullptr;
  }
#line 90
  m_volumeFade = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfVolumeFade(static_cast<GfObj *>(model->unknown08)->unknownf8, model->unknown18->getInterface());
}

} // namespace gf
