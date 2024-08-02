//
// Created by John on 2/08/2024.
//

#include "MemoryManager.hpp"

#include <malloc.h>

using namespace Nexus;

namespace Nexus {
static const uint32_t kBlockSizes[] = {
    // 4-increments
    4,
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
    92,
    96,

    // 32-increments
    128,
    160,
    192,
    224,
    256,
    288,
    320,
    352,
    384,
    416,
    448,
    480,
    512,
    544,
    576,
    608,
    640,

    // 64-increments
    704,
    768,
    832,
    896,
    960,
    1024,
};

static const uint32_t kPageSize = 8192;
static const uint32_t kAlignment = 4;

// Number of elements in the block size lookup table
static const uint32_t kNumBlockSizes =
    sizeof(kBlockSizes) / sizeof(kBlockSizes[0]);

// Largest valid block size
static const uint32_t kMaxBlockSize = kBlockSizes[kNumBlockSizes - 1];
}  // namespace Nexus

int Nexus::MemoryManager::Initialize() {
    // Only initialize once
    static bool s_bInitialized = false;
    if (!s_bInitialized) {
        // Initialize the lookup table
        m_pBlockSizeLookup = new size_t[kMaxBlockSize + 1];
        size_t j = 0;
        for (size_t i = 0; i <= kMaxBlockSize; ++i) {
            if (i > kBlockSizes[j]) ++j;
            m_pBlockSizeLookup[i] = j;
        }

        // Initialize allocators
        m_pAllocators = new Allocator[kNumBlockSizes];
        for (size_t i = 0; i < kNumBlockSizes; i++) {
            m_pAllocators[i].Reset(kBlockSizes[i], kPageSize, kAlignment);
        }

        s_bInitialized = true;
    }

    return 0;
}

void Nexus::MemoryManager::Finalize() {
    delete[] m_pAllocators;
    delete[] m_pBlockSizeLookup;
}

void Nexus::MemoryManager::Tick() {}

Allocator* Nexus::MemoryManager::LookUpAllocator(size_t size) {
    // Check the lookup table
    if (size <= kMaxBlockSize) {
        return m_pAllocators + m_pBlockSizeLookup[size];
    } else {
        return nullptr;
    }
}

void* Nexus::MemoryManager::Allocate(size_t size) {
    Allocator* pAlloc = LookUpAllocator(size);
    if (pAlloc) {
        return pAlloc->Allocate();
    } else {
        return malloc(size);
    }
}

void Nexus::MemoryManager::Free(void* p, size_t size) {
    Allocator* pAlloc = LookUpAllocator(size);
    if (pAlloc) {
        pAlloc->Free(p);
    } else {
        free(p);
    }
}