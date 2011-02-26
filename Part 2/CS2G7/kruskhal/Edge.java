package ianfield.cs2g7;

public class Edge {
	private int u, v, cost;
    
	public int get_u(){
		return u;
	}
	
	public int get_v(){
		return v;
	}
	
	public int get_cost(){
		return cost;
	}

	Edge(int u, int v, int cost)
    {
        this.u = u;
        this.v = v;
        this.cost = cost;
    }
	
	public String toString(){
		//return "((" + u + ", " + v +"), " + cost + ")";
		return ""+ cost;
	}
}
