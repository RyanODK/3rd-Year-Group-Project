//#include "Player.h"
//
//Player::Player() {
//	m_Health = INITIAL_HEALTH;
//	m_Speed = INITIAL_SPEED;
//	m_JumpDuration = 0.3;
//	m_SlideDuration = 0.5;
//
//	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
//		"Graphics/Main Player/playerSpritesheet.png", false));
//
//	ani_counter = 1;
//}
//
//void Player::spawn(sf::Vector2f resolution, float gravity) {
//	//// depending on resolution set position and scale of player
//	//if (m_Resolution.x == 2560 && m_Resolution.y == 1440) {
//	//	m_Sprite.setScale(6, 6);
//	//}
//	//else if (m_Resolution.x == 1920 && m_Resolution.y == 1080) {
//	//	m_Sprite.setScale(5, 5);
//	//}
//	//else if (m_Resolution.x == 1680 && m_Resolution.y == 1050) {
//	//	m_Sprite.setScale(4.5, 4.5);
//	//}
//
//	// 162, 228
//	m_Sprite.setScale((resolution.x / 100) / 4.1, (resolution.y / 100) / 2.2);
//
//	if (!m_Jump && !m_isFalling) {
//		m_Position.x = (m_Resolution.x / 100) * 10;
//		m_Position.y = (m_Resolution.y / 100) * 75;
//		m_Sprite.setPosition(m_Position);
//	}
//
//	// store gravity for future use
//	m_gravity = gravity;
//
//	// store resolution for future use
//	m_Resolution.x = resolution.x;
//	m_Resolution.y = resolution.y;
//}
//
//bool Player::Jump() {
//	m_JustJumped = false;
//
//	// if user presses space 
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//		// m_Jump and m_isFalling is false
//		if (!m_Jump && !m_isFalling) {
//			m_Jump = true; // set m_Jump to true
//			m_TimeThisJump = 0; // set timer for jump to 0
//			m_JustJumped = true; // set just jumped to false to stop constantly jumping
//		}
//	}
//	// else player is not pressing space bar
//	else 
//	{
//		m_Jump = false; // set m_Jump to false
//		m_isFalling = true; // set m_IsFalling to true
//	}
//	
//	// return m_JustJumped
//	return m_JustJumped;
//}
//
//bool Player::Slide() {
//	m_JustSlid = false;
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
//		if (!m_IsSliding) {
//			m_IsSliding = true;
//			m_TimeThisSlide = 0;
//			m_JustSlid = true;
//		}
//	}
//	else {
//		m_IsSliding = false;
//	}
//
//	return m_JustSlid;
//}
//
//bool Player::Laser() {
//	m_JustLasered = false;
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
//		if (!m_IsLasering) {
//			m_IsLasering = true;
//			m_TimeThisLaser = 0;
//			m_JustLasered = true;
//		}
//	}
//	else {
//		m_IsLasering = false;
//	}
//
//	return m_JustLasered;
//}
//
//void Player::update(float elapsedTime, int groundHeight) {
//	setCollisionZones();
//	// plays player run animation
//	m_IsRunning = true;
//	m_TimePerFrame = 0.09;
//	setSpriteFromSheet(sf::IntRect(0, 228, 174, 35), sf::Vector2i(29, 35));
//	moveTextureRect(elapsedTime);
//
//	//if m_Jump is true
//	if (m_Jump) {
//		m_IsRunning = false;
//		m_TimeThisJump += elapsedTime; // time jump by adding elapsedTime
//
//		// if timer for jump is less than players set jump duration
//		if (m_TimeThisJump < m_JumpDuration) { 
//			// move player up using gravity and elapsedTime
//			m_Position.y -= m_gravity * 2 * elapsedTime;
//			m_Sprite.setPosition(m_Position);
//			// set jump animation frame
//			setSpriteFromSheet(sf::IntRect(0, 152, 23, 35), sf::Vector2i(29, 38));
//		}
//		// else timer for jump has hit allowed jump duration
//		else {
//			m_Jump = false; // stop jump
//			m_isFalling = true; // start falling
//		}
//	}
//
//	// if player is falling
//	if (m_isFalling) {
//		m_IsRunning = false;
//		// increment position y of player with gravity to make sprite fall down
//		m_Position.y += m_gravity * elapsedTime;
//		m_Sprite.setPosition(m_Position);
//		// if players position y has hit current ground height
//		// stop falling
//		/*if (m_Position.y >= groundHeight) {
//			m_isFalling = false;
//		}*/
//		// set falling animation frame
//		setSpriteFromSheet(sf::IntRect(78, 152, 29, 35), sf::Vector2i(29, 38));
//	}
//
//	if (m_IsSliding) {
//		m_TimeThisSlide += elapsedTime;
//
//		if (m_TimeThisSlide < m_SlideDuration) {
//			setSpriteFromSheet(sf::IntRect(0, 327, 49, 54), sf::Vector2i(29, 38));
//		}
//		else {
//			m_IsSliding = false;
//		}
//	}
//
//	if (m_IsLasering) {
//		m_TimePerFrame = 0.09;
//		m_TimeThisLaser += elapsedTime;
//
//		if (m_TimeThisLaser < 0.12) {
//			setSpriteFromSheet(sf::IntRect(95, 190, 83, 38), sf::Vector2i(33, 38));
//			moveTextureRect(elapsedTime);
//		}
//		else {
//			m_IsLasering = false;
//		}
//	}
//}
//
//void Player::setSpriteFromSheet(sf::IntRect textureBox, sf::Vector2i spriteSize)
//{
//	// get sprite sheets left and top values
//	sheetCoordinate = sf::Vector2i(textureBox.left, textureBox.top);
//	// set sprite size
//	m_SpriteSize = spriteSize;
//
//	// if sprite sheet width is greater than sprite size x
//	if (textureBox.width > m_SpriteSize.x)
//	{
//		// set animation iterator limit to width of sprite sheet / sprite size x
//		animation_it_limit = textureBox.width / m_SpriteSize.x;
//	}
//	// else if sprite sheet height is greater than sprite size y
//	else if (textureBox.height > m_SpriteSize.y)
//	{
//		// set animation iterator limit to height of sprite sheet / sprite size y
//		animation_it_limit = textureBox.height / m_SpriteSize.y;
//	}
//	// else throw error 
//	//else
//		//throw logic_error("Animation bounding box must contain multiply sprites, setSprite(sf::IntRect )\n");
//
//	// set sprites texture rect size to sheet coordinate (left and top) by sprite size (x and y)
//	m_Sprite.setTextureRect(sf::IntRect{ sheetCoordinate, m_SpriteSize });
//
//}
//
//void Player::moveTextureRect(float elapsedTime) {
//	// if animation counter == animation iterator limit
//	if (ani_counter == animation_it_limit) {
//		// set animation counter to 0
//		ani_counter = 0;
//	}
//
//	m_Sprite.setTextureRect(sf::IntRect(sheetCoordinate + sf::Vector2i(
//		m_SpriteSize.x * ani_counter, 0), m_SpriteSize));
//
//	// increment animation counter to point to next frame
//	double timePerFrame;
//	timePerFrame = m_TimePerFrame;
//
//	animationTimer += elapsedTime;
//	if (animationTimer >= timePerFrame) {
//		ani_counter++;
//		animationTimer = 0;
//	}
//}
//
//void Player::setCollisionZones() {
//	sf::FloatRect r = getGlobal();
//
//	if (m_IsRunning) {
//		if (ani_counter == 0) {
//			// Feet
//			m_Feet.left = r.left + 4; // 4
//			m_Feet.top = r.top + r.height - 1; // 34
//			m_Feet.width = r.width - 10; // 19
//			m_Feet.height = 1; // 1
//
//			// Head
//			m_Head.left = r.left + 15; // 15
//			m_Head.top = r.top + 1; // 1
//			m_Head.width = r.width - 25; // 4
//			m_Head.height = 1;
//
//			// Right
//			m_Right.left = r.left + r.width - 6; // 23
//			m_Right.top = r.top + r.height * .37; // 13
//			m_Right.width = 1; // 1
//			m_Right.height = 27; // 27
//
//			// Left
//			m_Left.left = r.left + 4; // 4
//			m_Left.top = r.top + r.height * .72; // 25
//			m_Left.width = 1; // 1
//			m_Left.height = 2; // 2
//		}
//		if (ani_counter == 1) {
//			// Feet
//			m_Feet.left = r.left + 4; // 4
//			m_Feet.top = r.top + r.height - 1; // 34
//			m_Feet.width = r.width - 10; // 19
//			m_Feet.height = 1; // 1
//
//			// Head
//			m_Head.left = r.left + 15; // 15
//			m_Head.top = r.top + 1; // 1
//			m_Head.width = r.width - 25; // 4
//			m_Head.height = 1;
//
//			// Right
//			m_Right.left = r.left + r.width - 7; // 22
//			m_Right.top = r.top + r.height * .2; // 7
//			m_Right.width = 1; // 1
//			m_Right.height = 12; // 12
//
//			// Left
//			m_Left.left = r.left + 8; // 8
//			m_Left.top = r.top + r.height * .8; // 28
//			m_Left.width = 1; // 1
//			m_Left.height = 3; // 3
//		}
//		if (ani_counter == 2) {
//			// Feet
//			m_Feet.left = r.left + 4; // 4
//			m_Feet.top = r.top + r.height - 1; // 34
//			m_Feet.width = r.width - 10; // 19
//			m_Feet.height = 1; // 1
//
//			// Head
//			m_Head.left = r.left + 15; // 15
//			m_Head.top = r.top + 2; // 2
//			m_Head.width = r.width - 25; // 4
//			m_Head.height = 1;
//
//			// Right
//			m_Right.left = r.left + r.width - 3; // 26
//			m_Right.top = r.top + r.height * .58; // 20
//			m_Right.width = 1; // 1
//			m_Right.height = 2; // 2
//
//			// Left
//			m_Left.left = r.left + 6; // 6
//			m_Left.top = r.top + r.height * .46; // 16
//			m_Left.width = 1; // 1
//			m_Left.height = 18; // 18
//		}
//		if (ani_counter == 3) {
//			// Feet
//			m_Feet.left = r.left + 4; // 4
//			m_Feet.top = r.top + r.height - 1; // 34
//			m_Feet.width = r.width - 10; // 19
//			m_Feet.height = 1; // 1
//
//			// Head
//			m_Head.left = r.left + 15; // 15
//			m_Head.top = r.top + 1; // 1
//			m_Head.width = r.width - 25; // 4
//			m_Head.height = 1;
//
//			// Right
//			m_Right.left = r.left + r.width - 1; // 28
//			m_Right.top = r.top + r.height * .43; // 15
//			m_Right.width = 1; // 1
//			m_Right.height = 3; // 3
//
//			// Left
//			m_Left.left = r.left + 1; // 1
//			m_Left.top = r.top + r.height * .46; // 16
//			m_Left.width = 1; // 1
//			m_Left.height = 3; // 3
//		}
//		if (ani_counter == 4) {
//			// Feet
//			m_Feet.left = r.left + 4; // 4
//			m_Feet.top = r.top + r.height - 1; // 34
//			m_Feet.width = r.width - 10; // 19
//			m_Feet.height = 1; // 1
//
//			// Head
//			m_Head.left = r.left + 15; // 15
//			m_Head.top = r.top + 1; // 1
//			m_Head.width = r.width - 25; // 4
//			m_Head.height = 1;
//
//			// Right
//			m_Right.left = r.left + r.width - 7; // 22
//			m_Right.top = r.top + r.height * .2; // 7
//			m_Right.width = 1; // 1
//			m_Right.height = 17; // 17
//
//			// Left
//			m_Left.left = r.left + 7; // 7
//			m_Left.top = r.top + r.height * .57; // 20
//			m_Left.width = 1; // 1
//			m_Left.height = 3; // 3
//		}
//		if (ani_counter == 5) {
//			// Feet
//			m_Feet.left = r.left + 4; // 4
//			m_Feet.top = r.top + r.height - 1; // 34
//			m_Feet.width = r.width - 10; // 19
//			m_Feet.height = 1; // 1
//
//			// Head
//			m_Head.left = r.left + 15; // 15
//			m_Head.top = r.top + 2; // 2
//			m_Head.width = r.width - 25; // 4
//			m_Head.height = 1;
//
//			// Right
//			m_Right.left = r.left + r.width - 5; // 24
//			m_Right.top = r.top + r.height * .23; // 8
//			m_Right.width = 1; // 1
//			m_Right.height = 10; // 10
//
//			// Left
//			m_Left.left = r.left + 5; // 5
//			m_Left.top = r.top + r.height * .915; // 32
//			m_Left.width = 1; // 1
//			m_Left.height = 2; // 2
//		}
//	}
//}
//
//void Player::setFalling(bool falling) {
//	m_isFalling = falling;
//}
//
//sf::FloatRect Player::getHead()
//{
//	return m_Head;
//}
//
//sf::FloatRect Player::getFeet()
//{
//	return m_Feet;
//}
//
//sf::FloatRect Player::getLeft()
//{
//	return m_Left;
//}
//
//sf::FloatRect Player::getRight()
//{
//	return m_Right;
//}
//
//sf::FloatRect Player::getPosition() {
//	/*cout << "Local Bounds" << endl;
//	cout << "\n";
//	cout << "top: " << m_Sprite.getLocalBounds().top << endl;
//	cout << "left: " << m_Sprite.getLocalBounds().left << endl;
//	cout << "height: " << m_Sprite.getLocalBounds().height << endl;
//	cout << "width: " << m_Sprite.getLocalBounds().width << endl;
//	cout << "\n";*/
//	return m_Sprite.getLocalBounds();
//}
//
//sf::FloatRect Player::getGlobal() {
//	/*cout << "Global Bounds" << endl;
//	cout << "\n";
//	cout << "top: " << m_Sprite.getGlobalBounds().top << endl;
//	cout << "left: " << m_Sprite.getGlobalBounds().left << endl;
//	cout << "height: " << m_Sprite.getGlobalBounds().height << endl;
//	cout << "width: " << m_Sprite.getGlobalBounds().width << endl;
//	cout << "\n";*/
//	return m_Sprite.getGlobalBounds();
//}
//
//sf::Sprite Player::getSprite() {
//	return m_Sprite;
//}
//
//float Player::getPositionY() {
//	return m_Position.y;
//}