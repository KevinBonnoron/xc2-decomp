#include "framework/coli/coli_manager.h"

#include "framework/coli/coli_object.h"
#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "fw/fw_coli_check.h"
#include "idcoli/idcoli.h"
#include "ml/work_cpu.h"
#include "mtl/alloc_handle.h"

namespace fw {

ColiManager::Impl::Impl(mm::mtl::IAllocator *allocator, u32 capacity) : groundObject(nullptr), manager(nullptr), frameCount(1), allocator(allocator) {
  objectMap.reserve(allocator, capacity);
  objectMap.setRange(1, HANDLE_ID_MAX, HANDLE_ID_MAX);
  initializeContact();
}

void ColiManager::Impl::initializeContact() { contactTable.clear(); }

bool ColiManager::Impl::initialize() {
  if (manager == nullptr) {
    // __LINE__ of the game: it is the line argument of the operator new.
#line 248
    manager = new (Framework::getAllocator(), 16, __FILE__, __LINE__) idcoli::IDColiManager(Framework::get()->scn, FrameworkMemory::getMem(5), 0x80000);
  }

  return true;
}

bool ColiManager::Impl::finalize() {
  destroyContactTable();
  updateRelease();
  groundObject = nullptr;
  if (manager != nullptr) {
    delete manager;
    manager = nullptr;
  }

  return true;
}

void ColiManager::Impl::finalizeContact() { destroyContactTable(); }

void ColiManager::Impl::updateRelease() {
  for (mm::mtl::IntrusiveList<ColiObject>::iterator it = objects.begin(); it != objects.end();) {
    ColiObject *object = it.get();
    ++it;
    if (object != nullptr && object->getRefCount() == 1) {
      object->release();
    }
  }
}

void ColiManager::Impl::update() {
  if (manager != nullptr) {
    manager->update();
    frameCount++;
    updateContact();
    sendContactEvent();
  }

  for (mm::mtl::IntrusiveList<ColiObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
    it->update();
  }
}

void ColiManager::Impl::updateContact() {
  TColiCheckResult<256> result;
  for (mm::mtl::IntrusiveList<ColiObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
    ColiObject *object = it.get();
    if (!object->isChar()) {
      continue;
    }

    mm::mtl::List<ContactParam> *contacts = getContactList(object->userData.handle);
    if (object->getRefCount() == 1) {
      if (contacts != nullptr) {
        for (mm::mtl::List<ContactParam>::iterator contact = contacts->begin(); contact != contacts->end(); ++contact) {
          ContactParam &param = *contact;
          if ((param.flags & CONTACT_FLAG_CONTACTED) != 0) {
            param.flags |= CONTACT_FLAG_LEAVE;
          }
          param.flags &= ~(CONTACT_FLAG_CONTACT | CONTACT_FLAG_CONTACTED);
        }
      }
    } else {
      ColiCheckConfig config;
      config.flag14 = true;
      config.attributeMask = CONTACT_ATTRIBUTE_MASK;
      config.length = 0.0f;
      config.flag15 = false;
      config.resultMode = 2;
      config.flags = 2;
      config.margin = 0.1f;
      result.clear();
      if (ColiCheck::testObjectChara(result, object, config)) {
        makeContactList(object, result, contacts);
      }

      result.clear();
      if (ColiCheck::testObjectPhantom(result, object, config)) {
        makeContactList(object, result, contacts);
      }
    }
  }
}

void ColiManager::Impl::sendContactEvent() {
  for (ContactTable::iterator it = contactTable.begin(); it != contactTable.end(); ++it) {
    mm::mtl::List<ContactParam> *contacts = it->contacts;
    ColiObject *object = static_cast<ColiObject *>(objectMap.getPtr(it->handle));
    for (mm::mtl::List<ContactParam>::iterator contact = contacts->begin(); contact != contacts->end();) {
      ContactParam &param = *contact;
      ColiObject *other = static_cast<ColiObject *>(objectMap.getPtr(param.otherHandle));
      if (other == nullptr) {
        contact = contacts->erase(contact);
        continue;
      }

      IColiEventListener::EnterInfo enterInfo = {object, other, param.position, param.normal};
      IColiEventListener::EnterInfo otherEnterInfo = {other, object, param.position, param.normal};
      IColiEventListener::LeaveInfo leaveInfo = {object, other};
      IColiEventListener::LeaveInfo otherLeaveInfo = {other, object};
      if ((param.flags & (CONTACT_FLAG_ENTER | CONTACT_FLAG_LEAVE)) == CONTACT_FLAG_ENTER) {
        param.flags |= CONTACT_FLAG_ENTERED;
      }

      if ((param.flags & (CONTACT_FLAG_ENTERED | CONTACT_FLAG_CONTACTED | CONTACT_FLAG_CONTACT)) == (CONTACT_FLAG_ENTERED | CONTACT_FLAG_CONTACTED)) {
        param.flags |= CONTACT_FLAG_LEAVE;
      }

      if ((param.flags & CONTACT_FLAG_ENTER) != 0) {
        object->enter(enterInfo);
        if (!other->isChar()) {
          other->enter(otherEnterInfo);
        }
      }

      if ((param.flags & CONTACT_FLAG_CONTACT) != 0) {
        object->contact(enterInfo);
        if (!other->isChar()) {
          other->contact(otherEnterInfo);
        }
      }

      if ((param.flags & CONTACT_FLAG_LEAVE) != 0) {
        object->leave(leaveInfo);
        if (!other->isChar()) {
          other->leave(otherLeaveInfo);
        }
      }

      if ((param.flags & CONTACT_FLAG_CONTACT) != 0) {
        param.flags |= CONTACT_FLAG_CONTACTED;
      } else {
        param.flags &= ~CONTACT_FLAG_CONTACTED;
      }

      param.flags &= ~CONTACT_FLAG_ENTER;
      if ((param.flags & CONTACT_FLAG_LEAVE) != 0) {
        contact = contacts->erase(contact);
      } else {
        ++contact;
      }

      param.flags &= ~(CONTACT_FLAG_ENTER | CONTACT_FLAG_CONTACT | CONTACT_FLAG_LEAVE);
    }
  }
}

void ColiManager::Impl::postUpdate() {
  updateRelease();
  for (mm::mtl::IntrusiveList<ColiObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
    it->postUpdate();
  }

  if (manager != nullptr) {
    manager->consistentUpdate();
  }
}

void ColiManager::Impl::tail() {
  if (manager != nullptr) {
    manager->tail();
  }
}

u32 ColiManager::Impl::getFrameCount() const { return ml::WorkCpu::getFrameCount(); }

void ColiManager::Impl::destroyContactTable() {
  for (ContactTable::iterator it = contactTable.begin(); it != contactTable.end(); ++it) {
    mm::mtl::List<ContactParam> *contacts = it->contacts;
    contacts->clear();
    delete contacts;
  }

  contactTable.clear();
}

mm::mtl::List<ColiManager::Impl::ContactParam> *ColiManager::Impl::getContactList(u32 handle) {
  for (ContactTable::iterator it = contactTable.begin(); it != contactTable.end(); ++it) {
    if (it->handle == handle) {
      return it->contacts;
    }
  }

  return nullptr;
}

ColiObject *ColiManager::Impl::getObject(u32 handle, bool isCheck) const {
  if (isCheck && !objectMap.isValid(handle)) {
    return nullptr;
  }

  return static_cast<ColiObject *>(objectMap.getPtr(handle));
}

bool ColiManager::Impl::isContactList(mm::mtl::List<ContactParam> &contacts, u32 handle) {
  for (mm::mtl::List<ContactParam>::iterator contact = contacts.begin(); contact != contacts.end(); ++contact) {
    if ((*contact).otherHandle == handle) {
      return true;
    }
  }

  return false;
}

void ColiManager::Impl::sendRemoveEvent(u32 handle) {
  ColiObject *object = static_cast<ColiObject *>(objectMap.getPtr(handle));
  if (object == nullptr) {
    return;
  }

  for (ContactTable::iterator it = contactTable.begin(); it != contactTable.end(); ++it) {
    mm::mtl::List<ContactParam> *contacts = it->contacts;
    if (it->handle == handle) {
      for (mm::mtl::List<ContactParam>::iterator contact = contacts->begin(); contact != contacts->end(); ++contact) {
        ColiObject *other = static_cast<ColiObject *>(objectMap.getPtr((*contact).otherHandle));
        IColiEventListener::LeaveInfo leaveInfo = {object, other};
        IColiEventListener::LeaveInfo otherLeaveInfo = {other, object};
        if (((*contact).flags & CONTACT_FLAG_ENTER) != 0) {
          object->leave(leaveInfo);
          other->leave(otherLeaveInfo);
        }
      }
      return;
    }

    ColiObject *owner = static_cast<ColiObject *>(objectMap.getPtr(it->handle));
    for (mm::mtl::List<ContactParam>::iterator contact = contacts->begin(); contact != contacts->end();) {
      if ((*contact).otherHandle == handle) {
        IColiEventListener::LeaveInfo leaveInfo = {owner, object};
        IColiEventListener::LeaveInfo otherLeaveInfo = {object, owner};
        owner->leave(leaveInfo);
        object->leave(otherLeaveInfo);
        contact = contacts->erase(contact);
      } else {
        ++contact;
      }
    }
  }
}

bool ColiManager::Impl::isValidObject(u32 handle) { return objectMap.isValid(handle); }

void ColiManager::Impl::registObject(ColiObject *object) {
  object->setHandle(objectMap.regist(object) | HANDLE_FLAG);
  object->addRef();
  objects.push_back(object);
  if (object->isGrand()) {
    groundObject = object;
  }

  if (object->isChar()) {
    // __LINE__ of the game: it is the line argument of the operator new.
#line 771
    mm::mtl::List<ContactParam> *contacts = new (allocator, 16, __FILE__, __LINE__) mm::mtl::List<ContactParam>(allocator);
    contacts->reserve(CONTACT_LIST_RESERVE);
    contactTable.push_back(ListParam(object->userData.handle, contacts));
  }
}

void ColiManager::Impl::removeObject(ColiObject *object) {
  for (ContactTable::iterator it = contactTable.begin(); it != contactTable.end(); ++it) {
    if (it->handle == object->userData.handle) {
      mm::mtl::List<ContactParam> *contacts = it->contacts;
      contactTable.erase(it);
      contacts->clear();
      delete contacts;
      break;
    }
  }

  if (object->userData.handle != 0) {
    objectMap.remove(object->userData.handle);
  }

  objects.erase(object);
  if (groundObject == object) {
    groundObject = nullptr;
  }
}

void ColiManager::Impl::cleanupObject(ColiObject *object) { sendRemoveEvent(object->userData.handle); }

void ColiManager::Impl::openDebugWindow() {
  if (manager != nullptr) {
    manager->openDebugWindow(Framework::get()->winProc);
  }
}

bool ColiManager::Impl::isGblId(u32 id) {
  if (manager == nullptr) {
    return false;
  }

  return manager->isGblId(id) == 0;
}

void ColiManager::Impl::setGblId(u32 id, bool isGlobal) {
  if (manager != nullptr) {
    manager->setGblId(id, isGlobal);
  }
}

void *ColiManager::Impl::getGblIdTbl() {
  if (manager != nullptr) {
    return manager->getGblIdTbl();
  }

  return nullptr;
}

ColiManager::ColiManager(mm::mtl::IAllocator *allocator, u32 capacity)
// __LINE__ of the game: it is the line argument of the operator new.
#line 884
    : impl(new (allocator, 8, __FILE__, __LINE__) Impl(allocator, capacity)) {
}

ColiManager::~ColiManager() {}

bool ColiManager::initialize() { return impl->initialize(); }

bool ColiManager::finalize() { return impl->finalize(); }

void ColiManager::update() {
  if (isFinalized()) {
    return;
  }

  impl->update();
}

void ColiManager::postUpdate() {
  if (isFinalized()) {
    return;
  }

  impl->postUpdate();
}

void ColiManager::tail() {
  if (isFinalized()) {
    return;
  }

  impl->tail();
}

void ColiManager::registObject(ColiObject *object) { impl->registObject(object); }

void ColiManager::removeObject(ColiObject *object) { impl->removeObject(object); }

void ColiManager::cleanupObject(ColiObject *object) { impl->cleanupObject(object); }

const idcoli::IDColiManager *ColiManager::getInterface() const { return impl->manager; }

idcoli::IDColiManager *ColiManager::getInterface() { return impl->manager; }

void ColiManager::openDebugWindow() { impl->openDebugWindow(); }

ColiObject *ColiManager::getGroundObject() { return impl->groundObject; }

ColiObject *ColiManager::getObject(u32 handle) const {
  const PointerMap &objectMap = impl->objectMap;
  if (objectMap.isValid(handle)) {
    return static_cast<ColiObject *>(objectMap.getPtr(handle));
  }

  return nullptr;
}

bool ColiManager::isGblId(u32 id) { return impl->isGblId(id); }

void ColiManager::setGblId(u32 id, bool isGlobal) { impl->setGblId(id, isGlobal); }

void *ColiManager::getGblIdTbl() { return impl->getGblIdTbl(); }

} // namespace fw
