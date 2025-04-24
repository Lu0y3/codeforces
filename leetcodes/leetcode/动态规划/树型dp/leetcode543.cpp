https://leetcode.cn/problems/diameter-of-binary-tree

// ��������ֱ��
// ����һ�ö������ĸ��ڵ㣬���ظ�����ֱ��
// �������� ֱ�� ��ָ�������������ڵ�֮���·���ĳ���
// ����·�����ܾ���Ҳ���ܲ��������ڵ� root
// ���ڵ�֮��·���� ���� ������֮�������ʾ


struct Info {
	int diamater;
	int height;
	//������xͷ �� max����maxֱ���� ��maxֱ����
	//����xͷ : x�������� + x�������� (�����ĸ߶Ȳ�+�����ĸ߶Ȳ�)
};


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
    struct Info {
        int diameter;
        int height;

        Info(int a, int b) : diameter(a), height(b) {}
    };

public:
    int diameterOfBinaryTree(TreeNode* root) { return max_diaOfTree(root); }
    // ������xͷ �� max����maxֱ���� ��maxֱ����
    // ����xͷ : x�������� + x�������� (�����ĸ߶Ȳ�+�����ĸ߶Ȳ�)
    //
    int max_diaOfTree(TreeNode* root) { return f(root).diameter; }

    Info f(TreeNode* root) {
        // ��
        if (root == nullptr)
            return Info(0, 0);

        Info infol = f(root->left);
        Info infor = f(root->right);

        int height_ = max(infol.height, infor.height) + 1;
        // ������xͷ
        int diameter_ = max(infol.diameter, infor.diameter);
        // ����xͷ
        diameter_ = max(diameter_, infol.height + infor.height);

        return Info(diameter_, height_);
    }
};