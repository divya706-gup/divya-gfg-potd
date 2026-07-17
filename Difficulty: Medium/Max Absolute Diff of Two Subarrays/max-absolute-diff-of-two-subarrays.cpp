class Solution {
public:
    int maxDiffSubArrays(vector<int>& arr) {
        int n = arr.size();
        if (n < 2) return 0;

        // Arrays to store max and min subarray sums from left-to-right
        vector<int> leftMax(n), leftMin(n);
        // Arrays to store max and min subarray sums from right-to-left
        vector<int> rightMax(n), rightMin(n);

        // Forward pass: fill leftMax and leftMin
        int max_so_far = arr[0], current_max = arr[0];
        int min_so_far = arr[0], current_min = arr[0];
        leftMax[0] = max_so_far;
        leftMin[0] = min_so_far;

        for (int i = 1; i < n; i++) {
            current_max = max(arr[i], current_max + arr[i]);
            max_so_far = max(max_so_far, current_max);
            leftMax[i] = max_so_far;

            current_min = min(arr[i], current_min + arr[i]);
            min_so_far = min(min_so_far, current_min);
            leftMin[i] = min_so_far;
        }

        // Backward pass: fill rightMax and rightMin
        max_so_far = arr[n - 1]; current_max = arr[n - 1];
        min_so_far = arr[n - 1]; current_min = arr[n - 1];
        rightMax[n - 1] = max_so_far;
        rightMin[n - 1] = min_so_far;

        for (int i = n - 2; i >= 0; i--) {
            current_max = max(arr[i], current_max + arr[i]);
            max_so_far = max(max_so_far, current_max);
            rightMax[i] = max_so_far;

            current_min = min(arr[i], current_min + arr[i]);
            min_so_far = min(min_so_far, current_min);
            rightMin[i] = min_so_far;
        }

        // Calculate the maximum absolute difference by trying every split point
        int max_diff = 0;
        for (int i = 0; i < n - 1; i++) {
            int abs_diff1 = abs(leftMax[i] - rightMin[i + 1]);
            int abs_diff2 = abs(leftMin[i] - rightMax[i + 1]);
            max_diff = max({max_diff, abs_diff1, abs_diff2});
        }

        return max_diff;
    }
};