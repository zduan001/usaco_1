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
    		if (nums[i] > nums[j]) {
    			tmp.push_back(nums[i]);
    			count += (j-mid-1);
    			i++;
    		} else {

    			tmp.push_back(nums[j]);
    			j++;
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

    vector<int> countSmaller(vector<int>& nums) {
    	count = 0;
    	mergesort(nums, 0, nums.size() -1 );
    	cout << count << endl;
    	return nums;
    }
private:
    int count;
};

int main() {
	vector<int> input = {5,2,6,1};
	Solution* s = new Solution();
	s->countSmaller(input);
	for (auto i : input) {
		cout << i << " ";
	}

	return 0;
}