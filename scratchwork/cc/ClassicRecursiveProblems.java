package practice.cc;

import java.util.Set;
import java.util.SortedSet;
import java.util.TreeSet;
import java.util.HashSet;
import java.util.Map;
import java.util.HashMap;
import java.util.Stack;
import java.util.Iterator;

public class ClassicRecursiveProblems {
/*
 * return a set of all Strings that are legal parentheses 
 * for 'n' pairs of parentheses
 */
	public Set<String> legalParentheses(int n) {
		return legalParentheses(n, n);
	}

/*
 * return a set of all Strings that are legal parentheses paris
 * and with possibly extra close parentheses
 * for 'numOpens' open parentheses and 'numCloses' close parentheses
 *
 * numOpens <= numCloses
 */
	private Set<String> legalParentheses(int numOpens, int numCloses) {
		if (numCloses == 0) {
			Set<String> emptyStringSet = new HashSet<String>();
			emptyStringSet.add("");
			return emptyStringSet;
		}

		Set<String> legalParens = new HashSet<String>();
		if (numOpens > 0)
			legalParens.addAll(setPrepend(legalParentheses(numOpens-1, numCloses), "("));
		if (numCloses > numOpens)
			legalParens.addAll(setPrepend(legalParentheses(numOpens, numCloses-1), ")"));

		return legalParens;
	}

	private Set<String> setPrepend(Set<String> set, String str) {
		Set<String> prepended = new HashSet<String>();
		for (String elt : set) {
			prepended.add(str+elt);
		}
		return prepended;
	}

/*
 * return all combinations of any number of elements from a Set 'nums'
 * that add up to 'total'. Assume each element of 'nums' can be used
 * infinite times
 */
	public Set<Map<Integer,Integer>> makeTotal(int total, SortedSet<Integer> nums) {
		Set<Map<Integer,Integer>> totalCombos = new HashSet<Map<Integer,Integer>>();
/*
 * a base case that is more complex than usual, but probably necessarily so
 * if total is negative or nums Set is empty, we return an empty Set to signify that
 * its not possible
 *
 * if total is 0, then we add an empty Map into the Set to signify that a combination
 * which selects none of the nums elements makes total
 */
		if (total<0 || nums.isEmpty())
			return totalCombos;
		if (total == 0) {
			totalCombos.add(new HashMap<Integer,Integer>());
			return totalCombos;
		}

/*
 * all combinations which add up to total either contain an element 'num'
 * or do not contain an element 'num'
 *
 * get all combos that contain at least one instance of 'num'
 */
		Integer num = nums.first();
		totalCombos.addAll(makeTotal(total-num, nums));

		for (Map<Integer,Integer> combination : totalCombos) {
			if (combination.containsKey(num))
				combination.put(num, combination.get(num)+1);
			else
				combination.put(num, 1);
		}
/*
 * get all combos that do not contain an instance of 'num'
 */
		nums.remove(num);
		totalCombos.addAll(makeTotal(total, nums));
		nums.add(num);

		return totalCombos;
	}
}

/*
 * both of these problems are quite tricky
 * my implementation didnt contain well formed recursive steps
 * in both cases during the recursive step we recursed to a state
 * which involve reducing one of two variables we are recursing on
 * and getting closer to a base case
 */
