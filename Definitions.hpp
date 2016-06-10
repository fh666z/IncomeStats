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


#endif // DEFINITIONS_HPP
