package laboration3;

import java.awt.*;
import java.awt.geom.Ellipse2D;

public class Ball extends Sprite {
private Integer xSpeed;
private Integer ySpeed;
private SquareCollection boxes;
private Bat bat;
private Ellipse2D ballRect;
private Integer delay = 0;
	public Ball(int x, int y, int width, int height, Bat bat, SquareCollection sc) {
		super(x, y, width, height);
		this.bat = bat;
		this.boxes = sc;
		setxSpeed(5/2);
		setySpeed(5/2);
			
	}

	
	@Override
	public void update(Keyboard keyboard) {
		setBallRect(new Ellipse2D.Double(getX(),getY(),getWidth(),getHeight()));
		bounce();
		
		if(getBallRect().intersects(bat.getRect()) && delay <= 0) {
		delay = 20;
		ySpeed *= -1;
		System.out.println("Paddle: Hit!");
			
		}
	/*	if(getBallRect().intersects(boxes.getRect()) && delay <= 0) {
			delay = 20;
			ySpeed *= -1;
			xSpeed *= -1;
		}*/
		delay--;
	}
	public void bounce() {
		setX(getX()-xSpeed);
		setY(getY()-ySpeed);
		if(getX() <= 0) {
			xSpeed *= -1;
		}
		if(getX() >= 775) {
			xSpeed *= -1;
		}
		if(getY()<=0) {
			ySpeed *= -1;
		}	
		if(getY() >= 575) {	//Ändrad fr. 575 -> 565
			ySpeed *= -1;	
		}
		
	}
	
	@Override
	public void draw(Graphics2D graphics) {
		graphics.setColor(Color.red);
		graphics.fillOval(getX(), getY(), getWidth(), getHeight());
		
	}
	public Integer getxSpeed() {
		return xSpeed;
	}

	public void setxSpeed(Integer xSpeed) {
		this.xSpeed = xSpeed;
	}

	public Integer getySpeed() {
		return ySpeed;
	}

	public void setySpeed(Integer ySpeed) {
		this.ySpeed = ySpeed;
	}


	public Ellipse2D getBallRect() {
		return ballRect;
	}


	public void setBallRect(Ellipse2D ballRect) {
		this.ballRect = ballRect;
	}

}

/*private void bounce() {
		if(getX()<=0) {
			setX(-getX());
		}
		if(getX()+getWidth()>800) {
			setX(-getX());
		}	
		if(getY()<=0) {
			setY(-getY());
		}	
		if(getY()+getHeight()>650) {
			setY(-getY());	
		}
	}
*/
/*
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
*/
