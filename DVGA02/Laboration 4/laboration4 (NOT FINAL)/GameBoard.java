package laboration4_Test3;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.JComponent;

public class GameBoard extends JComponent {
	private static int FPS = 60; 
	private static Game game;
	private static Keyboard keyboard;
	
	
	
	public GameBoard() {
		
		keyboard = new Keyboard();
		
		game = new Game();
		
		
	}
	public static void ResetGame() {
		keyboard = new Keyboard();
		game = new Game();
		
	}
	@Override
	public Dimension getPreferredSize() {	
		return new Dimension(800, 600);
	}

	@Override
	protected void paintComponent(Graphics arg0) {
		super.paintComponent(arg0);
		Graphics2D graphics = (Graphics2D)arg0;
		graphics.setBackground(Color.darkGray);
		graphics.setColor(new Color(7, 12, 49));
		graphics.fillRect(0, 0, getWidth(), getHeight());
	
		game.draw(graphics);
	}
	
	@Override
	protected void processKeyEvent(KeyEvent e) {
		super.processKeyEvent(e);
		if (e.getID() == KeyEvent.KEY_PRESSED)
			keyboard.processKeyEvent(e.getKeyCode(), true);
		else if (e.getID() == KeyEvent.KEY_RELEASED)
			keyboard.processKeyEvent(e.getKeyCode(), false);
	}

	public void start() {
		while(true) {
			game.update(keyboard);
			try {
				Thread.sleep(1000 / getFPS()); //Throttle thread
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			this.repaint();
		}
	}
	public static int getFPS() {
		return FPS;
	}
	public static void setFPS(int fPS) {
		FPS = fPS;
	}
}
