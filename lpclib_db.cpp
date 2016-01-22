#include <iostream>
#include <sstream>
#include "lpclib.h"
#include "vector.h"
using namespace std;

#define THUMPER_IP "205.155.225.12"
#define INSERT_LIMIT 10

extern int __lpclib_system_messages;

static void Log(string msg)
{
    if (__lpclib_system_messages)
        cout << "[DB: " << msg << "]\n";
}

//MYSQL * sql;

// just runs the query and errors if invalid
static void InitiateQuery(string query)
{
    /*
    if (mysql_query(sql, query.c_str()) != 0)
        Error ("Internal error (Schatz's fault!) - DB query error");
     */
}

// sends query, but
// caller should free the result set themselves
//static MYSQL_RES * DoSelectQuery(string query)
//{
    /*
    InitiateQuery(query);
    MYSQL_RES * result = mysql_store_result(sql);
    if (result == NULL)
        Error("Internal error (Schatz' fault!) - DB query result ptr is null");
    return (result);
     */
//    return NULL;
//}

// returns # of rows query results in
static unsigned long CheckSelectQuery(string query)
{
    /*
    InitiateQuery(query);
    MYSQL_RES * result = mysql_store_result(sql);
    if (result == NULL)
        Error("Internal error (Schatz' fault!) - DB query result ptr is null");
    unsigned long numrows = mysql_num_rows(result);
    mysql_free_result(result);
    return (numrows);
     */
    return 0;
}

static void DoResultlessQuery(string query)
{
    /*
    InitiateQuery(query);
    MYSQL_RES * result = mysql_use_result(sql);
    if (result != NULL)
        Error("Internal error (Schatz' fault!) - DB query should have no result but it does");
    mysql_free_result(result);
     */
}

static int GetSingleIntResult(string query)
{
    /*
    MYSQL_RES * result = DoSelectQuery(query);
    if (mysql_num_rows(result) == 0)
        Error("Internal error (Schatz' fault!) - empty result");
    int num = StringToInt( (mysql_fetch_row(result))[0] );
    mysql_free_result(result);
    return (num);
     */
    return 0;
}


void ConnectToDB(string username, string password)
{
    //Error("LPC CS Database connectivity isn't supported in this version of the library.");
    if (username.substr(0,2) != "cs" && (username != password))
    {
        Error("Connection failed. Use your course name (lowercase) as the username and password"); 
    }
}

static void AuthCheck(int ID, int authcode)
{
    /*
    stringstream ss;
    ss << "select ID from users where ID=" << ID
        << " and auth=" << authcode;
    if (CheckSelectQuery(ss.str()) == 0)
        Error("DB access failed - invalid ID and/or auth code");
    Log ("auth ok");
     */
    // Error("LPC CS Database connectivity isn't supported in this version of the library.");
}

static void Connect(int ID, int authcode)
{
    //sql = mysql_init(NULL);
    //if (!sql) Error ("DB initalization failed - memory error");
    //if (!mysql_real_connect(sql, THUMPER_IP, "student", "2012SpringCS1", "lpc", 0, NULL, 0))
    //{
    //    Error ("DB initialization failed - no connection to server");
    //}
    AuthCheck(ID, authcode);
}

static void Close()
{
//    mysql_close(sql);
}

void DBInsertRecord(int ID, int authcode, string record)
{
    Connect(ID, authcode);
/*
    stringstream gg, ss;
    gg << "select count(*) from records where whoentered=" << ID <<
        " and date(whenentered) = date(now())";
    ss << "insert into records values ('" << record << "', " << ID
                            << ", now())";
    if (GetSingleIntResult(gg.str()) >= INSERT_LIMIT)
        Error ("DBInsertRecord failed - insert limit exceeded");
    DoResultlessQuery(ss.str());
    Close();
 */
}

Vector<string> DBRetrieveAllRecords(int ID, int authcode)
{
    Vector<string> all;
    Connect(ID, authcode);

    all.add("Bunnies are fluffy");
    /*
    MYSQL_RES * result = DoSelectQuery("select record from records");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        cout << row[0] << endl;
        all.push_back(row[0]);
    }
    mysql_free_result(result);
    Close();
    */
    return (all);
}

Vector<string> DBRetrieveMyRecords(int ID, int authcode)
{
    Vector<string> v;
    Connect(ID, authcode);
    return (v);
}
