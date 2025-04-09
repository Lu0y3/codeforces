https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal

//��ݲ�α���


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
     vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
         // cnt % 2 = ?   0 - 0  ����  1 - 1 ���ҵ���  2 - 0 
         // 
         queue<TreeNode*> que;
         vector<vector<int>> ans;
         int cnt{};
         if (root) que.push(root);

         while (!que.empty()) {
             //��ʱ��¼
             vector<int> tmp;

             for (int i = que.size(); i > 0; --i) {
                 auto t = que.front();
                 que.pop();
                 tmp.push_back(t->val);
                 // ���  ��������
                 //if(cnt%2 == 1) if(t->right) que.push(t->right);
                 if (t->left) que.push(t->left);
                 if (t->right) que.push(t->right);
                 // if(cnt%2 == 0) if(t->right) que.push(t->right);

             }
             if (cnt % 2) reverse(tmp.begin(), tmp.end());
             ++cnt;
             ans.push_back(tmp);

         }
         return ans;
     }
 };