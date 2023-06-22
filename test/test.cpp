#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;


class Solution {
public:
    bool equalFrequency(string word) {
        cout << word << "\n";
        int charCount[3] = {0};
        for (char c : word) {
            std::cout << c - 'a' << "\n";
            charCount[c - 'a']++;
        }
        for (int c: charCount) {
            cout << "charCount = " << c << "\n";
        }

        unordered_map<int, int> freqCount;
        for (int c : charCount) {
            // std::cout << "c = " << c << "\n";
            if (c > 0) {
                freqCount[c]++;
            }
        }
        // cout << freqCount[1] << "\n";
        // cout << freqCount[2] << "\n";

        for (int c : charCount) {  // 2
            if (c == 0) {
                continue;
            }
            cout << "freqCount = " << freqCount[c] << "\n";
            freqCount[c]--;
            if (freqCount[c] == 0) {
                freqCount.erase(c);
            }
            if (c - 1 > 0) {
                freqCount[c - 1]++;
            }
            if (freqCount.size() == 1) {
                return true;
            }
            if (c - 1 > 0) {
                freqCount[c - 1]--;
                if (freqCount[c - 1] == 0) {
                    freqCount.erase(c - 1);
                }
            }
            freqCount[c]++;
        }
        return false;
    }
};

int main() {
    Solution a;
    string s1("abcc");
    // char s1[4] = {"a", "b", "c", "c"};
    bool flag = a.equalFrequency(s1);
    std::cout << "flag = " << flag;
    return 0;
}