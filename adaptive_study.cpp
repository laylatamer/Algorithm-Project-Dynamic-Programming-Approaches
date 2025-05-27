#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

double computeXP(double base_rate, double burnout_rate, int t) {
    double val = base_rate * t - burnout_rate * t * t;
    return max(val, 0.0);
}

int main() {
    const int MAX_HOURS = 16;
    int n, H;

    cout << "Enter number of subjects: ";
    cin >> n;

    cout << "Enter total study hours (max 16): ";
    cin >> H;
    if (H > MAX_HOURS) H = MAX_HOURS;

    vector<string> names(n);
    vector<double> base(n), burnout(n);

    for (int i = 0; i < n; ++i) {
        cout << "Subject " << i + 1 << " name: ";
        cin >> names[i];
        cout << "  Base XP per hour: ";
        cin >> base[i];
        cout << "  Burnout rate: ";
        cin >> burnout[i];
    }

    vector<vector<double>> xp(n, vector<double>(H + 1, 0));
    for (int i = 0; i < n; ++i)
        for (int t = 0; t <= H; ++t)
            xp[i][t] = computeXP(base[i], burnout[i], t);

    using State = pair<double, vector<int>>;
    vector<vector<State>> dp(n, vector<State>(H + 1, {-1e9, vector<int>(n, 0)}));

    for (int h = 0; h <= H; ++h) {
        dp[0][h].first = xp[0][h];
        dp[0][h].second[0] = h;
    }

    for (int i = 1; i < n; ++i) {
        for (int h = 0; h <= H; ++h) {
            for (int t = 0; t <= h; ++t) {
                double val = dp[i - 1][h - t].first + xp[i][t];
                if (val > dp[i][h].first) {
                    dp[i][h].first = val;
                    dp[i][h].second = dp[i - 1][h - t].second;
                    dp[i][h].second[i] = t;
                }
            }
        }
    }

    double maxXP = dp[n - 1][H].first;
    vector<int> allocation = dp[n - 1][H].second;

    cout << fixed << setprecision(2);
    cout << "\nMaximum XP achievable today: " << maxXP << "\n";
    cout << "Hour allocation per subject:\n";
    for (int i = 0; i < n; ++i)
        cout << "  " << names[i] << ": " << allocation[i] << " hours\n";

    return 0;
}
