### cpu-ipc-extreme介绍

现代cpu有4条流水管线(pipeline slots), 使用nop循环实现流水管线利用率接近理论最大化，IPC(Instruction Per Cycle)最大化。

### CPU_CLK_UNHALTED.THREAD_P事件

event=0x3c, umask=0x0，表示非停机状态的机器周期数。很显然，对于一个程序，这个事件的数目越少越好，表明其运行状态(非停机状态)消耗的机器周期少。 THREAD_P表示 非停机状态下线程的机器周期。线程在运行HLT指令的时候进入halt state(停机状态)。由于CPU核的频率会不断变化，这个事件数目和时间的比例是变化的

### INST_RETIRED.ANY事件
event=0xc0,umask=0x0, 表示消耗的指令数，计数执行过程中消耗的指令数。

### IPC
INST_RETIRED.ANY / CPU_CLK_UNHALTED.THREAD, Instructions Per Cycle (per logical thread)

### RESOURCE_STALLS.ANY事件
event=0xa2, umask=0x1, Counts resource-related stall cycles. Reasons for stalls can be as follows:a. *any* u-arch structure got full (LB, SB, RS, ROB, BOB, LM, Physical Register Reclaim Table (PRRT), or Physical History Table (PHT) slots).b. *any* u-arch structure got empty (like INT/SIMD FreeLists).c. FPU control word (FPCW), MXCSR.and others. This counts cycles that the pipeline back-end blocked uop delivery from the front-end.

### 使用方法

编译
```
gcc -o membound membound.c
```

perf version<4.14
```
perf stat -e cpu/event=0xa2,umask=0x1,name=resource_stalls_any,period=2000003/  -e cpu/event=0x3c,umask=0x0,name=cpu_clk_unhalted_thread_p,period=2000003/ -e cpu/event=0xc0,umask=0x0,name=inst_retired.any,period=2000003/ ./membound
```

perf version>=4.14
```
perf stat -e resource_stalls_any -e cpu_clk_unhalted.thread_p -e inst_retired.any ./membound
```

### 参考
- [](https://software.intel.com/en-us/vtune-amplifier-help-tuning-applications-using-a-top-down-microarchitecture-analysis-method)

- [](https://yq.aliyun.com/articles/465499)

 * [Linux Perf PMU Events List](https://elixir.bootlin.com/linux/latest/source/tools/perf/pmu-events/arch/x86)
