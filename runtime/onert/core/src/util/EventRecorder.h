/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ONERT_UTIL_EVENT_RECORDER_H__
#define __ONERT_UTIL_EVENT_RECORDER_H__

#include "util/TracingCtx.h"

#include <map>
#include <memory>
#include <mutex>

#include <vector>

// refer to https://docs.google.com/document/d/1CvAClvFfyA5R-PhYUmn5OOQtYMH4h6I0nSsKchNAySU/edit#
struct Event
{
  const onert::util::TracingCtx *tracing_ctx;

  std::string ph;                                        // Event type.
  std::string ts;                                        // tracing clock of timestamp of this event
  std::vector<std::pair<std::string, std::string>> args; // user-defined data: pairs of (key, value)

  virtual ~Event() = default;
};

struct DurationEvent : public Event
{
  uint32_t session_index = 0;
  uint32_t subg_index = 0;

protected:
  DurationEvent() = default;
};

struct SubgDurationEvent : public DurationEvent
{ /* same with DurationEvent */
};

// TODO Rename it to OperationDurationEvent
struct OpSeqDurationEvent : public DurationEvent
{
  // Note: DurationEvent's name and tid will be set by EventWriter
  std::string backend;
  uint32_t op_index;
  std::string op_name;
};

struct CounterEvent : public Event
{
  std::string name; // name of event
  std::string tid;  // thread ID
  std::map<std::string, std::string> values;
};

//
// Record Event as Chrome Trace Event File Format
//
// Refrence: https://docs.google.com/document/d/1CvAClvFfyA5R-PhYUmn5OOQtYMH4h6I0nSsKchNAySU/edit
//
class EventRecorder
{
public:
  EventRecorder() = default;

public:
  void emit(std::unique_ptr<DurationEvent> &&evt);
  void emit(const CounterEvent &evt);

public:
  const std::vector<std::unique_ptr<DurationEvent>> &duration_events() const
  {
    return _duration_events;
  }
  const std::vector<CounterEvent> &counter_events() const { return _counter_events; }

private:
  std::mutex _mu;
  std::vector<std::unique_ptr<DurationEvent>> _duration_events;
  std::vector<CounterEvent> _counter_events;
};

#endif // __ONERT_UTIL_EVENT_RECORDER_H__
