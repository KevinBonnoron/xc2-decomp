#include "framework/coli/coli_manager.h"

#include "framework/coli/coli_object.h"
#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "fw/fw_coli_check.h"
#include "idcoli/idcoli.h"
#include "ml/work_cpu.h"
#include "mtl/alloc_handle.h"

namespace fw {

ColiManager::Impl::Impl(mm::mtl::IAllocator *allocator, u32 capacity) : unknown18(nullptr), unknown20(nullptr), unknown28(1), unknown30(allocator) {
  unknown38.reserve(allocator, capacity);
  unknown38.setRange(1, HANDLE_ID_MAX, HANDLE_ID_MAX);
  initializeContact();
}

void ColiManager::Impl::initializeContact() { unknown70.clear(); }

bool ColiManager::Impl::initialize() {
  if (unknown20 == nullptr) {
    // __LINE__ of the game: it is the line argument of the operator new.
#line 248
    unknown20 = new (Framework::getAllocator(), 16, __FILE__, __LINE__) idcoli::IDColiManager(Framework::get()->unknown58, FrameworkMemory::getMem(5), 0x80000);
  }

  return true;
}

bool ColiManager::Impl::finalize() {
  destroyContactTable();
  updateRelease();
  unknown18 = nullptr;
  if (unknown20 != nullptr) {
    delete unknown20;
    unknown20 = nullptr;
  }

  return true;
}

void ColiManager::Impl::finalizeContact() { destroyContactTable(); }

void ColiManager::Impl::updateRelease() {
  for (mm::mtl::IntrusiveList<ColiObject>::iterator it = unknown00.begin(); it != unknown00.end();) {
    ColiObject *object = it.get();
    ++it;
    if (object != nullptr && object->getRefCount() == 1) {
      object->release();
    }
  }
}

void ColiManager::Impl::update() {
  if (unknown20 != nullptr) {
    unknown20->update();
    unknown28++;
    updateContact();
    sendContactEvent();
  }

  for (mm::mtl::IntrusiveList<ColiObject>::iterator it = unknown00.begin(); it != unknown00.end(); ++it) {
    it->update();
  }
}

void ColiManager::Impl::updateContact() {
  TColiCheckResult<256> result;
  for (mm::mtl::IntrusiveList<ColiObject>::iterator it = unknown00.begin(); it != unknown00.end(); ++it) {
    ColiObject *object = it.get();
    if (!object->isChar()) {
      continue;
    }

    mm::mtl::List<ContactParam> *contacts = getContactList(object->unknownf0.unknown08);
    if (object->getRefCount() == 1) {
      if (contacts != nullptr) {
        for (mm::mtl::List<ContactParam>::iterator contact = contacts->begin(); contact != contacts->end(); ++contact) {
          ContactParam &param = *contact;
          if ((param.unknown38 & CONTACT_FLAG_CONTACTED) != 0) {
            param.unknown38 |= CONTACT_FLAG_LEAVE;
          }
          param.unknown38 &= ~(CONTACT_FLAG_CONTACT | CONTACT_FLAG_CONTACTED);
        }
      }
    } else {
      ColiCheckConfig config;
      config.unknown14 = true;
      config.unknown04 = CONTACT_ATTRIBUTE_MASK;
      config.unknown08 = 0.0f;
      config.unknown15 = false;
      config.unknown10 = 2;
      config.unknown00 = 2;
      config.unknown0c = 0.1f;
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
  for (ContactTable::iterator it = unknown70.begin(); it != unknown70.end(); ++it) {
    mm::mtl::List<ContactParam> *contacts = it->unknown08;
    ColiObject *object = static_cast<ColiObject *>(unknown38.getPtr(it->unknown00));
    for (mm::mtl::List<ContactParam>::iterator contact = contacts->begin(); contact != contacts->end();) {
      ContactParam &param = *contact;
      ColiObject *other = static_cast<ColiObject *>(unknown38.getPtr(param.unknown34));
      if (other == nullptr) {
        contact = contacts->erase(contact);
        continue;
      }

      IColiEventListener::EnterInfo enterInfo = {object, other, param.unknown00, param.unknown20};
      IColiEventListener::EnterInfo otherEnterInfo = {other, object, param.unknown00, param.unknown20};
      IColiEventListener::LeaveInfo leaveInfo = {object, other};
      IColiEventListener::LeaveInfo otherLeaveInfo = {other, object};
      if ((param.unknown38 & (CONTACT_FLAG_ENTER | CONTACT_FLAG_LEAVE)) == CONTACT_FLAG_ENTER) {
        param.unknown38 |= CONTACT_FLAG_ENTERED;
      }

      if ((param.unknown38 & (CONTACT_FLAG_ENTERED | CONTACT_FLAG_CONTACTED | CONTACT_FLAG_CONTACT)) == (CONTACT_FLAG_ENTERED | CONTACT_FLAG_CONTACTED)) {
        param.unknown38 |= CONTACT_FLAG_LEAVE;
      }

      if ((param.unknown38 & CONTACT_FLAG_ENTER) != 0) {
        object->enter(enterInfo);
        if (!other->isChar()) {
          other->enter(otherEnterInfo);
        }
      }

      if ((param.unknown38 & CONTACT_FLAG_CONTACT) != 0) {
        object->contact(enterInfo);
        if (!other->isChar()) {
          other->contact(otherEnterInfo);
        }
      }

      if ((param.unknown38 & CONTACT_FLAG_LEAVE) != 0) {
        object->leave(leaveInfo);
        if (!other->isChar()) {
          other->leave(otherLeaveInfo);
        }
      }

      if ((param.unknown38 & CONTACT_FLAG_CONTACT) != 0) {
        param.unknown38 |= CONTACT_FLAG_CONTACTED;
      } else {
        param.unknown38 &= ~CONTACT_FLAG_CONTACTED;
      }

      param.unknown38 &= ~CONTACT_FLAG_ENTER;
      if ((param.unknown38 & CONTACT_FLAG_LEAVE) != 0) {
        contact = contacts->erase(contact);
      } else {
        ++contact;
      }

      param.unknown38 &= ~(CONTACT_FLAG_ENTER | CONTACT_FLAG_CONTACT | CONTACT_FLAG_LEAVE);
    }
  }
}

void ColiManager::Impl::postUpdate() {
  updateRelease();
  for (mm::mtl::IntrusiveList<ColiObject>::iterator it = unknown00.begin(); it != unknown00.end(); ++it) {
    it->postUpdate();
  }

  if (unknown20 != nullptr) {
    unknown20->consistentUpdate();
  }
}

void ColiManager::Impl::tail() {
  if (unknown20 != nullptr) {
    unknown20->tail();
  }
}

u32 ColiManager::Impl::getFrameCount() const { return ml::WorkCpu::getFrameCount(); }

void ColiManager::Impl::destroyContactTable() {
  for (ContactTable::iterator it = unknown70.begin(); it != unknown70.end(); ++it) {
    mm::mtl::List<ContactParam> *contacts = it->unknown08;
    contacts->clear();
    delete contacts;
  }

  unknown70.clear();
}

mm::mtl::List<ColiManager::Impl::ContactParam> *ColiManager::Impl::getContactList(u32 handle) {
  for (ContactTable::iterator it = unknown70.begin(); it != unknown70.end(); ++it) {
    if (it->unknown00 == handle) {
      return it->unknown08;
    }
  }

  return nullptr;
}

ColiObject *ColiManager::Impl::getObject(u32 handle, bool isCheck) const {
  if (isCheck && !unknown38.isValid(handle)) {
    return nullptr;
  }

  return static_cast<ColiObject *>(unknown38.getPtr(handle));
}

bool ColiManager::Impl::isContactList(mm::mtl::List<ContactParam> &contacts, u32 handle) {
  for (mm::mtl::List<ContactParam>::iterator contact = contacts.begin(); contact != contacts.end(); ++contact) {
    if ((*contact).unknown34 == handle) {
      return true;
    }
  }

  return false;
}

void ColiManager::Impl::sendRemoveEvent(u32 handle) {
  ColiObject *object = static_cast<ColiObject *>(unknown38.getPtr(handle));
  if (object == nullptr) {
    return;
  }

  for (ContactTable::iterator it = unknown70.begin(); it != unknown70.end(); ++it) {
    mm::mtl::List<ContactParam> *contacts = it->unknown08;
    if (it->unknown00 == handle) {
      for (mm::mtl::List<ContactParam>::iterator contact = contacts->begin(); contact != contacts->end(); ++contact) {
        ColiObject *other = static_cast<ColiObject *>(unknown38.getPtr((*contact).unknown34));
        IColiEventListener::LeaveInfo leaveInfo = {object, other};
        IColiEventListener::LeaveInfo otherLeaveInfo = {other, object};
        if (((*contact).unknown38 & CONTACT_FLAG_ENTER) != 0) {
          object->leave(leaveInfo);
          other->leave(otherLeaveInfo);
        }
      }
      return;
    }

    ColiObject *owner = static_cast<ColiObject *>(unknown38.getPtr(it->unknown00));
    for (mm::mtl::List<ContactParam>::iterator contact = contacts->begin(); contact != contacts->end();) {
      if ((*contact).unknown34 == handle) {
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

bool ColiManager::Impl::isValidObject(u32 handle) { return unknown38.isValid(handle); }

void ColiManager::Impl::registObject(ColiObject *object) {
  object->setHandle(unknown38.regist(object) | HANDLE_FLAG);
  object->addRef();
  unknown00.push_back(object);
  if (object->isGrand()) {
    unknown18 = object;
  }

  if (object->isChar()) {
    // __LINE__ of the game: it is the line argument of the operator new.
#line 771
    mm::mtl::List<ContactParam> *contacts = new (unknown30, 16, __FILE__, __LINE__) mm::mtl::List<ContactParam>(unknown30);
    contacts->reserve(CONTACT_LIST_RESERVE);
    unknown70.push_back(ListParam(object->unknownf0.unknown08, contacts));
  }
}

void ColiManager::Impl::removeObject(ColiObject *object) {
  for (ContactTable::iterator it = unknown70.begin(); it != unknown70.end(); ++it) {
    if (it->unknown00 == object->unknownf0.unknown08) {
      mm::mtl::List<ContactParam> *contacts = it->unknown08;
      unknown70.erase(it);
      contacts->clear();
      delete contacts;
      break;
    }
  }

  if (object->unknownf0.unknown08 != 0) {
    unknown38.remove(object->unknownf0.unknown08);
  }

  unknown00.erase(object);
  if (unknown18 == object) {
    unknown18 = nullptr;
  }
}

void ColiManager::Impl::cleanupObject(ColiObject *object) { sendRemoveEvent(object->unknownf0.unknown08); }

void ColiManager::Impl::openDebugWindow() {
  if (unknown20 != nullptr) {
    unknown20->openDebugWindow(Framework::get()->unknown50);
  }
}

bool ColiManager::Impl::isGblId(u32 id) {
  if (unknown20 == nullptr) {
    return false;
  }

  return unknown20->isGblId(id) == 0;
}

void ColiManager::Impl::setGblId(u32 id, bool isGlobal) {
  if (unknown20 != nullptr) {
    unknown20->setGblId(id, isGlobal);
  }
}

void *ColiManager::Impl::getGblIdTbl() {
  if (unknown20 != nullptr) {
    return unknown20->getGblIdTbl();
  }

  return nullptr;
}

ColiManager::ColiManager(mm::mtl::IAllocator *allocator, u32 capacity)
// __LINE__ of the game: it is the line argument of the operator new.
#line 884
    : unknown18(new (allocator, 8, __FILE__, __LINE__) Impl(allocator, capacity)) {
}

ColiManager::~ColiManager() {}

bool ColiManager::initialize() { return unknown18->initialize(); }

bool ColiManager::finalize() { return unknown18->finalize(); }

void ColiManager::update() {
  if (isFinalized()) {
    return;
  }

  unknown18->update();
}

void ColiManager::postUpdate() {
  if (isFinalized()) {
    return;
  }

  unknown18->postUpdate();
}

void ColiManager::tail() {
  if (isFinalized()) {
    return;
  }

  unknown18->tail();
}

void ColiManager::registObject(ColiObject *object) { unknown18->registObject(object); }

void ColiManager::removeObject(ColiObject *object) { unknown18->removeObject(object); }

void ColiManager::cleanupObject(ColiObject *object) { unknown18->cleanupObject(object); }

const idcoli::IDColiManager *ColiManager::getInterface() const { return unknown18->unknown20; }

idcoli::IDColiManager *ColiManager::getInterface() { return unknown18->unknown20; }

void ColiManager::openDebugWindow() { unknown18->openDebugWindow(); }

ColiObject *ColiManager::getGroundObject() { return unknown18->unknown18; }

ColiObject *ColiManager::getObject(u32 handle) const {
  const PointerMap &objectMap = unknown18->unknown38;
  if (objectMap.isValid(handle)) {
    return static_cast<ColiObject *>(objectMap.getPtr(handle));
  }

  return nullptr;
}

bool ColiManager::isGblId(u32 id) { return unknown18->isGblId(id); }

void ColiManager::setGblId(u32 id, bool isGlobal) { unknown18->setGblId(id, isGlobal); }

void *ColiManager::getGblIdTbl() { return unknown18->getGblIdTbl(); }

} // namespace fw
