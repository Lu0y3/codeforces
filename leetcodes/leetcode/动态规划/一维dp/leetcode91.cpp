https://leetcode.cn/problems/decode-ways

//解码问题
//解码问题2 639

class Solution {
public:
    int numDecodings(string s) {
        //特殊的  "10"->'J'  "20"->'T' 中的'0'不能单独存在， '0' 和1\2绑定
        //返回解码成功的总数

        //尝试策略
        //return _Recur(s,0); 

        //return _Memory(s);


        //转移方程
        //return _Dynam(s);

        return _Dynam2(s);

    }
private:

    /*-------------------------------------动态规划--------------------------------------*/
    // f(n) = 1   f(i)-> f(i+1)\f(i+2) f(i-1)-> f(i)\f(i+1)类似于父节点依赖于孩子结点这里的孩子结点是(左1右2)  
    //dp从底到顶
    int _Dynam(string s) {
        std::array<int, 101> dp;
        dp.fill(0);
        int l_s = s.length();
        dp[l_s] = 1;

        for (int i = l_s - 1; i >= 0; --i) {
            if (s[i] == '0') {
                dp[i] = 0;
                continue;
            }
            //单字符解码
            dp[i] = dp[i + 1]; //单个字符不影响解码完成的情况

            //双字符解码
            if (i + 1 < s.length()) {
                int num = (s[i] - '0') * 10 + (s[i + 1] - '0');
                if (num >= 10 && num <= 26) {
                    dp[i] += dp[i + 2]; //双字符的影响是 ... 12 dp  => 1(2dp)不变  12(dp) +<dp>
                }
            }

        }
        return dp[0];
    }

    // i->i+1 i+2 依赖项连续 用两个变量 维护滚动数组 
    int _Dynam2(string s) {
        // i 依赖 i+1 i+2 
        int next = 1;//dp[n]   dp[i+1]
        int nextnext = 0;//dp[n+1]  dp[i+2]

        for (int i = s.length() - 1, cur; i >= 0; --i) {
            if (s[i] == '0') {
                cur = 0;
            }
            else {
                //单字符解码
                cur = next; //单个字符不影响解码完成的情况

                //双字符解码
                if (i + 1 < s.length()) {
                    int num = (s[i] - '0') * 10 + (s[i + 1] - '0');
                    if (num >= 10 && num <= 26) {
                        cur += nextnext; //双字符的影响是 ... 12 dp  => 1(2dp)不变  12(dp) +<dp>
                    }
                }
            }
            nextnext = next;
            next = cur;

        }
        return next;
    }


    /*-------------------------------------记忆化搜素--------------------------------------*/
    int _Memory(string& s) {
        vector<int> dp(s.length() + 1, -1);
        return _Memor(s, 0, dp);
    }
    // 改记忆化搜索 从顶到底
    int _Memor(string s, int i, vector<int>& dp) {
        if (i >= s.size()) return 1;
        if (s[i] == '0') return dp[i] = 0;

        //命中
        if (dp[i] != -1) return dp[i];

        int ans = 0;

        ans += _Memor(s, i + 1, dp);

        if (i + 1 < s.size()) {
            int num = (s[i] - '0') * 10 + (s[i + 1] - '0');
            if (num >= 10 && num <= 26) {
                ans += _Memor(s, i + 2, dp);
            }
        }
        return dp[i] = ans;
    }


    /*-------------------------------------递归尝试--------------------------------------*/
        // 递归尝试  recur :  
    int _Recur(string s, int i) {
        //成功解码完整个字符串
        if (i >= s.size()) return 1;

        //字符为'0'时无法解码 : 单字符为'0' 或者 双字符'0X'
        if (s[i] == '0') return 0;

        int ans = 0;

        //单字符解码1...9
        ans += _Recur(s, i + 1);

        //双字符解码10...26
        if (i + 1 < s.size()) {
            int num = (s[i] - '0') * 10 + (s[i + 1] - '0'); //双字符数字化
            if (num >= 10 && num <= 26) {
                ans += _Recur(s, i + 2);
            }
        }

        return ans;
    }

};