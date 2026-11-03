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

