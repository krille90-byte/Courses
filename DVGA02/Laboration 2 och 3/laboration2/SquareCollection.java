package laboration2;

import java.awt.*;

public class SquareCollection extends ColoredBox {
	
	public SquareCollection(int x, int y, int width, int height) {
		super(x, y, width, height, Color.CYAN);
		
	}

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



}
