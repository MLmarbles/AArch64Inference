#include <cstddef>
#include <iostream>
#include <vector>
#include <cstdint>
#include <limits>
#include <chrono>

#include "kai/ukernels/matmul/pack/kai_rhs_pack_kxn_x32p16x1b_x32_x32_neon.h"
#include "kai/ukernels/matmul/matmul_clamp_f32_f32_f32p/kai_matmul_clamp_f32_f32_f32p16x1b_6x16_neon_mla.h"

constexpr std::size_t M = 128;
constexpr std::size_t K = 128;
constexpr std::size_t N = 128;

void matmul(
    const std::vector<float>& lhs,
    const std::vector<float>& rhs,
    std::vector<float>& dst)
{
    for (std::size_t m = 0; m < M; ++m) {
        for (std::size_t n = 0; n < N; ++n) {
            float sum = 0;

            for (std::size_t k = 0; k < K; ++k) {
                sum += lhs[m * K + k] * rhs[k * N + n];
            }
            dst[m * N + n] = sum;
        }
    }

}

int main()
{
    const float clamp_min =
        -std::numeric_limits<float>::infinity();

    const float clamp_max =
        std::numeric_limits<float>::infinity();

    std::vector<float> lhs(M * K);
    std::vector<float> rhs(K * N);

    std::vector<float> reference(M * N, 0.0f);
    std::vector<float> kleidiai_output(M * N, 0.0f);

    std::vector<float> bias(N, 0.0f);

    const std::size_t nr = kai_get_n_step_rhs_pack_kxn_x32p16x1b_x32_x32_neon();
    const std::size_t kr = 1;
    const std::size_t sr = 1;

    const std::size_t packed_rhs_size = kai_get_rhs_packed_size_rhs_pack_kxn_x32p16x1b_x32_x32_neon(N, K);
    std::vector<std::uint8_t> packed_rhs(packed_rhs_size);

    const std::size_t rhs_stride = N * sizeof(float);
    const std::size_t lhs_stride = K * sizeof(float);
    const std::size_t dst_stride_row = N * sizeof(float);
    const std::size_t dst_stride_col = sizeof(float);

    for (std::size_t i = 0; i < lhs.size(); ++i) {
        lhs[i] = static_cast<float>(static_cast<int>(i % 7) - 3);
    }

    for (std::size_t i = 0; i < rhs.size(); ++i) {
        rhs[i] = static_cast<float>(static_cast<int>(i % 5) - 2);
    }


    kai_run_rhs_pack_kxn_x32p16x1b_x32_x32_neon(
        1,
        N,
        K,
        nr,
        kr,
        sr,
        rhs_stride,
        rhs.data(),
        bias.data(),
        nullptr,
        packed_rhs.data(),
        0,
        nullptr
    );

    std::cout << "RHS size: " << rhs.size() * sizeof(float) << " bytes\n";

    std::cout << "Packed RHS size: " << packed_rhs_size << " bytes\n";

    long long flops = 2 * M * N * K;
    std::cout << "FLOPs per matmul: " << flops << '\n';

    int runs = 100000;

    long long total = 0;
    auto start = std::chrono::steady_clock::now();
    for(std::size_t i = 0; i < runs; ++i) {

        kai_run_matmul_clamp_f32_f32_f32p16x1b_6x16_neon_mla(
            M,
            N,
            K,
            lhs.data(),
            lhs_stride,
            packed_rhs.data(),
            kleidiai_output.data(),
            dst_stride_row,
            dst_stride_col,
            clamp_min,
            clamp_max
        );

    }

    auto end = std::chrono::steady_clock::now();
    total += std::chrono::duration_cast<std::chrono::nanoseconds>((end - start)).count();
    std::cout << "KleidiAI Time: " << total/runs << " average \n";
    double nanoseconds = static_cast<double>(total) / runs;
    double gflops = static_cast<double>(flops) / nanoseconds;
    std::cout << "KleidiAI Performance: " << gflops << " GFLOPS\n";

    total = 0;
    start = std::chrono::steady_clock::now();
    for(std::size_t i = 0; i < runs; ++i) {

        matmul(lhs, rhs, reference);

    }
    end = std::chrono::steady_clock::now();
    total += std::chrono::duration_cast<std::chrono::nanoseconds>((end - start)).count();
    std::cout << "Naive Time: " << total/runs << " average \n";
    nanoseconds = static_cast<double>(total) / runs;
    gflops = static_cast<double>(flops) / nanoseconds;
    std::cout << "Naive Performance: " << gflops << " GFLOPS\n";

    for (std::size_t i = 0; i < reference.size(); ++i) {
        if (kleidiai_output[i] != reference[i]) {
            std::cout << "nope" << '\n';
        }
    }

    return 0;
}