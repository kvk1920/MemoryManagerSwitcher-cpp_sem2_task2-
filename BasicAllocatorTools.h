//
// Created by kvk1920 on 06.05.18.
//

#ifndef TASK2_BASICALLOCATORTOOLS_H
#define TASK2_BASICALLOCATORTOOLS_H

#include <cstdlib>

namespace AllocatorTools {

typedef unsigned char Byte;

class IMemoryManager;

struct DataInfo {
  size_t size_of_data;
  IMemoryManager* allocated_with;

  DataInfo(size_t size, IMemoryManager* allocator) :
      size_of_data(size),
      allocated_with(allocator) {}
};

const size_t kSizeOfDataInfo = sizeof(DataInfo);

class IMemoryManager {
 private:
  virtual Byte* getMemory(size_t size) = 0;

  virtual void freeMemory(Byte* ptr, size_t size) = 0;

 public:
  void* Alloc(size_t size) {
    Byte* ptr(getMemory(size + kSizeOfDataInfo));
    new(ptr) DataInfo(size, this);
    return ptr + kSizeOfDataInfo;
  }

  void Free(void* ptr) {
    Byte* p = reinterpret_cast<Byte*>(ptr);
    p -= kSizeOfDataInfo;
    freeMemory(p, reinterpret_cast<DataInfo*>(p)->size_of_data);
  }
};

}

using AllocatorTools::IMemoryManager;

#endif //TASK2_BASICALLOCATORTOOLS_H
