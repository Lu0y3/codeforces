https://leetcode.cn/problems/maximal-rectangle
//最大矩形


class Solution {
private:
    //这里直接使用84的解法，，
    int largestRectangleArea(vector<int> h) {
        stack<int> stk;
        int max_area = 0;
        h.push_back(0); // 添加虚拟右边界

        for (int i = 0; i < h.size(); ++i) {
            while (!stk.empty() && h[i] < h[stk.top()]) {
                int height = h[stk.top()];
                stk.pop();
                int left = stk.empty() ? -1 : stk.top();
                max_area = max(max_area, height * (i - left - 1));
            }
            stk.push(i);
        }
        return max_area;
    }

public:

    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        // m行 n列
        int m = matrix.size(), n = matrix[0].size();
        //高度数组
        vector<int> heights(n, 0);
        int max_area = 0;

        //遍历行 构建柱状图
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                //--压缩数组--
                heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
            }
            //计算当前行最大矩形面积
            max_area = max(max_area, largestRectangleArea(heights));
        }
        return max_area;
    }

    /*
    1 1
    1 111
    11111
    1  1
上述是原图
假设此时是 m=1
    1 1
    ----- 看作一个柱状图
    1 1
    1 111
    ----- 计算每次遍历出来的最大值
    1 1
    1 111
    11111
    ----- 这里的解法是84 的 只不过是要进行 m次 找max
    ...
    */
    
};