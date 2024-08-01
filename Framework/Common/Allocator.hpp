//
// Created by John on 1/08/2024.
//

#ifndef NEXUS_ALLOCATOR_HPP
#define NEXUS_ALLOCATOR_HPP

#include <cstddef>
#include <cstdint>

namespace Nexus {
/// @brief Represents a header for a block of memory.
struct BlockHeader {
    /// @briief Pointer to the next block header in the list.
    BlockHeader* pNext;
};

/// @brief Represents a header for a page of memory blocks.
struct PageHeader {
    /// @brief Pointer to the next page in the list.
    PageHeader* pNext;

    /// @brief Function to get a pointer to the first block header within this
    /// page.
    BlockHeader* Blocks() { return reinterpret_cast<BlockHeader*>(this + 1); }
};

class Allocator {
   public:
    // Debug patterns
    static const uint8_t PATTERN_ALIGN = 0xFC;
    static const uint8_t PATTERN_ALLOC = 0xFD;
    static const uint8_t PATTERN_FREE = 0xFE;

    Allocator(size_t dataSize, size_t pageSize, size_t alignment);
    ~Allocator();

    /// @brief Resets the allocator to a clean state, freeing all allocated
    /// @param dataSize Size of each data block.
    /// @param pageSize Size of a page of blocks.
    /// @param alignment Alignment of each block.
    void Reset(size_t dataSize, size_t pageSize, size_t alignment);

    // Alloc and Free blocks
    void* Allocate();
    void Free(void* p);
    void FreeAll();

   private:
#if defined(_DEBUG)
    /// @brief Fill a free page with debug patterns.
    /// @param pPage Pointer to the page to fill.
    void FillFreePage(PageHeader* pPage);
    /// @brief Fill a free block with debug patterns.
    /// @param pBlock Pointer to the block to fill.
    void FillFreeBlock(BlockHeader* pBlock);
    /// @brief Fill an allocated block with debug patterns.
    /// @param pBlock Pointer to the block to fill.
    void FillAllocatedBlock(BlockHeader* pBlock);
#endif
    /// @brief Gets the next block in the list.
    /// @param pBlock Pointer to the current block.
    BlockHeader* NextBlock(BlockHeader* pBlock);

    /// @brief Page list.
    PageHeader* m_pPageList;

    /// @brief Free block list.
    BlockHeader* m_pFreeList;

    size_t m_szDataSize;
    size_t m_szPageSize;
    size_t m_szAlignmentSize;
    size_t m_szBlockSize;
    uint32_t m_nBlocksPerPage;

    // Statistics
    uint32_t m_nPages;
    uint32_t m_nBlocks;
    uint32_t m_nFreeBlocks;

    // Disable copy and assignment
    Allocator(const Allocator& clone);
    Allocator& operator=(const Allocator& rhs);
};
}  // namespace Nexus

#endif  // NEXUS_ALLOCATOR_HPP
