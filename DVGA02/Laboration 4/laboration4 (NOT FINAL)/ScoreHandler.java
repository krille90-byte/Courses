package laboration4_Test3;

import java.awt.Graphics2D;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.Writer;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class ScoreHandler {

private Game game;
private boolean tryAndDo = true;
private boolean goNext = false;
private boolean NextAgain = true;
private boolean lockThis = false;
	public ScoreHandler(Game game) {
		this.game = game;
		
		
			
	}
	
	
	public void update() {
		
		doThis();
		read();
		
		//newTry();
		//sorting();
		//tryThisNow();
	
}
	public void doThis() {
		if(tryAndDo == true) {
			//Boolean för att stänga inmatningen senare.
			File filNamn = new File("AllIn.txt");
			//ANVÄNDS EJ!
			Date today = new Date();
			//Variabel för datum
			long datum_too = today.getTime();
			//läser in Tid/Datum
			String PointsAndNames = " ";
			//Sträng variabel för utmatningen
			String names = " ";
			//Sträng variabel för namn som vi senare använder för att få ut vårt namn till vår fil.
			ArrayList<String> namePoints = new ArrayList<String>();
			//ANVÄNDS EJ!
			ArrayList<String> aList = new ArrayList<String>();
			//ArrayListan vi använder för att spara namnen
			names = JOptionPane.showInputDialog("[DEBUG] Name: ");
			//InmatningsFält för att skriva in vårt namn
			aList.add(names);
			//Lägger till namnet vi matade in till vår aList
			try {
				FileWriter fw = new FileWriter(filNamn.getAbsoluteFile(),true);
				//Vår utmatare som skriver in poäng,namn,datum till vår fil "MyPoints.txt"
				for(int i = 0; i < PointsAndNames.length(); i++) {
				//For loopen som lägger till allt till vår fil
				fw.write(game.getPoints()+" "+names.toUpperCase()+" "+ today+"\n");
				//Det som faktiskt läggs till.	
					
				}
				System.out.println("Writing Successful!");
				//Skriver ut i konsolen om det gick.
				
				fw.close();
				//Stänger vår utmatare.
				
				tryAndDo = false;
				//Stänger update 
			} catch (IOException e) {
				System.out.println("Ett fel har uppstått i doThis");
				e.printStackTrace();
			}
		}
		
	}	
	public void read() {
		if(goNext == false) {
		char[] array = new char[900];
		//char array2[] = {5,0,0,1,0,0,2,0,0,0};
		List<String> arrayList = new ArrayList<> ( Arrays.asList ( " " , " " , " ", " " , " " , " ", " " , " " , " ", " " ));
		//ANVÄNDS EJ!
		try {
			
			FileReader fr = new FileReader("AllIn.txt");
			fr.read(array);
			System.out.println("\nData in the File(AllIn.txt): ");
			System.out.println(array);
			fr.close();
			
			goNext = true;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	}
	/*public void PointsToBoard() {
		int points = game.getPoints();
		ArrayList<Integer> listan = new ArrayList<Integer>(10);
		
	}*/
	public void newTry() {
		if(NextAgain == true) {
		 try {
		        String content = game.getPoints()+"\n";

		        File file2 = new File("NextTry.txt");

		        // if file doesnt exists, then create it
		        if (!file2.exists())
		            file2.createNewFile();

		        FileWriter fw = new FileWriter(file2.getAbsoluteFile(),true);
		        
		        BufferedWriter bw = new BufferedWriter(fw);
		        bw.write(content);
		        bw.close();
		        NextAgain = false;
		    } catch (IOException e) {
		        e.printStackTrace();
		    }
		}
	}
	public void sorting() {
		String[] lista = new String[100];
		int count = 0;
		String content = game.getPoints()+"\n";
		if(lockThis == false) {
		try {
			BufferedReader let = new BufferedReader(new FileReader(content));
			while(let.ready()){
				String item = let.readLine();
				lista[count] = item;
				count = count + 1;
			}
			let.close();
			
			sort(lista,count);
			//Writes sorted Strings back into the file
			PrintWriter output = new PrintWriter(new FileWriter(content));
				for(int x = 0; x < count; x = x + 1) {
					output.println(lista[x]);
				}
				output.close();
				lockThis = true;
		} catch (IOException ex) {
			System.out.println(ex.toString());
		}
	}
}
	public void sort(String[] lista,int count) {
		for(int pass = 0; pass < count; pass = pass + 1) {
			for(int p = 0; p < count-1; p = p + 1) {
				if(lista[p].compareTo(lista[p+1]) > 0) {
					String Temp = lista[p];
					lista[p] = lista[p+1];
					lista[p+1] = Temp;
				}
			}
		}
	}

	public void draw(Graphics2D graphics) {
		// TODO Auto-generated method stub
		
	}
	
}
