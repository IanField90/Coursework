package ianfield.cs2g7;

public class Vertex {

	private int v, u;
	
	public int get_v(){
		return v;
	}
	
	public int get_u(){
		return u;
	}
	
	Vertex(int u, int v){
		this.u = u;
		this.v = v;
	}
	
	public String toString(){
		return "(" + u + ", " + v + ")";
	}
}
