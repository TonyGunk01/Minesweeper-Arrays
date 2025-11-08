#include "../../header/GameWindow/GameWindowManager.h"

using namespace sf;

namespace GameWindow
{
	GameWindowManager::GameWindowManager() 
	{ 
		initialize(); 
	}

	GameWindowManager::~GameWindowManager() 
	{ 
		onDestroy(); 
	}

	void GameWindowManager::initialize()
	{
		game_window = createGameWindow();
		setFrameRate(frame_rate);
	}

	sf::RenderWindow* GameWindowManager::createGameWindow()
	{
		configureVideoMode();
		return new RenderWindow(video_mode, game_window_title, Style::Fullscreen);
	}

	void GameWindowManager::configureVideoMode()
	{
		video_mode = *(new VideoMode(game_window_width, game_window_height, VideoMode::getDesktopMode().bitsPerPixel));
	}

	void GameWindowManager::onDestroy() 
	{ 
		delete(game_window); 
	}

	void GameWindowManager::setFrameRate(int frame_rate_to_set) 
	{ 
		game_window->setFramerateLimit(frame_rate_to_set); 
	}

	void GameWindowManager::update() 
	{ 
	
	}

	void GameWindowManager::render() 
	{ 
	
	}

	bool GameWindowManager::isGameWindowOpen() 
	{ 
		return game_window->isOpen(); 
	}

	RenderWindow* GameWindowManager::getGameWindow() 
	{ 
		return game_window; 
	}
}