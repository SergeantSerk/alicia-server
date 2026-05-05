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

#include "libserver/util/Scheduler.hpp"

namespace server
{

Scheduler::Scheduler() noexcept
{
  _jobHandle = _jobs.end();
}

void Scheduler::Tick()
{
  {
    std::scoped_lock lock(_jobsMutex);

    // Make sure there is jobs to execute.
    if (_jobs.empty())
      return;

    // If the job iterator is at the end cycle it back to the front,
    // since the job list is not empty.
    if (_jobHandle == _jobs.cend())
    {
      _jobHandle = _jobs.begin();
    }
  }

  // Iterate over the jobs until you find one that can be executed,
  // execute it and remove it from the job list.
  while (true)
  {
    auto& job = *_jobHandle;
    if (Clock::now() >= job.when)
    {
      try
      {
        job.task();

        // If the job has a period queue it for later.
        if (job.period > Clock::duration::zero())
        {
          job.when = Clock::now() + job.period;
        }
        else
        {
          std::scoped_lock lock(_jobsMutex);
          _jobHandle = _jobs.erase(_jobHandle);
        }

      }
      catch (const std::exception& x)
      {
        // Executing task for job threw an error, erase the job
        // and move onto the next one on the next tick.
        std::scoped_lock lock(_jobsMutex);
        _jobHandle = _jobs.erase(_jobHandle);

        throw x;
      }

      break;
    }

    {
      std::scoped_lock lock(_jobsMutex);
      if (++_jobHandle == _jobs.cend())
        break;
    }
  }
}

Scheduler::JobHandle Scheduler::Queue(
  const Task& task,
  const Clock::time_point when)
{
  std::scoped_lock lock(_jobsMutex);
  return _jobs.emplace(_jobs.end(), Job{
    .when = when,
    .task = task});
}

Scheduler::JobHandle Scheduler::QueueRepeating(
  const Task& task,
  const Clock::duration period)
{
  std::scoped_lock lock(_jobsMutex);
  return _jobs.emplace(_jobs.end(), Job{
    .period = period,
    .task = task,});
}

void Scheduler::Deque(const JobHandle handle)
{
  std::scoped_lock lock(_jobsMutex);
  _jobs.erase(handle);
}

} // namespace server
