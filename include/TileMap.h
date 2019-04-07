#pragma once
#include "GameObject.h"
#include "TileSet.h"

class TileMap
{
public:
	TileMap(GameObject& associated, const std::string& file, TileSet* tileSet);
	void Load(const std::string& file);
	void SetTileSet(TileSet* tileSet);
	int& At(int x, int y, int z = 0);
	void Render();
	void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
	int MapWidth() const;
	int MapHeight() const;
	int MapDepth() const;

private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
};

