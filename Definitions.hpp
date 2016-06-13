#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

// JSON storage parameters
#define JSON_STORAGE_FILENAME       "storage.json"
#define JSON_OPEN_FILE_FLAGS        (QFile::ReadWrite | QFile::Text)

#define JSON_KEY_HEADER_TITLE       "title"
#define JSON_VALUE_HEADER_TITLE     "IncomStats JSon storage file"

#define JSON_KEY_HEADER_APP_VER     "appVersion"
#define JSON_VALUE_HEADER_APP_VER   "1.0"

#define JSON_KEY_HEADER_MAGIC       "magic"
#define JSON_KEY_RECORDS            "records"

#define INCOME_ORDER_ID_KEY         "id"
#define INCOME_ORDER_AMOUNT_KEY     "amount"
#define INCOME_ORDER_DATE_KEY       "date"
#define INCOME_ORDER_TYPE_KEY       "type"
#define INCOME_ORDER_COMMENT_KEY    "comment"

#endif // DEFINITIONS_HPP
