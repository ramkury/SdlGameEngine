#pragma once
#include "GameObject.h"
#include "Sprite.h"

class TileSet
{
public:
	TileSet(GameObject& associated, int tileWidth, int tileHeight, const std::string& file);
	void RenderTile(unsigned index, float x, float y);
	int GetTileWidth() const;
	int GetTileHeight() const;

private:
	Sprite tileSet;
	int rows;
	int columns;
	int tileWidth;
	int tileHeight;
};

