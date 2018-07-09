#CPU False Sharing

### Build
参考源文件中头部的注释

### 验证

```
perf c2c record 
perf report perf --stdio
```

```
    1	=================================================
     2	            Trace Event Information              
     3	=================================================
     4	  Total records                     :     329219
     5	  Locked Load/Store Operations      :      14654
     6	  Load Operations                   :      69679
     7	  Loads - uncacheable               :          0
     8	  Loads - IO                        :          0
     9	  Loads - Miss                      :       3972
    10	  Loads - no mapping                :          0
    11	  Load Fill Buffer Hit              :      11958
    12	  Load L1D hit                      :      17235
    13	  Load L2D hit                      :         21
    14	  Load LLC hit                      :      14219
    15	  Load Local HITM                   :       3402
    16	  Load Remote HITM                  :      12757
    17	  Load Remote HIT                   :       5295
    18	  Load Local DRAM                   :        976
    19	  Load Remote DRAM                  :       3246
    20	  Load MESI State Exclusive         :       4222
    21	  Load MESI State Shared            :          0
    22	  Load LLC Misses                   :      22274
    23	  LLC Misses to Local DRAM          :        4.4%
    24	  LLC Misses to Remote DRAM         :       14.6%
    25	  LLC Misses to Remote cache (HIT)  :       23.8%
    26	  LLC Misses to Remote cache (HITM) :       57.3%
    27	  Store Operations                  :     259539
    28	  Store - uncacheable               :          0
    29	  Store - no mapping                :         11
    30	  Store L1D Hit                     :     256696
    31	  Store L1D Miss                    :       2832
    32	  No Page Map Rejects               :       2376
    33	  Unable to parse data source       :          1
       
    34	=================================================
    35	    Global Shared Cache Line Event Information   
    36	=================================================
    37	  Total Shared Cache Lines          :         55
    38	  Load HITs on shared lines         :      55454
    39	  Fill Buffer Hits on shared lines  :      10635
    40	  L1D hits on shared lines          :      16415
    41	  L2D hits on shared lines          :          0
    42	  LLC hits on shared lines          :       8501
    43	  Locked Access on shared lines     :      14351
    44	  Store HITs on shared lines        :     109953
    45	  Store L1D hits on shared lines    :     109449
    46	  Total Merged records              :     126112
       
    47	=================================================
    48	                 c2c details                     
    49	=================================================
    50	  Events                            : cpu/mem-loads,ldlat=30/P
    51	                                    : cpu/mem-stores/P
    52	  Cachelines sort on                : Remote HITMs
    53	  Cacheline data groupping          : offset,pid,iaddr
       
    54	=================================================
    55	           Shared Data Cache Line Table          
    56	=================================================
    57	#
    58	#                              Total      Rmt  ----- LLC Load Hitm -----  ---- Store Reference ----  --- Load Dram ----      LLC    Total  ----- Core Load Hit -----  -- LLC Load Hit --
    59	# Index           Cacheline  records     Hitm    Total      Lcl      Rmt    Total    L1Hit   L1Miss       Lcl       Rmt  Ld Miss    Loads       FB       L1       L2       Llc       Rmt
    60	# .....  ..................  .......  .......  .......  .......  .......  .......  .......  .......  ........  ........  .......  .......  .......  .......  .......  ........  ........
    61	#
    62	      0            0x602180   149904   77.09%    12103     2269     9834   109504   109036      468       727      2657    13747    40400     5355    16154        0      2875       529
    63	      1            0x602100    12128   22.20%     3951     1119     2832        0        0        0        65       200     3749    12128     5096      108        0      2056       652
    64	      2  0xffff883ffb6a7e80      260    0.09%       15        3       12      161      161        0         1         1       15       99       25       50        0         6         1
    65	      3  0xffffffff81aec000      157    0.07%        9        0        9        1        0        1         0         7       20      156       50       59        0        27         4
    66	      4  0xffffffff81e3f540      179    0.06%        9        1        8      117       97       20         0        10       25       62       11        1        0        24         7
       
    67	=================================================
    68	      Shared Cache Line Distribution Pareto      
    69	=================================================
    70	#
    71	#        ----- HITM -----  -- Store Refs --        Data address                               ---------- cycles ----------       cpu                                     Shared                                   
    72	#   Num      Rmt      Lcl   L1 Hit  L1 Miss              Offset      Pid        Code address  rmt hitm  lcl hitm      load       cnt               Symbol                Object                  Source:Line  Node{cpu list}
    73	# .....  .......  .......  .......  .......  ..................  .......  ..................  ........  ........  ........  ........  ...................  ....................  ...........................  ....
    74	#
    75	  -------------------------------------------------------------
    76	      0     9834     2269   109036      468            0x602180
    77	  -------------------------------------------------------------
    78	          65.51%   55.88%   75.20%    0.00%                 0x0    14604            0x400b4f     27161     26039     26017         9  [.] read_write_func  no_false_sharing.exe  false_sharing_example.c:144   0{0-1,4}  1{24-25,120}  2{48,54}  3{169}
    79	           0.41%    0.35%    0.00%    0.00%                 0x0    14604            0x400b56     18088     12601     26671         9  [.] read_write_func  no_false_sharing.exe  false_sharing_example.c:145   0{0-1,4}  1{24-25,120}  2{48,54}  3{169}
    80	           0.00%    0.00%   24.80%  100.00%                 0x0    14604            0x400b61         0         0         0         9  [.] read_write_func  no_false_sharing.exe  false_sharing_example.c:145   0{0-1,4}  1{24-25,120}  2{48,54}  3{169}
    81	           7.50%    9.92%    0.00%    0.00%                0x20    14604            0x400ba7      2470      1729      1897         2  [.] read_write_func  no_false_sharing.exe  false_sharing_example.c:154   1{122}  2{144}
    82	          17.61%   20.89%    0.00%    0.00%                0x28    14604            0x400bc1      2294      1575      1649         2  [.] read_write_func  no_false_sharing.exe  false_sharing_example.c:158   2{53}  3{170}
    83	           8.97%   12.96%    0.00%    0.00%                0x30    14604            0x400bdb      2325      1897      1828         2  [.] read_write_func  no_false_sharing.exe  false_sharing_example.c:162   0{96}  3{171}
       
    84	  -------------------------------------------------------------
    85	      1     2832     1119        0        0            0x602100
    86	  -------------------------------------------------------------
    87	          29.13%   36.19%    0.00%    0.00%                0x20    14604            0x400bb3      1964      1230      1788         2  [.] read_write_func  no_false_sharing.exe  false_sharing_example.c:155   1{122}  2{144}
    88	          43.68%   34.41%    0.00%    0.00%                0x28    14604            0x400bcd      2274      1566      1793         2  [.] read_write_func  no_false_sharing.exe  false_sharing_example.c:159   2{53}  3{170}
    89	          27.19%   29.40%    0.00%    0.00%                0x30    14604            0x400be7      2045      1247      2011         2  [.] read_write_func  no_false_sharing.exe  false_sharing_example.c:163   0{96}  3{171}
       
    90	  -------------------------------------------------------------
    91	      2       12        3      161        0  0xffff883ffb6a7e80
    92	  -------------------------------------------------------------
    93	          58.33%  100.00%    0.00%    0.00%                 0x0    14604  0xffffffff810cf16d      1380       941      1229         9  [k] task_tick_fair              [kernel.kallsyms]  atomic64_64.h:21   0{0,4,96}  1{25,120,122}  2{53}  3{170-171}
    94	          16.67%    0.00%   98.76%    0.00%                 0x0    14604  0xffffffff810c9379      1794         0       625        13  [k] update_cfs_rq_blocked_load  [kernel.kallsyms]  atomic64_64.h:45   0{1,4,96}  1{25,120,122}  2{48,53-54,144}  3{169-171}
    95	          16.67%    0.00%    0.00%    0.00%                 0x0    14604  0xffffffff810ce098      1382         0       867        12  [k] update_cfs_shares           [kernel.kallsyms]  atomic64_64.h:21   0{1,4,96}  1{25,120,122}  2{53-54,144}  3{169-171}
    96	           8.33%    0.00%    0.00%    0.00%                 0x8    14604  0xffffffff810cf18c      2560         0       679         8  [k] task_tick_fair              [kernel.kallsyms]  atomic.h:26        0{4,96}  1{24-25,120,122}  2{54}  3{170}
    97	           0.00%    0.00%    1.24%    0.00%                 0x8    14604  0xffffffff810cf14f         0         0         0         2  [k] task_tick_fair              [kernel.kallsyms]  atomic.h:50        2{48,53}
       
    98	  -------------------------------------------------------------
    99	      3        9        0        0        1  0xffffffff81aec000
   100	  -------------------------------------------------------------
   101	          77.78%    0.00%    0.00%    0.00%                 0x0    14604  0xffffffff810c331f       430         0       234        12  [k] scheduler_tick            [kernel.kallsyms]  core.c:3055          0{1,4,96}  1{25,120,122}  2{53-54,144}  3{169-171}
   102	          22.22%    0.00%    0.00%    0.00%                 0x0    14604  0xffffffff810d3126       332         0       103        11  [k] trigger_load_balance      [kernel.kallsyms]  fair.c:7222          0{1,4,96}  1{25,120,122}  2{53-54,144}  3{170-171}
   103	           0.00%    0.00%    0.00%  100.00%                 0x0    14604  0xffffffff810eb556         0         0         0         1  [k] do_timer                  [kernel.kallsyms]  timekeeping.c:1875   3{169}
       
   104	  -------------------------------------------------------------
   105	      4        8        1       97       20  0xffffffff81e3f540
   106	  -------------------------------------------------------------
   107	          12.50%    0.00%    0.00%    0.00%                 0x0    14604  0xffffffff810eb0b0       429         0         0         1  [k] update_wall_time            [kernel.kallsyms]  timekeeping.c:1719   3{169}
   108	           0.00%    0.00%    4.12%   10.00%                 0x8    14604  0xffffffff810eb1f3         0         0         0         1  [k] update_wall_time            [kernel.kallsyms]  timekeeping.c:1605   3{169}
   109	           0.00%    0.00%    5.15%    0.00%                 0x8    14604  0xffffffff810eb27d         0         0         0         1  [k] update_wall_time            [kernel.kallsyms]  timekeeping.c:1436   3{169}
   110	           0.00%    0.00%    4.12%    0.00%                0x18    14604  0xffffffff810eaf96         0         0         0         1  [k] update_wall_time            [kernel.kallsyms]  timekeeping.c:1456   3{169}
   111	           0.00%    0.00%    1.03%    0.00%                0x20    14604  0xffffffff810eaffa         0         0         0         1  [k] update_wall_time            [kernel.kallsyms]  timekeeping.c:1489   3{169}
   112	          50.00%  100.00%    0.00%    0.00%                0x38    14604  0xffffffff810ea2e1       442       218       526        10  [k] ktime_get                   [kernel.kallsyms]  seqlock.h:77         0{4,96}  1{120,122}  2{53-54,144}  3{169-171}
   113	          37.50%    0.00%    0.00%    0.00%                0x38    14604  0xffffffff810eb593       593         0       184        10  [k] ktime_get_update_offsets_n  [kernel.kallsyms]  seqlock.h:77         0{4,96}  1{25,120,122}  2{53-54,144}  3{170-171}
   114	           0.00%    0.00%   11.34%    0.00%                0x38    14604  0xffffffff810eb088         0         0       627         3  [k] update_wall_time            [kernel.kallsyms]  seqlock.h:180        0{1}  2{54}  3{169}
   115	           0.00%    0.00%   26.80%   90.00%                0x38    14604  0xffffffff810eb0c6         0         0       120         1  [k] update_wall_time            [kernel.kallsyms]  seqlock.h:187        3{169}
   116	           0.00%    0.00%    1.03%    0.00%                0x3c    14604  0xffffffff8168ab02         0         0         0         1  [k] _raw_spin_unlock_irqrestor  [kernel.kallsyms]  spinlock.h:160       3{169}
   117	           0.00%    0.00%   46.39%    0.00%                0x3c    14604  0xffffffff8168acff         0         0      1942         3  [k] _raw_spin_lock_irqsave      [kernel.kallsyms]  spinlock.h:86        0{1}  1{120}  3{169}
```

### Reference
- https://yq.aliyun.com/articles/465504
