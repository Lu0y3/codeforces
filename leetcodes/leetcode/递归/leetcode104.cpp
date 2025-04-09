https://leetcode.cn/problems/maximum-depth-of-binary-tree

//�����������

//���������ݹ鷽��Ĳ�ͬ��Ҫ�� +1�ķ�ʽ
// �Ե������� ��ȫ���ݹ�չ�� Ȼ��ӵײ�+1 ���� ��������
// �Զ������� �ߵݹ�չ�� ������ +1  ��������

//�Ե����� �� 

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;

        int l_d = maxDepth(root->left);
        int r_d = maxDepth(root->right);

        return max(l_d, r_d) + 1;
    }
};


//�Զ�����

class Solution {
public:
    int maxDepth(TreeNode* root) {
        int ans = 0;

        auto dfs = [&](this auto&& dfs, TreeNode* node, int depth) -> void {
            if (node == nullptr) {
                return;
            }
            depth++;
            ans = max(ans, depth);
            dfs(node->left, depth);
            dfs(node->right, depth);
            };

        dfs(root, 0);
        return ans;
    }
};