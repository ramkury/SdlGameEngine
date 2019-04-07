#include "TileMap.h"
#include <fstream>


TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet) : tileSet(tileSet)
{
	Load(file);
}

void TileMap::Load(const std::string& file)
{
	std::ifstream fs(file);
	char c;
	fs >> mapWidth >> c;
	fs >> mapHeight >> c;
	fs >> mapDepth >> c;

	const size_t mapSize = mapWidth * mapHeight * mapDepth;

	tileMatrix.clear();
	tileMatrix.reserve(mapSize);

	while (!fs.eof())
	{
		int tile;
		fs >> tile >> c;
		tileMatrix.push_back(tile);
	}

	if (tileMatrix.size() != mapSize)
	{
		throw std::runtime_error("Bad tile map: " + file);
	}
}

void TileMap::SetTileSet(TileSet* tileSet)
{
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z)
{
	const int index = 
		(z * mapWidth * mapHeight) + 
		(y * mapWidth) + 
		(x);
	return tileMatrix.at(index);
}

void TileMap::Render()
{
	for (int z = 0; z < mapDepth; ++z)
	{
		RenderLayer(z);
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
	for (int x = 0; x < mapWidth; ++x)
	{
		for (int y = 0; y < mapHeight; ++y)
		{
			tileSet->RenderTile(
				At(x, y, layer),
				x * tileSet->GetTileWidth(),
				y * tileSet->GetTileHeight()
			);
		}
	}
}

int TileMap::MapWidth() const
{
	return mapWidth;
}

int TileMap::MapHeight() const
{
	return mapHeight;
}

int TileMap::MapDepth() const
{
	return mapDepth;
}
