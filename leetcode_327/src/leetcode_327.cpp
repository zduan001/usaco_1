#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	void meger(vector<int>& nums, int l, int r, int m, int lower, int upper) {
		int i = l,j = m+1;
		vector<int> tmp;
		while(i <= m && j <=r){
			if (nums[r] - nums[l] < lower) {
				tmp.push_back(nums[r]);
//				count += (mid-i+1);
			} else if (nums[r] - nums[l] <= upper) {
				tmp.push_back(n)
			}
		}
	}
    int countRangeSum(vector<int>& nums, int lower, int upper) {
    	count = 0;
    	return count;

    }
private:
    int count
};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
