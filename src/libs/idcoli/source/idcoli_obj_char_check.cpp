#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "types.h"

namespace idcoli {

// Inferred helper: runs the test of the table on the primitives of a check list of the binary, merging the hits into isHit; original name unknown.
static bool unknown063(const IDColiObjCharCheck *object, const unknown004 *table, IDColiResult &result, const IDColiInput &input, const u8 *binary, const unknown061 &check, bool isHit) {
  const u16 *list = reinterpret_cast<const u16 *>(binary + check.unknown00);
  for (int i = 0; i < check.unknown04; i++) {
    const unknown008 *prim = &object->unknown1e8[*list++];
    isHit |= table[prim->unknownb0](result, input, prim);
  }
  return isHit;
}

// Inferred helper: runs the test of the table on the primitives of the default check list of the binary, up to the first hit; original name unknown.
static bool unknown064(const IDColiObjCharCheck *object, const unknown004 *table, IDColiResult &result, const IDColiInput &input) {
  const u8 *binary = reinterpret_cast<const u8 *>(object->unknown1d0);
  const unknown022 *info = reinterpret_cast<const unknown022 *>(binary + object->unknown1d0->unknown0c);
  const u16 *list = reinterpret_cast<const u16 *>(binary + info->unknown20.unknown00);
  for (int i = 0; i < info->unknown20.unknown04; i++) {
    const unknown008 *prim = &object->unknown1e8[*list++];
    if (table[prim->unknownb0](result, input, prim)) {
      return true;
    }
  }
  return false;
}

bool IDColiObjCharCheck::testResultLine(IDColiResult &result, const IDColiInput &input) {
  if ((result.unknowne8 & unknown2c) || !(unknown18 & 2) || (unknown1c & 3)) {
    return false;
  }
  if (!(unknown1c & 0x100)) {
    const void *data = unknownd0;
    return IDColiUtilColiResult::s_CallLine[unknownc4](result, input, data);
  }

  const u8 *binary = reinterpret_cast<const u8 *>(unknown1d0);
  const unknown022 *info = reinterpret_cast<const unknown022 *>(binary + unknown1d0->unknown0c);
  return unknown063(this, IDColiUtilColiResult::s_CallLine, result, input, binary, info->unknown20, false);
}

bool IDColiObjCharCheck::testResultRay(IDColiResult &result, const IDColiInput &input) {
  if ((result.unknowne8 & unknown2c) || !(unknown18 & 2) || (unknown1c & 3)) {
    return false;
  }
  if (!(unknown1c & 0x100)) {
    const void *data = unknownd0;
    return IDColiUtilColiResult::s_CallRay[unknownc4](result, input, data);
  }

  const u8 *binary = reinterpret_cast<const u8 *>(unknown1d0);
  const unknown022 *info = reinterpret_cast<const unknown022 *>(binary + unknown1d0->unknown0c);
  return unknown063(this, IDColiUtilColiResult::s_CallRay, result, input, binary, info->unknown20, false);
}

bool IDColiObjCharCheck::testResultSphere(IDColiResult &result, const IDColiInput &input) {
  if ((result.unknowne8 & unknown2c) || !(unknown18 & 2) || (unknown1c & 3)) {
    return false;
  }
  if (!(unknown1c & 0x100)) {
    const void *data = unknownd0;
    return IDColiUtilColiResult::s_CallSphere[unknownc4](result, input, data);
  }

  const u8 *binary = reinterpret_cast<const u8 *>(unknown1d0);
  const unknown022 *info = reinterpret_cast<const unknown022 *>(binary + unknown1d0->unknown0c);
  return unknown063(this, IDColiUtilColiResult::s_CallSphere, result, input, binary, info->unknown20, false);
}

bool IDColiObjCharCheck::testResultCapsule(IDColiResult &result, const IDColiInput &input) {
  if ((result.unknowne8 & unknown2c) || !(unknown18 & 2) || (unknown1c & 3)) {
    return false;
  }
  if (!(unknown1c & 0x100)) {
    const void *data = unknownd0;
    return IDColiUtilColiResult::s_CallCapsule[unknownc4](result, input, data);
  }

  const u8 *binary = reinterpret_cast<const u8 *>(unknown1d0);
  const unknown022 *info = reinterpret_cast<const unknown022 *>(binary + unknown1d0->unknown0c);
  return unknown063(this, IDColiUtilColiResult::s_CallCapsule, result, input, binary, info->unknown20, false);
}

// The parts of a binary are tested through the result tables, not the simple ones (original bug, reproduced).
bool IDColiObjCharCheck::testCheckLine(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & unknown2c) && (unknown18 & 2) && !(unknown1c & 3)) {
    if (unknown1c & 0x100) {
      return unknown064(this, IDColiUtilColiResult::s_CallLine, result, input);
    } else {
      const void *data = unknownd0;
      return IDColiUtilColiSimple::s_CallLine[unknownc4](result, input, data);
    }
  }

  return false;
}

bool IDColiObjCharCheck::testCheckRay(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & unknown2c) && (unknown18 & 2) && !(unknown1c & 3)) {
    if (unknown1c & 0x100) {
      return unknown064(this, IDColiUtilColiResult::s_CallRay, result, input);
    } else {
      const void *data = unknownd0;
      return IDColiUtilColiSimple::s_CallRay[unknownc4](result, input, data);
    }
  }

  return false;
}

bool IDColiObjCharCheck::testCheckSphere(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & unknown2c) && (unknown18 & 2) && !(unknown1c & 3)) {
    if (unknown1c & 0x100) {
      return unknown064(this, IDColiUtilColiResult::s_CallSphere, result, input);
    } else {
      const void *data = unknownd0;
      return IDColiUtilColiSimple::s_CallSphere[unknownc4](result, input, data);
    }
  }

  return false;
}

bool IDColiObjCharCheck::testCheckCapsule(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & unknown2c) && (unknown18 & 2) && !(unknown1c & 3)) {
    if (unknown1c & 0x100) {
      return unknown064(this, IDColiUtilColiResult::s_CallCapsule, result, input);
    } else {
      const void *data = unknownd0;
      return IDColiUtilColiSimple::s_CallCapsule[unknownc4](result, input, data);
    }
  }

  return false;
}

bool IDColiObjCharCheck::testCheckBox(IDColiResult &result, const IDColiInput &input) {
  if (!(result.unknowne8 & unknown2c) && (unknown18 & 2) && !(unknown1c & 3)) {
    const void *data = unknownd0;
    return IDColiUtilColiSimple::s_CallBox[unknownc4](result, input, data);
  }

  return false;
}

bool IDColiObjCharCheck::testTypeLine(IDColiResult &result, const IDColiInput &input, ColiCheckType type) {
  if ((result.unknowne8 & unknown2c) || !(unknown18 & 2) || (unknown1c & 3)) {
    return false;
  }
  if (!(unknown1c & 0x100)) {
    if (type == ColiCheckType_UNKNOWN_1) {
      if (!(unknown1c & 0x400)) {
        return false;
      }
    } else if (type == ColiCheckType_UNKNOWN_2) {
      if (unknown1c & 0x400) {
        return false;
      }
    }
    const void *data = unknownd0;
    return IDColiUtilColiResult::s_CallLine[unknownc4](result, input, data);
  }

  bool isHit = false;
  const u8 *binary = reinterpret_cast<const u8 *>(unknown1d0);
  const unknown022 *info = reinterpret_cast<const unknown022 *>(binary + unknown1d0->unknown0c);
  if (type == ColiCheckType_UNKNOWN_1) {
    const u16 *list = reinterpret_cast<const u16 *>(binary + info->unknown18.unknown00);
    for (int i = 0; i < info->unknown18.unknown04; i++) {
      const unknown008 *prim = &unknown1e8[*list++];
      isHit |= IDColiUtilColiResult::s_CallLine[prim->unknownb0](result, input, prim);
    }
  } else if (type == ColiCheckType_UNKNOWN_2) {
    const u16 *list = reinterpret_cast<const u16 *>(binary + info->unknown28.unknown00);
    for (int i = 0; i < info->unknown28.unknown04; i++) {
      const unknown008 *prim = &unknown1e8[*list++];
      isHit |= IDColiUtilColiResult::s_CallLine[prim->unknownb0](result, input, prim);
    }
  } else {
    const u16 *list = reinterpret_cast<const u16 *>(binary + info->unknown20.unknown00);
    for (int i = 0; i < info->unknown20.unknown04; i++) {
      const unknown008 *prim = &unknown1e8[*list++];
      isHit |= IDColiUtilColiResult::s_CallLine[prim->unknownb0](result, input, prim);
    }
  }
  return isHit;
}

bool IDColiObjCharCheck::testTypeSphere(IDColiResult &result, const IDColiInput &input, ColiCheckType type) {
  if ((result.unknowne8 & unknown2c) || !(unknown18 & 2) || (unknown1c & 3)) {
    return false;
  }
  if (!(unknown1c & 0x100)) {
    if (type == ColiCheckType_UNKNOWN_1) {
      if (!(unknown1c & 0x400)) {
        return false;
      }
    } else if (type == ColiCheckType_UNKNOWN_2) {
      if (unknown1c & 0x400) {
        return false;
      }
    }
    const void *data = unknownd0;
    return IDColiUtilColiResult::s_CallSphere[unknownc4](result, input, data);
  }

  bool isHit = false;
  const u8 *binary = reinterpret_cast<const u8 *>(unknown1d0);
  const unknown022 *info = reinterpret_cast<const unknown022 *>(binary + unknown1d0->unknown0c);
  if (type == ColiCheckType_UNKNOWN_1) {
    return false;
  } else if (type == ColiCheckType_UNKNOWN_2) {
    const u16 *list = reinterpret_cast<const u16 *>(binary + info->unknown18.unknown00);
    for (int i = 0; i < info->unknown18.unknown04; i++) {
      const unknown008 *prim = &unknown1e8[*list++];
      isHit |= IDColiUtilColiResult::s_CallSphere[prim->unknownb0](result, input, prim);
    }
    list = reinterpret_cast<const u16 *>(binary + info->unknown28.unknown00);
    for (int i = 0; i < info->unknown28.unknown04; i++) {
      const unknown008 *prim = &unknown1e8[*list++];
      isHit |= IDColiUtilColiResult::s_CallSphere[prim->unknownb0](result, input, prim);
    }
  } else {
    const u16 *list = reinterpret_cast<const u16 *>(binary + info->unknown20.unknown00);
    for (int i = 0; i < info->unknown20.unknown04; i++) {
      const unknown008 *prim = &unknown1e8[*list++];
      isHit |= IDColiUtilColiResult::s_CallSphere[prim->unknownb0](result, input, prim);
    }
  }
  return isHit;
}

bool IDColiObjCharCheck::testTypeCapsule(IDColiResult &result, const IDColiInput &input, ColiCheckType type) {
  if ((result.unknowne8 & unknown2c) || !(unknown18 & 2) || (unknown1c & 3)) {
    return false;
  }
  if (!(unknown1c & 0x100)) {
    if (type == ColiCheckType_UNKNOWN_1) {
      if (!(unknown1c & 0x400)) {
        return false;
      }
    } else if (type == ColiCheckType_UNKNOWN_2) {
      if (unknown1c & 0x400) {
        return false;
      }
    }
    const void *data = unknownd0;
    return IDColiUtilColiResult::s_CallCapsule[unknownc4](result, input, data);
  }

  bool isHit = false;
  const u8 *binary = reinterpret_cast<const u8 *>(unknown1d0);
  const unknown022 *info = reinterpret_cast<const unknown022 *>(binary + unknown1d0->unknown0c);
  if (type == ColiCheckType_UNKNOWN_1) {
    return false;
  } else if (type == ColiCheckType_UNKNOWN_2) {
    const u16 *list = reinterpret_cast<const u16 *>(binary + info->unknown28.unknown00);
    for (int i = 0; i < info->unknown28.unknown04; i++) {
      const unknown008 *prim = &unknown1e8[*list++];
      isHit |= IDColiUtilColiResult::s_CallCapsule[prim->unknownb0](result, input, prim);
    }
    list = reinterpret_cast<const u16 *>(binary + info->unknown18.unknown00);
    for (int i = 0; i < info->unknown18.unknown04; i++) {
      const unknown008 *prim = &unknown1e8[*list++];
      isHit |= IDColiUtilColiResult::s_CallCapsule[prim->unknownb0](result, input, prim);
    }
  } else {
    const u16 *list = reinterpret_cast<const u16 *>(binary + info->unknown20.unknown00);
    for (int i = 0; i < info->unknown20.unknown04; i++) {
      const unknown008 *prim = &unknown1e8[*list++];
      isHit |= IDColiUtilColiResult::s_CallCapsule[prim->unknownb0](result, input, prim);
    }
  }
  return isHit;
}

} // namespace idcoli
