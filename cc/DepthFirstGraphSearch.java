import java.util.Set;
import java.util.HashSet;
import java.util.Stack;
import java.util.Iterator;

import practice.util.GraphNode;

public class DepthFirstGraphSearch<V> implements GraphSearch<GraphNode, V> {
	public boolean searchGraph(GraphNode start, V val) {
		if (start == null)
			return false;

		Set visited = new HashSet();
		Stack<GraphNode> searchStack = new Stack<GraphNode>();

		searchStack.push(start);

		while (!searchStack.isEmpty()) {
			GraphNode top = searchStack.pop();

			if (top.content.equals(val))
				return true;

			visited.add(top);
			Iterator<GraphNode> neighborsIter = top.neighbors.iterator();
			while (neighborsIter.hasNext()) {
				GraphNode nextNeighbor = neighborsIter.next();
				if (!visited.contains(nextNeighbor))
					searchStack.push(nextNeighbor);
			}	
		}
		return false;
	}
}
