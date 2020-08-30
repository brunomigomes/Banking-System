#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
using namespace std;


static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for (i=0; i<argc; i++){
        cout << "&s = &s\n" << azColName[i] << argv[i] << argv[i] << "NULL" <<endl;
        // printf("&s = &s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    cout << "\n" << endl;
    // printf("\n");
    return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   const char *sql;
   char username;
   char password;

   cout << "Type in your username: " <<endl;
   cin >> username;

   cout << "Type in your password: " <<endl;
   cin >> password;

   /* Open the database */

   rc = sqlite3_open("test.db", &db);

   if( rc ) {
       cerr << "Can't open database: %s\n" << sqlite3_errmsg(db);
    //   fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
       cout << "Opened database successfully\n" << endl;
    //   fprintf(stdout, "Opened database successfully\n");
   }
   
   /* Create SQL statement */

   sql = "INSERT INTO LOGIN ('USERNAME', 'PASSWORD') VALUES ('?','?');";

   /* Execute SQL statement */

   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

   if(rc!= SQLITE_OK){
       cerr << "SQL error" << &zErrMsg <<endl;
    //    void fprintf(stderr, "SQL error: &s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }else{
       cout<< "Table created successfully\n" << endl;
    //    void fprintf(stdout, 'Table created successfully\n');
   }
   sqlite3_close(db);
   return 0;
   
}

