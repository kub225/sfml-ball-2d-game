#include <iostream>
#include <cmath>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
using namespace std;

class Ball {
private:
	sf::CircleShape shape;
	sf::Texture shapeTexture;
public:
	Ball(float x, float y) {
		if (!shapeTexture.loadFromFile("ball.png")) {
			cout << "Failed to load the ball image.\n";
		}
		shape.setRadius(40.f);
		shape.setPosition({ x, y });
		shape.setTexture(&shapeTexture);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(shape);
	}
	sf::CircleShape& getShape() {
		return shape;
	}
	sf::FloatRect getBounds() const {
		return shape.getGlobalBounds();
	}
	void movement(float speed, sf::Vector2f& offset) {
		float gravity = 0.2f;
		offset = { 0.f, gravity };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			offset.x -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			offset.x += speed * 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
			offset.y -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
			offset.y += speed;
		}
		shape.move(offset);
	}

	void mvback(sf::Vector2f offset) {
		shape.move(-offset);
	}


};


class Wall {
private:
	sf::RectangleShape rectangle;
public:
	Wall(float x, float y, sf::Texture& wallTexture) {

		rectangle.setSize(sf::Vector2f(200.f, 100.f));
		rectangle.setPosition({ x, y });
		rectangle.setTexture(&wallTexture);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(rectangle);
	}
	sf::RectangleShape& getShape() {
		return rectangle;
	}
	sf::FloatRect getBounds() const {
		return rectangle.getGlobalBounds();
	}
	void setRotation(float angle) {
		rectangle.setRotation(sf::degrees(angle));
	}
};




class Spike {
private:
	sf::RectangleShape rectangle;
public:
	Spike(float a, float b, float x, float y, sf::Texture& spikeTexture) {
		rectangle.setSize(sf::Vector2f(a, b));
		rectangle.setPosition({ x,y });
		rectangle.setTexture(&spikeTexture);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(rectangle);
	}

	void rotation(float angle) {
		rectangle.setRotation(sf::degrees(angle));
	}

	sf::RectangleShape& getShape() {
		return rectangle;
	}
	sf::FloatRect getBounds()const {
		return rectangle.getGlobalBounds();
	}
};




class Border {
private:
	sf::RectangleShape rectangle;
public:
	Border(float x, float y, sf::Texture& borderTexture) {
		rectangle.setSize(sf::Vector2f(2000.f, 90.f));
		rectangle.setPosition({ x,y });
		rectangle.setTexture(&borderTexture);

	}
	void draw(sf::RenderWindow& window) {
		window.draw(rectangle);
	}

	void setRotation(float angle) {
		rectangle.setRotation(sf::degrees(angle));
	}

	sf::RectangleShape& getShape() {
		return rectangle;
	}
	sf::FloatRect getBounds()const {
		return rectangle.getGlobalBounds();
	}

};




class Coin {
private:
	sf::CircleShape coin;
public:
	Coin(float x, float y, sf::Texture& cointexture) {
		coin.setRadius(30.f);
		coin.setPosition({ x,y });
		coin.setTexture(&cointexture);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(coin);
	}
	sf::CircleShape& getShape() {
		return coin;
	}
	sf::FloatRect getBounds()const {
		return coin.getGlobalBounds();
	}
};

class Exitt {
private:
	sf::RectangleShape ex;
public:
	Exitt(float x, float y) {
		ex.setSize(sf::Vector2f(90.f, 200.f));
		ex.setPosition({ x,y });
		ex.setFillColor(sf::Color::Black);
	}

	void draw(sf::RenderWindow& window) {
		window.draw(ex);
	}
	sf::RectangleShape& getShape() {
		return ex;
	}

	sf::FloatRect getBounds()const {
		return ex.getGlobalBounds();
	}
};


class Barrier {
private:
	sf::RectangleShape bar;

public:
	Barrier(float x, float y, sf::Texture& black) {
		bar.setSize(sf::Vector2f(90.f, 200.f));
		bar.setPosition({ x,y });
		bar.setTexture(&black);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(bar);
	}
	sf::RectangleShape& getShape() {
		return bar;
	}
	sf::FloatRect getBounds()const {
		return bar.getGlobalBounds();
	}
};

class Playex {
private:
	sf::Text menutext;
	sf::Text exittext;
	sf::Text title;
public:
	Playex(sf::Font& font):menutext(font),exittext(font),title(font){
		title.setString("BALL");
		title.setCharacterSize( 80 );
		title.setPosition({ 500.f,200.f });
		title.setFillColor(sf::Color::Black);

		menutext.setString("Play");
		menutext.setCharacterSize(40);
		menutext.setPosition({ 600.f,400.f });
;
		exittext.setString("Exit");
		exittext.setCharacterSize(40);
		exittext.setPosition({ 600.f,500.f });

	}
	void draw(sf::RenderWindow& window, bool drawtitle = true) {
		if(drawtitle){
		window.draw(title);
	}
		window.draw(menutext);
		window.draw(exittext);
	}

	void upd(sf::Vector2f mouse) {
		if (menutext.getGlobalBounds().contains(mouse)) {
			menutext.setFillColor(sf::Color::Cyan);
		}
		else {
			menutext.setFillColor(sf::Color::Red);
		}
		if (exittext.getGlobalBounds().contains(mouse)) {
			exittext.setFillColor(sf::Color::Cyan);
		}
		else {
			exittext.setFillColor(sf::Color::Red);
		}
	}
	int click(sf::Vector2f mouse) {
		if (menutext.getGlobalBounds().contains(mouse)) {
			return 1;
		}
		if (exittext.getGlobalBounds().contains(mouse)) {
			return 2;
		}
		return 0;
	}
};





void level1(Ball& ball, Barrier& barrier, Exitt& exit, sf::Texture& wallText, sf::Texture& spikeText, sf::Texture& borderText, sf::Texture& coinText, sf::Texture& barText, vector <Wall>& walls, vector <Spike>& spikes, vector <Coin>& coins, vector <Border>& borders) {
	walls.clear();
	spikes.clear();
	coins.clear();
	borders.clear();

	//Walls
	walls.push_back(Wall(35.f, 200.f, wallText));
	walls.push_back(Wall(225.f, 295.f, wallText));
	walls.push_back(Wall(410.f, 200.f, wallText));
	walls.push_back(Wall(595.f, 200.f, wallText));
	walls.push_back(Wall(780.f, 200.f, wallText));
	walls.push_back(Wall(1450.f, 250.f, wallText));
	walls.push_back(Wall(1650.f, 250.f, wallText));
	walls.push_back(Wall(1450.f, 600.f, wallText));
	walls.push_back(Wall(1635.f, 600.f, wallText));
	walls.push_back(Wall(1270.f, 505.f, wallText));
	walls.push_back(Wall(1080.f, 505.f, wallText));
	walls.push_back(Wall(895.f, 600.f, wallText));
	walls.push_back(Wall(710.f, 600.f, wallText));
	walls.push_back(Wall(525.f, 600.f, wallText));
	walls.push_back(Wall(340.f, 600.f, wallText));


	//Coins
	coins.push_back(Coin(320.f, 80.f, coinText));
	coins.push_back(Coin(1600.f, 80.f, coinText));
	coins.push_back(Coin(660.f, 80.f, coinText));
	coins.push_back(Coin(1600.f, 360.f, coinText));
	coins.push_back(Coin(1270.f, 660.f, coinText));

	//Borders
	borders.push_back(Border(-40.f, -40.f, borderText));
	borders.push_back(Border(-40.f, 1030.f, borderText));
	{
		Border b(65.f, 0.f, borderText);
		b.setRotation(90.f);
		borders.push_back(b);
	}

	{
		Border b1(1940.f, -1150.f, borderText);
		b1.setRotation(90.f);
		borders.push_back(b1);
	}

	//Spikes
	{
		Spike s(120.f, 40.f, 330.f, 320.f, spikeText);
		s.rotation(270.f);
		spikes.push_back(s);
	}

	{
		Spike s3(120.f, 40.f, 1855.f, 120.f, spikeText);
		s3.rotation(180.f);
		spikes.push_back(s3);
	}

	{
		Spike s4(120.f, 40.f, 1855.f, 220.f, spikeText);
		s4.rotation(180.f);
		spikes.push_back(s4);
	}

	{
		Spike s5(320.f, 50.f, 1490.f, 300.f, spikeText);
		s5.rotation(180.f);
		spikes.push_back(s5);
	}

	{
		Spike s6(120.f, 40.f, 1530.f, 640.f, spikeText);
		s6.rotation(270.f);
		spikes.push_back(s6);
	}

	{
		Spike s7(120.f, 40.f, 1630.f, 640.f, spikeText);
		s7.rotation(270.f);
		spikes.push_back(s7);
	}

	{
		Spike s8(120.f, 40.f, 1730.f, 640.f, spikeText);
		s8.rotation(270.f);
		spikes.push_back(s8);
	}

	{
		Spike s9(320.f, 50.f, 1135.f, 580.f, spikeText);
		s9.rotation(180.f);
		spikes.push_back(s9);
	}

	{
		Spike s10(120.f, 40.f, 660.f, 280.f, spikeText);
		s10.rotation(90.f);
		spikes.push_back(s10);
	}

	{
		Spike s11(120.f, 40.f, 560.f, 280.f, spikeText);
		s11.rotation(90.f);
		spikes.push_back(s11);
	}

	{
		Spike s12(120.f, 40.f, 760.f, 280.f, spikeText);
		s12.rotation(90.f);
		spikes.push_back(s12);
	}

	{
		Spike s13(160.f, 40.f, 380.f, 690.f, spikeText);
		s13.rotation(180.f);
		spikes.push_back(s13);
	}

	{
		Spike s14(160.f, 40.f, 980.f, 690.f, spikeText);
		s14.rotation(90.f);
		spikes.push_back(s14);
	}

	{
		Spike s15(160.f, 40.f, 480.f, 1040.f, spikeText);
		s15.rotation(270.f);
		spikes.push_back(s15);
	}

	{
		Spike s16(160.f, 40.f, 680.f, 1040.f, spikeText);
		s16.rotation(270.f);
		spikes.push_back(s16);
	}

	{
		Spike s0(160.f, 40.f, 1580.f, 1040.f, spikeText);
		s0.rotation(270.f);
		spikes.push_back(s0);
	}

	}


void level2(Ball& ball, Barrier& barrier, Exitt& exit, sf::Texture& wallText, sf::Texture& spikeText, sf::Texture& borderText, sf::Texture& coinText, sf::Texture& barText, vector <Wall>& walls, vector <Spike>& spikes, vector <Coin>& coins, vector <Border>& borders) {
	walls.clear();
	spikes.clear();
	coins.clear();
	borders.clear();

	//Borders
	borders.push_back(Border(-40.f, -40.f, borderText));
	borders.push_back(Border(-40.f, 1030.f, borderText));
	{
		Border b(65.f, 240.f, borderText);
		b.setRotation(90.f);
		borders.push_back(b);
	}

	{
		Border b1(1940.f, -900.f, borderText);
		b1.setRotation(90.f);
		borders.push_back(b1);
	}

	//Walls
	walls.push_back(Wall(835.f, 200.f, wallText));
	walls.push_back(Wall(1035.f, 200.f, wallText));
	walls.push_back(Wall(635.f, 200.f, wallText));
	walls.push_back(Wall(65.f, 450.f, wallText));
	walls.push_back(Wall(265.f, 450.f, wallText));
	walls.push_back(Wall(465.f, 450.f, wallText));
	walls.push_back(Wall(665.f, 450.f, wallText));
	walls.push_back(Wall(865.f, 450.f, wallText));
	walls.push_back(Wall(1065.f, 450.f, wallText));
	walls.push_back(Wall(1650.f, 730.f, wallText));
	walls.push_back(Wall(1450.f, 730.f, wallText));
	walls.push_back(Wall(1250.f, 730.f, wallText));
	walls.push_back(Wall(1050.f, 730.f, wallText));
	walls.push_back(Wall(850.f, 730.f, wallText));
	walls.push_back(Wall(650.f, 730.f, wallText));
	walls.push_back(Wall(450.f, 730.f, wallText));

	//Spikes
	{
		Spike s(90.f, 30.f, 1330.f, 1040.f, spikeText);
		s.rotation(270.f);
		spikes.push_back(s);
	}

	{
		Spike s(90.f, 30.f, 1170.f, 820.f, spikeText);
		s.rotation(90.f);
		spikes.push_back(s);
	}

	{
		Spike s(90.f, 30.f, 930.f, 1040.f, spikeText);
		s.rotation(270.f);
		spikes.push_back(s);
	}

	{
		Spike s(90.f, 30.f, 770.f, 820.f, spikeText);
		s.rotation(90.f);
		spikes.push_back(s);
	}

	{
		Spike s(230.f, 40.f, 460.f, 810.f, spikeText);
		s.rotation(180.f);
		spikes.push_back(s);
	}
	{
		Spike s(90.f, 30.f, 930.f, 740.f, spikeText);
		s.rotation(270.f);
		spikes.push_back(s);
	}
	{
		Spike s(90.f, 30.f, 880.f, 740.f, spikeText);
		s.rotation(270.f);
		spikes.push_back(s);
	}
	{
		Spike s(90.f, 30.f, 980.f, 740.f, spikeText);
		s.rotation(270.f);
		spikes.push_back(s);
	}
	{
		Spike s(90.f, 30.f, 1030.f, 740.f, spikeText);
		s.rotation(270.f);
		spikes.push_back(s);
	}
	{
		Spike s(90.f, 30.f, 630.f, 540.f, spikeText);
		s.rotation(90.f);
		spikes.push_back(s);
	}
	{
		Spike s(90.f, 30.f, 580.f, 540.f, spikeText);
		s.rotation(90.f);
		spikes.push_back(s);
	}
	{
		Spike s(90.f, 30.f, 680.f, 540.f, spikeText);
		s.rotation(90.f);
		spikes.push_back(s);
	}
	{
		Spike s(90.f, 30.f, 530.f, 540.f, spikeText);
		s.rotation(90.f);
		spikes.push_back(s);
	}
	{
		Spike s(230.f, 40.f, 1870.f, 510.f, spikeText);
		s.rotation(180.f);
		spikes.push_back(s);
	}
	{
		Spike s(230.f, 40.f, 1250.f, 470.f, spikeText);
		s.rotation(0.f);
		spikes.push_back(s);
	}
	{
		Spike s(190.f, 30.f, 780.f, 40.f, spikeText);
		s.rotation(90.f);
		spikes.push_back(s);
	}


	//Coins
	coins.push_back(Coin(120.f, 750.f, coinText));
	coins.push_back(Coin(1000.f, 860.f, coinText));
	coins.push_back(Coin(840.f, 80.f, coinText));
	coins.push_back(Coin(1530.f, 450.f, coinText));
	coins.push_back(Coin(750.f, 600.f, coinText));
	



}


void level3(Ball& ball, Barrier& barrier, Exitt& exit, sf::Texture& wallText, sf::Texture& spikeText, sf::Texture& borderText, sf::Texture& coinText, sf::Texture& barText, vector <Wall>& walls, vector <Spike>& spikes, vector <Coin>& coins, vector <Border>& borders) {
	walls.clear();
	spikes.clear();
	coins.clear();
	borders.clear();

	//Borders
	borders.push_back(Border(-40.f, -40.f, borderText));
	borders.push_back(Border(-40.f, 1030.f, borderText));
	{
		Border b(65.f, 0.f, borderText);
		b.setRotation(90.f);
		borders.push_back(b);
	}

	{
		Border b1(1940.f, -1150.f, borderText);
		b1.setRotation(90.f);
		borders.push_back(b1);
	}

	//Walls
	walls.push_back(Wall(20.f, 250.f, wallText));
	{
		Wall w(720.f, 50.f, wallText);
		w.setRotation(90.f);
		walls.push_back(w);
	}
	{
		Wall w(720.f, 250.f, wallText);
		w.setRotation(90.f);
		walls.push_back(w);
	}
	{
		Wall w(720.f, 450.f, wallText);
		w.setRotation(90.f);
		walls.push_back(w);
	}
	{
		Wall w(720.f, 650.f, wallText);
		w.setRotation(90.f);
		walls.push_back(w);
	}
	walls.push_back(Wall(1020.f, 300.f, wallText));
	walls.push_back(Wall(1220.f, 300.f, wallText));
	walls.push_back(Wall(1020.f, 600.f, wallText));
	walls.push_back(Wall(1220.f, 600.f, wallText));
	walls.push_back(Wall(1650.f, 300.f, wallText));
	{
		Wall w(1620.f, 840.f, wallText);
		w.setRotation(90.f);
		walls.push_back(w);
	}
	{
		Wall w(1020.f, 290.f, wallText);
		w.setRotation(90.f);
		walls.push_back(w);
	}
	{
		Wall w(1020.f, 490.f, wallText);
		w.setRotation(90.f);
		walls.push_back(w);
	}
	{
		Wall w(1020.f, 690.f, wallText);
		w.setRotation(90.f);
		walls.push_back(w);
	}
	//Spikes
	{
		Spike s(190.f, 30.f, 980.f, 840.f, spikeText);
		s.rotation(90.f);
		spikes.push_back(s);
	}
	{
		Spike s(230.f, 30.f, 650.f, 340.f, spikeText);
		s.rotation(180.f);
		spikes.push_back(s);
	}
	{
		Spike s(230.f, 30.f, 650.f, 540.f, spikeText);
		s.rotation(180.f);
		spikes.push_back(s);
	}
	{
		Spike s(230.f, 30.f, 650.f, 740.f, spikeText);
		s.rotation(180.f);
		spikes.push_back(s);
	}
	{
		Spike s(50.f, 40.f, 950.f, 340.f, spikeText);
		s.rotation(180.f);
		spikes.push_back(s);
	}
	{
		Spike s(50.f, 40.f, 950.f, 540.f, spikeText);
		s.rotation(180.f);
		spikes.push_back(s);
	}
	{
		Spike s(50.f, 40.f, 950.f, 740.f, spikeText);
		s.rotation(180.f);
		spikes.push_back(s);
	}
	{
		Spike s(230.f, 30.f, 1900.f, 200.f, spikeText);
		s.rotation(180.f);
		spikes.push_back(s);
	}
	{
		Spike s(230.f, 30.f, 1900.f, 650.f, spikeText);
		s.rotation(180.f);
		spikes.push_back(s);
	}

	//Coins
	coins.push_back(Coin(120.f, 750.f, coinText));
	coins.push_back(Coin(1200.f, 860.f, coinText));
	coins.push_back(Coin(840.f, 80.f, coinText));
	coins.push_back(Coin(1530.f, 450.f, coinText));
	coins.push_back(Coin(520.f, 600.f, coinText));

}

int main() {
	enum class state {Menu, Game, Exit, Win};
	state st = state::Menu;
	//Textures
	sf::Texture wallText, spikeText, borderText, coinText, barText;
	int lvlnum = 1;
	//Font and text
	sf::Font font;
	sf::Text coinstext(font, "");
	coinstext.setCharacterSize(30);
	coinstext.setFillColor(sf::Color::White);
	coinstext.setPosition({ 50.f, 50.f });
	font.openFromFile("ARIAL.TTF");
	
	//Timer
	sf::Text timerTextDisplay(font, "");
	timerTextDisplay.setCharacterSize(30);
	timerTextDisplay.setFillColor(sf::Color::White);
	timerTextDisplay.setPosition({ 250.f, 50.f });

	sf::Clock gameClock;

	//Textures
	wallText.loadFromFile("metalwall.png");
	spikeText.loadFromFile("spike.png");
	borderText.loadFromFile("border.png");
	coinText.loadFromFile("coin.png");
	barText.loadFromFile("black.png");

	//Win title
	sf::Text wintitle(font,"You win!");
	wintitle.setCharacterSize(90);
	wintitle.setFillColor(sf::Color::Cyan);
	wintitle.setPosition({ 750.f,200.f });

	//Arrays with objects
	vector <Wall> walls;
	vector <Spike> spikes;
	vector <Coin> coins;
	vector <Border> borders;

	//Exit
	Exitt exit(1850.f, 830.f);
	//Ball
	Ball ball(80.f, 70.f);

	//Barrier
	Barrier barrier(1850.f, 830.f, barText);

	//Play and exit
	Playex pe(font);

	level1(ball, barrier, exit, wallText, spikeText, borderText, coinText, barText, walls, spikes, coins, borders);
	

	sf::RenderWindow window(sf::VideoMode({ 1920u, 1080u }), "Ball");
	sf::Texture backgroundImage;
	if (!backgroundImage.loadFromFile("board.png")) {
		cout << "Failed to load background image.\n";
		return -1;
	}
	sf::Sprite background(backgroundImage);


	while (window.isOpen()) {
		sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		while (const optional<sf::Event>event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			if (st == state::Menu && event->is<sf::Event::MouseButtonPressed>()) {
				int choice = pe.click(mouse);
				if (choice == 1) {
					st = state::Game;
					lvlnum = 1;
					level1(ball, barrier, exit, wallText, spikeText, borderText, coinText, barText, walls, spikes, coins, borders);
					ball.getShape().setPosition({ 80.f, 70.f });
					gameClock.restart();
				}
				else if (choice == 2) {
					window.close();
				}
			}

			if (st == state::Win && event->is<sf::Event::MouseButtonPressed>()) {
				int choice = pe.click(mouse);
				if (choice == 1) {
					st = state::Game;
					lvlnum = 1;
					level1(ball, barrier, exit, wallText, spikeText, borderText, coinText, barText, walls, spikes, coins, borders);
					ball.getShape().setPosition({80.f, 70.f});
					gameClock.restart();
				}
				else if (choice == 2) {
					window.close();
				}

			}
		}

		if (st == state::Menu) {
			window.clear();
			window.draw(background);
			pe.upd(mouse);
			pe.draw(window,true);
		}

		if (st == state::Win) {
			window.clear();
			window.draw(background);
			window.draw(wintitle);
			pe.upd(mouse);
			pe.draw(window,false);
		}
		else if (st == state::Game) {
			sf::Vector2f currentOffset;
			ball.movement(0.4f, currentOffset);

			coinstext.setString("Coins:" + to_string(5 - coins.size()) + "/ 5");
			int seconds = gameClock.getElapsedTime().asSeconds();
			timerTextDisplay.setString("Time:" + to_string(seconds) + "s");

			window.clear();
			window.draw(background);
			for (auto& s : spikes) {
				s.draw(window);
			}
			for (auto& w : walls) {
				if (ball.getBounds().findIntersection(w.getBounds())) {
					ball.mvback(currentOffset);
					break;
				}
			}
			for (auto& b : borders) {
				if (ball.getBounds().findIntersection(b.getBounds())) {
					ball.mvback(currentOffset);
					break;
				}
			}
			for (auto& s : spikes) {
				if (ball.getBounds().findIntersection(s.getBounds())) {
					if (lvlnum == 1) {
						ball.getShape().setPosition({ 80.f, 70.f });
					}
					else if (lvlnum == 2) {
						ball.getShape().setPosition({ 1750.f, 930.f });
					}
					else if (lvlnum == 3) {
						ball.getShape().setPosition({ 80.f,70.f });
					}
					if (lvlnum == 1) {
						level1(ball, barrier, exit, wallText, spikeText, borderText, coinText, barText, walls, spikes, coins, borders);
						exit.getShape().setPosition({ 1850.f, 830.f });
						barrier.getShape().setPosition({ 1850.f, 830.f });
						break;

					}
					else if (lvlnum == 2) {
						level2(ball, barrier, exit, wallText, spikeText, borderText, coinText, barText, walls, spikes, coins, borders);
						exit.getShape().setPosition({ -25.f,50.f });
						barrier.getShape().setPosition({ -25.f,50.f });
						break;
					}
					else if (lvlnum == 3) {
						level3(ball, barrier, exit, wallText, spikeText, borderText, coinText, barText, walls, spikes, coins, borders);
						exit.getShape().setPosition({ 1850.f, 830.f });
						barrier.getShape().setPosition({ 1850.f, 830.f });
						break;
					}

				}
			}

			for (int i = 0; i < coins.size();) {
				if (ball.getBounds().findIntersection(coins[i].getBounds())) {
					coins.erase(coins.begin() + i);
				}
				else {
					i++;
				}
			}

			for (auto& w : walls) {
				w.draw(window);
			}

			for (auto& b : borders) {
				b.draw(window);
			}
			if (!coins.empty()) {
				barrier.draw(window);
				if (ball.getBounds().findIntersection(barrier.getBounds())) {
					ball.mvback(currentOffset);
				}

			}
			else {
				exit.draw(window);
			}

			if (ball.getBounds().findIntersection(exit.getBounds())) {
				if (lvlnum == 1) {
					lvlnum = 2;
					level2(ball, barrier, exit, wallText, spikeText, borderText, coinText, barText, walls, spikes, coins, borders);
					ball.getShape().setPosition({ 1750.f, 930.f });
					exit.getShape().setPosition({ -25.f,50.f });
					barrier.getShape().setPosition({ -25.f,50.f });

				}
				else if (lvlnum == 2) {
					lvlnum = 3;
					level3(ball, barrier, exit, wallText, spikeText, borderText, coinText, barText, walls, spikes, coins, borders);
					exit.getShape().setPosition({ 1850.f, 830.f });
					barrier.getShape().setPosition({ 1850.f, 830.f });
				}
				else if (lvlnum == 3) {
					st = state::Win;
				}
						
			}

			for (auto& c : coins) {
				c.draw(window);
			}
			ball.draw(window);
			window.draw(timerTextDisplay);
			window.draw(coinstext);

		}
		window.display();
	}
	return 0;
}