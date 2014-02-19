package practice.clr;

import java.util.List;
import java.util.ArrayList;
import java.util.Set;
import java.util.HashSet;
import java.util.Iterator;

public class StringMatching {
	public static void main(String[] args) {
		List<Integer> found = stringMatchedIndices("", "");
		assert found.isEmpty();

		found = stringMatchedIndices("abc", "");
		assert found.isEmpty();

		found = stringMatchedIndices("", "abc");
		assert found.isEmpty();

		found = stringMatchedIndices("abababababababa", "ababa");

		assert found.size() == 6;
		assert found.contains(new Integer(0));
		assert found.contains(new Integer(2));
		assert found.contains(new Integer(4));
		assert found.contains(new Integer(6));
		assert found.contains(new Integer(8));
		assert found.contains(new Integer(10));

		found = stringMatchedIndices("aabbcxxyyzzaabbxxyyxxyybbccabbcxyyzz", "aabbcxyyzz");
		assert found.isEmpty();
	}

	public static boolean stringMatched(String input, String find) {
		return stringMatchedIndices(input,find).size() > 0;
	}

/*
 * string matching is the simplist form of patern matching
 * the naive approach is O(nm) where 'input' is of length n and 'find' length m
 * there is a very scientific way of building an automaton
 * (can also be called state machine) which builds an automaton, and once built
 * matches the string in O(n)
 * imagine if we are trying to find a million character string in some files that
 * total hundreds of gigs, having these optimizations can make some programs a lot
 * faster
 *
 * below i borrow from the idea of automaton, except i use a really simplistic
 * but easy to understand version which in worst case is O(nm) but in all practical
 * cases is a lot closer to O(n) than O(nm)
 *
 * building automaton for String matching is rather complex (regular expression
 * matching even more so) and beyond the scope what what im trying to
 * demonstrate here
 */
	public static List<Integer> stringMatchedIndices(String input, String find) {
		List<Integer> foundIndices = new ArrayList<Integer>();
		if (input==null || find==null || find.equals(""))
			return foundIndices;

		Set<Integer> state = new HashSet<Integer>();
		state.add(new Integer(0));

		for(int i=0; i<input.length(); i++) {
/*
 * the central ideal behind automaton (aka state machine) is that once the state
 * machine is built, transitioning from one state to another occurs in constant
 * time
 *
 * my transition function is worst case O(m) but average case is very close to
 * constant for vast majority of inputs
 */
			state = transitionState(state, find, input.charAt(i));
			if(state.contains(new Integer(find.length()))) {
				foundIndices.add(i-find.length()+1);
				state.remove(new Integer(find.length()));
			}
		}
		
		return foundIndices;
	}

	private static Set<Integer> transitionState(Set<Integer> state, String find, char currChar) {
		Set<Integer> newState = new HashSet<Integer>();
		for (Integer matchSoFar : state) {
			if (currChar == find.charAt(matchSoFar.intValue()))
				newState.add(new Integer(matchSoFar+1));
		}
		newState.add(new Integer(0));
		return newState;
	}
}
