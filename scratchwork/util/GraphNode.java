package practice.util;

import java.util.ArrayList;

public class GraphNode<T> {
	public T content;
	public ArrayList<GraphNode<T>> neighbors;
	
	public GraphNode(T content) {
		this.content = content;
		this.neighbors = new ArrayList<GraphNode<T>>();
	}
}
