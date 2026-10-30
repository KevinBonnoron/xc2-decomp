#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

enum LAYER_TYPE {
  LAYER_OBJ_TYPE_OBJ = 1,
  LAYER_OBJ_TYPE_FONT = 2,
  LAYER_OBJ_TYPE_LAYOUT = 3,
  LAYER_OBJ_TYPE_TEX = 4,
  LAYER_OBJ_TYPE_MEM = 5,
  LAYER_OBJ_TYPE_POLY = 6,
  LAYER_OBJ_TYPE_MASK = 7,
  LAYER_OBJ_TYPE_FILTER = 8,
  LAYER_OBJ_TYPE_FONT_STYLE = 9,
  LAYER_OBJ_TYPE_FONT_RES = 10,
  LAYER_TYPE_UNKNOWN_11 = 11, // Inferred role: font icon object; original enumerator name unknown.
  LAYER_TYPE_UNKNOWN_12 = 12, // Inferred role: font color map object; original enumerator name unknown.
};

class LayerBase {
public:
  LayerBase() : unknown08(nullptr), unknown10(nullptr), unknown1c(0xcc) {}
  virtual ~LayerBase() {}
  virtual void release();

  // Inferred layout of a list of objects linked through unknown08 and unknown10; original type name unknown.
  struct unknown001 {
    void unknown002(LayerBase *node) {
      if (unknown08 == nullptr) {
        unknown00 = node;
        unknown08 = node;
        node->unknown08 = nullptr;
      } else {
        unknown08->unknown10 = node;
        node->unknown08 = unknown08;
        unknown08 = node;
      }
      node->unknown10 = nullptr;
      unknown10++;
    }

    void unknown004(LayerBase *node) {
      LayerBase *prev = node->unknown08;
      LayerBase *next = node->unknown10;
      if (prev == nullptr) {
        if (next == nullptr) {
          unknown00 = nullptr;
          unknown08 = nullptr;
        } else {
          unknown00 = next;
          next->unknown08 = nullptr;
        }
      } else if (next == nullptr) {
        unknown08 = prev;
        prev->unknown10 = nullptr;
      } else {
        prev->unknown10 = next;
        node->unknown10->unknown08 = node->unknown08;
      }
      node->unknown08 = nullptr;
      node->unknown10 = nullptr;
      unknown10--;
    }

    void unknown003() {
      LayerBase *node = unknown00;
      while (node != nullptr) {
        LayerBase *next = node->unknown10;
        delete node;
        node = next;
      }
      unknown10 = 0;
      unknown00 = nullptr;
      unknown08 = nullptr;
    }

    LayerBase *unknown00; // Inferred role: first object; original member name unknown.
    LayerBase *unknown08; // Inferred role: last object; original member name unknown.
    s32 unknown10;        // Inferred role: object count; original member name unknown.
  };

  LayerBase *unknown08; // Inferred role: previous node; original member name unknown.
  LayerBase *unknown10; // Inferred role: next node; original member name unknown.
  int unknown18;        // Inferred role: type; original member name unknown.
  u8 unknown1c;         // Inferred role: state, 0xcc once constructed and 0x22 once released; original member name unknown.
};

static_assert(offsetof(LayerBase, unknown08) == 0x08, "");
static_assert(offsetof(LayerBase, unknown10) == 0x10, "");
static_assert(offsetof(LayerBase, unknown18) == 0x18, "");
static_assert(offsetof(LayerBase, unknown1c) == 0x1c, "");
static_assert(sizeof(LayerBase::unknown001) == 0x18, "");

} // namespace layer
