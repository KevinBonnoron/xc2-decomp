#include <stddef.h>

#include "ssd/ssd_allocator.h"
#include "ssd/ssd_audio_file.h"
#include "ssd/ssd_behavior_impl.h" // IWYU pragma: keep
#include "ssd/ssd_debug.h"
#include "ssd/ssd_file_stream.h"
#include "ssd/ssd_io_stream.h"
#include "types.h"

namespace ssd {
enum Result : long;
class TextRef;

AudioContents::AudioContents() {}

Result MediaContentsHeader::CheckFileType(IoStreamBase *stream, MediaFileType *fileType) {
  SSD_ASSERT(fileType != nullptr, u"Assert : \"%s\" = nullptr, %s:%d", u"fileType", u"D:/ssd/ssd51/ssd/sources/media/audio_file_base.cpp", 0x27);
  unknown002 header;
  u64 position;
  stream->GetPosition(&position);
  stream->Seek(IoStreamBase::SEEK_MODE_BEGIN, 0, nullptr);
  stream->Read(sizeof(header), &header, nullptr);
  switch (unknown004(header.unknown00)) {
  case 0x52494646:
    *fileType = header.unknown08 == 0x45564157 ? MEDIA_FILE_TYPE_UNKNOWN_2 : MEDIA_FILE_TYPE_UNKNOWN_0;
    break;
  case 0x464f524d: {
    u32 type = unknown004(header.unknown08);
    if (type == 0x41494646 || type == 0x41494643) {
      *fileType = MEDIA_FILE_TYPE_UNKNOWN_1;
    }
    break;
  }
  case 0x73616466:
    *fileType = MEDIA_FILE_TYPE_UNKNOWN_3;
    break;
  default:
    stream->unknown001(position);
    *fileType = MEDIA_FILE_TYPE_UNKNOWN_0;
    break;
  }
  stream->unknown001(position);
  return static_cast<Result>(0);
}

AudioFileBase::AudioFileBase()
    : unknown08(nullptr), unknown10(nullptr), unknown18(false), unknown19(false), unknown1a(false), unknown1b(false), unknown1c(0), unknown20(0), unknown24(0), unknown28(0), unknown2c(48000.0f),
      unknown30(0), unknown34(0), unknown35(0), unknown38(0), unknown3c(0), unknown40(0), unknown44(0), unknown48(0), unknown4c(0), unknown4e(0), unknown50(false) {}

AudioFileBase::~AudioFileBase() { DeleteReadBuffer(); }

Result AudioFileBase::OpenFileBase(AudioFileBase **file, const TextRef &name) {
  FileStream *stream = new FileStream();
  if (stream->Open(name, IoStreamBase::OPEN_MODE_READ) < 0) {
    delete stream;
    return static_cast<Result>(-1);
  }
  Result result = OpenFileBase(file, stream);
  (*file)->unknown1a = true;
  return result;
}

Result AudioFileBase::CloseFileBase(AudioFileBase **file) {
  if (file != nullptr && *file != nullptr) {
    AudioFileBase *base = *file;
    base->Close();
    if (base->unknown1a && base->unknown08 != nullptr) {
      base->unknown08->Close();
      base->unknown08 = nullptr;
    }
    if (base->unknown19) {
      delete base;
    } else {
      base->~AudioFileBase();
    }
    *file = nullptr;
  }
  return static_cast<Result>(0);
}

Result AudioFileBase::Open(IoStreamBase *stream) {
  unknown08 = nullptr;
  return static_cast<Result>(-1);
}

Result AudioFileBase::Close() {
  DeleteReadBuffer();
  return static_cast<Result>(-1);
}

Result AudioFileBase::PreLoad() { return static_cast<Result>(-1); }

Result AudioFileBase::PreSave() { return static_cast<Result>(-1); }

Result AudioFileBase::SaveAudioData(const s16 *data, int count) { return static_cast<Result>(-1); }

void AudioFileBase::SetPositionBySample(u64 sample) {}

void AudioFileBase::DeleteReadBuffer() {
  if (unknown10 != nullptr && unknown18) {
    Allocator *allocator = SoundMemory::allocator_;
    Allocator::Block *block = allocator->GetMemoryBlock(unknown10);
    allocator->DeleteBufferImpl(block);
    unknown10 = nullptr;
    unknown18 = false;
  }
}

void AudioFileBase::NewReadBuffer(size_t size) {
  if (unknown10 == nullptr) {
    unknown18 = true;
    Allocator::Block *block = SoundMemory::allocator_->NewBufferImpl(size, 1, 16);
    void *buffer;
    if (block != nullptr) {
      buffer = block->unknown08;
    } else {
      buffer = nullptr;
    }
    unknown10 = buffer;
  }
}

int AudioFileBase::ReadBySamples(s16 *buffer, int count) {
  u64 size = static_cast<u64>(unknown40) * count;
  unknown08->Read(size, buffer, nullptr);
  return 0;
}

int AudioFileBase::WriteBySamples(const s16 *buffer, int count) {
  u64 size = static_cast<u64>(unknown40) * count;
  unknown08->Write(size, buffer, nullptr);
  return 0;
}

AudioMarker *AudioMarkerList::GetMarkerDataByIndex(int index) {
  // Original bug: indexes the list object itself as an array instead of walking its markers.
  return this[index].unknown002();
}

AudioMarker *AudioMarkerList::GetMarkerDataByID(int id) {
  AudioMarker *it = unknown002();
  while (it != unknown003()) {
    if (it->unknown18 == id) {
      return it;
    }
    it = unknown004(it);
  }
  return nullptr;
}

template List<AudioMarker>::Node::~Node();

} // namespace ssd
