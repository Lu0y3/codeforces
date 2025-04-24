https://leetcode.cn/problems/minimum-cost-to-cut-a-stick/

// 切棍子的最小成本
// 有一根长度为n个单位的木棍，棍上从0到n标记了若干位置
// 给你一个整数数组cuts，其中cuts[i]表示你需要将棍子切开的位置
// 你可以按顺序完成切割，也可以根据需要更改切割的顺序
// 每次切割的成本都是当前要切割的棍子的长度，切棍子的总成本是历次切割成本的总和
// 对棍子进行切割将会把一根木棍分成两根较小的木棍
// 这两根木棍的长度和就是切割前木棍的长度
// 返回切棍子的最小总成本

class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        sort(cuts.begin(), cuts.end());
        //return f1(n, cuts);
        return f3(n, cuts);
    }

    /*--------------记忆化+递归---------------*/
    int f1(int n, const vector<int>& cuts) {
        int m = cuts.size();
        vector<int> cuts_(m + 2);
        cuts_[0] = 0;
        cuts_[m + 1] = n;
        for (int i = 1; i <= m; ++i) {
            cuts_[i] = cuts[i - 1];
        }
        vector<vector<int>> dp(m + 2, vector<int>(m + 2, -1));
        return f2(cuts_, 1, m, dp);
    }

    int f2(const vector<int>& cuts_, int l, int r, vector<vector<int>>& dp) {
        if (dp[l][r] != -1)
            return dp[l][r];
        if (l > r)
            return 0;
        if (l == r)
            return cuts_[r + 1] - cuts_[l - 1];
        int ans = INT_MAX;
        for (int k = l; k <= r; ++k) {
            ans = min(ans, f2(cuts_, l, k - 1, dp) + f2(cuts_, k + 1, r, dp));
        }
        ans += cuts_[r + 1] - cuts_[l - 1];
        dp[l][r] = ans;
        return ans;
    }
    /*--------------动态规划---------------*/

    int f3(int n, const vector<int>& cuts) {
        int m = cuts.size();
        vector<int> cuts_(m + 2);
        cuts_[0] = 0;
        for (int i = 1; i <= m; ++i) {
            cuts_[i] = cuts[i - 1];
        }
        cuts_[m + 1] = n;

        vector<vector<int>> dp(m + 2, vector<int>(m + 2, 0));
        //0-m+1上 1-m维护二维表  0行0列全为0 
        for (int i = 1; i <= m; ++i) {
            dp[i][i] = cuts_[i + 1] - cuts_[i - 1];
        }
        //上面把对角线填了  
        //两层for是从 (m-1,m)开始  二维表右下角的上一行同列格子
        for (int l = m - 1, tmp; l >= 1; --l) {
            for (int r = l + 1; r <= m; ++r) {

                tmp = INT_MAX;
                for (int k = l; k <= r; ++k) { //基于范围 划分点
                    tmp = min(tmp, dp[l][k - 1] + dp[k + 1][r]);
                }
                dp[l][r] = tmp + cuts_[r + 1] - cuts_[l - 1];

            }
        }

        return dp[1][m];

    }


};