public class MaxSubArray {
	public static void main(String[] args) {
		assert maxSubSum(new int[] {}) == 0;
		assert maxSubSum(new int[] {-1,1,-2,2,-3,3,4,-5,6,-7}) == 8;
		assert maxSubSum(new int[] {-5,-1,-4,-2,-3}) == 0;

		assert maxSubSumNLogN(new int[] {}) == 0;
		assert maxSubSumNLogN(new int[] {-1,1,-2,2,-3,3,4,-5,6,-7}) == 8;
		assert maxSubSumNLogN(new int[] {-5,-1,-4,-2,-3}) == 0;		

		assert maxSubSumLinear(new int[] {}) == 0;
		assert maxSubSumLinear(new int[] {-1,1,-2,2,-3,3,4,-5,6,-7}) == 8;
		assert maxSubSumLinear(new int[] {-5,-1,-4,-2,-3}) == 0;

		int[] lengths = new int[] {1000, 10000, 100000, 200000};

		for (int length: lengths) {
			int[] random = RandomArray.randomArray(length, -999999, 999999);
			long start = System.currentTimeMillis();
			int brute = maxSubSum(random);
			long bruteFinish = System.currentTimeMillis();
			int nlogn = maxSubSumNLogN(random);
			long nlognFinish = System.currentTimeMillis();
			int linear = maxSubSumLinear(random);
			long linearFinish = System.currentTimeMillis();

			System.out.println("Array size: " + String.valueOf(length));
			System.out.println("Brute  : " + String.valueOf(bruteFinish-start) + "ms");
			System.out.println("NLogN  : " + String.valueOf(nlognFinish-bruteFinish) + "ms");
			System.out.println("Linear : " + String.valueOf(linearFinish-nlognFinish) + "ms");
			
			assert brute==nlogn && nlogn==linear;
		}

		System.out.println("all asserts passed");
	}

	public static int maxSubSum(int[] nums) {
		int maxSubSum = 0;
		for (int i=0; i<nums.length; i++) {
			int iStartMax = 0;
			for (int j=i; j<nums.length; j++) {
				iStartMax += nums[j];
				maxSubSum = Math.max(maxSubSum, iStartMax);
			}
		}
		return maxSubSum;  
  	}

	public static int maxSubSumNLogN(int[] nums) {
		if (nums.length == 0)
			return 0;
		return maxSubSum(nums, 0, nums.length-1);
	}

	private static int maxSubSum(int[] nums, int start, int end) {
		if (start == end)
			return nums[start];

/*
 * (middle+1 <= end) should always be the case
 */
		int middle = (start+end)/2;
		int maxSubSum = Math.max(maxSubSum(nums, start, middle), maxSubSum(nums, middle+1, end));
		return Math.max(maxSubSum, maxSubSumRight(nums, start, middle) + maxSubSumLeft(nums, middle+1, end));
	}

	private static int maxSubSumRight(int[] nums, int start, int end) {
		int sum = 0;
		int maxSubSum = 0;
		for (int i=end; i>=start; i--) {
			sum += nums[i];
			maxSubSum = Math.max(maxSubSum, sum);
		}
		return maxSubSum;
	}

	private static int maxSubSumLeft(int[] nums, int start, int end) {
        int sum = 0;
        int maxSubSum = 0;
        for (int i=start; i<=end; i++) {
            sum += nums[i];
            maxSubSum = Math.max(maxSubSum, sum);
        }
		return maxSubSum;
	}

	public static int maxSubSumLinear(int[] nums) {
		int minFromLeft = 0;
		int sumFromLeft = 0;
		int maxSoFar = 0;

		for (int i: nums) {
			sumFromLeft += i;
			minFromLeft = Math.min(minFromLeft, sumFromLeft);
			maxSoFar = Math.max(maxSoFar, sumFromLeft - minFromLeft);
		}

		return maxSoFar;
	}
}
