// 2 vs 3

// The fight for the best number in the globe is going to finally come to an end.The top two contenders for the best number are number 2 and number 3.It's the final the entire world was waiting for. Expectorates from all across the globe came to witness the breath taking finals.
// The finals began in an astonishing way.A common problem was set for both of them which included both these number.The problem goes like this.
// Given a binary string (that is a string consisting of only 0 and 1). They were supposed to perform two types of query on the string.

// Type 0: Given two indices l and r.Print the value of the binary string from l to r modulo 3.

// Type 1: Given an index l flip the value of that index if and only if the value at that index is 0.

// The problem proved to be a really tough one for both of them.Hours passed by but neither of them could solve the problem.So both of them wants you to solve this problem and then you get the right to choose the best number in the globe.
// Input:

// The first line contains N denoting the length of the binary string .
// The second line contains the N length binary string.Third line contains the integer Q indicating the number of queries to perform.
// This is followed up by Q lines where each line contains a query.

// Output:

// For each query of Type 0 print the value modulo 3.

// Constraints:

// 1<= N <=10^5

// 1<= Q <= 10^5

// 0 <= l <= r < N

// Sample Input

// 5
// 10010
// 6
// 0 2 4
// 0 2 3
// 1 1
// 0 0 4
// 1 1
// 0 0 3

// Sample Output

// 2
// 1
// 2
// 1



#include<bits/stdc++.h>
using namespace std;


int power[100001];

void buildPower(){
    power[0] = 1;
    for(int i = 1; i < 100001; i++) power[i] = (power[i-1]*2)%3;
}

void buildTree(int *ar, int *tree, int start, int end, int treeIndex) {

	if(start == end) {
		tree[treeIndex] = ar[start];
		return ;
	}

	int mid = (start + end)/2;

	buildTree(ar, tree, start, mid, 2*treeIndex);
	buildTree(ar, tree, mid + 1, end, 2*treeIndex + 1);

	tree[treeIndex] = ((tree[2*treeIndex] * power[end-mid]) + tree[2*treeIndex + 1])%3;
}

void updateTree(int *ar, int *tree, int start, int end, int treeIndex, int index) {

	if(start == end ) {
    	ar[index] = 1;
		tree[treeIndex] = 1;
		return;
	}

	int mid = (start + end)/2;

	if(index <= mid) {
		updateTree(ar, tree, start, mid, 2*treeIndex, index);
	}
	else {
		updateTree(ar, tree, mid + 1, end, 2*treeIndex + 1, index);
	}

	tree[treeIndex] = ((tree[2*treeIndex] * power[end-mid]) + tree[2*treeIndex + 1])%3;
}

int queryTree(int *tree, int start, int end, int treeIndex, int left, int right) {

	if(start > right || end < left) {
		return 0;
	}
	if(start >= left && end <= right) {
		return tree[treeIndex]*power[right-end]%3;
	}

	int mid = (start + end)/2;

	int ans1 = queryTree(tree, start, mid, 2*treeIndex, left, right);
	int ans2 = queryTree(tree, mid+1, end, 2*treeIndex + 1, left, right);

	int ans = (ans1+ans2)%3;

	return ans;
}
int main() {

	int n;
	cin >> n;

	string bstring;
	cin >> bstring;

	int *ar = new int[n];
	for(int i = 0; i < n; i++) {
		ar[i] = bstring[i] - '0';
	}

    buildPower();

	int *tree = new int[3*n];
	buildTree(ar, tree, 0, n-1, 1);

	int q;
	cin >> q;

	while(q--) {

		int query, left, right, index, ans;
		cin >> query;

		switch(query) {
			case 0 : cin >> left >> right;
					 ans = queryTree(tree, 0, n-1, 1, left, right);
					 cout << ans << endl;

					 break;
			case 1 : cin >> index;
					 updateTree(ar, tree, 0, n-1, 1, index);

					 break;
		}
	}


	delete [] ar;
	delete [] tree;

	return 0;
}