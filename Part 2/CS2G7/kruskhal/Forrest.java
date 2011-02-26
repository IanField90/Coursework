package ianfield.cs2g7;

import java.util.ArrayList;

public class Forrest {
	public ArrayList<ArrayList<Integer>> forrest = new ArrayList<ArrayList<Integer>>();

	//initialise component i with vertex i.
	public void initialiseForrest(int n){
		forrest.add(new ArrayList<Integer>());
		//0 blank so n = n not n-1
		for(int i = 1; i <= n; i++){
			ArrayList<Integer> element = new ArrayList<Integer>();
			element.add(i);
			forrest.add(element);
		}
	}
	
	//search the Forest looking for vertex Ð return the component number
	//where vertex is found. Otherwise return -1 as error case.
	public int findVertex(int v){
		int componentNumber = -1;
		//start at 1 as 0 is empty for simplicity
		for(int i = 1; i < forrest.size(); i++){
			for (int j = 0; j < forrest.get(i).size(); j++){
				if(forrest.get(i).get(j) == v){
					componentNumber = i;
					break;
				}
			}
		}
		return componentNumber;
	}
	
	//merge the components c1 and c2 of the forest (see lecture notes on how the merge happens)
	public void mergeComponents(int c1, int c2){
		forrest.get(c1).add(c2);
		forrest.set(c2, new ArrayList<Integer>());
	}
}
