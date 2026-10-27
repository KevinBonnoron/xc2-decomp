#include "ssd/ssd_allocator.h"
#include "ssd/ssd_command_manager.h"
#include "ssd/ssd_sound.h"

namespace ssd {

void HandlePlay::Exec() { unknown08->Play(unknown10, unknown18, unknown20, unknown24); }

void CommandManager::CommandBuffer::Init(int size) {
  Allocator::Block *block = SoundMemory::allocator_->NewInstanceImpl(sizeof(unknown002), size, 16);
  unknown002 *slots;
  if (block != nullptr) {
    slots = static_cast<unknown002 *>(block->unknown08);
  } else {
    slots = nullptr;
  }
  unknown00 = slots;
  unknown08 = 0;
}

void CommandManager::CommandBuffer::Quit() {
  unknown002 *slots = unknown00;
  Allocator *allocator = SoundMemory::allocator_;
  Allocator::Block *block = allocator->GetMemoryBlock(slots);
  if (block != nullptr) {
    allocator->DeleteInstanceImpl(block);
  }
}

void CommandManager::Quit() {
  unknown00[0].Quit();
  unknown00[1].Quit();
}

void CommandManager::ExecuteCommands() {
  for (int i = 0; i < unknown28->unknown08; i++) {
    unknown001 *command = unknown28->unknown00[i].unknown00;
    command->Exec();
    command->~unknown001();
  }
}

} // namespace ssd
