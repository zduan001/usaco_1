// http://usaco.org/index.php?page=viewproblem2&cpid=91
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums, int start, int end, int mid) {
    	int i, j;
    	vector<int> tmp;
    	i = start;
    	j = mid+1;
    	while(i <= mid && j <= end) {
    		if (nums[j] >= nums[i]) {
    			tmp.push_back(nums[j]);
    			count += (mid -i +1);
    			j++;
    		} else {
    			tmp.push_back(nums[i]);
//    			count += (j-mid-1);
    			i++;
    		}
    	}
    	while(i <= mid) {
    		tmp.push_back(nums[i++]);
    	}
    	while(j <= end) {
    		tmp.push_back(nums[j++]);
    	}
    	for (int i = start; i <=end; i++) {
    		nums[i] = tmp[i - start];
    	}
    }

    void mergesort(vector<int>& nums, int start, int end) {
    	if (start >= end) {
    		return;
    	}
    	int mid = start + (end-start)/2;
    	mergesort(nums, start, mid);
    	mergesort(nums, mid+1, end);
    	merge(nums, start, end, mid);
    }

    int countInverse(vector<int>& nums) {
    	count = 0;
    	mergesort(nums, 0, nums.size() -1 );
    	return count;
    }
private:
    int count;
};

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> arr(n, 0);
	int tmp;
	for (int i = 0; i < n; i++) {
		cin >> tmp;
		arr[i] = tmp >= m ? 1 : -1;
	}
	vector<int> sum_arr;
	tmp = 0;
	for (int i = 0; i< n; i++) {
		tmp += arr[i];
		sum_arr.push_back(tmp);
	}
	for (auto i : sum_arr) {
		cout << i << " ";
	}
	cout << endl;
	Solution*  s = new Solution();
	int res = s->countInverse(sum_arr);
	for (auto i : sum_arr) {
		res += i >=0 ? 1 : 0;
	}
	cout << res;

	return 0;
}
