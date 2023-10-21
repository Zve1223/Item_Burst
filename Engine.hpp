#pragma once

#include "Resources.hpp"
#include "Item.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>

#include <thread>
#include <chrono>

#define CHAR_SIZE 16u
#define LINE_SPACE 1.25f
#define MAX_SIZE_SOUND_POLL 140ull


namespace bst
{
	struct WindowConfig
	{
		unsigned int width = 720u;
		unsigned int height = 720u;
		std::string name = "Item Burst";
		uint8_t antialiasingLevel = 16u;
	};

	struct GameSettings
	{
		size_t FPSLimit = 144ull;
		float volume = 50.0f;
	};

	class Engine
	{
	public:
		Engine();
		void run();

		~Engine();

	private:
		WindowConfig config;
		sf::ContextSettings settings;
		sf::RenderWindow* window;
		sf::Vector2u winSize;
		sf::Event event;
		bool isFullscreen;
		void setFullscreen();

		long double deltaTime;
		std::chrono::high_resolution_clock timer;
		std::chrono::steady_clock::time_point startFrameTime;

		void checkEvents();
		void update();
		void draw();

		GameSettings gameSettings;

		size_t FPSLimit;
		float volume;

		sf::Text FPSCounter;
		long double timeCounter;
		void setFPSCounter();

		void loadSettings();

		float getHeightOfBottomPanel(const std::string&);

		std::vector<sf::Text> controlsTab;
		bool isControlsTab;
		void setControlsTab();

		void debugLog(size_t, ...);
		sf::Text debugString;
		void setDebugString();

		inline void sleep(int64_t);
	};
}