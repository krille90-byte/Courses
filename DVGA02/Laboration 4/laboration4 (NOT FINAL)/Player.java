package laboration4_Test3;

import java.awt.*;
import javax.swing.*;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.util.Scanner;

public class Player extends Sprite{
	
	private Rectangle playerRect;
	//Scanner scan = new Scanner(System.in);
	
	public Player(int x, int y, int width, int height) {
		super(x, y, width, height);	//super(x, y, width, height, Color.pink);
		playerRect = new Rectangle(getX(),getY(),80,12);
	}

	@Override
	public void update(Keyboard keyboard) {
		playerRect = new Rectangle(getX(),getY(),80,12);
		
		if(keyboard.isKeyDown(Key.Left) && getX() > 0){
			setX(getX()-7);
			
		}if(keyboard.isKeyDown(Key.Right) && getX() < 800 - 80) {
			setX(getX()+7);
		}
		
		if(keyboard.isKeyDown(Key.P)) {
			try {
				Thread.sleep(10000);
			} catch (InterruptedException e) {
				
				e.printStackTrace();
			}
		}
	}

	@Override
	public void draw(Graphics2D graphics) {
		graphics.setColor(Color.RED);
		graphics.fillRect(getX(), getY(), 80, 12);
	}

	public Rectangle getRect() {										//Var här från början
		return this.playerRect;
	}
}
