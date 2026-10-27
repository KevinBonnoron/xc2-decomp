#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

class SoundActor;
class SoundEntry;
class SoundHandle;

class CommandManager {
public:
  // Inferred role: base of the queued commands; original name unknown.
  class unknown001 {
  public:
    virtual ~unknown001() {}
    virtual void Exec() = 0;
  };

  // Inferred role: slot of a command buffer holding a command; original name unknown.
  struct unknown002 {
    unknown001 *unknown00; // Inferred role: command stored in unknown08; original member name unknown.
    u8 unknown08[0x80];    // Inferred role: command storage; original member name unknown.
  };

  struct CommandBuffer {
    void Init(int size);
    void Quit();

    unknown002 *unknown00; // Inferred role: command slots; original member name unknown.
    int unknown08;         // Inferred role: command count; original member name unknown.
  };

  void Quit();
  void ExecuteCommands();

  CommandBuffer unknown00[2]; // Inferred role: double buffered commands; original member name unknown.
  CommandBuffer *unknown20;   // Inferred role: buffer receiving commands; original member name unknown.
  CommandBuffer *unknown28;   // Inferred role: buffer being executed; original member name unknown.
  int unknown30;              // Inferred role: command slot count; original member name unknown.
};

static_assert(sizeof(CommandManager::unknown002) == 0x88, "");
static_assert(sizeof(CommandManager::CommandBuffer) == 0x10, "");
static_assert(offsetof(CommandManager, unknown20) == 0x20, "");
static_assert(offsetof(CommandManager, unknown28) == 0x28, "");
static_assert(offsetof(CommandManager, unknown30) == 0x30, "");

class HandlePlay : public CommandManager::unknown001 {
public:
  ~HandlePlay() override { unknown08 = nullptr; }
  void Exec() override;

  SoundHandle *unknown08;      // Inferred role: sound handle; original member name unknown.
  const SoundEntry *unknown10; // Inferred role: sound entry; original member name unknown.
  SoundActor *unknown18;       // Inferred role: sound actor; original member name unknown.
  f32 unknown20;               // Inferred role: volume; original member name unknown.
  f32 unknown24;               // Inferred role: fade time; original member name unknown.
};

static_assert(offsetof(HandlePlay, unknown08) == 0x8, "");
static_assert(offsetof(HandlePlay, unknown24) == 0x24, "");
static_assert(sizeof(HandlePlay) == 0x28, "");

} // namespace ssd
