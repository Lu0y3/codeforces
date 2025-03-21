
// https://leetcode.cn/problems/largest-rectangle-in-histogram
//柱状图中最大的矩形

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        //寻找一个矩形的高和宽
        //谁决定了它的高？ 谁又决定了它的宽？
        //什么情况下矩形的高不会改变？ 在以此高的柱子两端都是高度>= 它的柱子  ： 两边出现小于它的柱子的内侧
        //思路： 找到一个柱子能代表当前区域[left right]的最低点  算面积
        
        int n = heights.size();
        stack<int> stk;
        int max_area = 0;
        // 添加虚拟右边界哨兵
        heights.push_back(0); 
        
        for (int i = 0; i <= n; ++i) {
            // 当遇到更矮的柱子时，计算当前栈顶元素作为最低点的面积
            while (!stk.empty() && heights[i] < heights[stk.top()]) {
                int cur_height = heights[stk.top()];
                stk.pop();
                // 确定左右边界
                int left = stk.empty() ? -1 : stk.top();
                int right = i;
                // 计算面积：高为cur_height，宽为right-left-1
                max_area = max(max_area, cur_height * (right - left - 1));
            }
            stk.push(i);
        }
        // 恢复原数组（可选）
        heights.pop_back(); 
        return max_area;
    }
};
