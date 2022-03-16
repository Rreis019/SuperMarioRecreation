#include "Sprite.h"
#include <SDL2/SDL_image.h>
#include "Game.h"
#include "Utils.h"
#include "Logger.h"

Sprite::~Sprite(){}

Sprite::Sprite(const char* filename)
{
	if(!fileExists(filename))
	{
		log("File not found: %s\n",filename);
		return;
	}

    SDL_Surface* imageSurface = IMG_Load(filename);
 	this->w = imageSurface->w;
	this->h = imageSurface->h;
	this->texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	SDL_FreeSurface(imageSurface);
}

Sprite::Sprite(const char* filename,SDL_Color transparentColor)
{
	if(!fileExists(filename))
	{
		log("File not found: %s\n",filename);
		return;
	}

    SDL_Surface* imageSurface = IMG_Load(filename);
    this->w = imageSurface->w;
	this->h = imageSurface->h;
	Uint32 colorkey = SDL_MapRGB(imageSurface->format, transparentColor.r, transparentColor.g, transparentColor.b);
	SDL_SetColorKey(imageSurface, SDL_TRUE, colorkey);
	this->texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	SDL_FreeSurface(imageSurface);
}

Sprite::Sprite(SDL_Surface* image_surface, int w, int h,SDL_Color transparentColor)
{
	this->w = w;
	this->h = h;
	Uint32 colorkey = SDL_MapRGB(image_surface->format, transparentColor.r, transparentColor.g, transparentColor.b);
	SDL_SetColorKey(image_surface, SDL_TRUE, colorkey);
	this->texture = SDL_CreateTextureFromSurface(renderer, image_surface);
	SDL_FreeSurface(image_surface);
}

void Sprite::draw(int x,int y,SDL_RendererFlip flip)
{  
	if(this->w == 0 || this->h == 0) return;
	if(!this->texture)
	{
		log("Sprite::draw: texture is null\n");
		return;
	}

    SDL_Rect rect = { x,y,this->w,this->h };
	SDL_Point center= SDL_Point();
    SDL_RenderCopyEx(renderer, this->texture, NULL, &rect, 0, &center, flip);
}

//get image in certain cell of sprite sheet
Sprite getImage(SDL_Surface* sheet, int FrameX, int FrameY, int margin, int width, int height, SDL_Color transparent)
{
	int x = FrameX * width + margin * FrameX;
	int y = FrameY * height + margin * FrameY;

	SDL_Surface* image = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

	SDL_Rect src = { x,y,width,height };
	SDL_Rect dest = { 0,0,width,height };
	SDL_BlitSurface(sheet, &src, image, &dest);

	return Sprite(image, width, height, transparent);
}

void loadSpriteSheet(std::vector<Sprite>& sprites,const char*  imagePath)
{
	std::string txtFile = swapExtension(imagePath,"txt");

	//if file not found assert
	if(!fileExists(txtFile.c_str()))
	{
		log("imagePath: %s\n",txtFile.c_str());
		system("pause");
		//assert(( false && "Sprite text configuration file not found"));
		exit(1);
	}

	FILE* file = fopen(txtFile.c_str(),"r");
	SpreadSheetInfo info;
	char buffer[256];
	fscanf(file,"%s = %i\n",buffer,&info.width);
	fscanf(file,"%s = %i\n",buffer,&info.height);
	fscanf(file,"%s = %hhu,%hhu,%hhu\n",buffer,&info.transparent.r,&info.transparent.g,&info.transparent.b);
	fscanf(file,"%s = %i\n",buffer,&info.margin);
	fclose(file);

	SDL_Surface* sheet = IMG_Load(imagePath);
	int totalFrameX = 0;
	int tempX = 0;
	while(tempX < sheet->w)
	{
		tempX += info.width + info.margin;
		totalFrameX++;
	}



	int totalFrameY = sheet->h / info.height;

	
	for(int y = 0;y < totalFrameY;y++)
	{
		for(int x = 0;x < totalFrameX;x++)
		{
			Sprite sprite = getImage(sheet, x, y, info.margin, info.width, info.height, {info.transparent.r,info.transparent.g,info.transparent.b,255});
			sprites.push_back(sprite);
		}
	}

	//free sheet
	SDL_FreeSurface(sheet);
}

void loadMultipleImages(std::vector<Sprite>& sprites, std::string FolderPath, std::string Base_ImageName)
{
	int index = 0;
	while (true)
	{
		std::string imageNames = FolderPath + Base_ImageName + std::to_string(index) + ".png";
		std::string extension = "";

		if(!fileExists(imageNames.c_str())) { break;}
		if(!getFileExtension(imageNames,extension)) { break;} //if no extension break
		if(strcmp(extension.c_str(),"png") != 0) { break;} //if extension is not png break

		std::string txtFile = swapExtension(imageNames, "txt");

		if(fileExists(txtFile.c_str())){
			 loadSpriteSheet(sprites,imageNames.c_str());
		}
		else{
			sprites.push_back(Sprite(imageNames.c_str(),{0, 108, 248,255}));
		}
		index++;
	}
}

void Sprite::destroy()
{
	 if(texture != nullptr) 
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}