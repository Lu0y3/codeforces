https://leetcode.cn/problems/daily-temperatures
//Ã¿ÈÕÎÂ¶È


class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        // temperatures[] = {23, 45, 23, 53, 43}
        // answer[] = {1,2,1,0,0}
        // 
        int n = temperatures.size();
        vector<int> answer(n, 0);
        stack<int> stk;

        for (int i = 0; i < n; i++) {
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
                int t = stk.top();
                stk.pop();
                answer[t] = i - t;
            }
            stk.push(i);
        }
        return answer;
    }
};