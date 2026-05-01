package laboration4_Test3;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.util.ArrayList;

public class Enemy extends Sprite {

private Rectangle enemyRectangle;
//private ArrayList<Color> colors;
private Color color;
private int HP;
//public int points;

	public Enemy(int x, int y, int width, int height) {
		super(x, y, width, height);	
	
	setHP(1);
	health();
	
	
	}
	
	private void health() {
	
	switch (getHP()) {
	case 1:
		color = Color.green;
		
		break;
	case 2:
		color = Color.orange;
		
		break;
	case 3:
		color = Color.red;
		
		break;
	default:
		//color = Color.LIGHT_GRAY;
	}
}
	

	@Override
	public void update(Keyboard keyboard) {
	enemyRectangle = new Rectangle(getX(),getY(),getWidth()+1,getHeight()+1);
	health();
	
	}

	@Override
	public void draw(Graphics2D graphics) {
		graphics.setColor(color);
		graphics.fillRect(getX(), getY(), getWidth(), getHeight());
		
	}
	
	public Rectangle getRect() {
		return this.enemyRectangle;
	}

	public int getHP() {
		return HP;
	}

	public void setHP(int hP) {
		HP = hP;
	}
}
