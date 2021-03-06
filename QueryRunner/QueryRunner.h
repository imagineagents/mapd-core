/*
 * Copyright 2017 MapD Technologies, Inc.
 *
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

#ifndef QUERY_RUNNER_H
#define QUERY_RUNNER_H

#include "../QueryEngine/CompilationOptions.h"
#include "LeafAggregator.h"

#include <memory>
#include <string>

namespace Catalog_Namespace {
class SessionInfo;
} // namespace Catalog_Namespace

class ResultSet;
class ExecutionResult;

namespace QueryRunner {

LeafAggregator* get_leaf_aggregator();

Catalog_Namespace::SessionInfo* get_distributed_session(const char* db_path);

Catalog_Namespace::SessionInfo* get_session(const char* db_path,
                                            std::vector<LeafHostInfo> string_servers,
                                            std::vector<LeafHostInfo> leaf_servers);

Catalog_Namespace::SessionInfo* get_session(const char* db_path);

ExecutionResult run_select_query(const std::string& query_str,
                                 const std::unique_ptr<Catalog_Namespace::SessionInfo>& session,
                                 const ExecutorDeviceType device_type,
                                 const bool hoist_literals,
                                 const bool allow_loop_joins);

std::shared_ptr<ResultSet> run_multiple_agg(const std::string& query_str,
                                            const std::unique_ptr<Catalog_Namespace::SessionInfo>& session,
                                            const ExecutorDeviceType device_type,
                                            const bool hoist_literals,
                                            const bool allow_loop_joins);

void run_ddl_statement(const std::string& create_table_stmt,
                       const std::unique_ptr<Catalog_Namespace::SessionInfo>& session);

std::shared_ptr<ResultSet> run_sql_distributed(const std::string& query_str,
                                               const std::unique_ptr<Catalog_Namespace::SessionInfo>& session,
                                               const ExecutorDeviceType device_type,
                                               bool allow_loop_joins);

}  // namespace QueryRunner

#endif  // QUERY_RUNNER_H
