//
//  transform.cpp
//  UCSD_CSE168_HW1
//
//  Created by Brendan Mulcahey on 1/10/23.
//

#include "transform.hpp"
 
int nTransformCacheHits;

transformation *transformCache::lookup(const transformation &t) {

        int offset = hash(t) & (hashTable.size() - 1);
        int step = 1;
        while (true) {
            // Keep looking until we find the Transform or determine that
            // it's not present.
            if (!hashTable[offset] || *hashTable[offset] == t)
                break;
            // Advance using quadratic probing.
            offset = (offset + step * step) & (hashTable.size() - 1);
            ++step;
        }
        //ReportValue(transformCacheProbes, step);
        transformation *tCached = hashTable[offset];
        if (tCached)
            ++nTransformCacheHits;
        else {
            tCached = arena.alloc<transformation>();
            *tCached = t; //this may be a bug location
            insert(tCached);
        }
        return tCached;
    }

void transformCache::clear() {
    //transformCacheBytes += arena.TotalAllocated() + hashTable.size() * sizeof(Transform *);
    hashTable.clear();
    hashTable.resize(512);
    hashTableOccupancy = 0;
    arena.reset();
}


void transformCache::insert(transformation *tNew) {
    if (++hashTableOccupancy == hashTable.size() / 2)
        grow();

    int baseOffset = hash(*tNew) & (hashTable.size() - 1);
    for (int nProbes = 0;; ++nProbes) {
        // Quadratic probing.
        int offset = (baseOffset + nProbes/2 + nProbes*nProbes/2) & (hashTable.size() - 1);
        if (hashTable[offset] == nullptr) {
            hashTable[offset] = tNew;
            return;
        }
    }
}


void transformCache::grow() {
    std::vector<transformation *> newTable(2 * hashTable.size());
    //LOG(INFO) << "Growing transform cache hash table to " << newTable.size();

    // Insert current elements into newTable.
    for (transformation *tEntry : hashTable) {
        if (!tEntry) continue;

        int baseOffset = hash(*tEntry) & (hashTable.size() - 1);
        for (int nProbes = 0;; ++nProbes) {
            // Quadratic probing.
            int offset = (baseOffset + nProbes/2 + nProbes*nProbes/2) & (hashTable.size() - 1);
            if (newTable[offset] == nullptr) {
                newTable[offset] = tEntry;
                break;
            }
        }
    }

    std::swap(hashTable, newTable);
}
