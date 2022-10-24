#include "Player.h"

Player::Player() {
	m_Health = INITIAL_HEALTH;
	m_Speed = INITIAL_SPEED;
	m_JumpDuration = 0.5;

	m_Sprite = Sprite(TextureHolder::GetTexture(
		"Graphics/Free 3 Cyberpunk Sprites Pixel Art/2 Punk/Punk_SpriteSheet.png"));
	m_Sprite.setTextureRect(IntRect{ 0, 0, 48, 56 });

	ani_counter = 1;
}

void Player::spawn(Vector2f resolution, float gravity) {
	// depending on resolution set position and scale of player
	if (m_Resolution.x == 2560 && m_Resolution.y == 1440) {
		//m_Sprite.setPosition(250, 1080);
		m_Sprite.setScale(6, 6);
	}
	else if (m_Resolution.x == 1920 && m_Resolution.y == 1080) {
		//m_Sprite.setPosition(200, 850);
		m_Sprite.setScale(5, 5);
	}
	else if (m_Resolution.x == 1680 && m_Resolution.y == 1050) {
		//m_Sprite.setPosition(200, 800);
		m_Sprite.setScale(4.5, 4.5);
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

void Player::update(float elapsedTime, int groundHeight) {
	// plays player run animation
	setSpriteFromSheet(IntRect(0, 0, 288, 56));
	moveTextureRect(elapsedTime);

	//if m_Jump is true
	if (m_Jump) {
		m_TimeThisJump += elapsedTime; // time jump by adding elapsedTime

		// if timer for jump is less than players set jump duration
		if (m_TimeThisJump < m_JumpDuration) { 
			// move player up using gravity and elapsedTime
			m_Position.y -= m_gravity * 2 * elapsedTime;

			// set jump animation frame
			setSpriteFromSheet(IntRect(48, 58, 96, 56));
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

		// if players position y has hit current ground height
		// stop falling
		if (m_Position.y >= groundHeight) {
			m_isFalling = false;
		}
		// set falling animation frame
		setSpriteFromSheet(IntRect(144, 58, 192, 56));
	}

	// set sprites position
	m_Sprite.setPosition(m_Position);
}

void Player::setSpriteFromSheet(IntRect textureBox)
{
	// get sprite sheets left and top values
	sheetCoordinate = Vector2i(textureBox.left, textureBox.top);
	// set sprite size
	spriteSize = Vector2i(48, 56);

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
	timePerFrame = 0.09; // each frame will last 0.09 seconds

	animationTimer += elapsedTime;
	if (animationTimer > timePerFrame) {
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