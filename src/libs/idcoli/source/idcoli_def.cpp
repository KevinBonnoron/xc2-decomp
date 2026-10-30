#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

IDColiDef::IDColiDef() {
  unknown00 = false;
  unknown04 = 0.0f;
  unknown01 = true;
  unknown02 = true;
  unknown08 = nullptr;
}

bool IDColiDef::testLine(const mm::Vec3 &start, const mm::Vec3 &end) {
  IDColiInput input;
  IDColiInputUtil::getLine(input, start, end, true);
  if (input.unknown98 <= 0.0001f) {
    return false;
  }
  input.unknowna0 = unknown04;
  unknown10.unknown030();
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = unknown08;
  if (unknown10.unknown00 == 0 && unknown08 == nullptr) {
    if (unknown01) {
      for (IDColiObj *object = IDColiManager::get()->unknown08[0].m_head; object != nullptr; object = object->unknown10) {
        if (static_cast<IDColiObjGrand *>(object)->unknown051(unknown10, input)) {
          return true;
        }
      }
    }
    if (unknown02) {
      for (IDColiObj *object = IDColiManager::get()->unknown08[3].m_head; object != nullptr; object = object->unknown10) {
        if (static_cast<IDColiObjGrdChar *>(object)->testLine(unknown10, input)) {
          return true;
        }
      }
    }
    if (unknown00) {
      IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[0]);
      tree.startTreeAaBbMode(input.unknown00, input.unknown10);
      ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *object = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          if (object->testCheckLine(unknown10, input)) {
            return true;
          }
        }
      }
    }
    return false;
  }

  bool isHit = false;
  if (unknown01) {
    for (IDColiObj *object = IDColiManager::get()->unknown08[0].m_head; object != nullptr; object = object->unknown10) {
      unknown10.unknownf8 = object;
      unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
      isHit |= static_cast<IDColiObjGrand *>(object)->unknown051(unknown10, input);
    }
  }
  if (unknown02) {
    for (IDColiObj *object = IDColiManager::get()->unknown08[3].m_head; object != nullptr; object = object->unknown10) {
      IDColiObj *owner = static_cast<IDColiObjGrdChar *>(object)->unknown78;
      unknown10.unknownf8 = owner;
      unknown10.unknownf0 = reinterpret_cast<u64>(owner->unknown48);
      isHit |= static_cast<IDColiObjGrdChar *>(object)->testLine(unknown10, input);
    }
  }
  if (unknown00) {
    IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[0]);
    tree.startTreeAaBbMode(input.unknown00, input.unknown10);
    ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
    if (unknown10.unknown00 == 0) {
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *object = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          unknown10.unknownf8 = object;
          unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
          isHit |= object->testCheckLine(unknown10, input);
        }
      }
    } else {
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *object = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          unknown10.unknownf8 = object;
          unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
          isHit |= object->testResultLine(unknown10, input);
        }
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

bool IDColiDef::testRay(const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength) {
  IDColiInput input;
  IDColiInputUtil::getRay(input, start, direction, length, -backLength, true);
  input.unknowna0 = unknown04;
  unknown10.unknown030();
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = unknown08;
  if (unknown10.unknown00 == 0 && unknown08 == nullptr) {
    if (unknown01) {
      for (IDColiObj *object = IDColiManager::get()->unknown08[0].m_head; object != nullptr; object = object->unknown10) {
        if (static_cast<IDColiObjGrand *>(object)->unknown052(unknown10, input)) {
          return true;
        }
      }
    }
    if (unknown02) {
      for (IDColiObj *object = IDColiManager::get()->unknown08[3].m_head; object != nullptr; object = object->unknown10) {
        if (static_cast<IDColiObjGrdChar *>(object)->testRay(unknown10, input)) {
          return true;
        }
      }
    }
    if (unknown00) {
      IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[0]);
      tree.startTreeAaBbMode(input.unknown00, input.unknown10);
      ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *object = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          if (object->testCheckRay(unknown10, input)) {
            return true;
          }
        }
      }
    }
    return false;
  }

  bool isHit = false;
  if (unknown01) {
    for (IDColiObj *object = IDColiManager::get()->unknown08[0].m_head; object != nullptr; object = object->unknown10) {
      unknown10.unknownf8 = object;
      unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
      isHit |= static_cast<IDColiObjGrand *>(object)->unknown052(unknown10, input);
    }
  }
  if (unknown02) {
    for (IDColiObj *object = IDColiManager::get()->unknown08[3].m_head; object != nullptr; object = object->unknown10) {
      IDColiObj *owner = static_cast<IDColiObjGrdChar *>(object)->unknown78;
      unknown10.unknownf8 = owner;
      unknown10.unknownf0 = reinterpret_cast<u64>(owner->unknown48);
      isHit |= static_cast<IDColiObjGrdChar *>(object)->testRay(unknown10, input);
    }
  }
  if (unknown00) {
    IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[0]);
    tree.startTreeAaBbMode(input.unknown00, input.unknown10);
    ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
    if (unknown10.unknown00 == 0) {
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *object = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          unknown10.unknownf8 = object;
          unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
          isHit |= object->testCheckRay(unknown10, input);
        }
      }
    } else {
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *object = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          unknown10.unknownf8 = object;
          unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
          isHit |= object->testResultRay(unknown10, input);
        }
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

bool IDColiDef::testSphere(const mm::Vec3 &center, f32 radius) {
  IDColiInput input;
  IDColiInputUtil::getSphere(input, center, radius, true);
  input.unknowna0 = unknown04;
  unknown10.unknown030();
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = unknown08;
  if (unknown10.unknown00 == 0 && unknown08 == nullptr) {
    if (unknown01) {
      for (IDColiObj *object = IDColiManager::get()->unknown08[0].m_head; object != nullptr; object = object->unknown10) {
        if (static_cast<IDColiObjGrand *>(object)->unknown053(unknown10, input, false)) {
          return true;
        }
      }
    }
    if (unknown02) {
      for (IDColiObj *object = IDColiManager::get()->unknown08[3].m_head; object != nullptr; object = object->unknown10) {
        if (static_cast<IDColiObjGrdChar *>(object)->testSphere(unknown10, input)) {
          return true;
        }
      }
    }
    if (unknown00) {
      IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[0]);
      tree.startTreeAaBbMode(input.unknown00, input.unknown10);
      ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *object = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          if (object->testCheckSphere(unknown10, input)) {
            return true;
          }
        }
      }
    }
    return false;
  }

  bool isHit = false;
  if (unknown01) {
    for (IDColiObj *object = IDColiManager::get()->unknown08[0].m_head; object != nullptr; object = object->unknown10) {
      unknown10.unknownf8 = object;
      unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
      isHit |= static_cast<IDColiObjGrand *>(object)->unknown053(unknown10, input, false);
    }
  }
  if (unknown02) {
    for (IDColiObj *object = IDColiManager::get()->unknown08[3].m_head; object != nullptr; object = object->unknown10) {
      IDColiObj *owner = static_cast<IDColiObjGrdChar *>(object)->unknown78;
      unknown10.unknownf8 = owner;
      unknown10.unknownf0 = reinterpret_cast<u64>(owner->unknown48);
      isHit |= static_cast<IDColiObjGrdChar *>(object)->testSphere(unknown10, input);
    }
  }
  if (unknown00) {
    IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[0]);
    tree.startTreeAaBbMode(input.unknown00, input.unknown10);
    ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
    if (unknown10.unknown00 == 0) {
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *object = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          unknown10.unknownf8 = object;
          unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
          isHit |= object->testCheckSphere(unknown10, input);
        }
      }
    } else {
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *object = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          unknown10.unknownf8 = object;
          unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
          isHit |= object->testResultSphere(unknown10, input);
        }
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

bool IDColiDef::testCapsule(const mm::Vec3 &start, const mm::Vec3 &end, f32 radius) {
  IDColiInput input;
  IDColiInputUtil::getCapsule(input, start, end, radius, true);
  input.unknowna0 = unknown04;
  unknown10.unknown030();
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = unknown08;
  if (unknown10.unknown00 == 0 && unknown08 == nullptr) {
    if (unknown01) {
      for (IDColiObj *object = IDColiManager::get()->unknown08[0].m_head; object != nullptr; object = object->unknown10) {
        if (static_cast<IDColiObjGrand *>(object)->unknown054(unknown10, input, false)) {
          return true;
        }
      }
    }
    if (unknown02) {
      for (IDColiObj *object = IDColiManager::get()->unknown08[3].m_head; object != nullptr; object = object->unknown10) {
        if (static_cast<IDColiObjGrdChar *>(object)->testCapsule(unknown10, input)) {
          return true;
        }
      }
    }
    if (unknown00) {
      IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[0]);
      tree.startTreeAaBbMode(input.unknown00, input.unknown10);
      ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *object = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          if (object->testCheckCapsule(unknown10, input)) {
            return true;
          }
        }
      }
    }
    return false;
  }

  bool isHit = false;
  if (unknown01) {
    for (IDColiObj *object = IDColiManager::get()->unknown08[0].m_head; object != nullptr; object = object->unknown10) {
      unknown10.unknownf8 = object;
      unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
      isHit |= static_cast<IDColiObjGrand *>(object)->unknown054(unknown10, input, false);
    }
  }
  if (unknown02) {
    for (IDColiObj *object = IDColiManager::get()->unknown08[3].m_head; object != nullptr; object = object->unknown10) {
      IDColiObj *owner = static_cast<IDColiObjGrdChar *>(object)->unknown78;
      unknown10.unknownf8 = owner;
      unknown10.unknownf0 = reinterpret_cast<u64>(owner->unknown48);
      isHit |= static_cast<IDColiObjGrdChar *>(object)->testCapsule(unknown10, input);
    }
  }
  if (unknown00) {
    IDColiUtilTreeAcc tree(IDColiManager::get()->unknownd8[0]);
    tree.startTreeAaBbMode(input.unknown00, input.unknown10);
    ColiLinkList<IDColiTreeObj> *list = tree.unknown033();
    if (unknown10.unknown00 == 0) {
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *object = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          unknown10.unknownf8 = object;
          unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
          isHit |= object->testCheckCapsule(unknown10, input);
        }
      }
    } else {
      for (; list != nullptr; list = tree.unknown033()) {
        for (IDColiTreeObj *node = list->m_head; node != nullptr; node = node->unknown08) {
          IDColiObjCharCheck *object = static_cast<IDColiObjCharCheck *>(reinterpret_cast<unknown031 *>(node)->unknown10);
          unknown10.unknownf8 = object;
          unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
          isHit |= object->testResultCapsule(unknown10, input);
        }
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

bool IDColiDef::testAaBb(const mm::Vec3 &max, const mm::Vec3 &min) {
  IDColiInput input;
  IDColiInputUtil::getAaBb(input, max, min);
  input.unknowna0 = unknown04;
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = nullptr;
  unknown10.unknown030();
  if (unknown01) {
    for (IDColiObj *object = IDColiManager::get()->unknown08[0].m_head; object != nullptr; object = object->unknown10) {
      if (static_cast<IDColiObjGrand *>(object)->unknown034(unknown10, input)) {
        return true;
      }
    }
  }
  return false;
}

bool IDColiDef::getAaBbPoliAaBb(mm::Vec3 &max, mm::Vec3 &min, const mm::Vec3 &inputMax, const mm::Vec3 &inputMin) {
  IDColiInput input;
  IDColiInputUtil::getAaBb(input, inputMax, inputMin);
  input.unknowna0 = unknown04;
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = nullptr;
  unknown10.unknown030();
  unknown10.unknown50.unknown00 = inputMin;
  unknown10.unknown50.unknown10 = inputMax;
  bool isHit = false;
  if (unknown01) {
    for (IDColiObj *object = IDColiManager::get()->unknown08[0].m_head; object != nullptr; object = object->unknown10) {
      isHit |= static_cast<IDColiObjGrand *>(object)->unknown035(unknown10, input);
    }
  }
  if (isHit) {
    max = unknown10.unknown50.unknown00;
    min = unknown10.unknown50.unknown10;
    max.x = max.x < inputMax.x ? max.x : inputMax.x;
    max.y = max.y < inputMax.y ? max.y : inputMax.y;
    max.z = max.z < inputMax.z ? max.z : inputMax.z;
    min.x = min.x > inputMin.x ? min.x : inputMin.x;
    min.y = min.y > inputMin.y ? min.y : inputMin.y;
    min.z = min.z > inputMin.z ? min.z : inputMin.z;
    return true;
  }
  max = inputMax;
  min = inputMin;
  return false;
}

} // namespace idcoli
