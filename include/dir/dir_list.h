#pragma once
#include <stddef.h>

#include "types.h"

namespace dir {

// Layout evidence: SingleListNode::SingleListNode 0x7100141198 and the vtable _ZTVN3dir14SingleListNodeE.
class SingleListNode {
public:
  SingleListNode();
  virtual ~SingleListNode() {}
  void InitVariable();
  virtual void Reset();

  SingleListNode *unknown08; // Inferred role: next node of the circular list; original member name unknown.
  u8 unknown10;              // Inferred role: reset by the constructor and Reset; original member name unknown.
  s32 unknown14;             // Inferred role: reset to -1 by the constructor and Reset; original member name unknown.
};

static_assert(offsetof(SingleListNode, unknown08) == 0x08, "");
static_assert(offsetof(SingleListNode, unknown10) == 0x10, "");
static_assert(offsetof(SingleListNode, unknown14) == 0x14, "");
static_assert(sizeof(SingleListNode) == 0x18, "");

// Layout evidence: SingleListHeader::InsertTop 0x71001411e0 (the head of the circular list lies at offset 0x08).
class SingleListHeader {
public:
  virtual ~SingleListHeader() {}
  SingleListNode *InsertTop(SingleListNode *node);
  SingleListNode *InsertEnd(SingleListNode *node);
  SingleListNode *InsertPrev(SingleListNode *position, SingleListNode *node);
  SingleListNode *InsertNext(SingleListNode *position, SingleListNode *node);
  SingleListNode *Remove(SingleListNode *node);

  SingleListNode *unknown08; // Inferred role: head of the circular list; original member name unknown.
};

static_assert(offsetof(SingleListHeader, unknown08) == 0x08, "");
static_assert(sizeof(SingleListHeader) == 0x10, "");

// Layout evidence: DoubleListNode::DoubleListNode 0x71001413f0 and the vtable _ZTVN3dir14DoubleListNodeE.
class DoubleListNode {
public:
  DoubleListNode();
  virtual ~DoubleListNode() {}
  void InitVariable();
  virtual void Reset();

  DoubleListNode *unknown08; // Inferred role: next node of the circular list; original member name unknown.
  DoubleListNode *unknown10; // Inferred role: previous node of the circular list; original member name unknown.
  u8 unknown18;              // Inferred role: reset by the constructor and Reset; original member name unknown.
  s32 unknown1c;             // Inferred role: reset to -1 by the constructor and Reset; original member name unknown.
};

static_assert(offsetof(DoubleListNode, unknown08) == 0x08, "");
static_assert(offsetof(DoubleListNode, unknown10) == 0x10, "");
static_assert(offsetof(DoubleListNode, unknown18) == 0x18, "");
static_assert(offsetof(DoubleListNode, unknown1c) == 0x1c, "");
static_assert(sizeof(DoubleListNode) == 0x20, "");

// Layout evidence: DoubleListHeader::InsertTop 0x710014143c (the head of the circular list lies at offset 0x08).
class DoubleListHeader {
public:
  DoubleListHeader() : unknown08(nullptr) {}
  virtual ~DoubleListHeader() {}
  DoubleListNode *InsertTop(DoubleListNode *node);
  DoubleListNode *InsertEnd(DoubleListNode *node);
  DoubleListNode *InsertPrev(DoubleListNode *position, DoubleListNode *node);
  DoubleListNode *InsertNext(DoubleListNode *position, DoubleListNode *node);
  DoubleListNode *Remove(DoubleListNode *node);

  DoubleListNode *unknown08; // Inferred role: head of the circular list; original member name unknown.
};

static_assert(offsetof(DoubleListHeader, unknown08) == 0x08, "");
static_assert(sizeof(DoubleListHeader) == 0x10, "");

// The vtable of this template holds DoubleListHeader::~DoubleListHeader and the deleting destructor, as the game's
// _ZTVN3dir16TChildListHeaderINS_13ChildListNodeEEE and _ZTVN3dir16TChildListHeaderINS_9VwProcessEEE.
template <typename T> class TChildListHeader : public DoubleListHeader {};

// Layout evidence: ChildListNode::ChildListNode 0x7100141110 and the vtable _ZTVN3dir13ChildListNodeE.
class ChildListNode : public DoubleListNode {
public:
  ChildListNode();
  void InitVariable();
  void Reset() override;

  ChildListNode *unknown20; // Inferred role: parent node, null for a root node; original member name unknown.
  u8 _28[0x38 - 0x28];
  TChildListHeader<ChildListNode> unknown38; // Inferred role: list of the children; original member name unknown.
};

static_assert(offsetof(ChildListNode, unknown20) == 0x20, "");
static_assert(offsetof(ChildListNode, unknown38) == 0x38, "");
static_assert(sizeof(ChildListNode) == 0x48, "");

} // namespace dir
