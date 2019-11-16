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

  GameWorld* GameWorldFactory::CreateGameWorld(Game* game, std::string tilemapFile, std::string materialMapFile, std::string texturesPrefix) {
    auto tilemap = loadTilemap(tilemapFile);
    loadTextures(tilemap, texturesPrefix);
    MaterialMap* materialMap = nullptr;
    if(materialMapFile != "") {
      materialMap = loadMaterialMap(game, materialMapFile);
    }
    auto world = new GameWorld(tilemap, materialMap);
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

  MaterialMap* GameWorldFactory::loadMaterialMap(Game* game, std::string filename) {
    try {
      ifstream ifs(filename);
      json data;
      ifs >> data;
      auto ret = new MaterialMap();

      auto materials = data["materials"];
      int curMaterial = 0;
      while(materials[curMaterial] != nullptr) {
        auto material = materials[curMaterial];
        auto materialOut = Material();
        materialOut.TileID = material["tile"].get<int>();
        LOGD("Material " << curMaterial << " tileID: " << materialOut.TileID);
        materialOut.Name = material["name"].get<string>();
        LOGD("Material " << curMaterial << " name: " << materialOut.Name);

        int curShape = 0;
        auto shapes = material["shapes"];
        while(shapes[curShape] != nullptr) {
          auto shape = shapes[curShape];

          float friction = shape["friction"].get<float>();
          LOGD("Shape " << curMaterial << "-" << curShape << " friction: " << friction);
          float elasticity = shape["elasticity"].get<float>();
          LOGD("Shape " << curMaterial << "-" << curShape << " elasticity: " << elasticity);
          bool sensor = shape["sensor"].get<bool>();
          LOGD("Shape " << curMaterial << "-" << curShape << " sensor: " << sensor);

          Shape<StaticShapeDefinition>* shapeOut = nullptr;
          string def = shape["shape"].get<string>();
          LOGD("Shape " << curMaterial << "-" << curShape << " definition: " << def);
          if(def == "rect" || def == "rectangle") {
            float width = shape["width"].get<float>();
            LOGD("Shape " << curMaterial << "-" << curShape << " width: " << width);
            float height = shape["height"].get<float>();
            LOGD("Shape " << curMaterial << "-" << curShape << " height: " << height);
            shapeOut = ShapeFactory::CreateStaticRectangleShape(game, width, height, friction, elasticity, sensor);
          } else if(def == "circle") {
            // TODO
            LOGE("Unimplemented circle shape");
          } else if(def == "poly" || def == "polygon") {
            // TODO
            LOGE("Unimplemented polygon shape");
          } else {
            LOGE("Bad definition type: " + def);
          }

          if(shapeOut != nullptr) {
            materialOut.Shapes.push_back(shapeOut);
          }

          ret->Materials[materialOut.TileID] = materialOut;
          curShape++;
        }

        curMaterial++;
      }
      return ret;

    } catch(const std::exception& e) {
      stringstream ss;
      ss << "Failed to load materialmap: " << e.what();
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