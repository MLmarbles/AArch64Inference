#include <cstddef>
#include <iostream>
#include <vector>

constexpr std::size_t M = 6;
constexpr std::size_t K = 8;
constexpr std::size_t N = 16;

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
    std::vector<float> lhs(M * K);
    std::vector<float> rhs(K * N);
    std::vector<float> reference(M * N, 0.0f);

    for (std::size_t i = 0; i < lhs.size(); ++i) {
        lhs[i] = static_cast<float>(static_cast<int>(i % 7) - 3);
    }

    for (std::size_t i = 0; i < rhs.size(); ++i) {
        rhs[i] = static_cast<float>(static_cast<int>(i % 5) - 2);
    }

    matmul(lhs, rhs, reference);

    std::cout << "Reference C[0][0] = " << reference[0] << '\n';

    return 0;
}