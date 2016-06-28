#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#define USE_SQL_STORAGE

#ifndef USE_SQL_STORAGE
#define USE_JSON_STORAGE
#endif

//=============================================================================
// JSON storage parameters
//=============================================================================
#define JSON_STORAGE_FILENAME       "storage.json"
#define JSON_OPEN_FILE_FLAGS        (QFile::ReadWrite | QFile::Text)

#define JSON_KEY_HEADER_TITLE       "title"
#define JSON_VALUE_HEADER_TITLE     "IncomStats JSon storage file"

#define JSON_KEY_HEADER_APP_VER     "appVersion"
#define JSON_VALUE_HEADER_APP_VER   "1.0"

#define JSON_KEY_HEADER_MAGIC       "magic"
#define JSON_KEY_RECORDS            "records"
#define JSON_KEY_NUM_RECORDS        "numRecords"

#define INCOME_ORDER_ID_KEY         "id"
#define INCOME_ORDER_AMOUNT_KEY     "amount"
#define INCOME_ORDER_DATE_KEY       "date"
#define INCOME_ORDER_TYPE_KEY       "type"
#define INCOME_ORDER_COMMENT_KEY    "comment"

//=============================================================================
// SQL storage parameters
//=============================================================================
#define QSQL_DB_TYPE                "QMYSQL"
#define QSQL_HOSTNAME               "reb.wip.bg"
#define QSQL_DB_NAME                "incomestats"
#define QSQL_USER                   "root"
#define QSQL_USER_PASS              "IgorPederast1234"


#endif // DEFINITIONS_HPP
