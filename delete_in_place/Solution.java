import java.io.*;
import java.util.*;

/*
 * To execute Java, please define "static void main" on a class
 * named Solution.
 *
 * If you need more classes, simply define them inline.
 */

// deleting all occurrances from an array c++ style, using -1 to mark end of new array

class Solution {
  public static void main(String[] args) {
    int[] arr = {2,3,5,6,7,10,3,4,5,11,4,5,-5,0,-20,-45,-100,50};
    removeMultiplesOfFive(arr);
    for (int i : arr)
      System.out.print(i+",");
    System.out.println("");
  }
  
  public static void removeMultiplesOfFive(int[] arr) {
    int numDeleted = 0;
    for (int i=0; i<arr.length; i++) {
      if (arr[i]%5 == 0)
        numDeleted++;
      else
        swap(arr, i, i-numDeleted);
    }
    arr[arr.length-numDeleted] = -1;
  }
  
  public static void swap(int[] arr, int idx1, int idx2) {
    int temp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = temp;
  }
}
