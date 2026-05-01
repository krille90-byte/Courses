package laboration4_Test3;

import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.Shape;
import java.awt.event.KeyListener;
import java.util.*;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JPanel;

import laboration4_Test3.Ball;

public class SquareCollection{
	Enemy enemy;
	Ball ball;
	
	public Rectangle blockRect;
	private ArrayList<Enemy> enemies = new ArrayList<>();						//Nytt
	//public ArrayList<Enemy> blocks = new ArrayList<>();
	
	public SquareCollection(int AmountOfBlocks, Enemy enemy, Ball ball) {	//Nytt(AmountOfBlocks)
		//super(x, y, width, height);
		
		for(int i = 0; i < AmountOfBlocks; i++) {							//Nytt for loop
			enemies.add(new Enemy(20+i*50,70,25,25));
		}
		
		
		
		/*for(int i = 0; i < AmountOfBlocks; i++) {
			blocks.add(new Enemy(20+i*50,70,25,25, null));
			blocks.add(new Enemy(20+i*50,120,25,25, null));	
			
		}*/
		
		
}




	public void update(Keyboard keyboard) {
		
		for(Enemy enemyList : enemies) {
			enemyList.update(keyboard);
		}
		for(Enemy enemyList : enemies) {
			if(ball.getBallRect().intersects(enemyList.getRect())) {
				System.out.println("--Träff--");
			}
		}
	
		
	}

	
	public void draw(Graphics2D graphics) {
		
		for(Enemy enemyList : enemies) {
			enemyList.draw(graphics);
		}
		
		
		/*for(Enemy blocks : blocks) {
			blocks.draw(graphics);
			
		}*/
	}

}
