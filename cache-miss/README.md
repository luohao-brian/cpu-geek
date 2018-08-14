### Cache Miss

下面两段程序，仅从时间复杂度来看完全一样。但是前者耗时0.864s, 而后者耗时0.111s。

这是因为前者循环因为a, b内存不连续，所以每次都要分别从内存中加载a，b到cache, 造成大量cache miss; 相反的，后者a, b每次都会同时被加载到cahce, 所以性能高很多。 

用`perf stat -e cache-misses ./a.out`可以看出，前者cache-miss数量117,056， 而后者仅有26,274。
