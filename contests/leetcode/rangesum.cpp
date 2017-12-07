#include <vector>
#include <stdio.h>

class NumArray {
public:
	NumArray *left;
	NumArray *right;
	int leftIdx;
	int rightIdx;
	int sum;

	NumArray(std::vector<int> &nums, int left, int right):leftIdx(left),rightIdx(right) {
printf("%d %d\n", left, right);

		if(left>right) return;
		if(left==right) {
			this->left = NULL;
			this->right = NULL;
			sum = nums[left];
		} else {
			int divide = (left+right)/2;
			this->left = new NumArray(nums,left,divide);
			this->right = new NumArray(nums,divide+1,right);
			sum = this->left->sum + this->right->sum;
		}
	}

	NumArray(std::vector<int> &nums):NumArray(nums,0,nums.size()-1){}

	int sumRange(int i, int j) {
printf("sumrange: %d %d\n", i, j);
		if(i>j) return 0;

		if(i==leftIdx && j==rightIdx) return sum;

		int divide = (leftIdx+rightIdx)/2;

		if(j<=divide)
			return this->left->sumRange(i,j);
		else if (i>divide)
			return this->right->sumRange(i,j);
		else
			return this->left->sumRange(i,divide)+this->right->sumRange(divide+1,j);
	}
};

int main() {
	std::vector<int> test {-2,0,3,-5,2,-1};
	NumArray numArray(test);
printf("here %d %d %d %d\n", test.size(), numArray.leftIdx, numArray.rightIdx, numArray.sum);
	printf("%d\n", numArray.sumRange(0,2));
	printf("%d\n", numArray.sumRange(2,5));
	printf("%d\n", numArray.sumRange(0,5));
}
