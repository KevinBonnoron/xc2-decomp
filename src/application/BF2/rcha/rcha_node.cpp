#include "rcha/rcha_node.h"

#include "mm_mtl/fixstr.h"

u32 RchaNode::hashStr(const char *name) const {
  if (name == nullptr || *name == '\0') {
    return 0;
  }
  u32 hash = 0x811c9dc5;
  const char *position = name;
  int length = 0;
  while (*position != '\0' && length < 128) {
    hash = (hash * 0x1000193) ^ static_cast<u8>(*position);
    position++;
    length++;
  }
  return hash;
}

void RchaNode::clear() {
  unknown1994 = 0;
  unknown1998 = 0;
  unknown199c = 0;
  for (int i = 0; i < TRACK_UNKNOWN_48; i++) {
    RchaAnm &anm = unknown10[i];
    anm.unknown001();
    anm.unknown00 = "";
    anm.unknown80 = false;
    anm.unknown70 = 0.0f;
    anm.unknown74 = 0;
    anm.unknown78 = nullptr;
  }
  unknown1990 = 0;
}
