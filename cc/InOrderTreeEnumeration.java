package practice.cc;

import java.util.Enumeration;
import java.util.NoSuchElementException;
import java.util.Stack;

import practice.util.TreeNode;

public class InOrderTreeEnumeration implements Enumeration<TreeNode> {
	private Stack<TreeNode> enumStack;

	public InOrderTreeEnumeration(TreeNode root) {
		enumStack = new Stack<TreeNode>();
		TreeNode curr = root;
		while (curr != null) {
			enumStack.push(curr);
			curr = curr.left;
		}	
	}

	public boolean hasMoreElements() {
		return !enumStack.empty();
	}

	public TreeNode nextElement() {
		if (enumStack.empty())
			throw new NoSuchElementException();

		TreeNode next = enumStack.pop();

		if (next.right != null) {
			TreeNode curr = next.right;
			while (curr != null) {
				enumStack.push(curr);
				curr = curr.left;
			}
		}

		return next;
	}
}
