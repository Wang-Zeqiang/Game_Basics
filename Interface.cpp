#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <limits>
#include "Cards.h"
#include "Players.h"
using namespace std;

void switch_rounds_in_main(vector<Player*> Players_lib);
bool check_duplicates(Player* curr, int idx);

int main(){
    //Define Library of Cards

    const Wands wand_lib("wand", 1000, 50);
    const Cups cup_lib("cup", 1500, 50, 100);
    const Swords sword_lib("sword", 1250, 150);
    const Pentacles pentacle_lib("pentacle", 1250, 50, 1);

    const vector<const Card*> Library = {&wand_lib, &cup_lib, &sword_lib, &pentacle_lib};

    unsigned int seed = 4; // can change later
    srand(seed);

    //Setup the players

    cout << "Player1 (moves first) enters name: " << endl;
    string uname1;
    cin >> uname1;
    cout << endl;

    Player Player1(true, uname1, 0, 0, 0, 5000);

    cout << "Player2 enters name: " << endl;
    string uname2;
    cin >> uname2;
    cout << endl;

    Player Player2(false, uname2, 0, 0, 0, 5000);

    vector<Player*> Players_lib = {&Player1, &Player2}; // Do I really need to declare this?


    //User have their own Cards -- copy constructor 
    // && Change the player_ptr of the card


    cout << "Now randomly assigning 5 cards to the players: " << endl << endl;

    for(int i = 0; i < 5; i++){
        Players_lib[0]->CardInHand.push_back(Library[rand() % Library.size()]->makeCopy());
        Players_lib[1]->CardInHand.push_back(Library[rand() % Library.size()]->makeCopy());
    }

    // Initialize the pointer of card to corresponding players
    for(int i = 0; i < 5; i++){
        Players_lib[0]->CardInHand[i]->change_player_ptr(Players_lib[0]);
        Players_lib[1]->CardInHand[i]->change_player_ptr(Players_lib[1]);
    }

    // Display Card Details for both players
    cout << Players_lib[0]->username_ << " "; 
    Players_lib[0]->display_userhp();
    cout << "Card Details: " << endl << endl;
    for(unsigned int i = 0; i < Players_lib[0]->CardInHand.size(); i++){
        Players_lib[0]->CardInHand[i]->display_card_details();
    }

    cout << endl << endl;

    cout << Players_lib[1]->username_ << " ";
    Players_lib[1]->display_userhp();
    cout << "Card Details: " << endl << endl;    
    for(unsigned int i = 0; i < Players_lib[1]->CardInHand.size(); i++){
        Players_lib[1]->CardInHand[i]->display_card_details();
    }

    cout << endl;

    cout << "Instructions: You have to first select a card then perform operations." << endl;
    cout << "============================================================" << endl;
    cout << "QUIT:           |   type: 'q'   |                |   (0sp)" << endl;
    cout << "SELECT CARD:    |   type: 's'   |   card_index   |   (0sp)" << endl;
    cout << "LEVEL UP:       |   type: 'l'   |   card_index   |   (3sp)" << endl;
    cout << "DRAW A CARD:    |   type: 'd'   |                |   (4sp)" << endl;
    cout << "ATTACK CARD:    |   type: 'ac'  |   card_index   |   (2sp)" << endl;
    cout << "ATTACK PLAYER:  |   type: 'ap'  |                |   (2sp)" << endl;
    // cout << "ADD BUFF:       |   type: 'b'   |   buff_type    |   (2sp)" << endl;
    cout << "HEAL CARD:      |   type: 'hc'  |   card_index   |   (2sp)" << endl;
    cout << "HEAL PLAYER:    |   type: 'hp'  |                |   (2sp)" << endl;
    cout << "ROUND OVER:     |   type: 'ro'  |                |   (0sp)" << endl;
    cout << "============================================================" << endl;
    cout << endl << endl;

    
    // User Interaction (I suppose there would be a bunch of if and else if statement)
    string cs = "?";
    while(!(Players_lib[0]->Lose()) && !(Players_lib[1]->Lose())){
    
        Player* curr = nullptr;
        Player* oppo = nullptr;
        int idx;
        int sp = 10;

        // determine current user
        if(Players_lib[0]->IsMyRound()){
            curr = Players_lib[0];
            oppo = Players_lib[1];
        } 
        else if (Players_lib[1]->IsMyRound()){
            curr = Players_lib[1];
            oppo = Players_lib[0];
        }
        else {
            cout << "Error in IsMyRound()." << endl; 
            return 1;
        }

        // Calculated the buff derived from the Wands Card && Pentacles Card

        for(unsigned int i = 0; i < curr->CardInHand.size(); i++){
            if(curr->CardInHand[i]->getName() == "wand"){
                curr->buff_damage_reduction(curr->CardInHand[i]->get_wand_dr());
                curr->buff_attack_boost(curr->CardInHand[i]->get_wand_ab());
                curr->buff_hp_recovery_rate(curr->CardInHand[i]->get_wand_hr());
            }
            else if(curr->CardInHand[i]->getName() == "pentacle"){
                sp += curr->CardInHand[i]->get_sp_increment();
            }
        }

        cout << "sp = " << sp << endl << endl;

        // Card Selection
        while(cs != "s"){
            cout << "You have to select a card first (type 's')." << endl;
            cin >> cs;
        }

        cout << "Enter the Index of Card you want to choose." << endl;
        cin >> idx;
        while (cin.fail() || idx - 1 < 0 || idx - 1 >= (int)curr->CardInHand.size()) {
            cout << "Invalid input! Please enter a valid card index: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> idx;
        }
        idx--;
        
        // Perform Operations
        cout << "Card Selected. Please Enter the Operation you wish to perform." << endl;
        cin >> cs;

        while(cs != "ro"){ 
            if(cs == "hp") {
                if (sp-2 >= 0 && curr->CardInHand[idx]->getName() == "cup"){
                    sp -= 2;
                    // Check if the card selected is "Cups"
                    int ra = curr->get_hp_recovery_total(curr->CardInHand[idx]->get_recovery_amount());
                    if (curr->get_user_hp() + ra > curr->get_user_tp()){
                        curr->user_maxRecovery();
                        cout << "User hitpoints set to max." << endl;
                    }
                    else{
                        curr->user_recovery(ra);
                        cout << "User hitpoints have recovered by " << ra << "." << endl;
                    }
                }
                else {
                    cout << "Error: not enough skill points or the card selected doesn't have the corresponding function." << endl;
                }
                
            }
            else if(cs == "hc") {
                if(sp-2 >= 0 && curr->CardInHand[idx]->getName() == "cup"){
                    sp -= 2;
                    
                    int idx2;
                    cout << "Select the card that you wish to heal: " << endl;
                    cin >> idx2;
                    while (cin.fail() || idx2 - 1 < 0 || idx2 - 1 >= (int)curr->CardInHand.size()) {
                        cout << "Invalid input! Please enter a valid card index: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin >> idx2;
                    }
                    idx2--;       
                    
                    int ra = curr->get_hp_recovery_total(curr->CardInHand[idx]->get_recovery_amount());

                    if (curr->CardInHand[idx2]->getHitPoints() + ra > curr->CardInHand[idx2]->getTotalPoints()){
                        //made a new function, card_maxRecovery(), cardRecovery()
                        curr->CardInHand[idx2]->cardMaxRecovery();
                        cout << "Card hitpoints set to max." << endl;
                    }
                    else{
                        curr->CardInHand[idx2]->cardRecovery(ra);
                        cout << curr->CardInHand[idx2]->getName() << " hitpoints have recovered by " << ra << "." << endl;
                    }
                }
                else {
                    cout << "Error, not enough skill points to perform action." << endl;
                }
            }
            else if(cs == "ap") {
                if(sp - 2 >= 0){
                    sp -= 2;

                    int dmg = curr->get_attack_boost_total(curr->CardInHand[idx]->getAttackPower());
                    oppo->user_takeDamage(dmg);
                    cout << oppo->username_ << ": ";
                    oppo->display_userhp();

                    if(oppo->Lose()){
                        break;
                    }
                }
                else {
                    cout << "Error, not enough skill points to perform action." << endl;
                }
            }
            else if(cs == "ac") {
                if(sp - 2 >= 0){
                    sp -= 2;

                    int dmg = curr->get_attack_boost_total(curr->CardInHand[idx]->getAttackPower());
                    cout << "Select the index of cards that you want to attack." << endl;

                    int idx2;
                    cin >> idx2;
                    while (cin.fail() || idx2 - 1 < 0 || idx2 - 1 >= (int)oppo->CardInHand.size()) {
                        cout << "Invalid input! Please enter a valid card index: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin >> idx2;
                    }
                    idx2--;

                    oppo->CardInHand[idx2]->takeDamage(dmg);
                    cout << "After attack: " << endl;
                    oppo->CardInHand[idx2]->display_card_details();

                    if(!oppo->CardInHand[idx2]->IsAwake()){
                        delete oppo->CardInHand[idx2];
                        oppo->CardInHand.erase(oppo->CardInHand.begin() + idx2);
                    }
                }
                else {
                    cout << "Error, not enough skill points to perform action." << endl;
                }
            }
            else if(cs == "d"){
                // Draw a card
                if(sp - 4 >= 0){
                    sp -= 4;
                    curr->CardInHand.push_back(Library[rand() % Library.size()]->makeCopy());
                }
                else {
                    cout << "Error, not enough skill points to perform action." << endl;
                }
            }
            else if(cs == "l"){
                if(sp - 3 >= 0){
                    if(check_duplicates(curr, idx)){
                        sp -= 3;
                        // Display All Card New
                    }
                    else{
                        cout << "No duplicated cards: Unable to level up." << endl;
                    }
                }
                else {
                    cout << "Error, not enough skill points to perform action." << endl;
                }
            }
            else if(cs == "s"){
                cout << "Reselect your card." << endl;
                cin >> idx;
                while (cin.fail() || idx - 1 < 0 || idx - 1 >= (int)curr->CardInHand.size()) {
                    cout << "Invalid input! Please enter a valid card index: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> idx;
                }
                idx--;
                cout << "Please Enter the Operation you wish to perform." << endl;
            }
            else if(cs == "q"){
                break;
            }
            
            cout << endl;
            for(unsigned int k = 0; k < curr->CardInHand.size(); k++){
                curr->CardInHand[k]->display_card_details();
            }
            cout << endl;
            cout << "sp = " << sp << endl;
            cin >> cs;
            cout << endl;
        }

        if (cs == "q"){
            break;
        }

        switch_rounds_in_main(Players_lib);
    }

    if(cs == "q"){cout << "Game Ended with Quit." << endl;}
    else if(Players_lib[0]->Lose()){cout << Players_lib[0]->username_ <<" Loses." << endl;}
    else {cout << Players_lib[1]->username_ <<" Loses." << endl;}

    for(unsigned int i = 0; i < Players_lib.size(); i++){
        for(unsigned int j = 0; j < Players_lib[i]->CardInHand.size(); j++){
            delete Players_lib[i]->CardInHand[j];
        }
    } 

    return 0;
}



// other functions in main
void switch_rounds_in_main(vector<Player*> Players_lib){
    for(unsigned int i = 0; i < Players_lib.size(); i++){
        Players_lib[i]->switch_rounds();
    }
}

/*check for duplicate card -- bool fuction -- if it exist -- levelup and return true, else return false*/
bool check_duplicates(Player* curr, int idx){
    for(unsigned int i = 0; i < curr->CardInHand.size(); i++){
        if((int)i != idx && curr->CardInHand[idx]->getName() == curr->CardInHand[i]->getName()){
            for(int j = 0; j < curr->CardInHand[i]->getLevel(); j++){
                curr->CardInHand[idx]->LevelUp();
            }
            delete curr->CardInHand[i];
            curr->CardInHand.erase(curr->CardInHand.begin() + i);
            return true;
        }
    }
    return false;
}








