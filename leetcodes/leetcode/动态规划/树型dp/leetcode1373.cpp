https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/

// ������������������ֵ��
// ����һ���� root Ϊ���Ķ�����
// ���㷵�� ���� ������������������ֵ��
// �����������Ķ������£�
// ����ڵ���������еļ�ֵ�� С�� �˽ڵ�ļ�ֵ
// ����ڵ���������еļ�ֵ�� ���� �˽ڵ�ļ�ֵ
// ����ڵ�������������������Ƕ���������


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
    struct Info {
        long max_val;
        long min_val;
        long sum;
        bool IsBST;
        long maxBSTsum;

        Info(long a, long b, long e, bool c, long d) :
            max_val(a), min_val(b), sum(e), IsBST(c), maxBSTsum(d) {
        }
    };

public:
    int maxSumBST(TreeNode* root) {
        auto res = f(root);
        return res.maxBSTsum > 0 ? res.maxBSTsum : 0;
    }

    Info f(TreeNode* root) {
        //����
        if (root == nullptr) return Info(INT_MIN, INT_MAX, 0, true, 0);

        Info infol = f(root->left);
        Info infor = f(root->right);

        long max_ = max((long)root->val, max(infol.max_val, infor.max_val));
        long min_ = min((long)root->val, min(infol.min_val, infor.min_val));

        bool isBST_ = infol.IsBST && infor.IsBST &&
            infol.max_val < root->val && infor.min_val > root->val;

        //���Ǵ������Ľ�� ��Ӳ������� [-3,-5,-1,-6,-4,null,6]  
        long sum_ = infol.sum + infor.sum + root->val;
        long maxBSTsum_ = max(infol.maxBSTsum, infor.maxBSTsum);

        if (isBST_) {
            maxBSTsum_ = max(sum_, maxBSTsum_);
        }

        return Info(max_, min_, sum_, isBST_, maxBSTsum_);
    }

};