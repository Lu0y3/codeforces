https://leetcode.cn/problems/predict-the-winner

// 预测赢家
// 给你一个整数数组 nums 。玩家 1 和玩家 2 基于这个数组设计了一个游戏
// 玩家 1 和玩家 2 轮流进行自己的回合，玩家 1 先手
// 开始时，两个玩家的初始分值都是 0
// 每一回合，玩家从数组的任意一端取一个数字
// 取到的数字将会从数组中移除，数组长度减1
// 玩家选中的数字将会加到他的得分上
// 当数组中没有剩余数字可取时游戏结束
// 如果玩家 1 能成为赢家，返回 true
// 如果两个玩家得分相等，同样认为玩家 1 是游戏的赢家，也返回 true
// 你可以假设每个玩家的玩法都会使他的分数最大化



// 区间dp 基于两端
class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {

        // return Recur_(nums);
        // return Memor_(nums);
        return Dynamic_(nums);
    }

    /*---------------递归----------------*/
    bool Recur_(const vector<int>& nums) {
        int n = nums.size();
        int sums{};
        for (const auto& sum : nums) {
            sums += sum;
        }
        int play1 = f1(nums, 0, n - 1);
        return play1 >= sums - play1;
    }
    //返回玩家1 的得分
    int f1(const vector<int>& nums, int l, int r) {
        if (l == r) return nums[l];
        if (l == r - 1) return nums[l] >= nums[r] ? nums[l] : nums[r];
        //玩家1 拿左边 后： 玩家2 拿 max 在 l+1 到 r 上 ; 玩家1只能拿之后的 min
        int p1 = nums[l] + min(f1(nums, l + 2, r), f1(nums, l + 1, r - 1));
        //玩家1 拿右边 后： 玩家2 拿 max 在 l 到 r-1 上 ; 玩家1只能拿之后的 min
        int p2 = nums[r] + min(f1(nums, l, r - 2), f1(nums, l + 1, r - 1));

        return max(p1, p2);
    }

    /*---------------记忆化----------------*/
    bool Memor_(const vector<int>& nums) {
        int n = nums.size();
        int sums{};
        for (const auto& sum : nums) {
            sums += sum;
        }
        vector<vector<int>> dp(n, vector<int>(n, -1));
        int play1 = f2(nums, 0, n - 1, dp);
        return play1 >= sums - play1;
    }
    //返回玩家1 的得分
    int f2(const vector<int>& nums, int l, int r, vector<vector<int>>& dp) {
        if (dp[l][r] != -1) {
            return dp[l][r];
        }
        int ans{};
        if (l == r)  ans = nums[l];
        else if (l == r - 1) ans = nums[l] >= nums[r] ? nums[l] : nums[r];
        else {
            int p1 = nums[l] + min(f2(nums, l + 2, r, dp), f2(nums, l + 1, r - 1, dp));
            int p2 = nums[r] + min(f2(nums, l, r - 2, dp), f2(nums, l + 1, r - 1, dp));
            ans = max(p1, p2);
        }
        dp[l][r] = ans;
        return ans;
    }

    /*----------------动态规划-----------------*/
    //: 严格位置依赖
    bool Dynamic_(const vector<int>& nums) {
        int n = nums.size();
        int sums{};
        for (const auto& sum : nums) {
            sums += sum;
        }
        vector<vector<int>> dp(n, vector<int>(n));

        for (int i = 0; i < n - 1; ++i) {
            dp[i][i] = nums[i];
            dp[i][i + 1] = max(nums[i], nums[i + 1]);
        }

        dp[n - 1][n - 1] = nums[n - 1];

        //这里的两层for 是为了满足依赖项的
        for (int l = n - 3; l >= 0; --l) {
            for (int r = l + 2; r < n; ++r) {
                dp[l][r] = max(
                    nums[l] + min(dp[l + 2][r], dp[l + 1][r - 1]),
                    nums[r] + min(dp[l][r - 2], dp[l + 1][r - 1])
                );
            }
        }
        int play1 = dp[0][n - 1];
        return play1 >= sums - play1;

    }

};