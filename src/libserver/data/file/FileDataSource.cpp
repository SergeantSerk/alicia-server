/**
 * Alicia Server - dedicated server software
 * Copyright (C) 2024 Story Of Alicia
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 **/

#include "libserver/data/file/FileDataSource.hpp"

#include <fstream>

#include <nlohmann/json.hpp>

namespace
{

std::filesystem::path ProduceDataPath(
  const std::filesystem::path& root,
  const std::string& filename)
{
  if (not std::filesystem::exists(root))
    std::filesystem::create_directories(root);
  return root / (filename + ".json");
}

} // namespace

void soa::FileDataSource::Initialize(const std::filesystem::path& path)
{
  _path = path;
  _usersPath = _path / "users";
  create_directories(_usersPath);
  _charactersPath = _path / "characters";
  create_directories(_charactersPath);
  _horsesPath = _path / "horses";
  create_directories(_horsesPath);
  _ranchesPath = _path / "ranches";
  create_directories(_ranchesPath);
  _itemsPath = _path / "items";
  create_directories(_itemsPath);
  _metaFilePath = _path / "meta.json";

  const std::filesystem::path metaFilePath = ProduceDataPath(
    _metaFilePath, "meta");
  std::ifstream metaFile(metaFilePath);
  if (not metaFile.is_open())
  {
    return;
  }

  const auto meta = nlohmann::json::parse(metaFile);
  _sequentialUid = meta["sequentialUid"].get<uint32_t>();
}

void soa::FileDataSource::Terminate()
{
  const std::filesystem::path metaFilePath = ProduceDataPath(
    _metaFilePath, "meta");

  std::ofstream metaFile(metaFilePath);
  if (not metaFile.is_open())
  {
    return;
  }

  nlohmann::json meta;
  meta["sequentialUid"] = _sequentialUid;

  metaFile << meta.dump(2);
}

void soa::FileDataSource::RetrieveUser(std::string name, data::User& user)
{
  const std::filesystem::path dataFilePath = ProduceDataPath(
    _usersPath, name);

  std::ifstream file(dataFilePath);
  if (not file.is_open())
    return;

  const auto json = nlohmann::json::parse(file);
  user.name = json["name"].get<std::string>();
  user.token = json["token"].get<std::string>();
  user.characterUid = json["characterUid"].get<data::Uid>();
}

void soa::FileDataSource::StoreUser(std::string name, const data::User& user)
{
  const std::filesystem::path userFilePath = ProduceDataPath(
    _usersPath, name);

  std::ofstream file(userFilePath);
  if (not file.is_open())
    return;

  nlohmann::json json;
  json["name"] = user.name();
  json["token"] = user.token();
  json["characterUid"] = user.characterUid();

  file << json.dump(2);
}

void soa::FileDataSource::CreateCharacter(data::Character& character)
{
  _sequentialUid++;
  character.uid = _sequentialUid;
}

void soa::FileDataSource::RetrieveCharacter(data::Uid uid, data::Character& character)
{
  const std::filesystem::path dataFilePath = ProduceDataPath(
    _charactersPath, std::format("{}", uid));

  std::ifstream file(dataFilePath);
  if (not file.is_open())
    return;

  const auto json = nlohmann::json::parse(file);

  character.name = json["name"].get<std::string>();
  auto parts = json["parts"];
  character.parts = data::Character::Parts{
    .modelId = parts["modelId"].get<data::Uid>(),
    .mouthId = parts["mouthId"].get<data::Uid>(),
    .faceId = parts["faceId"].get<data::Uid>()};
  auto appearance = json["appearance"];
  character.appearance = data::Character::Appearance{
    .headSize = appearance["headSize"].get<uint32_t>(),
    .height = appearance["height"].get<uint32_t>(),
    .thighVolume = appearance["thighVolume"].get<uint32_t>(),
    .legVolume = appearance["legVolume"].get<uint32_t>()};
}

void soa::FileDataSource::StoreCharacter(data::Uid uid, const data::Character& character)
{
  const std::filesystem::path userFilePath = ProduceDataPath(
    _charactersPath, std::format("{}", uid));

  std::ofstream file(userFilePath);
  if (not file.is_open())
    return;

  nlohmann::json json;
  json["name"] = character.name();

  // character parts
  nlohmann::json parts;
  parts["modelId"] = character.parts.modelId();
  parts["mouthId"] = character.parts.mouthId();
  parts["faceId"] = character.parts.faceId();
  json["parts"] = parts;

  // character appearance
  nlohmann::json appearance;
  appearance["headSize"] = character.appearance.headSize();
  appearance["height"] = character.appearance.height();
  appearance["thighVolume"] = character.appearance.thighVolume();
  appearance["legVolume"] = character.appearance.legVolume();
  json["appearance"] = appearance;

  file << json.dump(2);
}

void soa::FileDataSource::RetrieveItem(data::Uid uid, data::Item& item)
{
  const std::filesystem::path dataFilePath = ProduceDataPath(
    _itemsPath, std::format("{}", uid));

  std::ifstream file(dataFilePath);
  if (not file.is_open())
    return;

  const auto json = nlohmann::json::parse(file);

  item.uid = json["uid"].get<data::Uid>();
  item.tid = json["tid"].get<data::Tid>();
  item.count = json["count"].get<uint32_t>();
  item.slot = static_cast<soa::data::Item::Slot>(json["slot"].get<int32_t>());
}

void soa::FileDataSource::StoreItem(data::Uid uid, const data::Item& item)
{
  const std::filesystem::path userFilePath = ProduceDataPath(
    _itemsPath, std::format("{}", uid));

  std::ofstream file(userFilePath);
  if (not file.is_open())
    return;

  nlohmann::json json;
  json["uid"] = item.uid();
  json["tid"] = item.tid();
  json["count"] = item.count();
  json["slot"] = item.slot();
  file << json.dump(2);
}

void soa::FileDataSource::RetrieveHorse(data::Uid uid, data::Horse& horse)
{
  const std::filesystem::path dataFilePath = ProduceDataPath(
    _horsesPath, std::format("{}", uid));

  std::ifstream file(dataFilePath);
  if (not file.is_open())
    return;

  const auto json = nlohmann::json::parse(file);

  horse.name = json["name"].get<std::string>();
}

void soa::FileDataSource::StoreHorse(data::Uid uid, const data::Horse& horse)
{
  const std::filesystem::path userFilePath = ProduceDataPath(
    _horsesPath, std::format("{}", uid));

  std::ofstream file(userFilePath);
  if (not file.is_open())
    return;

  nlohmann::json json;
  json["name"] = horse.name();
  file << json.dump(2);
}

void soa::FileDataSource::RetrieveRanch(data::Uid uid, data::Ranch& ranch)
{
  const std::filesystem::path dataFilePath = ProduceDataPath(
    _ranchesPath, std::format("{}", uid));

  std::ifstream file(dataFilePath);
  if (not file.is_open())
    return;

  const auto json = nlohmann::json::parse(file);

  ranch.name = json["name"].get<std::string>();
}

void soa::FileDataSource::StoreRanch(data::Uid uid, const data::Ranch& ranch)
{
  const std::filesystem::path userFilePath = ProduceDataPath(
    _ranchesPath, std::format("{}", uid));

  std::ofstream file(userFilePath);
  if (not file.is_open())
    return;

  nlohmann::json json;
  json["name"] = ranch.name();
  file << json.dump(2);
}
