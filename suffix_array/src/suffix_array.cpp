#include <bits/stdc++.h>
#define MAX_N 200

using namespace std;

typedef pair<int,int> ii;
char T[MAX_N];
char P[MAX_N];
int n;
int m;
int RA[MAX_N], tmpRA[MAX_N];
int SA[MAX_N], tmpSA[MAX_N];
int c[MAX_N];

//void countingSort(int k) {
//	int i, sum, maxi = max(300, n); // max char is 256
//	memset(c, 0, sizeof(c));
//
//	for (i = 0; i < n; i++) {
//		c[i + k < n ? RA[i+k] : 0] ++;
//	}
////	for (i = 0; i < maxi; i++) {
////		if (c[i] >0) {
////			cout << "c[" << i << "] = " << c[i] <<endl;
////		}
////	}
////	cout << " ------------------ " << endl;
//	for (i = sum = 0; i < maxi; i++) {
//		int t = c[i];
//		c[i] = sum;
//		sum += t;
//	}
////	for (i = 0; i < maxi; i++) {
////		if (c[i] >0) {
////			cout << "c[" << i << "] = " << c[i] <<endl;
////		}
////	}
////	cout << " ------------------ " << endl;
//	for (i = 0; i < n; i++) {
////		cout << i << "  ";
////		cout << "c[" << (SA[i]+k < n ? RA[SA[i]+k] : 0) << "] = "
////		<< (c[(SA[i]+k < n ? RA[SA[i]+k] : 0)])  <<  endl;
//		tmpSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
//	}
//
////	for (int i = 0; i < n; i++) {
//////		cout << i << endl;
////		cout << SA[i] << "  " << tmpSA[i] << endl;
////	}
//
//	for (i = 0; i < n; i++) {
//		SA[i] = tmpSA[i];
//	}
//}

void countingSort(int k) {                                          // O(n)
  int i, sum, maxi = max(300, n);   // up to 255 ASCII chars or length of n
  memset(c, 0, sizeof c);                          // clear frequency table
  for (i = 0; i < n; i++)       // count the frequency of each integer rank
    c[i + k < n ? RA[i + k] : 0]++;
  for (i = sum = 0; i < maxi; i++) {
    int t = c[i]; c[i] = sum; sum += t;
  }
  for (i = 0; i < n; i++)          // shuffle the suffix array if necessary
    tmpSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i]; // still have trouble to undrstand this line
  for (i = 0; i < n; i++)                     // update the suffix array SA
    SA[i] = tmpSA[i];
}

void constructSA() {         // this version can go up to 100000 characters
  int i, k, r;
  for (i = 0; i < n; i++) RA[i] = T[i];                 // initial rankings
  for (i = 0; i < n; i++) SA[i] = i;     // initial SA: {0, 1, 2, ..., n-1}
  for (k = 1; k < n; k <<= 1) {       // repeat sorting process log n times
    countingSort(k);  // actually radix sort: sort based on the second item
    countingSort(0);          // then (stable) sort based on the first item
    tmpRA[SA[0]] = r = 0;             // re-ranking; start from rank r = 0
    for (i = 1; i < n; i++)                    // compare adjacent suffixes
      tmpRA[SA[i]] = // if same pair => same rank r; otherwise, increase r
      (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
    for (i = 0; i < n; i++)                     // update the rank array RA
      RA[i] = tmpRA[i];
    if (RA[SA[n-1]] == n-1) break;               // nice optimization trick
  }
}

//ii stringMatch() {
//	int lo = 0, hi = n-1, mid = lo;
//	while(lo < hi) {
//		mid = lo + (hi - lo) /2;
//		int res = strncmp(T + SA[mid], P, m);
//		if (res >= 0) hi = mid;
//		else 	      lo = mid + 1;
//	}
//
//	if (strncmp(T + SA[mid], P, m) != 0) return ii(-1,-1);
//	ii res; res.first = mid;
//	lo = 0; hi = n-1; mid = lo;
//	while(lo < hi) {
//		mid = lo + (hi -lo) /2;
//		int res = strncmp(T + SA[mid], P, m);
//		if (res > 0) hi = mid;
//		else 	lo  = mid+1;
//	}
//	if (strncmp(T+ SA[mid], P, m) != 0 ) hi--;
//	res.second = hi;
//	return res;
//}

ii stringMatch() {                      // string matching in O(m log n)
  int lo = 0, hi = n-1, mid = lo;              // valid matching = [0..n-1]
  while (lo < hi) {                                     // find lower bound
    mid = (lo + hi) / 2;                              // this is round down
    int res = strncmp(T + SA[mid], P, m);  // try to find P in suffix 'mid'
    if (res >= 0) hi = mid;        // prune upper half (notice the >= sign)
    else          lo = mid + 1;           // prune lower half including mid
  }                                      // observe `=' in "res >= 0" above
  if (strncmp(T + SA[lo], P, m) != 0) return ii(-1, -1);    // if not found
  ii ans; ans.first = lo;
  lo = 0; hi = n - 1; mid = lo;
  while (lo < hi) {            // if lower bound is found, find upper bound
    mid = (lo + hi) / 2;
    int res = strncmp(T + SA[mid], P, m);
    if (res > 0) hi = mid;                              // prune upper half
    else         lo = mid + 1;            // prune lower half including mid
  }                           // (notice the selected branch when res == 0)
  if (strncmp(T + SA[hi], P, m) != 0) hi--;                 // special case
  ans.second = hi;
  return ans;
} // return lower/upperbound as first/second item of the pair, respectively


int main() {
	string input;
	cin >> input;
	input += '$';
	n = input.length();
	strcpy(T, input.c_str());
	cin >> input;
	m = input.length();
	strcpy(P, input.c_str());

	int i, k, r;
	for (i = 0; i < n; i++) {
		RA[i] = T[i];
		SA[i] = i;
	}

	r = 0;
	for (k = 1; k < n; k <<= 1) {
//		cout << "k = " << k << endl;
//		for (i = 0; i < n; i++) {
//			cout << SA[i] << " " << RA[SA[i]] << " " << ((i + k) < n ? RA[SA[i]+k] : 0) << "  " << T + SA[i] << endl;
//		}
//		cout << " ------------------ " << endl;
		countingSort(k);
//		for (i = 0; i < n; i++) {
//			cout << SA[i] << " " << RA[SA[i]] << " " << ((i + k) < n ? RA[SA[i]+k] : 0) << "  " << T + SA[i] << endl;
//		}
//		cout << "------------------ " << endl;
		countingSort(0);

		r = tmpRA[SA[0]] = 0;
		for (i = 1; i < n; i++) {
			tmpRA[SA[i]] =
			(RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
//			(RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
		}
		for(i = 0; i < n; i ++) {
			RA[i] = tmpRA[i];
		}
//		for (i = 0; i < n; i++) {
//			cout << SA[i] << " " << RA[SA[i]] << " " << ((i + k) < n ? RA[SA[i]+k] : 0) <<"  " << T + SA[i] << endl;
//		}
//		cout << "xxxxxxxxxxxxxxxxxxxx " << endl;
		if (RA[SA[n-1]] == n -1) {
			break;
		}
	}

//	constructSA();

	for (int i = 0; i < n; i++) {
		cout << SA[i] << "  " << T + SA[i] << endl;
	}
	ii res = stringMatch();
	cout << res.first << "  " << res.second << endl;

	return 0;
}
