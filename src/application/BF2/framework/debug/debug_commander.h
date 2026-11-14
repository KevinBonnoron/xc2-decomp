#pragma once
#include <stddef.h>
#include <string.h>

#include "framework/debug/debug_input_keyboard.h"
#include "framework/manager_object.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "skt/command_manager.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {
namespace debug {

class CommandManager {
public:
  static bool sendCommand(const char *server, const char *command);
  static bool sendCommandHtcs(const char *server, const char *command);
  static bool openServer(const skt::PortRegistInfo &info);
  static void closeServer(const char *server);
  static bool isConnectedHtcs(const char *server);
  static bool setServerOption(const char *server, skt::SERVER_OPTION option);
  static skt::SERVER_OPTION getServerOption(const char *server);
};

class DebugCommander : public ManagerObject, public mm::mtl::PtrSingleton<DebugCommander>, public skt::ICommandCallback, public InputCallback {
public:
  // Inferred role: registered command callback; original type name unknown.
  struct unknown001 {
    unknown001(const char *name, bool (*callback)(const skt::CommandParam &)) : unknown00(name) { unknown88.bind(callback); }

    bool operator==(const unknown001 &other) const { return strcmp(unknown00.c_str(), other.unknown00.c_str()) == 0; }

    mm::mtl::FixStr<128> unknown00;                               // Inferred role: command name; original member name unknown.
    mm::mtl::Delegate<bool(const skt::CommandParam &)> unknown88; // Inferred role: callback; original member name unknown.
  };

  DebugCommander(mm::mtl::IAllocator *allocator, const char *name, u16 port, s8 unknown);
  ~DebugCommander() override;
  bool initialize() override;
  bool finalize() override;
  const char *getName() const override;
  void OnRecv(const skt::CommandParam &param) override;
  void onEnter() override;
  void onLeave() override;
  void onDecide(const char *command) override;
  void update();
  void registCallback(const char *name, bool (*callback)(const skt::CommandParam &));
  void removeCallback(const char *name);
  void setDebugInput(IDebugInput *input);
  void enableDebugInput(bool enable);
  void setServerOption(const char *server, skt::SERVER_OPTION option);
  skt::SERVER_OPTION getServerOption(const char *server) const;

  mm::mtl::FixedVector<unknown001, 16> unknown28; // Inferred role: command callbacks; original member name unknown.
  u16 unknownab0;                                 // Inferred role: port number; original member name unknown.
  s8 unknownab2;                                  // Role and original member name unknown.
  mm::mtl::FixStr<32> unknownab4;                 // Inferred role: server name; original member name unknown.
  mm::mtl::IAllocator *unknownad8;                // Inferred role: allocator; original member name unknown.
  IDebugInput *unknownae0;                        // Inferred role: debug input; original member name unknown.
  bool unknownae8;                                // Inferred role: debug input enabled; original member name unknown.
  skt::SERVER_OPTION m_serverOption;
};

static_assert(sizeof(DebugCommander::unknown001) == 0xa8, "");
static_assert(offsetof(DebugCommander, unknown28) == 0x28, "");
static_assert(offsetof(DebugCommander, unknownab0) == 0xab0, "");
static_assert(offsetof(DebugCommander, unknownab2) == 0xab2, "");
static_assert(offsetof(DebugCommander, unknownab4) == 0xab4, "");
static_assert(offsetof(DebugCommander, unknownad8) == 0xad8, "");
static_assert(offsetof(DebugCommander, unknownae0) == 0xae0, "");
static_assert(offsetof(DebugCommander, unknownae8) == 0xae8, "");
static_assert(offsetof(DebugCommander, m_serverOption) == 0xaec, "");
static_assert(sizeof(DebugCommander) == 0xaf0, "");

} // namespace debug
} // namespace fw
