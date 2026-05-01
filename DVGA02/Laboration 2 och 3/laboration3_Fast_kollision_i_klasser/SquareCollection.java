package laboration3_Fast_kollision_i_klasser;

import java.awt.*;
import java.util.ArrayList;

public class SquareCollection extends Sprite {
	private Rectangle boxRect;
	private int HP;
	private Color color;
	//////
	private int boxX;
	private int boxY;
	private int boxWidth;
	private int boxHeight;
	//////
	public SquareCollection(int x, int y, int width, int height) {
		super(x, y, width, height);
		this.boxX = x;
		this.boxY = y;
		this.boxWidth = width;
		this.boxHeight = height;
		
		setHP(1);
		health();
	}

	@Override
	public void update(Keyboard keyboard) {
		
		boxRect = new Rectangle(getX(),getY(),getWidth(),getHeight());
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
	public void draw(Graphics2D graphics) {
		graphics.setColor(color);
		graphics.fillRect(getX(), getY(), getWidth(), getHeight());
		
	}

	public Rectangle getRect() {										//hämtar rektangeln
		return this.boxRect;
	}

	public int getHP() {
		return HP;
	}

	public void setHP(int hP) {
		HP = hP;
	}

}
/*
@Override
public void update(Keyboard keyboard) {
	for(int i = 0; i < 1; i++) {
	if(getY()==575) {
		System.out.println("Nått botten");
		System.exit(i);
		break;
	}else {
	this.setY(getY()+1);
	}
	}
}
*/