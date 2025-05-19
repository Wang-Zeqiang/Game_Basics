#include "Players.h"
#include "Cards.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Player::Player(bool myRound, string username, double damage_reduction,  
               double attack_boost, double hp_recovery_rate, int usertp)
{
    myRound_ = myRound;
    Died = false;
    username_ = username;
    damage_reduction_ = damage_reduction;
    damage_reduction_buff_ = 0;
    attack_boost_ = attack_boost;
    attack_boost_buff_ = 0;
    hp_recovery_rate_ = hp_recovery_rate;
    hp_recovery_rate_buff_ = 0;
    userhp_ = usertp;
    usertp_ = usertp;
} 

void Player::switch_rounds(){
    myRound_ = !myRound_;
    // reset all buffs
    damage_reduction_buff_ = 0;
    attack_boost_buff_ = 0;
    hp_recovery_rate_buff_ = 0;
}

bool Player::IsMyRound() const{
    return myRound_;
}

bool Player::Lose() const{
    return Died;
}

void Player::buff_damage_reduction(const double buff){
    damage_reduction_buff_ += buff;
}

void Player::buff_attack_boost(const double buff){
    attack_boost_buff_ += buff;
}

void Player::buff_hp_recovery_rate(const double buff){
    hp_recovery_rate_buff_ += buff;
}

int Player::get_damage_reduction_total(const int damage) const{
    return damage * (1-damage_reduction_buff_); // Note damage reduction buff has to be from 0-1 (e.g., max 0.8)
}

int Player::get_attack_boost_total(const int atk) const{
    return atk * (1+attack_boost_buff_);
}

int Player::get_hp_recovery_total(const int hr) const{
    return hr * (1+hp_recovery_rate_buff_);
}

void Player::display_userhp() const{
    cout << userhp_ << "/" << usertp_ << " " << endl;
}

void Player::user_takeDamage(int damage){
    int trueDamage = get_damage_reduction_total(damage);
    if (trueDamage >= userhp_){
        userhp_ = 0;
        Died = true;
    }
    else {
        userhp_ -= trueDamage;
    }
}

int Player::get_user_hp() const{
    return userhp_;
}

int Player::get_user_tp() const{
    return usertp_;
}

void Player::user_recovery(int ra){
    userhp_ += ra;
}

void Player::user_maxRecovery(){
    userhp_ = usertp_;
}
