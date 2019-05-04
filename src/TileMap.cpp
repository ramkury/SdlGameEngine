#include "TileMap.h"
#include <fstream>
#include "Camera.h"


TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet) : Component(associated), tileSet(tileSet)
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

	while (tileMatrix.size() < tileMatrix.capacity())
	{
		int tile;
		fs >> tile >> c;
		tileMatrix.push_back(tile - 1);
	}

	if (tileMatrix.size() != mapSize)
	{
		throw std::runtime_error("Bad tile map: " + file);
	}
}

void TileMap::SetTileSet(TileSet* tileSet)
{
	this->tileSet = std::unique_ptr<TileSet>(tileSet);
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
		RenderLayer(z, int(Camera::pos.x), int(Camera::pos.y));
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
	const int parallax_offset = (layer * 2) + 1;
	for (int x = 0; x < mapWidth; ++x)
	{
		for (int y = 0; y < mapHeight; ++y)
		{
			const auto tile = At(x, y, layer);
			if (tile < 0) continue;

			tileSet->RenderTile(
				tile,
				x * tileSet->GetTileWidth() - cameraX * parallax_offset,
				y * tileSet->GetTileHeight() - cameraY * parallax_offset
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

void TileMap::Update(float dt)
{
}

bool TileMap::Is(const std::string& type)
{
	return type == "TileMap";
}
