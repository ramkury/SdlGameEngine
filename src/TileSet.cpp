#include "TileSet.h"

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, const std::string& file)
	: tileSet(associated, file), tileWidth(tileWidth), tileHeight(tileHeight)
{
	if (tileSet.IsOpen())
	{
		rows = tileSet.GetHeight() / tileHeight;
		columns = tileSet.GetWidth() / tileWidth;
	}
}

void TileSet::RenderTile(unsigned index, float x, float y)
{
	const bool validIndex = index < unsigned(rows * columns);
	if (!validIndex)
	{
		throw std::runtime_error("Bad index");
	}

	const int row = index / columns;
	const int col = index % columns;
	const int srcY = row * tileHeight;
	const int srcX = col * tileWidth;
	tileSet.SetClip(srcX, srcY, tileWidth, tileHeight);
	tileSet.Render(int(x), int(y), tileWidth, tileHeight);
}

int TileSet::GetTileWidth() const
{
	return tileWidth;
}

int TileSet::GetTileHeight() const
{
	return tileHeight;
}

