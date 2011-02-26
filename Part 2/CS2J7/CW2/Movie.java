package uk.ac.reading.ianfield.mmmgui;

/**
 * Stores and retrieves information about a single movie.
 * @author Ian Field
 */
public class Movie {
	private String title, genre, actors;
	private int rating, votes, year;
	
	/**
	 * Default Constructor.
	 */
	public Movie() {
	}
	
	/**
	 * Constructor for Movie Class.
	 * @param title Title of the Movie.
	 * @param genre Genre of the Movie.
	 * @param actors Actors of the Movie.
	 * @param rating Rating of the Movie.
	 * @param votes Votes of the Movie.
	 * @param year Year of the Movie.
	 */
	public Movie(String title, String genre, String actors, int rating, int votes, int year) {
		super();
		this.title = title;
		this.genre = genre;
		this.actors = actors;
		this.rating = rating;
		this.votes = votes;
		this.year = year;
	}
	
	
	/**
	 * @return Title of the Movie.
	 */
	public String getTitle() {
		return title;
	}

	/**
	 * @param title Value for the Title of the Movie.
	 */
	public void setTitle(String title) {
		this.title = title;
	}

	/**
	 * @return Genre of the Movie.
	 */
	public String getGenre() {
		return genre;
	}

	/**
	 * @param genre Value for Genre of the Movie.
	 */
	public void setGenre(String genre) {
		this.genre = genre;
	}

	/**
	 * @return Actors of the Movie.
	 */
	public String getActors() {
		return actors;
	}

	/**
	 * @param actors Value for the Actors of the Movie.
	 */
	public void setActors(String actors) {
		this.actors = actors;
	}

	/**
	 * @return Rating of the Movie.
	 */
	public int getRating() {
		return rating;
	}

	/**
	 * @param rating Value for the Rating of the Movie.
	 */
	public void setRating(int rating) {
		this.rating = rating;
	}

	/**
	 * @return Votes of the Movie.
	 */
	public int getVotes() {
		return votes;
	}

	/**
	 * @param votes Value for the Votes of the Movie.
	 */
	public void setVotes(int votes) {
		this.votes = votes;
	}

	/**
	 * @return Year of the Movie.
	 */
	public int getYear() {
		return year;
	}

	/**
	 * @param year Value for the Year of the Movie.
	 */
	public void setYear(int year) {
		this.year = year;
	}

	/**
	 * Converts the Movies to a pipe separated variable string
	 * @return Pipe separated variable string
	 */
	public String toMMMRow() {
		String result = this.title + "|" + this.genre + "|" + this.actors + "|" + this.rating + "|" + this.votes + "|" + this.year;
		return result;
	}
}
