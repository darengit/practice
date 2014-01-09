package practice.cc;

import java.util.Set;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Iterator;

import practice.util.GraphNode;

public class BreadthFirstGraphSearch<V> implements GraphSearch<GraphNode, V> {
	public boolean searchGraph(GraphNode start, V val) {
		if (start == null)
			return false;

		Set visited = new HashSet();
		LinkedList<GraphNode> searchQueue = new LinkedList<GraphNode>();

		searchQueue.add(start);

		GraphNode head;
		while ((head=searchQueue.poll()) != null) {
			if (head.content.equals(val))
				return true;

			visited.add(head);
			Iterator<GraphNode> neighborsIter = head.neighbors.iterator();
			while (neighborsIter.hasNext()) {
				GraphNode nextNeighbor = neighborsIter.next();
				if (!visited.contains(nextNeighbor))
					searchQueue.add(nextNeighbor);
			}	
		}
		return false;
	}
}
