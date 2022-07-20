#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

struct Animation {
	std::vector<IntRect> frames, flippedFrames, rotatedFrames, rotatedFlippedFrames;
	float currentFrame, animationSpeed;
	bool flip, isPlaying, rotate, rotateFlip;
	Sprite sprite;

	Animation(Texture &texture, int x, int y, int width, int height, int framesCount, float speed, int step);

	Animation() = default;

	void Tick(float time);
};

Animation::Animation(Texture& texture, int x, int y, int width, int height, int framesCount, float speed, int step) {
	animationSpeed = speed;
	sprite.setTexture(texture);

	currentFrame = 0;
	isPlaying = true;
	flip = false;
	rotate = false;

	for (int i = 0; i < framesCount; i++) {
		frames.push_back(IntRect(x + i * step, y, width, height));
		flippedFrames.push_back(IntRect(x + i * step + width, y, -width, height));
		rotatedFrames.push_back(IntRect(x + i * step, y+height, width, -height));
		rotatedFlippedFrames.push_back(IntRect(x + i * step+width, y + height, -width, -height));
	}
}

void Animation::Tick(float time) {
	if (!isPlaying) {
		return;
	}

	currentFrame += animationSpeed * time;

	if (currentFrame > frames.size()) {
		currentFrame -= frames.size();
	}

	int i = currentFrame;
	sprite.setTextureRect(frames[i]);
	if (flip) {
		sprite.setTextureRect(flippedFrames[i]);
	}
	if (rotate) {
		sprite.setTextureRect(rotatedFrames[i]);
	}
	if (rotateFlip) {
		sprite.setTextureRect(rotatedFlippedFrames[i]);
	}
}

struct AnimationManager : public Animation{
	String animationName;
	std::map<String, Animation> animationMap;

	AnimationManager() = default;

	void Draw(RenderWindow& window, int x = 0, int y = 0);

	void CreateAnimation(String name, Texture &texture, int x, int y, int width, int height, int framesCount, float speed, int step);

	void Set(String name) {
		animationName = name;
		animationMap[animationName].flip = false;
		animationMap[animationName].rotate = false;
		animationMap[animationName].rotateFlip = false;
	}

	void Flip(bool flip) {
		animationMap[animationName].flip = flip;
	}

	void Rotate(bool rotate) {
		animationMap[animationName].rotate = rotate;
	}

	void RotateFlip(bool rotateFlip) {
		animationMap[animationName].rotateFlip = rotateFlip;
	}

	void Tick(float time) {
		animationMap[animationName].Tick(time);
	}

	void Pause() {
		animationMap[animationName].isPlaying = false;
	}

	void Play() {
		animationMap[animationName].isPlaying = true;
	}

};

void AnimationManager::CreateAnimation(String name, Texture& texture, int x, int y, int width, int height, int framesCount, float speed, int step) {
	animationMap[name] = Animation(texture, x, y, width, height, framesCount, speed, step);
	animationName = name;
}

void AnimationManager::Draw(RenderWindow& window, int x, int y) {
	animationMap[animationName].sprite.setPosition(x, y);
	window.draw(animationMap[animationName].sprite);
}
