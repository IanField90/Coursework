package uk.ac.reading.cs2j7.ianfield.coursework;


/**
 * @author Ian Field
 */
public class Movie {

	private String _title;
	private int _votes;
	private double _rating;
	
	/**
	 * @param title
	 * Value to become title
	 */
	public void setTitle(String title) {
		_title = title;
	}
	
	/**
	 * @param votes
	 * Value to become votes
	 */
	public void setVotes(int votes){
		_votes = votes;
	}
	
	/**
	 * @param rating
	 * Value to become rating
	 */
	public void setRating(double rating){
		_rating = rating;
	}

	/**
	 * @return
	 * Title for the Movie
	 */
	public String getTitle() {
		return _title;
	}
	
	/**
	 * @return
	 * Votes for the Movie
	 */
	public int getVotes(){
		return _votes;
	}
	
	/**
	 * @return
	 * Rating for the Movie
	 */
	public double getRating(){
		return _rating;
	}
	
	/**
	 * @return Movie details. Example:<br/>
	 * Title, Votes: 100, Rating: 3.4
	 */
	public String toText()
	{
		return _title + ", Votes: " + _votes + ", Rating: " + _rating;
	}
	
	/**
	 * @return Movie as a CSV row. Example:
	 * Blade,20,3.4
	 */
	public String toCSVRow(){
		return _title + "," + _votes + "," + _rating;
	}
	
	/**
	 * Default constructor. Null Movie
	 */
	Movie()
	{
	}
	
	/**
	 * Constructor with arguments
	 * @param title Title of Movie
	 * @param votes Number of Votes movie has
	 * @param rating Rating of Movie
	 */
	Movie(String title, int votes, double rating)
	{
		_title = title;
		_votes = votes;
		_rating = rating;
	}
}
