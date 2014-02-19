package practice.cc;

import java.util.Set;
import java.util.HashSet;
import java.util.Stack;
import java.util.Iterator;

import practice.util.GraphNode;

public class DepthFirstGraphSearch<V> implements GraphSearch<GraphNode<V>, V> {
	public boolean searchGraph(GraphNode<V> start, V val) {
		if (start == null)
			return false;

		Set<GraphNode<V>> visited = new HashSet<GraphNode<V>>();
		Stack<GraphNode<V>> searchStack = new Stack<GraphNode<V>>();

		searchStack.push(start);

		while (!searchStack.isEmpty()) {
			GraphNode<V> top = searchStack.pop();

			if (top.content.equals(val))
				return true;

			visited.add(top);
			for (GraphNode<V> neighbor : top.neighbors) {
				if (!visited.contains(neighbor))
					searchStack.push(neighbor);
			}
		}
		return false;
	}
}
