https://leetcode.cn/problems/minimum-score-triangulation-of-polygon

// 多边形三角剖分的最低得分
// 你有一个凸的 n 边形，其每个顶点都有一个整数值
// 给定一个整数数组values，其中values[i]是第i个顶点的值(顺时针顺序)
// 假设将多边形 剖分 为 n - 2 个三角形
// 对于每个三角形，该三角形的值是顶点标记的乘积
// 三角剖分的分数是进行三角剖分后所有 n - 2 个三角形的值之和
// 返回 多边形进行三角剖分后可以得到的最低分

//基于范围上划分点的可能性展开
class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        //return Memor_(values);
        return f2(values);
    }

    int Memor_(const vector<int>& values) {
        int n = values.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return f1(values, 0, n - 1, dp);
    }

    int f1(const vector<int>& values, int l, int r, vector<vector<int>>& dp) {
        if (dp[l][r] != -1) {
            return dp[l][r];
        }
        int ans = INT_MAX;

        if (l == r || l == r - 1) ans = 0;
        else {
            for (int m = l + 1; m < r; ++m) {  //基于范围上划分点
                ans = min(ans, f1(values, l, m, dp) + f1(values, m, r, dp) + values[l] * values[m] * values[r]);
            }
        }
        dp[l][r] = ans;
        return ans;
    }



    int f2(const vector<int>& values) {
        int n = values.size();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int l = n - 3; l >= 0; l--) {
            for (int r = l + 2; r < n; r++) {
                dp[l][r] = INT_MAX;
                for (int m = l + 1; m < r; m++) {
                    dp[l][r] = min(dp[l][r], dp[l][m] + dp[m][r] + values[l] * values[m] * values[r]);
                }
            }
        }
        return dp[0][n - 1];
    }

};