#include "framework/memory/allocator.h"

#include "mtl/mem_manager.h"

namespace fw {

MemHandlebaseAllocator::MemHandlebaseAllocator() {}

MemHandlebaseAllocator::MemHandlebaseAllocator(mtl::ALLOC_HANDLE handle) : unknown08(handle) {}

void MemHandlebaseAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) { this->unknown08 = handle; }

mtl::ALLOC_HANDLE MemHandlebaseAllocator::getMemHandle() const { return unknown08; }

void *MemHandlebaseAllocator::allocate(size_t size, size_t alignment) { return mtl::MemManager::allocate(unknown08, size, alignment, false, "no name", 0); }

void MemHandlebaseAllocator::deallocate(void *pointer) {
  if (pointer != nullptr) {
    mtl::MemManager::deallocate(pointer, 0, false);
  }
}

Allocator::SysAllocator Allocator::m_SysAllocator;
Allocator::DebAllocator Allocator::m_DebAllocator;
Allocator::TmpAllocator Allocator::m_TmpAllocator;
Allocator::ProcAllocator Allocator::m_ProcAllocator;

mm::mtl::IAllocator *Allocator::getSysAllocator() { return &m_SysAllocator; }

mm::mtl::IAllocator *Allocator::getDebAllocator() { return &m_DebAllocator; }

mm::mtl::IAllocator *Allocator::getTmpAllocator() { return &m_TmpAllocator; }

mm::mtl::IAllocator *Allocator::getProcAllocator() { return &m_ProcAllocator; }

void Allocator::setSysMemHandle(mtl::ALLOC_HANDLE handle) { m_SysAllocator.setMemHandle(handle); }

void Allocator::setDebMemHandle(mtl::ALLOC_HANDLE handle) { m_DebAllocator.setMemHandle(handle); }

void Allocator::setTmpMemHandle(mtl::ALLOC_HANDLE handle) { m_TmpAllocator.setMemHandle(handle); }

void Allocator::setProcMemHandle(mtl::ALLOC_HANDLE handle) { m_ProcAllocator.setMemHandle(handle); }

} // namespace fw
