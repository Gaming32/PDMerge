/*
MIT License

Copyright (c) 2021 Josiah (Gaming32) Glosson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
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


#ifndef PDMERGE_TYPE
    #define PDMERGE_TYPE int
#endif


// Comparison function
typedef int (*PDMergeCompare)(const PDMERGE_TYPE* a, const PDMERGE_TYPE* b);


// Sorting functions
void pdmerge(PDMERGE_TYPE* array, size_t nmemb, PDMergeCompare CMP);
void pdmerge2(PDMERGE_TYPE* array, size_t nmemb, PDMergeCompare CMP);
void pdmerge3(PDMERGE_TYPE* array, size_t nmemb, PDMergeCompare CMP);
void pdmerge4(PDMERGE_TYPE* array, size_t nmemb, PDMergeCompare CMP);


// Internal utilities

