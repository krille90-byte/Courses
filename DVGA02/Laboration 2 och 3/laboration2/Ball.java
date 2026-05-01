package laboration2;

import java.awt.Color;
import java.awt.Graphics2D;

public class Ball extends Sprite {

	public Ball(int x, int y, int width, int height) {
		super(x, y, width, height);
		
	}

	@Override
	public void update(Keyboard keyboard) {
		if(keyboard.isKeyDown(Key.Left) && keyboard.isKeyDown(Key.Down)) {
			this.setX(getX()-5);
			this.setY(getY()+5);
		}else if(keyboard.isKeyDown(Key.Right) && keyboard.isKeyDown(Key.Down)) {
			setX(getX()+5);
			setY(getY()+5);
		}
		else if(keyboard.isKeyDown(Key.Left) && keyboard.isKeyDown(Key.Up)) {
			setX(getX()-5);
			setY(getY()-5);
		}
		else if(keyboard.isKeyDown(Key.Right) && keyboard.isKeyDown(Key.Up)) {
			setX(getX()+5);
			setY(getY()-5);
		}
		else if(keyboard.isKeyDown(Key.Right)) {
			this.setX(getX()+5);
		}
		else if(keyboard.isKeyDown(Key.Left)) {
			this.setX(getX()-5);
		}
		else if(keyboard.isKeyDown(Key.Down)) {
			this.setY(getY()+5);
		}
		else if(keyboard.isKeyDown(Key.Up)) {
			this.setY(getY()-5);
		}
		else if(keyboard.isKeyDown(Key.Left)) {
			this.setX(getX()-5);
		}
		
	}

	@Override
	public void draw(Graphics2D graphics) {
		graphics.setColor(Color.red);
		graphics.fillOval(getX(), getY(), getWidth(), getHeight());
		
	}

}
