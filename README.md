#关于CPU的一些研究

### cpufp

这是利用SIMD指令测试cpu峰值浮点的工具。

### false-sharing
CPU cache line伪共享会导致严重的性能下降, 这个测试程序对比了伪共享带来的下降，可以看出在类似轮询的场景，伪共享会导致数倍的延时增加。

### false-sharing2
linux 4.14， CPU i7-4790上测试代码和测试结果，极端情况下，性能下降到八分之一左右。c2c report中看到Load Local HITM暴涨。

### cpu-msr-tools/cputemp
使用MSR获取当前CPU温度

### cpu-msr-tools/cpuhot
利用MSR获取CPU的当前温度和警告阈值温度

### cpu-msr-tools/showboost
利用MSR获取cpu的基线频率，运行频率以及turbo频率

### pmu-counters
利用CPUID获取PMU的counters
