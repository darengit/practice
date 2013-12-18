public class MaxSubArray {
	public static void main(String[] args) {
		assert maxSum(new int[] {}) == 0;
		System.out.println("all asserts passed");
	}

	private static int maxSum(int[] nums) {
		int maxSum = 0;
		for (int i=0; i<nums.length; i++)
			for (int j=i; j<nums.length; j++)
				maxSum = Math.max(maxSum, subSum(nums,i,j));
		return maxSum;  
  	}

	private static int subSum(int[] nums, int start, int end) {
		int subSum = 0;
		for (int i=start; i<=end; i++)
			subSum += nums[i];
		return subSum;
	}
}
