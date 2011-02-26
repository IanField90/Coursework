package uk.ac.reading.ianfield.mmmgui;

import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.Date;
import java.util.zip.GZIPInputStream;

import javax.swing.*;

/**
 * Graphical user interface for the Import menu. Allows managing
 * FTP servers and retrieves download dates for downloaded files if present.
 * @author Ian Field
 */
public class ImportMenu  extends JPanel implements ActionListener{
	private static final long serialVersionUID = -1614345004047086165L;
	private JProgressBar progBar = new JProgressBar();
	private JButton jb_import, jb_retrieve, jb_addFTP, jb_removeFTP , jb_findDownloaded;
	private JComboBox jcb_FTPServers, jcb_FTPServersImport, jcb_files;
	private JTextField jtf_FTPEntry;
	private File ftpConfigFile = new File("ftpConfig.pwn");

	/**
	 * Constructor
	 */
	public ImportMenu(){
		progBar.setValue(0);
		jb_addFTP = new JButton("Add FTP");
		jb_addFTP.addActionListener(this);
		jb_removeFTP = new JButton("Remove FTP");
		jb_removeFTP.addActionListener(this);
		jb_import = new JButton("Import");
		jb_import.addActionListener(this);
		jb_retrieve = new JButton("Retrieve");
		jb_retrieve.addActionListener(this);
		jcb_files = new JComboBox();
		jcb_files.addActionListener(this);
		
		jb_findDownloaded = new JButton("Last Date");
		jb_findDownloaded.addActionListener(this);
	
		jcb_FTPServers = new JComboBox();
		jcb_FTPServersImport = new JComboBox();
		jcb_FTPServersImport.addActionListener(this);
		jcb_FTPServers.addActionListener(this);
		jtf_FTPEntry = new JTextField();
		
		JPanel managePanel = new JPanel();
		managePanel.setLayout(new GridLayout(2,2));
		managePanel.add(jtf_FTPEntry);
		managePanel.add(jb_addFTP);
		managePanel.add(jcb_FTPServers);
		managePanel.add(jb_removeFTP);
		
		JPanel importPanel = new JPanel();
		importPanel.setLayout(new GridLayout(3,2));
		importPanel.add(jcb_FTPServersImport);
		importPanel.add(jb_retrieve);
		importPanel.add(jcb_files);
		importPanel.add(jb_findDownloaded);
		importPanel.add(jb_import);
		importPanel.add(progBar);
		
		JTabbedPane pane = new JTabbedPane();
		pane.addTab("Import", importPanel);
		pane.addTab("Manage", managePanel);	
		add(pane);
		loadFTPConfig();
	}
	
	/**
	 * Loads JComboBoxes with values of previous runs items
	 */
	public void loadFTPConfig(){
		//Each line in file is an FTP server
		FileReader fReader;
		try {
			fReader = new FileReader(ftpConfigFile);
			BufferedReader inputFile = new BufferedReader(fReader);
			String line = inputFile.readLine(); // returns null if \n
			// go until end of file
			while(line != null){
				jcb_FTPServers.addItem(line);
				jcb_FTPServersImport.addItem(line);
				line = inputFile.readLine();
			}
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
	
	/**
	 * Saves values of current JComboBox items for next launch.
	 */
	public void saveFTPConfig(){
		// Save config
		//take each element in jcb_FTPServers and write new line for each
		FileWriter fSaveWriter;
		try{
			// Write new file
			fSaveWriter = new FileWriter(ftpConfigFile);
			PrintWriter savePrintWriter = new PrintWriter(fSaveWriter);
			for(int i = 0; i < jcb_FTPServers.getItemCount(); i++){
				savePrintWriter.println(jcb_FTPServers.getItemAt(i));
			}
			savePrintWriter.close();
		}catch(IOException e){
			e.printStackTrace();
		}
	}
	
	/**
	 * Retrieves file from server
	 * @param server URL of server
	 */
	public void retrieveFromFTP(String server){
		// download filesizes + display them
		String type = ";type=i";
		String file = "filesizes";
		try{
			URL url = new URL(server+file+type);
			URLConnection urlc = url.openConnection();
			InputStream is = urlc.getInputStream();
			BufferedReader bin = new BufferedReader(new InputStreamReader(is));
			String line;
			while((line = bin.readLine()) != null){
				String[] split = line.split(" ");
				jcb_files.addItem(split[0] + " (" + split[1] + " bytes)");
			}	
			bin.close();
			
		} catch (MalformedURLException e1) {
			JOptionPane.showMessageDialog(this, "Invalid FTP address!", "Error", JOptionPane.ERROR_MESSAGE);
		} catch (IOException e1) {
				System.out.println(e1);
				e1.printStackTrace();
		}
	}
	
	/**
	 * Retrieves file from FTP server.
	 * @param server Server which holds the file.
	 * @param file File name with extension to be downloaded.
	 */
	public void downloadFromFTP(String server, String file)//, long size)
	{
		String type = ";type=i";
		try{
			System.out.println(server+file+type);
			URL url = new URL(server+file+type);
			URLConnection urlc = url.openConnection();
			InputStream is = urlc.getInputStream();
			BufferedInputStream bin = new BufferedInputStream(is);
			
			FileOutputStream fout = new FileOutputStream(file);
			
			byte data[] = new byte[1024];
			int cnt, tot=0;
			cnt = bin.read(data);
			while(cnt>0){
				tot += cnt;
				fout.write(data, 0, cnt);
				//progBar.setValue((int) ((tot / size) * 100));
				cnt = bin.read(data);
			}			
			bin.close();
			
		} catch (MalformedURLException e1) {
			JOptionPane.showMessageDialog(this, "Invalid FTP address!", "Error", JOptionPane.ERROR_MESSAGE);
			e1.printStackTrace();
		} catch (IOException e1) {
				e1.printStackTrace();
		}
	}
	
	/**
	 * Saves the date of the most recent downloaded file. 
	 * @param fileName Latest downloaded file
	 */
	public long findDownloadDate(String fileName){
		File file = new File(fileName);
		if(file.exists())
			return file.lastModified();
		else 
			return 0;
	}
	
	/**
	 * Unzips the locally downloaded file.
	 * @param inFileName File name of the zipped file.
	 * @return File name of the unzipped file.
	 */
	public static String gunzipFile(String inFileName)
	{		
		String outFileName = null;
		try{
	    	File inFile = new File(inFileName);
		    GZIPInputStream gzipInputStream = new GZIPInputStream(new FileInputStream(inFile));
		    outFileName = inFileName.replace(".gz", "");
		    OutputStream out = new FileOutputStream(outFileName);
		    byte[] buf = new byte[1024];
		    int len;
		    while ((len = gzipInputStream.read(buf)) > 0)
		        out.write(buf, 0, len);
		 
		    gzipInputStream.close();
		    out.close();
		    //delete uncompressed
		    inFile.delete();
		} catch (IOException e) {
			e.printStackTrace();
		}
	    return outFileName;
	}
	
	/**
	 * Imports the file into the main datastructure missing the first 200 lines in case of 
	 * jargon preceeding the movie data.
	 * @param Name of file to be imported.
	 * */
	private void doImport(String fileName) {
		String regex = "(\\(|\\)|\\/)";	
		FileReader fReader;
		try {
			fReader = new FileReader(new File(fileName));
			BufferedReader inputFile = new BufferedReader(fReader);
			String line = inputFile.readLine(); // returns null if \n
			// go until end of file
			for(int i = 0; i < 200; i++)
				line = inputFile.readLine();
			while(line != null){
				String[] split = line.split(regex);
				MyMoviesManagerGUI.movieList.add(new Movie(split[0]," "," ", 0, 0, 0));
				line = inputFile.readLine();
			}
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

	/**
	 * Processes user interaction with the GUI and responds to events.
	 */
	@SuppressWarnings("deprecation")
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == jb_addFTP){
			jcb_FTPServers.addItem(jtf_FTPEntry.getText());
			jcb_FTPServersImport.addItem(jtf_FTPEntry.getText());
			saveFTPConfig();
		}
		else if(e.getSource() == jb_removeFTP){
			jcb_FTPServers.removeItemAt(jcb_FTPServers.getSelectedIndex());
			jcb_FTPServersImport.removeItemAt(jcb_FTPServersImport.getSelectedIndex());
			saveFTPConfig();
		}
		else if(e.getSource() == jb_retrieve){
			retrieveFromFTP(jcb_FTPServersImport.getSelectedItem().toString());//"ftp://anonymous:na@ftp.fu-berlin.de/pub/misc/movies/database/");
		}
		else if(e.getSource() == jb_findDownloaded){
			String[] split = jcb_files.getSelectedItem().toString().split(" ");
			if(findDownloadDate(split[0]) != 0){
				Date time = new Date(findDownloadDate(split[0]));				
				JOptionPane.showMessageDialog(null, "Last Modified on: " + time.toGMTString());

			}
			else
				JOptionPane.showMessageDialog(null, "File not previously downloaded");
		}
		else if(e.getSource() == jb_import){
			String[] split = jcb_files.getSelectedItem().toString().split(" ");
			String server = jcb_FTPServersImport.getSelectedItem().toString();
			split[0] += ".gz";
			
			//String[] split2 = split[1].split("[0-9]");
			
			downloadFromFTP(server, split[0]);//, Long.parseLong(split2[0]));
			String returnedFile = gunzipFile(split[0]);
			System.out.println(returnedFile);
			doImport(returnedFile);
		}
	}

	/**
	 * Launches the GUI on event dispatcher
	 */
	public static void createAndShowGUI() {
		JFrame frame = new JFrame("Import Menu");
		ImportMenu panel = new ImportMenu();
		frame.add(panel);
		frame.setPreferredSize(new Dimension(800,300));
		frame.pack();
		frame.setVisible(true);
	}
}