#include "dr/dr_res_mdo_seam_read.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "ml/dev_file_th.h"

namespace ml {

DrResMdoSeamRead::DrResMdoSeamRead() {
  memset(&unknown08, 0, 0x50);
  unknown4c = FLAG_UNKNOWN_2;
}

DrResMdoSeamRead::~DrResMdoSeamRead() { release(); }

void DrResMdoSeamRead::release() {
  unknown48 = 0;
  unknown4a = 0;
  if (unknown4c & FLAG_UNKNOWN_0) {
    for (int i = 0; i < 8; i++) {
      if (unknown08[i] != nullptr) {
        DevFileTh::rfClose(unknown08[i]);
        unknown08[i] = nullptr;
      }
    }
    unknown4c &= ~FLAG_UNKNOWN_0;
  }
  if (unknown4c & FLAG_UNKNOWN_1) {
    for (int i = 0; i < 8; i++) {
      if (unknown08[i] != nullptr) {
        DevFileTh::cancel(unknown08[i], false);
        unknown08[i] = nullptr;
      }
    }
    unknown4c &= ~FLAG_UNKNOWN_1;
  }
}

void DrResMdoSeamRead::setup(bool isKeepOpen) {
  u32 flags = unknown4c & ~(FLAG_UNKNOWN_2 | FLAG_UNKNOWN_3);
  if (isKeepOpen) {
    flags |= FLAG_UNKNOWN_2;
  } else {
    flags |= FLAG_UNKNOWN_3;
  }
  unknown4c = flags;
}

void DrResMdoSeamRead::setReadInit() {
  release();
  if (unknown4c & FLAG_UNKNOWN_3) {
    unknown4c |= FLAG_UNKNOWN_1;
  }
}

void DrResMdoSeamRead::setOpenInit() {
  release();
  if (unknown4c & FLAG_UNKNOWN_2) {
    DevFileParamTh param;
    param.unknown60 = this;
    param.unknown00 = unknown50;
    for (int i = 0; i < 8; i++) {
      if (unknown08[i] == nullptr) {
        unknown08[i] = DevFileTh::rfOpen(param);
        if (unknown08[i] == nullptr) {
          unknown4c |= FLAG_UNKNOWN_8;
          return;
        }
      }
    }
    unknown4c |= FLAG_UNKNOWN_0;
  }
}

void DrResMdoSeamRead::update(const char *path, bool isReadEach) {
  u32 flags = unknown4c;
  unknown50 = path;
  unknown4c = flags & ~FLAG_UNKNOWN_8;
  if (isReadEach) {
    if (unknown4c & FLAG_UNKNOWN_3) {
      unknown4c |= FLAG_UNKNOWN_5;
    }
  } else {
    if (unknown4c & FLAG_UNKNOWN_2) {
      unknown4c |= FLAG_UNKNOWN_6;
    }
  }
  if ((unknown4c & (FLAG_UNKNOWN_3 | FLAG_UNKNOWN_5)) == (FLAG_UNKNOWN_3 | FLAG_UNKNOWN_5)) {
    unknown4c |= FLAG_UNKNOWN_4;
  }
  if ((unknown4c & (FLAG_UNKNOWN_2 | FLAG_UNKNOWN_6)) == (FLAG_UNKNOWN_2 | FLAG_UNKNOWN_6)) {
    unknown4c |= FLAG_UNKNOWN_4;
  }
  if (unknown4c & FLAG_UNKNOWN_4) {
    if (!isRead()) {
      if (!(unknown4c & FLAG_UNKNOWN_7)) {
        unknown4c |= FLAG_UNKNOWN_7;
      } else {
        release();
        u32 flags = unknown4c & ~0xff;
        if (unknown4c & FLAG_UNKNOWN_5) {
          flags |= FLAG_UNKNOWN_2;
        } else {
          flags |= FLAG_UNKNOWN_3;
        }
        unknown4c = flags;
      }
    }
  }
  if ((unknown4c & (FLAG_UNKNOWN_2 | FLAG_UNKNOWN_0)) == FLAG_UNKNOWN_2) {
    setOpenInit();
  }
  if ((unknown4c & (FLAG_UNKNOWN_3 | FLAG_UNKNOWN_1)) == FLAG_UNKNOWN_3) {
    setReadInit();
  }
}

bool DrResMdoSeamRead::isRead() {
  if (unknown4c & FLAG_UNKNOWN_2) {
    for (int i = 0; i < 8; i++) {
      if (DevFileTh::rfIsBusy(unknown08[i])) {
        return true;
      }
    }
    return false;
  }
  if (unknown4c & FLAG_UNKNOWN_3) {
    for (int i = 0; i < 8; i++) {
      if (unknown08[i] != nullptr) {
        return true;
      }
    }
  }
  return false;
}

void DrResMdoSeamRead::readCancel() {}

bool DrResMdoSeamRead::read(int &handleNum, u32 offset, u32 size, DrResMdoSeamMemObj *memObj) {
  int num = getFileHandleNum();
  if (num == -1) {
    return false;
  }
  u16 bit = 1 << num;
  unknown4a &= ~bit;
  unknown48 |= bit;
  int padding = 0;
  if (static_cast<int>(size) % 0x40 != 0) {
    padding = 0x40 - static_cast<int>(size) % 0x40;
  }
  size += padding;
  DevFileParamTh param;
  param.unknown4c = offset;
  param.unknown50 = size;
  param.unknown40 = memObj->m_buffer;
  param.unknown48 = memObj->m_size;
  param.unknown68 = DrMan::get()->unknown1d94;
  if (unknown4c & FLAG_UNKNOWN_2) {
    DevFileTh::rfRead(unknown08[num], param);
  } else {
    param.unknown00 = unknown50;
    param.unknown60 = this;
    unknown08[num] = DevFileTh::readFile(param);
  }
  handleNum = num;
  return true;
}

bool DrResMdoSeamRead::readColi(int &handleNum, u32 offset, u32 size, DrResMdoSeamMemObj *memObj) {
  int num = getFileHandleNum();
  if (num == -1) {
    return false;
  }
  u16 bit = 1 << num;
  unknown4a &= ~bit;
  unknown48 |= bit;
  int padding = 0;
  if (static_cast<int>(size) % 0x40 != 0) {
    padding = 0x40 - static_cast<int>(size) % 0x40;
  }
  size += padding;
  DevFileParamTh param;
  param.unknown4c = offset;
  param.unknown50 = size;
  param.unknown40 = memObj->m_buffer;
  param.unknown48 = memObj->m_size;
  param.unknown68 = DrMan::get()->unknown1d94;
  if (unknown4c & FLAG_UNKNOWN_2) {
    DevFileTh::rfRead(unknown08[num], param);
  } else {
    param.unknown00 = unknown50;
    param.unknown60 = this;
    unknown08[num] = DevFileTh::readFile(param);
  }
  handleNum = num;
  return true;
}

int DrResMdoSeamRead::getFileHandleNum() {
  if (unknown4c & FLAG_UNKNOWN_3) {
    for (int i = 0; i < 8; i++) {
      if (!(unknown48 & (1 << i)) && unknown08[i] == nullptr) {
        return i;
      }
    }
  } else if (unknown4c & FLAG_UNKNOWN_2) {
    for (int i = 0; i < 8; i++) {
      if (!(unknown48 & (1 << i)) && !DevFileTh::rfIsBusy(unknown08[i])) {
        return i;
      }
    }
  }
  return -1;
}

bool DrResMdoSeamRead::OnFileEvent(EventFileTh *event) {
  for (int i = 0; i < 8; i++) {
    if (unknown08[i] == event->unknown08 && event->type == EventFileTh::TYPE_COMPLETE) {
      unknown4a |= 1 << i;
      if (unknown4c & FLAG_UNKNOWN_3) {
        unknown08[i] = nullptr;
      }
      return true;
    }
  }
  return false;
}

int DrResMdoSeamRead::getReadMax() {
  int count = 0;
  if (unknown4c & FLAG_UNKNOWN_3) {
    for (int i = 0; i < 8; i++) {
      if (!(unknown48 & (1 << i)) && unknown08[i] == nullptr) {
        count++;
      }
    }
  } else if (unknown4c & FLAG_UNKNOWN_2) {
    for (int i = 0; i < 8; i++) {
      if (!(unknown48 & (1 << i)) && !DevFileTh::rfIsBusy(unknown08[i])) {
        count++;
      }
    }
  }
  return count;
}

} // namespace ml
