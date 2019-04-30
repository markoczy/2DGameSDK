#include <2DGameSDK/world/GameWorldFactory.h>

using namespace std;

namespace game {

  using json = nlohmann::json;

  GameWorld* GameWorldFactory::CreateGameWorld(std::string tilemapFile, std::string materialMapFile, std::string texturesPrefix) {
    return nullptr;
  }

  Tilemap GameWorldFactory::loadTilemap(std::string filename) {
    auto ret = Tilemap();

    ifstream ifs(filename);
    json data;
    ifs >> data;

    auto layers = data["layers"];
    int curLayer = 0;

    // Loop Layers
    while(layers[curLayer] != nullptr) {
      auto layer = layers[curLayer];
      string name = layer["name"].get<string>();
      int number = layer["number"].get<int>();

      auto layerOut = TileLayer();
      layerOut.Name = name;
      layerOut.Number = number;
      int curTile = 0;
      auto tiles = layer["tiles"];

      // Loop Tiles
      while(tiles[curTile] != nullptr) {
        // LOGD("Processing Tile: " << curTile);
        auto tile = tiles[curTile];
        int tileId = tile["tile"].get<int>();
        // LOGD("TileId: " << tileId);
        if(tileId >= 0) {
          auto tileOut = Tile();
          tileOut.Id = tile["index"].get<int>();
          tileOut.Rot = tile["rot"].get<int>();
          tileOut.X = tile["x"].get<int>();
          tileOut.Y = tile["y"].get<int>();
          tileOut.FlipX = tile["flipX"].get<bool>();
          tileOut.FlipY = tile["flipY"].get<bool>();
          // LOGD("TILE:: index: " << index << ", rot: " << rot << ", tileId: " << tileId << ", x: " << x << ", y: " << y << ", flipX: " << flipX);
          layerOut.Tiles[tileOut.Y][tileOut.X] = tileOut;
          // layerOut->AddTile(index, rot, tileId, x, y, false);
        } else {
          // LOGD("Skipping tile: " << curTile);
        }
        // LOGD("End Tile: " << curTile);
        curTile++;
      }
      curLayer++;
      // layerOut.tiles = tilesOut;
      mLayers.push_back(layerOut);
    }
    sort(mLayers.begin(), mLayers.end(), compareLayers);

    return ret;
  }
} // namespace game