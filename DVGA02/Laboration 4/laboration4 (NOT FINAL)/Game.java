package laboration4_Test3;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.PointerInfo;
import java.awt.Rectangle;
import java.awt.geom.Point2D;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;
import javax.swing.*;




public class Game extends JPanel{
	private Program program;
	private RedBox RedBox;
	private BlueBox BlueBox;
	private GreenBox GreenBox;
	private ColoredBox ColoredBox;
	private Player player;
	private Enemy enemy;
	private ArrayList<Enemy> enemies = new ArrayList<>();
	private ArrayList<String> aList = new ArrayList<String>();
	private static String names = " ";
	private SquareCollection blocks;
	private Ball ball;
	//public Leaderboard leaderboard;
	private boolean lockFive = false;
	private Program prog;
	private int delay = 0;
	private static int points = 0;
	
	
	
	public Game() {
		//make sprites
		RedBox = new RedBox(0, 0, 25, 25);
		BlueBox = new BlueBox(775, 0, 25, 25);
		GreenBox = new GreenBox(775, 575, 25, 25);
		player = new Player(400,550,10,10);
		enemy = new Enemy(0*50,30,25,10);
		ball = new Ball(440,520,10,10,player, enemy);
		//leaderboard = new Leaderboard(200, -500, 400, 500);
		//scorehandler = new ScoreHandler(this);

		
		for( int i = 1; i < 16; i++) {
			getEnemies().add(new Enemy(-20+i*50,35,41,10));
			getEnemies().get(i-1).setHP(3);
		}for(int i = 1; i < 16; i++) {
			getEnemies().add(new Enemy(-20+i*50,75,41,10));
			getEnemies().get(i+14).setHP(2);
		}for(int i = 1; i < 16; i++) {
			getEnemies().add(new Enemy(-20+i*50,115,41,10));
			getEnemies().get(i+29).setHP(3);
		}for(int i = 1; i < 16; i++) {
			getEnemies().add(new Enemy(-20+i*50,155,41,10));
			getEnemies().get(i+44).setHP(1);
		}for(int i = 1; i < 16; i++) {
			getEnemies().add(new Enemy(-20+i*50,195,41,10));
			getEnemies().get(i+59).setHP(2);
		}
		//points = 0;
		
	}
	
	public void update(Keyboard keyboard) {
		//Handle logic
		//Move sprites
		player.update(keyboard);
		
		ball.update(keyboard);
		//Leaderboard.update(keyboard);
		//scorehandler.update(keyboard);
		for(Enemy enemyList : getEnemies()) {
			enemyList.update(keyboard);
		}
		
		for(int i = 0; i < getEnemies().size(); i++) {
			if(ball.getRect().intersects(getEnemies().get(i).getRect()) && delay <= 0) {
				delay = 3;
				ball.setYspeed(ball.getYspeed() * -1);
				getEnemies().get(i).setHP(getEnemies().get(i).getHP() + 1);
		
				if(getEnemies().get(i).getHP() <= 2) {
				ball.setPoints(ball.getPoints() + 12);
				setPoints(getPoints() + 12);
				}else if(getEnemies().get(i).getHP() <= 3) {
				ball.setPoints(ball.getPoints() + 25);
				setPoints(getPoints() + 25);
				}
			}
			if(ball.getBallRect().intersects(getEnemies().get(i).getRect()) && getEnemies().get(i).getHP() > 3) {
				getEnemies().remove(i);
				ball.setPoints(ball.getPoints() + 50);
				setPoints(getPoints() + 50);
			}
		}
		--delay;
		if(keyboard.isKeyDown(Key.K)){						//DEBUG(Removes all blocks by holding in K)
			for(int i = 0; i < getEnemies().size(); i++) {
			getEnemies().remove(0);
			if(getEnemies().isEmpty()) {
				break;
			}
		}
	}
		if(keyboard.isKeyDown(Key.One)) {
			GameBoard.setFPS(144);
			System.out.println("FPS Set to: 144");
			
		}
		if(keyboard.isKeyDown(Key.Two)) {
			GameBoard.setFPS(60);
			System.out.println("FPS set back to: 60");
		}
		if(keyboard.isKeyDown(Key.Tre)) {
			ball.setLife(900);
		}
		if(keyboard.isKeyDown(Key.Four)) {
			ball.setLife(1);
		}
		if(keyboard.isKeyDown(Key.Five) && lockFive == false) {
			ball = new Ball(400,450,0,0,player, enemy);
			System.out.println("Bye Bye Mr.Ball!");
			lockFive = true;
		}
		if(keyboard.isKeyDown(Key.Six) && lockFive == true) {
			ball = new Ball(400,450,10,10,player,enemy);
			System.out.println("Welcome back Mr.Ball!");
			lockFive = false;
		}
		else if(getEnemies().isEmpty() || ball.getLife()==0) {
			/*prog.latest.add(Game.getPoints());
			Game.setPoints(0);*/
			/*int  StoreThis = Game.getPoints();
			int sum = 1;
			for(int i = 0; i < 4; i++) {
				prog.latest.add(sum+". "+StoreThis);
				sum++;
				break;
			}*/
			setNames(JOptionPane.showInputDialog("Your Name is: "));
			aList.add(getNames());
			//Program.storeScore();
			//Points.GetThis();
			//Points.Print();
			//Points.save();
			
			Program.NewScore(points);
			setPoints(0);
			//scorehandler.update();
			GameBoard.ResetGame();
			
			//leaderboard.update(keyboard);
		}
		
	}

	public void draw(Graphics2D graphics) {
		//draws all objects
		
		RedBox.draw(graphics);
		BlueBox.draw(graphics);
		GreenBox.draw(graphics);
		player.draw(graphics);
		//blocks.draw(graphics);
		ball.draw(graphics);
		//Leaderboard.draw(graphics);
		for(Enemy enemyList : getEnemies()) {
			enemyList.draw(graphics);
		}
		if(ball.getLife() <= 0) {
			ball.lives();
			graphics.setColor(Color.CYAN);
			graphics.setFont(new Font("TimesRoman", Font.PLAIN,50));
			graphics.drawString("GAME OVER", 200, 300);
			graphics.setColor(Color.RED);
			graphics.drawString(String.valueOf("Points: "+ ball.getPoints()), 200, 400);
			graphics.setFont(new Font("TimesRoman", Font.PLAIN,20));
			ball.setX(0);
			ball.setY(0);
			ball.setWidth(0);
			ball.setHeight(0);
			//leaderboard.draw(graphics);
			}
		if(getEnemies().isEmpty()) {
		graphics.setColor(Color.YELLOW);
		graphics.setFont(new Font("TimesRoman", Font.PLAIN, 35));
		graphics.drawString("Congratulations you win!", 210, 35);
		graphics.setFont(new Font("TimesRoman", Font.PLAIN,35));
		graphics.setColor(Color.GREEN);
		graphics.drawString(String.valueOf("Points: "+getPoints()), 300, 350);
		ball = new Ball(400,450,0,0,player, enemy);
		try {
			Thread.sleep(10);
		} catch (InterruptedException e) {
			System.out.println("Fel!");
			e.printStackTrace();
		}
		
		
		
	//	leaderboard.Leaderboard();
	//	leaderboard.draw(graphics);
		}
	}
	public static int getPoints() {
		return points;
	}

	public static void setPoints(int points) {
		Game.points = points;
	}

	public ArrayList<Enemy> getEnemies() {
		return enemies;
	}

	public void setEnemies(ArrayList<Enemy> enemies) {
		this.enemies = enemies;
	}

	public static String getNames() {
		return names;
	}

	public void setNames(String names) {
		Game.names = names;
	}
	
}


