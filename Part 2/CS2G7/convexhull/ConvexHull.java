package cs2g7.convexhull;

import java.util.ArrayList;
/**
 * @author Ian Field
 */
public class ConvexHull {
	private static ArrayList<Coordinate> hull, topPath, bottomPath;
	private static double topPathLength, bottomPathLength;
	static{
		hull = new ArrayList<Coordinate>();
		topPath = new ArrayList<Coordinate>();
		bottomPath = new ArrayList<Coordinate>();
		topPathLength = 0;
		bottomPathLength = 0;
	}
	
	/**
	 * @param points
	 * @return -ve if Right turn, +ve if Left turn, 0 if Co-linear
	 */
	public static int turnCheck(ArrayList<Coordinate> points){
		int Ax, Ay, Bx, By, Cx, Cy;
		int pointsSize = points.size();
		
		Ax = points.get(pointsSize-3).get_x();
		Ay = points.get(pointsSize-3).get_y();
		Bx = points.get(pointsSize-2).get_x();
		By = points.get(pointsSize-2).get_y();
		Cx = points.get(pointsSize-1).get_x();
		Cy = points.get(pointsSize-1).get_y();
		return ((Bx - Ax)*(Cy - Ay)) - ((By -Ay)*(Cx - Ax));
	}
		
	/**
	 * @param P
	 * @return Points comprising the Upper Hull
	 */
	public static ArrayList<Coordinate> UpperHull(ArrayList<Coordinate> P){
		ArrayList<Coordinate> LUpper = new ArrayList<Coordinate>();
		int n = P.size()-1;
		// Put the points P[1] and P[2] into a list Lupper 
		LUpper.add(P.get(0));
		LUpper.add(P.get(1));
		
		for(int i = 3; i <= n; i++){
			//	add P[i] to Lupper; 
			LUpper.add(P.get(i));
			//  while Lupper contains more than two points AND the last three points do not make a right turn
			while(LUpper.size() > 2 && turnCheck(LUpper) >= 0){
				LUpper.remove(LUpper.size()-2);
			}
		}
		return LUpper;
	}
	
	/**
	 * @param P
	 * @return Points comprising the Lower Hull
	 */
	public static ArrayList<Coordinate> LowerHull(ArrayList<Coordinate> P){
		ArrayList<Coordinate> LLower = new ArrayList<Coordinate>();
		int n = P.size()-1;
		//Put P[n] and P[n-1] in a list Llower with P[n] as the first point
		LLower.add(P.get(n));
		LLower.add(P.get(n-1));
		
		for(int i = n-2; i >= 1; i--){
			//  add P[i] to Llower;
			LLower.add(P.get(i));
			//	while Llower contains more than two points AND the last three points do not make a right turn
			while(LLower.size() > 2 && turnCheck(LLower) >= 0){
				LLower.remove(LLower.size()-2);
			}
		}
		return LLower;
	}
	
	/**
	 * @param list
	 * @return sorted by X-coordinate
	 */
	public static ArrayList<Coordinate> sortList(ArrayList<Coordinate> list){
		//Bubble Sort
		Coordinate temp = null;
		
		//if .size() then 1 wasted loop
		for(int i = 0; i < list.size()-1; i++){
			//size()-1 prevents out of bounds exception
			for(int j = 0; j < list.size()-1; j++){
				// Check if it's greater
				if(list.get(j).get_x() > list.get(j+1).get_x()){
					//do swap
					temp = list.get(j);
					list.set(j, list.get(j+1));
					list.set(j+1, temp);
				}
			}
		}	
		return list;
	}
	
	/**
	 * @param L List of points
	 * @return Convex Hull of provided points
	 */
	public static ArrayList<Coordinate> calculateConvexHull(ArrayList<Coordinate> L){	
		L = sortList(L);
		// Combine the two hulls
		//return the union of Llower and Lupper as the convex hull
		ArrayList<Coordinate> hull = new ArrayList<Coordinate>();
		hull = UpperHull(L);
		ArrayList<Coordinate> combination = LowerHull(L);
		//Remove the first and last point from Llower
		//TODO Awesome fix for DC Hull Fuck yea
		if(combination.size() > 2)
			combination.remove(0);
		combination.remove(combination.size()-1); 
		for(int i = 0; i < combination.size(); i++){
			hull.add(combination.get(i));
		}
		return hull;
	}
	
	
	// DC only
	/**
	 * @param L List of points
	 * @return List of Points that make up the DC hull
	 */
	public static ArrayList<Coordinate> calculateDCHull(ArrayList<Coordinate> L){
		if(L.size() < 4){
			return calculateConvexHull(L);
		}
		else{
			ArrayList<Coordinate> L1, L2;
			L1 = new ArrayList<Coordinate>();
			L2 = new ArrayList<Coordinate>();
			L = sortList(L);
			//Split point list
			for(int i = 0; i < L.size()/2; i++){
				L1.add(L.get(i));
			}
			for(int i = L.size()/2; i < L.size(); i++){
				L2.add(L.get(i));
			}
			return mergeHulls(calculateDCHull(L1), calculateDCHull(L2));
		}
	}
	
	
	// DC Only
	/**
	 * @param L1
	 * @param L2
	 * @return Hull of merged points
	 */
	public static ArrayList<Coordinate> mergeHulls(ArrayList<Coordinate> L1, ArrayList<Coordinate> L2){
		ArrayList<Coordinate> L = new ArrayList<Coordinate>();
		for(int i = 0; i < L1.size(); i++){
			L.add(L1.get(i));
		}
		for(int i = 0; i < L2.size(); i++){
			L.add(L2.get(i));
		}
		return calculateConvexHull(L);
	}
	
	/**
	 * @param startPoint
	 * @param endPoint
	 */
	public static void determinePaths(Coordinate startPoint, Coordinate endPoint){
		boolean endPointPassed = false;
		bottomPath = new ArrayList<Coordinate>();
		topPath = new ArrayList<Coordinate>();
		
		for(int i = 0; i<hull.size(); i++){
			if(hull.get(i) != endPoint && !endPointPassed){
				//Creating bottom path
				topPath.add(hull.get(i));
			}
			else if(hull.get(i) == endPoint){
				//end of bottom path
				//begin top path
				topPath.add(hull.get(i));
				bottomPath.add(hull.get(i));
				endPointPassed = true;
			}
			else
				bottomPath.add(hull.get(i));
		}
		bottomPath.add(startPoint);
		
		ArrayList<Coordinate> sortedBottomPath = new ArrayList<Coordinate>();
		//reverse bottom path order to make it A to B
		for(int i = bottomPath.size()-1; i >= 0; i--){
			sortedBottomPath.add(bottomPath.get(i));
		}
		bottomPath = sortedBottomPath;
		
		//Calculate Length of each path
		for(int i = 0; i < bottomPath.size()-1; i++){
			bottomPathLength += Coordinate.findDistance(bottomPath.get(i), bottomPath.get(i+1));
		}
		for(int i = 0; i < topPath.size()-1; i++){
			topPathLength += Coordinate.findDistance(topPath.get(i), topPath.get(i+1));
		}
	}
	
	/**
	 * @param args
	 * Generates input as a set of points. Outputs Convex Hull of the points
	 */
	public static void main(String[] args) {
		boolean topPathFirst = false;
		
		// input a set of point P from 2-D -> (x,y) 
		// output a set of points CH(P) the vertices of convex hull in clockwise order
		ArrayList<Coordinate> L = new ArrayList<Coordinate>();
		//Set up pathing test
		Coordinate startPoint = new Coordinate(1, 5);
		Coordinate endPoint = new Coordinate(10, 5);
		//Start point
		L.add(startPoint);
		//Obstacle
		L.add(new Coordinate(3,9));
		L.add(new Coordinate(4,1));
		L.add(new Coordinate(5,5));
		L.add(new Coordinate(6,9));
		L.add(new Coordinate(9,1));

		L.add(new Coordinate(4,5));
		L.add(new Coordinate(6,5));
		//End point
		L.add(endPoint);
		
		
		//Sort the points by the x co-ordinate and place in a list L
		System.out.println("Full coordinates are: " + L.toString());
		System.out.println();
		
		//Algorithm start

		hull = calculateConvexHull(L);
		// Display hull path
		System.out.println("Hull Coordinates are: " + hull.toString());			
		determinePaths(startPoint, endPoint);
		System.out.println();

		System.out.println("Bottom path: " + bottomPath.toString());
		System.out.println("Bottom path length: " + bottomPathLength);
		System.out.println("Top path: " + topPath.toString());
		System.out.println("Top path length: "+ topPathLength);
		System.out.println();
		
		// Decide which path
		if(bottomPathLength > topPathLength){
			System.out.println("Using Top Path");
			//for Obstacle 2
			topPathFirst = true;
		}
		else if(topPathLength > bottomPathLength){
			System.out.println("Using Bottom Path");
			//for Obstacle 2
			topPathFirst = false;
		}
		else if(topPathLength == bottomPathLength){
			System.out.println("Either paths are the same length, defaulting to top");
			//for obstacle 2
			topPathFirst = true;
		}
		
		//DCHull
		hull = calculateDCHull(L);
		System.out.println("DC Hull Coordinates are: " + hull.toString());
		
		// ######################
		// # Multiple obstacles #
		// ######################
		ArrayList<Coordinate> firstTopPath, firstBottomPath;
		firstTopPath = topPath;
		firstBottomPath = bottomPath;
		Coordinate endPoint2 = new Coordinate(22, 6);
		
		ArrayList<Coordinate> L2 = new ArrayList<Coordinate>();
		//Start point for obstacle 2
		L2.add(endPoint);
		
		//Obstacle 2
		L2.add(new Coordinate(15,10));
		L2.add(new Coordinate(16,2));
		L2.add(new Coordinate(17,6));
		L2.add(new Coordinate(18,10));
		L2.add(new Coordinate(21,2));

		L2.add(new Coordinate(16,5));
		L2.add(new Coordinate(18,5));
		
		//End point for obstacle 2
		L2.add(endPoint2);
		hull = calculateConvexHull(L2);
		System.out.println("Obstacle 2 Hull Coordinates are: " + hull.toString());
		determinePaths(endPoint, endPoint2);
		System.out.println("Obstacle 2 Bottom path: " + bottomPath.toString());
		System.out.println("Obstacle 2 Bottom path length: " + bottomPathLength);
		System.out.println("Obstacle 2 Top path: " + topPath.toString());
		System.out.println("Obstacle 2 Top path length: "+ topPathLength);
		System.out.println();
		
		
		// Decide which path and display it
		// first ifs are for Latest obstacle
		// inner ifs are to check which path was originally taken
		if(bottomPathLength > topPathLength){
			System.out.println("Using Top Path for second obstacle");
			System.out.println("Path summary: ");
			if(topPathFirst){
				//Original path was top
				System.out.println(firstTopPath.toString());
				System.out.println(" then ");
				System.out.println(topPath.toString());
			}
			else{
				//original path was bottom
				System.out.println(firstBottomPath.toString());
				System.out.println(" then ");
				System.out.println(topPath.toString());
			}
		}
		else if(topPathLength > bottomPathLength){
			System.out.println("Using Bottom Path for second obstacle");
			System.out.println("Path summary: ");
			if(topPathFirst){
				//Original path was top
				System.out.println(firstTopPath.toString());
				System.out.println(" then ");
				System.out.println(bottomPath.toString());
			}
			else{
				//original path was bottom
				System.out.println(firstBottomPath.toString());
				System.out.println(" then ");
				System.out.println(bottomPath.toString());
			}
		}
		else if(topPathLength == bottomPathLength){
			System.out.println("Either paths are the same length");
			System.out.println("Defaulting to top path for second obstacle");
			System.out.println("Path summary: ");
			if(topPathFirst){			
				//Original path was top
				System.out.println(firstTopPath.toString());
				System.out.println(" then ");
				System.out.println(topPath.toString());
			}
			else{
				//original path was bottom
				System.out.println(firstBottomPath.toString());
				System.out.println(" then ");
				System.out.println(topPath.toString());
			}
		}
	}
}
