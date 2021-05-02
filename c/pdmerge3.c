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

PDMERGE_TYPE* pdmerge3_monoboundLeft(PDMERGE_TYPE* start, PDMERGE_TYPE* end, PDMERGE_TYPE* value, PDMergeCompare cmpfunc) {
    size_t top, mid;
    top = end - start;

    while (top > 1) {
        mid = top / 2;

        if (cmpfunc(value, end - mid) <= 0) {
            end -= mid;
        }
        top -= mid;
    }

    if (cmpfunc(value, end - 1) <= 0) {
        return end - 1;
    }
    return end;
}

PDMERGE_TYPE* pdmerge3_monoboundRight(PDMERGE_TYPE* start, PDMERGE_TYPE* end, PDMERGE_TYPE* value, PDMergeCompare cmpfunc) {
    size_t top, mid;
    top = end - start;

    while (top > 1) {
        mid = top / 2;

        if (cmpfunc(start + mid, value) <= 0) {
            start += mid;
        }
        top -= mid;
    }

    if (cmpfunc(start, value) <= 0) {
        return start + 1;
    }
    return start;
}

void pdmerge3_merge(PDMERGE_TYPE* start, PDMERGE_TYPE* mid, PDMERGE_TYPE* end, PDMERGE_TYPE* copy, PDMergeCompare cmpfunc) {
    start = pdmerge3_monoboundRight(start, mid, mid, cmpfunc);
    if (start == mid) return;
    end = pdmerge3_monoboundLeft(mid, end, mid - 1, cmpfunc);
    pdmerge_merge(start, mid, end, copy, cmpfunc);
}

void pdmerge3(PDMERGE_TYPE* array, size_t length, PDMergeCompare cmpfunc) {
    PDMERGE_TYPE* arrayEnd = array + length;
    PDMERGE_TYPE** runs = malloc(sizeof(PDMERGE_TYPE*) * ((length + 31) / 16));
    PDMERGE_TYPE* copy = malloc(sizeof(PDMERGE_TYPE) * (length / 2));
    PDMERGE_TYPE** runTop = pdmerge2_findRuns(array, runs, array + length - 2, cmpfunc) + runs;

    while (runTop > runs + 1) {
        for (PDMERGE_TYPE** i = runs; i < runTop - 1; i += 2) {
            PDMERGE_TYPE* end = i + 3 > runTop ? arrayEnd : i[2];
            pdmerge3_merge(*i, i[1], end, copy, cmpfunc);
        }
        for (PDMERGE_TYPE **i = runs + 1, **j = runs + 2; i < runTop; i++, j += 2, runTop--) {
            *i = *j;
        }
    }

    free(runs);
    free(copy);
}
