#pragma once
#include <stddef.h>

#include "dr/dr_res_list.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrCalcClipObj;
class DrCalcCpPlaneObj;
class DrCalcViewWork;
class DrMan;

class DrCalcClipMan {
public:
  // Inferred role: links of a doubly linked list (the previous and next element of a node, the first and last element of a list); original type name unknown.
  template <typename T> struct unknown009 {
    T *unknown00; // Inferred role: previous element or first element; original member name unknown.
    T *unknown08; // Inferred role: next element or last element; original member name unknown.

    // Inferred role: appends an element to the list; original name unknown.
    void unknown010(T *element) {
      if (unknown08 == nullptr) {
        unknown00 = element;
        unknown08 = element;
        element->unknown00 = nullptr;
      } else {
        unknown08->unknown08 = element;
        element->unknown00 = unknown08;
        unknown08 = element;
      }
      element->unknown08 = nullptr;
    }

    // Inferred role: removes an element from the list; original name unknown.
    void unknown011(T *element) { unknown001(unknown00, unknown08, element); }

    // Inferred role: deletes every element of the list; original name unknown.
    void unknown012() {
      T *element = unknown00;
      while (element != nullptr) {
        T *next = element->unknown08;
        delete element;
        element = next;
      }
      unknown00 = nullptr;
      unknown08 = nullptr;
    }
  };

  DrCalcClipMan(DrMan *man, DrCalcViewWork *viewWork);
  ~DrCalcClipMan();
  void release();
  void update();
  void calcBitTbl();
  bool testObjectClip(const mm::Vec3 &position, f32 radius);
  bool testPlaneClip(const mm::Vec3 &position, f32 radius);
  DrCalcClipObj *createClipObj(const void *data);
  DrCalcCpPlaneObj *createCpPlaneObj(const void *data);

  DrMan *unknown00;                          // Inferred role: dr man; original member name unknown.
  DrCalcViewWork *unknown08;                 // Inferred role: view work; original member name unknown.
  unknown009<DrCalcClipObj> unknown10;       // Inferred role: clip objects in use; original member name unknown.
  unknown009<DrCalcClipObj> unknown20[2];    // Inferred role: new clip objects per double buffer index; original member name unknown.
  unknown009<DrCalcCpPlaneObj> unknown40;    // Inferred role: clip plane objects in use; original member name unknown.
  unknown009<DrCalcCpPlaneObj> unknown50[2]; // Inferred role: new clip plane objects per double buffer index; original member name unknown.
  u32 *unknown70;                            // Inferred role: clip flags; original member name unknown.
  s32 unknown78;                             // Inferred role: size of the clip flags; original member name unknown.
  u32 unknown7c;                             // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrCalcClipMan, unknown08) == 0x08, "");
static_assert(offsetof(DrCalcClipMan, unknown10) == 0x10, "");
static_assert(offsetof(DrCalcClipMan, unknown20) == 0x20, "");
static_assert(offsetof(DrCalcClipMan, unknown40) == 0x40, "");
static_assert(offsetof(DrCalcClipMan, unknown50) == 0x50, "");
static_assert(offsetof(DrCalcClipMan, unknown70) == 0x70, "");
static_assert(offsetof(DrCalcClipMan, unknown78) == 0x78, "");
static_assert(offsetof(DrCalcClipMan, unknown7c) == 0x7c, "");
static_assert(sizeof(DrCalcClipMan) == 0x80, "");

} // namespace ml
