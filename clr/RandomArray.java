import java.util.Random;

public class RandomArray {
	private static Random rand = new Random();

	public static int[] randomArray(int length, int min, int max) {
		int[] random = new int[length];
		for (int i=0; i<length-1; i++) {
			random[i] = rand.nextInt(max-min+1) + min;
		}
		return random;
	}
}
