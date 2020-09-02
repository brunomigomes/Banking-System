#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;

bool auth;
string username;
string password;
string repeat;
bool ret;

// Create a callback function
int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value

    for (int i = 0; i < argc; i++)
    {

        // Show column name, value, and newline
        // if (argv[i] == '1'){
        //     bool auth = true;
        //     return auth;
        // }else{
        //     bool auth = false;
        //     return auth;
        // }
        if (ret == true){
        cout << azColName[i] << ": " << argv[i] << "$" << endl;
        }
        if (argv[i]){
            auth = true;
        } else{
            auth = false;
        }
        return auth;
    }


    // Insert a newline
    cout << endl;

    // Return successful
    return 0;
}

int balance(){
    sqlite3 *db;

    char *zErrMsg = 0;

    int rc;

    string sql;

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
          "PASSWORD STRING                 NOT NULL,"
          "BALANCE  DECIMAL                NOT NULL);";

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "SELECT BALANCE FROM LOGIN WHERE USERNAME = '"+username+"';";

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sqlite3_close(db);

    return 0;
}
int opcenter(){
    
    string selector;

    cout << "Welcome to the main page of your account!" << endl;
    cout << "Select what do you want to do: \n"
    "B - Balance; \n"
    "D - Deposit; \n"
    "W - Withdraw; \n" << endl;

    cin >> selector;

    if (selector == "B" || selector == "b"){
        balance(); //Calls "balance function"
    }

//     if (selector == "D" || selector == "d"){
//         deposit();
//     }

//     if (selector == "W" || selector == "w"){
//         withdraw();
//     }

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

    string cont;

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
          "PASSWORD STRING                 NOT NULL,"
          "BALANCE  DECIMAL                NOT NULL);";

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    sql = "INSERT INTO LOGIN ('USERNAME', 'PASSWORD', 'BALANCE') VALUES ('" + username + "', '" + password + "', 0);";

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    // cout << "Do you want to login now? (Y/N)" << endl;
    // cin >> cont;

    // if (cont == "Y" || cont == "y"){
    //     int login();
    // }
    // if (cont == "N" || cont == "n"){
    //     exit(0);
    // }

    sqlite3_close(db);


    
    return 0;
}

int login()
{

    sqlite3 *db;

    char *zErrMsg = 0;

    int rc;

    string sql;

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
          "PASSWORD STRING                 NOT NULL,"
          "BALANCE  FLOAT                   NOT NULL,);";

    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);


    sql= "SELECT 1 FROM LOGIN WHERE USERNAME = '"+username+"' AND PASSWORD = '"+password+"'";


    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);


    // if (rc != SQLITE_OK){
    //     cout << "SQL error: " << sqlite3_errmsg(db) << endl;
    //     return (0);   
    
    // }
    if (rc == true) {
        cout << "Operation Ok" << endl; 

    }if (auth == true){
        ret = true;
        opcenter();
    }else{
        cout << "Account does not exist! Do you want to try again or register? \n"
        "T - Try Again; \n"
        "C - Close; \n"
        "R - Register \n";
        cin >> repeat;

        if (repeat == "T" || repeat == "t"){
            login();
        }
        
        if (repeat == "C" || repeat == "c"){
            exit(0);
        }
        
        if (repeat == "R" ||  repeat == "r"){
            newuser();
        }

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
