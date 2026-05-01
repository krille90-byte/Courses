package laboration4_Test3;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.swing.DefaultListModel;

public class ScoreLista {
	
	private DefaultListModel dlm;
	private static List<List> Rank = new ArrayList<List>(10);
	private ArrayList<Integer> TheScore = new ArrayList(10);
	private ArrayList<String> Names = new ArrayList();
	private String[] namnen = {" LOP1", " LOW2"," HEY3"," NIO4"," UPS5"," AWF6"," HFS7"," HSD8"," YUP9","AHF10"};
	private int[] poang = {3000,2750,2500,2250,2000,750,500,350,200,0};
	
	public ScoreLista()
		{
			dlm = new DefaultListModel();
			
			Names.add("LOP1");				TheScore.add(3000); //100
			Names.add("LOW2");				TheScore.add(2750); //200
			Names.add("HEY3");				TheScore.add(2500); //350
			Names.add("NIO4");				TheScore.add(2250); //500
			Names.add("UPS5");				TheScore.add(2000); //750
			Names.add("AWF6");				TheScore.add(750); //2000
			Names.add("HFS7");				TheScore.add(500); //2250
			Names.add("HGB8");				TheScore.add(350); //2500
			Names.add("YUP9");				TheScore.add(200); //2750
			Names.add("WTF10");				TheScore.add(100); //3000
			
			//dlm.add(0, "      HighScoreLista:");
			//String[] namnen = {" LOP1", " LOW2"," HEY3"," NIO4"," UPS5"," AWF6"," HFS7"," HSD8"," YUP9","AHF10"};
			//int[] poang = {3000,2750,2500,2250,2000,750,500,350,200,0};
			//for(int i = 0; i < 10; i++) {
			//	dlm.add(i,(i+1)+". "+namnen[i]+" "+poang[i]);
				
			//}
			for(int i = 0; i < TheScore.size(); i++) {
				dlm.add(i, (i+1)+". "+Names.get(i)+" "+TheScore.get(i));
			}
			if(!dlm.isEmpty()) {
				dlm.add(0, "      HighScoreLista:");
			}
		
		}
		
			public void add(Integer score, String annan)
			{
				dlm.removeAllElements();
				
				for(int i = 0; i < TheScore.size(); i++) {
					dlm.add(i, (i+1)+". "+Names.get(i)+" "+TheScore.get(i));
				}
				
				//Checking if it is greater or not
				for(int i = 0; i < 10 ; i++) {
					
					if(score > TheScore.get(0)) {
						
						for(int j = 0; j <= 9; j++) {
							TheScore.get(j);
							TheScore.set(j, TheScore.get(j));
							j++;
						}
						
						TheScore.set(0, score);
						Names.set(0, annan);
					}
					
				}
				
				
																				//Ta bort allt i listan och sen lägg till på nytt
				if(!dlm.isEmpty()) {
					dlm.add(0, "      HighScoreLista:");
				}
			}
			
					public DefaultListModel getList()
					{
						return dlm;
					}

					public static List<List> getRank() {
						return Rank;
					}

					public void setRank(List<List> rank) {
						Rank = rank;
					}
}
