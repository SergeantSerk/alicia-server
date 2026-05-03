/**
 * Alicia Server - dedicated server software
 * Copyright (C) 2026 Story Of Alicia
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

#include "server/ServerInstance.hpp"

#include "server/race/RaceDirector.hpp"
#include "server/race/RaceInstance.hpp"

#include <libserver/util/Util.hpp>

namespace server
{

RaceInstance::RaceInstance(
  RaceDirector& raceDirector,
  uint32_t roomUid) :
    _raceDirector(raceDirector),
    _roomUid(roomUid)
{

}

uint32_t RaceInstance::GetRoomUid()
{
  return _roomUid;
}

void RaceInstance::GetRoom(const std::function<void(Room&)>& consumer)
{
  _raceDirector._serverInstance.GetRoomSystem().GetRoom(
    _roomUid,
    consumer);
}

void RaceInstance::GetRoom(const std::function<void(const Room&)>& consumer) const
{
  _raceDirector._serverInstance.GetRoomSystem().GetRoom(
    _roomUid,
    consumer);
}

void RaceInstance::TickLoading()
{
  // Determine whether all racers have started racing.
  const bool allRacersLoaded = std::ranges::all_of(
    std::views::values(tracker.GetRacers()),
    [](const tracker::RaceTracker::Racer& racer)
    {
      return racer.state == tracker::RaceTracker::Racer::State::Racing
        || racer.state == tracker::RaceTracker::Racer::State::Disconnected;
    });

  const bool loadTimeoutReached = std::chrono::steady_clock::now() >= stageTimeoutTimePoint;

  // If not all the racers have loaded yet and the timeout has not been reached yet
  // do not start the race.
  if (not allRacersLoaded && not loadTimeoutReached)
    return;

  if (loadTimeoutReached)
  {
    spdlog::warn("Room {} has reached the loading timeout threshold",
      this->GetRoomUid());
  }

  for (auto& racer : tracker.GetRacers() | std::views::values)
  {
    // todo: handle the players that did not load in to the race.
    // for now just consider them disconnected
    if (racer.state != tracker::RaceTracker::Racer::State::Racing)
      racer.state = tracker::RaceTracker::Racer::State::Disconnected;
  }

  const auto mapBlockTemplate = _raceDirector._serverInstance.GetCourseRegistry().GetMapBlockInfo(
    raceMapBlockId);

  // Switch to the racing stage and set the timeout time point.
  stage = RaceInstance::Stage::Racing;
  stageTimeoutTimePoint = std::chrono::steady_clock::now() + std::chrono::seconds(
    mapBlockTemplate.timeLimit);

  // Set up the race start time point.
  const auto now = std::chrono::steady_clock::now();
  raceStartTimePoint = now + std::chrono::seconds(
    mapBlockTemplate.waitTime);

  const protocol::AcCmdUserRaceCountdown raceCountdown{
    .raceStartTimestamp = util::TimePointToRaceTimePoint(
      raceStartTimePoint)};

  // Broadcast the race countdown.
  _raceDirector.Broadcast(*this, raceCountdown);
}

void RaceInstance::TickRacing()
{
    const bool raceTimeoutReached = std::chrono::steady_clock::now() >= stageTimeoutTimePoint;

    const bool isFinishing = std::ranges::any_of(
      std::views::values(tracker.GetRacers()),
      [](const tracker::RaceTracker::Racer& racer)
      {
        return racer.state == tracker::RaceTracker::Racer::State::Finishing;
      });

    // If the race is not finishing and the timeout was not reached
    // do not finish the race.
    if (not isFinishing && not raceTimeoutReached)
      return;

    stage = RaceInstance::Stage::Finishing;
    stageTimeoutTimePoint = std::chrono::steady_clock::now() + std::chrono::seconds(15);

    // If the race timeout was reached notify the clients about the finale.
    if (raceTimeoutReached)
    {
      // Broadcast the race final (only to participants).
      this->GetRoom(
        [this](const server::Room& room)
        {
          const protocol::AcCmdUserRaceFinalNotify notify{};
          for (const auto& [characterUid, player] : room.GetPlayers())
          {
            const bool isParticipant = tracker.IsRacer(
              characterUid);

            if (not isParticipant)
              continue;

            _raceDirector._commandServer.QueueCommand<decltype(notify)>(
              player.GetClientId(),
              [notify]()
              {
                return notify;
              });
          }
        });
    }
}

void RaceInstance::TickFinishing()
{
  // TODO: transfer implementation
}

void RaceInstance::Tick()
{
  switch (stage)
  {
    case RaceInstance::Stage::Waiting:
      // Do nothing on waiting stage
      break;
    case RaceInstance::Stage::Loading:
      // Process rooms which are loading
      this->TickLoading();
      break;
    case RaceInstance::Stage::Racing:
      // Process rooms which are racing
      this->TickRacing();
      break;
    case RaceInstance::Stage::Finishing:
      this->TickFinishing();
      break;
  }
}

} // namespace server
