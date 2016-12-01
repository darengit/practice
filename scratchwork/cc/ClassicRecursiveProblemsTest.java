package practice.cc;

import java.util.SortedSet;
import java.util.TreeSet;

public class ClassicRecursiveProblemsTest {
	public static void main(String[] args) {
		ClassicRecursiveProblems crp = new ClassicRecursiveProblems();

		System.out.println(crp.legalParentheses(0));
		System.out.println(crp.legalParentheses(1));
		System.out.println(crp.legalParentheses(2));
		System.out.println(crp.legalParentheses(3));
		System.out.println(crp.legalParentheses(4));
		System.out.println(crp.legalParentheses(5));

		SortedSet<Integer> nums = new TreeSet<Integer>();

		System.out.println(crp.makeTotal(-10, nums));
		System.out.println(crp.makeTotal(0, nums));
		System.out.println(crp.makeTotal(10, nums));

		nums.add(new Integer(1));
		nums.add(new Integer(5));
		nums.add(new Integer(10));
		nums.add(new Integer(25));

		System.out.println(crp.makeTotal(-10, nums));
		System.out.println(crp.makeTotal(0, nums));
		System.out.println(crp.makeTotal(1, nums));
		System.out.println(crp.makeTotal(2, nums));
		System.out.println(crp.makeTotal(99, nums));
		System.out.println(crp.makeTotal(100, nums));
	}
}
