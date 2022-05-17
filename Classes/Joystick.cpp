#include "Joystick.h"

// ������ ���
bool Joystick::isTouchCircle(Point pos, Point center, float radius)
{
	float dx = (pos.x - center.x);
	float dy = (pos.y - center.y);
	return (radius >= sqrt((dx*dx) + (dy*dy)));
}

Joystick::~Joystick()
{
	cocos2d::Director::getInstance()->getScheduler()->unschedule("JoyStickUpdate", this);
}

bool Joystick::init()
{
	if (!Layer::init())
		return false;


	_winSize = Director::getInstance()->getWinSize();

	_isTouch = false;

	// speed
	_speed = 0.1;

	// touch show
	_isTouchShow = false;

	// limit win size
	_isLimmitWinSize = false;

	// Joystick - Standard Position
	centerPos = Vec2(125, 125);

	// Joystick - Back Sprite (Limit)
	joystick_limit = Sprite::create("joystick_limit_circle.png");
	joystick_limit->setPosition(centerPos);
	this->addChild(joystick_limit);


	// Joystick - Front Sprite (Controler)
	joystick_control = Sprite::create("joystick_control_circle.png");
	joystick_control->setPosition(centerPos);
	this->addChild(joystick_control);

	// Joystick - Controler Position
	controlerPos = centerPos;

	// Touch Enabled
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);

	// setSchedule Update
	cocos2d::Director::getInstance()->getScheduler()->schedule(
		std::bind(&Joystick::update, this, std::placeholders::_1),
		this, 1 / 60.f, false, "JoyStickUpdate");

	return true;
}

void Joystick::update(float dt)
{
	// ���̽�ƽ - ������ ���� ��� ������Ʈ ����
	joystick_control->setPosition(controlerPos);

	// ��ġ �����϶��� ������
	if (_isTouch)
	{
		// ������ �Ÿ� ���ϱ�
		float moveX = controlerPos.x - centerPos.x;
		float moveY = controlerPos.y - centerPos.y;

		Vec2 charPos = mainChar->getPosition();

		if (checkLimit())
		{
			if (0 < charPos.x + moveX * _speed && charPos.x + moveX * _speed < _winSize.width)
			{
				charPos.x += moveX * _speed;
			}
			if (0 < charPos.y + moveY * _speed && charPos.y + moveY * _speed < _winSize.height)
			{
				charPos.y += moveY * _speed;
			}
			mainChar->setPosition(charPos);
		}
		else
		{
			charPos.x += moveX * _speed;
			charPos.y += moveY * _speed;
			mainChar->setPosition(charPos);
		}
	}
}

void Joystick::setSpeed(float speed)
{
	_speed = speed;
}

void Joystick::setMainChar(Sprite* mainChar)
{
	this->mainChar = mainChar;
}

void Joystick::setTouchShow(bool check)
{
	_isTouchShow = check;

	if (_isTouchShow)
		this->setVisible(false);
}

void Joystick::setLimitScreen(bool check)
{
	_isLimmitWinSize = check;
}

bool Joystick::checkLimit()
{
	return _isLimmitWinSize;
}

void Joystick::onTouchesBegan(const std::vector<Touch*> &touches, Event* unused_event)
{
	for (auto it : touches)
	{
		Touch* touch = it;
		if (_isTouchShow)
		{
			centerPos = touch->getLocation();
			joystick_limit->setPosition(centerPos);
			joystick_control->setPosition(centerPos);
			this->setVisible(true);
		}

		// ���̽�ƽ - ����Ʈ �����ȿ��� ������ �Ͽ��ٸ�
		if (isTouchCircle(touch->getLocation(), centerPos, joystick_limit->getContentSize().width / 4))
		{
			_isTouch = true;

			controlerPos = touch->getLocation();
		}
	}
}

void Joystick::onTouchesMoved(const std::vector<Touch*> &touches, Event* unused_event)
{
	for (auto it : touches)
	{
		Touch* touch = it;
		if (_isTouch)
		{
			float limitSize = joystick_limit->getContentSize().width / 4;	// ���� ������ ������

			// ��ġ�� ����Ʈ ������ �Ѿ��� �ÿ� ��Ʈ�ѷ��� ���κп� �����ְ� �ϱ� ����
			if (!(isTouchCircle(touch->getLocation(), centerPos, limitSize)))
			{
				Point touchPos = touch->getLocation();	// ��ġ ��ġ��

				float dX = touchPos.x - centerPos.x;
				float dY = touchPos.y - centerPos.y;

				float distance = sqrt(dX*dX + dY * dY);	// �밢�� ���� ���ϱ�
				float angle = atan2(dY, dX);			// ���� ���ϱ�

				if (distance > limitSize)
				{
					dX = cos(angle) * limitSize;
					dY = sin(angle) * limitSize;

					touchPos.x = centerPos.x + dX;
					touchPos.y = centerPos.y + dY;
				}

				controlerPos = Vec2(touchPos);

			}
			else
			{
				controlerPos = touch->getLocation();
			}
		}
	}
}

void Joystick::onTouchesEnded(const std::vector<Touch*> &touches, Event* unused_event)
{
	for (auto it : touches)
	{
		if (_isTouch)
		{
			// ��ġ�� ������ ���̽�ƽ�� ���� ��ġ�� ���ư�
			controlerPos = centerPos;
		}
		_isTouch = false;

		if (_isTouchShow)
			this->setVisible(false);
	}
}