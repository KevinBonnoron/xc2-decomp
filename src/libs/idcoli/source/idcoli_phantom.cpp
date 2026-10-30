#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace idcoli {

IDColiPhantom::IDColiPhantom() {
  unknown00 = false;
  unknown04 = 0.0f;
  unknown01 = true;
  unknown02 = true;
  unknown08 = nullptr;
}

bool IDColiPhantom::testLine(const mm::Vec3 &start, const mm::Vec3 &end) {
  unknown10.unknown030();
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = unknown08;
  IDColiInput input;
  IDColiInputUtil::getLine(input, start, end, true);
  input.unknowna0 = unknown04;
  IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[1]);
  tree.startTreeAaBbMode(input.line.unknown40, input.line.unknown50);
  ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
  if (unknown08 == nullptr) {
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjPhantomCheck *object = static_cast<IDColiObjPhantomCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        if (object->testCheckLine(unknown10, input)) {
          return true;
        }
      }
    }
    return false;
  }

  bool isHit = false;
  if (unknown10.unknown00 == 0) {
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjPhantomCheck *object = static_cast<IDColiObjPhantomCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        unknown10.unknownf8 = object;
        unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
        isHit |= object->testCheckLine(unknown10, input);
      }
    }
  } else {
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjPhantomCheck *object = static_cast<IDColiObjPhantomCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        unknown10.unknownf8 = object;
        unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
        isHit |= object->testResultLine(unknown10, input);
      }
    }
  }
  if (!isHit) {
    return false;
  }
  if (unknown10.unknown00 == 1 && unknown08 != nullptr) {
    unknown08->unknown01(unknown10.unknown98, &unknown10.unknown10);
  }
  return true;
}

bool IDColiPhantom::testRay(const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength) {
  unknown10.unknown030();
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = unknown08;
  IDColiInput input;
  IDColiInputUtil::getRay(input, start, direction, length, -backLength, true);
  input.unknowna0 = unknown04;
  IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[1]);
  tree.startTreeAaBbMode(input.unknown00, input.unknown10);
  ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
  if (unknown08 == nullptr) {
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjPhantomCheck *object = static_cast<IDColiObjPhantomCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        if (object->testCheckRay(unknown10, input)) {
          return true;
        }
      }
    }
    return false;
  }

  bool isHit = false;
  if (unknown10.unknown00 == 0) {
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjPhantomCheck *object = static_cast<IDColiObjPhantomCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        unknown10.unknownf8 = object;
        unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
        isHit |= object->testCheckRay(unknown10, input);
      }
    }
  } else {
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjPhantomCheck *object = static_cast<IDColiObjPhantomCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        unknown10.unknownf8 = object;
        unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
        isHit |= object->testResultRay(unknown10, input);
      }
    }
  }
  if (!isHit) {
    return false;
  }
  if (unknown10.unknown00 == 1 && unknown08 != nullptr) {
    if (unknown10.unknownb0) {
      unknown08->unknown01(unknown10.unknown98, &unknown10.unknown10);
    }
    if (unknown10.unknownb1) {
      unknown08->unknown01(unknown10.unknowna8, &unknown10.unknown50);
    }
  }
  return true;
}

bool IDColiPhantom::testSphere(const mm::Vec3 &center, f32 radius) {
  IDColiInput input;
  IDColiInputUtil::getSphere(input, center, radius, true);
  input.unknowna0 = unknown04;
  unknown10.unknown030();
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = unknown08;
  IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[1]);
  tree.startTreeAaBbMode(input.unknown00, input.unknown10);
  ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
  if (unknown08 == nullptr) {
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjPhantomCheck *object = static_cast<IDColiObjPhantomCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        if (object->testCheckSphere(unknown10, input)) {
          return true;
        }
      }
    }
    return false;
  }

  bool isHit = false;
  if (unknown10.unknown00 == 0) {
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjPhantomCheck *object = static_cast<IDColiObjPhantomCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        unknown10.unknownf8 = object;
        unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
        isHit |= object->testCheckSphere(unknown10, input);
      }
    }
  } else {
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjPhantomCheck *object = static_cast<IDColiObjPhantomCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        unknown10.unknownf8 = object;
        unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
        isHit |= object->testResultSphere(unknown10, input);
      }
    }
  }
  if (!isHit) {
    return false;
  }
  if (unknown10.unknown00 == 1 && unknown08 != nullptr) {
    unknown08->unknown01(unknown10.unknown98, &unknown10.unknown10);
  }
  return true;
}

bool IDColiPhantom::testCapsule(const mm::Vec3 &start, const mm::Vec3 &end, f32 radius) {
  IDColiInput input;
  IDColiInputUtil::getCapsule(input, start, end, radius, true);
  input.unknowna0 = unknown04;
  unknown10.unknown030();
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = unknown08;
  IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[1]);
  tree.startTreeAaBbMode(input.unknown00, input.unknown10);
  ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
  if (unknown08 == nullptr) {
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjPhantomCheck *object = static_cast<IDColiObjPhantomCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        if (object->testCheckCapsule(unknown10, input)) {
          return true;
        }
      }
    }
    return false;
  }

  bool isHit = false;
  if (unknown10.unknown00 == 0) {
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjPhantomCheck *object = static_cast<IDColiObjPhantomCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        unknown10.unknownf8 = object;
        unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
        isHit |= object->testCheckCapsule(unknown10, input);
      }
    }
  } else {
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjPhantomCheck *object = static_cast<IDColiObjPhantomCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        unknown10.unknownf8 = object;
        unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
        isHit |= object->testResultCapsule(unknown10, input);
      }
    }
  }
  if (!isHit) {
    return false;
  }
  if (unknown10.unknown00 == 1 && unknown08 != nullptr) {
    unknown08->unknown01(unknown10.unknown98, &unknown10.unknown10);
  }
  return true;
}

// The three shape blocks below repeat the same character tree walk, as the game does.
bool IDColiPhantom::testPhantomColiObj(IDColiObj *object, f32 range) {
  unknown10.unknown030();
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = unknown08;
  IDColiObjBase *phantom = static_cast<IDColiObjBase *>(object);
  IDColiInput input;
  switch (phantom->unknownc4) {
  case IDColiBaseType_UNKNOWN_0:
  case IDColiBaseType_UNKNOWN_4: {
    const CLSphereWork *sphere = reinterpret_cast<const CLSphereWork *>(phantom->unknownd0);
    IDColiInputUtil::getSphere(input, sphere->unknown00, sphere->unknown10 + range, true);
    input.unknowna0 = unknown04;
    unknown10.unknown030();
    unknown10.unknownf8 = nullptr;
    unknown10.unknown100 = unknown08;
    IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[0]);
    tree.startTreeAaBbMode(input.unknown00, input.unknown10);
    ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
    if (unknown08 != nullptr) {
      bool isHit = false;
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *character = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          unknown10.unknownf8 = character;
          unknown10.unknownf0 = reinterpret_cast<u64>(character->unknown48);
          isHit |= character->testCheckSphere(unknown10, input);
        }
      }
      return isHit;
    }
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjCharCheck *character = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        if (character->testCheckSphere(unknown10, input)) {
          return true;
        }
      }
    }
    break;
  }
  case IDColiBaseType_UNKNOWN_1: {
    IDColiInputUtil::getBox(input, *reinterpret_cast<const CLBoxWork *>(phantom->unknownd0));
    input.unknowna0 = unknown04;
    unknown10.unknown030();
    unknown10.unknownf8 = nullptr;
    unknown10.unknown100 = unknown08;
    IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[0]);
    tree.startTreeAaBbMode(input.unknown00, input.unknown10);
    ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
    if (unknown08 != nullptr) {
      bool isHit = false;
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *character = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          unknown10.unknownf8 = character;
          unknown10.unknownf0 = reinterpret_cast<u64>(character->unknown48);
          isHit |= character->testCheckBox(unknown10, input);
        }
      }
      return isHit;
    }
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjCharCheck *character = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        if (character->testCheckBox(unknown10, input)) {
          return true;
        }
      }
    }
    break;
  }
  case IDColiBaseType_UNKNOWN_2:
  case IDColiBaseType_UNKNOWN_3: {
    const CLCapsuleWork *capsule = reinterpret_cast<const CLCapsuleWork *>(phantom->unknownd0);
    IDColiInputUtil::getCapsule(input, capsule->unknown00, capsule->unknown10, capsule->unknown50 + range, true);
    input.unknowna0 = unknown04;
    unknown10.unknown030();
    unknown10.unknownf8 = nullptr;
    unknown10.unknown100 = unknown08;
    IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[0]);
    tree.startTreeAaBbMode(input.unknown00, input.unknown10);
    ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
    if (unknown08 != nullptr) {
      bool isHit = false;
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *character = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          unknown10.unknownf8 = character;
          unknown10.unknownf0 = reinterpret_cast<u64>(character->unknown48);
          isHit |= character->testCheckCapsule(unknown10, input);
        }
      }
      return isHit;
    }
    for (; list != nullptr; list = tree.unknown033()) {
      for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
        IDColiObjCharCheck *character = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
        if (character->testCheckCapsule(unknown10, input)) {
          return true;
        }
      }
    }
    break;
  }
  default:
    break;
  }
  return false;
}

} // namespace idcoli
