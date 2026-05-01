package laboration4_Test3;

import java.awt.Color;
import java.awt.Graphics2D;
import java.util.Random;
public class RedBox extends ColoredBox {


	public RedBox(int x, int y, int width, int height) {
		super(x, y, width, height, Color.red);
		
	}

	public static void main(String[] args) {
		
	}

	@Override
	public void update(Keyboard keyboard) {
		Random random = new Random();
		setY(getY()+2);
		
		
	}

}
