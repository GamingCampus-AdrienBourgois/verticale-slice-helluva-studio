#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/SceneManager.h"
#include "Managers/AssetManager.h"
#include "Components/SpriteRenderer.h"
#include "Components/Animation.h"
#include "Components/RigidBody2D.h"
#include "Components/ComponentsGame/WeaponsContainer.h"
#include "Components/ComponentsGame/Bullet.h"
#include "Components/ComponentsGame/Sword.h"
#include "Components/ComponentsGame/Gun.h"
#include "Components/Entity/Character.h"
#include "Components/Inputs/InputCharacter.h"
#include "Components/Shapes/Rectangle.h"


GameObject* BuilderEntityGameObject::CreateBulletGameObject(const std::string& _name, sf::Texture* _textureBullet, GameObject* _player, const float& _scalex, const float& _scaley, const float& _damage, const float& _speed, const Maths::Vector2f& _direction)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_player->GetPosition().GetX(), _player->GetPosition().GetY()));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_textureBullet);
	sprite->SetSprite();

	Bullet* bullet = gameObject->CreateComponent<Bullet>();
	bullet->SetSpeed(_speed);
	bullet->SetDamage(_damage);

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	rigidBody2D->SetIsGravity(false);
	rigidBody2D->AddForces(_direction * bullet->GetSpeed());

	return gameObject;
}

GameObject* BuilderEntityGameObject::CreateCharacterGameObject(const std::string& _name, const float& _x, const float& _y, sf::Texture* texture, const float& scalex, const float& scaley)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetDepth(1.f);
	gameObject->SetScale(Maths::Vector2f(scalex, scaley));

	Character* character = gameObject->CreateComponent<Character>();

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(true);
	rigidBody2D->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	rigidBody2D->SetScale(scalex, scaley);

	Animation* idle = gameObject->CreateComponent<Animation>();
	idle->SetLoop(-1);
	idle->SetName("idle");
	idle->SetFrame(10);
	idle->SetAnimationTime(1);
	idle->SetSpriteSheet(AssetManager::GetAsset("idleCharacter"));

	Animation* jump = gameObject->CreateComponent<Animation>();
	jump->SetLoop(-1);
	jump->SetName("jump");
	jump->SetFrame(3);
	jump->SetAnimationTime(1);
	jump->SetSpriteSheet(AssetManager::GetAsset("jumpCharacter"));

	Animation* run = gameObject->CreateComponent<Animation>();
	run->SetLoop(-1);
	run->SetName("run");
	run->SetFrame(8);
	run->SetAnimationTime(1);
	run->SetSpriteSheet(AssetManager::GetAsset("runCharacter"));

	Animation* shootArm = gameObject->CreateComponent<Animation>();
	shootArm->SetLoop(-1);
	shootArm->SetName("shootArm");
	shootArm->SetFrame(10);
	shootArm->SetAnimationTime(1);
	shootArm->SetSpriteSheet(AssetManager::GetAsset("shootArm"));
	
	Animation* shootBody = gameObject->CreateComponent<Animation>();
	shootBody->SetLoop(-1);
	shootBody->SetName("shootBody");
	shootBody->SetFrame(10);
	shootBody->SetAnimationTime(1);
	shootBody->SetSpriteSheet(AssetManager::GetAsset("shootBody"));

	idle->Play();

	InputCharacter* inputCharacter = gameObject->CreateComponent<InputCharacter>();

	WeaponsContainer* weaponsContainer = gameObject->CreateComponent<WeaponsContainer>();
	weaponsContainer->AddNewWeapon(BuilderEntityGameObject::CreateWeaponGameObject(std::string("Gun"), gameObject, Weapon::TypeWeapon::Gun, _x, _y, 25.f, 100.f, 0.02f));
	/*HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(player->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(player->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(sprite->GetBounds().y / 2 + 50.f);
	healthPointBar->SetSize(sprite->GetBounds().x, 5);
	healthPointBar->SetScale(scalex, scaley);
	healthPointBar->SetHealthPointBar();*/

	return gameObject;
}

GameObject* BuilderEntityGameObject::CreateWeaponGameObject(const std::string& _name, GameObject* _player, const Weapon::TypeWeapon& _typeWeapon, const float& _positionX, const float& _positionY, const float& _damage, const float& _range, const float& _attackSpeed)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_positionX, _positionY));

	//RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	//rigidBody2D->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	//rigidBody2D->SetScale(0.5, 0.5);

	WeaponsContainer* weaponsContainer = _player->GetComponent<WeaponsContainer>();
	weaponsContainer->AddNewWeapon(gameObject);

	Weapon* weapon;
	if (_typeWeapon == Weapon::TypeWeapon::Gun) weapon = gameObject->CreateComponent<Gun>();
	else if (_typeWeapon == Weapon::TypeWeapon::Sword) weapon = gameObject->CreateComponent<Sword>();
	else weapon = gameObject->CreateComponent<Weapon>();
	weapon->SetName(_name);
	weapon->SetAttackSpeed(_attackSpeed);
	weapon->SetDamage(_damage);
	weapon->SetRange(_range);
	weapon->SetIndexWeapon(weaponsContainer->GetIndexActualWeapon());

	return gameObject;
}

GameObject* BuilderEntityGameObject::CreatePlateformGameObject(const std::string& _name, const float& _positionX, const float& _positionY, const float& _scalex, const float& _scaley)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_positionX, _positionY));
	gameObject->SetScale(Maths::Vector2f(_scalex, _scaley));


	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);
	rigidBody2D->SetSize(200.f, 50.f);
	rigidBody2D->SetScale(_scalex, _scaley);

	Rectangle* rectangle = gameObject->CreateComponent<Rectangle>();
	rectangle->SetSize(200.f, 50.f);
	rectangle->SetScale(_scalex, _scaley);

	return gameObject;

}

