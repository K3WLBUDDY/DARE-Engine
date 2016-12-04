#include "sprite.h"

#include "vertex.h"

#include<cstddef>

using namespace DARE_Engine;

sprite::sprite()
{
	_vboID = 0;
}


void sprite::init(float x, float y, float width, float height,std::string texPath)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	_texture = ResourceManager::getTexture(texPath);

	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);//Generates the VBO
	}
	

	vertex vertexData[6];

	//Sets the Vertice Coordinates for the 6 vertex coordinates needed

	//Since the Vertices here are a structure, these vertices are called Interleaved Vertices

	vertexData[0].setPosition(x + width, y+height);
	vertexData[1].setPosition(x, y +height);
	vertexData[2].setPosition(x, y);
	vertexData[3].setPosition(x, y);
	vertexData[4].setPosition(x + width, y);
	vertexData[5].setPosition(x + width, y + height);

	vertexData[0].setUV(1.0f, 1.0f);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setUV(0.0f, 0.0f);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setUV(1.0f, 1.0f);
	
	for (int i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255, 0, 255, 255);

		
	}
	
	vertexData[1].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);//Binds the type of Data that is being uploaded to the GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);//Uploads the Data to the VBO present in the GPU

	glBindBuffer(GL_ARRAY_BUFFER, 0);//UNbinds the Buffer
}

void sprite::draw()
{

	glBindTexture(GL_TEXTURE_2D, _texture.ID);
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	

	glDrawArrays(GL_TRIANGLES, 0, 6);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//Unbinds the Data.

}


sprite::~sprite()
{
	if (_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}
