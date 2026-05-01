package tva;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
	
		Scanner sc = new Scanner(System.in);
		int count = 0;
		char a = 0;
		while(a != '?') {
			a = sc.next().charAt(0);
			if(a >= 'A' && a <= 'Z') {
				count += 1;
			}
		}
		System.out.println("Antal Versaler: "+count);
	}

}
