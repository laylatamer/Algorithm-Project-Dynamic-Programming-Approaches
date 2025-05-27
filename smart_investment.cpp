#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int smartInvestmentPlanning(const vector<int>& profit, const vector<int>& cooldown) {
    int n = profit.size();
    vector<int> dp(n + 1, 0);

    unordered_map<int, vector<int>> cooldownGroups;
    for (int i = 0; i < n; ++i) {
        cooldownGroups[cooldown[i]].push_back(i);
    }

    for (int i = n - 1; i >= 0; --i) {
        int skip = dp[i + 1];
        int nextDay = i + cooldown[i] + 1;
        int take = profit[i] + (nextDay < n ? dp[nextDay] : 0);
        dp[i] = max(skip, take);
    }

    return dp[0];
}

int main() {
    vector<int> profit = {3, 2, 5, 8, 7};
    vector<int> cooldown = {1, 1, 2, 1, 2};

    int maxProfit = smartInvestmentPlanning(profit, cooldown);
    cout << "Maximum Profit: " << maxProfit << endl;

    return 0;
}
