package uk.ac.reading.cs2j7.ianfield.coursework;

import java.io.*;

import javax.swing.JOptionPane;
/**
 * @author Ian Field
 */

public final class Main {	
	private static MovieList currentList = new MovieList();
	private static MovieList originalList = new MovieList();
	private static MovieList[] searchResults = {new MovieList(), new MovieList(), new MovieList(), new MovieList()};
	private static File activeFile = null;
	private static int searchIteration = 0;
	// Constant for max search refinement
	private static final int MAX_ITERATIONS = 4;
	/**
	 * Displays file Menu - Processes outcome of user input.
	 * Allows user to create, open, save, save as...
	 */
	public static void displayFileMenu() {
		
		//For custom file format
		int choice =  Integer.parseInt(JOptionPane.showInputDialog(null, "1. New" +
				"\n2. Open" +
				"\n3. Save" +
				"\n4. Save As..." +
				"\n5. Exit"));
		switch (choice){
			case 1:
				//New
				//Prompt user for file name
				String fileName = JOptionPane.showInputDialog(null, "File name:");
				File newFile = new File(fileName + ".csv");
				try {
					FileWriter outFileWriter = new FileWriter(newFile);
					PrintWriter writer = new PrintWriter(outFileWriter);
					writer.println("#title,votes,rating");// not really needed
					writer.close();
					System.out.println(fileName + ".csv has been created!");
				} catch (IOException e1) {
					//File Writer exception
					e1.printStackTrace();
				}
				break;
			case 2:
				//Open
				File f = new File(JOptionPane.showInputDialog(null, "File Name without extension: ")+ ".csv");
				FileReader fReader;
				try {
					fReader = new FileReader(f);
					BufferedReader inputFile = new BufferedReader(fReader);
					String line = inputFile.readLine(); // returns null if \n
					// go until end of file
					do{
						line = inputFile.readLine();
						if(line != null){
							//split read line
							String[] split = line.split(",");
							//retrieve data from split array
							//convert to movie and add it.
							currentList.add(new Movie(split[0], Integer.parseInt(split[1]), Double.parseDouble(split[2])));
						}
					}while(line != null);
					//ensure file is closed
					inputFile.close();
				} catch (FileNotFoundException e) {
					// Exception for file not existent
					e.printStackTrace();
				} catch (IOException e) {
					// Exception for readLine
					e.printStackTrace();
				}
				break;
			case 3:
				//Save
				if(currentList.getNumberOfMovies() > 0){
					FileWriter fSaveWriter;
					try{
						fSaveWriter = new FileWriter(activeFile);
						PrintWriter savePrintWriter = new PrintWriter(fSaveWriter);
						savePrintWriter.println("#title,votes,rating");
						for(int i=0; i<currentList.getNumberOfMovies(); i++){
							savePrintWriter.println(currentList.getMovieAtIndex(i).toCSVRow());
							System.out.println("shoved in movie:" + i);
						}
						savePrintWriter.close();
					}catch(IOException e){
						e.printStackTrace();
					}
				}
				break;
			case 4:
				//Save as...
				// Prompt user for file name
				activeFile = new File(JOptionPane.showInputDialog(null, "File name:") + ".csv");
				FileWriter fSaveWriter;
				try{
					// Write new file
					fSaveWriter = new FileWriter(activeFile);
					PrintWriter savePrintWriter = new PrintWriter(fSaveWriter);
					savePrintWriter.println("#title,votes,rating");
					for(int i=0; i<currentList.getNumberOfMovies(); i++){
						savePrintWriter.println(currentList.getMovieAtIndex(i).toCSVRow());
					}
					savePrintWriter.close();
				}catch(IOException e){
					e.printStackTrace();
				}				
				break;
			case 5:
				//Exit
				//Show main menu
				break;
			default:
				System.out.println("Invalid input!");
				break;
		}
	}
	
	/**
	 * Displays view Menu - Processes outcome of user input.
	 * Allows Stepping forwards and backwards through the list of Movies.
	 * Movie can be jumped to by providing index.
	 */
	public static void displayViewMenu() {
		int choice;
		do{
			choice =  Integer.parseInt(JOptionPane.showInputDialog(null, "1. Display Info about current Movie" +
					"\n2. Go to next Movie" +
					"\n3. Go to previous Movie" +
					"\n4. Go to a Movie index" +
					"\n-ve. Exit"));
			
			//break if negative
			if(choice < 0)
				break;
			
			switch (choice){
				case 1:
					// Display current Movie
					System.out.println(currentList.getMovieAtIndex(currentList.getCurrentMovieIndex()).toText());
					break;
				case 2:
					// Go to next Movie & display it
					System.out.println(currentList.goToNext().toText());
					break;
				case 3:
					//Go to previous movie & display it
					System.out.println(currentList.goToPrevious().toText());
					break;
				case 4:
					// Go to movie at given index & display it
					// otherwise say it doesn't exist
					int index = Integer.parseInt(JOptionPane.showInputDialog(null, "Index: "));
					if(index >= 0 && index < currentList.getNumberOfMovies()){
						currentList.setCurrentMovieIndex(index);
						System.out.println(currentList.getMovieAtIndex(index).toText());
					}
					else
						System.out.println("Index '" + index + " 'doesn't exist");	
					break;
				default:
					//Notify user entry was invalid
					System.out.println("Invalid input!");
					break;
			}
		}while(choice > 0);
	}
	
	/**
	 * Displays edit Menu - Allows editing of movie attributes of the current movie.
	 * Each field required to be entered once this menu is initialised.
	 */
	public static void displayEditMenu() {
		int choice =  Integer.parseInt(JOptionPane.showInputDialog(null, "1. Modify current Movie" +
				"\n2. Remove current Movie" +
				"\n3. Add a new Movie"));
		switch (choice){
			case 1:
				// Modify current movie
				currentList.modify(currentList.getCurrentMovieIndex());
				break;
			case 2:
				// Remove current movie
				currentList.remove(currentList.getCurrentMovieIndex());
				break;
			case 3:
				// Create a new Movie
				String title = JOptionPane.showInputDialog(null, "Title:");
				int votes = Integer.parseInt(JOptionPane.showInputDialog(null, "Votes:"));
				double rating = Double.parseDouble(JOptionPane.showInputDialog(null, "Rating:"));
				Movie myMovie = new Movie(title, votes, rating);
				currentList.add(myMovie);
				break;
			default:
				System.out.println("Invalid input!");
				break;
		}
	}
	
	/**
	 * Displays search Menu - Processes outcome of user input.
	 * <br />As user searches the search result is stored. The user may backtrack through search results.
	 * <br />The user may also clear search results, which returns them to the original file contents.
	 */
	public static void displaySearchMenu() {
		int choice = Integer.parseInt(JOptionPane.showInputDialog(null, "1. Search exact title" +
				"\n2. Filter Titles" +
				"\n3. Return to previous search result" +
				"\n4. Reset filter criteria"));
		String searchTerm = null;
		switch (choice){
			case 1:
				if(searchIteration == 0)
					originalList = currentList;
				
				searchTerm = JOptionPane.showInputDialog(null, "Exact Title:");
				searchIteration = 0;
				searchResults[searchIteration] = currentList.findExactTitle(searchTerm);			
				currentList = searchResults[searchIteration];		
				break;
			case 2:
				if(searchIteration == 0)
					originalList = currentList;
				
				if(searchIteration < MAX_ITERATIONS){
					searchTerm = JOptionPane.showInputDialog(null, "Filter term:");
					searchResults[searchIteration] = currentList.findMoviesByTitle(searchTerm);
					currentList = searchResults[searchIteration];
					searchIteration++;
					break;
				}
				else{
					System.out.println("Maximum search iterations reached!");
					break;
				}
				
			case 3:
				// go back a search term
				if(searchIteration > 0){
					searchIteration--;
				}
				currentList = searchResults[searchIteration];
				break;
			case 4:
				// clear filter (back to main list)
				searchIteration = 0;
				currentList = originalList;
				break;
			default:
				System.out.println("Invalid input!");
				break;
		}
	}
	
	/**
	 * Displays import Menu - Processes outcome of user input
	 * Allows Top 246, Top 250, 1000movies.list, movies.list to be imported.
	 * Only Top 246 and Top 250 contain Votes and Rating fields for each movie.
	 * Other file types import Movie Title only.
	 * Custom IMDB files:
	 */
	public static void displayImportMenu(){
		int choice =  Integer.parseInt(JOptionPane.showInputDialog(null, "1. Top ranked Movies" +
				"\n2. Import IMDB Movie File" +
				"\n3. Import other IMDB files"));
		
		switch (choice){
			case 1:
				int rankedMovie = Integer.parseInt(JOptionPane.showInputDialog(null, "1. 246" +
						"\n2. 250"));
				//top246
				if(rankedMovie == 1){
					//read from file + add
					currentList.removeAllMovies();
					activeFile = new File("top246.csv");
					File f = new File("top246.csv");
					FileReader fReader;
					try {
						fReader = new FileReader(f);
						BufferedReader inputFile = new BufferedReader(fReader);
						String line = inputFile.readLine(); // returns null if \n
						// go until end of file
						do{
							line = inputFile.readLine();
							if(line != null){
								//split read line
								String[] split = line.split(",");
								//retrieve data from split array
								//convert to movie and add it.
								currentList.add(new Movie(split[0], Integer.parseInt(split[1]), Double.parseDouble(split[2])));
							}
						}while(line != null);
						//ensure file is closed
						inputFile.close();
					} catch (FileNotFoundException e) {
						// Exception for file not existent
						e.printStackTrace();
					} catch (IOException e) {
						// Exception for readLine
						e.printStackTrace();
					}			
				}//Top 250
				else if(rankedMovie == 2){
					//read from file + add
					currentList.removeAllMovies();
					activeFile = new File("top250.csv");
					File f = new File("top250.csv");
					FileReader fReader;
					try {
						fReader = new FileReader(f);
						BufferedReader inputFile = new BufferedReader(fReader);
						String line = inputFile.readLine(); // returns null if \n
						// go until end of file
						do{
							line = inputFile.readLine();
							if(line != null){
								//split read line
								String[] split = line.split(",");
								//retrieve data from split array
								//convert to movie and add it.
								currentList.add(new Movie(split[0], Integer.parseInt(split[1]), Double.parseDouble(split[2])));
							}
						}while(line != null);
						//ensure file is closed
						inputFile.close();
					} catch (FileNotFoundException e) {
						// Exception for file not existent
						e.printStackTrace();
					} catch (IOException e) {
						// Exception for readLine
						e.printStackTrace();
					}
				}
				break;
			case 2:
				int input = Integer.parseInt(JOptionPane.showInputDialog(null, "Which IMDB file would you like?" +
						"\n1. 1000" +
						"\n2. 1,500,000+"));
				if (input == 1){
					File movList = new File("1000movies.list");
					FileReader fReader;
					try {
						fReader = new FileReader(movList);
						BufferedReader inputFile = new BufferedReader(fReader);
						String line;
						currentList = new MovieList();
						//Skip first 17 lines
						for(int i = 0; i<17; i++)
							line = inputFile.readLine(); // returns null if \n
						// go until end of file
						do{
							line = inputFile.readLine();
							if(line != null){
								//split read line
								//REGEX
								//Example
						        String regex = "(\\(|\\)|\\/)";
						        // 0-title, 3-genre, 4-year
						        String fields[] = line.split(regex);
						        currentList.add(new Movie(fields[0], 0, 0));
						        
							}
						}while(line != null);
						//ensure file is closed
						inputFile.close();
						System.out.println("Imported movies only contain title field.");
					} catch (FileNotFoundException e) {
						// Exception for file not existent
						e.printStackTrace();
					} catch (IOException e) {
						// Exception for readLine
						e.printStackTrace();
					}
				}
				else if(input == 2){
					File movList = new File("movies.list");
					FileReader fReader;
					try {
						fReader = new FileReader(movList);
						BufferedReader inputFile = new BufferedReader(fReader);
						String line;
						currentList = new MovieList();
						//Skip first 17 lines
						for(int i = 0; i<17; i++)
							line = inputFile.readLine(); // returns null if \n
						// go until end of file
						do{
							line = inputFile.readLine();
							if(line != null){
								//split read line
						        String regex = "(\\(|\\)|\\/)";
						        String fields[] = line.split(regex);
						        currentList.add(new Movie(fields[0], 0, 0));
						        
							}
						}while(line != null);
						//ensure file is closed
						inputFile.close();
						System.out.println("Imported movies only contain title field.");
					} catch (FileNotFoundException e) {
						// Exception for file not existent
						System.out.println("File not found!");
						e.printStackTrace();
					} catch (IOException e) {
						// Exception for readLine
						e.printStackTrace();
					}
				}
				else
					System.out.println("Invalid input!");
				
				break;
			case 3:
				FileReader fReader;
				File movList = new File("genres.list");
				int input2 = Integer.parseInt(JOptionPane.showInputDialog(null, "1. Genres"));
				if (input2 == 1){
				try{
					// Load Genres file
					System.out.println("Importing file, please wait...");
					fReader = new FileReader(movList);
					BufferedReader inputFile = new BufferedReader(fReader);
					String line;
					currentList = new MovieList();
					//Skip first 376lines
					for(int i = 0; i<376; i++)
						line = inputFile.readLine(); // returns null if \n
					// go until end of file
					do{
						line = inputFile.readLine();
						if(line != null){
							//split read line
					        String regex = "(\\(|\\)|\\/)";
					        String fields[] = line.split(regex);
					        currentList.add(new Movie(fields[0], 0, 0));
					        
						}
					}while(line != null);
					//ensure file is closed
					inputFile.close();
					System.out.println("Imported movies only contain title field.");
				} catch (FileNotFoundException e) {
					// Exception for file not existent
					System.out.println("File not found!");
					e.printStackTrace();
				} catch (IOException e) {
					// Exception for readLine
					e.printStackTrace();
				}
				}
				else if(input2 == 2){
					//complete-cast.list
					// 136 first movie
					// 72944 last movie
					
				}
				break;
			default:
				System.out.println("Invalid input!");
				break;
		}
	}
	
	/**
	 * @param args
	 * Displays main menu system. Allows user to continually perform actions until
	 * <br />a negative value is entered.
	 */
	public static void main(String[] args){
		// On load read custom file for last used file
		File f = new File("UserSetting.txt");
		FileReader fReader;
		try {
			fReader = new FileReader(f);
			BufferedReader inputFile = new BufferedReader(fReader);
			String lastFileName = inputFile.readLine(); // returns null if \n
			// if null no file was saved
			if(lastFileName != null){			
				activeFile = new File(lastFileName);
				try{
					fReader = new FileReader(activeFile);
					inputFile = new BufferedReader(fReader);
					String line = inputFile.readLine();
					do{
						line = inputFile.readLine();
						if(line != null){
							//split read line
							String[] split = line.split(",");
							//retrieve data from split array
							//convert to movie and add it.
							currentList.add(new Movie(split[0], Integer.parseInt(split[1]), Double.parseDouble(split[2])));
						}
					}while(line != null);
				} catch (FileNotFoundException e){
					// Exception for data file non existent
					e.printStackTrace();
				} catch (IOException e){
					// Exception for data file readLine
					e.printStackTrace();
				}		
			}
			else
				activeFile = new File("Default.csv");
			//ensure file is closed
			inputFile.close();
		} catch (FileNotFoundException e) {
			// Exception for settings file non existent
			e.printStackTrace();
		} catch (IOException e) {
			// Exception for settings file readLine
			e.printStackTrace();
		}
		
		
		// Display options to user
		int menuChoice;
		do{
			//Initial menu option
			menuChoice = Integer.parseInt(JOptionPane.showInputDialog("Which Menu would you like first?" +
					"\n1. File" +
					"\n2. View" +
					"\n3. Edit" +
					"\n4. Search" +
					"\n5. Import" +
					"\n-ve. Exit"));
			
			//exit loop as user has selected exit
			if(menuChoice < 0)
				break;
			
			//otherwise process input
			switch (menuChoice){
				case 1:
					Main.displayFileMenu();
					break;
				case 2:
					Main.displayViewMenu();
					break;
				case 3:
					Main.displayEditMenu();
					break;
				case 4:
					Main.displaySearchMenu();
					break;
				case 5:
					Main.displayImportMenu();
					break;
				default:
					System.out.println("Invalid input!");
					break;
			}
		}while(menuChoice > 0);
		
		
		// On exit save current file name to custom file
		File settings = new File("UserSetting.txt");
		try {
			FileWriter outFileWriter = new FileWriter(settings);
			PrintWriter writer = new PrintWriter(outFileWriter);
			writer.println(activeFile.getName());		
			writer.close();
			System.out.println("User Settings have been saved. Goodbye!");
		} catch (IOException e1) {
			//File Writer exception			
			e1.printStackTrace();
		}
	}
}