package practice.cc;

import java.util.Enumeration;
import java.util.NoSuchElementException;
import java.util.Stack;
import practice.util.TreeNode;

/*
 * out of the traversals this one is particularly tricky
 */

public class PostOrderTreeEnumeration<T> implements Enumeration<T> {
	private Stack<TreeNode<T>> enumStack;

	public PostOrderTreeEnumeration(TreeNode<T> root) {
		enumStack = new Stack<TreeNode<T>>();
		initializeTreeToStack(root);
	}

	private void initializeTreeToStack(TreeNode<T> n) {
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

	public T nextElement() {
		if (enumStack.empty())
			throw new NoSuchElementException();

		TreeNode<T> next = enumStack.pop();
		if (enumStack.empty())
			return next.content;
		TreeNode<T> nextNext = enumStack.peek();

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

		return next.content;
	}
}
