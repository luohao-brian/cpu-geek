#cputemp

利用MSR获取当前CPU温度，

### SDM V3 - 14.5.7.2
> MSR IA32_THERM_STATUS
> Digital Readout (bits 22:16, RO) 
> Digital temperature reading in 1 degree Celsius relative to the TCC activation temperature.

### SDM V4
> MSR_TEMPERATURE_TARGET
> Temperature Target (23:16)
> The default thermal throttling or PROCHOT# activation temperature in degree C.

#cpuhot
利用MSR获取CPU的当前温度和警告阈值温度

#showboost
利用MSR获取cpu的基线频率，运行频率以及turbo频率
