#include "Engine.hpp"


namespace bst
{
	Engine::Engine()
	{
		config = WindowConfig{};

		settings.antialiasingLevel = config.antialiasingLevel;
		window = new sf::RenderWindow(sf::VideoMode(config.width, config.height), config.name, sf::Style::Default, settings);
		winSize = window->getSize();
		isFullscreen = false;

		loadSettings();
		loadPresets();
		setFullscreen();

		window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}

	Engine::~Engine()
	{
		delete window;

		for (auto texture : textures)
			delete texture;

		delete errorTexture;
	}

	void Engine::setFullscreen()
	{
		sf::Vector2u maxSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		sf::Vector2u size(maxSize);
		sf::Vector2i winPos(0, 0);
		uint16_t style = sf::Style::None;

		if (!isFullscreen)
		{
			size = sf::Vector2u(std::min(config.width, maxSize.x), std::min(config.height, maxSize.y));
			winPos = sf::Vector2i((maxSize.x - size.x) / 2, (maxSize.y - size.y) / 2);
			style = sf::Style::Default;
		}

		window->close();
		delete window;

		window = new sf::RenderWindow(sf::VideoMode(size.x, size.y), config.name, style, settings);
		window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		winSize = window->getSize();

		setControlsTab();
		setDebugString();
	}

// --------------------------------Load Presets--------------------------------

	void Engine::loadSettings()
	{
		timeCounter = 0.0l;
		FPSLimit = gameSettings.FPSLimit;
		timer = std::chrono::high_resolution_clock();

		isControlsTab = true;

		volume = gameSettings.volume;
	}

	void Engine::setFPSCounter()
	{
		FPSCounter.setFont(font);
		FPSCounter.setString(std::to_string(FPSLimit));
		FPSCounter.setPosition(sf::Vector2f(8.0f, 8.0f));
		FPSCounter.setCharacterSize(16u);
		FPSCounter.setFillColor(sf::Color::Green);
		FPSCounter.setOutlineThickness(1.0f);
		FPSCounter.setOutlineColor(sf::Color::Black);
	}

	float Engine::getHeightOfBottomPanel(const std::string& panel)
	{
		size_t lineCount = std::count(panel.begin(), panel.end(), '\n') + 1ull;
		float panelHeight = lineCount * CHAR_SIZE * LINE_SPACE;
		return static_cast<int>(winSize.y) - panelHeight - 8.0f;
	}

// --------------------------------Useful Functions--------------------------------

	sf::Vector2f getNormalized(const sf::Vector2f& v)
	{
		float mag = std::sqrtf(v.x * v.x + v.y * v.y);
		return sf::Vector2f(v.x / mag, v.y / mag);
	}

	inline sf::Vector2f getScaled(const sf::Vector2f& v, float scale)
	{
		return sf::Vector2f(v.x * scale, v.y * scale);
	}

	inline sf::Vector2f getDistance(const sf::Vector2f& a, const sf::Vector2f& b)
	{
		return sf::Vector2f(b.x - a.x, b.y - a.y);
	}

	inline float getMagnitude(const sf::Vector2f& v)
	{
		return std::sqrtf(v.x * v.x + v.y * v.y);
	}

	inline float getSqrMagnitude(const sf::Vector2f& v)
	{
		return v.x * v.x + v.y * v.y;
	}

	inline void Engine::sleep(int64_t milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

	void Engine::debugLog(size_t n, ...)
	{
		size_t* pointer = &n;

		std::string result = "Debug Log: " + std::to_string(*(pointer + 1ull));
		for (size_t i = 1ull; i < n; ++i)
		{
			result += ' ' + std::to_string(*(pointer + i + 1ull));
		}
		debugString.setString(result);
	}

	void Engine::setControlsTab()
	{
		std::vector<std::string> panelContent = {
			",--------Controls--------,\n"
			"|                                                                      |\n"
			"|                                                                      |\n"
			"|                                                                      |\n"
			"|                                                                      |\n"
			"|                                                                      |\n"
			"|                                                                      |\n"
			"|                                                                      |\n"
			"|                                                                      |\n"
			"|                                                                      |\n"
			"|                                                                      |\n"
			"|                                                                      |\n"
			"|                                                                      |\n"
			"|                                                                      |\n"
			"\\______________________/",

			"Esc\n"
			"F3\n"
			"F11\n"
			"R\n"
			"1/4\n"
			"2/5\n"
			"3/6\n"
			"A/Q\n"
			"S/W\n"
			"D/E\n"
			"Z/X\n"
			"C\n"
			"",

			"->    Exit\n"
			"->    F3 Menu\n"
			"->    Fullscreen\n"
			"->    Restart\n"
			"->    -/+ Rocks\n"
			"->    -/+ Papers\n"
			"->    -/+ Scissors\n"
			"->    -/+ Speed\n"
			"->    -/+ Size\n"
			"->    -/+ Volume\n"
			"->    -/+ Count\n"
			"->    Close Tab\n"
			""
		};

		std::vector<sf::Vector2f> panelPoses = {
			sf::Vector2f(8.0f, getHeightOfBottomPanel(panelContent[0]) - 20.0f),
			sf::Vector2f(48.0f, getHeightOfBottomPanel(panelContent[1]) - 20.0f),
			sf::Vector2f(100.0f, getHeightOfBottomPanel(panelContent[2]) - 20.0f)
		};

		for (size_t i = 0ull; i < panelPoses.size(); ++i)
		{
			controlsTab.push_back(sf::Text());
			controlsTab[i].setFont(font);
			controlsTab[i].setString(panelContent[i]);
			controlsTab[i].setPosition(panelPoses[i]);
			controlsTab[i].setCharacterSize(CHAR_SIZE);
			controlsTab[i].setFillColor(sf::Color::White);
			controlsTab[i].setOutlineThickness(1.0f);
			controlsTab[i].setOutlineColor(sf::Color::Black);
			controlsTab[i].setLineSpacing(LINE_SPACE);
		}
	}

	void Engine::setDebugString()
	{
		debugString.setFont(font);
		debugString.setPosition(sf::Vector2f(8.0f, winSize.y - 24.0f));
		debugString.setCharacterSize(CHAR_SIZE);
		debugString.setFillColor(sf::Color::Yellow);
	}

// --------------------------------Loop Functions--------------------------------

	void Engine::checkEvents()
	{
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;

			case sf::Event::Resized:
				isFullscreen = !isFullscreen;
				setFullscreen();
				break;

			case sf::Event::KeyPressed:

				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					window->close(); break;
				case sf::Keyboard::C:
					isControlsTab = !isControlsTab; break;
				}
				break;

			}
		}
	}

	void Engine::update()
	{

	}

	void Engine::draw()
	{
		window->draw(debugString);

		if (isControlsTab)
			for (const auto& panel : controlsTab)
				window->draw(panel);

		if (std::round(timeCounter + deltaTime) > std::round(timeCounter))
			FPSCounter.setString(std::to_string(static_cast<int>(std::roundl(1.0l / deltaTime))));

		window->draw(FPSCounter);
	}

	void Engine::run()
	{
		while (window->isOpen())
		{
			startFrameTime = timer.now();

			checkEvents();

			window->clear();
			draw();
			window->display();

			deltaTime = std::chrono::duration_cast<std::chrono::duration<long double>>(timer.now() - startFrameTime).count();
			if (1.0l / FPSLimit >= deltaTime)
			{
				deltaTime = 1.0l / FPSLimit;
				sleep(static_cast<int64_t>(deltaTime * 1000.0l));
			}

			timeCounter += deltaTime;
		}
	}
}