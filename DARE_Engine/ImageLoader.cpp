#include "ImageLoader.h"
#include "Picopng.h"
#include "IOManager.h"
#include "errors.h"

#include<iostream>

using namespace std;
using namespace DARE_Engine;

OpenGLTexture ImageLoader::loadPNG(string filePath)
{
	OpenGLTexture texture = {};
	
	std::vector<unsigned char>in;
	std::vector<unsigned char> out;
	unsigned long width, height;

	
	if (IOManager::readFileToBuffer(in, filePath) == false)
		fatalError("Failed to load PNG File to Buffer");

	int errorCode = decodePNG(out, width, height, &in[0], in.size());

	if (errorCode != 0)
		fatalError("decodePNG failed with error: " + to_string(errorCode));
	
	glGenTextures(1, &(texture.ID));

	glBindTexture(GL_TEXTURE_2D, texture.ID); //Binds the 2D TEx to the created tex id.

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &out[0]);

	/*  --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	     glTexImage2D Specifies a 2D Texture image. First parameter must be GL_TEXTUER_2D, next is the LOD number with 0 for base image level and n for the nth mipmap reduction              
	     Next is the internal format for the no. of color components. Can be 1-4 or a symbolic constant. Width and height of 2^n+2(border) size. Then the width of the border (must be 0 or 1) 
	     Then the format of the pixel data and the data type of the pixel data. Finally a pointer to the image data in memory																  
	    -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	*/


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//Sets the Texture Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/*  --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		 Some notes about the various parameters used:																																													
		 Actually before that, some notes about Texture Mapping.																																									
																																																									
		 Take a quad. Or any geometrical mesh. Without any texture it, the mesh will look bland. So the first step is to apply a texture on it. This process where a Texture is applied onto a 2D/3D									
		 object is texture mapping.																																																		
																																																										
		 There are two major ways texture mapping works. Clamping and wrapping.																																							
			Clamping is when the texture is applied once and then to fill the sprite/mesh the edge pixels of the textures are smeared/streched to the boundries of the sprite/mesh.														
																																																										
			Wrapping is when the textuer is applied how many ever times it is needed to fill the mesh. Generally it is repeated at every integer junction.																				
			Mirror is similar to Wrapping but the odd integer ones will be mirrored																																						
			Clamp to Border is when the coordinates falling outside the Texture are given a specific color.																																
																																																										
		 In tex terms x,y,z are referred to as s,t,r																																														
																																																										
		 The GL_TEXTURE_MAG_FILTER can be used to apply texture magnification when the pixel being texture mapped to is less than one texture element. GL_NEAR returns the value of the nearest texture element							
		 to the center of the pixel being textured																																														
		 GL_LINEAR returns the weighted average of the surrounding 4 textures of the pixel being textured.																																
		 GL_LINEAR_MIPMAP_LINEAR chooses two mip maps that match the size of the pixel being textured and uses the GL_LINEAR parameter to produce a tex value from each mipmap. Final mipmap is a weighted average of both the mipmaps  
		--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	*/

	glGenerateMipmap(GL_TEXTURE_2D);//Generates a mipmap for the texture

	/*	---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		 Notes about Mipmapping:																																												
		 When a textureed object moves away from the viewpoint/camera, the texture must be applied to a smaller object. The texture is filtered down to the smaller size to make this possible.					
		 But this filtering down might cause noticable flickering. This flickring can be avoided by mip mapping where a smaller texture is created from the original hig res and applied when the object becomes
		 smaller																																																
		---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	*/

	glBindTexture(GL_TEXTURE_2D, 0);//Unbinds the texture

	texture.width = width;
	texture.height = height;
	return texture;
}