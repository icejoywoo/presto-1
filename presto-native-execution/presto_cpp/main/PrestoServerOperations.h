/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <string>
#include "presto_cpp/main/TaskManager.h"

namespace proxygen {
class HTTPMessage;
class ResponseHandler;
} // namespace proxygen

namespace facebook::presto {

class PrestoServer;
struct ServerOperation;

/// Static class implements Presto Server Operations.
class PrestoServerOperations {
 public:
  PrestoServerOperations(TaskManager* taskManager, PrestoServer* server)
      : taskManager_(taskManager), server_(server) {}

  void runOperation(
      proxygen::HTTPMessage* message,
      proxygen::ResponseHandler* downstream);

  std::string connectorOperation(
      const ServerOperation& op,
      proxygen::HTTPMessage* message);

  std::string systemConfigOperation(
      const ServerOperation& op,
      proxygen::HTTPMessage* message);

  std::string veloxQueryConfigOperation(
      const ServerOperation& op,
      proxygen::HTTPMessage* message);

  std::string taskOperation(
      const ServerOperation& op,
      proxygen::HTTPMessage* message);

  std::string serverOperation(
      const ServerOperation& op,
      proxygen::HTTPMessage* message);

 private:
  std::string serverOperationTrace();

  std::string serverOperationSetState(proxygen::HTTPMessage* message);

  std::string serverOperationAnnouncer(proxygen::HTTPMessage* message);

  // Clears the in-memory (and optional ssd) cache.
  std::string serverOperationClearCache(proxygen::HTTPMessage* message);

  // Writes the in-memory cache into SSD and makes checkpoints.
  std::string serverOperationWriteSsd(proxygen::HTTPMessage* message);

  // Get/update the verbose log level of glog.
  std::string serverOperationGlog(proxygen::HTTPMessage* message);

  TaskManager* const taskManager_;
  PrestoServer* const server_;
};

} // namespace facebook::presto
