package laboration2;
import java.awt.Color;
import java.awt.Graphics2D;
import java.util.*;

public class Game {
private Integer size = 10;	
//Tester//////////////////////
private Integer tickcount = 0;
private Integer xvar = -20;
private Integer yvar = 25;
/////////////////////////////
private Ball boll = new Ball(400,575,25,25);
ArrayList<SquareCollection> col = new ArrayList<SquareCollection>(size);
	public Game(GameBoard board) {
		for(int j = 1; j <= 10; j++) {
			col.add(new SquareCollection(-20+j*50,25,25,25));
			}

	}

	public void update(Keyboard keyboard) {
		for(SquareCollection s: col) {
			s.update(keyboard);
			}
		boll.update(keyboard);
		
	}

	public void draw(Graphics2D graphics) {
		
		for(SquareCollection s: col) {
			s.draw(graphics);
			}
		boll.draw(graphics);
		
	}

}
/*	public void update(Keyboard keyboard) {
		rbox.update(keyboard);
		System.out.println(tickcount);
		tickcount += 1;
		if(tickcount % 40 == 0) {
			size += 1;
			for(int j = 0; j < size; j++) {
			bboxes.add(new Bluebox(xvar+j*50,yvar,25,25));
			}
			
		}
		
	}*/
