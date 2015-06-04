import java.io.*;
import java.util.*;

/*
 * To execute Java, please define "static void main" on a class
 * named Solution.
 *
 * If you need more classes, simply define them inline.
 */

class Solution {
    public static void main(String[] args) {
        int[] test1 = {0,1,2,0,1,2,2,0,0,2,1,1,0};
        sortColors(test1);
        for (int num : test1)
            System.out.print(num);
        System.out.println("");
      
    }

    public static void sortColors(int[] nums) {
        if (nums.length < 2)
            return;

        int left = 0;
        int middle = left;
        int right = nums.length-1;

        while (middle <= right) {
            System.out.println(left + " " + middle + " " + right + " ");
        for (int num : nums)
            System.out.print(num);
        System.out.println("");

            if (middle == left) {
                if (nums[right] == 0) {
                    swap(nums, left, right);
                    left++;
                    middle++;
                } else if (nums[right] == 1) {
                    swap(nums, middle, right);
                    middle++;
                    right--;
                }
                while (right>=0 && nums[right]==2) {
                        right--;
                }
            } else {
                if (nums[right] == 0) {
                    swap(nums, left, right);
                    left++;
                } else if (nums[right] == 1) {
                    swap(nums, middle, right);
                    middle++;
                }
                while (right>=0 && nums[right]==2) {
                        right--;
                }
            }
        }
/*            
        int left = 0; // right of all 0's
        while (left<nums.length && nums[left] == 0)
            left++;
        
        if (left >= nums.length)
            return;
        
        int middle = left; // right of all 0's followed by 1's
        while (middle<nums.length && nums[middle] == 1)
            middle++;
        
        int right = nums.length-1; // left of all 2's
        while (right>=0 && nums[right] == 2)
            right--;
       
        int j = 0;
 
        while(middle < right) {
            j++;
            if (j>nums.length) return;
            System.out.println(left + " " + middle + " " + right + " ");
        for (int num : nums)
            System.out.print(num);
        System.out.println("");
            if (nums[left] == 1) { // middle is not in the same position as left
                if (nums[middle] == 0) {
                    swap(nums, left, middle);
                    left++;
                    middle++;
                } else { // nums[middle] == 2
                    swap(nums, middle, right);
                    right--;
                    if (nums[middle] == 1)
                        middle++;
                }
            } else { // middle is in the same position as left, nums[middle] == 2
                swap(nums, middle, right);
                middle++;
                right--;
                if (nums[left] == 0) 
                    left++;
            }
            
        }
*/

    }
    
    public static void swap(int[] nums, int idx1, int idx2) {
        int temp = nums[idx1];
        nums[idx1] = nums[idx2];
        nums[idx2] = temp;
    }
}

