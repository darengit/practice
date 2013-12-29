import java.util.Random;

public class MaxSubArray {
	private static Random rand = new Random();

	private static int[] randomArray(int length, int min, int max) {
		int[] random = new int[length];
		for (int i=0; i<length-1; i++) {
			random[i] = rand.nextInt(max-min+1) + min;
		}
		return random;
	}

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

		int[] lengths = new int[] {10, 100, 1000, 10000, 100000};

		for (int length: lengths) {
			int[] random = randomArray(length, -999, 999);
			int brute = maxSubSum(random);
			int nlogn = maxSubSumNLogN(random);
			int linear = maxSubSumLinear(random);

			assert brute==nlogn && nlogn==linear;
		}

		System.out.println("all asserts passed");
	}

	private static int maxSubSum(int[] nums) {
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

	private static int maxSubSumNLogN(int[] nums) {
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

	private static int maxSubSumLinear(int[] nums) {
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
