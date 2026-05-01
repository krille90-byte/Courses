package laboration4_Test3;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.swing.*;



public class Program extends JFrame {
	GameBoard board;
	private JList scoreboard;
	private JList latestlist;
	private static ScoreLista scores;
	static LatestList latest;
	public Program() {
		
		board = new GameBoard();
		
		scores = new ScoreLista();
		scoreboard = new JList(scores.getList());
		
		latest = new LatestList();
		latestlist = new JList(latest.getList());
		
		setLayout(new FlowLayout());
		
		scoreboard.setFocusable(false);
		latestlist.setFocusable(false);
		latestlist.setForeground(Color.red);
		scoreboard.setForeground(Color.red);
		latestlist.setPreferredSize(new Dimension(100,600));
		//board.setPreferredSize(new Dimension(800,600));
		scoreboard.setPreferredSize(new Dimension(200,600));
		add(scoreboard);
		add(board);
		add(latestlist);
		
		//latest.add("LatestPoints: ");
		
		//latest.add(NewScore());
		
		//add(latestLista);
		
		setResizable(true);
		pack();
		
		setTitle("BrickBreaker Game");
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
	public static int storeScore() {
		int score = Game.getPoints();
		return score;
		
	}
	public static String storenames() {
		String namelist = Game.getNames();
		return namelist;
	}
	public static List storeRank() {
		List<List> addedlist = ScoreLista.getRank();
		return addedlist;
	}
	
	public static void NewScore(int score) {
			latest.add(score);
			scores.add(score,Game.getNames());
			
	}

}
