#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval {
    int start;
    int end;
    int weight;
};

// finds the rightmost compatible interval with the interval at current index
int latestNonOverlapping(const vector<Interval>& intervals, int index) {
    int low = 0, high = index - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (intervals[mid].end <= intervals[index].start) {
            if (intervals[mid + 1].end <= intervals[index].start) {
                low = mid + 1;
            } else {
                return mid;
            }
        } else {
            high = mid - 1;
        }
    }
    return -1;
}


int maxWeightIntervalScheduling(vector<Interval>& intervals) {
    int n = intervals.size();
    // Sort intervals by end time
    sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
        return a.end < b.end;
    });

    // DP array to store the maximum weight at each interval
    vector<int> dp(n);
    dp[0] = intervals[0].weight;

    for (int i = 1; i < n; ++i) {
        
        int includeWeight = intervals[i].weight;
        int latest = latestNonOverlapping(intervals, i);
        if (latest != -1) {
            includeWeight += dp[latest];
        }

        // Choose whether or not to pick the curren interval
        dp[i] = max(dp[i - 1], includeWeight);
    }

    return dp[n - 1];
}

int main() {
    // start, end, weight
    vector<Interval> intervals = {
        {1, 3, 5},
        {2, 5, 6},
        {4, 6, 5},
        {6, 7, 4},
        {5, 8, 11},
        {7, 9, 2}
    };

    int maxWeight = maxWeightIntervalScheduling(intervals);
    cout << "Maximum Weight of Non-Overlapping Intervals: " << maxWeight << endl;

    return 0;
}
