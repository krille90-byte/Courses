package laboration3;

import java.awt.*;

public class Bat extends Sprite{
private Rectangle batRect;
	public Bat(int x, int y, int width, int height) {
		super(x, y, width, height);
		
	//	batRect = new Rectangle(getX(),getY(),getWidth(),getHeight());
	//	getRect();
	}

	@Override
	public void update(Keyboard keyboard) {
		batRect = new Rectangle(getX(),getY(),getWidth(),getHeight());
		if(keyboard.isKeyDown(Key.Right)) {
			if(getX() >= 695) {
				setX(695);
			}else
			setX(getX()+10);
		}
		if(keyboard.isKeyDown(Key.Left)) {
			if(getX() <= 0) {
				setX(0);
			}else
			setX(getX()-10);
		}
		
	}

	@Override
	public void draw(Graphics2D graphics) {
		graphics.setColor(Color.red);
		graphics.fillRect(getX(), getY(), getWidth(), getHeight());
		
		
	}
	public Rectangle getRect() {										//hämtar rektangeln
		return this.batRect;
	}
}
