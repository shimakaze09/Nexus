//
// Created by John on 2/08/2024.
//

#ifndef NEXUS_MEMORYMANAGER_HPP
#define NEXUS_MEMORYMANAGER_HPP

#include "Allocator.hpp"
#include "IRuntimeModule.hpp"

#include <new>

namespace Nexus {
class MemoryManager : implements IRuntimeModule {
   public:
    template <typename T, typename... Arguments>
    T* New(Arguments... parameters) {
        return new (Allocate(sizeof(T))) T(parameters...);
    }

    template <typename T>
    void Delete(T* p) {
        reinterpret_cast<T*>(p)->~T();
        Free(p, sizeof(T));
    }

   public:
    virtual ~MemoryManager() = default;

    int Initialize() override;
    void Finalize() override;
    void Tick() override;

    void* Allocate(size_t size);
    void Free(void* p, size_t size);

   private:
    static size_t* m_pBlockSizeLookup;
    static Allocator* m_pAllocators;

   private:
    static Allocator* LookUpAllocator(size_t size);
};
}  // namespace Nexus

#endif  // NEXUS_MEMORYMANAGER_HPP
