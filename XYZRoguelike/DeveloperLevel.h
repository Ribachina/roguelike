#pragma once

#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "RatEnemy.h"
#include <vector>
#include "Wall.h"

using namespace XYZEngine;

namespace XYZRoguelike
{	
	class DeveloperLevel : public Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;
	private:
		std::shared_ptr<Player> player;
		std::shared_ptr<RatEnemy> ratEnemy;
		
		std::vector<std::shared_ptr<Wall>> walls;
	};
}