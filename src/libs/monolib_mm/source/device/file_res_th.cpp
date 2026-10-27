#include "ml/file_res_th.h"

#include "ml/dev_file_th.h"
#include "ml/file_handle_th.h"
#include "ml/path_util.h"

namespace ml {

bool FileResTh::isExist() const { return unknownc8 != nullptr; }

void FileResTh::setMem(void *buffer, int size, const char *name, bool isBufferOwner) {
  unknownf0 = isBufferOwner;
  unknownc8 = buffer;
  unknownd0 = size;
  SetName(PathUtil::getFilePtrFromPath(name));
}

bool FileResTh::OnFileEvent(EventFileTh *event) {
  if (event->type == EventFileTh::TYPE_COMPLETE) {
    void *buffer = unknownc0->unknown08;
    unknownc0->unknown08 = nullptr;
    unknownc8 = buffer;
    unknownd0 = unknownc0->unknown18;
    unknowne8 = unknownc0->unknown1c8;
    unknowne0 = unknownc0->m_time;
    unknownf8 = static_cast<mm::mtl::IAllocator *>(unknownc0->unknown30);
    unknownf4 = 2;
  } else {
    unknownd0 = -2;
    unknownf4 = 3;
  }
  unknownc0 = nullptr;
  return true;
}

} // namespace ml
