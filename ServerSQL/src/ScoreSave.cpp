#include "ScoreSave.h"
#include "config.h"
#include <stdio.h>

MYSQL *conn;
bool init = false;
bool connectDatabase()
{
    conn = mysql_init(NULL);
    conn = mysql_real_connect(conn,  DatabaseIp, DatabaseUser, DatabasePassword, DatabaseName, atoi(DatabasePort), NULL, 0);
    if (conn == NULL)
    {
        printf("[-] Error connecting to database: Ip:%s User:%s Password:%s Name:%s\n", DatabaseIp, DatabaseUser, DatabasePassword, DatabaseName);
        mysql_close(conn);
        getchar();
        exit(1);
        return false;
    }
    return true;
}


void initMysql()
{
    connectDatabase();
    mysql_close(conn);
    printf("[+] MySQL initialized -> %s:%s %s.\n", DatabaseIp, DatabasePort, DatabaseName);
}

bool addPerson(char* personName,int score)
{
    connectDatabase();
    char sql[64];
    sprintf(sql, "INSERT INTO scoreboard VALUES ('%s', %d);", personName, score);
    printf("[+] %s\n", sql);
    int qstate = mysql_query(conn,sql);
    if (!qstate){
        printf("[+] Successfully added %s to the database.\n", personName);
        mysql_close(conn);
        return true;
    }
    
    printf("[-] Error adding %s to the database: %s\n", personName, mysql_error(conn));
    mysql_close(conn);
    return false;
}

bool getScores(std::vector<ScoreSaveData>& scores)
{
    connectDatabase();
    const char *sql = "SELECT * FROM scoreboard ORDER BY score DESC LIMIT 8;";
    printf("[+] %s\n", sql);
    int qstate = mysql_query(conn,sql);
    if(qstate)
    {
        printf("[-] Error getting scores: %s\n", mysql_error(conn));
        mysql_close(conn);
        return false;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;
    //int num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
    {
        ScoreSaveData data;
        char* name = (char*)row[0];
        //set all letters to uppercase
        for (int i = 0; i < strlen(name); i++)
        {
            name[i] = toupper(name[i]);
        }
        data.personName = name;
        data.score = atoi(row[1]);
        scores.push_back(data);
        printScore(data);
    }

    mysql_close(conn);
    return true;
}

void printScore(ScoreSaveData& scoreData)
{
    puts("----------------------------------------");
    printf("PersonName: %s\n", scoreData.personName);
    printf("Score: %d\n", scoreData.score);
    puts("----------------------------------------");
}
