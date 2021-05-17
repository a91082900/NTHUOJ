#include "function.h"
#include <iostream>
#include <sstream>

	/*string name;
	int money;
	int skill;
	bool kicked;
	int cards;
	int bets;*/

Human::Human(string n, int m, int ski)
  : name(n),
    money(m),
    skill(ski),
    kicked(false),
    cards(0),
    bets(0)
{}

Human::~Human() {

}

int Human::get_money() {
    return money;
}

Guard::Guard(int ski) : Human("Guard", 0, ski) {
}

void Guard::Pay(Human *human) {
    int m = 0;
    if(this->skill < human->skill)
        m = human->skill - this->skill;
    this->money -= m;
    human->money += m;
}

void Guard::Kick(Human *human, int flag) {
    human->kicked = true;
    if(flag) {
        this->Pay(human);
    }
}

Guard::~Guard() {

}


Banker::Banker(int ski) : Human("Banker", 0, ski) {

}

void Banker::Pay(Human *human) {
    if(human->name == "Guard") {
        money -= 100;
        human->money += 100;
    }
    else {
        int m = human->bets;
        if(human->skill < skill)
            m += 10*human->cards;
        if(human->cards == 21)
            m *= 2;
        money -= m;
        human->money += m;
        human->bets = m; // for cheating check
    }
}

int Banker::Win(Human *human) {
    if(this->cards > 21 && human->cards > 21)
        return -1;
    if(this->cards <= 21 && (human->cards > 21 || human->cards <= this->cards))
        return 1;
    if(human->cards <= 21 && (this->cards > 21 || this->cards < human->cards))
        return 0;
    return -1;
}

void Banker::Draw() {
    string s, tmps;
    stringstream ss;
    //getline(cin, tmps); // no need to do this since last command is also getline
    getline(cin, s);
    ss << s;
    int card = 0, tmp;
    while(ss >> tmp) {
        card += tmp;
    }
    cards = card;
}

Banker::~Banker() {

}


Player::Player(string name, int m, int ski) : Human(name, m, ski) {

}

void Player::Pay(Human *human) {
    if(this->money <= this->bets) {
        this->bets = this->money;
    }
    human->money += this->bets;
    this->money -= this->bets;
}

void Player::Bet() {
    string tmp;
    cin >> tmp >> bets;
}

void Player::Draw() {
    string s, tmps;
    stringstream ss;
    getline(cin, tmps);
    getline(cin, s);
    ss << s;
    int card = 0, tmp;
    while(ss >> tmp) {
        card += tmp;
    }
    cards = card;
}

bool Player::Kicked() {
    return kicked;
}

bool Player::Bankrupt() {
    return money <= 0;
}

bool Player::Cheat(Human *human) {
    return 2 * this->skill < this->bets;
}

Player::~Player() {

}
