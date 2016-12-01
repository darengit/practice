package practice.cc;

import java.util.ArrayList;

import practice.util.GraphNode;

public class GraphSearchTest {
	public static void main(String[] args) {
		GraphNode<Integer> single = new GraphNode<Integer>(new Integer(0));

		GraphNode<Integer> zero  = new GraphNode<Integer>(new Integer(0));
		GraphNode<Integer> one   = new GraphNode<Integer>(new Integer(1));
		GraphNode<Integer> two   = new GraphNode<Integer>(new Integer(2));
		GraphNode<Integer> three = new GraphNode<Integer>(new Integer(3));
		GraphNode<Integer> four  = new GraphNode<Integer>(new Integer(4));
		GraphNode<Integer> five  = new GraphNode<Integer>(new Integer(5));
		GraphNode<Integer> six   = new GraphNode<Integer>(new Integer(6));

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

		GraphSearch<GraphNode<Integer>,Integer> dfsSearch = new DepthFirstGraphSearch<Integer>();

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

		GraphSearch<GraphNode<Integer>,Integer> bfsSearch = new BreadthFirstGraphSearch<Integer>();

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
