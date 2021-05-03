#include "function.h"
#include <iostream>
/*class Guest {
private:
	string name;
	int money;
	int skill;
};*/


Guest::Guest(string s, int m, int ski) {
    name = s;
    money = m;
    skill = ski;
}

Guest::~Guest() {

}

string Guest::get_name() {
    return name;
}

int Guest::get_money() {
    return money;
}

int Guest::get_skill() {
    return skill;
}

void Guest::Win(int m) {
    money += m;
}


/*class Casino {
private:
	int fee;

	int guest_num;
	Guest *guest[1009];

	int income;
	int list_num;
	string blacklist[1009];
};*/
Casino::Casino() {
    guest_num = income = list_num = 0;
}

Casino::~Casino() {
    EndDay();
}

void Casino::Casino::Enterance(int f) {
    fee = f;
}

void Casino::GuestEnter(string s, int m, int ski) {
    for(int i = 0; i < list_num; i++) {
        if(blacklist[i] == s) {
            //cout << s << " cannot enter because blacklisted\n";
            return;
        }
    }
    for(int i = 0; i < guest_num; i++) {
        if(guest[i]->get_name() == s) {
            //cout << s << " cannot enter because already entered\n";
            return;
        }
    }

    if(m <= fee) {
        income += m;
        blacklist[list_num++] = s;
        //cout << s << " cannot enter because bankrupted\n";
        return;
    }
    guest[guest_num++] = new Guest(s, m-fee, ski);
    income += fee;
    //cout << s << " entered successfully\n";
}

void Casino::Win(string s, int m) {
    for(int i = 0; i < guest_num; i++) {
        if(guest[i]->get_name() == s) {
            if(guest[i]->get_money() < -m)
                m = -guest[i]->get_money();
            income -= m;
            guest[i]->Win(m);
            if(guest[i]->get_money() <= 0 || guest[i]->get_skill() * 2 < m) {
                //cout << s << " was kicked out because cheating or bankrupted\n";
                blacklist[list_num++] = guest[i]->get_name();

                delete guest[i];
                if(i != guest_num-1)
                    guest[i] = guest[guest_num-1];
                guest_num--;
            }
        }
    }
}

void Casino::EndDay() {
    //cout << "\nThe income is " << income << "\n\n";
    for(int i = 0; i < guest_num; i++) {
        //cout << "[" << i << "]" << guest[i]->get_name() << ": " << guest[i]->get_money() << "\n";
        delete guest[i];
    }
    guest_num = 0;
}

void Casino::Result() {
    cout << income << '\n';
    for(int i = 0; i < list_num; i++) {
        cout << blacklist[i] << '\n';
    }
}
