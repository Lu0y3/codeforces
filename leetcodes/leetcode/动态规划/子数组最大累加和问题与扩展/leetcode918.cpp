https://leetcode.cn/problems/maximum-sum-circular-subarray


// �������������������ۼӺ�
// ����һ������nums������Ϊn
// nums��һ���������飬�±�0���±�n-1������һ���
// ���ػ��������У�����������ۼӺ�

// 1> �����ϲ����0  ����д
// 2> ���ϵ�    �����ۼӺ�max = all�� - �������ۼӺ�min


/*-------------------ȡ��------------------*/
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        
        return Negate_(nums);
    }

    /*----------------��̬�滮-------------------*/



    /*-------------------ȡ��------------------*/
    int Negate_(vector<int>& nums)
    {
        int n = nums.size(), all = nums[0], maxsum = nums[0], minsum = nums[0];
        for (int i = 1, maxpre = nums[0], minpre = nums[0]; i < n; ++i) {
            all += nums[i];
            maxpre = max(maxpre + nums[i], nums[i]);
            maxsum = max(maxsum, maxpre);
            minpre = min(minpre + nums[i], nums[i]);
            minsum = min(minsum, minpre);
        }
        // maxsum   \ all - minsum
        if (maxsum < 0) { //[...]�ж��Ǹ���
            return maxsum;
        }
        else {
            return max(maxsum, all - minsum);
        }
    }


    /*----------------��������-------------------*/




};

