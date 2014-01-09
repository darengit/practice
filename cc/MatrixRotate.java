package practice.cc;

public class MatrixRotate {
	public static void main(String[] args) {
/*
 * empty matrix
 */
		int[][] test = new int[0][0];
		rotateRight90(test);
/*
 * still empty matrix, same as above, thought i try both just to see
 */
		test = new int[][] {};
		rotateRight90(test);
/*
 * matrix [[1]]
 */
		test = new int[][] {{1}};
		rotateRight90(test);
		System.out.println(matrixToString(test));
/*
 * matrix [[ 1,  2,  3,  4],
 *         [ 5,  6,  7,  8],
 *         [ 9, 10, 11, 12],
 *         [13, 14, 15, 16]]
 */
        test = new int[][] {{ 1,  2,  3,  4},
                            { 5,  6,  7,  8},
                            { 9, 10, 11, 12},
                            {13, 14, 15, 16}};
        rotateRight90(test);
        System.out.println(matrixToString(test));
/*
 * matrix [[ 1,  2,  3,  4,  5],
 *         [ 6,  7,  8,  9, 10],
 *         [11, 12, 13, 14, 15],
 *         [16, 17, 18, 19, 20],
 *         [21, 22, 23, 24, 25]]
 */
        test = new int[][] {{ 1,  2,  3,  4,  5},
                            { 6,  7,  8,  9, 10},
                            {11, 12, 13, 14, 15},
                            {16, 17, 18, 19, 20},
                            {21, 22, 23, 24, 25}};
        rotateRight90(test);
        System.out.println(matrixToString(test));

	}

	public static String matrixToString(int[][] matrix) {
		String matrixSerialized = "";
		for (int i=0; i<matrix.length; i++) {
			for (int j=0; j<matrix[i].length; j++) {
				matrixSerialized += '\t' + String.valueOf(matrix[i][j]);
			}
			matrixSerialized += '\n';
		}
		return matrixSerialized;
	}

	public static void rotateRight90(int[][] toRotate) {
		int length = toRotate.length;
		if (length == 0)
			return;
	
		for (int i=0; i<length/2; i++) {
			for (int j=0; j<(length/2+((length%2==0)?0:1)); j++) {
				int tmp = toRotate[i][j];
				toRotate[i][j] = toRotate[length-1-j][i];
				toRotate[length-1-j][i] = toRotate[length-1-i][length-1-j];
				toRotate[length-1-i][length-1-j] = toRotate[j][length-1-i];
				toRotate[j][length-1-i] = tmp;
			}
		}
	}
}
