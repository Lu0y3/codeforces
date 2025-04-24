https://leetcode.cn/problems/minimum-insertion-steps-to-make-a-string-palindrome/

// 让字符串成为回文串的最少插入次数
// 给你一个字符串 s
// 每一次操作你都可以在字符串的任意位置插入任意字符
// 请你返回让s成为回文串的最少操作次数

/*区间dp: 可能性展开 基于两侧端点 */



class Solution {
public:
    int minInsertions(string s) {
        //return Memory_(s);
        //return Dynamic_(s);
        return Dynamic_space(s);


        // int n = s.length();

        // return Recur_(s,0,n-1); 
    }

    /*------------------递归--------------------*/
    int Recur_(const string& s, int l, int r) {
        if (l == r) return 0;  //区间上只有一个字符
        if (l + 1 == r) return s[l] == s[r] ? 0 : 1; //区间上有两个字符 aa  ab 

        //两个以上
        if (s[l] == s[r]) //基于两端
        {
            return Recur_(s, l + 1, r - 1);
        }
        else {
            return min(Recur_(s, l + 1, r), Recur_(s, l, r - 1)) + 1;
        }
    }


    /*------------------记忆化--------------------*/
    int Memory_(const string& s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, -1)); //dp[l][r]: 在区间l...r上是否以及递归
        return Memor_(s, 0, n - 1, dp);
    }
    int Memor_(const string& s, int l, int r, vector<vector<int>>& dp) {
        if (dp[l][r] != -1) {
            return dp[l][r];
        }
        int ans{};

        if (l == r) ans = 0;  //区间上只有一个字符
        else if (l + 1 == r)  ans = s[l] == s[r] ? 0 : 1; //区间上有两个字符 aa  ab 

        //两个以上
        else if (s[l] == s[r]) //基于两端
        {
            ans = Memor_(s, l + 1, r - 1, dp);
        }
        else {
            ans = min(Memor_(s, l + 1, r, dp), Memor_(s, l, r - 1, dp)) + 1;
        }

        dp[l][r] = ans;
        return ans;
    }

    /*------------------动态规划--------------------*/
    // : 严格位置依赖   二维表中(l,r) 依赖 (l+1,r-1)左下 和 (l,r-1)\(l+1,r)左 下
    int Dynamic_(const string& s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0)); // n * n 的二维表 
        //上面已经解决l == r  下面是l+1 == r
        for (int l = 0; l < n - 1; ++l) {
            dp[l][l + 1] = s[l] == s[l + 1] ? 0 : 1;
        }

        //自下向上 每层自左向右 
        for (int l = n - 3; l >= 0; --l) {
            for (int r = l + 2; r < n; ++r) {
                if (s[l] == s[r]) {
                    dp[l][r] = dp[l + 1][r - 1];
                }
                else {
                    dp[l][r] = min(dp[l][r - 1], dp[l + 1][r]) + 1;
                }

            }
        }
        return dp[0][n - 1];
    }

    // : 严格位置依赖 + 空间压缩  只需要维护 左下 左 下 三个 
    // 二维dp 改成 一维dp   一维dp中维护不同层的值
    // 传递过程可以想象成一个 田字 右上角为当前要求的值 在每层向右移动  
    //可以参考从递归入手二维动态规划，题目4，最长回文子序列问题的讲解
    int Dynamic_space(const string& s) {
        int n = s.length();
        if (n < 2) return 0;

        vector<int> dp(n, 0);
        dp[n - 1] = s[n - 1] == s[n - 2] ? 0 : 1;

        for (int l = n - 3, leftDown{}, backUp{}; l >= 0; --l) {

            leftDown = dp[l + 1]; //保存旧dp[l + 1]
            dp[l + 1] = s[l] == s[l + 1] ? 0 : 1; //更新新dp[l + 1]

            for (int r = l + 2; r < n; ++r) {
                backUp = dp[r]; //保存旧dp[r]

                //更新新dp[r]
                if (s[l] == s[r]) {
                    dp[r] = leftDown;
                }
                else {
                    dp[r] = min(dp[r - 1], dp[r]) + 1;
                }

                leftDown = backUp; //更新leftDown

            }
        }
        return dp[n - 1];
    }

};
