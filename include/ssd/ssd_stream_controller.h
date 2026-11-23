#pragma once
#include <stddef.h>

#include "nn/codec.h"
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_file_stream.h"
#include "ssd/ssd_memory_buffer.h"
#include "ssd/ssd_stream_buffer.h"
#include "ssd/ssd_wave_source.h"
#include "types.h"

namespace ssd {
enum Result : long;

class StreamController : public List<StreamController>::Node {
public:
  ~StreamController();
  s64 ResetStream();
  void ExecReadStream(Result (StreamBuffer::*read)(const void *data, u64 size, bool mark));
  int OutData(u8 *buffer, u64 size, u64 *outSize, bool *isMark);
  u32 SampleToPosition(int sample);
  void ExecCloseStream();
  void ExecSetPosition();
  void SetReadPosition(u64 position);
  int PositionToFrame(u64 position);
  void ExecAdpcmDecode();
  void ClearReadBuffer();
  s64 CloseStream();
  s64 QuitStream();
  u64 SizeToReadPosition(u64 size);
  u32 PlayTimeToPosition(f32 time);

  WaveSource m_waveSource; // Inferred role: wave source; original member name unknown.
  int unknowne8;           // Inferred role: stream id; original member name unknown.
  bool unknownec;          // Inferred role: stream thread registered; original member name unknown.
  u8 _ed[0xee - 0xed];
  bool unknownee; // Inferred role: close request; original member name unknown.
  bool unknownef; // Inferred role: initialized; original member name unknown.
  bool unknownf0; // Inferred role: open; original member name unknown.
  bool unknownf1; // Inferred role: set position done; original member name unknown.
  bool unknownf2; // Inferred role: loop enabled; original member name unknown.
  bool unknownf3; // Inferred role: end of data read; original member name unknown.
  bool unknownf4; // Inferred role: end of data reached; original member name unknown.
  bool unknownf5; // Inferred role: keep open; original member name unknown.
  bool unknownf6; // Inferred role: set position request; original member name unknown.
  bool unknownf7; // Inferred role: set position pending; original member name unknown.
  u32 unknownf8;  // Inferred role: state; original member name unknown.
  u8 _fc[0x100 - 0xfc];
  FileStream m_fileStream;                                                   // Inferred role: file stream; original member name unknown.
  Result (StreamBuffer::*unknown138)(const void *data, u64 size, bool mark); // Inferred role: pending read function; original member name unknown.
  void (StreamController::*unknown148)();                                    // Inferred role: pending callback; original member name unknown.
  StreamBuffer m_streamBuffer;                                               // Inferred role: stream buffer; original member name unknown.
  nn::codec::OpusDecoder unknown188;                                         // Inferred role: opus decoder; original member name unknown.
  void *unknown1b8;                                                          // Inferred role: allocated buffer; original member name unknown.
  u32 *unknown1c0;                                                           // Inferred role: frame position table; original member name unknown.
  u8 *unknown1c8;                                                            // Inferred role: decode output buffer; original member name unknown.
  u64 unknown1d0;                                                            // Inferred role: decode output sample count; original member name unknown.
  u64 unknown1d8;                                                            // Inferred role: decoded size; original member name unknown.
  f64 unknown1e0;                                                            // Inferred role: stream decode info time; original member name unknown.
  int unknown1e8;                                                            // Inferred role: stream decode info second value; original member name unknown.
  int unknown1ec;                                                            // Inferred role: stream decode info first value; original member name unknown.
  u32 unknown1f0;                                                            // Inferred role: opus decode state; original member name unknown.
  u8 _1f4[0x1f8 - 0x1f4];
  void *unknown1f8; // Inferred role: allocated buffer; original member name unknown.
  u8 _200[0x208 - 0x200];
  u64 unknown208; // Inferred role: read position; original member name unknown.
  u64 unknown210; // Inferred role: data offset in the file; original member name unknown.
  u64 unknown218; // Inferred role: file position; original member name unknown.
  u8 _220[0x228 - 0x220];
  u64 unknown228; // Inferred role: loop start position; original member name unknown.
  u64 unknown230; // Inferred role: loop end position; original member name unknown.
  u8 _238[0x248 - 0x238];
  int unknown248; // Inferred role: frame count; original member name unknown.
  int unknown24c; // Inferred role: loop count; original member name unknown.
  int unknown250; // Inferred role: remain loop count; original member name unknown.
  u8 _254[0x258 - 0x254];
  MemoryBuffer m_memoryBuffer; // Inferred role: read buffer; original member name unknown.
};

static_assert(sizeof(StreamController) == 0x278, "");

static_assert(offsetof(StreamController, unknowne8) == 0xe8, "");
static_assert(offsetof(StreamController, unknown188) == 0x188, "");
static_assert(offsetof(StreamController, unknownee) == 0xee, "");
static_assert(offsetof(StreamController, unknownf0) == 0xf0, "");
static_assert(offsetof(StreamController, unknownf5) == 0xf5, "");
static_assert(offsetof(StreamController, unknownf8) == 0xf8, "");
static_assert(offsetof(StreamController, unknown138) == 0x138, "");
static_assert(offsetof(StreamController, unknown148) == 0x148, "");
static_assert(offsetof(StreamController, unknown1c0) == 0x1c0, "");
static_assert(offsetof(StreamController, unknown1c8) == 0x1c8, "");
static_assert(offsetof(StreamController, unknown1d8) == 0x1d8, "");
static_assert(offsetof(StreamController, unknown210) == 0x210, "");
static_assert(offsetof(StreamController, unknown228) == 0x228, "");
static_assert(offsetof(StreamController, unknown230) == 0x230, "");
static_assert(offsetof(StreamController, unknown24c) == 0x24c, "");
static_assert(offsetof(StreamController, m_fileStream) == 0x100, "");
static_assert(offsetof(StreamController, m_streamBuffer) == 0x158, "");
static_assert(offsetof(StreamController, m_memoryBuffer) == 0x258, "");
static_assert(offsetof(StreamController, unknown1e0) == 0x1e0, "");
static_assert(offsetof(StreamController, unknown208) == 0x208, "");
static_assert(offsetof(StreamController, unknown218) == 0x218, "");
static_assert(offsetof(StreamController, unknown248) == 0x248, "");
static_assert(offsetof(StreamController, unknown250) == 0x250, "");

} // namespace ssd
