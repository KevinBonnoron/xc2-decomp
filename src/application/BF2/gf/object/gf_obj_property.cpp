#include "gf/object/gf_obj_property.h"

#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

// __LINE__ must be 26 to 52 as in the original file: they are the line arguments of the allocations.
#line 23
GfObjProperty *GfObjProperty::create(GF_OBJ_HANDLE *handle) {
  switch (GfObjUtil::getObjType(handle)) {
  case OBJECT_TYPE_MAP:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyMap(handle);
  case OBJECT_TYPE_PC:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyDriver(handle);
  case OBJECT_TYPE_BLADE:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyBlade(handle);
  case OBJECT_TYPE_ENEMY:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyEnemy(handle);
  case OBJECT_TYPE_NPC:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyNpc(handle);
  case OBJECT_TYPE_MOB:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyMob(handle);
  case OBJECT_TYPE_GIMMICK:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyGimmick(handle);
  case OBJECT_TYPE_FIELD_OBJ:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyFobj(handle);
  case OBJECT_TYPE_PC_WEAPON:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyPcWeapon(handle);
  case OBJECT_TYPE_EVENT_OBJ:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyEvent(handle);
  case OBJECT_TYPE_EN_WEAPON:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyEnWeapon(handle);
  case OBJECT_TYPE_OPTION:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyBelonging(handle);
  case OBJECT_TYPE_EXTRA:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyExtra(handle);
  case OBJECT_TYPE_UI_OBJ:
    return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjPropertyUi(handle);
  default:
    return nullptr;
  }
}

GfObjPropertyMap *GfObjProperty::getMap() { return GfObjUtil::getObjType(unknown08) == OBJECT_TYPE_MAP ? static_cast<GfObjPropertyMap *>(this) : nullptr; }

GfObjPropertyDriver *GfObjProperty::getDriver() { return GfObjUtil::getObjType(unknown08) == OBJECT_TYPE_PC ? static_cast<GfObjPropertyDriver *>(this) : nullptr; }

GfObjPropertyBlade *GfObjProperty::getBlade() { return GfObjUtil::getObjType(unknown08) == OBJECT_TYPE_BLADE ? static_cast<GfObjPropertyBlade *>(this) : nullptr; }

GfObjPropertyPcWeapon *GfObjProperty::getPcWeapon() { return GfObjUtil::getObjType(unknown08) == OBJECT_TYPE_PC_WEAPON ? static_cast<GfObjPropertyPcWeapon *>(this) : nullptr; }

GfObjPropertyEnWeapon *GfObjProperty::getEnWeapon() { return GfObjUtil::getObjType(unknown08) == OBJECT_TYPE_EN_WEAPON ? static_cast<GfObjPropertyEnWeapon *>(this) : nullptr; }

GfObjPropertyBelonging *GfObjProperty::getBelonging() { return GfObjUtil::getObjType(unknown08) == OBJECT_TYPE_OPTION ? static_cast<GfObjPropertyBelonging *>(this) : nullptr; }

GfObjPropertyEnemy *GfObjProperty::getEnemy() { return GfObjUtil::getObjType(unknown08) == OBJECT_TYPE_ENEMY ? static_cast<GfObjPropertyEnemy *>(this) : nullptr; }

GfObjPropertyNpc *GfObjProperty::getNpc() { return GfObjUtil::getObjType(unknown08) == OBJECT_TYPE_NPC ? static_cast<GfObjPropertyNpc *>(this) : nullptr; }

GfObjPropertyMob *GfObjProperty::getMob() { return GfObjUtil::getObjType(unknown08) == OBJECT_TYPE_MOB ? static_cast<GfObjPropertyMob *>(this) : nullptr; }

GfObjPropertyGimmick *GfObjProperty::getGimmick() { return GfObjUtil::getObjType(unknown08) == OBJECT_TYPE_GIMMICK ? static_cast<GfObjPropertyGimmick *>(this) : nullptr; }

GfObjPropertyFobj *GfObjProperty::getFobj() { return GfObjUtil::getObjType(unknown08) == OBJECT_TYPE_FIELD_OBJ ? static_cast<GfObjPropertyFobj *>(this) : nullptr; }

GfObjPropertyEvent *GfObjProperty::getEvent() { return GfObjUtil::getObjType(unknown08) == OBJECT_TYPE_EVENT_OBJ ? static_cast<GfObjPropertyEvent *>(this) : nullptr; }

GfObjPropertyUi *GfObjProperty::getUi() { return GfObjUtil::getObjType(unknown08) == OBJECT_TYPE_UI_OBJ ? static_cast<GfObjPropertyUi *>(this) : nullptr; }

} // namespace gf
