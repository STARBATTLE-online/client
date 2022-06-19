#pragma once
#include "HeadSprite.h"
#include <map>

bool fix = false;

enum class PowerTypes {
	Shield,
	Barrage,
	Speed
};


class ShipPower : public HeadSprite
{
public:
	ShipPower() {};
	~ShipPower() override {};

	bool IsEnable() {
		return is_enable;
	}

	PowerTypes GetPowerName() {
		return name;
	}


	int time;

protected:
	bool is_enable = false;
	PowerTypes name;
};


class Shield : public ShipPower
{
public:
	Shield(int t) {
		width = 280;
		height = 280;
		is_enable = true;
		name = PowerTypes::Shield;
		time = t;
	};
	~Shield() override {};

	void SetSpriteId(int id) {
		shield_sprite_id = id;
	}
	
	int GetSpriteId() {
		return shield_sprite_id;
	}

private:
	int shield_sprite_id = 1;
};

class Ship : public HeadSprite
{
public:
	Ship() {};
	Ship(int sprite_width, int sprite_height, int sprite_mass) {
		width = sprite_width;
		height = sprite_height;
	};
	virtual ~Ship() {};


	void SetRotation(Rotation rot) {
		rotation = rot;
	}


	Rotation GetRotation() {
		return rotation;
	}


	void Draw() {
		
		drawSprite(ship_sprites[{sprite_id, rotation}], x(), y());
		if (is_engine)
		{
			//drawSprite(engine_sprites[rotation], x() - (engine_width - width) / 2, y() - (engine_height - height) / 2);
			drawSprite(engine_sprites[{sprite_id, rotation}], (x() - ((engine_width - width) / 2)), (y() - ((engine_height - height) / 2)));
		}
		if (power)
		{
			if (power->GetPowerName() == PowerTypes::Shield)
			{
				if (power->time >= (200 / 3) * 2)
				{
					drawSprite(shield_sprites[1], (x() - ((power->GetSize().first - width) / 2)), (y() - ((power->GetSize().second - height) / 2)));
				}
				else if (power->time < (200 / 3) * 2 && power->time > 200 / 3)
				{
					drawSprite(shield_sprites[2], (x() - ((power->GetSize().first - width) / 2)), (y() - ((power->GetSize().second - height) / 2)));
				}
				else if (power->time <= 200 / 3 && power->time > 0)
				{
					drawSprite(shield_sprites[3], (x() - ((power->GetSize().first - width) / 2)), (y() - ((power->GetSize().second - height) / 2)));
				}
			}
		}
	}

	void DrawXY(int x, int y){
		drawSprite(ship_sprites[{sprite_id, rotation}], x, y);
		if (is_engine)
		{
			//drawSprite(engine_sprites[rotation], x() - (engine_width - width) / 2, y() - (engine_height - height) / 2);
			drawSprite(engine_sprites[{sprite_id, rotation}], (x - ((engine_width - width) / 2)), (y - ((engine_height - height) / 2)));
		}
		if (power)
		{
			if (power->GetPowerName() == PowerTypes::Shield)
			{
				if (power->time >= (200 / 3) * 2)
				{
					drawSprite(shield_sprites[1], (x - ((power->GetSize().first - width) / 2)), (y - ((power->GetSize().second - height) / 2)));
				}
				else if (power->time < (200 / 3) * 2 && power->time > 200 / 3)
				{
					drawSprite(shield_sprites[2], (x - ((power->GetSize().first - width) / 2)), (y - ((power->GetSize().second - height) / 2)));
				}
				else if (power->time <= 200 / 3 && power->time > 0)
				{
					drawSprite(shield_sprites[3], (x - ((power->GetSize().first - width) / 2)), (y - ((power->GetSize().second - height) / 2)));
				}
			}
		}
	}

	void SetHP(int hp) {
		if (hit_points != hp)
		{
			std::cout << "HP: " << hp << "\n";
		}
		hit_points = hp;
	}

	void SetEngine(bool flag) {
		is_engine = flag;
	}

	bool IsPower() {
		if (power)
		{
			return true;
		}
		return false;
	}

	bool IsShield() {
		if (power->GetPowerName() == PowerTypes::Shield)
		{
			return true;
		}
		return false;
	}

	void SetShield(int t) {
		if (power)
		{
			if (power->GetPowerName() == PowerTypes::Shield)
			{
				std::cout << "shield: " << t << "\n";
				
				power->time = t;
			}
		}
		else
		{
			power = new Shield(t);
		}
	}

	int sprite_id;


	ShipPower* power = nullptr;
protected: //?
	Rotation rotation;
	int engine_width;
	int engine_height;
	bool is_engine = false;
	int hit_points;

};

class MainHeroShip : public Ship
{
public:
	MainHeroShip(int id = 4) {
		sprite_id = id;

		rotation = Rotation::Top;
		width = 192;
		height = 192;
		engine_width = 424;
		engine_height = 424;
	};
	~MainHeroShip() {};

	bool GetRotationByMouse(int x_mouse, int y_mouse) {
		Rotation temp_rot = rotation;
		if (x_mouse <= window_width / 2) {
			if (abs(x_mouse - window_width / 2) > abs(y_mouse - window_height / 2))
				SetRotation(Rotation::Left);
			else {
				if (y_mouse <= window_height / 2)
					SetRotation(Rotation::Top);
				else
					SetRotation(Rotation::Bottom);
			}
		}
		else {
			if (abs(x_mouse - window_width / 2) > abs(y_mouse - window_height / 2))
				SetRotation(Rotation::Right);
			else {
				if (y_mouse <= window_height / 2)
					SetRotation(Rotation::Top);
				else
					SetRotation(Rotation::Bottom);
			}
		}

		if (temp_rot!= rotation)
		{
			return 1;
		}
		return 0;
	}


private:
};

class EnemyShip : public Ship
{
public:
	EnemyShip(int x, int y, Rotation rot, int id = 3) {
		sprite_id = id;
		width = 192;
		height = 192;
		SetRotation(rot);
		SetCoordsByCenter(x, y);
		engine_width = 424;
		engine_height = 424;
	};
	~EnemyShip() {};

private:

};


