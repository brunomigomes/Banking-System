#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;

// Create a callback function
int callback(void *NotUsed, int argc, char **argv, char **azColName)
{

    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value

    for (int i = 0; i < argc; i++)
    {

        // Show column name, value, and newline
        cout << azColName[i] << ": " << argv[i] << endl;
    }

    // Insert a newline
    cout << endl;

    // Return successful
    return 0;
}

int opcenter(){
    cout << "Welcome to the main page of your account!" << endl;
    return 0;
}

int newuser()
{

    sqlite3 *db;

    char *zErrMsg = 0;

    int rc;

    string sql;

    string username;

    string password;

    string operation;

    cout << "Type in your username: " << endl;
    cin >> username;

    cout << "Type in your password: " << endl;
    cin >> password;

    /* Open the database */

    rc = sqlite3_open("banking.db", &db);

    if (rc)
    {
        cout << "SQL error: " << sqlite3_errmsg(db) << endl;

        sqlite3_close(db);
        //    cerr << "Can't open database: %s\n" << sqlite3_errmsg(db);
        //   fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (1);
    }

    sql = "CREATE TABLE LOGIN ("
          "USERNAME STRING PRIMARY KEY     NOT NULL,"
          "PASSWORD STRING                 NOT NULL);";

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "INSERT INTO LOGIN ('USERNAME', 'PASSWORD') VALUES ('" + username + "', '" + password + "');";

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sqlite3_close(db);

    return 0;
}

int login()
{

    sqlite3 *db;

    char *zErrMsg = 0;

    int rc;

    string sql;

    string username;
    string password;

    cout << "Type in your username: " << endl;
    cin >> username;

    cout << "Type in your password: " << endl;
    cin >> password;

    /* Open the database */

    rc = sqlite3_open("banking.db", &db);

    if (rc)
    {
        cout << "SQL error: " << sqlite3_errmsg(db) << endl;

        sqlite3_close(db);
        //    cerr << "Can't open database: %s\n" << sqlite3_errmsg(db);
        //   fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (1);
    }

    sql = "CREATE TABLE LOGIN ("
          "USERNAME STRING PRIMARY KEY     NOT NULL,"
          "PASSWORD STRING                 NOT NULL);";

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);


    sql= "SELECT * FROM LOGIN WHERE USERNAME = '"+username+"' AND PASSWORD = '"+password+"'";

    
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    
    if (rc != SQLITE_OK){
        cout << "Invalid Account!" << endl;
        cout << "SQL error: " << sqlite3_errmsg(db) << endl;

        
        //    cerr << "Can't open database: %s\n" << sqlite3_errmsg(db);
        //   fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);   
    
    }if (rc == true) {
        cout << "Operation Ok" << endl; 

    }else{
        opcenter();
    }
    sqlite3_close(db);
    return 0;
}
int main()
{

    string operation;

    cout << "Welcome to the bank! " << endl;
    cout << "Select an option to continue: " << endl;

    cout << "R - Register for a new account" << endl;

    cout << "L - Login to your account" << endl;

    cin >> operation;

    if (operation == "R" || operation == "r")
    {
        newuser();
    }

    if (operation == "L" || operation == "l")
    {
        login();
    }
    
}
