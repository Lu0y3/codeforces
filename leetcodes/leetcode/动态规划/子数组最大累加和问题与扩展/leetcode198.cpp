https://leetcode.cn/problems/house-robber

//打家劫舍

// 数组中不能选相邻元素的最大累加和
// 给定一个数组，可以随意选择数字
// 但是不能选择相邻的数字，返回能得到的最大累加和



class Solution {
public:
    int rob(vector<int>& nums) {
        return Dynmac_(nums);
    }

    int Dynmac_(const vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        }
        if (n == 2) {
            return max(nums[0], nums[1]);
        }
        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = nums[0] >= nums[1] ? nums[0] : nums[1];

        for (int i = 2; i < n; ++i) {
            dp[i] = max(dp[i - 1], max(dp[i - 2], dp[i - 2] + nums[i]));
        }
        return dp[n - 1];
    }


    int Dynmac_compress(const vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        }
        if (n == 2) {
            return max(nums[0], nums[1]);
        }

        int prepre = nums[0];
        int pre = nums[0] >= nums[1] ? nums[0] : nums[1];

        for (int i = 2, cur{}; i < n; ++i) {
            cur = max(cur, max(prepre, pre + nums[i]));
            prepre = pre;
            pre = cur;
        }
        return pre;

    }

};

