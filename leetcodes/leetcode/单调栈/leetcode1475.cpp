https://leetcode.cn/problems/final-prices-with-a-special-discount-in-a-shop
//��Ʒ�ۿۺ�����ռ۸�


class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        int N = prices.size();
        vector<int> ans(N, 0);
        stack<int> stk;
        for (int i = N - 1; i >= 0; i--) {
            while (!stk.empty() && prices[i] < stk.top())
                stk.pop();
            //���֮�����Ʒû�е�ǰ��Ʒ��ֵ�� �����ۿ�
            ans[i] = stk.empty() ? prices[i] : prices[i] - stk.top();

            stk.emplace(prices[i]);
        }
        return ans;
    }
};