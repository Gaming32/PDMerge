/*
MIT License

Copyright (c) 2021 Josiah (Gaming32) Glosson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, pdmerge_merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "pdmerge.h"

#define MIN_RUN_SIZE 16

void pdmerge2_insertSort(PDMERGE_TYPE* start, PDMERGE_TYPE* mid, PDMERGE_TYPE* end, PDMergeCompare cmpfunc) {
    PDMERGE_TYPE *pos, *pos1, cur;
    for (PDMERGE_TYPE* i = mid; i < end; i++) {
        cur = *i;
        pos = i - 1;
        pos1 = i;
        while (pos >= start && cmpfunc(pos, &cur) > 0)
            *pos1-- = *pos--;
        *pos1 = cur;
    }
}

PDMERGE_TYPE* pdmerge2_identifyRun(PDMERGE_TYPE* index, PDMERGE_TYPE* maxIndex, PDMergeCompare cmpfunc) {
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

    if (index - startIndex + 1 < MIN_RUN_SIZE) {
        PDMERGE_TYPE* end = startIndex + MIN_RUN_SIZE;
        if (end > maxIndex + 1) {
            end = maxIndex + 1;
        }
        pdmerge2_insertSort(startIndex, index + 1, end, cmpfunc);
        return end > maxIndex ? NULL : end;
    }

    if (index > maxIndex) {
        return NULL;
    }
    return index + 1;
}

size_t pdmerge2_findRuns(PDMERGE_TYPE* lastRun, PDMERGE_TYPE** runs, PDMERGE_TYPE* maxIndex, PDMergeCompare cmpfunc) {
    size_t runCount = 0;
    while (lastRun != NULL) {
        runs[runCount++] = lastRun;
        lastRun = pdmerge2_identifyRun(lastRun, maxIndex, cmpfunc);
    }
    return runCount;
}

void pdmerge2(PDMERGE_TYPE* array, size_t length, PDMergeCompare cmpfunc) {
    PDMERGE_TYPE* arrayEnd = array + length;
    PDMERGE_TYPE** runs = malloc(sizeof(PDMERGE_TYPE*) * ((length + 31) / 16));
    PDMERGE_TYPE* copy = malloc(sizeof(PDMERGE_TYPE) * (length / 2));
    PDMERGE_TYPE** runTop = pdmerge2_findRuns(array, runs, array + length - 2, cmpfunc) + runs - 1;

    while (runTop > runs + 1) {
        for (PDMERGE_TYPE** i = runs; i < runTop - 1; i += 2) {
            PDMERGE_TYPE* end = i + 3 > runTop ? arrayEnd : i[2];
            pdmerge_merge(*i, i[1], end, copy, cmpfunc);
        }
        for (PDMERGE_TYPE **i = runs + 1, **j = runs + 2; i < runTop; i++, j += 2, runTop--) {
            *i = *j;
        }
    }

    free(runs);
    free(copy);
}
