package ianfield.cs2g7;

import java.util.ArrayList;
import java.util.Collections;

public class Heap {
	/**
	 * Performs the insert method for the heap data structure
	 * @param a Edge list
	 * @param n 
	 * @return
	 */
	public ArrayList<Edge> insert(ArrayList<Edge> a, int n){
		int j = n-1, i = (n-1)/2;
		Edge data = a.get(n-1);
		// > for correct smallest to biggest
		while((i > 0) && (a.get(i).get_cost() > data.get_cost())){
			a.set(j, a.get(i));
			j = i;
			i /= 2;
		}
		//fix for programatic implementation
		if(a.get(0).get_cost() > data.get_cost()){
			Edge temp = a.get(0);
			a.set(0, data);
			a.set(1, temp);
		}
		else{
			a.set(j, data);
		}
		return a;
	}
	
	public ArrayList<Edge> heapify(ArrayList<Edge> a){
		ArrayList<Edge> heap = new ArrayList<Edge>();
		int size = a.size();
		heap.add(a.remove(0));
		for (int i = 1; i < size; i++ ){
			heap.add(a.remove(0));
			heap = insert(heap, heap.size());
		}
		return heap;
	}
	
	
	/**
	 * Performs fix heap algorithm
	 * @param a Edge List
	 * @param n Edge List size
	 * @param i
	 * @return
	 */
	public ArrayList<Edge> fixHeap(ArrayList<Edge> a, int n, int i){
		int j = 2*i;
		Edge data = a.get(i-1);
		while(j <= n){
			// > for correct smallest to biggest
			if(j<n && a.get(j) != null && a.get(j-1).get_cost() > a.get(j).get_cost())
				j++;
			if(data.get_cost() <= a.get(j-1).get_cost())
				break;
			else{
				a.set((j/2)-1, a.get(j-1));
				j *= 2;
			}
		}
		a.set((j/2) -1, data);	
		return a;
	}
	
	/**
	 * 
	 * @param a Edge List
	 * @param n Edge List Size
	 * @return
	 */
	public ArrayList<Edge> makeHeap(ArrayList<Edge> a, int n){
		for(int i = n/2; i > 0; i--){
			a = fixHeap(a, n, i);
		}
		return a;
	}
	
	/**
	 * Krushkal algorithm using a sorted list of edges
	 */
	public void Krushkal1(){
		Forrest forrest = new Forrest();
		forrest.initialiseForrest(6);
		
		System.out.println("Krushkal 1");
		ArrayList<Edge> edgeList = new ArrayList<Edge>();
		edgeList.add(new Edge(1,2,2));
		edgeList.add(new Edge(1,3,8));		
		edgeList.add(new Edge(1,4,6));
		edgeList.add(new Edge(2,3,2));
		edgeList.add(new Edge(2,4,6));	
		edgeList.add(new Edge(3,4,7));	
		edgeList.add(new Edge(3,5,4));
		edgeList.add(new Edge(3,6,4));
		edgeList.add(new Edge(4,5,9));
		edgeList.add(new Edge(4,6,3));	
		edgeList.add(new Edge(5,6,5));
		Collections.sort(edgeList, new CustomComparator());
		System.out.println(edgeList.toString());
		int i = 0, mincost = 0;
		int n = 6;
		
		ArrayList<Vertex> t = new ArrayList<Vertex>();
		while((i<n-1) &&(edgeList.size()>0)){
			Edge next = edgeList.remove(0);
			int u = next.get_u();
			int v = next.get_v();
			int j = forrest.findVertex(u);
			int k = forrest.findVertex(v);
			if(j!=k){
				i++;
				if(k != -1 && j !=-1){
					t.add(new Vertex(u, v));
					mincost += next.get_cost();
					forrest.mergeComponents(j, k);
				}
			}
		}
		if(i != n-1)
			System.out.println("No spanning tree");
		else
		{
			System.out.println("Minimum Spanning tree is:");
			System.out.println(t.toString());
			System.out.println("Minimum cost is: " + mincost);
		}
		System.out.println("End");
	}
	
	/**
	 * Krushkal 2 algorithm using a heap data structure, list of edges
	 */
	public void Krushkal2(){
		Forrest forrest = new Forrest();
		forrest.initialiseForrest(6);
		System.out.println("Krushkal 2");
		ArrayList<Edge> edgeList = new ArrayList<Edge>();
		edgeList.add(new Edge(1,2,2));
		edgeList.add(new Edge(1,3,8));		
		edgeList.add(new Edge(1,4,6));
		edgeList.add(new Edge(2,3,2));
		edgeList.add(new Edge(2,4,6));	
		edgeList.add(new Edge(3,4,7));
		edgeList.add(new Edge(3,5,4));
		edgeList.add(new Edge(3,6,4));	
		edgeList.add(new Edge(4,5,9));
		edgeList.add(new Edge(4,6,3));	
		edgeList.add(new Edge(5,6,5));
		edgeList = makeHeap(edgeList, edgeList.size()); 
		System.out.println(edgeList.toString());
		int i = 0, mincost = 0;
		int n = 6;

		ArrayList<Vertex> t = new ArrayList<Vertex>();
		while((i<n-1) &&(edgeList.size()>0)){
			Edge next = edgeList.remove(0);
			int u = next.get_u();
			int v = next.get_v();
			fixHeap(edgeList, edgeList.size(), 1);
			int j = forrest.findVertex(u);
			int k = forrest.findVertex(v);
			
			if(j!=k){
				i++;
				if(k != -1 && j !=-1){
					t.add(new Vertex(u, v));
					mincost += next.get_cost();
					forrest.mergeComponents(j, k);
				}
			}
		}
		if(i != n-1)
			System.out.println("No spanning tree");
		else
		{
			System.out.println("Minimum Spanning tree is:");
			System.out.println(t.toString());
			System.out.println("Minimum cost is: " + mincost);
		}
	}
	
	
	public static void main(String[] args){
		Heap heap = new Heap();
		heap.Krushkal1();// no heap used
		heap.Krushkal2();//bottom up used
	}
		
}
/*Original
Edge data = A.get(i);
while(j <= n){
	// > for correct smallest to biggest
	if(j<n && A.get(j).cost > A.get(j+1).cost){
		j++;
	}
	if(data.cost <= A.get(j).cost){
		break;
	}
	else{
		A.set(j/2, A.get(j));
		j *= 2;
	}
}
A.set(j/2, data);
return A;
*/


/*
edgeList.add(new Edge(1,2,2));
edgeList.add(new Edge(1,4,6));
edgeList.add(new Edge(2,4,6));
edgeList.add(new Edge(1,3,8));
edgeList.add(new Edge(2,3,2));
edgeList.add(new Edge(3,4,7));
edgeList.add(new Edge(3,5,4));
edgeList.add(new Edge(3,6,4));
edgeList.add(new Edge(4,6,3));
edgeList.add(new Edge(5,4,9));
edgeList.add(new Edge(5,6,5));
*/

/*
System.out.println("Insert");
ArrayList<Edge> edgeList = new ArrayList<Edge>();
edgeList.add(new Edge(1,2,2));
edgeList.add(new Edge(1,3,8));		
edgeList.add(new Edge(1,4,6));
edgeList.add(new Edge(2,3,2));
edgeList.add(new Edge(2,4,6));	
edgeList.add(new Edge(3,4,7));
edgeList.add(new Edge(3,5,4));
edgeList.add(new Edge(3,6,4));	
edgeList.add(new Edge(4,5,9));
edgeList.add(new Edge(4,6,3));	
edgeList.add(new Edge(5,6,5));
edgeList = heap.heapify(edgeList); //insertion method
System.out.println(edgeList.toString());
*/