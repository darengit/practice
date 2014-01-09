package practice.cc;

import java.util.ArrayList;

import practice.util.GraphNode;

public class GraphSearchTest {
	public static void main(String[] args) {
		GraphNode single = new GraphNode(new Integer(0));

		GraphNode zero  = new GraphNode(new Integer(0));
		GraphNode one   = new GraphNode(new Integer(1));
		GraphNode two   = new GraphNode(new Integer(2));
		GraphNode three = new GraphNode(new Integer(3));
		GraphNode four  = new GraphNode(new Integer(4));
		GraphNode five  = new GraphNode(new Integer(5));
		GraphNode six   = new GraphNode(new Integer(6));

		zero.neighbors.add(one);
		zero.neighbors.add(two);
		zero.neighbors.add(four);

		one.neighbors.add(zero);
		one.neighbors.add(three);

		two.neighbors.add(zero);
		two.neighbors.add(three);
		two.neighbors.add(four);

		three.neighbors.add(one);
		three.neighbors.add(two);
		three.neighbors.add(four);
		three.neighbors.add(five);

		four.neighbors.add(zero);
		four.neighbors.add(two);
		four.neighbors.add(three);

		five.neighbors.add(three);

		GraphSearch dfsSearch = new DepthFirstGraphSearch();

		assert !dfsSearch.searchGraph(null, null);

		assert dfsSearch.searchGraph(single, new Integer(0));
		assert !dfsSearch.searchGraph(single, new Integer(1));
		assert !dfsSearch.searchGraph(single, null);

		for (int i=0; i<6; i++) {
			assert dfsSearch.searchGraph(zero, new Integer(i));
			assert dfsSearch.searchGraph(three, new Integer(i));
			assert dfsSearch.searchGraph(five, new Integer(i));
			assert !dfsSearch.searchGraph(null, new Integer(i));
			assert !dfsSearch.searchGraph(one, null);
			assert !dfsSearch.searchGraph(six, new Integer(i));
			assert !dfsSearch.searchGraph(four, new Integer(6));
		}

		GraphSearch bfsSearch = new BreadthFirstGraphSearch();

		assert !bfsSearch.searchGraph(null, null);

		assert bfsSearch.searchGraph(single, new Integer(0));
		assert !bfsSearch.searchGraph(single, new Integer(1));
		assert !bfsSearch.searchGraph(single, null);

		for (int i=0; i<6; i++) {
			assert bfsSearch.searchGraph(zero, new Integer(i));
			assert bfsSearch.searchGraph(three, new Integer(i));
			assert bfsSearch.searchGraph(five, new Integer(i));
			assert !bfsSearch.searchGraph(null, new Integer(i));
			assert !bfsSearch.searchGraph(one, null);
			assert !bfsSearch.searchGraph(six, new Integer(i));
			assert !bfsSearch.searchGraph(four, new Integer(6));
		}
	}
}
