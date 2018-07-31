### cpu-ipc-extreme介绍

现代cpu有4条流水管线(pipeline slots), 使用nop循环实现流水管线利用率接近理论最大化，IPC(Instruction Per Cycle)最大化。

### 使用方法

```
gcc main.c
perf stat ./a.out
```

```

 Performance counter stats for './a.out':

        948.727399      task-clock (msec)         #    1.000 CPUs utilized
                 1      context-switches          #    0.001 K/sec
                 1      cpu-migrations            #    0.001 K/sec
                44      page-faults               #    0.046 K/sec
     3,229,991,344      cycles                    #    3.405 GHz
    15,037,023,084      instructions              #    4.66  insn per cycle
     2,148,320,131      branches                  # 2264.423 M/sec
            27,301      branch-misses             #    0.00% of all branches

       0.949050567 seconds time elapsed

```

### 参考
- [](https://software.intel.com/en-us/vtune-amplifier-help-tuning-applications-using-a-top-down-microarchitecture-analysis-method)

- [](https://yq.aliyun.com/articles/465499)
