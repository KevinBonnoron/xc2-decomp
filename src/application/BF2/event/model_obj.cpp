#include "event/model_obj.h"

#include "dr/dr_stm_read_obj.h"
#include "event/extend.h"
#include "event/res_manager.h"
#include "fw/fw_transform.h"
#include "gf/event/gf_evt_model.h"
#include "gf/object/component/effect/gf_com_effect_caster.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"
#include "scn/scn_obj_acc.h"

namespace event {

ModelObj::ModelObj() : unknown0c(KIND_UNKNOWN_3), unknown10(0), unknown14(0), unknown5c(0), unknown118(nullptr), unknown120(gf::unknown020), unknown128(nullptr), unknown130(-1), unknown134(0) {
  unknown08 = FLAG_UNKNOWN_1;
}

ModelObj::ModelObj(const char *path, bool isPriority, u32 id)
    : unknown08(0), unknown0c(KIND_UNKNOWN_0), unknown10(0), unknown14(0), unknown18(path), unknown5c(id), unknown118(nullptr), unknown120(gf::unknown020), unknown128(nullptr), unknown130(-1),
      unknown134(0) {
  if (isPriority) {
    unknown08 |= FLAG_UNKNOWN_0;
  } else {
    unknown08 &= ~FLAG_UNKNOWN_0;
  }
  mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->mdo(path), this, false);
  unknown08 |= FLAG_UNKNOWN_2;
  mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->arc(path), this, false);
  unknown08 |= FLAG_UNKNOWN_3;
  unknown118 = ml::ScnObjAccStmReadObj::create(path);
  ml::ScnObjAccStmReadObj acc(unknown118);
  acc.readType(ml::ScnObjAccStmReadObj::READ_TYPE_UNKNOWN_0);
  acc.readType(ml::ScnObjAccStmReadObj::READ_TYPE_UNKNOWN_1);
}

ModelObj::ModelObj(const char *path, const DESC &desc, bool isPriority, u32 id)
    : unknown08(0), unknown0c(KIND_UNKNOWN_1), unknown10(0), unknown14(0), unknown18(path), unknown5c(id), unknown118(nullptr), unknown120(gf::unknown020), unknown128(nullptr), unknown130(-1),
      unknown134(0) {
  unknown60 = desc;
  if (isPriority) {
    unknown08 |= FLAG_UNKNOWN_0;
  } else {
    unknown08 &= ~FLAG_UNKNOWN_0;
  }
  setupModel(unknown60);
}

ModelObj::ModelObj(MODEL_TYPE type, u32 modelId, const OPTION &option, bool isPriority, u32 id)
    : unknown0c(KIND_UNKNOWN_2), unknown10(type), unknown14(modelId), unknown5c(id), unknown118(nullptr), unknown120(gf::unknown020), unknown128(nullptr), unknown130(-1), unknown134(0) {
  unknown08 = isPriority;
  unknown110 = option;
  setupModel(type, modelId, unknown110);
}

ModelObj::~ModelObj() {
  mm::mtl::safeRelease(unknown128);
  if (unknown118 != nullptr) {
    unknown118->release();
    unknown118 = nullptr;
  }
}

bool ModelObj::getEfpMat(mm::Mat44 &mat, const char *name) const {
  mat = mm::Mat44::identity;
  gf::GfObj *actor = gf::GfObjUtil::getObj(unknown120);
  gf::GfComTransform *transform = actor->getComponent<gf::GfComTransform>();
  if (!transform) {
    return false;
  }
  gf::GfComEffectCaster *caster = actor->getComponent<gf::GfComEffectCaster>();
  if (!caster || !caster->getEfpMatrix(name, mat)) {
    return false;
  }
  mm::Vec3 rotation = mm::quatToEuler(transform->getRotation());
  mm::Vec3 position = transform->getPosition();
  mm::Mat44 world;
  world.setRotXYZ(rotation);
  world.setTrans(position);
  mat = mat * world.unknown003();
  return true;
}

bool ModelObj::getBoneMat(mm::Mat44 &mat, const char *name) const {
  mat = mm::Mat44::identity;
  gf::GfObjAcc actor(unknown120);
  int bone = actor.getBoneIdx(name);
  if (bone < 0) {
    return false;
  }
  fw::Transform boneTransform;
  if (!actor.getBoneTransform(boneTransform, bone)) {
    return false;
  }
  boneTransform.unknown001(mat);
  gf::GfComTransform *transform = gf::GfObjUtil::getObj(unknown120)->getComponent<gf::GfComTransform>();
  mm::Vec3 rotation = mm::quatToEuler(transform->getRotation());
  mm::Vec3 position = transform->getPosition();
  mm::Mat44 world;
  world.setRotXYZ(rotation);
  world.setTrans(position);
  mat = mat * world.unknown003();
  return true;
}

void ModelObj::setReserve(u32 index, bool isReserve) {
  if (isReserve) {
    unknown134 |= 1 << index;
  } else {
    unknown134 &= ~(1 << index);
  }
}

bool ModelObj::isReserve(int index) { return (unknown134 & (index >= 0 ? 1 << index : 0x7fffffff)) != 0; }

bool ModelObj::isSame(const char *path, bool isPriority, u32 id) {
  if (unknown0c != KIND_UNKNOWN_0) {
    return false;
  }
  if (__builtin_strcmp(this->unknown18.c_str(), path) != 0) {
    return false;
  }
  if (((unknown08 & FLAG_UNKNOWN_0) != 0) != isPriority) {
    return false;
  }
  return unknown5c == id;
}

bool ModelObj::isSame(const char *path, const DESC &desc, bool isPriority, u32 id) {
  if (unknown0c != KIND_UNKNOWN_1) {
    return false;
  }
  if (__builtin_strcmp(this->unknown18.c_str(), path) != 0) {
    return false;
  }
  if (__builtin_strcmp(unknown60.unknown00.c_str(), desc.unknown00.c_str()) != 0) {
    return false;
  }
  if (unknown60.unknown48 != desc.unknown48 || unknown60.unknown50 != desc.unknown50) {
    return false;
  }
  if (__builtin_strcmp(unknown60.unknown58.c_str(), desc.unknown58.c_str()) != 0) {
    return false;
  }
  if (unknown60.unknowna0 != desc.unknowna0 || unknown60.unknowna8 != desc.unknowna8) {
    return false;
  }
  if (((unknown08 & FLAG_UNKNOWN_0) != 0) != isPriority) {
    return false;
  }
  return unknown5c == id;
}

bool ModelObj::isSame(MODEL_TYPE type, u32 modelId, const OPTION &option, bool isPriority, u32 id) {
  if (unknown0c != KIND_UNKNOWN_2) {
    return false;
  }
  if (unknown10 != type || unknown14 != modelId) {
    return false;
  }
  if (unknown110.unknown00 != option.unknown00 || unknown110.unknown04 != option.unknown04 || unknown110.unknown05 != option.unknown05) {
    return false;
  }
  if (((unknown08 & FLAG_UNKNOWN_0) != 0) != isPriority) {
    return false;
  }
  return unknown5c == id;
}

bool ModelObj::isBusy() const {
  if ((unknown08 & 0xc) != 0) {
    return true;
  }
  if (unknown130 >= 0) {
    return true;
  }
  if (unknown128 != nullptr) {
    if (unknown128->isBusy(nullptr)) {
      return true;
    }
  }
  return false;
}

void ModelObj::update() {
  if (unknown128 != nullptr) {
    if (unknown130 >= 0) {
      unknown130--;
    }
    if (unknown128->isBusy(nullptr)) {
      unknown130 = 2;
    }
  }
}

bool ModelObj::isSame() {
  if (unknown0c != KIND_UNKNOWN_3) {
    return false;
  }
  return (unknown08 & FLAG_UNKNOWN_1) != 0;
}

void ModelObj::OnResEvent(const PARAM &param) {
  if (__builtin_strcmp(param.path, mm::mtl::Singleton<Extend>::getPtr()->mdo(unknown18.c_str())) == 0) {
    if (param.result == RES_RESULT_TYPE_UNKNOWN_3) {
      unknown60.unknown00 = mm::mtl::Singleton<Extend>::getPtr()->mdo(unknown18.c_str());
      unknown60.unknown48 = param.adr;
      unknown60.unknown50 = param.size;
    }
    unknown08 &= ~FLAG_UNKNOWN_2;
  } else if (__builtin_strcmp(param.path, mm::mtl::Singleton<Extend>::getPtr()->arc(unknown18.c_str())) == 0) {
    unknown60.unknown58 = mm::mtl::Singleton<Extend>::getPtr()->arc(unknown18.c_str());
    unknown60.unknowna0 = param.adr;
    unknown60.unknowna8 = param.size;
    unknown08 &= ~FLAG_UNKNOWN_3;
  }
  if ((unknown08 & (FLAG_UNKNOWN_2 | FLAG_UNKNOWN_3)) == 0 && unknown60.unknown48 != nullptr) {
    setupModel(unknown60);
  }
}

} // namespace event
