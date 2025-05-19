#include "Cards.h"
#include "Players.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

//constructor
Card::Card(string name, int tp, int ap){

    hp_ = tp;
    tp_ = tp;
    atk_ = ap;
    awake_ = true;
    name_ = name;
    level_ = 1;
    player_ptr = nullptr; // set player_ptr to nullptr first and we will assign it later after the user
}

//get hp
int Card::getHitPoints() const{
    return hp_;
}

//get tp
int Card::getTotalPoints()const{
    return tp_;
}

//get ap
int Card::getAttackPower() const{
    return atk_;
}

//get card availabiltiy (died or not)
bool Card::IsAwake() const{
    return awake_;
}

//get card name
std::string Card::getName() const{
    return name_;
}

//level up
int Card::getLevel() const{
    return level_;
}

// get player ptr
Player* Card::get_player_ptr() const{
    return player_ptr;
}

// change player ptr
void Card::change_player_ptr(Player* ptr){
    player_ptr = ptr;
}

void Card::takeDamage(int damage){
    int trueDamage = player_ptr->get_damage_reduction_total(damage);
    if (trueDamage >= hp_){
        hp_ = 0;
        awake_ = false;
    }
    else {
        hp_ -= trueDamage;
    }
}

void Card::cardMaxRecovery(){
    hp_ = tp_;
}

void Card::cardRecovery(int ra){
    hp_ += ra;
}



// The Wands

Wands::Wands(const std::string name, int tp, int ap)
     : Card(name, tp, ap){
        wand_dr = 0.05;
        wand_ab = 0.1;
        wand_hr = 0.15;
     }

void Wands::LevelUp(){
    level_++;
    tp_ += 100 * level_;
    /* 3 kinds of buffs based on levels*/
    int choice1 = -1, choice2 = -1;

    cout << "Choose the buff(s) you want to level up: " << endl;
    cout << "Buff1: damage_reduction -- " << wand_dr << endl;
    cout << "Buff2: attack_boost -- " << wand_ab << endl;
    cout << "Buff3: hp_recovery_rate -- " << wand_hr << endl;

    if (level_ < 4){
        cout << "You can choose 1 buff because your level < 5: (type in from 1, 2, or 3)" << endl;
        cin >> choice1;
        
        
        while(choice1 != 1 && choice1 != 2 && choice1 != 3){
            cout << "Invalid Input: Please Enter Again: " << endl;
            cin >> choice1;            
        }
        

        if(choice1 == 1){
            wand_dr += 0.1;
        } 
        else if (choice1 == 2){
            wand_ab += 0.1*level_;
        } 
        else if (choice1 == 3){
            wand_hr += 0.15*level_;
        }
    }
    else if (level_ >= 4 && level_ < 8){
        cout << "You can choose 2 buffs because your level < 5 (no duplication)" << endl;
        cin >> choice1 >> choice2;
        
        while (choice1 == choice2){
            cout << "No Duplicate Choices." << endl;
            cin >> choice1 >> choice2;
        }
        

        // Choice 1

        while(choice1 != 1 && choice1 != 2 && choice1 != 3){
            cout << "Invalid Input for your first choice: Please Enter Again: " << endl;
            cin >> choice1;
        }
        

        if(choice1 == 1){
            wand_dr += 0.1;
        } 
        else if (choice1 == 2){
            wand_ab += 0.1*level_;
        } 
        else if (choice1 == 3){
            wand_hr += 0.15*level_;
        }

        // Choice 2
        while(choice2 != 1 && choice2 != 2 && choice2 != 3){
            cout << "Invalid Input for your second choice: Please Enter Again: " << endl;
            cin >> choice2;
        }
        

        
        if(choice2 == 1){
            wand_dr += 0.1;
        } 
        else if (choice2 == 2){
            wand_ab += 0.15*level_;
        } 
        else if (choice2 == 3){
            wand_hr += 0.2*level_;
        }

    }
    else if (level_ >= 8){
        if(wand_dr + 0.1 < 0.85){
            wand_dr += 0.1;
        } else {
            cout << "You've reached the maximum level of damage reduction (85%)." << endl;
            wand_dr = 0.85;
        }
        
        wand_ab += 0.2*level_;
        wand_hr += 0.25*level_;
    }
}

double Wands::get_wand_dr() const{
    return wand_dr;
}

double Wands::get_wand_ab() const{
    return wand_ab;
}

double Wands::get_wand_hr() const{
    return wand_hr;
}

void Wands::display_card_details() const{
    cout << "Card: " << name_ << endl;
    if(hp_ == 0){cout << "Died." << endl; return;}
    cout << "hp: " << hp_ << "/" << tp_ << "   ";
    cout << "atk: " << atk_ << "   ";
    cout << "level: " << level_ << endl;
    
    cout << "Buff1: damage_reduction -- " << wand_dr << "   ";
    cout << "Buff2: attack_boost -- " << wand_ab << "   ";
    cout << "Buff3: hp_recovery_rate -- " << wand_hr << endl;
}





// The Cups

Cups::Cups(const std::string name, int tp, int ap, int ra)
    : Card(name, tp, ap){ recovery_amount = ra; }

void Cups::LevelUp(){
    level_++;
    tp_ += 100 * level_;
    recovery_amount += 75 * pow((double)level_, 1.25);

}

int Cups::get_recovery_amount() const{
    return recovery_amount;
}

void Cups::display_card_details() const{
    cout << "Card: " << name_ << endl;
    if(hp_ == 0){cout << "Died." << endl; return;}
    cout << "hp: " << hp_ << "/" << tp_ << "   ";
    cout << "atk: " << atk_ << "   ";
    cout << "level: " << level_ << "   ";

    cout << "recovery amount: " << recovery_amount << endl;
}





// The Swords

Swords::Swords(const std::string name, int tp, int ap)
     : Card(name, tp, ap){}
    
void Swords::LevelUp(){
    level_++;
    tp_ += 100 * level_;
    atk_ += 150 * level_;
}

void Swords::display_card_details() const{
    cout << "Card: " << name_ << endl;
    if(hp_ == 0){cout << "Died." << endl; return;}
    cout << "hp: " << hp_ << "/" << tp_ << "   ";
    cout << "atk: " << atk_ << "   ";
    cout << "level: " << level_ << endl;
}





// The Pentacles

Pentacles::Pentacles(const std::string name, int tp, int ap, int sp)
         : Card(name, tp, ap){ sp_increment = sp; }

void Pentacles::LevelUp(){
    level_++;
    tp_ += 100 * level_;
    sp_increment = level_ + (level_% 3);
}

int Pentacles::get_sp_increment() const{
    return sp_increment;
}

void Pentacles::display_card_details() const{
    cout << "Card: " << name_ << endl;
    if(hp_ == 0){cout << "Died." << endl; return;}

    cout << "hp: " << hp_ << "/" << tp_ << "   ";
    cout << "atk: " << atk_ << "   ";
    cout << "level: " << level_ << "   ";
    

    cout << "sp increment amount: " << sp_increment << " per round" << endl;
}




