#include "CollisionManager.h"
#include "Util.h"
#include <algorithm>
#include  "Player.h"
#include "Ground.h"
#include "Enemy.h"
#include "Game.h"
#include "GameManager.h"


int CollisionManager::squaredDistance(glm::vec2 P1, glm::vec2 P2)
{
	int diffOfXs = P2.x - P1.x;
	int diffOfYs = P2.y - P1.y;
	int result = diffOfXs * diffOfXs + diffOfYs * diffOfYs;

	return result;
}

bool CollisionManager::squaredRadiusCheckPlayer(Player* player, GameObject* object2)
{

	glm::vec2 P1 = player->getPosition();
	glm::vec2 P2 = object2->getPosition();
	int halfHeights = (player->getHeight() + object2->getHeight()) * 0.5f;

	//if (glm::distance(P1, P2) < halfHeights) {

	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {

		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			switch (object2->getType())
			{
			case  GROUND:

				if ( P1.x > P2.x && P1.y > P2.y)
				{

					float overlapping = P2.x + object2->getWidth() *0.5f - P1.x + player->getWidth() *0.5f;
					player->setVelocity(glm::vec2(0, player->getVelocity().y));

					player->setPosition(glm::vec2(player->getPosition().x + overlapping +10, player->getPosition().y));
				} else if( P1.x < P2.x && P1.y > P2.y)
				{

					float overlapping = P1.x + player->getWidth() * 0.5f - P2.x + object2->getWidth() * 0.5f;

					
					player->setPosition(glm::vec2(player->getPosition().x - overlapping - 2, player->getPosition().y));
					player->setVelocity(glm::vec2(0, player->getVelocity().y));
				}
			break;

			case  GROUND_PLATFORM:

				if (P1.x > P2.x&& P1.y > P2.y)
				{
					std::cout << "Collision on the right of ground!" << std::endl;

					float overlapping = P2.x + object2->getWidth() * 0.5f - P1.x + player->getWidth() * 0.5f;
					player->setVelocity(glm::vec2(0, player->getVelocity().y));

					player->setPosition(glm::vec2(player->getPosition().x + overlapping + 10, player->getPosition().y));
				}
				else if (P1.x < P2.x && P1.y > P2.y)
				{
					std::cout << "Collision on the left of ground!" << std::endl;

					float overlapping = P1.x + player->getWidth() * 0.5f - P2.x + object2->getWidth() * 0.5f;


					player->setPosition(glm::vec2(player->getPosition().x - overlapping - 2, player->getPosition().y));
					player->setVelocity(glm::vec2(0, player->getVelocity().y));
				}
				break;

			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}

			return true;
		}
		return false;
	}
	else
	{
		object2->setIsColliding(false);
		return false;
	}
}


bool CollisionManager::squaredRadiusCheck(GameObject* object1, GameObject* object2)
{

	glm::vec2 P1 = object1->getPosition();
	glm::vec2 P2 = object2->getPosition();
	int halfHeights = (object1->getHeight() + object2->getHeight()) * 0.5f;

	//if (glm::distance(P1, P2) < halfHeights) {

	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {

		
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			switch (object2->getType()) {
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}

			return true;
		}
		return false;
	}
	else
	{
		object2->setIsColliding(false);
		return false;
	}
}


bool CollisionManager::AABBCheckPlayer(Player* player, GameObject* object2)
{
	// prepare relevant variables
	glm::vec2 P1 = player->getPosition();
	glm::vec2 P2 = object2->getPosition();
	float P1width = player->getWidth();
	float P1height = player->getHeight();
	float P2width = object2->getWidth();
	float P2height = object2->getHeight();

	if(P2.x < P1.x)
	{
		P2.x = P2.x - (P2width / 2);
	} else
	{
		P2.x = P2.x + (P2width / 2);
	}
	

	if (
		P1.x < P2.x + P2width &&
		P1.x + P1width > P2.x&&
		P1.y < P2.y + P2height &&
		P1.y + P1height > P2.y
		)
	{
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);



			switch (object2->getType()) {
			case  GROUND:
				std::cout << "#####################" << std::endl;
				std::cout << "Player X  = " << P1.x;
				std::cout << " Player Height = " << P1height;
				std::cout << " Player Y = " << P1.y;
				std::cout << " Player Width = " << P1width << std::endl;
				std::cout << "Ground X = " << P2.x;
				std::cout << " Ground Height = " << P2height;
				std::cout << " Ground Y = " << P2.y;
				std::cout << " Ground Width  = " << P2width << std::endl;				
				std::cout << "#####################" << std::endl;
				player->jumping = false;
				player->jumpTime = 0;
				player->setPosition(glm::vec2(P1.x, P2.y - object2->getHeight() / 2 - player->getHeight() / 2));

				break;
			case ENEMY:
				player->jumping = false;
				player->jumpTime = 0;
				player->setPosition(glm::vec2(P1.x, P2.y - object2->getHeight() / 2 - player->getHeight() / 2));
				object2->setPosition(glm::vec2(P2.x, P2.y));

				if(TheGameManager::Instance()->getPlayerLives() == 0)
				{
					TheGame::Instance()->changeSceneState(SceneState::GAME_OVER_SCENE);

				} else
				{
					TheGameManager::Instance()->setPlayerLives(TheGameManager::Instance()->getPlayerLives() - 1);
					TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				}
				
				break;
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}
			
			return true;
		}
		return false;
	}
	else
	{
		object2->setIsColliding(false);
		return false;
	}

	return false;
}



bool CollisionManager::AABBCheck(GameObject* object1, GameObject* object2)
{
	// prepare relevant variables
	glm::vec2 P1 = object1->getPosition();
	glm::vec2 P2 = object2->getPosition();
	float P1width = object1->getWidth();
	float P1height = object1->getHeight();
	float P2width = object2->getWidth();
	float P2height = object2->getHeight();

	if (
		P1.x < P2.x + P2width &&
		P1.x + P1width > P2.x&&
		P1.y < P2.y + P2height &&
		P1.y + P1height > P2.y
		)
	{
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);


			if(object1->getType() == PLAYER)
			{
				std::cout << "Player collided!" << std::endl;
				switch (object2->getType()) {
				case  GROUND:
										
					std::cout << "Collision with Ground type!" << std::endl;
					std::cout << "Position: (" << object1->getPosition().x << "," << object1->getPosition().y << ")" << std::endl;
					std::cout << "Player Instance Position: (" << Player::Instance()->getPosition().x << "," << Player::Instance()->getPosition().y << ")" << std::endl;

					Player::Instance()->jumping = false;
					Player::Instance()->jumpTime = 0;
					Player::Instance()->setPosition(glm::vec2(P1.x, P2.y - object2->getHeight() / 2 - Player::Instance()->getHeight() / 2));

					break;


				default:
					//std::cout << "Collision with unknown type!" << std::endl;
					break;
				}
			}

			
			switch (object2->getType()) {
			case PLAYER:
				std::cout << "Collision with Platform!" << std::endl;
				TheSoundManager::Instance()->playSound("yay", 0);
				break;
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}

			return true;
		}
		return false;
	}
	else
	{
		object2->setIsColliding(false);
		return false;
	}

	return false;
}

bool CollisionManager::lineLineCheck(glm::vec2 line1Start, glm::vec2 line1End, glm::vec2 line2Start, glm::vec2 line2End)
{
	float x1 = line1Start.x;
	float x2 = line1End.x;
	float x3 = line2Start.x;
	float x4 = line2End.x;
	float y1 = line1Start.y;
	float y2 = line1End.y;
	float y3 = line2Start.y;
	float y4 = line2End.y;



	
	// calculate the distance to intersection point
	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		return true;
	}

	return false;
}

bool CollisionManager::lineRectCheck(Player* player, glm::vec2 line1End, Ground* ground, float recWidth, float recHeight)
{
	float x1 = player->getPosition().x;
	float x2 = line1End.x;
	float y1 = player->getPosition().y;
	float y2 = line1End.y;
	float rx = ground->getPosition().x - ground->getWidth()/2;
	float ry = ground->getPosition().y;
	float rw = recWidth;
	float rh = recHeight;

	//TODO FIX THIS

	// check if the line has hit any of the rectangle's sides
	// uses the Line/Line function below
	bool left = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx, ry + rh));
	bool right = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx + rw, ry), glm::vec2(rx + rw, ry + rh));
	bool top = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx + rw, ry));
	bool bottom = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry + rh), glm::vec2(rx + rw, ry + rh));

	// if ANY of the above are true, the line
	// has hit the rectangle
	if (top) {



		if (ry < player->getPosition().y + 50 && player->getVelocity().y > 0)
		{
			ground->playerAtGround = true;
			player->stopJump(glm::vec2(player->getPosition().x, ground->getPosition().y - recHeight * 0.5));
			return true;
		}
		
	} 	
	ground->playerAtGround = false;
	return false;
}

bool CollisionManager::lineRectCheck(Player* player, glm::vec2 line1End, GroundPlatform* ground, float recWidth, float recHeight)
{
	float x1 = player->getPosition().x;
	float x2 = line1End.x;
	float y1 = player->getPosition().y;
	float y2 = line1End.y;
	float rx = ground->getPosition().x - ground->getWidth() * 0.5f;
	float ry = ground->getPosition().y - ground->getHeight() * 0.5f;
	float rw = recWidth;
	float rh = recHeight;

	//TODO FIX THIS

	// check if the line has hit any of the rectangle's sides
	// uses the Line/Line function below
	bool left = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx, ry + rh));
	bool right = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx + rw, ry), glm::vec2(rx + rw, ry + rh));
	bool top = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx + rw, ry));
	bool bottom = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry + rh), glm::vec2(rx + rw, ry + rh));

	// if ANY of the above are true, the line
	// has hit the rectangle
	if (top) {

		if(ry < player->getPosition().y +20 && player->getVelocity().y > 0)
		{
			ground->playerAtGround = true;
			player->stopJump(glm::vec2(player->getPosition().x, ground->getPosition().y - recHeight * 0.5));
			return true;
		}



	}
	ground->playerAtGround = false;
	return false;
}


int CollisionManager::minSquaredDistanceLineLine(glm::vec2 line1Start, glm::vec2 line1End, glm::vec2 line2Start, glm::vec2 line2End)
{
	glm::vec2 u = line1End - line1Start;
	glm::vec2 v = line2End - line2Start;
	glm::vec2 w = line1Start - line2Start;
	float a = Util::dot(u, u);         // always >= 0
	float b = Util::dot(u, v);
	float c = Util::dot(v, v);         // always >= 0
	float d = Util::dot(u, w);
	float e = Util::dot(v, w);
	float D = a * c - b * b;					// always >= 0
	float sc, tc;

	// compute the line parameters of the two closest points
	if (D < Util::EPSILON) {					// the lines are almost parallel
		sc = 0.0;
		tc = (b > c ? d / b : e / c);			// use the largest denominator
	}
	else {
		sc = (b * e - c * d) / D;
		tc = (a * e - b * d) / D;
	}

	// get the difference of the two closest points
	glm::vec2 dP = w + (sc * u) - (tc * v);  // =  L1(sc) - L2(tc)

	float norm = Util::dot(dP, dP);
	return norm;
}

int CollisionManager::circleAABBsquaredDistance(glm::vec2 circleCentre, int circleRadius, glm::vec2 boxStart, int boxWidth, int boxHeight)
{
	float dx = std::max(boxStart.x - circleCentre.x, 0.0f);
	dx = std::max(dx, circleCentre.x - (boxStart.x + boxWidth));
	float dy = std::max(boxStart.y - circleCentre.y, 0.0f);
	dy = std::max(dy, circleCentre.y - (boxStart.y + boxHeight));

	return (dx * dx) + (dy * dy);
}

bool CollisionManager::circleAABBCheck(GameObject* object1, GameObject* object2)
{
	// circle
	glm::vec2 circleCentre = object1->getPosition();
	int circleRadius = std::max(object1->getWidth() * 0.5f, object1->getHeight() * 0.5f);
	// aabb
	int boxWidth = object2->getWidth();
	int halfBoxWidth = boxWidth * 0.5f;
	int boxHeight = object2->getHeight();
	int halfBoxHeight = boxHeight * 0.5f;

	glm::vec2 boxStart = object2->getPosition() - glm::vec2(boxWidth * 0.5f, boxHeight * 0.5f);

	if (circleAABBsquaredDistance(circleCentre, circleRadius, boxStart, boxWidth, boxHeight) <= (circleRadius * circleRadius))
	{
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			glm::vec2 attackVector = object1->getPosition() - object2->getPosition();
			glm::vec2  normal = glm::vec2(0.0f, -1.0f);


			/*std::cout << "=====================================" << std::endl;
			std::cout << "AttackX: " << attackVector.x << std::endl;
			std::cout << "AttackY: " << attackVector.y << std::endl;*/
			float dot = Util::dot(attackVector, normal);
			/*std::cout << "dot: " << dot << std::endl;*/
			float angle = acos(dot / Util::magnitude(attackVector)) * Util::Rad2Deg;
			//std::cout << "Angle: " << angle << std::endl;

			switch (object2->getType()) {
			case PLAYER:
				std::cout << "Collision with Planet!" << std::endl;
				TheSoundManager::Instance()->playSound("yay", 0);
				break;
		
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}

			return true;
		}
		return false;
	}
	else
	{
		object2->setIsColliding(false);
		return false;
	}

	return false;
}


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}