#include <iostream>
#include <vector>
#include <deque>
#include <list>

using namespace std;

class Good {
public:
	int id;
	int price;
	int time;
	Good(int id, int price) :
			id { id }, price { price } {
		time = rand() % 10 + 1;
	}
};

class Basket {
public:
	int time;
	std::vector<Good*> basket;
	void addGood(Good *g) {
		basket.push_back(g);
		time += g->time;
	}
	void removeGood() {
		for (size_t i = 0; i < basket.size(); ++i) {
			cout << i + 1 << ".\t" << basket[i]->id << endl;
		}
		int change;
		cin >> change;
		time -= basket[change - 1]->time;
		basket.erase(basket.begin() + (change - 1));
	}
};

class Buyer {
public:
	int debit;
	int credit;
	Basket *basket;

	void pay(/*int xxx*/) {
		this->debit -= this->credit;
		this->credit = 0;
	}
};

class Cashier {
public:
	static int cash;
	std::deque<Buyer*> line;
	int time;
	void enqueue(Buyer *b) {
		this->line.push_back(b);
	}
	void relax() {
		cout << "On break..." << endl;
		line.erase(line.begin(),line.end());
	}
	void sale() {
		Buyer *b = this->line.front();
		time -= b->basket->time;
		int payment { }; //int payment = 0;
		/*
		 * for_each(b->basket->basket->begin(), b->basket->basket->end(), [&payment](Good* value) {payment += value->price;})
		 */
		for (auto g : b->basket->basket) {
			payment += g->price;
		}
		b->credit += payment;
		b->pay();
		this->line.pop_front();
	}
};

class Market {
public:
	list<Cashier*> cashiers;
	deque<Buyer*> tmp;
	Market() {
		cashiers.push_back(new Cashier());
		cashiers.push_back(new Cashier());
		(*(cashiers.begin()))->time = 6 * 60;
		(*++(cashiers.begin()))->time = 3 * 60;
	}
	void work() {
		while (!cashiers.empty()) {
			for (auto &cashier : cashiers) {
				if (cashier->time > 0) {
					if (tmp.size() > 0) {
						for (auto &x : tmp) {
							cashier->enqueue(x);
						}
						tmp.erase(tmp.begin(), tmp.end());
					}
				}
				cashier->sale();
			}
		}
	}
};

int main() {
	int payment { };

	int x = 0;
	std::cout << "Hello World!\n";
}

