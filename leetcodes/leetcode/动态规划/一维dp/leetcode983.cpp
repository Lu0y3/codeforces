https://leetcode.cn/problems/minimum-cost-for-tickets


//���Ʊ��



class Solution {
public:
    std::array<int, 3> durations = { 1,7,30 }; //costs��Ӧ�±�����

    int mincostTickets(vector<int>& days, vector<int>& costs) {
        //return f1(days,costs,0); //�����ݹ� �Ӷ�����չ��  �ӵ׵�������Сֵ

        //return f2(days, costs); //���仯���� ����ÿ��f(i)�ĵ�һ�μ���  �Ӷ����׵Ķ�̬�滮

        return f3(days, costs); //dp  �ӵ׵�����dp
    }
    /*-------------------------------------��̬�滮--------------------------------------*/
    //�ϸ�λ�������Ķ�̬�滮 �ӵ׵���dp  ��  ���� f(n) = ?(�߽�ֵ)   f(n-1)->f(n)  f(n-2)->f(n-1) ... f(0)->f(1)
    //f1 f2 ���ֻҪ return dp[0] ��һ��  ������Ҫ �� ѹ����ֻ����returnһ�� dp[0]  �����ǵݹ鷵��

    int f3(vector<int>& days, vector<int>& costs) {
        //f2��dp���ȸ�days�Ĵ�С�й� ԭ����������Ҫ�ݹ鷵��days�±��
        //f3���Ǽٶ�ֻ��Ҫ����һ�� ��˼��ֻ��Ҫ�������е���Сֵ��������ÿһ�������Сֵ
        std::array<int, 366> dp; // ����1 <= days[i] <= 365  ���һ��Խ��ֵ ��ʼcost���ֵ��ʾû���
        dp.fill(INT_MAX);
        int n_days = days.size();
        //dp[0...n-1 n ... 365]
        dp[n_days] = 0; //�߽� dp[n] = ? �׸���������ֵ f(n) = ?(0)

        for (int i = n_days - 1; i >= 0; --i) {

            for (int k = 0, j = i; k < 3; ++k) {
                while (j < n_days && durations[k] + days[i] > days[j]) ++j;
                dp[i] = min(dp[i], costs[k] + dp[j]);
            }
            //dp[i] ������С
        }

        return dp[0];
    }

    /*-------------------------------------���仯����-------------------------------------*/
    // (f1���ظ����ã�����ǰ���durations������ 1+1+1+1+1+1+1+1 _f(8)... / 1+7 _f(8)... �ظ�����f(8)����Сֵ ����ģ����) 
    //�����ļ��仯�������Ӷ�����
    //�ѷ���ֵװ��һ��dp������� ���仯 {...f(n) ��o, f(m) ��p, f(k) ��w...}  ��С : **�ɱ����**���� ׼�� n+1 �ӱ߽� \ n+0 ���طǱ��ڵ�
    //  std::vector<int> dp(days.size(), INT_MAX); //������õ���С���� �����ظ�����  ���仯
    int f2(vector<int>& days, vector<int>& costs) {
        std::vector<int> dp(days.size(), INT_MAX); //������õ���С���� �����ظ�����  ���仯
        return _f2(days, costs, 0, dp); //���仯����
    }

    int _f2(vector<int>& days, vector<int>& costs, int i, std::vector<int>& dp) {
        if (i == days.size()) return 0; //�߽�
        if (dp[i] != INT_MAX) return dp[i]; //���У�������� 

        int min_costs = INT_MAX;

        //���Ӷ� for while ������ʱ�� O(1) ���30 /
        for (int k = 0, j = i; k < 3; k++) {

            while (j < days.size() && durations[k] + days[i] > days[j]) {
                ++j;
            }
            min_costs = min(min_costs, costs[k] + _f2(days, costs, j, dp));
        }
        // ����n   O(n)
        dp[i] = min_costs; //����  
        return min_costs;

    }

    /*-------------------------------------�����ݹ�--------------------------------------*/
    //�����ݹ� ���±�i��ʼ��ĩβ�����ٻ���
    int f1(vector<int>& days, vector<int>& costs, int i) {
        if (i == days.size()) return 0; //�߽�

        //i.... �ڼ���
        //int day = days[i];
        // durations��ѡһ �����Ҷ�Ӧ 1��7��30��� (days�±�)��λ�ÿ�ʼ����С����
        int min_costs = INT_MAX;

        //k ���ַ���   j��Ӧ�������´˿�ʼλ��
        for (int k = 0, j = i; k < 3; k++) {
            // ���� ��2����7��Ʊ 2.3.4...8���� ��9��
            while (j < days.size() && durations[k] + days[i] > days[j]) {
                ++j;
            }
            // (cost1[k1] + ( cost2[k2] + ... + (costk[kk] + ..��+ (costn[kn] + 0))  ) )
            min_costs = min(min_costs, costs[k] + f1(days, costs, j));
        }

        return min_costs;
    }

};