#include <assert.h>
#include <ctype.h>
#include <string.h>

#include <string>

using namespace std;

namespace ecpp {
	class ci_char_traits : public char_traits<char> {
		public:
			static constexpr bool eq(char a, char b) {
				return toupper(a)==toupper(b);
			}
			static constexpr bool lt(char a, char b) {
				return toupper(a)<toupper(b);
			}
			static int compare(const char *s1, const char *s2, size_t count) {
				for(size_t i=0; i<count; ++i) {
					if(lt(s1[i],s2[i]))
						return -1;
					if(!eq(s1[i],s2[i]))
						return 1;
				}
				return 0;
			}
	};

	typedef basic_string<char, ecpp::ci_char_traits> ci_string;
}

bool operator==(const string &lhs, const ecpp::ci_string &rhs) {
	return lhs.c_str()==rhs;
}

int main() {
	ecpp::ci_string s("AbCdE");

	assert(s=="abcde");
	assert(s=="ABCDE");
	assert(s<"b");
	assert(s<"B");
	assert(s>"ab");
	assert(s>"Ab");

	string str("abcde");
	assert(str==s);

	assert(s==ecpp::ci_string("abcde"));

	assert(strcmp(s.c_str(),"AbCdE") == 0);
	assert(strcmp(s.c_str(),"abcde") != 0);
}
