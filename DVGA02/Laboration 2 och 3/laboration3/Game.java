package laboration3;

import java.awt.*;
import java.util.*;

public class Game {
private Integer size = 10;
private Integer antalBollar = 1;
private SquareCollection sq;
private Bat slagtra;
private Random rand = new Random();
private ArrayList<Ball> balls = new ArrayList<Ball>(antalBollar);
private ArrayList<SquareCollection> col = new ArrayList<SquareCollection>(size);
private Integer delay = 0;
	public Game(GameBoard board) {

		slagtra = new Bat(400,575,105,10);
		
		for(int i = 0; i < antalBollar; i++) {
			getBalls().add(new Ball(rand.nextInt(500)+200,rand.nextInt(300)+200,20,20,slagtra,sq));
		}
		
		
		for(int j = 1; j < 14; j++) {			
			getCol().add(new SquareCollection(20+j*50,40+15,47,25));
			getCol().get(j-1).setHP(rand.nextInt(3)+1);
			}
		for(int j = 1; j < 14; j++) {			
			getCol().add(new SquareCollection(20+j*50,70+13,47,25));
			getCol().get(j+12).setHP(rand.nextInt(3)+1);
			}
		for(int j = 1; j < 14; j++) {
			getCol().add(new SquareCollection(20+j*50,100+10,47,25));
			getCol().get(j+25).setHP(rand.nextInt(3)+1);
		}
			
	}

	public void update(Keyboard keyboard) {
		
		slagtra.update(keyboard);
		for(Ball b : getBalls()) {
			b.update(keyboard);
		}
		for(SquareCollection s: getCol()) {
			s.update(keyboard);
			}
		
		//Logik
		
		if(!col.isEmpty()) {
		
		for(int i = 0; i < getBalls().size(); i++) {
		for(int j = 0; j < getCol().size(); j++) {
			if(getBalls().get(i).getBallRect().intersects(getCol().get(j).getRect()) && delay <= 0) {
				//delay = 9;
				if(getBalls().get(i).getBallRect().getX() + 1 >= (getCol().get(j).getX()+getCol().get(j).getWidth())) {
					delay = 6;
					getBalls().get(i).setxSpeed(getBalls().get(i).getxSpeed() *-1);
					System.out.println("Ball x is greater than brick(x+width)");
					if(getCol().get(j).getHP() < 3) {
						getCol().get(j).setHP(getCol().get(j).getHP() + 1);
					}
						else {
						getCol().remove(getCol().get(j));
						}
				}
			else if(getBalls().get(i).getBallRect().getX() + 12 <= getCol().get(j).getRect().getX() || getBalls().get(i).getBallRect().getX() +1 >= (getCol().get(j).getRect().getX() + getCol().get(j).getRect().getWidth()) || getBalls().get(i).getBallRect().getX() + 15 <= getCol().get(j).getRect().getWidth()) {
				
					delay = 6;
					getBalls().get(i).setxSpeed(getBalls().get(i).getxSpeed() *-1);
					System.out.println(getBalls().get(i).getxSpeed());
					if(getCol().get(j).getHP() < 3) {
					getCol().get(j).setHP(getCol().get(j).getHP() + 1);
					}
					else {
					getCol().remove(getCol().get(j));
					}
				}
				else {
					delay = 6;
			
					
					getBalls().get(i).setySpeed(getBalls().get(i).getySpeed() *-1);
					System.out.println(getBalls().get(i).getySpeed());
					if(getCol().get(j).getHP() < 3) {
						getCol().get(j).setHP(getCol().get(j).getHP() + 1);
					}
						else {
						getCol().remove(getCol().get(j));
						}
				}
			}
			
			
		}
		
		}
		
		
		
		if(keyboard.isKeyDown(Key.M) && delay <= 0) {
			delay = 20;
			antalBollar += 1;
			//System.out.println("Antal bollar: "+antalBollar);
			getBalls().add(new Ball(rand.nextInt(500)+200,rand.nextInt(300)+200,20,20,slagtra,sq));
		}
		
		}
		else if(col.isEmpty()) {
			System.out.println("There's no more bricks now.. boss.");
		}
		--delay;
		
	}

	public void draw(Graphics2D graphics) {
		//boll.draw(graphics);
		for(Ball b : balls) {
			b.draw(graphics);
		}
		for(SquareCollection s: col) {
			s.draw(graphics);
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

