#include "TileSet.h"
#include <stdexcept>

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, const std::string& file)
	: tileSet(associated, file), tileWidth(tileWidth), tileHeight(tileHeight), rows(0), columns(0)
{
	if (tileSet.IsOpen())
	{
		rows = tileSet.GetHeight() / tileHeight;
		columns = tileSet.GetWidth() / tileWidth;
	}
}

void TileSet::RenderTile(unsigned index, float x, float y)
{
	SDL_assert(index < unsigned(rows * columns));
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

