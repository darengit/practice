package practice.cc;

import java.util.Enumeration;
import java.util.NoSuchElementException;
import java.util.Stack;

import practice.util.TreeNode;

public class InOrderTreeEnumeration<T> implements Enumeration<T> {
	private Stack<TreeNode<T>> enumStack;

	public InOrderTreeEnumeration(TreeNode<T> root) {
		enumStack = new Stack<TreeNode<T>>();
		TreeNode<T> curr = root;
		while (curr != null) {
			enumStack.push(curr);
			curr = curr.left;
		}	
	}

	public boolean hasMoreElements() {
		return !enumStack.empty();
	}

	public T nextElement() {
		if (enumStack.empty())
			throw new NoSuchElementException();

		TreeNode<T> next = enumStack.pop();

		if (next.right != null) {
			TreeNode<T> curr = next.right;
			while (curr != null) {
				enumStack.push(curr);
				curr = curr.left;
			}
		}

		return next.content;
	}
}
