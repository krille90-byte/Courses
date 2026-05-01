package laboration4_Test3;

import java.util.ArrayList;
import java.util.Collections;

public class Points {
private int store = Game.getPoints();
private Game spel;

private static ArrayList<Integer> MyPoint = new ArrayList();
private static int sparaPoints;

		public Points() {
		GetThis();
		save();
		change();
		}
		public static int GetThis() {
			sparaPoints = Game.getPoints();
			System.out.println(sparaPoints);			//DEBUG
			return sparaPoints;
		}
		static void save() {
			Integer storeInt = 0;
			MyPoint.add(0, sparaPoints);
			System.out.println(MyPoint);				//DEBUG
			for(int Sum = 1; Sum <= MyPoint.size(); Sum++) {
				if(Sum>2) {
				MyPoint.remove(Sum-1);
				}
				Program.latest.add(Sum+". "+MyPoint);
				System.out.println(MyPoint);
				storeInt = MyPoint.get(0);
			}
			
			
			
			/*for(int i = 0; i < 1; i++) {
				System.out.println(storeInt);
				Program.latest.add(i+". "+storeInt);
			}*/
			
			//Collections.sort(MyPoint);
			//System.out.println("Sorted: "+MyPoint);		//Accending order
			//Collections.reverse(MyPoint);
			//System.out.println("Test: "+MyPoint);		//Deccending order
		}
		public static void Print() {
			int run = 1;
			int Sum = 1;
			/*for(int i = 0; i < 1; i++) {
				Program.latest.add(Sum+". "+sparaPoints);
				Sum++;
			
				System.out.println("DEBUG: "+Sum+" "+sparaPoints);
				
				GameBoard.ResetGame();
			}*/
			
			
	}
		public static void change() {
			
			
		}
}
