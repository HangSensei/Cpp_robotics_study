#pragma once
#include "monster_hero.h"

class Game 
{
public:
    Game() 
    {
        init_characters();
    }

    void run() 
    {
        while (hero.is_alive() && monster.is_alive())//回合控制,只要两个都活着就继续回合
        {
            show_status();
            char input = user_input();
            if (!process_user_input(input)) 
                break;
            if (!monster.is_alive())
                break;

            // Monster Turn
            monster_turn();

            if (!hero.is_alive())
                break;

            // Hero Turn Finished： mp regen speed +1 / mp regen
            hero.end_of_turn();
        }
        show_result();//最终战斗结算
    }

private:
    Hero hero{ "", 0, 0, 0 };     // 对象默认值
    Monster monster{ "", 0, 0 };  // 同上

    void init_characters() 
    {
        std::string hname = "Hero";
        int hp, mp, atk;
        std::cout << "---- Hero Initialization ----\n";
        std::cout << "Enter Hero HP: ";
        std::cin >> hp;
        std::cout << "Enter Hero MP: ";
        std::cin >> mp;
        std::cout << "Enter Hero ATTACK: ";
        std::cin >> atk;
        hero = Hero(hname, hp, atk, mp);//无名临时对象 + 编译器生成的默认拷贝赋值运算符

        std::string mname = "Monster";
        int mhp, matk;
        std::cout << "\n---- Monster Initialization ----\n";
        std::cout << "Enter Monster HP: ";
        std::cin >> mhp;
        std::cout << "Enter Monster ATTACK: ";
        std::cin >> matk;
        monster = Monster(mname, mhp, matk);
    }

    void show_status() 
    {
        hero.show_status();
        monster.show_status();
    }

    char user_input() 
    {
        std::cout << "Choose Action:\n"
            "  [a] Normal Attack\n"
            "  [1] Skill1 (DMG 10, Cost 10 MP)\n"
            "  [2] Skill2 (DMG 15, Cost 20 MP)\n"
            "  [3] Skill3 (DMG 20, Cost 30 MP)\n"
            "  [4] Skill4 (DMG 30, Cost 40 MP)\n"
            "  [q] Exit Game\n";
        char c; 
        std::cin >> c;
        return c;
    }

    bool process_user_input(char input)
    {
        switch (input)
        {
        case 'a':
            hero.normal_attack(monster);
            break;
        case '1':
            hero.skill1(monster);
            break;
        case '2':
            hero.skill2(monster);
            break;
        case '3':
            hero.skill3(monster);
            break;
        case '4':
            hero.skill4(monster);
            break;
        case 'q':
            return false;
        default:
            std::cout << "Invalid User Input\n";
            return true;
        }
        return true;
    }

    void monster_turn() 
    {
        if (monster.is_alive())
            monster.normal_attack(hero);
    }

    void show_result() 
    {
        std::cout << "\nBattle Finished：";

        if (hero.is_alive() && !monster.is_alive())
            std::cout << "YOU WIN!" << std::endl;
        else if (!hero.is_alive())
            std::cout << "YOU DIED" << std::endl;
        else 
            std::cout << "GAME OVER!\n";
    }
};

