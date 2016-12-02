#include"Camera2D.h"

using namespace DARE_Engine;

Camera2D::Camera2D() :_position(0.0f, 0.0f), _cameraMatrix(1.0f), _scale(1.0f), _change(true), _width(1366), _height(768), _orthoMatrix(1.0f)
{

}

void Camera2D::init(int width, int height)
{
	_width = width;
	_height = height;
	_orthoMatrix = glm::ortho(0.0f, (float)_width, 0.0f, (float)_height);
}

void Camera2D::update()
{

	/*if (start == 1)
	{
		//Camera is being initialized for the first time
		glm::vec3 translate(_width / 2,  _height / 2, 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);
		start = 0;
	}
	*/
    if (_change == true)
	{
		glm::vec3 translate(_position.x-_width/2 , -_position.y+_height/2 , 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);

		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) *_cameraMatrix;

	
		_change = false;
	}
}

Camera2D::~Camera2D()
{

}