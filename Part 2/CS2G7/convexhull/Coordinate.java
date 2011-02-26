package cs2g7.convexhull;
/**
 * @author Ian Field
 */
public class Coordinate {

	private int x, y;
	
	/**
	 * Constructor
	 * @param x x-coordinate
	 * @param y y-coordinate
	 */
	Coordinate(int x, int y){
		this.x = x;
		this.y = y;
	}
	
	/**
	 * @return x-coordinate
	 */
	public int get_x(){
		return this.x;
	}
	
	/**
	 * @return y-coordinate
	 */
	public int get_y(){
		return y;
	}
	
	/**
	 * @return Coordinate in the form "(X, Y)"
	 */
	public String toString(){
		return "(" + x + ", " + y +")";
	}

	/**
	 * @param point1
	 * @param point2
	 * @return Distance of separation of the given points
	 */
	public static double findDistance(Coordinate point1, Coordinate point2){
		int xLength, yLength;
		double result;
		//ensure +ve
		xLength = Math.abs(point1.get_x() - point2.get_x());
		yLength = Math.abs(point1.get_y() - point2.get_y());
		
		result = Math.sqrt((xLength * xLength) + (yLength * yLength));
		
		return result;
	}
}
