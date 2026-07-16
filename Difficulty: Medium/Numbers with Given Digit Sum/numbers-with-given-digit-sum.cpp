class Solution {
public:
    int dp[10][82];

    int count(int n, int sum) {
        // Base case: if we have no more digits left, check if sum is 0
        if (n == 0) {
            return sum == 0;
        }
        
        // If sum becomes negative, it's invalid
        if (sum < 0) {
            return 0;
        }

        // Return cached result if already calculated
        if (dp[n][sum] != -1) {
            return dp[n][sum];
        }

        int ans = 0;
        // Loop through all possible digits (0 to 9)
        for (int i = 0; i <= 9; i++) {
            if (sum - i >= 0) {
                ans += count(n - 1, sum - i);
            }
        }

        return dp[n][sum] = ans;
    }

    int countWays(int n, int sum) {
        // Initialize the DP table with -1
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= sum; j++) {
                dp[i][j] = -1;
            }
        }

        int ans = 0;
        // The first digit cannot be 0, so loop from 1 to 9
        for (int i = 1; i <= 9; i++) {
            if (sum - i >= 0) {
                ans += count(n - 1, sum - i);
            }
        }

        // If no valid numbers are found, return -1 as specified
        if (ans == 0) {
            return -1;
        }
        
        return ans;
    }
};