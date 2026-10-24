#include "gf/object/gf_obj_property.h"

#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

GfObjPropertyMap *GfObjProperty::getMap() { return GfObjUtil::getObjType(handle) == OBJECT_TYPE_MAP ? static_cast<GfObjPropertyMap *>(this) : nullptr; }

GfObjPropertyDriver *GfObjProperty::getDriver() { return GfObjUtil::getObjType(handle) == OBJECT_TYPE_DRIVER ? static_cast<GfObjPropertyDriver *>(this) : nullptr; }

GfObjPropertyBlade *GfObjProperty::getBlade() { return GfObjUtil::getObjType(handle) == OBJECT_TYPE_BLADE ? static_cast<GfObjPropertyBlade *>(this) : nullptr; }

GfObjPropertyPcWeapon *GfObjProperty::getPcWeapon() { return GfObjUtil::getObjType(handle) == OBJECT_TYPE_PC_WEAPON ? static_cast<GfObjPropertyPcWeapon *>(this) : nullptr; }

GfObjPropertyEnWeapon *GfObjProperty::getEnWeapon() { return GfObjUtil::getObjType(handle) == OBJECT_TYPE_EN_WEAPON ? static_cast<GfObjPropertyEnWeapon *>(this) : nullptr; }

GfObjPropertyBelonging *GfObjProperty::getBelonging() { return GfObjUtil::getObjType(handle) == OBJECT_TYPE_BELONGING ? static_cast<GfObjPropertyBelonging *>(this) : nullptr; }

GfObjPropertyEnemy *GfObjProperty::getEnemy() { return GfObjUtil::getObjType(handle) == OBJECT_TYPE_ENEMY ? static_cast<GfObjPropertyEnemy *>(this) : nullptr; }

GfObjPropertyNpc *GfObjProperty::getNpc() { return GfObjUtil::getObjType(handle) == OBJECT_TYPE_NPC ? static_cast<GfObjPropertyNpc *>(this) : nullptr; }

GfObjPropertyMob *GfObjProperty::getMob() { return GfObjUtil::getObjType(handle) == OBJECT_TYPE_MOB ? static_cast<GfObjPropertyMob *>(this) : nullptr; }

GfObjPropertyGimmick *GfObjProperty::getGimmick() { return GfObjUtil::getObjType(handle) == OBJECT_TYPE_GIMMICK ? static_cast<GfObjPropertyGimmick *>(this) : nullptr; }

GfObjPropertyFobj *GfObjProperty::getFobj() { return GfObjUtil::getObjType(handle) == OBJECT_TYPE_FOBJ ? static_cast<GfObjPropertyFobj *>(this) : nullptr; }

GfObjPropertyEvent *GfObjProperty::getEvent() { return GfObjUtil::getObjType(handle) == OBJECT_TYPE_EVENT ? static_cast<GfObjPropertyEvent *>(this) : nullptr; }

GfObjPropertyUi *GfObjProperty::getUi() { return GfObjUtil::getObjType(handle) == OBJECT_TYPE_UI ? static_cast<GfObjPropertyUi *>(this) : nullptr; }

} // namespace gf
