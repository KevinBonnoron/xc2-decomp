// Original file name from the game string C:/Monolithsoft/BF2/prog/libs/aiLib/src/ailib/behavior/ai_behavior_tree.cpp.
#include "ai/ai_behavior_tree.h"

#include "ai/ai_behavior_decorator.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h" // IWYU pragma: keep
#include "mm_mtl/vector.h"        // IWYU pragma: keep

template void mm::mtl::Vector<mm::mtl::IntrusivePtr<ai::BehaviorNode>>::destroy();
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<ai::BehaviorNode>>::expand(size_t, size_t);
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<ai::BehaviorNode>>::extend(size_t, size_t, const mm::mtl::IntrusivePtr<ai::BehaviorNode> &);
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<ai::BehaviorNode>>::push_back(const mm::mtl::IntrusivePtr<ai::BehaviorNode> &);
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<ai::BehaviorNode>>::resize(size_t, const mm::mtl::IntrusivePtr<ai::BehaviorNode> &);
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<ai::BehaviorNodeInfo>>::destroy();
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<ai::BehaviorNodeInfo>>::expand(size_t, size_t);

namespace ai {

BehaviorTree::BehaviorTree() : m_rootNode(), unknown40(), m_pNodes(), m_pAllocator(nullptr), m_setup(false) {}

BehaviorTree::~BehaviorTree() {}

BlackBoard::BlackBoard() {}

BlackBoard::~BlackBoard() {}

const mm::mtl::RTTI *BlackBoard::getRTTI() const { return &m_rtti; }

BehaviorNode::BehaviorNode(const char *name, u32 flags) : unknown30(false), unknown34(flags) { unknown0c = name; }

BehaviorNode::~BehaviorNode() {}

const mm::mtl::RTTI *BehaviorNode::getRTTI() const { return &m_rtti; }

bool BehaviorNode::execute(BlackBoard &blackBoard) { return true; }

bool BehaviorNode::checkCondition(const BlackBoard &blackBoard) { return true; }

void BehaviorTree::beginSetup(u32 nodeNum, mm::mtl::IAllocator *allocator) {
  m_pAllocator = allocator;
  m_pNodes.setAllocator(allocator);
  m_pNodes.resize(nodeNum, nullptr);
  m_setup = true;
}

void BehaviorTree::endSetup() { m_setup = false; }

void BehaviorTree::cleanup() {
  for (u32 i = 0; i < m_pNodes.size(); i++) {
    if (m_pNodes[i].get() != nullptr) {
      if ((m_pNodes[i]->unknown34 & 4) != 0) {
        DestroyEvent event;
        m_pNodes[i]->onEvent(*unknown40, event);
      }
    }
  }
  m_pNodes.clear();
  unknown40.reset();
  m_pNodes.setAllocator(nullptr);
  m_pAllocator = nullptr;
}

void BehaviorTree::attachRoot(u32 nodeID) {
  BehaviorNode *pNode = m_pNodes[nodeID].get();
#line 88
  MM_ASSERT(pNode);
  m_rootNode.attachChild(pNode);
}

void BehaviorTree::attachComposite(u32 parentID, u32 childID, u32 index) {
  BehaviorNode *pNode = m_pNodes[parentID].get();
  CompositeNode *pComposite = nullptr;
  if (pNode != nullptr && pNode->getRTTI()->isKindOf(&CompositeNode::m_rtti)) {
    pComposite = static_cast<CompositeNode *>(pNode);
  }
#line 104
  MM_ASSERT(pComposite);
  BehaviorNode *pChildNode = m_pNodes[childID].get();
#line 107
  MM_ASSERT(pChildNode);
  pComposite->attachChild(index, pChildNode);
}

void BehaviorTree::attachDecorator(u32 nodeID, u32 childID) {
  BehaviorNode *pNode = m_pNodes[nodeID].get();
  DecoratorNode *pDecorator = nullptr;
  if (pNode != nullptr && pNode->getRTTI()->isKindOf(&DecoratorNode::m_rtti)) {
    pDecorator = static_cast<DecoratorNode *>(pNode);
  }
#line 121
  MM_ASSERT(pDecorator);
  BehaviorNode *pChildNode = m_pNodes[childID].get();
#line 124
  MM_ASSERT(pChildNode);
  pDecorator->attachChild(pChildNode);
}

void BehaviorTree::execute() {
  BlackBoard *pBB = unknown40.get();
#line 157
  MM_ASSERT(pBB);
  bool result = m_rootNode.execute(*pBB);
  m_rootNode.setActive(*pBB, result);
}

void BehaviorTree::queryNode(mm::mtl::IAllocator *allocator, BehaviorNodeInfo *info) const {
  BehaviorNode *pChildNode = m_rootNode.m_pChildNode;
  if (pChildNode == nullptr) {
    return;
  }
  info->unknown10 = pChildNode->unknown0c.c_str();
  info->unknown18 = pChildNode->unknown30;
  info->unknown20.setAllocator(allocator);
  collectChildNode(pChildNode, allocator, info);
}

// Inferred helper: creates the info record of a child node, appends it to the list of the parent and collects the children of the child; original name unknown. The game
// inlines it into both arms of collectChildNode (1.0.0: 0x7100942450, 321 instructions). Without `inline` it stays a call (110 instructions, cost above the threshold of 275); the
// block written out in both arms also gives the game's 321, so ruling 8 does not apply and the block is written once (P4).
static inline void unknown002(const BehaviorTree *tree, BehaviorNode *pChildNode, mm::mtl::IAllocator *allocator, BehaviorNodeInfo *info) {
  void *buffer = allocator->allocate(sizeof(BehaviorNodeInfo), alignof(BehaviorNodeInfo));
  mm::mtl::IntrusivePtr<BehaviorNodeInfo> childInfo(new (buffer) BehaviorNodeInfo);
  info->unknown20.push_back(childInfo);
  BehaviorNodeInfo &childInfoRef = *childInfo;
  childInfoRef.unknown10 = pChildNode->unknown0c.c_str();
  childInfoRef.unknown18 = pChildNode->unknown30;
  childInfoRef.unknown20.setAllocator(allocator);
  tree->collectChildNode(pChildNode, allocator, &childInfoRef);
}

void BehaviorTree::collectChildNode(BehaviorNode *node, mm::mtl::IAllocator *allocator, BehaviorNodeInfo *info) const {
  if (node == nullptr) {
    return;
  }
  if (node->getRTTI()->isKindOf(&CompositeNode::m_rtti)) {
    const CompositeNode *pComposite = static_cast<CompositeNode *>(node);
    u32 childNum = pComposite->m_childNodes.size();
    info->unknown20.reserve(childNum);
    for (u32 i = 0; i < childNum; i++) {
      BehaviorNode *pChildNode = pComposite->m_childNodes[i];
      if (pChildNode != nullptr) {
        unknown002(this, pChildNode, allocator, info);
      }
    }
  } else if (node->getRTTI()->isKindOf(&DecoratorNode::m_rtti)) {
    DecoratorNode *pDecorator = static_cast<DecoratorNode *>(node);
    BehaviorNode *pChildNode = pDecorator->m_pChildNode;
    if (pChildNode != nullptr) {
      unknown002(this, pChildNode, allocator, info);
    }
  }
}

} // namespace ai
