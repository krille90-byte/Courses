package tre;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		
		String[] strangar;
		Scanner sc = new Scanner(System.in);
		System.out.print("Hur många element vill du ha?: ");
		int antal = sc.nextInt();
		strangar = new String[antal];
		for(int i = 0; i < antal; i++) {
			System.out.printf("Element nr(%d): ",(i+1));
			strangar[i] = sc.next();
		}
		System.out.println("\nListan:");
		for(int i = 0; i < antal; i++) {
			System.out.println(strangar[i]);
		}
		
		//Sort.
		String temp;
		for(int i = 0; i < antal; i++) {
			for(int j = 0; j < antal; j++) {
				if((strangar[i].compareTo(strangar[j])) <0) {
					temp = strangar[i];
					strangar[i] = strangar[j];
					strangar[j] = temp;
				}
			}
		}
		System.out.println("\nListan efter sortering:");
		for(int i = 0; i < antal; i++) {
			System.out.println(strangar[i]);
		}
		sc.close();

	}

}
/*
 * NOTES:
 * 
 * ((strangar[i].compareTo(strangar[j])) <0)
 * compareTo är detsamma som i C
 * strcmp(string,string2)
 * Används för att jämföra strängar.
 * */

