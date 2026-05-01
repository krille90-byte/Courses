package ett;

public class Main {

	public static void main(String[] args) {
		System.out.print("Roten ur 2 = ");
		Integer heltal = 2;
		double x = (double) Math.sqrt(heltal);
		System.out.printf("%1.6f",x);
		System.out.print("\n2.5 Upphöjt med a = ");
		Double flyttal = 2.5;
		double x2 = (double) Math.pow(flyttal, heltal);
		System.out.println(x2);
	}

}

/*
 * NOTES:
 * 
 * __10 är antal blanksteg.
 * System.out.printf("%10f",x);
 * 
 * __6:an avgör decimalerna
 * System.out.printf("%1.6f",x);
 * 
 * __Tar reda på vad decimalen är i hex.
 * Integer hextest = 13;
		System.out.printf("%x",hextest);
 * */
