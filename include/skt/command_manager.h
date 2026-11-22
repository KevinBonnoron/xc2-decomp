#pragma once
#include <stddef.h>

#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mm_thread/mm_thread_csection.h"
#include "mm_thread/mm_thread_refcount.h"
#include "skt/fixed_vector.h"
#include "types.h"

namespace mm {
namespace threading {
class Thread;
} // namespace threading
} // namespace mm

namespace skt {

class CommandManager;

// Inferred role: parsed argument of a command; original type name unknown.
struct unknown001 {
  const char *unknown00; // Inferred role: argument string, read by CommandParam::getArg; original member name unknown.
  u32 unknown08;         // Inferred role: argument type; original member name unknown.
};

class CommandParam {
public:
  void parseCommand(s8 separator);
  bool isValid(int index) const;
  const char *getArg(int index) const;
  mm::mtl::FixStr<128> getStr(int index) const;
  bool getS32(int index, int &value) const;
  bool getF32(int index, f32 &value) const;

  char unknown000[0x400];                 // Inferred role: command line parsed by parseCommand; original member name unknown.
  char unknown400[0x400];                 // Inferred role: copy of the command line split in place into arguments; original member name unknown.
  FixedVector<unknown001, 32> unknown800; // Inferred role: arguments; original member name unknown.
  void *unknowna08;                       // Inferred role: binary data of the command, allocated by recvBinary; original member name unknown.
  u32 unknowna10;                         // Inferred role: size of the binary data; original member name unknown.
};

static_assert(sizeof(unknown001) == 0x10, "");
static_assert(offsetof(CommandParam, unknown400) == 0x400, "");
static_assert(offsetof(CommandParam, unknown800) == 0x800, "");
static_assert(offsetof(CommandParam, unknowna08) == 0xa08, "");
static_assert(offsetof(CommandParam, unknowna10) == 0xa10, "");
static_assert(sizeof(CommandParam) == 0xa18, "");

class ICommandCallback {
public:
  virtual void OnRecv(const CommandParam &param) = 0;
  virtual void OnDisconnect(const char *name) {}
};

struct PortRegistInfo {
  PortRegistInfo() : m_iCommandCallback(nullptr), unknownb8(-2), unknownbc(0), unknownc0(0x10000), unknownc4(' ') {}

  u16 unknown00; // Inferred role: port number; original member name unknown.
  u8 _02[0x04 - 0x02];
  mm::mtl::FixStr<32> unknown04;        // Inferred role: server name; original member name unknown.
  mm::mtl::FixStr<128> unknown28;       // Role and original member name unknown.
  ICommandCallback *m_iCommandCallback; // Inferred role: receive callback; original member name unknown.
  int unknownb8;                        // Role and original member name unknown.
  u32 unknownbc;                        // Role and original member name unknown.
  u32 unknownc0;                        // Inferred role: buffer size; original member name unknown.
  char unknownc4;                       // Inferred role: argument separator; original member name unknown.
};

static_assert(offsetof(PortRegistInfo, unknown04) == 0x04, "");
static_assert(offsetof(PortRegistInfo, unknown28) == 0x28, "");
static_assert(offsetof(PortRegistInfo, m_iCommandCallback) == 0xb0, "");
static_assert(offsetof(PortRegistInfo, unknownb8) == 0xb8, "");
static_assert(offsetof(PortRegistInfo, unknownc4) == 0xc4, "");
static_assert(sizeof(PortRegistInfo) == 0xc8, "");

// Name given by the xc2 symbols of CommandManager::openServer and setServerOption; the enumerators are unknown.
enum SERVER_OPTION : int {
  SERVER_OPTION_UNKNOWN_1 = 1, // Inferred role: port that does not send commands, read by sendCommand; original name unknown.
  SERVER_OPTION_UNKNOWN_2 = 2, // Inferred role: port that does not queue received commands, read by recvCommand; original name unknown.
};

// Name given by the xc2 symbol _ZN3skt14CommandManager10removePortEPKcNS_12NETWORK_MODEE; the enumerators are unknown.
enum NETWORK_MODE {
  NETWORK_MODE_UNKNOWN_1 = 1, // Inferred role: server port; original name unknown.
  NETWORK_MODE_UNKNOWN_2 = 2, // Inferred role: client port; original name unknown.
  NETWORK_MODE_UNKNOWN_3 = 3, // Inferred role: htcs port; original name unknown.
};

// Inferred role: name and number of an htcs port; original type name unknown.
struct unknown002 {
  u16 unknown00;                 // Inferred role: port number, read by CommandManager::getTargetPortNo; original member name unknown.
  mm::mtl::FixStr<32> unknown04; // Inferred role: port name; original member name unknown.
};

static_assert(offsetof(unknown002, unknown04) == 0x04, "");
static_assert(sizeof(unknown002) == 0x28, "");

// Inferred role: connection of a port, reference counted; original type name unknown.
class unknown003 : public mm::threading::ReferenceObject {
public:
  // The game releases this object without the assertion on m_allocator that ReferenceObject::release has, and reads the allocator before the
  // destructor runs (PortInfo::destroy 0x71009831a0-0x71009831d8); the release of the thread next to it (0x710098313c) is ReferenceObject's.
  void release() {
    if ((--unknown08 & 0xffff) == 0) {
      mm::mtl::IAllocator *allocator = m_allocator;
      this->~unknown003();
      allocator->deallocate(this);
    }
  }

  virtual void unknown10() = 0;                        // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
  virtual void unknown18() = 0;                        // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
  virtual void unknown20(const char *command) = 0;     // Inferred role: sends a command, called by sendCommand and sendCommandHtcs; original name unknown.
  virtual void unknown28() = 0;                        // Inferred role: vtable slot not called by the matched code; original name and signature unknown.
  virtual void unknown30(CommandManager *manager) = 0; // Inferred role: thread body of the port, called by thServerExecute and thClientExecute; original name unknown.
};

} // namespace skt

namespace mm {
namespace mtl {

// The game's skt code has the older PtrSingleton (decision 56): its constructor has no get() == 0 assertion. CommandManager::create 0x710098468c
// inlines the constructor and stores the instance with no test, and the constructor 0x7100983314 does the same; every other PtrSingleton in the game
// (for example ml::ProcDesktop's, 0x710075e508) calls mm::MMStdBase::mmAssert there. A full specialization keeps the names and symbols of
// mm::mtl::PtrSingleton<skt::CommandManager> (vtable 0x71011b9b88, sys()::s_instance 0x7101bd9cc0, destructors 0x7100984c1c and 0x7100984c3c)
// while include/mm_mtl/singleton.h stays the template everywhere else.
template <> class PtrSingleton<skt::CommandManager> {
public:
  PtrSingleton();

  virtual ~PtrSingleton() { sys() = nullptr; }

  static skt::CommandManager *get() { return sys(); }

  static skt::CommandManager *&sys() {
    static skt::CommandManager *s_instance;
    return s_instance;
  }
};

} // namespace mtl
} // namespace mm

namespace skt {

class CommandManager : public mm::mtl::PtrSingleton<CommandManager> {
public:
  struct PortInfo {
    // The game inlines this constructor into openServer (0x71009835c0, stores at 0x7100983684-0x71009836ac): unknown00 = 0x10000 and unknown04 = 0
    // (stp), the FixStr unknown0c (terminator at 0x0c, length 0 at 0x2c), unknown30 = ' ', the count of unknown50 (0x150), m_iCommandCallback, unknown40 and
    // unknown48 = 0. unknown158 and unknown15c are not set. Same defaults as PortRegistInfo's constructor for the matching members.
    PortInfo() : unknown00(0x10000), unknown04(0), unknown30(' '), m_iCommandCallback(nullptr), unknown40(nullptr), unknown48(nullptr) {}

    void destroy();

    u32 unknown00; // Inferred role: buffer size, copied from PortRegistInfo by openServer; original member name unknown.
    u32 unknown04; // Inferred role: port id, read by findPortInfoFromID; original member name unknown.
    u16 unknown08; // Inferred role: port number, copied from PortRegistInfo by openServer; original member name unknown.
    u8 _0a[0x0c - 0x0a];
    mm::mtl::FixStr<32> unknown0c; // Inferred role: port name; original member name unknown.
    char unknown30;                // Inferred role: argument separator, copied from PortRegistInfo by openServer; original member name unknown.
    u8 _31[0x38 - 0x31];
    ICommandCallback *m_iCommandCallback;      // Inferred role: callback notified by notifyDisconnect; original member name unknown.
    mm::threading::Thread *unknown40;          // Inferred role: thread of the port, stopped and joined by destroy and copied whole by mtl::copy<PortInfo> (0x7100984cf0); original member name unknown.
    unknown003 *unknown48;                     // Inferred role: connection of the port; original member name unknown.
    FixedVector<CommandParam *, 32> unknown50; // Inferred role: received commands; original member name unknown.
    NETWORK_MODE unknown158;                   // Inferred role: kind of port; original member name unknown.
    SERVER_OPTION unknown15c;                  // Inferred role: server option; original member name unknown.
  };

  CommandManager(mm::mtl::IAllocator *allocator);
  ~CommandManager();

  static CommandManager *create(mm::mtl::IAllocator *allocator);
  static void destroy();
  void finalize();
  static mm::mtl::IAllocator *getAllocator();
  static bool sendCommand(const char *server, const char *command);
  static bool sendCommandHtcs(const char *server, const char *command);
  static bool openServer(const PortRegistInfo &info, SERVER_OPTION option);
  static void closeServer(const char *server);
  static bool openClient(const PortRegistInfo &info);
  static void closeClient(const char *server);
  static bool isConnectedHtcs(const char *server);
  static bool setServerOption(const char *server, SERVER_OPTION option);
  static void recvCommand(u32 id, const char *command, u32 size);
  static void recvBinary(u32 id, const char *command, const char *data, u32 size);
  static void notifyDisconnect(u32 id);
  static void updateCallback();
  static u32 thServerExecute(void *argument);
  static u32 thClientExecute(void *argument);
  static bool updateHtcsPortInfo(size_t unknown);

  PortInfo *findPortInfo(u16 port, const char *name);
  PortInfo *findPortInfoFromID(u32 id);
  PortInfo *findHtcsPortInfo(const char *name);
  PortInfo *findPortInfoExcludeHtcs(const char *name);
  u16 getTargetPortNo(const char *name);
  void removePort(const char *name, NETWORK_MODE mode);

  FixedVector<PortInfo, 32> unknown08;     // Inferred role: ports; original member name unknown.
  FixedVector<unknown002, 32> unknown2c10; // Inferred role: htcs ports; original member name unknown.
  mm::mtl::IAllocator *m_allocator;
  mm::threading::CriticalSection unknown3120; // Inferred role: lock of the port tables; original member name unknown.
  bool unknown3148;                           // Inferred role: running flag; original member name unknown.
  u8 _3149[0x314c - 0x3149];
  u32 unknown314c; // Inferred role: last port id given out by openServer; original member name unknown.
  u32 unknown3150; // Inferred role: first port id, the counter wraps to it; original member name unknown.
  u32 unknown3154; // Inferred role: last port id; original member name unknown.
};

static_assert(offsetof(CommandManager::PortInfo, unknown04) == 0x04, "");
static_assert(offsetof(CommandManager::PortInfo, unknown08) == 0x08, "");
static_assert(offsetof(CommandManager::PortInfo, unknown0c) == 0x0c, "");
static_assert(offsetof(CommandManager::PortInfo, unknown30) == 0x30, "");
static_assert(offsetof(CommandManager::PortInfo, m_iCommandCallback) == 0x38, "");
static_assert(offsetof(CommandManager::PortInfo, unknown40) == 0x40, "");
static_assert(offsetof(CommandManager::PortInfo, unknown48) == 0x48, "");
static_assert(offsetof(CommandManager::PortInfo, unknown50) == 0x50, "");
static_assert(offsetof(CommandManager::PortInfo, unknown158) == 0x158, "");
static_assert(offsetof(CommandManager::PortInfo, unknown15c) == 0x15c, "");
static_assert(sizeof(CommandManager::PortInfo) == 0x160, "");
static_assert(offsetof(CommandManager, unknown08) == 0x08, "");
static_assert(offsetof(CommandManager, unknown2c10) == 0x2c10, "");
static_assert(offsetof(CommandManager, m_allocator) == 0x3118, "");
static_assert(offsetof(CommandManager, unknown3120) == 0x3120, "");
static_assert(offsetof(CommandManager, unknown3148) == 0x3148, "");
static_assert(offsetof(CommandManager, unknown314c) == 0x314c, "");
static_assert(offsetof(CommandManager, unknown3154) == 0x3154, "");
static_assert(sizeof(CommandManager) == 0x3158, "");

} // namespace skt

inline mm::mtl::PtrSingleton<skt::CommandManager>::PtrSingleton() { sys() = static_cast<skt::CommandManager *>(this); }
