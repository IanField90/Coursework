package uk.ac.reading.cs2j7.ianfield.coursework;

import java.util.ArrayList;
import javax.swing.JOptionPane;
/**
 * @author Ian Field
 */
public class MovieList {
	//ArrayList construction
	private ArrayList<Movie> movies = new ArrayList<Movie>();
	private int currentMovieIndex;
	
	/**
	 * @return ArrayList of Movies
	 */
	public ArrayList<Movie> getMovies(){
		return movies;
	}
	
	/**
	 * @param mov Movie to add
	 */
	public void add(Movie mov){
		movies.add(mov);
	}
	
	/**
	 * @param index
	 * Displays menu to edit values of the movie at index
	 */
	public void modify(int index){
		Movie modified = movies.get(index);
		modified.setTitle(JOptionPane.showInputDialog("Current Title is: " + 
				modified.getTitle() +
				"\nTitle:"));
		
		modified.setVotes(Integer.parseInt(JOptionPane.showInputDialog("Current Votes are: " +
				modified.getVotes() +
				"\nVotes:")));
		
		modified.setRating(Double.parseDouble(JOptionPane.showInputDialog("Current Rating is: " + 
				modified.getRating() + 
				"\nRating:")));
		
		//Put the modified version back into the list
		movies.add(index, modified);
	}
	
	/**
	 * @param index Index of the movie to be deleted from the list
	 */
	public void remove(int index){
		movies.remove(index);
	}
	
	/**
	 * @return Index of the currently pointed movie
	 */
	public int getCurrentMovieIndex(){
		return currentMovieIndex;
	}
	
	/**
	 * @param index Index to point to
	 */
	public void setCurrentMovieIndex(int index){
		currentMovieIndex = index;
	}
	
	/**
	 * @param index Index of movie to return
	 * @return Movie at given index
	 */
	public Movie getMovieAtIndex(int index)
	{
		return (Movie) movies.get(index);
	}
	
	/**
	 * @return Number of movies in the list
	 */
	public int getNumberOfMovies(){
		return movies.size();
	}
	
	/**
	 * @return Current Movie
	 */
	public Movie getCurrent(){
		return movies.get(currentMovieIndex);
	}
	
	/**
	 * Increments the index
	 * @return Movie at new index
	 */
	public Movie goToNext(){
		currentMovieIndex++;
		if(currentMovieIndex > getNumberOfMovies()-1)
			currentMovieIndex = 0;
		
		return movies.get(currentMovieIndex);
	}
	
	/**
	 * Decrements the index
	 * @return Movie at new index
	 */
	public Movie goToPrevious(){
		currentMovieIndex--;
		if(currentMovieIndex < 0)
		{
			currentMovieIndex = getNumberOfMovies()-1;
		}
		return movies.get(currentMovieIndex);
	}
	
	public void removeAllMovies(){
		for(int i = 0; i < movies.size(); i++){
			movies.remove(i);
		}
	}
	
	/**
	 * Default Constructor with index set to 0
	 */
	MovieList(){
		currentMovieIndex = 0;
	}
	
	/**
	 * @param term Search term
	 * @return MovieList of Movies containing the search term
	 */
	public MovieList findMoviesByTitle(String term){
		MovieList subMovies = new MovieList();
		for (int i = 0; i < movies.size(); i++ ){
			if(movies.get(i).getTitle().contains(term)){
				subMovies.add(movies.get(i));
			}
		}		
		return subMovies;
	}
	
	/**
	 * @param term Search term
	 * @return MovieList of movies matching the search term.
	 */
	public MovieList findExactTitle(String term){
		MovieList subMovies = new MovieList();
		for (int i = 0; i < movies.size(); i++){
			if (movies.get(i).getTitle().compareTo(term) == 0){
				subMovies.add(movies.get(i));
			}
		}
		return subMovies;
	}
}
