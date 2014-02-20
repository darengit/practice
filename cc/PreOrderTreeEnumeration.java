package practice.cc;

import java.util.Enumeration;
import java.util.NoSuchElementException;
import java.util.Stack;
import practice.util.TreeNode;

public class PreOrderTreeEnumeration<T> implements Enumeration<T> {
	private Stack<TreeNode<T>> enumStack;

	public PreOrderTreeEnumeration(TreeNode<T> root) {
		enumStack = new Stack<TreeNode<T>>();
		if (root != null)
			enumStack.push(root);
	}

	public boolean hasMoreElements() {
		return !enumStack.empty();
	}

	public T nextElement() {
		if (enumStack.empty())
			throw new NoSuchElementException();

		TreeNode<T> next = enumStack.pop();

		if (next.right != null)
			enumStack.push(next.right);
		if (next.left != null)
			enumStack.push(next.left);

		return next.content;
	}
}
