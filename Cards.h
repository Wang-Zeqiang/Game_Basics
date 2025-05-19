#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <vector>

class Player;

class Card {
    public:

        Card(std::string name, int tp, int ap);
        
        int getHitPoints() const;
        int getTotalPoints() const;
        int getAttackPower() const;
        bool IsAwake() const;
        std::string getName() const;
        int getLevel() const;
        Player* get_player_ptr() const;

        void change_player_ptr(Player* ptr);
        void takeDamage(int damage);

        virtual void LevelUp() = 0;
        virtual void display_card_details() const = 0;
        virtual Card* makeCopy() const = 0;
        virtual ~Card() = default;

        virtual double get_wand_dr() const {return 0;}
        virtual double get_wand_ab() const {return 0;}
        virtual double get_wand_hr() const {return 0;}
        virtual int get_sp_increment() const {return 0;}
        virtual int get_recovery_amount() const {return 0;}

        void cardMaxRecovery();
        void cardRecovery(int ra);
        


    protected:
        int hp_; // hitpoints
        int tp_; // totalpoints
        int atk_; // attackpower
        bool awake_; // awake?
        std::string name_;
        int level_; // can level up
        Player* player_ptr;

};

// Small Arcana:

class Wands: public Card{
    // card of buff -- based on level
    public:
        Wands(const std::string name, int tp, int ap); // Constructor
        // using choice to determine which feature do you want to level up 
        // (1. damage_reduction 2. attack_boost 3. hp_recovery_rate)
        void LevelUp(); 
        void display_card_details() const;
        Card* makeCopy() const override {return new Wands(*this);} // use the default copy constructor

        double get_wand_dr() const;
        double get_wand_ab() const;
        double get_wand_hr() const;

    private:
        double wand_dr;
        double wand_ab;
        double wand_hr;
};

class Cups: public Card{
    // cards that recovery hp
    public:
        Cups(const std::string name, int tp, int ap, int ra);
        void LevelUp();
        int get_recovery_amount() const;
        void display_card_details() const;
        Card* makeCopy() const override{return new Cups(*this);}

    private:
        int recovery_amount;
        
};

class Swords: public Card{
    // attack other cards
    public:
        Swords(const std::string name, int tp, int ap);
        void LevelUp();
        void display_card_details() const;
        Card* makeCopy() const override{return new Swords(*this);}
};

class Pentacles: public Card{
    // increase user's skill points
    public:
        Pentacles(const std::string name, int tp, int ap, int sp);
        void LevelUp();
        int get_sp_increment() const;
        void display_card_details() const;
        Card* makeCopy() const override{return new Pentacles(*this);}

    private:
        int sp_increment;
};

#endif
