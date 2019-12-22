#include <2DGameSDK/world/GameWorldFactory.h>

using namespace std;

namespace game {

  using json = nlohmann::json;

  bool compareLayers(TileLayer* i, TileLayer* j) {
    return i->GetNumber() < j->GetNumber();
  }

  string getFilename(string prefix, int tile, int pad) {
    stringstream ss;
    ss << prefix;
    ss << setfill('0') << setw(pad) << tile;
    ss << ".png";
    auto ret = ss.str();
    LOGD("Filename: " << ret);
    return ret;
  }

  GameWorld* GameWorldFactory::CreateGameWorld(Game* game, std::string tilemapFile, std::string materialMapFile, std::string texturesPrefix, int pad) {
    auto tilemap = loadTilemap(game, tilemapFile);
    loadTextures(tilemap, texturesPrefix, pad);
    MaterialMap* materialMap = nullptr;
    if(materialMapFile != "") {
      materialMap = loadMaterialMap(game, materialMapFile);
      loadMaterials(game, tilemap, materialMap);
    }
    auto world = new GameWorld(game, tilemap, materialMap);
    return world;
  }

  Tilemap* GameWorldFactory::loadTilemap(Game*, std::string filename) {
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

      auto worldBounds = sf::IntRect(0, 0, tilemapOut->TilesWide * tilemapOut->TileWidth, tilemapOut->TilesHigh * tilemapOut->TileHeight);
      auto tileBounds = sf::IntRect(0, 0, tilemapOut->TileWidth, tilemapOut->TileHeight);

      // Loop Layers
      while(layers[curLayer] != nullptr) {
        auto layer = layers[curLayer];

        auto layerOut = new TileLayer(worldBounds, tileBounds);
        if(layer["name"] != nullptr) {
          layerOut->SetName(layer["name"].get<string>());
        }

        if(layer["number"] != nullptr) {
          layerOut->SetNumber(layer["number"].get<int>());
        } else {
          LOGW("No number specified for layer");
        }

        if(layer["zindex"] != nullptr) {
          layerOut->SetNumber(layer["zindex"].get<int>());
        } else {
          layerOut->SetZIndex(constants::DEFAULT_ZINDEX_WORLD + layerOut->GetNumber());
        }

        auto tilesOut = std::vector<std::vector<Tile*>>(tilemapOut->TilesHigh);
        for(unsigned int i = 0; i < tilesOut.size(); i++) {
          tilesOut[i] = std::vector<Tile*>(tilemapOut->TilesWide);
        }

        int curTile = 0;
        auto tiles = layer["tiles"];

        // Loop Tiles
        while(tiles[curTile] != nullptr) {
          // LOGD("Processing Tile: " << curTile);
          auto tile = tiles[curTile];
          auto tileOut = new Tile();

          tileOut->TileID = tile["tile"].get<int>();
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
          tilesOut[tileOut->Y][tileOut->X] = tileOut;

          curTile++;
        }
        layerOut->SetTiles(tilesOut);
        layersOut.push_back(layerOut);
        curLayer++;
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
    LOGI("Start");
    try {
      ifstream ifs(filename);
      json data;
      ifs >> data;
      auto ret = new MaterialMap();
      float pxToMeter = game->GetOptions().MeterPerPixel;

      auto materials = data["materials"];
      int curMaterial = 0;
      while(materials[curMaterial] != nullptr) {
        auto material = materials[curMaterial];
        auto materialOut = new Material();
        materialOut->TileID = material["tile"].get<int>();
        LOGD("Material " << curMaterial << " tileID: " << materialOut->TileID);
        if(material["name"] != nullptr) {
          materialOut->Name = material["name"].get<string>();
          LOGD("Material " << curMaterial << " name: " << materialOut->Name);
        }
        if(material["type"] != nullptr) {
          materialOut->Type = material["type"].get<int>();
          LOGD("Material " << curMaterial << " type: " << materialOut->Type);
        }

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
            shapeOut = ShapeFactory::CreateStaticRectangleShape(game, width * pxToMeter, height * pxToMeter, friction, elasticity, sensor);
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
            materialOut->Shapes.push_back(shapeOut);
          }

          curShape++;
        }

        ret->Materials[materialOut->TileID] = materialOut;
        curMaterial++;
      }
      LOGI("Done");
      return ret;

    } catch(const std::exception& e) {
      stringstream ss;
      ss << "Failed to load materialmap: " << e.what();
      throw std::runtime_error(ss.str());
    }
  }

  void GameWorldFactory::loadTextures(Tilemap* tilemap, std::string prefix, int pad) {
    LOGI("Start");
    try {
      for(unsigned int iLayer = 0; iLayer < tilemap->Layers.size(); iLayer++) {
        auto layer = tilemap->Layers[iLayer];
        auto tiles = layer->GetTiles();
        for(unsigned int iY = 0; iY < tiles.size(); iY++) {
          for(unsigned int iX = 0; iX < tiles[iY].size(); iX++) {
            auto tile = tiles[iY][iX];
            if(tile->TileID > -1) {
              string fileName = getFilename(prefix, tile->TileID, pad);
              tile->Texture = AssetManager::GetTexture(fileName);
            }
          }
        }
        layer->OnTexturesLoaded();
      }
    } catch(const std::exception& e) {
      stringstream ss;
      ss << "Failed to load textures: " << e.what();
      throw std::runtime_error(ss.str());
    }
    LOGI("Done");
  }

  void GameWorldFactory::loadMaterials(Game* game, Tilemap* tilemap, MaterialMap* materialMap) {
    LOGI("Start");
    if(tilemap == nullptr || materialMap == nullptr) {
      LOGI("Not loading any materials");
      return;
    }

    // Pose converter is not initialized yet so we have to convert lowlevel
    float height = tilemap->TileHeight * tilemap->TilesHigh;
    float pxToMeter = game->GetOptions().MeterPerPixel;

    auto space = game->GetPhysicalWorld();
    for(auto layer : tilemap->Layers) {
      for(auto row : layer->GetTiles()) {
        for(auto tile : row) {
          if(tile->TileID == -1) {
            continue;
          }

          auto material = materialMap->Materials[tile->TileID];
          if(!material) continue;
          auto matBody = cpSpaceAddBody(space, cpBodyNewStatic());

          auto visualPos = sf::Vector2f((tile->X + 0.5) * tilemap->TileWidth, (tile->Y + 0.5) * tilemap->TileHeight);
          auto pos = cpv(visualPos.x * pxToMeter, (height - visualPos.y) * pxToMeter);

          for(auto shape : material->Shapes) {
            auto copy = shape->CopyTemplate();
            copy->AttachToBody(space, matBody);
          }
          cpBodySetPosition(matBody, pos);
          cpBodySetUserData(matBody, new CollisionTarget(tile, ObjectType::Tile));
          cpSpaceReindexShapesForBody(space, matBody); //?
          tile->Material = material;
        }
      }
    }
    LOGI("Done");
  }
} // namespace game