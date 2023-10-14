//===----------------------------------------------------------------------===//
//                         DuckDB
//
// postgres_utils.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb.hpp"
#include <libpq-fe.h>

namespace duckdb {

struct PostgresTypeData {
	string type_name;
	int32_t precision;
	int32_t scale;
};

enum class PostgresTypeAnnotation {
	STANDARD,
	NUMERIC_AS_DOUBLE,
	CTID,
	JSONB
};

struct PostgresType {
	PostgresTypeAnnotation info = PostgresTypeAnnotation::STANDARD;
	vector<PostgresType> children;
};

class PostgresUtils {
public:
	static PGconn *PGConnect(const string &dsn);

	static LogicalType ToPostgresType(const LogicalType &input);
	static LogicalType TypeToLogicalType(const PostgresTypeData &input, PostgresType &postgres_type);
	static string TypeToString(const LogicalType &input);
	static uint32_t ToPostgresOid(const LogicalType &input);
};

} // namespace duckdb
