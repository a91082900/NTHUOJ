#include "function.h"
#include <iostream>

Guest::Guest() {
    name = "";
    money = 0;
    skill = 0;
}

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


Casino::Casino() {
    list_num = guest_num = income = 0;
}

Casino::~Casino() {
    EndDay();
}

void Casino::Enterance(int f) {
    fee = f;
}

void Casino::GuestEnter(string s, int m, int ski) {
    for(int i = 0; i < guest_num; i++) {
        if(s == guest[i]->get_name())
            return;
    }
    for(int i = 0; i < list_num; i++) {
        if(s == blacklist[i])
            return;
    }
    if(m <= fee) {
        income += m;
        blacklist[list_num++] = s;
        return;
    }
    income += fee;
    guest[guest_num++] = new Guest(s, m-fee, ski);
}

void Casino::Win(string s, int m) {
    for(int i = 0; i < guest_num; i++) {
        if(s == guest[i]->get_name()) {
            if(guest[i]->get_money() < -m)
                m = -guest[i]->get_money();
            income -= m;
            guest[i]->Win(m);
            if(guest[i]->get_money() <= 0 || m > 2 * guest[i]->get_skill()) {
                blacklist[list_num++] = s;
                delete guest[i];
                if(i != guest_num-1) {
                    guest[i] = guest[guest_num-1];
                }
                guest_num--;
            }
        }
    }
}

void Casino::EndDay() {
    for(int i = 0; i < guest_num; i++) {
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