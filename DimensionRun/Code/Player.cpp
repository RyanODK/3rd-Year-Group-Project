#include "Player.h"

Player::Player() {
	m_Health = INITIAL_HEALTH;
	m_Speed = INITIAL_SPEED;
	m_JumpDuration = 0.25;
	m_SlideDuration = 0.5;

	m_Sprite = Sprite(TextureHolder::GetTexture(
		"Graphics/Free 3 Cyberpunk Sprites Pixel Art/2 Punk/Punk_SpriteSheet.png", false));

	ani_counter = 1;
}

void Player::spawn(Vector2f resolution, float gravity) {
	// depending on resolution set position and scale of player
	if (m_Resolution.x == 2560 && m_Resolution.y == 1440) {
		m_Sprite.setScale(6, 6);
	}
	else if (m_Resolution.x == 1920 && m_Resolution.y == 1080) {
		m_Sprite.setScale(5, 5);
	}
	else if (m_Resolution.x == 1680 && m_Resolution.y == 1050) {
		m_Sprite.setScale(4.5, 4.5);
	}

	if (!m_Jump && !m_isFalling) {
		m_Position.x = (m_Resolution.x / 100) * 10;
		m_Position.y = (m_Resolution.y / 100) * 75;
		m_Sprite.setPosition(m_Position);
	}

	// store gravity for future use
	m_gravity = gravity;

	// store resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

bool Player::Jump() {
	m_JustJumped = false;

	// if user presses space 
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		// m_Jump and m_isFalling is false
		if (!m_Jump && !m_isFalling) {
			m_Jump = true; // set m_Jump to true
			m_TimeThisJump = 0; // set timer for jump to 0
			m_JustJumped = true; // set just jumped to false to stop constantly jumping
		}
	}
	// else player is not pressing space bar
	else 
	{
		m_Jump = false; // set m_Jump to false
		m_isFalling = true; // set m_IsFalling to true
	}
	
	// return m_JustJumped
	return m_JustJumped;
}

bool Player::Slide() {
	m_JustSlid = false;

	if (Keyboard::isKeyPressed(Keyboard::C)) {
		if (!m_IsSliding) {
			m_IsSliding = true;
			m_TimeThisSlide = 0;
			m_JustSlid = true;
		}
	}
	else {
		m_IsSliding = false;
	}

	return m_JustSlid;
}

bool Player::Laser() {
	m_JustLasered = false;

	if (Keyboard::isKeyPressed(Keyboard::X)) {
		if (!m_IsLasering) {
			m_IsLasering = true;
			m_TimeThisLaser = 0;
			m_JustLasered = true;
		}
	}
	else {
		m_IsLasering = false;
	}

	return m_JustLasered;
}

void Player::update(float elapsedTime, int groundHeight) {
	// plays player run animation
	m_TimePerFrame = 0.09;
	setSpriteFromSheet(IntRect(0, 0, 288, 56));
	moveTextureRect(elapsedTime);

	//if m_Jump is true
	if (m_Jump) {
		m_TimeThisJump += elapsedTime; // time jump by adding elapsedTime

		// if timer for jump is less than players set jump duration
		if (m_TimeThisJump < m_JumpDuration) { 
			// move player up using gravity and elapsedTime
			m_Position.y -= m_gravity * 2 * elapsedTime;
			m_Sprite.setPosition(m_Position);
			// set jump animation frame
			setSpriteFromSheet(IntRect(0, 58, 96, 54));
		}
		// else timer for jump has hit allowed jump duration
		else {
			m_Jump = false; // stop jump
			m_isFalling = true; // start falling
		}
	}

	// if player is falling
	if (m_isFalling) {
		// increment position y of player with gravity to make sprite fall down
		m_Position.y += m_gravity * elapsedTime;
		m_Sprite.setPosition(m_Position);
		// if players position y has hit current ground height
		// stop falling
		if (m_Position.y >= groundHeight) {
			m_isFalling = false;
		}
		// set falling animation frame
		setSpriteFromSheet(IntRect(144, 58, 192, 54));
	}

	if (m_IsSliding) {
		m_TimeThisSlide += elapsedTime;

		if (m_TimeThisSlide < m_SlideDuration) {
			setSpriteFromSheet(IntRect(0, 327, 49, 54));
		}
		else {
			m_IsSliding = false;
		}
	}

	if (m_IsLasering) {
		m_TimePerFrame = 0.9;
		m_TimeThisLaser += elapsedTime;

		if (m_TimeThisLaser < 0.2) {
			setSpriteFromSheet(IntRect(0, 374, 385, 54));
			moveTextureRect(elapsedTime);
		}
		else {
			m_IsLasering = false;
		}
	}
}

void Player::setSpriteFromSheet(IntRect textureBox)
{
	// get sprite sheets left and top values
	sheetCoordinate = Vector2i(textureBox.left, textureBox.top);
	// set sprite size
	spriteSize = Vector2i(48, 54);

	// if sprite sheet width is greater than sprite size x
	if (textureBox.width > spriteSize.x)
	{
		// set animation iterator limit to width of sprite sheet / sprite size x
		animation_it_limit = textureBox.width / spriteSize.x;
	}
	// else if sprite sheet height is greater than sprite size y
	else if (textureBox.height > spriteSize.y)
	{
		// set animation iterator limit to height of sprite sheet / sprite size y
		animation_it_limit = textureBox.height / spriteSize.y;
	}
	// else throw error 
	else
		throw logic_error("Animation bounding box must contain multiply sprites, setSprite(sf::IntRect )\n");

	// set sprites texture rect size to sheet coordinate (left and top) by sprite size (x and y)
	m_Sprite.setTextureRect(IntRect{ sheetCoordinate, spriteSize });

}

void Player::moveTextureRect(float elapsedTime) {
	// if animation counter == animation iterator limit
	if (ani_counter == animation_it_limit) {
		// set animation counter to 0
		ani_counter = 0;
	}

	m_Sprite.setTextureRect(IntRect(sheetCoordinate + Vector2i(
		spriteSize.x * ani_counter, 0), spriteSize));

	// increment animation counter to point to next frame
	double timePerFrame;
	timePerFrame = m_TimePerFrame;

	animationTimer += elapsedTime;
	if (animationTimer >= timePerFrame) {
		ani_counter++;
		animationTimer = 0;
	}
}

FloatRect Player::getPosition() {
	return m_Sprite.getLocalBounds();
}

Sprite Player::getSprite() {
	return m_Sprite;
}