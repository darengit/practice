/**
 * Definition for binary tree
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */

public class BSTIterator {
    private BSTIterator rightIter;
    private BSTIterator leftIter;
    private TreeNode rootIterItem;

    public BSTIterator(TreeNode root) {
        rootIterItem = root;
        if (root != null) {
            rightIter = new BSTIterator(root.right);
            leftIter = new BSTIterator(root.left); 
	}	
    }

    /** @return whether we have a next smallest number */
    public boolean hasNext() {
	if (rootIterItem == null && rightIter == null && leftIter == null) {
            return false;
        }

        return ((rightIter != null && rightIter.hasNext()) ||
                rootIterItem != null ||
                (leftIter != null && leftIter.hasNext()));
    }

    /** @return the next smallest number */
    public int next() {
        if (leftIter != null && leftIter.hasNext()) {
            return leftIter.next();
        }

        if (rootIterItem != null) {
            int retVal = rootIterItem.val;
            rootIterItem = null;
            return retVal;
        }

        if (rightIter != null && rightIter.hasNext()) {
            return rightIter.next();
        }

        return 0;
    }

    private static class TreeNode {
       int val;
       TreeNode left;
       TreeNode right;
       TreeNode(int x) { val = x; }
    }

    public static void main(String[] args) {
        TreeNode one = new TreeNode(1);
        TreeNode two = new TreeNode(2);
        one.right = two;

        BSTIterator Iter = new BSTIterator(one);
        while (Iter.hasNext()) {
            System.out.println(Iter.next());
        }
    }
}
