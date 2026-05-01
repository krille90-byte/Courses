package laboration4_Test3;

import javax.swing.*;
import javax.swing.Timer;
import javax.swing.text.Position;

import java.util.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Ball extends Sprite {
	
	private Leaderboard leaderboard;
	private  Player player;
	private Enemy enemy;
	private Rectangle ballRect = new Rectangle(400,200,26,26);
	private Rectangle endRect;
	private int xspeed, yspeed;
	private int delay = 0;
	private int life = 3;
	private int points;

public Ball(int x, int y, int width, int height, Player player, Enemy enemy) {
	super(x, y, width, height);
	this.player = player;
	this.enemy = enemy;
	setXspeed(-5);
	setYspeed(-5);
	//lives();
	}

private void bounce() {														//Lagts till 2022-02-14
	if(getX()<=0) {
		setXspeed(-getXspeed());
	}
	if(getX()+getWidth()>800) {
		setXspeed(-getXspeed());
	}	
	if(getY()<=0) {
		setYspeed(-getYspeed());
	}	
	if(getY()+getHeight()>650) {
		setYspeed(-getYspeed());	
	}
}

public void paddleCol() {
	//System.out.println(getBallRect());							//DEBUG Get ball position
	if(getBallRect().intersects(player.getRect()) && delay<=0) {
		delay = 20;
		setYspeed(getYspeed() * -1);
	}
	
}
public void lives() {
	if(getBallRect().intersects(endRect) && delay <= 0) {
		
		setLife(getLife() - 1);
		delay = 40;
		//setBallRect(new Rectangle());
		setX(440);
		setY(520);
	}
}
@Override
public void update(Keyboard keyboard) {
setBallRect(new Rectangle(getX(),getY(),getWidth(),getHeight()));
endRect = new Rectangle(0,650,800,650);
setX(getX()-getXspeed());
setY(getY()-getYspeed());
delay--;
		
paddleCol();
bounce();
lives();

	//leaderboard.update(keyboard);

}
	@Override
	public void draw(Graphics2D graphics) {
		
		graphics.setColor(Color.GREEN);
		graphics.fillOval(getX(), getY(), getWidth(), getHeight());
		
		graphics.setColor(Color.CYAN);
		graphics.drawRect(0, 540, 100, 50);
		graphics.setColor(Color.RED);
		graphics.drawString(String.valueOf("Points: "+getPoints()),25,580);
		graphics.setColor(Color.CYAN);
		graphics.drawString(String.valueOf("Lives: " + getLife()), 25, 560);
		
		
	}
	public Rectangle getRect() {
		return this.getBallRect();
	}

	public int getYspeed() {
		return yspeed;
	}

	public void setYspeed(int yspeed) {
		this.yspeed = yspeed;
	}

	public int getPoints() {
		return points;
	}

	public void setPoints(int points) {
		this.points = points;
	}

	public Rectangle getBallRect() {
		return ballRect;
	}

	public void setBallRect(Rectangle ballRect) {
		this.ballRect = ballRect;
	}

	public int getXspeed() {
		return xspeed;
	}

	public void setXspeed(int xspeed) {
		this.xspeed = xspeed;
	}

	public int getLife() {
		return life;
	}

	public void setLife(int life) {
		this.life = life;
	}
}
	

