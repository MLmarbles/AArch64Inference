### 1000 runs at 6x8x16
FLOPs per matmul: 1536
KleidiAI Time: 60 average 
KleidiAI Performance: 25.5485 GFLOPS
Naive Time: 564 average 
Naive Performance: 2.72242 GFLOPS

100,000 runs at 8x8x8
FLOPs per matmul: 1024
KleidiAI Packing Time: 26 average 
KleidiAI Time: 74 average 
KleidiAI Performance: 13.6984 GFLOPS
Naive Time: 380 average 
Naive Performance: 2.69135 GFLOPS

100,000 runs at 16x16x16
FLOPs per matmul: 8192
KleidiAI Packing Time: 31 average 
KleidiAI Time: 232 average 
KleidiAI Performance: 35.2509 GFLOPS
Naive Time: 2687 average 
Naive Performance: 3.04854 GFLOPS

100,000 runs at 32x32x32
FLOPs per matmul: 65536
KleidiAI Packing Time: 99 average 
KleidiAI Time: 1594 average 
KleidiAI Performance: 41.0927 GFLOPS
Naive Time: 23576 average 
Naive Performance: 2.77973 GFLOPS

100,000 runs at 64x64x64
FLOPs per matmul: 524288
KleidiAI Packing Time: 370 average
KleidiAI Time: 11810 average 
KleidiAI Performance: 44.3924 GFLOPS
Naive Time: 181903 average 
Naive Performance: 2.88223 GFLOPS

100,000 runs at 128x128x128
FLOPs per matmul: 4194304
KleidiAI Packing Time: 1643 average 
KleidiAI Time: 95133 average 
KleidiAI Performance: 44.0887 GFLOPS
Naive Time: 1432450 average 
Naive Performance: 2.92806 GFLOPS

comment: it seems like when the matrices get larger, the kernel gets enough work
to make good use of NEON and its 6x16 blocking technique.

### boundary cases
6x16x128
FLOPs per matmul: 24576
KleidiAI Time: 705 average 
KleidiAI Performance: 34.8258 GFLOPS

7x16x128
FLOPs per matmul: 28672
KleidiAI Time: 813 average 
KleidiAI Performance: 35.2528 GFLOPS

6x17x128
FLOPs per matmul: 26112
KleidiAI Time: 752 average 
KleidiAI Performance: 34.6955 GFLOPS

7x17x128
FLOPs per matmul: 30464
KleidiAI Time: 874 average 
KleidiAI Performance: 34.8349 GFLOPS

12x32x128
FLOPs per matmul: 98304
KleidiAI Time: 2414 average 
KleidiAI Performance: 40.7141 GFLOPS

comment: it seems that crossing into edges where 6x16 tiling doesnt perfectly fit
didnt actually tank performance that much
after observing the assembly files it seems that there are special cases for 
rows sizes less than 6
and for columns it seems that it still computes uses a 16 sized vector with padded values
but only writes to the last existing few values