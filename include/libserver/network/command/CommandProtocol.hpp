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

#ifndef COMMAND_PROTOCOL_HPP
#define COMMAND_PROTOCOL_HPP

#include <array>
#include <cstdint>
#include <string_view>

namespace alicia
{

//! A constant buffer size for message magic.
//! The maximum size of message payload is 4092 bytes.
//! The extra 4 bytes are reserved for message magic.
constexpr uint16_t BufferSize = 4096;

//! When switching between scenes due to user interaction,
//! a client may request blocking until it receives a specific response from the server.
//! Setting this bit prevents the client from resolving the scene lock when
//! the message is receieved.
constexpr uint16_t ResolveSceneLockBit = 1 << 15;

//! XOR code.
using XorCode = std::array<std::byte, 4>;

//! A constant 4-byte XOR control value,
//! with which message bytes are XORed.
constexpr int32_t XorControl{
  static_cast<int32_t>(0xA20191CB)};

//! XOR rolling key algorithm constant
constexpr int32_t XorMultiplier{
  0x20080825};

//! Message magic with which all messages are prefixed.
struct MessageMagic
{
  //! An ID of the message.
  uint16_t id{0};
  //! A length of message payload.
  //! Maximum payload length is 4092 bytes.
  uint16_t length{0};
};

//! Decode message magic value.
//!
//! @param value Magic value.
//! @return Decoded message magic.
MessageMagic decode_message_magic(uint32_t value);

//! Encode message magic.
//!
//! @param magic Message magic.
//! @return Encoded message magic value.
uint32_t encode_message_magic(MessageMagic magic);

//! IDs of the commands in the protocol.
enum class CommandId : uint16_t
{
  LobbyLogin = 0x7,
  LobbyLoginOK = 0x8,
  LobbyLoginCancel = 0x9,

  LobbyHeartbeat = 0x12,

  LobbyCreateNicknameNotify = 0x6b,
  LobbyCreateNickname = 0x6c,
  LobbyCreateNicknameCancel = 0x6e,

  LobbyEnterChannel = 0x2b,
  LobbyEnterChannelOK = 0x2c,
  LobbyEnterChannelCancel = 0x2d,

  LobbyMakeRoom = 0x13,
  LobbyMakeRoomOK = 0x14,
  LobbyMakeRoomCancel = 0x15,

  LobbyShowInventory = 0x007e,
  LobbyShowInventoryOK = 0x007f,
  LobbyShowInventoryCancel = 0x0080,

  LobbyAchievementCompleteList = 0x00e5,
  LobbyAchievementCompleteListOK = 0x00e6,
  LobbyAchievementCompleteListCancel = 0x00e7,

  LobbyRequestDailyQuestList = 0x0356,
  LobbyRequestDailyQuestListOK = 0x0357,
  // ToDo: Not sure about the cancel response being available.
  LobbyRequestDailyQuestListCancel = 0x0358,

  LobbyRequestLeagueInfo = 0x0376,
  LobbyRequestLeagueInfoOK = 0x0377,
  LobbyRequestLeagueInfoCancel = 0x0378,

  LobbyRequestQuestList = 0x03f8,
  LobbyRequestQuestListOK = 0x03f9,
  LobbyRequestQuestListCancel = 0x03fa,

  LobbyRequestSpecialEventList = 0x417,
  LobbyRequestSpecialEventListOK = 0x418,

  LobbyEnterRanch = 0xfc,
  LobbyEnterRanchOK = 0xfd,
  LobbyEnterRanchCancel = 0xfe,

  LobbyGetMessengerInfo = 0x186,
  LobbyGetMessengerInfoOK = 0x187,
  LobbyGetMessengerInfoCancel = 0x188,

  LobbyClientNotify = 0x309,

  LobbyGoodsShopList = 0xB2,
  LobbyGoodsShopListOK = 0xB3,
  LobbyGoodsShopListCancel = 0xB4,

  LobbyInquiryTreecash = 0x2b1,
  LobbyInquiryTreecashOK = 0x2b2,
  LobbyInquiryTreecashCancel = 0x2b3,

  LobbyGuildPartyList = 0x3c2,
  LobbyGuildPartyListOK = 0x3c3,

  LobbyEnterRandomRanch = 0x109,

  LobbyRequestPersonalInfo = 0xeb,
  LobbyPersonalInfo = 0xec,

  LobbySetIntroduction = 0x171,

  RanchEnterRanch = 0x12b,
  RanchEnterRanchCancel = 0x12d,
  RanchEnterRanchNotify = 0x12e,
  RanchEnterRanchOK = 0x12c,

  RanchHeartbeat = 0x9e,

  RanchSnapshot = 0x139,
  RanchSnapshotNotify = 0x13a,

  RanchCmdAction = 0x1c9,
  RanchCmdActionNotify = 0x1ca,

  RanchStuff = 0x1af,
  RanchStuffOK = 0x1b0,

  RanchUpdateBusyState = 0x1a8,
  RanchUpdateBusyStateNotify = 0x1a9,

  RanchSearchStallion = 0x145,
  RanchSearchStallionOK = 0x146,
  RanchSearchStallionCancel = 0x147,

  RanchEnterBreedingMarket = 0x13f,
  RanchEnterBreedingMarketOK = 0x140,
  RanchEnterBreedingMarketCancel = 0x141,

  RanchTryBreeding = 0x156,
  RanchTryBreedingOK = 0x157,
  RanchTryBreedingCancel = 0x158,

  RanchBreedingWishlist = 0x1e8,
  RanchBreedingWishlistCancel = 0x1ea,
  RanchBreedingWishlistOK = 0x1e9,

  RanchUpdateMountNickname = 0x197,
  RanchUpdateMountNicknameOK = 0x198,
  RanchUpdateMountNicknameCancel = 0x199,

  RanchRequestStorage = 0x299,
  RanchRequestStorageOK = 0x29a,
  RanchRequestStorageCancel = 0x29b,

  RanchGetItemFromStorage = 0x29e,
  RanchGetItemFromStorageOK = 0x29f,
  RanchGetItemFromStorageCancel = 0x2a0,

  RanchRequestNpcDressList = 0x44c,
  RanchRequestNpcDressListCancel = 0x44e,
  RanchRequestNpcDressListOK = 0x44d,

  RanchChat = 0x137,
  RanchChatNotify = 0x138,

  RanchWearEquipment = 0x81,
  RanchWearEquipmentOK = 0x82,
  RanchWearEquipmentCancel = 0x83,

  RanchRemoveEquipment = 0x84,
  RanchRemoveEquipmentOK = 0x85,
  RanchRemoveEquipmentCancel = 0x86,

  RanchUseItem = 0x1e0,
  RanchUseItemOK = 0x1e1,
  RanchUseItemCancel = 0x1e2,

  RanchUpdateEquipmentNotify = 0x14e,

  RanchSetIntroductionNotify = 0x174,

  RaceEnterRoom = 0x30,
  RaceEnterRoomNotify = 0x31,
  RaceEnterRoomOK = 0x32,
  RaceEnterRoomCancel = 0x33,

  RaceChangeRoomOptions = 0x54,
  RaceChangeRoomOptionsNotify = 0x55,

  RaceStartRace = 0x5a,
  RaceStartRaceNotify = 0x5b,
  RaceStartRaceCancel = 0x5c,

  UserRaceTimer = 0x1024,
  UserRaceTimerOK = 0x1025,

  RaceLoadingComplete = 0x1b6,
  RaceLoadingCompleteNotify = 0x1b7,

  RaceChat = 0x52,
  RaceChatNotify = 0x53,

  Count = 0xFFFF
};

//! Get the name of the command from its ID.
//! @param command ID of the command to retrieve the name for.
//! @returns If command is registered, name of the command.
//!          Otherwise, returns "n/a".
std::string_view GetCommandName(CommandId command);

} // namespace alicia

#endif // COMMAND_PROTOCOL_HPP
