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

// ------------------------------------------------------------------------------------------------
//- Helpers
// ------------------------------------------------------------------------------------------------

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

// ------------------------------------------------------------------------------------------------
//- Simple Tests
// ------------------------------------------------------------------------------------------------

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

// ------------------------------------------------------------------------------------------------
//- Complex Tests
// ------------------------------------------------------------------------------------------------

//! Perform test of a character with multiple pets.
void TestDataDirector_CharacterWithPets()
{
    // Create a data director.
    server::DataDirector dataDirector(".");

    // Create a character.
    auto characterRecord = dataDirector.CreateCharacter();
    assert(characterRecord.IsAvailable());

    // Create a few pets.
    auto petRecord1 = dataDirector.CreatePet();
    assert(petRecord1.IsAvailable());
    auto petRecord2 = dataDirector.CreatePet();
    assert(petRecord2.IsAvailable());

    // Add the pets to the character.
    auto petUid1 = GetRecordUid(petRecord1);
    auto petUid2 = GetRecordUid(petRecord2);
    characterRecord.Mutable([petUid1, petUid2](auto& character) {
        character.pets().emplace_back(petUid1);
        character.pets().emplace_back(petUid2);
    });

    // Verify that the character has the pets.
    auto characterUid = GetRecordUid(characterRecord);
    auto existentCharacterRecord = dataDirector.GetCharacter(characterUid);
    assert(existentCharacterRecord.IsAvailable());
    existentCharacterRecord.Immutable([petUid1, petUid2](const auto& character) {
        assert(character.pets().size() == 2);
        assert(character.pets()[0] == petUid1);
        assert(character.pets()[1] == petUid2);
    });
}

//! Perform test of a character with multiple items.
void TestDataDirector_CharacterWithItems()
{
    // Create a data director.
    server::DataDirector dataDirector(".");

    // Create a character.
    auto characterRecord = dataDirector.CreateCharacter();
    assert(characterRecord.IsAvailable());

    // Create a few items.
    auto itemRecord1 = dataDirector.CreateItem();
    assert(itemRecord1.IsAvailable());
    auto itemRecord2 = dataDirector.CreateItem();
    assert(itemRecord2.IsAvailable());

    // Add the items to the character.
    auto itemUid1 = GetRecordUid(itemRecord1);
    auto itemUid2 = GetRecordUid(itemRecord2);
    characterRecord.Mutable([itemUid1, itemUid2](auto& character) {
        character.items().emplace_back(itemUid1);
        character.items().emplace_back(itemUid2);
    });

    // Verify that the character has the items.
    auto characterUid = GetRecordUid(characterRecord);
    auto existentCharacterRecord = dataDirector.GetCharacter(characterUid);
    assert(existentCharacterRecord.IsAvailable());
    existentCharacterRecord.Immutable([itemUid1, itemUid2](const auto& character) {
        assert(character.items().size() == 2);
        assert(character.items()[0] == itemUid1);
        assert(character.items()[1] == itemUid2);
    });
}

//! Perform test of multiple characters in a guild.
void TestDataDirector_GuildWithCharacters()
{
    // Create a data director.
    server::DataDirector dataDirector(".");

    // Create a guild.
    auto guildRecord = dataDirector.CreateGuild();
    assert(guildRecord.IsAvailable());
    auto guildUid = GetRecordUid(guildRecord);

    // Create a few characters.
    auto characterRecord1 = dataDirector.CreateCharacter();
    assert(characterRecord1.IsAvailable());
    auto characterRecord2 = dataDirector.CreateCharacter();
    assert(characterRecord2.IsAvailable());

    // Add the characters to the guild.
    auto characterUid1 = GetRecordUid(characterRecord1);
    auto characterUid2 = GetRecordUid(characterRecord2);
    characterRecord1.Mutable([guildUid](auto& character) { character.guildUid() = guildUid; });
    characterRecord2.Mutable([guildUid](auto& character) { character.guildUid() = guildUid; });

    // Verify that the characters are in the guild.
    auto existentCharacterRecord1 = dataDirector.GetCharacter(characterUid1);
    assert(existentCharacterRecord1.IsAvailable());
    existentCharacterRecord1.Immutable([guildUid](const auto& character) {
        assert(character.guildUid() == guildUid);
    });
    auto existentCharacterRecord2 = dataDirector.GetCharacter(characterUid2);
    assert(existentCharacterRecord2.IsAvailable());
    existentCharacterRecord2.Immutable([guildUid](const auto& character) {
        assert(character.guildUid() == guildUid);
    });
}

// ------------------------------------------------------------------------------------------------
//- Comprehensive Tests
// ------------------------------------------------------------------------------------------------

//! Perform a comprehensive test of user data.
void TestDataDirector_Comprehensive_User()
{
    server::DataDirector dataDirector(".");
    auto& userStorage = dataDirector.GetUsers();

    // Create a user and set its fields.
    auto userRecord = userStorage.Create("test-user");
    userRecord.Mutable([](auto& user) {
        user.token() = "test-token";
        user.characterUid() = 1;
    });

    // Verify the user's fields.
    auto existentUserRecord = userStorage.Get("test-user");
    assert(existentUserRecord.IsAvailable());
    existentUserRecord.Immutable([](const auto& user) {
        assert(user.name() == "test-user");
        assert(user.token() == "test-token");
        assert(user.characterUid() == 1);
    });
}

//! Perform a comprehensive test of character data.
void TestDataDirector_Comprehensive_Character()
{
    server::DataDirector dataDirector(".");

    // Create a character and set its fields.
    auto characterRecord = dataDirector.CreateCharacter();
    characterRecord.Mutable([](auto& character) {
        character.name() = "test-character";
        character.introduction() = "test-introduction";
        character.level() = 10;
        character.carrots() = 100;
        character.cash() = 1000;
        character.role() = server::data::Character::Role::GameMaster;
        character.parts.modelId() = 1;
        character.parts.mouthId() = 2;
        character.parts.faceId() = 3;
        character.appearance.voiceId() = 4;
        character.appearance.headSize() = 5;
        character.appearance.height() = 6;
        character.appearance.thighVolume() = 7;
        character.appearance.legVolume() = 8;
        character.appearance.emblemId() = 9;
        character.isRanchLocked() = false;
    });

    // Verify the character's fields.
    auto characterUid = GetRecordUid(characterRecord);
    auto existentCharacterRecord = dataDirector.GetCharacter(characterUid);
    assert(existentCharacterRecord.IsAvailable());
    existentCharacterRecord.Immutable([](const auto& character) {
        assert(character.name() == "test-character");
        assert(character.introduction() == "test-introduction");
        assert(character.level() == 10);
        assert(character.carrots() == 100);
        assert(character.cash() == 1000);
        assert(character.role() == server::data::Character::Role::GameMaster);
        assert(character.parts.modelId() == 1);
        assert(character.parts.mouthId() == 2);
        assert(character.parts.faceId() == 3);
        assert(character.appearance.voiceId() == 4);
        assert(character.appearance.headSize() == 5);
        assert(character.appearance.height() == 6);
        assert(character.appearance.thighVolume() == 7);
        assert(character.appearance.legVolume() == 8);
        assert(character.appearance.emblemId() == 9);
        assert(character.isRanchLocked() == false);
    });
}

//! Perform a comprehensive test of horse data.
void TestDataDirector_Comprehensive_Horse()
{
    server::DataDirector dataDirector(".");

    // Create a horse and set its fields.
    auto horseRecord = dataDirector.CreateHorse();
    horseRecord.Mutable([](auto& horse) {
        horse.name() = "test-horse";
        horse.tid() = 1;
        horse.parts.skinTid() = 2;
        horse.parts.faceTid() = 3;
        horse.parts.maneTid() = 4;
        horse.parts.tailTid() = 5;
        horse.appearance.scale() = 6;
        horse.appearance.legLength() = 7;
        horse.appearance.legVolume() = 8;
        horse.appearance.bodyLength() = 9;
        horse.appearance.bodyVolume() = 10;
        horse.stats.agility() = 11;
        horse.stats.courage() = 12;
        horse.stats.rush() = 13;
        horse.stats.endurance() = 14;
        horse.stats.ambition() = 15;
        horse.mastery.spurMagicCount() = 16;
        horse.mastery.jumpCount() = 17;
        horse.mastery.slidingTime() = 18;
        horse.mastery.glidingDistance() = 19;
        horse.rating() = 20;
        horse.clazz() = 21;
        horse.clazzProgress() = 22;
        horse.grade() = 23;
        horse.growthPoints() = 24;
        horse.potentialType() = 25;
        horse.potentialLevel() = 26;
        horse.luckState() = 27;
        horse.emblemUid() = 28;
    });

    // Verify the horse's fields.
    auto horseUid = GetRecordUid(horseRecord);
    auto existentHorseRecord = dataDirector.GetHorse(horseUid);
    assert(existentHorseRecord.IsAvailable());
    existentHorseRecord.Immutable([](const auto& horse) {
        assert(horse.name() == "test-horse");
        assert(horse.tid() == 1);
        assert(horse.parts.skinTid() == 2);
        assert(horse.parts.faceTid() == 3);
        assert(horse.parts.maneTid() == 4);
        assert(horse.parts.tailTid() == 5);
        assert(horse.appearance.scale() == 6);
        assert(horse.appearance.legLength() == 7);
        assert(horse.appearance.legVolume() == 8);
        assert(horse.appearance.bodyLength() == 9);
        assert(horse.appearance.bodyVolume() == 10);
        assert(horse.stats.agility() == 11);
        assert(horse.stats.courage() == 12);
        assert(horse.stats.rush() == 13);
        assert(horse.stats.endurance() == 14);
        assert(horse.stats.ambition() == 15);
        assert(horse.mastery.spurMagicCount() == 16);
        assert(horse.mastery.jumpCount() == 17);
        assert(horse.mastery.slidingTime() == 18);
        assert(horse.mastery.glidingDistance() == 19);
        assert(horse.rating() == 20);
        assert(horse.clazz() == 21);
        assert(horse.clazzProgress() == 22);
        assert(horse.grade() == 23);
        assert(horse.growthPoints() == 24);
        assert(horse.potentialType() == 25);
        assert(horse.potentialLevel() == 26);
        assert(horse.luckState() == 27);
        assert(horse.emblemUid() == 28);
    });
}

//! Perform a comprehensive test of item data.
void TestDataDirector_Comprehensive_Item()
{
    server::DataDirector dataDirector(".");

    // Create an item and set its fields.
    auto itemRecord = dataDirector.CreateItem();
    itemRecord.Mutable([](auto& item) {
        item.tid() = 1;
        item.count() = 10;
    });

    // Verify the item's fields.
    auto itemUid = GetRecordUid(itemRecord);
    auto existentItemRecord = dataDirector.GetItem(itemUid);
    assert(existentItemRecord.IsAvailable());
    existentItemRecord.Immutable([](const auto& item) {
        assert(item.tid() == 1);
        assert(item.count() == 10);
    });
}

//! Perform a comprehensive test of pet data.
void TestDataDirector_Comprehensive_Pet()
{
    server::DataDirector dataDirector(".");

    // Create a pet and set its fields.
    auto petRecord = dataDirector.CreatePet();
    petRecord.Mutable([](auto& pet) {
        pet.name() = "test-pet";
        pet.itemUid() = 1;
        pet.petId() = 2;
    });

    // Verify the pet's fields.
    auto petUid = GetRecordUid(petRecord);
    auto existentPetRecord = dataDirector.GetPet(petUid);
    assert(existentPetRecord.IsAvailable());
    existentPetRecord.Immutable([](const auto& pet) {
        assert(pet.name() == "test-pet");
        assert(pet.itemUid() == 1);
        assert(pet.petId() == 2);
    });
}

//! Perform a comprehensive test of storage item data.
void TestDataDirector_Comprehensive_StorageItem()
{
    server::DataDirector dataDirector(".");

    // Create a storage item and set its fields.
    auto storageItemRecord = dataDirector.CreateStorageItem();
    storageItemRecord.Mutable([](auto& storageItem) {
        storageItem.sender() = "test-sender";
        storageItem.message() = "test-message";
        storageItem.checked() = true;
        storageItem.expired() = false;
    });

    // Verify the storage item's fields.
    auto storageItemUid = GetRecordUid(storageItemRecord);
    auto existentStorageItemRecord = dataDirector.GetStorageItem(storageItemUid);
    assert(existentStorageItemRecord.IsAvailable());
    existentStorageItemRecord.Immutable([](const auto& storageItem) {
        assert(storageItem.sender() == "test-sender");
        assert(storageItem.message() == "test-message");
        assert(storageItem.checked() == true);
        assert(storageItem.expired() == false);
    });
}

//! Perform a comprehensive test of egg data.
void TestDataDirector_Comprehensive_Egg()
{
    server::DataDirector dataDirector(".");

    // Create an egg and set its fields.
    auto eggRecord = dataDirector.CreateEgg();
    eggRecord.Mutable([](auto& egg) {
        egg.tid() = 1;
        egg.petTid() = 2;
    });

    // Verify the egg's fields.
    auto eggUid = GetRecordUid(eggRecord);
    auto existentEggRecord = dataDirector.GetEgg(eggUid);
    assert(existentEggRecord.IsAvailable());
    existentEggRecord.Immutable([](const auto& egg) {
        assert(egg.tid() == 1);
        assert(egg.petTid() == 2);
    });
}

//! Perform a comprehensive test of housing data.
void TestDataDirector_Comprehensive_Housing()
{
    server::DataDirector dataDirector(".");

    // Create a housing and set its fields.
    auto housingRecord = dataDirector.CreateHousing();
    housingRecord.Mutable([](auto& housing) {
        housing.housingId() = 1;
        housing.durability() = 100;
    });

    // Verify the housing's fields.
    auto housingUid = GetRecordUid(housingRecord);
    auto existentHousingRecord = dataDirector.GetHousing(housingUid);
    assert(existentHousingRecord.IsAvailable());
    existentHousingRecord.Immutable([](const auto& housing) {
        assert(housing.housingId() == 1);
        assert(housing.durability() == 100);
    });
}

//! Perform a comprehensive test of guild data.
void TestDataDirector_Comprehensive_Guild()
{
    server::DataDirector dataDirector(".");

    // Create a guild and set its fields.
    auto guildRecord = dataDirector.CreateGuild();
    guildRecord.Mutable([](auto& guild) {
        guild.name() = "test-guild";
    });

    // Verify the guild's fields.
    auto guildUid = GetRecordUid(guildRecord);
    auto existentGuildRecord = dataDirector.GetGuild(guildUid);
    assert(existentGuildRecord.IsAvailable());
    existentGuildRecord.Immutable([](const auto& guild) {
        assert(guild.name() == "test-guild");
    });
}

//! Perform a comprehensive test of complex scenarios.
void TestDataDirector_Comprehensive_Complex()
{
    server::DataDirector dataDirector(".");

    // Create a character.
    auto characterRecord = dataDirector.CreateCharacter();

    // Create a horse and set it as the character's mount.
    auto horseRecord = dataDirector.CreateHorse();
    auto horseUid = GetRecordUid(horseRecord);
    characterRecord.Mutable([horseUid](auto& character) {
        character.mountUid() = horseUid;
    });

    // Create a pet and set it as the character's pet.
    auto petRecord = dataDirector.CreatePet();
    auto petUid = GetRecordUid(petRecord);
    characterRecord.Mutable([petUid](auto& character) {
        character.petUid() = petUid;
    });

    // Create items and add them to the character's equipment.
    auto itemRecord1 = dataDirector.CreateItem();
    auto itemRecord2 = dataDirector.CreateItem();
    auto itemUid1 = GetRecordUid(itemRecord1);
    auto itemUid2 = GetRecordUid(itemRecord2);
    characterRecord.Mutable([itemUid1, itemUid2](auto& character) {
        character.characterEquipment().emplace_back(itemUid1);
        character.mountEquipment().emplace_back(itemUid2);
    });

    // Create a storage item with items.
    auto storageItemRecord = dataDirector.CreateStorageItem();
    auto itemRecord3 = dataDirector.CreateItem();
    auto itemRecord4 = dataDirector.CreateItem();
    auto itemUid3 = GetRecordUid(itemRecord3);
    auto itemUid4 = GetRecordUid(itemRecord4);
    storageItemRecord.Mutable([itemUid3, itemUid4](auto& storageItem) {
        storageItem.items().emplace_back(itemUid3);
        storageItem.items().emplace_back(itemUid4);
    });

    // Verify the complex scenario.
    auto characterUid = GetRecordUid(characterRecord);
    auto existentCharacterRecord = dataDirector.GetCharacter(characterUid);
    assert(existentCharacterRecord.IsAvailable());
    existentCharacterRecord.Immutable([horseUid, petUid, itemUid1, itemUid2](const auto& character) {
        assert(character.mountUid() == horseUid);
        assert(character.petUid() == petUid);
        assert(character.characterEquipment().size() == 1);
        assert(character.characterEquipment()[0] == itemUid1);
        assert(character.mountEquipment().size() == 1);
        assert(character.mountEquipment()[0] == itemUid2);
    });

    auto storageItemUid = GetRecordUid(storageItemRecord);
    auto existentStorageItemRecord = dataDirector.GetStorageItem(storageItemUid);
    assert(existentStorageItemRecord.IsAvailable());
    existentStorageItemRecord.Immutable([itemUid3, itemUid4](const auto& storageItem) {
        assert(storageItem.items().size() == 2);
        assert(storageItem.items()[0] == itemUid3);
        assert(storageItem.items()[1] == itemUid4);
    });
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
    TestDataDirector_CharacterWithPets();
    TestDataDirector_CharacterWithItems();
    TestDataDirector_GuildWithCharacters();
    TestDataDirector_Comprehensive_User();
    TestDataDirector_Comprehensive_Character();
    TestDataDirector_Comprehensive_Horse();
    TestDataDirector_Comprehensive_Item();
    TestDataDirector_Comprehensive_Pet();
    TestDataDirector_Comprehensive_StorageItem();
    TestDataDirector_Comprehensive_Egg();
    TestDataDirector_Comprehensive_Housing();
    TestDataDirector_Comprehensive_Guild();
    TestDataDirector_Comprehensive_Complex();
}