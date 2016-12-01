package practice.cc;

import java.util.Set;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Iterator;

import practice.util.GraphNode;

public class BreadthFirstGraphSearch<V> implements GraphSearch<GraphNode<V>, V> {
	public boolean searchGraph(GraphNode<V> start, V val) {
		if (start == null)
			return false;

		Set<GraphNode<V>> visited = new HashSet<GraphNode<V>>();
		LinkedList<GraphNode<V>> searchQueue = new LinkedList<GraphNode<V>>();

		searchQueue.add(start);

		GraphNode<V> head;
		while ((head=searchQueue.poll()) != null) {
			if (head.content.equals(val))
				return true;

			visited.add(head);
			for (GraphNode<V> neighbor : head.neighbors) {
				if (!visited.contains(neighbor))
					searchQueue.add(neighbor);
			}
		}
		return false;
	}
}
