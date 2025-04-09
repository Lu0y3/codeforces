https://leetcode.cn/problems/maximum-width-of-binary-tree

//�������������

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    //�뷨�� ������� ÿһ�� �����������ڸò�Ľ��ı��(���һ����¼��)���� ȡ���ֵ
    //����ά���� ��������  �ս��������չ���� ����ʹ��queueȥʵ���ˣ���Ҳ���������� ���ٽ�
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        //����: 2^3000 ?  666 �� ull
        queue<pair<TreeNode*, unsigned long long>> que; //����ڵ��������λ��

        que.push({ root,1 });
        int max_width = 1;

        while (!que.empty()) {
            int l_s = que.size();

            unsigned long long l_i = que.front().second; //����idx

            for (int i = 0; i < l_s; ++i) {
                auto [tmn, idx] = que.front(); // tmn ��� idx ����
                que.pop();

                //����max_width : ����-����  ��ÿ���������
                if (l_s - 1 == i)
                    max_width = max(max_width, int(idx - l_i + 1)); //�������ifʱ idx�������ҵ�  l������Ǹտ�ʼ������һ���idx

                //����
                if (tmn->left)
                    que.push({ tmn->left,idx * 2 - l_i }); // �����ȥ l_i��һ�������idx ��Ϊ�˻�ȡ���λ��;ͬʱ����ȡmax��(idx - l_i + 1)Ҳ���������λ�õ���� ����"ͬ��"��"ͬ��"�� ���ʵ�ڲ������Ի�ͼ֤��������Ҳ�ǻ�ͼ֤�����ġ�

                //�Һ���
                if (tmn->right)
                    que.push({ tmn->right,idx * 2 + 1 - l_i });

            }
        }
        return max_width;

    }
};

//�ٽ� BFS
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        unsigned long long res = 1;
        vector<pair<TreeNode*, unsigned long long>> arr;
        arr.emplace_back(root, 1L);
        while (!arr.empty()) {
            vector<pair<TreeNode*, unsigned long long>> tmp;
            for (auto& [node, index] : arr) {
                if (node->left) {
                    tmp.emplace_back(node->left, index * 2);
                }
                if (node->right) {
                    tmp.emplace_back(node->right, index * 2 + 1);
                }
            }
            res = max(res, arr.back().second - arr[0].second + 1);
            arr = move(tmp);
        }
        return res;
    }
};