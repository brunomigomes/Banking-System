#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;

// Create a callback function  
int callback(void *NotUsed, int argc, char **argv, char **azColName){

    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value

    for(int i = 0; i < argc; i++) {
        
        // Show column name, value, and newline
        cout << azColName[i] << ": " << argv[i] << endl;
    
    }

    // Insert a newline
    cout << endl;

    // Return successful
    return 0;
}
  
int main() {

    // Pointer to SQLite connection
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg = 0;

    // Save the result of opening the file
    int rc;

    // Save any SQL
    string sql;

    // Save the result of opening the file
    rc = sqlite3_open("example.db", &db);
    
    if( rc ){
        // Show an error message
        cout << "DB Error: " << sqlite3_errmsg(db) << endl;
        // Close the connection
        sqlite3_close(db);
        // Return an error
        return(1);
    }

    // Save SQL to create a table
    sql = "CREATE TABLE PEOPLE ("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL);";
    
    // Run the SQL (convert the string to a C-String with c_str() )
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    // Save SQL insert data
    sql = "INSERT INTO PEOPLE ('ID', 'NAME') VALUES ('3','Jeff');";
    
    // Run the SQL (convert the string to a C-String with c_str() )
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    // Save SQL insert data
    sql = "INSERT INTO PEOPLE ('ID', 'NAME') VALUES ('2','Dan');";
    
    // Run the SQL (convert the string to a C-String with c_str() )
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    // Save SQL insert data
    sql = "INSERT INTO PEOPLE ('ID', 'NAME') VALUES ('1','Cara');";
    
    // Run the SQL (convert the string to a C-String with c_str() )
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    // Save SQL insert data
    sql = "SELECT * FROM 'PEOPLE';";
    
    // Run the SQL (convert the string to a C-String with c_str() )
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    
    // Close the SQL connection
    sqlite3_close(db);
    
    return 0;
}