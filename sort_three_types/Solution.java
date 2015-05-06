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
        sortThreeTypes(test1);
        for (int num : test1)
            System.out.print(num);
        System.out.println("");
      
    }

    public static void sortThreeTypes(int[] arr) {
        int head = 0;
        int tail = arr.length-1;
      
        boolean doneFromHead = false;
        boolean doneFromTail = false;
      
        while (head < tail && !doneFromHead && !doneFromTail) {
            System.out.println(head);
            System.out.println(tail);
            for (int num: arr)
              System.out.print(num);
            System.out.println("");
            if (arr[head] == 0)
                head++;
            if (arr[tail] == 2)
                tail--;
          
            if (arr[head] == 1 && !doneFromHead) {
                int idx = head;
                while(++idx < tail) {
                    if (arr[idx] == 0) {
                        swap(arr, idx, head++);
                        break;
                    }
                }
                if (idx >= tail) {
                    doneFromHead = true;
                }
            }
          
            if (arr[tail] == 1 && !doneFromTail) {
                int idx = tail;
                while(head <= --idx) {
                    if (arr[idx] == 2) {
                        swap(arr, idx, tail--);
                        break;
                    }
                }
                if (idx <= head) {
                    doneFromTail = true;
                }
            }
          
            if ((arr[head] == 2 && arr[tail] == 0) ||
                (arr[head] == 1 && arr[tail] == 0) ||
                (arr[head] == 2 && arr[tail] == 1))
                swap(arr, head++, tail--);
        }
      
    }
  
    public static void swap(int[] arr, int idx1, int idx2) {
        int temp = arr[idx1];  
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
}

