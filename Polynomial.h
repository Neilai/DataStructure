#include<iostream>
struct Node {
	double coe = 0;
	double exp = 0;
	Node * next = nullptr;
};
class Polynomial {
private:
	Node * first;
public:
	Polynomial() {
		this->first = new Node;
	};
	Polynomial(double coe[], double exp[], int n) {
		this->first = new Node;
		Node *p = this->first;
		for (int i = 0; i < n; i++) {
			Node *tmp = new Node;
			tmp->coe = coe[i];
			tmp->exp = exp[i];
			p->next = tmp;
			p = p->next;
		}
		Node *result = (this->first)->next;
		delete this->first;
		this->first = result;
	}
	Polynomial(Node *p) :first(p) {  }
	void show() {
		Node *p = first;
		while (p)
		{
			if (p->coe) {
				if (p->exp == 0) {
					std::cout << p->coe;
				}

				else if (p->exp == 1 && p->coe == 1) {
					std::cout << "x";
				}
				else if (p->exp == 1) {
					std::cout << p->coe << "*x";
				}
				else if (p->coe == 1) {
					std::cout << "x^" << p->exp;
				}
				else
					std::cout << p->coe << "*x^" << p->exp;
				if (p->next)
					std::cout << "+";
			}
			p = p->next;
		}
		std::cout << std::endl;
	}
	void create() {
		int n;
		std::cout << "请输入项数:" << std::endl;
		std::cin >> n;
		double *coe = new double[n];
		double *exp = new double[n];
		std::cout << "请输入系数（从低到高）:" << std::endl;
		for (int i = 0; i < n; i++)
			std::cin >> coe[i];
		std::cout << "请输入幂指数（从低到高）:" << std::endl;
		for (int i = 0; i < n; i++)
			std::cin >> exp[i];
		Node *p = this->first;
		for (int i = 0; i < n; i++) {
			Node *tmp = new Node;
			tmp->coe = coe[i];
			tmp->exp = exp[i];
			p->next = tmp;
			p = p->next;
		}
		Node *result = (this->first)->next;
		delete this->first;
		this->first = result;
	}
	Polynomial add(Polynomial &item) {
		Node *p1 = this->first;
		Node *p2 = item.first;
		Node *result = new Node;
		Node *p3 = result;
		while (p1&&p2) {
			Node *tmp = new Node;
			if (p1->exp == p2->exp) {
				tmp->exp = p1->exp;
				tmp->coe = p1->coe + p2->coe;
				p3->next = tmp;
				p3 = p3->next;
				p1 = p1->next;
				p2 = p2->next;
			}
			else if (p1->exp > p2->exp) {
				tmp->exp = p2->exp;
				tmp->coe = p2->coe;
				p3->next = tmp;
				p3 = p3->next;
				p2 = p2->next;
			}
			else {
				tmp->exp = p1->exp;
				tmp->coe = p1->coe;
				p3->next = tmp;
				p3 = p3->next;
				p1 = p1->next;
			}
		}
		if (p1) {
			p3->next = p1;
		}
		if (p2) {
			p3->next = p2;
		}
		Node *last = result->next;
		delete result;
		return Polynomial(last);

	}
	Polynomial mul(Node * item) {
		Node *p1 = this->first;
		Node *result = new Node;
		Node *p2 = result;
		while (p1) {
			Node *tmp = new Node;
			tmp->coe = p1->coe * item->coe;
			tmp->exp = p1->exp + item->exp;
			p2->next = tmp;
			p1 = p1->next;
			p2 = p2->next;
		}
		Node *last = result->next;
		delete result;
		return Polynomial(last);
	}
	Polynomial mul(Polynomial &item) {
		Polynomial result;
		Node *p1 = this->first;
		for (; p1; p1 = p1->next) {
			result = result.add(item.mul(p1));
		}
		return result;
	}
};