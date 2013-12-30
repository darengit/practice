import java.util.Arrays;
import java.util.Random;

public class Sorting {
	private static boolean sorted(int[] nums) {
		for (int i=1; i<nums.length; i++) {
			if (nums[i] < nums[i-1]) {
				return false;
			}
		}
		return true;
	}

	public static void main(String[] args) {
		insertionSort(new int[] {});
		insertionSort(new int[] {0});

		heapSort(new int[] {});
		heapSort(new int[] {0});

		quickSort(new int[] {});
		quickSort(new int[] {0});

		quickSortDups(new int[] {});
		quickSortDups(new int[] {0});

		for (int length: new int[] {1000, 10000, 100000, 200000}) {
			int[] toInsertionSort = RandomArray.randomArray(length, -99, 99);
			int[] toHeapSort = Arrays.copyOf(toInsertionSort, length);
			int[] toQuickSort = Arrays.copyOf(toInsertionSort, length);
			int[] toQuickSortDups = Arrays.copyOf(toInsertionSort, length);

			System.out.println("Array length: " + String.valueOf(length));

			long start;
			long finish;

			start = System.currentTimeMillis();
			insertionSort(toInsertionSort);
			finish = System.currentTimeMillis();
			System.out.println("Insertion : " + String.valueOf(finish-start) + "ms");
			assert sorted(toInsertionSort);

			start = System.currentTimeMillis();
			heapSort(toHeapSort);
			finish = System.currentTimeMillis();
			System.out.println("Heap      : " + String.valueOf(finish-start) + "ms");
			assert sorted(toHeapSort);

			start = System.currentTimeMillis();
			quickSort(toQuickSort);
			finish = System.currentTimeMillis();
			System.out.println("Quick     : " + String.valueOf(finish-start) + "ms");
			assert sorted(toQuickSort);

			start = System.currentTimeMillis();
			quickSortDups(toQuickSortDups);
			finish = System.currentTimeMillis();
			System.out.println("QuickDups : " + String.valueOf(finish-start) + "ms");
			assert sorted(toQuickSortDups);
		}

		System.out.println("all asserts passed");
	}

	public static void insertionSort(int[] nums) {
		for (int i=1; i<nums.length; i++) {
			int j=-1;
			while (nums[++j]<nums[i]);
			int insert = nums[i];
			for (int shift=i; shift>j; shift--) {
				nums[shift] = nums[shift-1];
			}
			nums[j] = insert;
		}
	}

	public static void heapSort(int[] nums) {
		heapCreate(nums);

		for (int i=nums.length-1; i>0; i--) {
			int tmp = nums[i];
			nums[i] = nums[0];
			nums[0] = tmp;

			heapPropagateNode(nums, i, 0);
		}
	}

	private static void heapCreate(int[] nums) {
		for (int i=nums.length/2; i>=0; i--) {
			heapPropagateNode(nums, nums.length, i);
		}
	}

	private static void heapPropagateNode(int[] nums, int length, int index) {
		int leftChildIndex = index*2+1;
		int rightChildIndex = index*2+2;

/*
 * if (node is leaf) { ... }
 * else if (node has only left child) { ... }
 * else if (node has two children) { ... }
 */
		if (leftChildIndex>length-1 && rightChildIndex>length-1) {
			return;
		} else if (rightChildIndex > length-1) {
			heapTestSwapPropagate(nums, length, index, leftChildIndex);
		} else {
			int node = nums[index];
			int left = nums[leftChildIndex];
			int right = nums[rightChildIndex];

			if (left > right) {
				heapTestSwapPropagate(nums, length, index, leftChildIndex);
			} else {
				heapTestSwapPropagate(nums, length, index, rightChildIndex);
			}
		}
	}

	private static void heapTestSwapPropagate(int[] nums, int length, int parent, int child) {
		if (nums[parent] < nums[child]) {
			int tmp = nums[parent];
			nums[parent] = nums[child];
			nums[child] = tmp;

			heapPropagateNode(nums, length, child);
		} else {
			return;
		}
	}

	public static void quickSort(int[] nums) {
		quickSort(nums, 0, nums.length-1);	
	}

	private static void quickSort(int[] nums, int start, int end) {
		if (end <= start) {
			return;
		}

		Random rand = new Random(System.currentTimeMillis());
		int randomIndex = rand.nextInt(end-start+1) + start;

		int tmp = nums[randomIndex];
		nums[randomIndex] = nums[end];
		nums[end] = tmp;

/*
 * we will iterate over nums[start:end] and modify nums
 * nums[start:ltpIndex] are values 'less than pivot' or ltp for short
 * nums[ltpIndex+1:index-1] are values greater than or equal to pivot
 */
		int ltpIndex = start-1;
		int index = start;

		while (index < end) {
			if (nums[index] < nums[end]) {
				ltpIndex++;
				int indexValue = nums[index];
				nums[index] = nums[ltpIndex];
				nums[ltpIndex] = indexValue;
			}
			index++;
		}

		int pivotIndex = ltpIndex+1;
		int pivotIndexValue = nums[pivotIndex];
		nums[pivotIndex] = nums[end];
		nums[end] = pivotIndexValue;

		quickSort(nums, start, ltpIndex);
		quickSort(nums, pivotIndex+1, end);
	}

	public static void quickSortDups(int[] nums) {
		quickSortDups(nums, 0, nums.length-1);
	}

    private static void quickSortDups(int[] nums, int start, int end) {
        if (end <= start) {
            return;
        }

        Random rand = new Random(System.currentTimeMillis());
        int randomIndex = rand.nextInt(end-start+1) + start;

        int tmp = nums[randomIndex];
        nums[randomIndex] = nums[end];
        nums[end] = tmp;

/*
 * we will iterate over nums[start:end] and modify nums
 * nums[start:ltpIndex] are values 'less than pivot' or ltp for short
 * nums[ltpIndex+1:etpIndex] are values 'equal to pivot' or etp for short
 * nums[etpIndex+1:index-1] are values 'greater than pivot'
 */
        int ltpIndex = start-1;
		int etpIndex = start-1;
        int index = start;

        while (index < end) {
            if (nums[index] < nums[end]) {
                ltpIndex++;
				etpIndex++;
                int indexValue = nums[index];
                nums[index] = nums[ltpIndex];
                nums[ltpIndex] = indexValue;
				if (nums[index] == nums[end]) {
					int etpValue = nums[etpIndex];
					nums[etpIndex] = nums[index];
					nums[index] = etpValue;
				}
            } else if (nums[index] == nums[end]) {
				etpIndex++;
				int etpValue = nums[etpIndex];
				nums[etpIndex] = nums[index];
				nums[index] = etpValue;
			}
            index++;
        }

        int pivotIndex = etpIndex+1;
        int pivotIndexValue = nums[pivotIndex];
        nums[pivotIndex] = nums[end];
        nums[end] = pivotIndexValue;

        quickSort(nums, start, ltpIndex);
        quickSort(nums, pivotIndex+1, end);
    }
}
