package practice.cc;

import java.util.Enumeration;
import java.util.NoSuchElementException;
import java.util.Stack;
import practice.util.TreeNode;

public class PreOrderTreeEnumeration implements Enumeration<TreeNode> {
	private Stack<TreeNode> enumStack;

	public PreOrderTreeEnumeration(TreeNode root) {
		enumStack = new Stack<TreeNode>();
		if (root != null)
			enumStack.push(root);
	}

	public boolean hasMoreElements() {
		return !enumStack.empty();
	}

	public TreeNode nextElement() {
		if (enumStack.empty())
			throw new NoSuchElementException();

		TreeNode next = enumStack.pop();

		if (next.right != null)
			enumStack.push(next.right);
		if (next.left != null)
			enumStack.push(next.left);

		return next;
	}
}
