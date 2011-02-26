package ianfield.cs2g7;

import java.util.Comparator;

public class CustomComparator implements Comparator<Edge>{
	@Override
	public int compare(Edge e1, Edge e2) {
		return e1.get_cost() - e2.get_cost();
	}
}
