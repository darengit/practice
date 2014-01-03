public class SingletonTest {
	public static void main(String[] args) {
		Singleton x = Singleton.getSingleton();
		Singleton y = Singleton.getSingleton();

		assert x == y;
	}
}
