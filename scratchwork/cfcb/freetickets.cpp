#include <vector>
#include <memory>
#include <iostream>

int freeTickets(std::vector<int> determination, std::vector<int> money, int n) {

  struct Element {
    int det, money;
    std::shared_ptr<Element> next;

    Element(int det, int money) :
        det(det), money(money), next(nullptr) { }
  };

  std::shared_ptr<Element> queueEnd(new Element(0, 0));
  for (int i = 0; i < determination.size(); i++) {
    std::shared_ptr<Element> prev = queueEnd;
    std::shared_ptr<Element> cur(new Element(determination[i], money[i]));
    std::shared_ptr<Element> next = queueEnd->next;
    while (next && cur->money >= next->det) {
      cur->money -= next->det;
      next->money += next->det;
      if (next->money >= n * next->det) {
        next = next->next;
        prev->next->next = nullptr;
        prev->next = next;
      } else {
        next = next->next;
        prev = prev->next;
      }
    }
    prev->next = cur;
    cur->next = next;

	std::shared_ptr<Element> p = queueEnd;
	while(p) {
		std::cout << p->money << " " << p->det << " | ";
		p=p->next;
	}
	std::cout << std::endl;
  }

  int answer = 0;
  std::shared_ptr<Element> cur = queueEnd;
  while (cur) {
    answer += cur->money;
    cur = cur->next;
  }
  return answer;

}


int main() {
	return freeTickets({4,7,5,8,7},{9,10,6,8,8},4);
}
