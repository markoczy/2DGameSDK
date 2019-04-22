#include <2DGameSDK/world/GameWorldFactory.h>

using namespace std;

namespace game {

  using json = nlohmann::json;

  bool compareLayers(TileLayer i, TileLayer j) { return (i.Number < j.Number); };

  string getFilename(string prefix, int tile, int pad) {
    stringstream ss;
    ss << prefix;
    for(int i = 0; i < pad; i++) {
      ss << '0';
    }
    ss << tile;
    ss << ".png";
    auto ret = ss.str();
    cout << ret << endl;
    return ret;
  };

  GameWorld* GameWorldFactory::CreateGameWorld(std::string tilemapFile, std::string materialMapFile, std::string texturesPrefix) {
    cout << "0" << endl;
    auto tilemap = loadTilemap(tilemapFile);
    loadTextures(&tilemap, texturesPrefix);
    auto world = new GameWorld(&tilemap, nullptr);
    return world;
  }

  Tilemap GameWorldFactory::loadTilemap(std::string filename) {
    cout << 1 << endl;
    auto ret = Tilemap();

    ifstream ifs(filename);
    json data;
    ifs >> data;

    auto layers = data["layers"];
    int curLayer = 0;
    auto layersOut = vector<TileLayer>();
    cout << 2 << endl;

    // Loop Layers
    while(layers[curLayer] != nullptr) {
      cout << 3 << endl;
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
        cout << 4 << endl;
        // LOGD("Processing Tile: " << curTile);
        auto tile = tiles[curTile];
        int tileId = tile["tile"].get<int>();
        // LOGD("TileId: " << tileId);
        // if(tileId >= 0) {
        auto tileOut = Tile();
        tileOut.Tile = tile["tile"].get<int>();
        tileOut.Id = tile["index"].get<int>();
        tileOut.Rot = tile["rot"].get<int>();
        tileOut.X = tile["x"].get<int>();
        tileOut.Y = tile["y"].get<int>();
        tileOut.FlipX = tile["flipX"].get<bool>();
        // tileOut.FlipY = tile["flipY"].get<bool>();
        // LOGD("TILE:: index: " << index << ", rot: " << rot << ", tileId: " << tileId << ", x: " << x << ", y: " << y << ", flipX: " << flipX);
        layerOut.Tiles[tileOut.Y][tileOut.X] = tileOut;
        // layerOut->AddTile(index, rot, tileId, x, y, false);
        // } else {
        // LOGD("Skipping tile: " << curTile);
        // }
        // LOGD("End Tile: " << curTile);
        curTile++;
      }
      curLayer++;
      layersOut.push_back(layerOut);
      // layerOut.tiles = tilesOut;
      // mLayers.push_back(layerOut);
    }
    cout << 5 << endl;
    sort(layersOut.begin(), layersOut.end(), compareLayers);
    ret.Layers = layersOut;
    cout << 6 << endl;

    return ret;
  }

  void GameWorldFactory::loadTextures(Tilemap* tilemap, std::string prefix) {
    for(unsigned int iLayer = 0; iLayer < tilemap->Layers.size(); iLayer++) {
      auto layer = tilemap->Layers[iLayer];
      for(unsigned int iY = 0; iY < layer.Tiles.size(); iY++) {
        for(unsigned int iX = 0; iX < layer.Tiles[iY].size(); iX++) {
          auto tile = layer.Tiles[iY][iX];
          if(tile.Tile > -1) {
            string fileName = getFilename(prefix, tile.Tile, 1);
            tile.Texture = AssetManager::GetTexture(fileName);
          }
        }
        // auto tile = layer->TileAt(iTile);
        // tile->tex = nullptr;
        // int pad = 0;
        // Texture* tex = 0;
        // while(tex == 0 && pad < 5) {
        //   string lName = getFilename(aPrefix, tile->tile, pad);

        //   tex = aTexBase->Get(lName);
        //   LOGD("Texture name: " << lName << ", Pointer: " << tex);
        //   pad++;
        // }

        // if(tex == 0) {
        //   LOGE("Tile texture " << aPrefix << tile->tile << " not found");
        // } else {
        //   GetTile(iLayer, iTile)->tex = tex;
        // }

        // mLayers[iLayer].tiles[iTile].tex = tex;
        // mLayers[iLayer].tiles[iTile].tex = tex;

        // stringstream ss;
        // ss << aPrefix << tile.tile;
        // auto lName = ss.str();
        // aMap.layers[iLayer].tiles[iTile].tex = aTexBase->Get(lName);
      }
    }
  }
} // namespace game