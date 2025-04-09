https://leetcode.cn/problems/decode-ways

//��������
//��������2 639

class Solution {
public:
    int numDecodings(string s) {
        //�����  "10"->'J'  "20"->'T' �е�'0'���ܵ������ڣ� '0' ��1\2��
        //���ؽ���ɹ�������

        //���Բ���
        //return _Recur(s,0); 

        //return _Memory(s);


        //ת�Ʒ���
        //return _Dynam(s);

        return _Dynam2(s);

    }
private:

    /*-------------------------------------��̬�滮--------------------------------------*/
    // f(n) = 1   f(i)-> f(i+1)\f(i+2) f(i-1)-> f(i)\f(i+1)�����ڸ��ڵ������ں��ӽ������ĺ��ӽ����(��1��2)  
    //dp�ӵ׵���
    int _Dynam(string s) {
        std::array<int, 101> dp;
        dp.fill(0);
        int l_s = s.length();
        dp[l_s] = 1;

        for (int i = l_s - 1; i >= 0; --i) {
            if (s[i] == '0') {
                dp[i] = 0;
                continue;
            }
            //���ַ�����
            dp[i] = dp[i + 1]; //�����ַ���Ӱ�������ɵ����

            //˫�ַ�����
            if (i + 1 < s.length()) {
                int num = (s[i] - '0') * 10 + (s[i + 1] - '0');
                if (num >= 10 && num <= 26) {
                    dp[i] += dp[i + 2]; //˫�ַ���Ӱ���� ... 12 dp  => 1(2dp)����  12(dp) +<dp>
                }
            }

        }
        return dp[0];
    }

    // i->i+1 i+2 ���������� ���������� ά���������� 
    int _Dynam2(string s) {
        // i ���� i+1 i+2 
        int next = 1;//dp[n]   dp[i+1]
        int nextnext = 0;//dp[n+1]  dp[i+2]

        for (int i = s.length() - 1, cur; i >= 0; --i) {
            if (s[i] == '0') {
                cur = 0;
            }
            else {
                //���ַ�����
                cur = next; //�����ַ���Ӱ�������ɵ����

                //˫�ַ�����
                if (i + 1 < s.length()) {
                    int num = (s[i] - '0') * 10 + (s[i + 1] - '0');
                    if (num >= 10 && num <= 26) {
                        cur += nextnext; //˫�ַ���Ӱ���� ... 12 dp  => 1(2dp)����  12(dp) +<dp>
                    }
                }
            }
            nextnext = next;
            next = cur;

        }
        return next;
    }


    /*-------------------------------------���仯����--------------------------------------*/
    int _Memory(string& s) {
        vector<int> dp(s.length() + 1, -1);
        return _Memor(s, 0, dp);
    }
    // �ļ��仯���� �Ӷ�����
    int _Memor(string s, int i, vector<int>& dp) {
        if (i >= s.size()) return 1;
        if (s[i] == '0') return dp[i] = 0;

        //����
        if (dp[i] != -1) return dp[i];

        int ans = 0;

        ans += _Memor(s, i + 1, dp);

        if (i + 1 < s.size()) {
            int num = (s[i] - '0') * 10 + (s[i + 1] - '0');
            if (num >= 10 && num <= 26) {
                ans += _Memor(s, i + 2, dp);
            }
        }
        return dp[i] = ans;
    }


    /*-------------------------------------�ݹ鳢��--------------------------------------*/
        // �ݹ鳢��  recur :  
    int _Recur(string s, int i) {
        //�ɹ������������ַ���
        if (i >= s.size()) return 1;

        //�ַ�Ϊ'0'ʱ�޷����� : ���ַ�Ϊ'0' ���� ˫�ַ�'0X'
        if (s[i] == '0') return 0;

        int ans = 0;

        //���ַ�����1...9
        ans += _Recur(s, i + 1);

        //˫�ַ�����10...26
        if (i + 1 < s.size()) {
            int num = (s[i] - '0') * 10 + (s[i + 1] - '0'); //˫�ַ����ֻ�
            if (num >= 10 && num <= 26) {
                ans += _Recur(s, i + 2);
            }
        }

        return ans;
    }

};