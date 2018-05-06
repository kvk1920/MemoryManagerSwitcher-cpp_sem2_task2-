//
// Created by kvk1920 on 06.05.18.
//

#ifndef TASK2_ALLOCATIONSTRATEGY_H
#define TASK2_ALLOCATIONSTRATEGY_H

#include "Allocators.h"
#include "MemoryManagerSwitcher.h"

class RuntimeHeap {
 public:
  static void* Alloc(size_t size) {
    return heap_allocator.Alloc(size);
  }
  static void Free(void* ptr) {
    heap_allocator.Free(ptr);
  }
};

class CurrentMemoryManager {
 public:
  static void* Alloc(size_t size) {
    return CMemoryManagerSwitcher::current_allocator->Alloc(size);
  }
  static void Free(void* ptr) {
    ::operator delete(ptr);
  }
};

template <typename Strategy>
class CAllocatedOn {
 public:
  void* operator new(size_t size) {
    return Strategy::Alloc(size);
  }
  void* operator new[](size_t size) {
    return Strategy::Alloc(size);
  }
  void* operator new(size_t size, std::nothrow_t) noexcept {
    return Strategy::Alloc(size);
  }
  void* operator new[](size_t size, std::nothrow_t) noexcept {
    return Strategy::Alloc(size);
  }
  void operator delete(void* p) {
    Strategy::free(p);
  }
  void operator delete[](void* p) {
    Strategy::free(p);
  }
  void operator delete(void* p, std::nothrow_t) noexcept {
    Strategy::free(p);
  }
  void operator delete[](void* p, std::nothrow_t) noexcept {
    Strategy::free(p);
  }
};

#endif //TASK2_ALLOCATIONSTRATEGY_H
