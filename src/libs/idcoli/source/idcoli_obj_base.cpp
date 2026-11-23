#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mtl/mem_manager.h"

namespace idcoli {

IDColiObjBase::IDColiObjBase(IDColiTreeTop *tree) {
  m_iDColiTreeTop = tree;
  m_iDColiTreeObj.unknown00 = nullptr;
  m_size.x = 0.5f;
  m_iDColiTreeObj.unknown08 = nullptr;
  unknown1c0 = this;
  m_size.y = 2.0f;
  m_size.z = 0.5f;
  m_matrix = mm::Mat44::identity;
  unknownc0 = SHAPE_TYPE_UNKNOWN_3;
  unknown198[0] = nullptr;
  unknown198[1] = nullptr;
  unknownc4 = IDColiBaseType_UNKNOWN_3;
  m_priority = 100;
  unknown1c8 = -1;
  m_max = mm::Vec3(1.0f, 1.0f, 1.0f);
  m_min = mm::Vec3(-1.0f, -1.0f, -1.0f);
  m_materialBit = 0;
  m_offMaterialBit = 0;
  unknown180[0] = 0.0f;
  unknown180[1] = 0.0f;
  unknown188[0] = nullptr;
  unknown188[1] = nullptr;
}

void IDColiObjBase::sweepPush(IDColiObjBase *object) {
  if (object != nullptr) {
    unknown198[0] = object;
    IDColiObjBase *prev = object->unknown188[0];
    if (prev != nullptr) {
      prev->unknown198[0] = this;
    }
    unknown188[0] = prev;
    object->unknown188[0] = this;
    unknown198[1] = object;
    prev = object->unknown188[1];
    if (prev != nullptr) {
      prev->unknown198[1] = this;
    }
    unknown188[1] = prev;
    object->unknown188[1] = this;
    unknown180[0] = 0.0f;
    unknown180[1] = 0.0f;
    return;
  }

  unknown198[0] = nullptr;
  unknown198[1] = nullptr;
  unknown180[0] = 0.0f;
  unknown180[1] = 0.0f;
  unknown188[0] = nullptr;
  unknown188[1] = nullptr;
}

void IDColiObjBase::sweepPop() {
  IDColiObjBase *next = unknown198[0];
  IDColiObjBase *prev = unknown188[0];
  if (prev != nullptr) {
    prev->unknown198[0] = next;
  }
  if (next != nullptr) {
    next->unknown188[0] = prev;
  }
  next = unknown198[1];
  prev = unknown188[1];
  unknown198[0] = nullptr;
  unknown188[0] = nullptr;
  if (prev != nullptr) {
    prev->unknown198[1] = next;
  }
  if (next != nullptr) {
    next->unknown188[1] = prev;
  }
  unknown198[1] = nullptr;
  unknown188[1] = nullptr;
}

bool IDColiObjBase::sweepUpdate(IdSweepAxisType sweepAxis, IdVectorAxisType vectorAxis) {
  IDColiObjBase *next = unknown198[sweepAxis];
  if (next == nullptr) {
    return false;
  }

  IDColiObjBase *target = nullptr;
  do {
    IDColiObjBase *node = next;
    if ((&m_min.x)[vectorAxis] >= (&node->m_min.x)[vectorAxis]) {
      if (target == nullptr) {
        return false;
      }
      break;
    }
    target = node;
    next = node->unknown198[sweepAxis];
  } while (next != nullptr);

  IDColiObjBase *prev = unknown188[sweepAxis];
  if (prev != nullptr) {
    prev->unknown198[sweepAxis] = unknown198[sweepAxis];
  }
  unknown198[sweepAxis]->unknown188[sweepAxis] = prev;
  next = target->unknown198[sweepAxis];
  if (next != nullptr) {
    next->unknown188[sweepAxis] = this;
  }
  unknown198[sweepAxis] = next;
  unknown188[sweepAxis] = target;
  target->unknown198[sweepAxis] = this;
  return true;
}

void IDColiObjBase::sweepTreeMax(IdSweepAxisType sweepAxis, IdVectorAxisType vectorAxis) {
  if (unknown1c & 0x80) {
    if (unknown198[sweepAxis] != nullptr) {
      unknown180[sweepAxis] = unknown198[sweepAxis]->unknown180[sweepAxis];
    }
  } else {
    unknown180[sweepAxis] = (&m_max.x)[vectorAxis];
    if (unknown198[sweepAxis] != nullptr && (&m_max.x)[vectorAxis] < unknown198[sweepAxis]->unknown180[sweepAxis]) {
      unknown180[sweepAxis] = unknown198[sweepAxis]->unknown180[sweepAxis];
    }
  }
}

void IDColiObjBase::releaseDefTree() {
  if (unknown1c8 != -1) {
    m_iDColiTreeTop->releaseTreeList(&m_iDColiTreeObj, unknown1c8);
    unknown1c8 = -1;
  }
}

void IDColiObjBase::defTreeUpdate() { unknown1c8 = m_iDColiTreeTop->setupTreeList(&m_iDColiTreeObj, m_max, m_min); }

void IDColiObjBase::updateBaseTree() {
  unknown1c8 = -1;
  if (!(unknown1c & 0x80)) {
    unknown1c8 = m_iDColiTreeTop->setupTreeList(&m_iDColiTreeObj, m_max, m_min);
  }
}

IDColiObjPhantom::IDColiObjPhantom(IDColiTreeTop *tree) : IDColiObjBase(tree) { unknown24 = unknown098_2; }

IDColiObjPhantom::~IDColiObjPhantom() {}

void IDColiObjPhantom::update() { sizeUpdate(); }

void IDColiObjPhantom::sizeUpdate() {
  if (unknown1c & 0x80) {
    return;
  }

  void *prim = unknownd0;
  IDColiPrimitive::s_CallPrimSet[unknownc0](prim, unknownc4, m_matrix, m_size);
  m_max = mm::Vec3(-100000.0f, -100000.0f, -100000.0f);
  m_min = mm::Vec3(100000.0f, 100000.0f, 100000.0f);
  IDColiPrimitive::s_CallAaBb[unknownc4](m_max, m_min, unknownd0);
}

bool IDColiObjPhantom::SweepAndPruneUpdate() {
  if (unknown1c & 0x80) {
    return false;
  }

  bool isUpdated = sweepUpdate(IdSweepAxisType_UNKNOWN_0, IdVectorAxisType_UNKNOWN_0) | sweepUpdate(IdSweepAxisType_UNKNOWN_1, IdVectorAxisType_UNKNOWN_2);
  unknown1c |= 0x1000;
  return isUpdated;
}

void IDColiObjPhantom::consistentUpdate() { updateBaseTree(); }

bool IDColiObjPhantomCheck::testResultLine(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & m_materialBit) && !(unknown1c & 3)) {
    const void *data = unknownd0;
    return IDColiUtilColiResult::s_CallLine[unknownc4](result, input, data);
  }
  return false;
}

bool IDColiObjPhantomCheck::testResultRay(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & m_materialBit) && !(unknown1c & 3)) {
    const void *data = unknownd0;
    return IDColiUtilColiResult::s_CallRay[unknownc4](result, input, data);
  }
  return false;
}

bool IDColiObjPhantomCheck::testResultSphere(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & m_materialBit) && !(unknown1c & 3)) {
    const void *data = unknownd0;
    return IDColiUtilColiResult::s_CallSphere[unknownc4](result, input, data);
  }
  return false;
}

bool IDColiObjPhantomCheck::testResultCapsule(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & m_materialBit) && !(unknown1c & 3)) {
    const void *data = unknownd0;
    return IDColiUtilColiResult::s_CallCapsule[unknownc4](result, input, data);
  }
  return false;
}

bool IDColiObjPhantomCheck::testCheckLine(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & m_materialBit) && !(unknown1c & 3)) {
    const void *data = unknownd0;
    return IDColiUtilColiSimple::s_CallLine[unknownc4](result, input, data);
  }
  return false;
}

bool IDColiObjPhantomCheck::testCheckRay(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & m_materialBit) && !(unknown1c & 3)) {
    const void *data = unknownd0;
    return IDColiUtilColiSimple::s_CallRay[unknownc4](result, input, data);
  }
  return false;
}

bool IDColiObjPhantomCheck::testCheckSphere(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & m_materialBit) && !(unknown1c & 3)) {
    const void *data = unknownd0;
    return IDColiUtilColiSimple::s_CallSphere[unknownc4](result, input, data);
  }
  return false;
}

bool IDColiObjPhantomCheck::testCheckCapsule(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & m_materialBit) && !(unknown1c & 3)) {
    const void *data = unknownd0;
    return IDColiUtilColiSimple::s_CallCapsule[unknownc4](result, input, data);
  }
  return false;
}

IDColiObjData::IDColiObjData(IDColiTreeTop *tree) : IDColiObjBase(tree) {
  unknown1d0 = nullptr;
  unknown1e0 = nullptr;
  unknown1e8 = nullptr;
  m_boneMax = 0;
  unknown1fc = 0;
  m_iDColiObjGrdChar = nullptr;
}

void IDColiObjData::workNodeClear() {
  unknown021();

  if (unknown1e0 != nullptr) {
    mtl::MemManager::deallocate(unknown1e0, 0, false);
    unknown1e0 = nullptr;
  }
  unknown1e8 = nullptr;
  m_boneMax = 0;
  unknown1fc = 0;
}

IDColiObjChar::~IDColiObjChar() { workNodeClear(); }

void IDColiObjChar::release() {
  m_userData = nullptr;
  setDeleteCall();
  unknown021();
}

void IDColiObjChar::update() {
  if (!(unknown1c & 0x80)) {
    unknown210.x = 0.0f;
    unknown210.y = 0.0f;
    unknown210.z = 0.0f;
    sizeUpdate();
  }
}

void IDColiObjChar::moveUpdate() {}

void IDColiObjChar::sizeUpdate() {
  if (unknown1fc != 0) {
    primUpdate();
    return;
  }

  void *prim = unknownd0;
  IDColiPrimitive::s_CallPrimSet[unknownc0](prim, unknownc4, m_matrix, m_size);
  m_max = mm::Vec3(-100000.0f, -100000.0f, -100000.0f);
  m_min = mm::Vec3(100000.0f, 100000.0f, 100000.0f);
  IDColiPrimitive::s_CallAaBb[unknownc4](m_max, m_min, unknownd0);
}

bool IDColiObjChar::SweepAndPruneUpdate() {
  if (unknown1c & 0x80) {
    return false;
  }

  bool isUpdated = sweepUpdate(IdSweepAxisType_UNKNOWN_0, IdVectorAxisType_UNKNOWN_0) | sweepUpdate(IdSweepAxisType_UNKNOWN_1, IdVectorAxisType_UNKNOWN_2);
  unknown1c |= 0x1000;
  return isUpdated;
}

void IDColiObjChar::consistentUpdate() { updateBaseTree(); }

} // namespace idcoli

// Same order as in the game executable.
// clang-format off
#include "idcoli_obj_char_check.cpp"
#include "idcoli_obj_data.cpp"
#include "idcoli_tree_top.cpp"
// clang-format on
