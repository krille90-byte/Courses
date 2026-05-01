package laboration3_Fast_kollision_i_klasser;

import java.awt.*;
import java.util.*;

public class Game {
private Integer antalBollar = 1;
private SquareCollection sq;
private Bat slagtra;
private Random rand = new Random();
private ArrayList<Ball> balls = new ArrayList<Ball>(antalBollar);
private ArrayList<SquareCollection> col = new ArrayList<SquareCollection>();
private Integer delay = 0;
	public Game(GameBoard board) {

		slagtra = new Bat(400,575,105,10);
		
		for(int i = 0; i < antalBollar; i++) {
			getBalls().add(new Ball(rand.nextInt(500)+200,rand.nextInt(300)+200,20,20,slagtra,sq,this));
		//getBalls().add(new Ball(250,550,20,20,slagtra,sq,this));
		}	
		for(int j = 1; j < 14; j++) {			
			getCol().add(new SquareCollection(20+j*50,40+15,47,26));
			getCol().get(j-1).setHP(rand.nextInt(3)+1);
			}
		for(int j = 1; j < 14; j++) {			
			getCol().add(new SquareCollection(20+j*50,70+13,47,26));
			getCol().get(j+12).setHP(rand.nextInt(3)+1);
			}
		for(int j = 1; j < 14; j++) {
			getCol().add(new SquareCollection(20+j*50,100+10,47,26));
			getCol().get(j+25).setHP(rand.nextInt(3)+1);
		}
			
	}

	public void update(Keyboard keyboard) {
		
		slagtra.update(keyboard);
		for(SquareCollection s: getCol()) {
			s.update(keyboard);
			}
		for(Ball b : getBalls()) {
			b.update(keyboard);
		}		
		
		if(col.isEmpty()) {
			System.out.println("There's no more bricks now.. boss.");
		}

		
	}

	public void draw(Graphics2D graphics) {
		//boll.draw(graphics);
		for(Ball b : balls) {
			b.draw(graphics);
		}
		try {
		for(SquareCollection s: col) {
			s.draw(graphics);
			}
		}catch(java.util.ConcurrentModificationException e) {
			System.out.println("/////////");
			System.out.println("PROBLEM: ");
			System.out.println(e);
			System.out.println("/////////");
			System.out.println("/////////");
		}
		
		slagtra.draw(graphics);
	}

	public ArrayList<SquareCollection> getCol() {
		return col;
	}

	public void setCol(ArrayList<SquareCollection> col) {
		this.col = col;
	}

	public ArrayList<Ball> getBalls() {
		return balls;
	}

	public void setBalls(ArrayList<Ball> balls) {
		this.balls = balls;
	}

}

/*	//GAMMAL KOD//
 * 
 * //		if(keyboard.isKeyDown(Key.M) && delay <= 0) {
//			delay = 20;
//			antalBollar += 1;
			//System.out.println("Antal bollar: "+antalBollar);
//			getBalls().add(new Ball(rand.nextInt(500)+200,rand.nextInt(300)+200,20,20,slagtra,sq));
//		}
*/
