#pragma once
#include"DARE_Engine.h"
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
//

namespace DARE_Engine{

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void update();
		void init(int width, int height);
		void setPosition(const glm::vec2 newPosition)
		{
			_position = newPosition;
			_change = true;
		}

		void setScale(const float newScale)
		{
			_scale = newScale;
			_change = true;
		}

		glm::vec2 getPosition()
		{
			return _position;
		}

		float getScale()
		{
			return _scale;
		}

		glm::mat4 getCameraMatrix()
		{
			return _cameraMatrix;
		}

	private:

		int _width, _height;
		bool _change;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;

	};
}