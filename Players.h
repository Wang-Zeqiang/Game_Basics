#ifndef PLAYERS_H
#define PLAYERS_H

#include <vector>
#include <string>

class Card;

class Player {
    public:

        Player(bool myRound_, std::string username, double damage_reduction,  
            double attack_boost, double hp_recovery_rate, int usertp);
        
        // buff included damage
        int get_damage_reduction_total(const int damage) const; // value
        int get_attack_boost_total(const int atk) const; // value
        int get_hp_recovery_total(const int hr) const; // value

        void buff_damage_reduction(const double buff);
        void buff_attack_boost(const double buff);
        void buff_hp_recovery_rate(const double buff);
        
        void switch_rounds();
        bool IsMyRound() const;
        bool Lose() const;

        void display_userhp() const;
        void user_recovery(int ra);
        void user_maxRecovery();
        void user_takeDamage(int damage);
        

        int get_user_hp() const;
        int get_user_tp() const;


        // public data structure
        
        std::string username_;
        std::vector<Card*> CardInHand; // you can have more than 3 cards in hand
        //std::vector<Card*> Occupation_Card; // Big Arcana Card

    protected:

        bool myRound_;
        bool Died;

        double damage_reduction_; // primary attribute that depends on the occupation
        double damage_reduction_buff_; // all initialize to 0 --> calculated each round

        double attack_boost_; // primary attribute that depends on the occupation
        double attack_boost_buff_; // all initialize to 0 --> calculated each round

        double hp_recovery_rate_; // primary attribute that depends on the occupation
        double hp_recovery_rate_buff_; // all initialize to 0 --> calculated each round

        int userhp_;
        int usertp_;
};

/* -- Occupation (Big Arcana) -- Discuss Later
class The_Priestess: public Player{
    // when recover hp --> also do damage based on hp_recovery_rate and recovery amount
    public:

    protected:
}

class The_Chariot: public Card{
    // Follow-up attack 
    public:

    protected:
}
*/

#endif
