package fyra;

import java.util.*;

public class Main {
private static final int x = 100;
	public static void main(String[] args) {
		Integer[] summan = new Integer[x];
		Integer sum = 0;
		Scanner sc = new Scanner(System.in);
		Random rand = new Random();
		int tarning_x = 0;
		int tarning_y = 0;
		
		for(int i = 0; i < x; i++) {
			tarning_x = rand.nextInt(6)+1;
			sum += tarning_x;
			tarning_y = rand.nextInt(6)+1;
			sum += tarning_y;
			summan[i] = sum;
			System.out.println((i+1)+" gånger blev tärningssumman "+sum);
			sum = 0;
		}
		for(int i = 0; i < x; i++) {
			System.out.println((i+1)+": "+summan[i]);
		}

	}

}
