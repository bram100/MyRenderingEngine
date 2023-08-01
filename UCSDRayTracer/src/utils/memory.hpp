//
//  memory.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 4/6/23.
//

/*
 arena-based allocation, which allows the user to quickly allocate objects from a large contiguous region of memory. In this scheme, individual objects are never explicitly freed; the entire region of memory is released when the lifetime of all of the allocated objects ends.

 dvantages to arena-based allocation: 1) extremely fast, usually just requiring a pointer increment. 2) it can improve locality of reference and lead to fewer cache misses, since the allocated objects are contiguous in memory.

 https://www.pbr-book.org/3ed-2018/Utilities/Memory_Management
 
 */

#ifndef memory_hpp
#define memory_hpp

//idk what is up with this?
#ifndef PBRT_L1_CACHE_LINE_SIZE
  #define PBRT_L1_CACHE_LINE_SIZE 64
#endif

#include <stdio.h>

#include <list>
#include <cstddef>

// Memory Declarations
#define ARENA_ALLOC(arena, Type) new ((arena).Alloc(sizeof(Type))) Type
void *allocAligned(size_t size);
template <typename T>
T *allocAligned(size_t count) {
    return (T *)allocAligned(count * sizeof(T));
}

void freeAligned(void *);
class
#ifdef PBRT_HAVE_ALIGNAS
alignas(PBRT_L1_CACHE_LINE_SIZE)
#endif // PBRT_HAVE_ALIGNAS
    memoryArena {
  public:
    // MemoryArena Public Methods
    memoryArena(size_t blockSize = 262144) : blockSize(blockSize) {}
    ~memoryArena() {
        freeAligned(currentBlock);
        for (auto &block : usedBlocks) freeAligned(block.second);
        for (auto &block : availableBlocks) freeAligned(block.second);
    }
    void *alloc(size_t nBytes) {
        // Round up _nBytes_ to minimum machine alignment
#if __GNUC__ == 4 && __GNUC_MINOR__ < 9
        // gcc bug: max_align_t wasn't in std:: until 4.9.0
        const int align = alignof(::max_align_t);
#elif !defined(PBRT_HAVE_ALIGNOF)
        const int align = 16;
#else
        const int align = alignof(std::max_align_t);
#endif
#ifdef PBRT_HAVE_CONSTEXPR
        static_assert(IsPowerOf2(align), "Minimum alignment not a power of two");
#endif
        nBytes = (nBytes + align - 1) & ~(align - 1);
        if (currentBlockPos + nBytes > currentAllocSize) {
            // Add current block to _usedBlocks_ list
            if (currentBlock) {
                usedBlocks.push_back(
                    std::make_pair(currentAllocSize, currentBlock));
                currentBlock = nullptr;
                currentAllocSize = 0;
            }

            // Get new block of memory for _MemoryArena_

            // Try to get memory block from _availableBlocks_
            for (auto iter = availableBlocks.begin();
                 iter != availableBlocks.end(); ++iter) {
                if (iter->first >= nBytes) {
                    currentAllocSize = iter->first;
                    currentBlock = iter->second;
                    availableBlocks.erase(iter);
                    break;
                }
            }
            if (!currentBlock) {
                currentAllocSize = std::max(nBytes, blockSize);
                currentBlock = allocAligned<uint8_t>(currentAllocSize);
            }
            currentBlockPos = 0;
        }
        void *ret = currentBlock + currentBlockPos;
        currentBlockPos += nBytes;
        return ret;
    }
    template <typename T>
    T *alloc(size_t n = 1, bool runConstructor = true) {
        T *ret = (T *)alloc(n * sizeof(T));
        if (runConstructor)
            for (size_t i = 0; i < n; ++i) new (&ret[i]) T();
        return ret;
    }
    void reset() {
        currentBlockPos = 0;
        availableBlocks.splice(availableBlocks.begin(), usedBlocks);
    }
    size_t totalAllocated() const {
        size_t total = currentAllocSize;
        for (const auto &alloc : usedBlocks) total += alloc.first;
        for (const auto &alloc : availableBlocks) total += alloc.first;
        return total;
    }

  private:
    memoryArena(const memoryArena &) = delete;
    memoryArena &operator=(const memoryArena &) = delete;
    // MemoryArena Private Data
    const size_t blockSize;
    size_t currentBlockPos = 0, currentAllocSize = 0;
    uint8_t *currentBlock = nullptr;
    std::list<std::pair<size_t, uint8_t *>> usedBlocks, availableBlocks;
};

template <typename T, int logBlockSize>
class BlockedArray {
  public:
    // BlockedArray Public Methods
    BlockedArray(int uRes, int vRes, const T *d = nullptr)
        : uRes(uRes), vRes(vRes), uBlocks(RoundUp(uRes) >> logBlockSize) {
        int nAlloc = RoundUp(uRes) * RoundUp(vRes);
        data = allocAligned<T>(nAlloc);
        for (int i = 0; i < nAlloc; ++i) new (&data[i]) T();
        if (d)
            for (int v = 0; v < vRes; ++v)
                for (int u = 0; u < uRes; ++u) (*this)(u, v) = d[v * uRes + u];
    }
    const int BlockSize() const { return 1 << logBlockSize; }
    int RoundUp(int x) const {
        return (x + BlockSize() - 1) & ~(BlockSize() - 1);
    }
    int uSize() const { return uRes; }
    int vSize() const { return vRes; }
    ~BlockedArray() {
        for (int i = 0; i < uRes * vRes; ++i) data[i].~T();
        FreeAligned(data);
    }
    int Block(int a) const { return a >> logBlockSize; }
    int Offset(int a) const { return (a & (BlockSize() - 1)); }
    T &operator()(int u, int v) {
        int bu = Block(u), bv = Block(v);
        int ou = Offset(u), ov = Offset(v);
        int offset = BlockSize() * BlockSize() * (uBlocks * bv + bu);
        offset += BlockSize() * ov + ou;
        return data[offset];
    }
    const T &operator()(int u, int v) const {
        int bu = Block(u), bv = Block(v);
        int ou = Offset(u), ov = Offset(v);
        int offset = BlockSize() * BlockSize() * (uBlocks * bv + bu);
        offset += BlockSize() * ov + ou;
        return data[offset];
    }
    void GetLinearArray(T *a) const {
        for (int v = 0; v < vRes; ++v)
            for (int u = 0; u < uRes; ++u) *a++ = (*this)(u, v);
    }

  private:
    // BlockedArray Private Data
    T *data;
    const int uRes, vRes, uBlocks;
};

#endif /* memory_hpp */
