https://leetcode.cn/problems/minimum-path-sum

//最小路径和

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        //return _Recur(grid, n-1, m-1);
        //return _Memor(grid, n-1, m-1);
        //return _Dymac(grid, n-1, m-1);
        return _Dymac2(grid, n - 1, m - 1);

        //需要注意的是这里填的是n-1 和 m-1 为了相对好看点，下面要做出更改

    }

    // 依赖： (i,j) -> min{(i ,j-1),(i-1 ,j)}...  (0,0)->(0,0) ... (3,3)->(3,2)\(2,3)

    /*--------------------------------动态规划---------------------------------*/
    /*
        严格位置依赖
    */
    int _Dymac(const vector<vector<int>>& grid, int n, int m) {
        //首先把最上和最左的都搞出来，，即只依赖一个的
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        dp[0][0] = grid[0][0];
        //左列
        for (int i = 1; i <= n; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        //上行
        for (int j = 1; j <= m; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }

        //依赖项 上左
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        return dp[n][m];
    }

    /*
        严格位置依赖 + 空间压缩(滚动数组两个或者一个)
    */
    int _Dymac2(const vector<vector<int>>& grid, int n, int m) {
        //首先把最上和最左的都搞出来，，即只依赖一个的
        vector<int> dp(m + 1, -1);
        dp[0] = grid[0][0];
        //初始化第一次 (0，n)
        for (int j = 1; j <= m; j++) {
            dp[j] = dp[j - 1] + grid[0][j];
        }

        //依赖项 
        for (int i = 1; i <= n; i++) {
            dp[0] += grid[i][0];
            for (int j = 1; j <= m; j++) {
                dp[j] = grid[i][j] + min(dp[j], dp[j - 1]);
            }
        }

        return dp[m];
    }



    /*--------------------------------记忆化搜素---------------------------------*/
    int _Memor(const vector<vector<int>>& grid, int n, int m) {
        // array<array<int,m>,n> dp;  编译期常量constexpr
        // dp.fill(-1);
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return _Memory(grid, n, m, dp);
    }

    int _Memory(const vector<vector<int>>& grid, int n, int m, vector<vector<int>>& dp) {
        if (dp[n][m] != -1) return dp[n][m];

        if (n == 0 && m == 0) return dp[0][0] = grid[0][0];

        int left = INT_MAX;
        int up = INT_MAX;
        if (n - 1 >= 0) {
            left = _Memory(grid, n - 1, m, dp); //左
        }
        if (m - 1 >= 0) {
            up = _Memory(grid, n, m - 1, dp); //上
        }
        dp[n][m] = grid[n][m] + min(left, up);


        return  dp[n][m];
    }


    /*--------------------------------暴力递归---------------------------------*/
    /*
    虽然让我们从左上到右下的最小值， 第一想法是从左上开始找最小值走，但这是错误的，，我们把路径的递归展开就会发现我们需要的是路径和最小，不是开始最小或最后最小。 依靠依赖项；我们依赖的是当前[n,m]的上下的 位置路径和 而每个位置都会有依赖但是 初始点grid[0][0]无上下依赖故作边界
    */
    int _Recur(const vector<vector<int>>& grid, int n, int m) {
        if (n == 0 && m == 0) return grid[0][0];

        int left = INT_MAX;
        int up = INT_MAX;
        if (n - 1 >= 0) {
            left = _Recur(grid, n - 1, m); //左
        }
        if (m - 1 >= 0) {
            up = _Recur(grid, n, m - 1); //上
        }

        return grid[n][m] + min(left, up); // 这里的min虽然是找的较小值，但依旧是要递归遍历创造多条路径(二叉)，  最后全部展开的路径一定是  grid[n][m] + min { grid[n-1][m]\grid[n][m-1] + min{ ..{grid[0][0]}.. }  }  从中选优。
    }

};