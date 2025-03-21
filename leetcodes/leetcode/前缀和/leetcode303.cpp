https://leetcode.cn/problems/range-sum-query-immutable
//����ͼ���-���鲻��
class NumArray {
    vector<int> sums;
public:
    //�ȼ����������ǰ׺��
    /*
     0  1 2  3 4  5  6
    [-2,0,3,-5,2,-1] ������
    [0,-2,-2,1,-4,-2,-3] ǰ׺��: i��ǰ����ǰ׺  ���һ��-3���������ۺ�

    ��ѯ���� l...r �������
    ���� ����[2..4]���ۼƺ� == [0,4] - [0,2] == ����5��ǰ׺�� - ����2��ǰ׺��
    -> sums[r+1] - sums[l]
    */

    NumArray(vector<int>& nums) {
        sums = new vector<int>(nums.size());
        sums[0] = nums[0];
        for (int i = 1; i <= nums.size(); ++i) {
            sums[i] = sums[i - 1] + nums[i];
        }
    }

    int sumRange(int left, int right) {
        return sums[right + 1] - sums[left];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */