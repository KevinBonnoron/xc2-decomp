#include "navi/nvmsh_res_obj.h"

#include "navi/nvmsh_res_mem_man.h"

// releaseFreeObj is inlined by the game in releaseNavi; keep its definition visible in this unit.
#include "nvmsh_res_mem_man.cpp"

namespace navi {

NvmshResObj::NvmshResObj()
    : unknown00(0), unknown08(nullptr), unknown10(nullptr), unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr),
      unknown50(nullptr) {}

NvmshResObj::~NvmshResObj() {}

NvmshResData::~NvmshResData() {}

void NvmshResObj::createNavi(const u8 *data) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data);
  unknown08 = data;
  unknown10 = data;
  unknown18 = data + header->unknown28;
  unknown20 = data + header->unknown30;
  unknown28 = data + header->unknown54;
  unknown48 = data + header->unknown40;
  unknown30 = data + header->unknown48;
  unknown50 = data + header->unknown50;
  unknown38 = data + header->unknown6c;
  unknown40 = data + header->unknown74;
  unknown00 |= 1;
}

// The game has both functions, with the same body.
void NvmshResObj::releaseNavi() {
  unknown00 = 0;
  unknown08 = nullptr;
}

void NvmshResObj::resetNavi() {
  unknown00 = 0;
  unknown08 = nullptr;
}

void NvmshResData::createNavi() {
  if ((m_readData->unknown00 & 1) != 0) {
    unknown10.createNavi(static_cast<const u8 *>(unknownc8->unknown18));
    if ((m_readData->unknown00 & 2) != 0) {
      unknown68.createNavi(static_cast<const u8 *>(unknownc8->unknown18) + m_readData->unknown0c);
    }
  } else if ((m_readData->unknown00 & 2) != 0) {
    unknown68.createNavi(static_cast<const u8 *>(unknownc8->unknown18));
  }
  unknown04 = 0;
  unknown00 = 0x11;
}

void NvmshResData::resetNavi() {
  unknown10.resetNavi();
  unknown68.resetNavi();
  if ((m_readData->unknown00 & 1) != 0) {
    unknown10.createNavi(static_cast<const u8 *>(unknownc8->unknown18));
    if ((m_readData->unknown00 & 2) != 0) {
      unknown68.createNavi(static_cast<const u8 *>(unknownc8->unknown18) + m_readData->unknown0c);
    }
  } else if ((m_readData->unknown00 & 2) != 0) {
    unknown68.createNavi(static_cast<const u8 *>(unknownc8->unknown18));
  }
}

void NvmshResData::setReadData(const _NvMhAllReadObj *readData, int offset) {
  m_readData = readData;
  unknownc0 = offset;
}

void NvmshResData::releaseNavi(NvmshResMemMan *memMan) {
  NvmshResMemObj *object = unknownc8;
  unknown00 = 0;
  unknown04 = 0;
  unknown10.releaseNavi();
  unknown68.releaseNavi();

  if (object != nullptr) {
    memMan->releaseFreeObj(object);
    unknownc8 = nullptr;
  }
}

void NvmshResData::update(NvmshResMemMan *memMan) {
  if ((unknown00 & 1) == 0) {
    return;
  }

  if ((unknown00 & 4) != 0) {
    if (++unknown04 >= 4) {
      releaseNavi(memMan);
    }
  } else if ((unknown00 & 0x10) != 0) {
    unknown04 = 0;
    if ((unknownc8->unknown10 & 4) != 0) {
      resetNavi();
      unknownc8->unknown10 &= ~4;
    }
  } else if (++unknown04 >= 0x10) {
    unknown04 = 0;
    unknown00 |= 4;
  } else {
    if ((unknownc8->unknown10 & 4) != 0) {
      resetNavi();
      unknownc8->unknown10 &= ~4;
    }
  }
  unknown00 &= ~0x10;
}

void NvmshResData::releaseCall() {
  unknown00 |= 4;
  unknown04 = 0;
}

} // namespace navi
