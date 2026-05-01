package laboration3_Fast_kollision_i_klasser;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.util.*;

import javax.swing.*;

public class Program extends JFrame {
	GameBoard board;
	public Program() {
		setLocation(500,300);	//Eget
		board = new GameBoard();
		add(board);
		setResizable(false);	//Ändrad
		pack();
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
		board.start();
	}
	
	@Override
	protected void processKeyEvent(KeyEvent e) {
		super.processKeyEvent(e);
		board.processKeyEvent(e);
	}

	public static void main(String[] args) {
		Program program = new Program();
	}

}
