package uk.ac.reading.ianfield.mmmgui;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Iterator;

import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JToolBar;
import javax.swing.border.EmptyBorder;


//using (10.5 marks) JButton, JLabel, JTextField, JPanel, JFrame, JToolBar, JMenu, JMenuItem, JMenuBar, 
//				  JOptionPane, JProgressBar, GridLayout, FlowLayout, BoxLayout, BorderLayout, ActionListener
//				  JFileChooser, JComboBox, JTabbedFrame, JTextArea, KeyListener
// To use: JPopupMenu, JTree, JList, ItemListner
// + 7 others & 2 page write up
/**
 * Provides a graphical user interface for the Movie Manager application
 * @author Ian Field
 */
public class MyMoviesManagerGUI  extends JPanel implements ActionListener, KeyListener{
	private static final long serialVersionUID = -7135200461136308822L;
	private JButton jb_previous, jb_next, jb_save, jb_open, jb_go;
	private JButton jb_enableEdit, jb_saveEdit, jb_add, jb_remove;
	private JLabel countLabel;
	private JMenuBar jmb_menuBar;
	private JMenu jm_file;
	private JMenuItem jmi_save, jmi_saveAs, jmi_open, jmi_import;
	private JTextField jtf_title, jtf_genre, jtf_actors, jtf_rating, jtf_votes, jtf_year, currentIndexField;
	private File activeFile = null;
	public static MovieList movieList;
	//would be used if not in jar
	//private static final String relpath = "images" + File.separator;
	private boolean firstAddClick = false;
	
	/**
	 * ViewMenu constructor sets up graphical elements.
	 */
	public MyMoviesManagerGUI(){
		movieList = new MovieList();
		
		//Top
		//Menu bar
		jmb_menuBar = new JMenuBar();
		jm_file = new JMenu("File");
		jmi_save = new JMenuItem("Save");
		jmi_save.addActionListener(this);
		jmi_open = new JMenuItem("Open");
		jmi_open.addActionListener(this);
		jmi_saveAs = new JMenuItem("Save As...");
		jmi_saveAs.addActionListener(this);
		jmi_import = new JMenuItem("Import");
		jmi_import.addActionListener(this);
		jm_file.add(jmi_open);
		jm_file.add(jmi_save);
		jm_file.add(jmi_saveAs);
		jm_file.add(jmi_import);
		jmb_menuBar.add(jm_file);
		
		//Toolbar
		//jb_save = new JButton(new ImageIcon(relpath + "save.gif"));
		jb_save = new JButton(new ImageIcon(this.getClass().getResource("/resources/save.gif")));
		jb_save.setToolTipText("Save");
		jb_save.addActionListener(this);
		//jb_open = new JButton(new ImageIcon(relpath + "open.gif"));
		jb_open = new JButton(new ImageIcon(this.getClass().getResource("/resources/open.gif")));
		jb_open.setToolTipText("Open");
		jb_open.addActionListener(this);

		JToolBar topToolBar = new JToolBar();
		topToolBar.add(jb_save);
		topToolBar.add(jb_open);
		topToolBar.setFloatable(false);
		topToolBar.setLayout(new BoxLayout(topToolBar, BoxLayout.X_AXIS));
		//End top
		
		//Centre
		JPanel jp_center = new JPanel();
		jp_center.setLayout(new GridLayout(1,1));
		
		jtf_title = new JTextField();
		jtf_genre = new JTextField();
		jtf_actors = new JTextField();
		jtf_rating = new JTextField();
		jtf_votes = new JTextField();
		jtf_year = new JTextField();
		
		jb_enableEdit = new JButton("Enable Edit");
		jb_enableEdit.setToolTipText("Allow field editing");
		jb_enableEdit.addActionListener(this);
		jb_saveEdit = new JButton("Save Edit");
		jb_saveEdit.setToolTipText("Saves fields for this movie");
		jb_saveEdit.addActionListener(this);
		jb_saveEdit.setEnabled(false);
		jb_add = new JButton("Add Movie");
		jb_add.setToolTipText("Allows manual addition of a movie to list");
		jb_add.addActionListener(this);
		jb_remove = new JButton("RemoveMovie");
		jb_remove.setToolTipText("Removes movie from list");
		jb_remove.addActionListener(this);
		
		JPanel jp_movieInfo = new JPanel();
		jp_movieInfo.setLayout(new GridLayout(6,2));
		jp_movieInfo.add(new JLabel("Title:"));
		jp_movieInfo.add(jtf_title);
		jp_movieInfo.add(new JLabel("Genre:"));
		jp_movieInfo.add(jtf_genre);
		jp_movieInfo.add(new JLabel("Actors:"));
		jp_movieInfo.add(jtf_actors);
		jp_movieInfo.add(new JLabel("Rating:"));
		jp_movieInfo.add(jtf_rating);
		jp_movieInfo.add(new JLabel("Votes:"));
		jp_movieInfo.add(jtf_votes);
		jp_movieInfo.add(new JLabel("Year:"));
		jp_movieInfo.add(jtf_year);
		
		JPanel jp_editItems = new JPanel();
		jp_editItems.setLayout(new GridLayout(2,2));
		jp_editItems.add(jb_enableEdit);
		jp_editItems.add(jb_saveEdit);
		jp_editItems.add(jb_add);
		jp_editItems.add(jb_remove);
		
		jp_center.add(jp_movieInfo);
		jp_center.add(jp_editItems);
		
		//TODO Search GUI elements + implementation
		//End centre
		
		//Bottom (Navigation)
		currentIndexField = new JTextField();
		countLabel = new JLabel(" / " + (movieList.getSize()));
		
		//jb_previous = new JButton(new ImageIcon(relpath + "left.gif"));
		jb_previous = new JButton(new ImageIcon(this.getClass().getResource("/resources/left.gif")));
		jb_previous.setToolTipText("Previous");
		jb_previous.addActionListener(this);
		//jb_next = new JButton(new ImageIcon(relpath + "right.gif"));
		jb_next = new JButton(new ImageIcon(this.getClass().getResource("/resources/right.gif")));
		jb_next.setToolTipText("Next");
		jb_next.addActionListener(this);
		jb_go = new JButton("Go");
		jb_go.setToolTipText("Go");
		jb_go.addActionListener(this);
		
		currentIndexField.setPreferredSize(new Dimension(50, 20));
		countLabel.setPreferredSize(new Dimension(60, 20));
		JPanel bottomPanel = new JPanel();
		bottomPanel.add("West", jb_previous);
		bottomPanel.add("Center", currentIndexField);
		bottomPanel.add("Center", countLabel);
		bottomPanel.add("Center", jb_go);
		bottomPanel.add("East", jb_next);
		//End bottom
		
		//Arrange GUI elements on panel
		setLayout(new BorderLayout());
		add("North", topToolBar);
		jp_center.setBorder(new EmptyBorder(10,10,10,10));
		add("Center", jp_center);
		add("South", bottomPanel);
		currentIndexField.addKeyListener(this);
		clearMovieFields();
		updateNumOfMovies();
		currentIndexField.setText("0");
		jb_next.setEnabled(false);
		jb_previous.setEnabled(false);
		jb_go.setEnabled(false);
		jb_enableEdit.setEnabled(false);
		jb_remove.setEnabled(false);
		disableEdits();
	}

	/**
	 * Prepares a JFrame at (200,300)
	 */
	public void createAndShowGUI() {
		JFrame frame = new JFrame("My Movies Manager");
		MyMoviesManagerGUI panel = new MyMoviesManagerGUI();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setJMenuBar(panel.jmb_menuBar);
		frame.add(panel);
		frame.pack();
		frame.setLocation(200,300);
		frame.setVisible(true);
	}
	
	/**
	 * Processes user actions based on which element is interacted with.
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		
		if(e.getSource() == jb_previous){
			updateMovieFields(movieList.getPrevious());
			currentIndexField.setText(String.valueOf(movieList.getCurrentIndex()+1));
			
		}
		else if(e.getSource() == jb_next){
			updateMovieFields(movieList.getNext());
			currentIndexField.setText(String.valueOf(movieList.getCurrentIndex()+1));
			
		}
		else if(e.getSource() == jb_save){
			if(activeFile != null){
				//do save
				writeFile(activeFile);
			}
			else{
				//Show save as instead
				JFileChooser jfc = new JFileChooser();
				jfc.addChoosableFileFilter(new mmmFileFilter());
				jfc.showSaveDialog(this);
				activeFile = jfc.getSelectedFile();
				//do save
				if(activeFile != null)
					writeFile(activeFile);
			}
		}
		else if(e.getSource() == jb_open){
			JFileChooser jfc = new JFileChooser();
			jfc.addChoosableFileFilter(new mmmFileFilter());
			jfc.showOpenDialog(this);
			activeFile = jfc.getSelectedFile();
			//do open
			if(activeFile != null)
				openFile(activeFile);
		}
		else if(e.getSource() == jb_go){
			//Sanitise
			try{
				int index = Integer.parseInt(currentIndexField.getText())-1;//GUI 1 = 0
				Movie movie = movieList.getAtIndex(index);
				if(movie != null){
					updateMovieFields(movieList.getAtIndex(index));
				}
				else{
					JOptionPane.showMessageDialog(null, "No Movie at index", "Error", JOptionPane.ERROR_MESSAGE);
				}
			}
			catch(Exception e1){
				JOptionPane.showMessageDialog(null, "Value wasn't integer", "Error", JOptionPane.ERROR_MESSAGE);
			}
			
		}
		else if(e.getSource() == jb_enableEdit){
			allowEdits();
			jb_saveEdit.setEnabled(true);
			jb_enableEdit.setEnabled(false);
			jb_add.setEnabled(false);
			jb_remove.setEnabled(false);
			
		}
		else if(e.getSource() == jb_saveEdit){
			Movie movie = getMovieFields();
			if(movie != null){
				movieList.modify(movieList.getCurrentIndex(), movie);
				disableEdits();
				jb_saveEdit.setEnabled(false);
				jb_enableEdit.setEnabled(true);
				jb_add.setEnabled(true);
				jb_remove.setEnabled(true);
			}
			
		}
		else if(e.getSource() == jb_add){
			//First click
			if(!firstAddClick){
				jb_enableEdit.setEnabled(false);
				jb_remove.setEnabled(false);
				jb_next.setEnabled(false);
				jb_previous.setEnabled(false);
				jb_go.setEnabled(false);
				allowEdits();
				clearMovieFields();
				firstAddClick = true;
			}else{
				//Second click actually adds the movie
				Movie movie = getMovieFields();
				if(movie != null){
					movieList.add(movie);
					jb_enableEdit.setEnabled(true);
					jb_remove.setEnabled(true);
					jb_next.setEnabled(true);
					jb_previous.setEnabled(true);
					jb_go.setEnabled(true);
					disableEdits();
					updateMovieFields(movieList.getCurrent());
					updateNumOfMovies();
					currentIndexField.setText(String.valueOf(movieList.getCurrentIndex()+1));
					firstAddClick = false;
				}
			}
			
		}
		else if(e.getSource() == jb_remove){
			movieList.remove(movieList.getCurrentIndex());
			// when list is size 1
			if(movieList.getCurrentIndex() == 0){
				clearMovieFields();
				updateNumOfMovies();
				currentIndexField.setText("0");
				jb_next.setEnabled(false);
				jb_previous.setEnabled(false);
				jb_go.setEnabled(false);
				jb_enableEdit.setEnabled(false);
				jb_remove.setEnabled(false);
				disableEdits();
			}
			else{
				updateMovieFields(movieList.getCurrent());
				updateNumOfMovies();
				currentIndexField.setText(String.valueOf(movieList.getCurrentIndex()+1));
			}
		}
		else if(e.getSource() == jmi_open){
			JFileChooser jfc = new JFileChooser();
			jfc.addChoosableFileFilter(new mmmFileFilter());
			jfc.showOpenDialog(this);
			activeFile = jfc.getSelectedFile();
			//do open
			openFile(activeFile);
		}
		else if(e.getSource() == jmi_save){
			if(activeFile != null){
				//do save
				writeFile(activeFile);
			}
			else{
				//Show save as instead
				JFileChooser jfc = new JFileChooser();
				jfc.addChoosableFileFilter(new mmmFileFilter());
				jfc.showSaveDialog(this);
				activeFile = jfc.getSelectedFile();
				//do save
				writeFile(activeFile);
			}
			
		}
		else if(e.getSource() == jmi_saveAs){
			JFileChooser jfc = new JFileChooser();
			jfc.addChoosableFileFilter(new mmmFileFilter());
			jfc.showSaveDialog(this);
			activeFile = jfc.getSelectedFile();
			//do save
			writeFile(activeFile);
		}
		else if(e.getSource() == jmi_import){
			ImportMenu.createAndShowGUI();
		}
		
	}
	
	/**
	 * Clears the GUI of movie fields for adding.
	 */
	private void clearMovieFields() {
		jtf_title.setText(null);
		jtf_genre.setText(null);
		jtf_actors.setText(null);
		jtf_rating.setText(null);
		jtf_votes.setText(null);
		jtf_year.setText(null);
	}

	/**
	 * Updates GUI with data from passed movie
	 * @param movie Movie with data to be displayed
	 */
	public void updateMovieFields(Movie movie){
		jtf_title.setText(movie.getTitle());
		jtf_genre.setText(movie.getGenre());
		jtf_actors.setText(movie.getActors());
		jtf_rating.setText(String.valueOf(movie.getRating()));
		jtf_votes.setText(String.valueOf(movie.getVotes()));
		jtf_year.setText(String.valueOf(movie.getYear()));
	}
	
	/**
	 * Update the label for the the movie count
	 */
	public void updateNumOfMovies(){
		countLabel.setText(" / " + (movieList.getSize()));
	}
	
	
	/**
	 * Converts GUI data to object
	 */
	public Movie getMovieFields(){
		String title = jtf_title.getText();
		String genre = jtf_genre.getText();
		String actors = jtf_actors.getText();
		
		try{
			int rating = Integer.parseInt(jtf_rating.getText());
			int votes = Integer.parseInt(jtf_votes.getText());
			int year = Integer.parseInt(jtf_year.getText());
			
			return new Movie(title, genre, actors, rating, votes, year);
		}catch(Exception e){
			JOptionPane.showMessageDialog(null, "Invalid field(s) entered", "Error", JOptionPane.ERROR_MESSAGE);
			return null;
		}
	}
	
	/**
	 * Allows editing of the Movie Fields
	 */
	public void allowEdits(){
		jtf_title.setEditable(true);
		jtf_genre.setEditable(true);
		jtf_actors.setEditable(true);
		jtf_rating.setEditable(true);
		jtf_votes.setEditable(true);
		jtf_year.setEditable(true);
	}
	
	/**
	 * Disables editing of the Movie Fields
	 */
	public void disableEdits(){
		jtf_title.setEditable(false);
		jtf_genre.setEditable(false);
		jtf_actors.setEditable(false);
		jtf_rating.setEditable(false);
		jtf_votes.setEditable(false);
		jtf_year.setEditable(false);
	}
	
	/**
	 * Writes out .mmm file
	 * @param file The file to be written
	 */
	public void writeFile(File file){			
		FileWriter fSaveWriter;
		try{
			// Write new file
			fSaveWriter = new FileWriter(activeFile);
			PrintWriter savePrintWriter = new PrintWriter(fSaveWriter);
			savePrintWriter.println("#title|actors|genre|rating|votes|year");
			//use Iterator for efficiency
			Iterator<Movie> it = movieList.getMovies().iterator();
			while(it.hasNext()){
				savePrintWriter.println(it.next().toMMMRow());
			}
			savePrintWriter.close();
		}catch(IOException e){
			e.printStackTrace();
		}
	}
	
	/**
	 * Open .mmm file
	 * @param file The file to be opened
	 */
	public void openFile(File file){
		FileReader fReader;
		try {
			fReader = new FileReader(file);
			BufferedReader inputFile = new BufferedReader(fReader);
			String line = inputFile.readLine(); // returns null if \n
			// go until end of file
			do{
				line = inputFile.readLine();
				if(line != null){
					//split read line
					//\|(?=([^\"]*\"[^\"]*\")*(?![^\"]*\")) - ignore if pipe inside quotes
					String[] split = line.split("[|]");
					//retrieve data from split array
					//convert to movie and add it.
					movieList.add(new Movie(split[0], split[1], split[2], 
							Integer.parseInt(split[3]), Integer.parseInt(split[4]), Integer.parseInt(split[5])));
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
		jb_next.setEnabled(true);
		jb_previous.setEnabled(true);
		jb_go.setEnabled(true);
		jb_enableEdit.setEnabled(true);
		jb_remove.setEnabled(true);
		updateMovieFields(movieList.getCurrent());
		updateNumOfMovies();
		currentIndexField.setText(String.valueOf(movieList.getCurrentIndex()+1));
	}
	
	/**
	 * Allows the Enter key to serve as 'go' command when in correct field.
	 */
	@Override
	public void keyPressed(KeyEvent k) {
		// 'Go'
		if(currentIndexField.hasFocus() && (k.getKeyCode() == KeyEvent.VK_ENTER)){
			jb_go.doClick();
		}
	}
	@Override
	public void keyReleased(KeyEvent k) {
		// Not required
	}
	@Override
	public void keyTyped(KeyEvent k) {
		// Not required
	}
	
	/**
	 * @author Ian Field
	 * FileFilter for use in the MyMoviesManager application.
	 * File is a Pipe (|) separated variable file, extension ".mmm"
	 */
	class mmmFileFilter extends javax.swing.filechooser.FileFilter {
	    public boolean accept(File file) {
	        String filename = file.getName();
	        return filename.endsWith(".mmm");
	    }
	    public String getDescription() {
	        return "*.mmm";
	    }
	}
	
	/**
	 * Program entry point. Creates and shows the MyMoviesManagerGUI interface.
	 * @param args
	 */
	public static void main(String[] args){
		final MyMoviesManagerGUI viewMenu = new MyMoviesManagerGUI();
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				viewMenu.createAndShowGUI();
			}
		});
	}
}


//try{
//FileInputStream inStream = new FileInputStream(file);	 
//ObjectInputStream iis = new ObjectInputStream(inStream);	 
//movieList.setMovies((ArrayList<Movie>) iis.readObject());
//}
//catch(IOException e){
//e.printStackTrace();
//} catch (ClassNotFoundException e) {
//e.printStackTrace();
//}

//try {
//FileOutputStream outStream = new FileOutputStream(file);
//ObjectOutputStream oos = new ObjectOutputStream(outStream);	 
//oos.writeObject(movieList.getMovies());
//oos.close();
//} catch (IOException e) {
//e.printStackTrace();
//}	