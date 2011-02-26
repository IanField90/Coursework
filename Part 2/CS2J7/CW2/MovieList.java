package uk.ac.reading.ianfield.mmmgui;

import java.util.ArrayList;
import java.util.Iterator;

/**
 * The Class MovieList with an ArrayList to store the list of movies.
 * @author Ian Field
 */
public class MovieList{
	private ArrayList<Movie> movies;
	private Iterator<Movie> it;
	private int currentIndex;
	
	/**
	 * Constructor
	 */
	public MovieList(){
		movies = new ArrayList<Movie>();
		currentIndex = 0;
		it = movies.iterator();
	}
	
	/**
	 * Retrieves the array list
	 * @return The array list
	 */
	public ArrayList<Movie> getMovies(){
		return movies;
	}
	
	/**
	 * @return Number of movies in the list
	 */
	public int getSize(){
		return movies.size();
	}

	/**
	 * @return Index of currently selected Movie
	 */
	public int getCurrentIndex() {
		return currentIndex;
	}
	
	/**
	 * Retrieves the current Movie in the list
	 * @return Current Movie or null if non-existent
	 */
	public Movie getCurrent(){
		if(movies.size()>0 && currentIndex >=0)
			return movies.get(currentIndex);
		else
			return null;
	}
	
	/**
	 * Retrieves the Movie at provided Index
	 * @param index Index of Movie to be Retrieved
	 * @return Movie at given index or null if non-existent
	 */
	public Movie getAtIndex(int index){
		if(movies.get(index) != null){
			currentIndex = index;
			return movies.get(index);
		}
		else
			return null;
	}
	
	/**
	 * Retrieves the next Movie in the list
	 * @return Next Movie or null if non-existent
	 */
	public Movie getNext(){
		currentIndex++;
		if(currentIndex > movies.size()-1)
			currentIndex = 0;
		
		return movies.get(currentIndex);
	}
	
	/**
	 * Retrieves the next Movie in the list
	 * @return Previous Movie or null if non-existent
	 */
	public Movie getPrevious(){
		currentIndex--;
		if(currentIndex < 0)
		{
			currentIndex = movies.size()-1;
		}
		return movies.get(currentIndex);
	}
	
	/**
	 * @param mov Movie to add
	 */
	public void add(Movie mov){
		movies.add(mov);
	}
	
	
	/**
	 * Modifies the Movie at given index
	 * @param index Index of modified Movie
	 * @param mov Movie to replace original
	 */
	public void modify(int index, Movie mov){
		movies.set(index, mov);
	}
	
	/**
	 * Removes a Movie from the list at provided index.
	 * @param index Index of the list to be removed
	 */
	public void remove(int index){
		if(movies.get(index) != null){
			movies.remove(index);
			currentIndex = 0;
		}
		else
			System.out.println("Error with removal");
	}
	
	/**
	 * New ArrayList created.
	 */
	public void removeAllMovies(){
		movies = new ArrayList<Movie>();
	}
	
	/**
	 * @param term Search term
	 * @return MovieList of Movies containing the search term
	 */
	public MovieList findMoviesByTitle(String term){
		it = movies.iterator();
		MovieList subMovies = new MovieList();
		while(it.hasNext()){
			Movie next = it.next();
			if(next.getTitle().contains(term)){
				subMovies.add(next);
			}
		}
		return subMovies;
	}
	
	/**
	 * @param term Search term
	 * @return MovieList of movies matching the search term.
	 */
	public MovieList findExactTitle(String term){
		it = movies.iterator();
		MovieList subMovies = new MovieList();
		while(it.hasNext()){
			Movie next = it.next();
			if(next.getTitle().compareTo(term) == 0){
				subMovies.add(next);
			}
		}
		return subMovies;
	}
}

//prev
//if(currentIndex > 0){	
//currentIndex--;	
//return movies.get(currentIndex);
//}
//else
//return null;

//next
//it = movies.listIterator(currentIndex);
//if(it.hasNext()){
//	currentIndex++;
//	it.next();
//	return getAtIndex(currentIndex);
//}
//else
//	return null;