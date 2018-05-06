//
// Created by kvk1920 on 06.05.18.
//

#ifndef TASK2_MEMORYMANAGERSWITCHER_H
#define TASK2_MEMORYMANAGERSWITCHER_H

#include "Allocators.h"
#include "BasicAllocatorTools.h"

namespace CMemoryManagerSwitcher {

static IMemoryManager* current_allocator = &heap_allocator;

void SwitchAllocator(IMemoryManager& allocator) {
  current_allocator = &allocator;
}

}

using __DataInfo = AllocatorTools::DataInfo;

void* operator new(size_t size) {
  return CMemoryManagerSwitcher::current_allocator->Alloc(size);
}

void operator delete(void* ptr) {
  __DataInfo* info(reinterpret_cast<__DataInfo*>(ptr));
  --info;
  info->allocated_with->Free(ptr);
}

void* operator new[](size_t size) {
  return CMemoryManagerSwitcher::current_allocator->Alloc(size);
}

void operator delete[](void* ptr) {
  __DataInfo* info(reinterpret_cast<__DataInfo*>(ptr));
  --info;
  info->allocated_with->Free(ptr);
}

void* operator new(size_t size, std::nothrow_t) noexcept {
  return CMemoryManagerSwitcher::current_allocator->Alloc(size);
}

void operator delete(void* ptr, std::nothrow_t) noexcept {
  __DataInfo* info(reinterpret_cast<__DataInfo*>(ptr));
  --info;
  info->allocated_with->Free(info);
}

void* operator new[](size_t size, std::nothrow_t) noexcept {
  return CMemoryManagerSwitcher::current_allocator->Alloc(size);
}

void operator delete[](void* ptr, std::nothrow_t) noexcept {
  __DataInfo* info(reinterpret_cast<__DataInfo*>(ptr));
  --info;
  info->allocated_with->Free(info);
}

#endif //TASK2_MEMORYMANAGERSWITCHER_H
