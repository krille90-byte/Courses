package fem;

import java.util.Scanner;

public class Circle {
	Scanner sc = new Scanner(System.in);
	private Double radius;
	private static final Double Pi = 3.14159265359;
	
	public Circle(Double radie) {
		this.radius = radie;
		System.out.print("Enter Radius(m): ");
		setRadius(sc.nextDouble());
		
		diameter();
		circumference();
		area();
	}
	public void diameter() {
		Double dia;
		dia = getRadius()*2;
		System.out.printf("Diameter: %1.0fm\n",dia);
	}
	public void area() {
		double ar = Circle.Pi * (getRadius()*getRadius());
		System.out.printf("Area: %1.4fm^2\n",ar);
	}
	public void circumference() {
		double ar2 = 0;
		double x = (2 * Circle.Pi) * getRadius();
		ar2 = x;
		System.out.printf("Omkrets: %1.5fm\n",ar2);
	}
	public Double getRadius() {
		return radius;
	}
	public void setRadius(Double radius) {
		this.radius = radius;
	}
}
