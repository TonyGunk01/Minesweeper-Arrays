#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

namespace GameWindow
{
	class GameWindowManager
	{
		private:
			const int frame_rate = 60;
			const string game_window_title = "Outscal Presents - Minesweeper";

			const int game_window_width = 1920;
			const int game_window_height = 1080;

			RenderWindow* game_window;
			VideoMode video_mode;
			const sf::Color window_color = Color(200, 200, 0, 255);

			void initialize();
			RenderWindow* createGameWindow();
			void setFrameRate(int);
			void configureVideoMode();
			void onDestroy();

		public:
			GameWindowManager();
			~GameWindowManager();

			bool isGameWindowOpen();
			RenderWindow* getGameWindow();

			void update();
			void render();
	};
}