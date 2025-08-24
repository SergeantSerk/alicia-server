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

} // namespace

int main()
{
    TestDataDirector_CharacterWithPets();
    TestDataDirector_CharacterWithItems();
    TestDataDirector_GuildWithCharacters();
}