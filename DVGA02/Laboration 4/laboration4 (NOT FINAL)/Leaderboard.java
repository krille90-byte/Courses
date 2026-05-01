package laboration4_Test3;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.util.ArrayList;

import javax.swing.JFrame;

public class Leaderboard extends Sprite {
Ball ball;
ScoreHandler scorehandler;
GameBoard board;
//private boolean goNext = false;
ArrayList<Game> leaderBoard = new ArrayList<>();
private Rectangle leaderRect  = new Rectangle(getX(),getY(),getWidth(),getHeight());
	public Leaderboard(int x, int y, int width, int height) {
		super(x, y, width, height);
		
	}

	
	
	public String Leaderboard() {
		//System.out.println("PRINTED OUT!");			//TEST
		//return Leaderboard();
		return null;
	}
	public void move() {
		if(getY() < 50) {
			setY(getY()+2);
		}
		/*else if(getY() == 50 && goNext == false ) {
			this.board.ResetGame();
			goNext = true;
		}*/
	}
	
	@Override
	public void update(Keyboard keyboard) {
		setLeaderRect(new Rectangle(getX(),getY(),getWidth(),getHeight()));
		move();
		//setY(getY()+2);
		Leaderboard();
		
	}

	@Override
	public void draw(Graphics2D graphics) {
		graphics.setFont(new Font("TimesRoman", Font.PLAIN,20));
		graphics.setColor(Color.CYAN);
		graphics.fillRect(getX(), getY(), getWidth(), getHeight());
		graphics.setColor(Color.RED);
		graphics.drawRect(getX(), getY(), getWidth(), getHeight());
		graphics.setColor(Color.white);
		graphics.fillRect(getX()+10, getY()+10, 380, 480);
		graphics.setColor(Color.red);
		graphics.drawString("  Name: ", getX()+10, getY()+40);
		graphics.setColor(Color.red);
		graphics.drawString("  Points: ", getX()+140, getY()+40);
		graphics.setColor(Color.red);
		graphics.drawString("  Date: ", getX()+270, getY()+40);
		
		//graphics.setColor(Color.ORANGE);
		
	}



	public Rectangle getLeaderRect() {
		return this.leaderRect;
	}



	public void setLeaderRect(Rectangle leaderRect) {
		this.leaderRect = leaderRect;
	}
}
