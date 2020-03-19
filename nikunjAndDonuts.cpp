// Nikunj and Donuts
// Send Feedback
// Nikunj loves donuts, but he also likes to stay fit. He eats n donuts in one sitting, and each donut has a calorie count, ci. After eating a donut with k calories, he must walk at least 2^j x k(where j is the number donuts he has already eaten) miles to maintain his weight.
// Given the individual calorie counts for each of the n donuts, find and print a long integer denoting the minimum number of miles Nikunj must walk to maintain his weight. Note that he can eat the donuts in any order.
// Input

// The first line contains an integer, n, denoting the number of donuts. 
// The second line contains n space-separated integers describing the respective calorie counts of each donut I, i.e ci.

// Output

// Print a long integer denoting the minimum number of miles Nikunj must walk to maintain his weight.

// Constraints
// 1 ≤ n ≤ 40
// 1 ≤ ci ≤ 1000
// Sample Input

// 3
// 1 3 2

// Sample Output

// 11



#include<bits/stdc++.h>
using namespace std;

long getMinMiles(int *cal, int n){

	sort(cal, cal+n, greater<int>());
	
	long minMiles = 0;
	for(int i = 0; i < n; i++) {
		minMiles += cal[i] * (1 << i);
	}

	return minMiles;
}

int main() {

	int n;
	cin >> n;
	int *cal = new int[n];
	for(int i = 0; i < n; i++) {
		cin >> cal[i];
	}

	long ans = getMinMiles(cal, n);
	cout << ans << endl;

	delete [] cal;

	return 0;
}