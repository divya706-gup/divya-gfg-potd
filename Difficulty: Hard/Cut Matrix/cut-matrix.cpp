class Solution {
    int dp[201][201][201];
    int suffixSum[201][201];
    int first_r[201][201];
    int first_c[201][201];
    int h_sum[201][201];
    int v_sum[201][201];
    int MOD = 1e9 + 7;

    int getOnes(int r1, int c1, int r2, int c2) {
        return suffixSum[r1][c1] - suffixSum[r1][c2 + 1] - suffixSum[r2 + 1][c1] + suffixSum[r2 + 1][c2 + 1];
    }

    void precomputeValidCuts(int n, int m) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                // Find the first row 'i' where the upper piece has at least one 1
                first_r[r][c] = n; 
                for (int i = r; i < n; ++i) {
                    if (getOnes(r, c, i, m - 1) > 0) {
                        first_r[r][c] = i;
                        break;
                    }
                }
                // Find the first col 'j' where the left piece has at least one 1
                first_c[r][c] = m;
                for (int j = c; j < m; ++j) {
                    if (getOnes(r, c, n - 1, j) > 0) {
                        first_c[r][c] = j;
                        break;
                    }
                }
            }
        }
    }

public:
    int findWays(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int m = matrix[0].size();

        // 1. Precompute 2D grid suffix sums for O(1) counting of 1s
        memset(suffixSum, 0, sizeof(suffixSum));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                suffixSum[i][j] = matrix[i][j] + suffixSum[i + 1][j] + suffixSum[i][j + 1] - suffixSum[i + 1][j + 1];
            }
        }

        // 2. Precompute the first valid row/col positions to cut
        precomputeValidCuts(n, m);

        // 3. Base Case: rem = 1 (No cuts remaining)
        memset(dp, 0, sizeof(dp));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                dp[r][c][1] = (getOnes(r, c, n - 1, m - 1) > 0) ? 1 : 0;
            }
        }

        // 4. Bottom-up DP for remaining cuts
        for (int rem = 2; rem <= k; ++rem) {
            // Compute suffix sums of the previous layer (rem - 1) to transition in O(1)
            for (int c = 0; c < m; ++c) {
                int current_sum = 0;
                for (int r = n - 1; r >= 0; --r) {
                    current_sum = (current_sum + dp[r][c][rem - 1]) % MOD;
                    h_sum[r][c] = current_sum;
                }
            }
            for (int r = 0; r < n; ++r) {
                int current_sum = 0;
                for (int j = m - 1; j >= 0; --j) {
                    current_sum = (current_sum + dp[r][j][rem - 1]) % MOD;
                    v_sum[r][j] = current_sum;
                }
            }

            // Fill the current layer
            for (int r = n - 1; r >= 0; --r) {
                for (int c = m - 1; c >= 0; --c) {
                    long long ways = 0;

                    // O(1) Horizontal cut lookup
                    int fr = first_r[r][c];
                    if (fr < n - 1) {
                        ways = (ways + h_sum[fr + 1][c]) % MOD;
                    }

                    // O(1) Vertical cut lookup
                    int fc = first_c[r][c];
                    if (fc < m - 1) {
                        ways = (ways + v_sum[r][fc + 1]) % MOD;
                    }

                    dp[r][c][rem] = ways;
                }
            }
        }

        return dp[0][0][k];
    }
};