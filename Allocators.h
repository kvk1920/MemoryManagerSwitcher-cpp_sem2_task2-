//
// Created by kvk1920 on 06.05.18.
//

#ifndef TASK2_ALLOCATORS_H
#define TASK2_ALLOCATORS_H

#include "StackAllocator.h"
#include "BasicAllocatorTools.h"

namespace Allocators {

using namespace AllocatorTools;

class HeapAllocator : public IMemoryManager {
 private:
  Byte* getMemory(size_t size) final {
    return reinterpret_cast<Byte*>(malloc(size));
  }

  void freeMemory(Byte* ptr, size_t size) final {
    free(ptr);
  }
} heap_allocator;

template<template<typename> typename AllocatorType>
class SpecialAllocator : public IMemoryManager {
 private:

  AllocatorType<Byte> allocator_;

  Byte* getMemory(size_t size) final {
    return allocator_.allocate(size);
  }

  void freeMemory(Byte* ptr, size_t size) final {
    allocator_.deallocate(ptr, size);
  }

 public:

  template <typename ...Args>
  SpecialAllocator(Args&& ...args) :
      allocator_(std::forward<Args>(args)...)
  {}
};


SpecialAllocator<StackAllocatorClass::StackAllocator> stack_allocator;

}

using Allocators::stack_allocator;
using Allocators::heap_allocator;

#endif //TASK2_ALLOCATORS_H
