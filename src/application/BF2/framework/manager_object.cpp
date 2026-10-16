#include "framework/manager_object.h"

#include "framework/manager_register.h"

namespace fw {

ManagerObject::ManagerObject() : flags(0) { ManagerRegister::get()->regist(this); }

ManagerObject::~ManagerObject() { ManagerRegister::get()->remove(this); }

} // namespace fw
