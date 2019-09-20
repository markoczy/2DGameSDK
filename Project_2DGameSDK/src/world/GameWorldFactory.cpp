#include <2DGameSDK/world/GameWorldFactory.h>

using namespace std;

namespace game {

  using json = nlohmann::json;

  bool compareLayers(TileLayer* i, TileLayer* j) { return (i->Number < j->Number); }

  string getFilename(string prefix, int tile, int pad) {
    stringstream ss;
    ss << prefix;
    ss << setfill('0') << setw(pad) << tile;
    ss << ".png";
    auto ret = ss.str();
    LOGD("Filename: " << ret);
    return ret;
  }

  GameWorld* GameWorldFactory::CreateGameWorld(std::string tilemapFile, std::string /*materialMapFile*/, std::string texturesPrefix) {
    auto tilemap = loadTilemap(tilemapFile);
    loadTextures(tilemap, texturesPrefix);
    auto world = new GameWorld(tilemap, nullptr);
    return world;
  }

  Tilemap* GameWorldFactory::loadTilemap(std::string filename) {
    try {
      ifstream ifs(filename);
      json data;
      ifs >> data;

      auto layers = data["layers"];
      int curLayer = 0;
      auto layersOut = vector<TileLayer*>();

      auto tilemapOut = new Tilemap();
      tilemapOut->TileWidth = data["tilewidth"];
      tilemapOut->TileHeight = data["tileheight"];
      tilemapOut->TilesWide = data["tileswide"];
      tilemapOut->TilesHigh = data["tileshigh"];

      // Loop Layers
      while(layers[curLayer] != nullptr) {
        auto layer = layers[curLayer];
        string name = layer["name"].get<string>();
        int number = layer["number"].get<int>();

        auto layerOut = new TileLayer();
        layerOut->Name = name;
        layerOut->Number = number;
        layerOut->Tiles = std::vector<std::vector<Tile*>>(tilemapOut->TilesHigh);
        for(unsigned int i = 0; i < layerOut->Tiles.size(); i++) {
          layerOut->Tiles[i] = std::vector<Tile*>(tilemapOut->TilesWide);
        }

        int curTile = 0;
        auto tiles = layer["tiles"];

        // Loop Tiles
        while(tiles[curTile] != nullptr) {
          // LOGD("Processing Tile: " << curTile);
          auto tile = tiles[curTile];
          auto tileOut = new Tile();

          tileOut->Tile = tile["tile"].get<int>();
          // LOGD("Tile: " << tileOut.Tile);
          tileOut->Id = tile["index"].get<int>();
          // LOGD("Id " << tileOut.Id);
          tileOut->Rot = tile["rot"].get<int>();
          // LOGD("Rot " << tileOut.Rot);
          tileOut->X = tile["x"].get<int>();
          // LOGD("X " << tileOut.X);
          tileOut->Y = tile["y"].get<int>();
          // LOGD("Y " << tileOut.Y);
          tileOut->FlipX = tile["flipX"].get<bool>();
          // LOGD("FlipX " << tileOut.FlipX);
          layerOut->Tiles[tileOut->Y][tileOut->X] = tileOut;

          curTile++;
        }
        curLayer++;
        layersOut.push_back(layerOut);
      }
      sort(layersOut.begin(), layersOut.end(), compareLayers);
      tilemapOut->Layers = layersOut;
      return tilemapOut;
    } catch(std::exception& e) {
      stringstream ss;
      ss << "Failed to load tilemap: " << e.what();
      throw std::runtime_error(ss.str());
    }
  }

  void GameWorldFactory::loadTextures(Tilemap* tilemap, std::string prefix) {
    try {
      for(unsigned int iLayer = 0; iLayer < tilemap->Layers.size(); iLayer++) {
        auto layer = tilemap->Layers[iLayer];
        for(unsigned int iY = 0; iY < layer->Tiles.size(); iY++) {
          for(unsigned int iX = 0; iX < layer->Tiles[iY].size(); iX++) {
            auto tile = layer->Tiles[iY][iX];
            if(tile->Tile > -1) {
              string fileName = getFilename(prefix, tile->Tile, 2);
              tile->Texture = AssetManager::GetTexture(fileName);
            }
          }
        }
      }
    } catch(const std::exception& e) {
      stringstream ss;
      ss << "Failed to load textures: " << e.what();
      throw std::runtime_error(ss.str());
    }
  }
} // namespace game