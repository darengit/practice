package practice.cc;

import java.util.Enumeration;
import java.util.NoSuchElementException;
import java.util.Stack;
import practice.util.TreeNode;

/*
 * out of the traversals this one is particularly tricky
 */

public class PostOrderTreeEnumeration implements Enumeration<TreeNode> {
	private Stack<TreeNode> enumStack;

	public PostOrderTreeEnumeration(TreeNode root) {
		enumStack = new Stack<TreeNode>();
		initializeTreeToStack(root);
	}

	private void initializeTreeToStack(TreeNode n) {
		while (n != null) {
			enumStack.push(n);
			if (n.left != null)
				n = n.left;
			else if (n.right != null) 
				n = n.right;
			else
				n = null;
		}
	}

	public boolean hasMoreElements() {
		return !enumStack.empty();
	}

	public TreeNode nextElement() {
		if (enumStack.empty())
			throw new NoSuchElementException();

		TreeNode next = enumStack.pop();
		if (enumStack.empty())
			return next;
		TreeNode nextNext = enumStack.peek();

/* 
 * two possibilities
 * nextNext.left = next, we have to process right subtree before getting to nextNext
 *   processing right subtree is not very straight forward
 *   i think we have to push onto the stack the whole path to the next node
 * nextNext.right = next, we are done with both subtrees and nextNext is next
 */
		if (nextNext.left == next) {
			initializeTreeToStack(nextNext.right);
		}

		return next;
	}
}
