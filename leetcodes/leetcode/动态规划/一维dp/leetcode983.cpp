https://leetcode.cn/problems/minimum-cost-for-tickets


//最低票价



class Solution {
public:
    std::array<int, 3> durations = { 1,7,30 }; //costs对应下标天数

    int mincostTickets(vector<int>& days, vector<int>& costs) {
        //return f1(days,costs,0); //暴力递归 从顶到底展开  从底到顶求最小值

        //return f2(days, costs); //记忆化搜素 记忆每个f(i)的第一次记忆  从顶到底的动态规划

        return f3(days, costs); //dp  从底到顶的dp
    }
    /*-------------------------------------动态规划--------------------------------------*/
    //严格位置依赖的动态规划 从底到顶dp  ；  依赖 f(n) = ?(边界值)   f(n-1)->f(n)  f(n-2)->f(n-1) ... f(0)->f(1)
    //f1 f2 最后都只要 return dp[0] 的一个  其他不要 ； 压缩到只返回return一个 dp[0]  而不是递归返回

    int f3(vector<int>& days, vector<int>& costs) {
        //f2的dp长度跟days的大小有关 原因是我们需要递归返回days下标的
        //f3我们假定只需要返回一次 意思是只需要返回最中的最小值，而不是每一层的子最小值
        std::array<int, 366> dp; // 条件1 <= days[i] <= 365  外加一个越界值 初始cost最大值表示没算过
        dp.fill(INT_MAX);
        int n_days = days.size();
        //dp[0...n-1 n ... 365]
        dp[n_days] = 0; //边界 dp[n] = ? 首个被以来的值 f(n) = ?(0)

        for (int i = n_days - 1; i >= 0; --i) {

            for (int k = 0, j = i; k < 3; ++k) {
                while (j < n_days && durations[k] + days[i] > days[j]) ++j;
                dp[i] = min(dp[i], costs[k] + dp[j]);
            }
            //dp[i] 三种最小
        }

        return dp[0];
    }

    /*-------------------------------------记忆化搜索-------------------------------------*/
    // (f1有重复调用：假设前面的durations方案是 1+1+1+1+1+1+1+1 _f(8)... / 1+7 _f(8)... 重复调用f(8)求最小值 ；可模拟找) 
    //暴力改记忆化搜索，从顶到底
    //把返回值装在一个dp缓存表中 记忆化 {...f(n) ：o, f(m) ：p, f(k) ：w...}  大小 : **可变参数**决定 准备 n+1 加边界 \ n+0 返回非表内的
    //  std::vector<int> dp(days.size(), INT_MAX); //缓存调用的最小费用 避免重复调用  记忆化
    int f2(vector<int>& days, vector<int>& costs) {
        std::vector<int> dp(days.size(), INT_MAX); //缓存调用的最小费用 避免重复调用  记忆化
        return _f2(days, costs, 0, dp); //记忆化搜素
    }

    int _f2(vector<int>& days, vector<int>& costs, int i, std::vector<int>& dp) {
        if (i == days.size()) return 0; //边界
        if (dp[i] != INT_MAX) return dp[i]; //命中！缓存记忆 

        int min_costs = INT_MAX;

        //复杂度 for while 但常数时间 O(1) 最多30 /
        for (int k = 0, j = i; k < 3; k++) {

            while (j < days.size() && durations[k] + days[i] > days[j]) {
                ++j;
            }
            min_costs = min(min_costs, costs[k] + _f2(days, costs, j, dp));
        }
        // 返回n   O(n)
        dp[i] = min_costs; //记忆  
        return min_costs;

    }

    /*-------------------------------------暴力递归--------------------------------------*/
    //暴力递归 从下标i开始到末尾的最少花费
    int f1(vector<int>& days, vector<int>& costs, int i) {
        if (i == days.size()) return 0; //边界

        //i.... 第几天
        //int day = days[i];
        // durations三选一 往后找对应 1、7、30天后 (days下标)的位置开始找最小花费
        int min_costs = INT_MAX;

        //k 三种方案   j对应方案的下此开始位置
        for (int k = 0, j = i; k < 3; k++) {
            // 如题 第2天获得7天票 2.3.4...8可以 但9否
            while (j < days.size() && durations[k] + days[i] > days[j]) {
                ++j;
            }
            // (cost1[k1] + ( cost2[k2] + ... + (costk[kk] + ..。+ (costn[kn] + 0))  ) )
            min_costs = min(min_costs, costs[k] + f1(days, costs, j));
        }

        return min_costs;
    }

};