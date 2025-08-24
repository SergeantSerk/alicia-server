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

#include "libserver/data/DataDirector.hpp"

#include <cassert>

namespace
{

//! Extracts the UID of a record.
//! @tparam T The type of the record.
//! @param record The record.
//! @return The UID of the record.
template<typename T>
server::data::Uid GetRecordUid(T& record)
{
    server::data::Uid uid = server::data::InvalidUid;
    record.Immutable([&uid](const auto& item) { uid = item.uid(); });
    return uid;
}

//! Perform test of the data director for users.
void TestDataDirector_User()
{
    // Create a data director.
    server::DataDirector dataDirector(".");

    // Test getting a non-existent user.
    auto nonExistentUserRecord = dataDirector.GetUser("non-existent-user");
    assert(!nonExistentUserRecord.IsAvailable());
}

//! Perform test of the data director for characters.
void TestDataDirector_Character()
{
    // Create a data director.
    server::DataDirector dataDirector(".");

    // Test getting a non-existent character.
    auto nonExistentCharacterRecord = dataDirector.GetCharacter(123);
    assert(!nonExistentCharacterRecord.IsAvailable());

    // Create a character.
    auto characterRecord = dataDirector.CreateCharacter();
    assert(characterRecord.IsAvailable());

    // Test getting an existent character.
    auto characterUid = GetRecordUid(characterRecord);
    auto existentCharacterRecord = dataDirector.GetCharacter(characterUid);
    assert(existentCharacterRecord.IsAvailable());
    assert(GetRecordUid(existentCharacterRecord) == characterUid);
}

//! Perform test of the data director for horses.
void TestDataDirector_Horse()
{
    // Create a data director.
    server::DataDirector dataDirector(".");

    // Test getting a non-existent horse.
    auto nonExistentHorseRecord = dataDirector.GetHorse(123);
    assert(!nonExistentHorseRecord.IsAvailable());

    // Create a horse.
    auto horseRecord = dataDirector.CreateHorse();
    assert(horseRecord.IsAvailable());

    // Test getting an existent horse.
    auto horseUid = GetRecordUid(horseRecord);
    auto existentHorseRecord = dataDirector.GetHorse(horseUid);
    assert(existentHorseRecord.IsAvailable());
    assert(GetRecordUid(existentHorseRecord) == horseUid);
}

//! Perform test of the data director for items.
void TestDataDirector_Item()
{
    // Create a data director.
    server::DataDirector dataDirector(".");

    // Test getting a non-existent item.
    auto nonExistentItemRecord = dataDirector.GetItem(123);
    assert(!nonExistentItemRecord.IsAvailable());

    // Create an item.
    auto itemRecord = dataDirector.CreateItem();
    assert(itemRecord.IsAvailable());

    // Test getting an existent item.
    auto itemUid = GetRecordUid(itemRecord);
    auto existentItemRecord = dataDirector.GetItem(itemUid);
    assert(existentItemRecord.IsAvailable());
    assert(GetRecordUid(existentItemRecord) == itemUid);
}

//! Perform test of the data director for storage items.
void TestDataDirector_StorageItem()
{
    // Create a data director.
    server::DataDirector dataDirector(".");

    // Test getting a non-existent storage item.
    auto nonExistentStorageItemRecord = dataDirector.GetStorageItem(123);
    assert(!nonExistentStorageItemRecord.IsAvailable());

    // Create a storage item.
    auto storageItemRecord = dataDirector.CreateStorageItem();
    assert(storageItemRecord.IsAvailable());

    // Test getting an existent storage item.
    auto storageItemUid = GetRecordUid(storageItemRecord);
    auto existentStorageItemRecord = dataDirector.GetStorageItem(storageItemUid);
    assert(existentStorageItemRecord.IsAvailable());
    assert(GetRecordUid(existentStorageItemRecord) == storageItemUid);
}

//! Perform test of the data director for eggs.
void TestDataDirector_Egg()
{
    // Create a data director.
    server::DataDirector dataDirector(".");

    // Test getting a non-existent egg.
    auto nonExistentEggRecord = dataDirector.GetEgg(123);
    assert(!nonExistentEggRecord.IsAvailable());

    // Create an egg.
    auto eggRecord = dataDirector.CreateEgg();
    assert(eggRecord.IsAvailable());

    // Test getting an existent egg.
    auto eggUid = GetRecordUid(eggRecord);
    auto existentEggRecord = dataDirector.GetEgg(eggUid);
    assert(existentEggRecord.IsAvailable());
    assert(GetRecordUid(existentEggRecord) == eggUid);
}

//! Perform test of the data director for pets.
void TestDataDirector_Pet()
{
    // Create a data director.
    server::DataDirector dataDirector(".");

    // Test getting a non-existent pet.
    auto nonExistentPetRecord = dataDirector.GetPet(123);
    assert(!nonExistentPetRecord.IsAvailable());

    // Create a pet.
    auto petRecord = dataDirector.CreatePet();
    assert(petRecord.IsAvailable());

    // Test getting an existent pet.
    auto petUid = GetRecordUid(petRecord);
    auto existentPetRecord = dataDirector.GetPet(petUid);
    assert(existentPetRecord.IsAvailable());
    assert(GetRecordUid(existentPetRecord) == petUid);
}

//! Perform test of the data director for guilds.
void TestDataDirector_Guild()
{
    // Create a data director.
    server::DataDirector dataDirector(".");

    // Test getting a non-existent guild.
    auto nonExistentGuildRecord = dataDirector.GetGuild(123);
    assert(!nonExistentGuildRecord.IsAvailable());

    // Create a guild.
    auto guildRecord = dataDirector.CreateGuild();
    assert(guildRecord.IsAvailable());

    // Test getting an existent guild.
    auto guildUid = GetRecordUid(guildRecord);
    auto existentGuildRecord = dataDirector.GetGuild(guildUid);
    assert(existentGuildRecord.IsAvailable());
    assert(GetRecordUid(existentGuildRecord) == guildUid);
}

//! Perform test of the data director for housing.
void TestDataDirector_Housing()
{
    // Create a data director.
    server::DataDirector dataDirector(".");

    // Test getting a non-existent housing.
    auto nonExistentHousingRecord = dataDirector.GetHousing(123);
    assert(!nonExistentHousingRecord.IsAvailable());

    // Create a housing.
    auto housingRecord = dataDirector.CreateHousing();
    assert(housingRecord.IsAvailable());

    // Test getting an existent housing.
    auto housingUid = GetRecordUid(housingRecord);
    auto existentHousingRecord = dataDirector.GetHousing(housingUid);
    assert(existentHousingRecord.IsAvailable());
    assert(GetRecordUid(existentHousingRecord) == housingUid);
}

} // namespace

int main()
{
    TestDataDirector_User();
    TestDataDirector_Character();
    TestDataDirector_Horse();
    TestDataDirector_Item();
    TestDataDirector_StorageItem();
    TestDataDirector_Egg();
    TestDataDirector_Pet();
    TestDataDirector_Guild();
    TestDataDirector_Housing();
}
