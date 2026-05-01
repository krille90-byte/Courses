package laboration4_Test3;

import java.awt.Color;
import java.awt.Graphics2D;

public class GreenBox extends ColoredBox {


	public GreenBox(int x, int y, int width, int height) {
		super(x, y, width, height, Color.green);
	}

	public static void main(String[] args) {

	}

	@Override
	public void update(Keyboard keyboard) {
		setY(getY()+1);
	}

//	@Override
//	public void draw(Graphics2D graphics) {
//		//graphics.setColor(color);
//		graphics.fillRect(x+440, y, 20, 20);
//	}

}
