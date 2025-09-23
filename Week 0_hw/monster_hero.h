#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class Character
{
public:
	Character(const std::string& name, int hp, int attack)//Hero��Monster���е�����---����/Ѫ��/������
		:_name(name), _hp(hp), _attack(attack) {}

	virtual ~Character() = default;

	void normal_attack(Character& target)//Hero��Monster���������ͨ��������
	{
		std::cout << "Normal Attack: " << _name << " cause " << _attack << " point damage to " << target._name << std::endl;
		target.take_damage(_attack);
	}


	virtual void show_status() const = 0;//������ / ���麯��(����ʵ��)
	virtual void end_of_turn() = 0;//ս���غ���������

	bool is_alive() const// �ж��Ƿ���
	{
		return _hp > 0;
	}

public:
	void take_damage(int dmg) //�˺�����
	{
		dmg = (dmg < 0) ? 0 : dmg;
		_hp -= dmg;
		_hp = (_hp < 0) ? 0 : _hp;

	}
protected://����name, hp, attack
	std::string _name;
	int _hp;
	int _attack;
};

class Monster final : public Character//���м̳л���
{
public:
	Monster(const std::string& name, int hp, int attack): Character(name, hp, attack){}
	void show_status() const override//��̬, ���麯��ʵ��,Ѫ���͹�����
	{
		std::cout << _name << " HP: " << _hp << "  ATK: " << _attack << std::endl;
	}

	void end_of_turn() override {}
};

class Hero final : public Character
{
public:
	Hero(const std::string& name, int hp, int attack, int mp)
		: Character(name, hp, attack), _mp(mp), _mp_max(mp), _regen(0) {}
	// ---- 4 Skills ----
	void skill1(Character& t) 
	{ 
		cast_skill(t, 10, 10, "Skill 1"); 
	}
	void skill2(Character& t)
	{
		cast_skill(t, 15, 20, "Skill 2");
	}
	void skill3(Character& t)
	{
		cast_skill(t, 20, 30, "Skill 3"); 
	}
	void skill4(Character& t)
	{
		cast_skill(t, 30, 40, "Skill 4");
	}

	// �غϽ�����mp regen speed +1��regen = current speed
	void end_of_turn() override
	{
		_regen += 1;  // regen speed +1 each round
		int before = _mp;//֮ǰ�غϽ�����mp�ָ��ٶ�
		_mp = std::min(_mp_max, _mp + _regen);//���ܳ���mp_max����
		std::cout << _name << " MP +" << (_mp - before) << " (Regen_Speed " << _regen << "��MP " << _mp << "/" << _mp_max << ")\n";
	}

	void show_status() const override 
	{
		std::cout << _name << " HP: " << _hp << "  MP:" << _mp << "/" << _mp_max << "  ATK:" << _attack << "\n";
	}

private:
	void cast_skill(Character& target, int dmg, int cost, const char* skill_label) 
	{
		if (_mp < cost) 
		{
			std::cout << "MP Insufficient (Need " << cost << "��Current " << _mp << ")\n";
			return;
		}
		_mp -= cost;
		std::cout << _name << " Release [" << skill_label << "]��Consume " << cost << " Point MP��Cause " << dmg << " Point Damage\n";
		target.take_damage(dmg);
	}

private:
	int _mp = 0;
	int _mp_max = 0;
	int _regen = 0; // mp regen speed, +1 each round
};

