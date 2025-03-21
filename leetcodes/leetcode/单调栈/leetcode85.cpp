https://leetcode.cn/problems/maximal-rectangle
//������


class Solution {
private:
    //����ֱ��ʹ��84�Ľⷨ����
    int largestRectangleArea(vector<int> h) {
        stack<int> stk;
        int max_area = 0;
        h.push_back(0); // ��������ұ߽�

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
        // m�� n��
        int m = matrix.size(), n = matrix[0].size();
        //�߶�����
        vector<int> heights(n, 0);
        int max_area = 0;

        //������ ������״ͼ
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                //--ѹ������--
                heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
            }
            //���㵱ǰ�����������
            max_area = max(max_area, largestRectangleArea(heights));
        }
        return max_area;
    }

    /*
    1 1
    1 111
    11111
    1  1
������ԭͼ
�����ʱ�� m=1
    1 1
    ----- ����һ����״ͼ
    1 1
    1 111
    ----- ����ÿ�α������������ֵ
    1 1
    1 111
    11111
    ----- ����Ľⷨ��84 �� ֻ������Ҫ���� m�� ��max
    ...
    */
    
};