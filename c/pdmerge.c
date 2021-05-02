#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "pdmerge.h"



void mergeUp(PDMERGE_TYPE* start, PDMERGE_TYPE* mid, PDMERGE_TYPE* end, PDMERGE_TYPE* copy, PDMergeCompare cmpfunc) {
    memcpy(copy, start, (mid - start) * sizeof(PDMERGE_TYPE));
    PDMERGE_TYPE* buffer = copy;
    PDMERGE_TYPE* left = start;
    PDMERGE_TYPE* right = mid;

    while (left < right && right < end) {
        if (cmpfunc(buffer, right) <= 0) {
            *left++ = *buffer++;
        } else {
            *left++ = *right++;
        }
    }
    while (left < right) {
        *left++ = *buffer++;
    }
}

void mergeDown(PDMERGE_TYPE* start, PDMERGE_TYPE* mid, PDMERGE_TYPE* end, PDMERGE_TYPE* copy, PDMergeCompare cmpfunc) {
    memcpy(copy, mid, (end - mid) * sizeof(PDMERGE_TYPE));
    PDMERGE_TYPE* buffer = copy + (end - mid - 1);
    PDMERGE_TYPE* left = mid - 1;
    PDMERGE_TYPE* right = end - 1;

    while (right > left && left >= start) {
        if (cmpfunc(buffer, left) >= 0) {
            *right-- = *buffer--;
        } else {
            *right-- = *left--;
        }
    }
    while (right > left) {
        *right-- = *buffer--;
    }
}

void merge(PDMERGE_TYPE* start, PDMERGE_TYPE* mid, PDMERGE_TYPE* end, PDMERGE_TYPE* copy, PDMergeCompare cmpfunc) {
    if (end - mid < mid - start) {
        mergeDown(start, mid, end, copy, cmpfunc);
    } else {
        mergeUp(start, mid, end, copy, cmpfunc);
    }
}

PDMERGE_TYPE* pdmerge_identifyRun(PDMERGE_TYPE* array, PDMERGE_TYPE* index, PDMERGE_TYPE* maxIndex, PDMergeCompare cmpfunc) {
    PDMERGE_TYPE* startIndex = index;
    if (index > maxIndex) {
        return NULL;
    }

    bool cmp = cmpfunc(index, index + 1) <= 0;
    index++;

    while (index < maxIndex) {
        bool checkCmp = cmpfunc(index, index + 1) <= 0;
        if (checkCmp != cmp) {
            break;
        }
        index++;
    }

    if (!cmp) {
        PDMERGE_TYPE *i = startIndex, *j = index;
        while (i < j) {
            PDMERGE_TYPE tmp = *i;
            *i++ = *j;
            *j-- = tmp;
        }
    }
    if (index > maxIndex) {
        return NULL;
    }
    return index + 1;
}

size_t pdmerge_findRuns(PDMERGE_TYPE* array, PDMERGE_TYPE** runs, PDMERGE_TYPE* maxIndex, PDMergeCompare cmpfunc) {
    size_t runCount = 0;
    PDMERGE_TYPE* lastRun = array;
    while (lastRun != NULL) {
        runs[runCount++] = lastRun;
        lastRun = pdmerge_identifyRun(array, lastRun, maxIndex, cmpfunc);
    }
    return runCount;
}

void pdmerge(PDMERGE_TYPE* array, size_t length, PDMergeCompare cmpfunc) {
    PDMERGE_TYPE* arrayEnd = array + length;
    PDMERGE_TYPE** runs = malloc(sizeof(PDMERGE_TYPE*) * ((length + 3) / 2));
    PDMERGE_TYPE* copy = malloc(sizeof(PDMERGE_TYPE) * (length / 2));
    PDMERGE_TYPE** runTop = pdmerge_findRuns(array, runs, array + length - 2, cmpfunc) + runs - 1;

    while (runTop > runs + 1) {
        for (PDMERGE_TYPE** i = runs; i < runTop - 1; i += 2) {
            PDMERGE_TYPE* end = i + 3 > runTop ? arrayEnd : i[2];
            merge(*i, i[1], end, copy, cmpfunc);
        }
        for (PDMERGE_TYPE **i = runs + 1, **j = runs + 2; i < runTop; i++, j += 2, runTop--) {
            *i = *j;
        }
    }

    free(runs);
    free(copy);
}
