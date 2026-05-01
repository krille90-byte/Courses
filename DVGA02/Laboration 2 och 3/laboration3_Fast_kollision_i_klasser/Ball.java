package laboration3_Fast_kollision_i_klasser;

import java.awt.*;
import java.awt.geom.Ellipse2D;



public class Ball extends Sprite {
private Integer xSpeed;
private Integer ySpeed;
//private SquareCollection boxes;
private Bat bat;
private Ellipse2D ballRect;
private Integer delay = 0;
private Integer antalBollar = 1;
//private ArrayList<SquareCollection> col = new ArrayList<SquareCollection>();
private Game game;

	public Ball(int x, int y, int width, int height, Bat bat, SquareCollection sc, Game game) {
		super(x, y, width, height);
		this.bat = bat;
		//this.boxes = sc;
		this.game = game;
		setxSpeed(2);
		setySpeed(2);
		
	
			
	}

	
	@Override
	public void update(Keyboard keyboard) {
		setBallRect(new Ellipse2D.Double(getX(),getY(),getWidth(),getHeight()));
		bounce();
		
		if(ballRect.intersects(bat.getRect()) && delay <= 0) {
		delay = 20;
		ySpeed *= -1;
		System.out.println("Paddle: Hit!");
			
		}
//		System.out.println(ballRect.getY());	//DEBUG FÖR ATT KOLLA Y-värdet.
//		System.out.println(ballRect.getX());	//DEBUG FÖR ATT KOLLA X-värdet.
		for(int i = 0; i < antalBollar; i++) {
			for(int j = 0; j < game.getCol().size(); j++) {
			if(ballRect.intersects(game.getCol().get(j).getRect()) && delay <= 0) {
			//delay = 6;
				System.out.println(ballRect.getY());	//DEBUG FÖR ATT KOLLA Y-värdet.
				System.out.println(ballRect.getX());	//DEBUG FÖR ATT KOLLA X-värdet.
			
			
			if(ballRect.getX() + 3  >= (game.getCol().get(j).getRect().getX()+game.getCol().get(j).getRect().getWidth())) {
				delay = 9/2;
				setxSpeed(getxSpeed()*-1);
				System.out.println("Ball x is greater than brick(x+width)");
				if(game.getCol().get(j).getHP() < 3) {
					game.getCol().get(j).setHP(game.getCol().get(j).getHP() + 1);
				}
				else {
					game.getCol().remove(game.getCol().get(j));
					//getCol().remove(j);
					}
			}
			
			else if(ballRect.getX() + 14 <= game.getCol().get(j).getRect().getX()) {
				delay = 9/2;
				setxSpeed(getxSpeed()*-1);
				System.out.println("Ball x is lesser than brick(x+width)");
				if(game.getCol().get(j).getHP() < 3) {
					game.getCol().get(j).setHP(game.getCol().get(j).getHP() + 1);
				}
				else {
					game.getCol().remove(game.getCol().get(j));
					//getCol().remove(j);
					}
				
			}		//Kollision med Y-Min(Toppen av brickan)
			else if(ballRect.getY()+ballRect.getHeight()  <= (game.getCol().get(j).getRect().getY()+game.getCol().get(j).getRect().getHeight()) - 10) {
				System.out.println("Y-Värde(-)");
				delay = 6;
				setySpeed(getySpeed()*-1);
				if(game.getCol().get(j).getHP() < 3) {
					game.getCol().get(j).setHP(game.getCol().get(j).getHP() + 1);
				}
					else {
					game.getCol().remove(game.getCol().get(j));
					//getCol().remove(j);
					}
			}
			
			
					//Kollision med Y-Max(Botten av brickan)
			else if( ballRect.getY()+ballRect.getHeight()  >= (game.getCol().get(j).getRect().getY()+game.getCol().get(j).getRect().getHeight() + 10)) {
				System.out.println("Y-Värde(+)");
				delay = 6;
				setySpeed(getySpeed()*-1);
				if(game.getCol().get(j).getHP() < 3) {
					game.getCol().get(j).setHP(game.getCol().get(j).getHP() + 1);
				}
					else {
					game.getCol().remove(game.getCol().get(j));
					//getCol().remove(j);
					}
			}
			
			/*else {
			delay = 6;
			setySpeed(getySpeed()*-1);
			if(game.getCol().get(j).getHP() < 3) {
				game.getCol().get(j).setHP(game.getCol().get(j).getHP() + 1);
			}
				else {
				game.getCol().remove(game.getCol().get(j));
				//getCol().remove(j);
				}
			}*/
		}
		}
		}
	

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

/*Notes:
 * 
 * //2023-01-31 && Kl.00:30.	//Ändrade ballRect.getX() + 3 >= (game.getCol().get(j).getRect().getX()+game.getCol().get(j).getRect().getWidth()) till 4.
 * 
 * 
 * 
 *Gammal Kod: 
 *
 *ÖVRE KANTEN:
 *else if((ballRect.getY()  <= game.getCol().get(j).getRect().getY() && ballRect.getX()  <= game.getCol().get(j).getRect().getX()) ) {
				delay = 6;
				System.out.println("SANT");
				setySpeed(getySpeed()*-1);
				setxSpeed(getxSpeed()*-1);
				if(game.getCol().get(j).getHP() < 3) {
					game.getCol().get(j).setHP(game.getCol().get(j).getHP() + 1);
				}
					else {
					game.getCol().remove(game.getCol().get(j));
					//getCol().remove(j);
					}
			}
 *
 *
 *
 * private void bounce() {
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
