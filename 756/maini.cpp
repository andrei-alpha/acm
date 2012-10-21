import java.util.Scanner;

public class Biorythms {

	private final static int PHYSICAL = 23;
	private final static int EMOTIONAL = 28;
	private final static int INTELLECTUAL = 33;

	public static void main(String[] args) {

		Scanner input = new Scanner(System.in);
		for (int nr = 1;; ++nr) {
			int p = input.nextInt();
			int e = input.nextInt();
			int i = input.nextInt();
			int d = input.nextInt();
			if (p == -1 && e == -1 && i == -1 && d == -1) {
				break;
			}
			System.out.println("Case " + nr
					+ ": the next triple peak occurs in " + days(p, e, i, d)
					+ " days.");
		}
	}

	public static int days(int p, int e, int i, int d) {
		int days = (5544 * p + 14421 * e + 1288 * i - d) % 21252;
		if (days <= 0) {
			days += PHYSICAL * EMOTIONAL * INTELLECTUAL;
		}
		return days;

	}
}
