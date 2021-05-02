# PDMerge C Benchmarks

These benchmarks were run on my Windows 10 PC using the included [bench.c](bench.c) compiled with `-O3`.

## PDMerge

```shell
$ ./bench
Running sort pdmerge 10 times on 16777216 numbers...
Ran sort pdmerge 10 times (total 12.220000 seconds):
  - Average time: 1.222000 seconds
  - Minimum time: 1.211000 seconds
```

## Optmized PDMerge

```shell
$ ./bench    
Running sort pdmerge2 10 times on 16777216 numbers...
Ran sort pdmerge2 10 times (total 11.029000 seconds):
  - Average time: 1.102900 seconds
  - Minimum time: 1.092000 seconds
```
