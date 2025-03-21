https://leetcode.cn/problems/final-prices-with-a-special-discount-in-a-shop
//商品折扣后的最终价格


class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        int N = prices.size();
        vector<int> ans(N, 0);
        stack<int> stk;
        for (int i = N - 1; i >= 0; i--) {
            while (!stk.empty() && prices[i] < stk.top())
                stk.pop();
            //如果之后的商品没有当前商品价值高 则无折扣
            ans[i] = stk.empty() ? prices[i] : prices[i] - stk.top();

            stk.emplace(prices[i]);
        }
        return ans;
    }
};