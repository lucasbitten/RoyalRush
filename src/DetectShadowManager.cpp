#include "DetectShadowManager.h"
#include <algorithm>

int DetectShadowManager::squaredDistance(glm::vec2 P1, glm::vec2 P2)
{
	const int diffOfXs = P2.x - P1.x;
	const int diffOfYs = P2.y - P1.y;
	const int result = diffOfXs * diffOfXs + diffOfYs * diffOfYs;

	return result;

}

void DetectShadowManager::playerOnShadow(Shadow* shadow, Player* player)
{
	const glm::vec2 playerPosition = player->getPosition();
	const glm::vec2 shadowPosition = shadow->getPosition();

	const glm::vec2 playerSize = glm::vec2(player->getWidth(), player->getHeight());
	const glm::vec2 shadowSize = glm::vec2(shadow->getWidth(), shadow->getHeight());


	const int halfHeights = (playerSize.y + shadowSize.y) * 0.5;
	const int halfWidth = (playerSize.x + shadowSize.x) * 0.5;


	if (DetectShadowManager::squaredDistance(playerPosition, shadowPosition) < halfHeights * halfHeights ||
		DetectShadowManager::squaredDistance(playerPosition, shadowPosition) < halfWidth * halfWidth)
	{

		glm::vec2 squareAngle = glm::vec2(shadowPosition.x - shadowSize.x / 2, shadowPosition.y + shadowSize.y / 2);
		glm::vec2 pointOnX = glm::vec2(shadowPosition.x + shadowSize.x / 2, shadowPosition.y + shadowSize.y / 2);
		glm::vec2 pointOnY = glm::vec2(shadowPosition.x - shadowSize.x / 2, shadowPosition.y - shadowSize.y / 2);
		glm::vec2 outsidePoint = glm::vec2(shadowPosition.x + shadowSize.x / 2, shadowPosition.y - shadowSize.y / 2);

		glm::vec2 playerRightBottomPoint = glm::vec2(playerPosition.x + playerSize.x / 2, playerPosition.y + playerSize.y / 2);
		//glm::vec2 playerLeftBottomPoint = glm::vec2(playerPosition.x - playerSize.x / 2, playerPosition.y + playerSize.y / 2);
		glm::vec2 playerRightTopPoint = glm::vec2(playerPosition.x + playerSize.x / 2, playerPosition.y - playerSize.y / 2);
		glm::vec2 playerLeftTopPoint = glm::vec2(playerPosition.x - playerSize.x / 2, playerPosition.y - playerSize.y / 2);



		if (playerRightBottomPoint.x < pointOnX.x && playerRightBottomPoint.x > squareAngle.x &&
			playerRightBottomPoint.y < pointOnX.y && playerRightBottomPoint.y > pointOnY.y)
		{

			if (glm::distance(playerRightTopPoint, squareAngle) < glm::distance(playerRightTopPoint, outsidePoint))
			{
				shadow->playerAtShadow = true;
			}
			else
			{
				shadow->playerAtShadow = false;

			}
		}
		else {
			shadow->playerAtShadow = false;

		}
	}
}

DetectShadowManager::DetectShadowManager()
{

}

DetectShadowManager::~DetectShadowManager()
{

}
