//
// Created by John on 1/08/2024.
//

#include "Allocator.hpp"

#include <cassert>
#include <cstring>

#ifndef ALIGN
#define ALIGN(x, a) (((x) + ((a) - 1)) & ~((a) - 1))
#endif

using namespace Nexus;

Nexus::Allocator::Allocator(size_t dataSize, size_t pageSize, size_t alignment)
    : m_pPageList(nullptr), m_pFreeList(nullptr) {
    Reset(dataSize, pageSize, alignment);
}

Nexus::Allocator::~Allocator() { FreeAll(); }

void Nexus::Allocator::Reset(size_t dataSize, size_t pageSize,
                             size_t alignment) {
    FreeAll();

    m_szDataSize = dataSize;
    m_szPageSize = pageSize;

    size_t minimalSize = (sizeof(BlockHeader) > m_szDataSize)
                             ? sizeof(BlockHeader)
                             : m_szDataSize;

    // Make sure the alignment value is a power of 2 and greater than 0.
#if defined(_DEBUG)
    assert(alignment > 0 && ((alignment & (alignment - 1))) == 0);
#endif

    m_szBlockSize = ALIGN(minimalSize, alignment);

    m_szAlignmentSize = m_szBlockSize - minimalSize;

    m_nBlocksPerPage = (m_szPageSize - sizeof(PageHeader)) / m_szBlockSize;
}

void* Nexus::Allocator::Allocate() {
    if (!m_pFreeList) {
        // Allocate a new page
        PageHeader* pNewPage =
            reinterpret_cast<PageHeader*>(new uint8_t[m_szPageSize]);

        m_nPages++;
        m_nBlocks += m_nBlocksPerPage;
        m_nFreeBlocks += m_nBlocksPerPage;

#if defined(_DEBUG)
        FillFreePage(pNewPage);
#endif

        if (m_pPageList) {
            pNewPage->pNext = m_pPageList;
        }

        m_pPageList = pNewPage;

        BlockHeader* pBlock = pNewPage->Blocks();

        // Link each block in the page
        for (uint32_t i = 0; i < m_nBlocksPerPage; i++) {
            pBlock->pNext = NextBlock(pBlock);
            pBlock = NextBlock(pBlock);
        }

        pBlock->pNext = nullptr;

        m_pFreeList = pNewPage->Blocks();
    }

    BlockHeader* pFreeList = m_pFreeList;
    m_pFreeList = m_pFreeList->pNext;
    --m_nFreeBlocks;

#if defined(_DEBUG)
    FillAllocatedBlock(pFreeList);
#endif

    return reinterpret_cast<void*>(pFreeList);
}

void Nexus::Allocator::Free(void* p) {
    BlockHeader* pBlock = reinterpret_cast<BlockHeader*>(p);

#if defined(_DEBUG)
    FillFreeBlock(pBlock);
#endif

    pBlock->pNext = m_pFreeList;
    m_pFreeList = pBlock;
    ++m_nFreeBlocks;
}

void Nexus::Allocator::FreeAll() {
    PageHeader* pPage = m_pPageList;
    while (pPage) {
        PageHeader* p = pPage;
        pPage = pPage->pNext;

        delete[] reinterpret_cast<uint8_t*>(p);
    }

    m_pPageList = nullptr;
    m_pFreeList = nullptr;

    m_nPages = 0;
    m_nBlocks = 0;
    m_nFreeBlocks = 0;
}

#if defined(_DEBUG)
void Nexus::Allocator::FillFreePage(PageHeader* pPage) {
    // Page header
    pPage->pNext = nullptr;

    // Blocks
    BlockHeader* pBlock = pPage->Blocks();
    for (uint32_t i = 0; i < m_nBlocksPerPage; i++) {
        FillFreeBlock(pBlock);
        pBlock = NextBlock(pBlock);
    }
}

void Nexus::Allocator::FillFreeBlock(BlockHeader* pBlock) {
    // Block header + data
    std::memset(pBlock, PATTERN_FREE, m_szBlockSize - m_szAlignmentSize);

    // Alignment
    std::memset(
        reinterpret_cast<uint8_t*>(pBlock) + m_szBlockSize - m_szAlignmentSize,
        PATTERN_ALIGN, m_szAlignmentSize);
}

void Nexus::Allocator::FillAllocatedBlock(BlockHeader* pBlock) {
    // Block header + data
    std::memset(pBlock, PATTERN_ALLOC, m_szBlockSize - m_szAlignmentSize);

    // Alignment
    std::memset(
        reinterpret_cast<uint8_t*>(pBlock) + m_szBlockSize - m_szAlignmentSize,
        PATTERN_ALIGN, m_szAlignmentSize);
}
#endif

Nexus::BlockHeader* Nexus::Allocator::NextBlock(BlockHeader* pBlock) {
    return reinterpret_cast<BlockHeader*>(reinterpret_cast<uint8_t*>(pBlock) +
                                          m_szBlockSize);
}
