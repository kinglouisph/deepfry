#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
#include <unistd.h>

int main(int argc, char** argv) {
	std::string path;
	uint8_t num = 0;
	uint8_t greyscale = 0;

	if (argc > 2) {
		path = argv[1];

		num = 256 / std::atoi(argv[2]);
		printf("%i\n", num);
		if (argc > 3) {
			if (argv[3][0] == '1') {
				greyscale = 1;
		}}

	} else {
		printf("main [PATH OF FILE] [COLORS PER COLOR] [GREYSCALE (optional, 1 or 0)]\n");
		return 0;
	}

	sf::Image image;
	image.loadFromFile(path);
	int width = image.getSize().x;
	int height = image.getSize().y;
	printf("%i %i\n", width, height);

	sf::RenderWindow window(sf::VideoMode(width, height), "test");
	uint a = 0;
	uint b = 0;

	

	while (a < width) {
		b = 0;
		while (b < height) {
			
			sf::Color px = image.getPixel(a,b);

			if (greyscale) {
				uint8_t c = ((uint32_t)px.r+(uint32_t)px.g+(uint32_t)px.b)/3;
				px.r = c;
				px.g = c;
				px.b = c;
			}

			px.r -= px.r % num;
			px.g -= px.g % num;
			px.b -= px.b % num;

			//printf("%i %i %i\n", px.a, px.g, px.b);
			image.setPixel(a,b,px);
			b++;
		}
		a++;
	}

	image.saveToFile("deepfried_" + path);

	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture, 1);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
			window.close();
			}
		}

		window.draw(sprite);
		window.display();

		usleep(200000);
	}
	return 0;
}
