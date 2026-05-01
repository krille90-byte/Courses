package laboration4_Test3;

import java.awt.Color;

public class BlueBox extends ColoredBox{
	
	public BlueBox(int x, int y, int width, int height) {
		super(x, y, width, height, Color.blue);
	
	}

	public static void main(String[] args) {

	}

	@Override
	public void update(Keyboard keyboard) {
		
		setY(getY()+1);
	}


}
