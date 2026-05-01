package laboration4_Test3;

import java.awt.Color;
import java.awt.Graphics2D;

public class ColoredBox extends Sprite {
	
	private Color color;
	public ColoredBox(int x, int y, int width, int height, Color
	color) {
	super(x, y, width, height);
	this.color = color;
	
	}
	

	public static void main(String[] args) {

	}

	@Override
	public void update(Keyboard keyboard) {
		
	}

	@Override
	public void draw(Graphics2D graphics) {
		graphics.setColor(color);
		graphics.fillRect(getX(),getY(),getWidth(),getHeight());
	}

}
