# PDMerge

PDMerge is short for Pattern-Defeating Mergesort. It is a `O(n)` best case time, `O(n log n)` worst-case, and `O(n)` space complexity. It is a runs-adaptive algorithm and it comes in three variants.

This repo contains implementations of PDMerge and its variants in various programming languages. The reference C implementatoin can be found in the "[C](c)" folder.

## Variants

### PDMerge

The base algorithm will collect as many runs as absolutely possible. It uses `n / 2` external records and `(n + 3) / 2` external indices.

### Optimized PDMerge

This will use insertion sort on runs less that 16 elements in length. It uses `n / 2` external records and `(n + 31) / 16` external indices.

### Binary PDMerge

This will use a pair of binary searches to copy as little data to external arrays as possible per merge. It uses `n / 2` external records and `(n + 31) / 16` external indices.

### Threaded PDMerge

This will use up to 24 extra threads to split the load of merging. It uses `n` external records and `(n + 31) / 16` external indices.
